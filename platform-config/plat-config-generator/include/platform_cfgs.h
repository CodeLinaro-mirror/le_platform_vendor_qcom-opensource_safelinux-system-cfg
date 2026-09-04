/* SPDX-License-Identifier: BSD-3-Clause-Clear
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 */

#ifndef __PLATFORM_CFG_H
#define __PLATFORM_CFG_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <systemd/sd-daemon.h>

#define MAX_SLICE_NAME    100
#define MAX_CPU_GOV_NAME  100
#define MAX_SKU_NAME      100
#define MAX_SLICES        10
#define INI_FILE_PATH_MAX 128
#define FILE_PATH_LEN     100
#define MACHINE_NAME_LEN  32
#define DROPIN_FILE_NAME  "override.conf"
#define CGROUP_DIR        "/sys/fs/cgroup"
#define CPU_ONLINE_PATH      "/sys/devices/system/cpu/cpu%d/online"
#define CPU_CLUSTER_CPUS_PATH "/sys/devices/system/cpu/cpu%d/topology/cluster_cpus"
#define MACHINE_PATH         "/sys/devices/soc0/machine"
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
	char name[MAX_SLICE_NAME];
	int boot_cpu_start;
	int boot_cpu_end;
	int cpu_start;
	int cpu_end;
	int total_cpu_num;
	int allow_cross_cluster;
} slice_conf_t;

typedef struct {
	char sku[MAX_SKU_NAME];
	slice_conf_t slices[MAX_SLICES];
	int slice_count;
	int pvm_total_num_cpus;
	int pvm_boot_from_top;
} target_conf_t;

extern char *sku_names[30];
extern target_conf_t ivi_conf;
extern target_conf_t flex_conf;
extern target_conf_t adas_conf;

bool write_sysfs(const char *path, const char *value);
void create_dir(char *gen_dir);
int  init_target_conf(target_conf_t *conf);

static inline void _cleanup_fclose(FILE **f)
{
	if (*f) {
		fclose(*f);
	}
}

static inline void _cleanup_close(int *pfd)
{
	if (pfd && *pfd >= 0) {
		close(*pfd);
		*pfd = -1;
	}
}

#define cleanup_close  __attribute__((cleanup(_cleanup_close)))
#define cleanup_fclose  __attribute__((cleanup(_cleanup_fclose)))

#endif
