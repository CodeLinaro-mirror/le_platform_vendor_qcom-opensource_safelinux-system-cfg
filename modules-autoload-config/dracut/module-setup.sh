# Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.$
# SPDX-License-Identifier: BSD-3-Clause-Clear$

#!/usr/bin/bash

# called by dracut
check() {
    return 0
}

# called by dracut
depends() {
    echo dracut-systemd systemd-modules-load
}

installkernel() {
# list of kernel modules to load during initramfs boot
# Necessary drivers for bringing up console and UFS based RootFS$
SA8775_INITRAMFS_DRIVERS=" \
    camcc-sa8775p \
    dispcc0-sa8775p \
    dispcc1-sa8775p \
    gpucc-sa8775p \
    videocc-sa8775p \
    pinctrl-spmi-gpio \
    pinctrl-spmi-mpp \
    nvmem_qcom-spmi-sdam \
    qcom-spmi-temp-alarm \
    virtio_mmio \
    virtio_net \
    failover \
    net_failover \
"

    instmods ${SA8775_INITRAMFS_DRIVERS}
    return 0
}

# called by dracut
install() {
    return 0
}
