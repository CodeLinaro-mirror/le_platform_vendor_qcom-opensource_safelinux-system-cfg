#!/bin/sh
# Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause-Clear

DEVS="17c23000.vfio_timer 3d00000.vfio_kgsl ac00000.vfio_titan_base ab00000.vfio_eva aa00000.vfio_vidc ae00000.vfio_dpu_00 22000000.vfio_dpu_10
	  780000.umd_glink 408000.umd_pil 90900000.subsystem_ramdump_util 1.cdsp0_cb 2.cdsp0_cb 3.cdsp0_cb 4.cdsp0_cb 1.cdsp1_cb 2.cdsp1_cb 3.cdsp1_cb 4.cdsp1_cb
	  2.adsp_cb 3.adsp_cb 4.adsp_cb 1.gpdsp0_cb 1.gpdsp1_cb 3.gpdsp0_cb 3.gpdsp1_cb soc:vfio_gmu soc:vfio_gmu_db soc:vfio_kgsl_secure soc:vfio_kgsl_lpac
	  soc:vfio_vidc_non_secure_pixel_cb 1.vfio_audio 2.vfio_audio_gpdsp0_cb 2.vfio_audio_gpdsp1_cb 90d80000.sail-mailbox 90e00000.sail-mailbox-ota"

for DEV in $DEVS; do
	echo "vfio-platform" > /sys/bus/platform/devices/$DEV/driver_override
	echo $DEV > /sys/bus/platform/drivers/vfio-platform/bind
done
