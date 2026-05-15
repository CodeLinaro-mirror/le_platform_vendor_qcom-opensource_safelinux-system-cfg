# SPDX-License-Identifier: GPL-2.0

ifneq ($(QCLINUX_BUILD), true)
# RH Kernel Case
dtb-y += sa8775p_overlay_rh.dtbo
dtb-y += sa8775p-v3_overlay_rh.dtbo
dtb-y += sa8770p-ride/sa8770p-ride.dtb
dtb-y += sa8775p-ride-mx/sa8775p-ride-mx_rh.dtb
dtb-y += sa8650p-ride/sa8650p-ride.dtb
dtb-y += sa8255p-ride/sa8255p-ride.dtb
dtb-$(CONFIG_ARCH_SA7255) += sa7255p-ride/sa7255p-ride_rh.dtb
dtb-$(CONFIG_ARCH_SA7255) += sa8620p-ride/sa8620p-ride_rh.dtb
dtb-y += sa8775p_overlay_pcie_ep_rh.dtbo
dtb-y += sa8775p-fw-managed-tmp.dtb
ifeq ($(shell uname -i), aarch64)
dtb-y += sa8775p-qvp/native/sa8775p-qvp.dtb
else
dtb-y += sa8775p-qvp/sa8775p-qvp_rh.dtb
endif
else
# QCLinux Kernel Case
dtb-y += sa8620p-ride/sa8620p-ride.dtb
dtb-y += sa8620p-ride/sa8620p-ride-v3.dtb
dtb-y += sa8620p-ride/sa8620p-ride_pcie_ep.dtb
dtb-y += sa8775p_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-v3_overlay.dtbo
dtb-y += sa8775p-ride-mx/sa8775p-ride-mx.dtb
dtb-y += sa8650p-ride-mx/sa8650p-ride-mx.dtb
dtb-y += sa7255p-ride/sa7255p_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-v3_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p_overlay_pcie_ep.dtbo
dtb-y += sa8775p-v3_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-v3_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p_overlay_pcie_ep.dtbo
dtb-y += sa8650p-ride/sa8650p_overlay_pcie_ep.dtbo
dtb-y += sa8775p_overlay_pcie_ep.dtbo
dtb-y += sa8255p-qvp/sa8255p-qvp.dtb
dtb-y += sa8775p-qvp/sa8775p-qvp.dtb
dtb-y += sa8775p-sw-eth-phy_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-sw-eth-phy_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-sw-eth-phy_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-sw-eth-phy_overlay.dtbo
dtb-y += sa8620p-ride/sa8620p-sw-eth-phy.dtb
dtb-y += sa7255p-ride/sa7255p-vm_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-vm-v3_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-vm-sw-eth-phy_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-vm_overlay_pcie_ep.dtbo
dtb-y += sa8255p-ride/sa8255p-vm_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-vm-v3_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-vm_overlay_pcie_ep.dtbo
dtb-y += sa8255p-ride/sa8255p-vm-sw-eth-phy_overlay.dtbo
ifeq ($(QCVIRTIO), true)
dtb-y += sa8255p-ride/sa8255p-vm-agl_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-vm-v3-agl_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-vm-agl_overlay_pcie_ep.dtbo
dtb-y += sa8255p-ride/sa8255p-vm-sw-eth-phy-agl_overlay.dtbo
endif
dtb-y += sa8775p-vm_overlay.dtbo
dtb-y += sa8775p-vm-v3_overlay.dtbo
dtb-y += sa8775p-vm_overlay_pcie_ep.dtbo
dtb-y += sa8775p-vm-sw-eth-phy_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-ride-mx_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-ddr-12gb_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-ddr-18gb_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-ddr-24gb_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-ddr-36gb_overlay.dtbo
ifeq ($(QCVIRTIO), true)
dtb-y += sa8775p-vm-trout_overlay.dtbo
dtb-y += sa8775p-vm-v3-trout_overlay.dtbo
dtb-y += sa8775p-vm-trout_overlay_pcie_ep.dtbo
dtb-y += sa8775p-vm-sw-eth-phy-trout_overlay.dtbo
endif
endif

#DDR Overlay
# 0gvm: pvm only; 1gvm: single LAGVM; no mention gvm: multigvm LAGVM + LVGVM
dtb-y += sa7255p-ride/sa7255p-ddr-12gb_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-ddr-12gb_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-ddr-36gb_overlay.dtbo

dtb-y += sa7255p-ride/sa7255p-ddr-0gvm-12gb_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-ddr-1gvm-12gb_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-ddr-0gvm-12gb_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-ddr-0gvm-36gb_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-ddr-1gvm-36gb_overlay.dtbo

#include common target file
include $(PWD)/Makefile.common
