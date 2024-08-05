#!/bin/sh
# SPDX-License-Identifier: BSD-3-Clause-Clear
# Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.

echo "IRQBALANCE_ARGS= -t 5 -l /usr/bin/set_irq_bal_level.sh" > /etc/sysconfig/irqbalance

# Stop further script processing
exit 0
