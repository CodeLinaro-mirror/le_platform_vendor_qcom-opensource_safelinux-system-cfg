#!/bin/sh
# SPDX-License-Identifier: BSD-3-Clause-Clear
# Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.

IRQ_NUM=$2
IRQ_NUM_MIN_FOR_BALANCING=32

# Script below is for setting balance_level to core
# if irq no. is greater than or equal to 32 &
# ban all IRQ's below 32
if [ "$IRQ_NUM" -lt "$IRQ_NUM_MIN_FOR_BALANCING" ]; then
	echo "ban = true"
else
	echo "balance_level = core"
fi

# Stop further script processing
exit 0
