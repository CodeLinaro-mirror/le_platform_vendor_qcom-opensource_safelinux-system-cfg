# SPDX-License-Identifier: GPL-2.0

dtb-y += sa8775p-qvp/sa8775p-qvp.dtb
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
else
# QCLinux Kernel Case
dtb-y += sa8620p-ride/sa8620p-ride.dtb
dtb-y += sa8620p-ride/sa8620p-ride-v3.dtb
dtb-y += sa8775p_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p_overlay.dtbo
dtb-y += sa8650p-ride/sa8650p-v3_overlay.dtbo
dtb-y += sa8775p-ride-mx/sa8775p-ride-mx.dtb
dtb-y += sa7255p-ride/sa7255p_overlay.dtbo
dtb-y += sa7255p-ride/sa7255p-v3_overlay.dtbo
dtb-y += sa8775p-v3_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p-v3_overlay.dtbo
dtb-y += sa8255p-ride/sa8255p_overlay_pcie_ep.dtbo
dtb-y += sa8650p-ride/sa8650p_overlay_pcie_ep.dtbo
dtb-y += sa8775p_overlay_pcie_ep.dtbo
dtb-y += sa8255p-qvp/sa8255p-qvp.dtb
endif

#include common target file
include $(PWD)/Makefile.common
