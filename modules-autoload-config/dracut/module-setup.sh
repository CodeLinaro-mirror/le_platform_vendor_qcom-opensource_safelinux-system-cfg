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
    clk-qcom \
    gcc-sa8775p \
    pinctrl-msm \
    pinctrl-sa8775p \
    clk-rpmh \
    cmd-db \
    qcom_rpmh \
    rpmhpd \
    qcom-geni-se \
    qcom_geni_serial \
    qnoc-sa8775p \
    qcom-rpmh-regulator \
    phy-qcom-qmp-ufs \
    ufs_qcom \
    ext4 \
    jbd2 \
    governor_simpleondemand \
    ufshcd-core \
    ufshcd-pltfrm \
    camcc-sa8775p \
    dispcc0-sa8775p \
    dispcc1-sa8775p \
    gpucc-sa8775p \
    videocc-sa8775p \
    regmap-spmi \
    spmi \
    spmi-pmic-arb \
    pinctrl-spmi-gpio \
    pinctrl-spmi-mpp \
    qcom-spmi-pmic \
    nvmem_qcom-spmi-sdam \
    qcom-spmi-temp-alarm \
    virtio_blk \
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
