# SPDX-License-Identifier: GPL-2.0
dtb-y += sa8255p_overlay.dtbo
dtb-y += sa8775p-qvp/sa8775p-qvp.dtb

ifneq ($(QCLINUX_BUILD), true)
dtb-y += sa8775p_overlay_rh.dtbo
dtb-y += sa8770p-ride/sa8770p-ride.dtb
dtb-y += sa8775p-ride-mx/sa8775p-ride-mx_rh.dtb
dtb-y += sa8650p-ride/sa8650p-ride.dtb
dtb-y += sa8255p-ride/sa8255p-ride.dtb
dtb-$(CONFIG_ARCH_SA7255) += sa7255p-ride/sa7255p-ride_rh.dtb
dtb-$(CONFIG_ARCH_SA7255) += sa8620p-ride/sa8620p-ride_rh.dtb
else
dtb-y += sa8620p-ride/sa8620p-ride.dtb
endif

#include common target file
include $(PWD)/Makefile.common
