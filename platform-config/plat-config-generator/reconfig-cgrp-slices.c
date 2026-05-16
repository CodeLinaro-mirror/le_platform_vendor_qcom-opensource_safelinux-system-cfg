// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"

static bool set_slice_cpuset(const char *slice_name,
							int cpu_start,
							int cpu_end)
{
	char range[10];
	char path[FILE_PATH_LEN];
	bool write_status;

	snprintf(range, sizeof(range), "%d-%d", cpu_start, cpu_end);
	snprintf(path, sizeof(path), "/sys/fs/cgroup/%s/cpuset.cpus", slice_name);
	write_status = write_sysfs(path, range);
	return write_status;
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
