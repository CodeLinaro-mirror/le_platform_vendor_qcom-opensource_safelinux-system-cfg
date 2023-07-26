/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef BOOTKPI_LOGGING_H
#define BOOTKPI_LOGGING_H

#include <syslog.h>
#include <stdint.h>

#define BOOTKPI_LOG_PREFIX "qcom-bootkpi"

/*
 * bootkpi_log_line API that logs one line of a bootkpi message
 *
 * Only logs ONE LINE. If you want to log multiple lines, you should call
 * bootkpi_log_line multiple times.
 *
 * The current implementation uses syslog() which does not need to include a
 * terminating newline character.
 *
 * ... argument: variadic arguments. use the same arguments as printf
 */
#define bootkpi_log_line(...) syslog(LOG_NOTICE, BOOTKPI_LOG_PREFIX ": " __VA_ARGS__)

#endif // BOOTKPI_LOGGING_H
