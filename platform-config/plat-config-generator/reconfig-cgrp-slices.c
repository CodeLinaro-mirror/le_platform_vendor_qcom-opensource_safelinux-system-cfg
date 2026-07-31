// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"

static bool set_slice_cpuset(const char *slice_name,
							int cpu_start,
							int cpu_end)
{
	char range[10];
	char cmd[FILE_PATH_LEN];
	char cgrp_dir[FILE_PATH_LEN];

	snprintf(cgrp_dir, sizeof(cgrp_dir), "/sys/fs/cgroup/%s", slice_name);
	create_dir(cgrp_dir);

	snprintf(range, sizeof(range), "%d-%d", cpu_start, cpu_end);

	/*
	 * Use systemctl set-property --runtime to update AllowedCPUs through
	 * systemd so the value persists through any future cgroup realization.
	 * A direct cpuset.cpus write would be overwritten by systemd whenever
	 * a new task enters the slice.
	 */
	snprintf(cmd, sizeof(cmd),
			"systemctl set-property --runtime %s AllowedCPUs=%s",
			slice_name, range);
	if (system(cmd) != 0) {
		fprintf(stderr, SD_ERR
				"Failed to set AllowedCPUs for slice %s\n", slice_name);
		return false;
	}

	return true;
}

void print_final_config(target_conf_t *conf)
{
	fprintf(stdout, SD_INFO "final cgrp configuration\n");

	for (int i = 0; i < conf->slice_count; ++i) {
		const char *slice_name = conf->slices[i].name;
		int start = conf->slices[i].cpu_start;
		int end = conf->slices[i].cpu_end;

		fprintf(stdout, SD_INFO "Slice: %s, CPUs: %d-%d\n", slice_name, start, end);
	}
}

int main(int argc, char **argv)
{
	int rc;
	target_conf_t conf;
	const char *generator_abs_dir = "/run/systemd/generator";

	if (init_target_conf(&conf) != 0)
		return -1;

	for (int i = 0; i < conf.slice_count; ++i) {
		const char *slice_name = conf.slices[i].name;
		int start = conf.slices[i].cpu_start;
		int end = conf.slices[i].cpu_end;

		if (!set_slice_cpuset(slice_name, start, end)) {
			fprintf(stderr, SD_ERR "Failed to set cpuset for slice %s\n",
					slice_name);
			return -1;
		}
	}

	print_final_config(&conf);
	return 0;
}
