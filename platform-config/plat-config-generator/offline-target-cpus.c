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
	int max_cpu;
	target_conf_t conf;
	bool cpu_used;

	if (init_target_conf(&conf) != 0)
		return -1;

	if (!strcmp(conf.sku, "ADAS"))
		return -1;

	max_cpu = sysconf(_SC_NPROCESSORS_CONF);

	for (int cpu = 0; cpu < max_cpu; cpu++) {
		cpu_used = false;
		for (int i = 0; i < conf.slice_count; i++) {
			if (cpu >= conf.slices[i].cpu_start &&
					cpu <= conf.slices[i].cpu_end) {
				cpu_used = true;
				break;
			}
		}

		if (cpu_used)
			continue;

		if (!offline_cpu(cpu)) {
			fprintf(stderr, SD_ERR "Failed to offline cpu %d\n", cpu);
			return -1;
		}
	}

	return 0;
}
