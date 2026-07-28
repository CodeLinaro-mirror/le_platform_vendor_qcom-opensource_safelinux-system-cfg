// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"

static bool offline_cpu(int cpu)
{
	char path[FILE_PATH_LEN];
	bool write_status;

	snprintf(path, sizeof(path), CPU_ONLINE_PATH, cpu);
	write_status = write_sysfs(path, "0");
	return write_status;
}

int main(int argc, char **argv)
{
	int rc;
	int max_cpu;
	target_conf_t conf;
	int pvm_boot_start = 0, pvm_boot_end = 0;

	if (init_target_conf(&conf) != 0)
		return -1;

	for (int i = 0; i < conf.slice_count; ++i) {
		if (strcmp(conf.slices[i].name, "pvm.slice") == 0) {
			pvm_boot_start = conf.slices[i].boot_cpu_start;
			pvm_boot_end = conf.slices[i].boot_cpu_end;
			break;
		}
	}

	max_cpu = pvm_boot_end + 1;

	for (int cpu = 0; cpu < max_cpu; cpu++) {
		if ((cpu >= pvm_boot_start && cpu <= pvm_boot_end)
				|| !strcmp(conf.sku, "ADAS")) {
			continue;
		}

		if (!offline_cpu(cpu)) {
			fprintf(stderr, SD_ERR "Failed to offline cpu %d\n", cpu);
			return -1;
		}
	}

	return 0;
}
