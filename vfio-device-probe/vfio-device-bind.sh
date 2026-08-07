#!/bin/sh
# Copyright (c) 2023-2024 Qualcomm Innovation Center, Inc. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause-Clear

# shellcheck disable=SC1090

KGSL_OVERRIDE_DIR="/sys/bus/platform/devices/1.vfio_kgsl_lpac/driver_override"
VFIO_BIND_DIR="/usr/lib/vfio-bind.d"
SECA_CONF="${VFIO_BIND_DIR}/seca_dev.conf"
NORD_CONF="${VFIO_BIND_DIR}/sa8797_dev.conf"
VFIO_DRIVER_BIND_NODE="/sys/bus/platform/drivers/vfio-platform/bind"
KIUMD_KGSL_UNBIND_NODE="/sys/bus/platform/drivers/kiumd_kgsl/unbind"

# Log to /dev/kmsg (dmesg)
log()
{
    echo "vfio-device-bind: $*" > /dev/kmsg 2>/dev/null || true
}

get_soc_id()
{
    if [ -r /sys/devices/soc0/soc_id ]; then
        cat /sys/devices/soc0/soc_id 2>/dev/null | tr -d '[:space:]'
    fi
}

get_machine_name()
{
    if [ -r /sys/devices/soc0/machine ]; then
        cat /sys/devices/soc0/machine 2>/dev/null | tr -d '\n'
    fi
}

get_single_conf_file()
{
    conf_count=0
    single_conf=""

    for conf in "${VFIO_BIND_DIR}"/*.conf; do
        [ -f "${conf}" ] || continue
        conf_count=$((conf_count + 1))
        single_conf="${conf}"
        [ "${conf_count}" -gt 1 ] && return 1
    done

    [ "${conf_count}" -eq 1 ] || return 1
    echo "${single_conf}"
}

select_conf_file()
{
    # Single-config targets do not need runtime ID selection.
    single_conf="$(get_single_conf_file)"
    if [ -n "${single_conf}" ]; then
        echo "${single_conf}"
        return 0
    fi

    socid="$(get_soc_id)"
    machine_name="$(get_machine_name)"

    # soc_id to machine mapping:
    # 742 -> QAM8787P
    # 690 -> QAM8797P
    # 689 -> QAM8397P
    case "${socid}" in
        742)
            [ -f "${SECA_CONF}" ] && echo "${SECA_CONF}" && return 0
            ;;
        689|690)
            [ -f "${NORD_CONF}" ] && echo "${NORD_CONF}" && return 0
            ;;
    esac

    case "${machine_name}" in
        *QAM8787P*)
            [ -f "${SECA_CONF}" ] && echo "${SECA_CONF}" && return 0
            ;;
        *QAM8397P*|*QAM8797P*)
            [ -f "${NORD_CONF}" ] && echo "${NORD_CONF}" && return 0
            ;;
    esac

    return 1
}

if [ "$(grep -c "vfio-platform" "$KGSL_OVERRIDE_DIR")" -ne '0' ];then
    echo "1.vfio_kgsl_lpac already probed"
else
    echo "1.vfio_kgsl" > /sys/bus/platform/drivers/kiumd_kgsl/unbind
    echo "1.vfio_kgsl_lpac" > /sys/bus/platform/drivers/kiumd_kgsl/unbind

    echo "vfio-platform" > $KGSL_OVERRIDE_DIR
    echo "1.vfio_kgsl_lpac" > /sys/bus/platform/drivers/vfio-platform/bind
fi

conf_file="$(select_conf_file)"
if [ -z "${conf_file}" ] || [ ! -f "${conf_file}" ]; then
    log "No vfio bind config in ${VFIO_BIND_DIR}" \
        "(soc_id=$(get_soc_id), machine=$(get_machine_name))"
    exit 1
fi

log "Using vfio bind config ${conf_file}"

. "${conf_file}"

if [ -z "${DEVS}" ]; then
    log "No devices defined in ${conf_file}"
    exit 1
fi

if [ ! -e "${VFIO_DRIVER_BIND_NODE}" ]; then
    log "vfio-platform bind node not found"
    exit 1
fi

for DEV in $DEVS; do
    (
        DEV_PATH="/sys/bus/platform/devices/${DEV}"
        [ -d "${DEV_PATH}" ] || { log "ERROR: ${DEV_PATH} not found"; exit 1; }

        # If this device is currently attached to kiumd_kgsl, unbind first.
        if [ -L "${DEV_PATH}/driver" ] && [ -e "${KIUMD_KGSL_UNBIND_NODE}" ]; then
            CUR_DRIVER="$(basename "$(readlink -f "${DEV_PATH}/driver")")"
            if [ "${CUR_DRIVER}" = "kiumd_kgsl" ]; then
                echo "${DEV}" > "${KIUMD_KGSL_UNBIND_NODE}" \
                    || { log "ERROR: Failed to unbind ${DEV} from kiumd_kgsl"; exit 1; }
            fi
        fi

        echo "vfio-platform" > "${DEV_PATH}/driver_override" \
            || { log "ERROR: Failed to set driver_override for ${DEV}"; exit 1; }

        echo "${DEV}" > "${VFIO_DRIVER_BIND_NODE}" \
            || { log "ERROR: Failed to bind ${DEV}"; exit 1; }
    ) &
done
wait

modprobe iommu_faults

if selinuxenabled && [ -x "$(command -v restorecon)" ]; then
    restorecon -vFR /dev
fi

echo 1 > /dev/vfio-complete

exit 0
