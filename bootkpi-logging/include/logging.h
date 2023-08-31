/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef BOOTKPI_LOGGING_H
#define BOOTKPI_LOGGING_H

#include <stdio.h>
#include <stdint.h>
#include "systemd/sd-daemon.h"

#define BOOTKPI_LOG_PREFIX "qcom-bootkpi"


/*
 * bootkpi_log_init initializes bootkpi logger
 *
 * Force stdout to be line buffered so bytes are written when newline is encountered.
 * This ensures that logs are collected by systemd immediately after they are written,
 * and their timestamps are accurate.
 */
#define bootkpi_log_init() setvbuf(stdout, NULL, _IOLBF, 0)

/*
 * bootkpi_log_line API that logs one line of a bootkpi message
 *
 * Only logs ONE LINE. If you want to log multiple lines, you should call
 * bootkpi_log_line multiple times.
 *
 * The current implementation uses fprintf, printing to stdout,
 * with log level NOTICE. The log is prefixed with BOOTKPI_LOG_PREFIX.
 *
 * ... argument: variadic arguments. use the same arguments as printf
 */
#define bootkpi_log_line(...) \
    do { \
        fprintf(stdout, SD_NOTICE BOOTKPI_LOG_PREFIX ": " __VA_ARGS__); \
        fprintf(stdout, "\n"); \
    } while (0)


#endif // BOOTKPI_LOGGING_H
