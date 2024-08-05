#!/bin/sh
# Copyright (c) 2023-2024 Qualcomm Innovation Center, Inc. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause-Clear

# shellcheck disable=SC1090

echo "3d00000.vfio_kgsl" > /sys/bus/platform/drivers/kiumd_kgsl/unbind
echo "soc@0:vfio_kgsl_lpac" > /sys/bus/platform/drivers/kiumd_kgsl/unbind

echo "vfio-platform" > /sys/bus/platform/devices/soc@0:vfio_kgsl_lpac/driver_override
echo "soc@0:vfio_kgsl_lpac" > /sys/bus/platform/drivers/vfio-platform/bind

# Assume only one conf file is present in /usr/lib/vfio-bind.d
# This conf file includes list of devices to bind to vfio-platform
conf_file=$(find /usr/lib/vfio-bind.d -name "*.conf")
if expr "X$conf_file" : 'X.*[[:space:]]' >/dev/null; then
    # space inside conf_file var means multiple conf files were found
    # currently only supporting one conf file per target
    exit 1
fi

. "$conf_file"

for DEV in $DEVS; do
	echo "vfio-platform" > /sys/bus/platform/devices/"$DEV"/driver_override
	echo "$DEV" > /sys/bus/platform/drivers/vfio-platform/bind
done
exit 0
