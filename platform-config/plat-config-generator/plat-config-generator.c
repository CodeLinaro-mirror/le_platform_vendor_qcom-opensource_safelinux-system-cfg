// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"

// This length must fit absolute path of drop-in file.
// Drop-in file example file name: /run/systemd/generator/pvm.slice.d/override.conf

static int config_irqbalance_mask(int max_cpu, int start_cpu, int end_cpu)
{
	int mask1_start, mask1_end;
	int mask2_start, mask2_end;
	char mask_env[128] = {0};
	int len;
	FILE *fptr;
	char irq_mask_dir[FILE_PATH_LEN] = "/run/systemd/generator/irqbalance.d";
	char irq_mask_path[FILE_PATH_LEN] =
		"/run/systemd/generator/irqbalance.d/irqbalance.env";
	mask1_start = 0;
	mask1_end = start_cpu - 1;
	mask2_start = end_cpu + 1;
	mask2_end = max_cpu - 1;
	len = snprintf(mask_env, sizeof(mask_env), "IRQBALANCE_BANNED_CPULIST=");

	if (mask1_end >= 0) {
		if (mask2_start < max_cpu)
			snprintf(mask_env + len, sizeof(mask_env) - len, "%d-%d,%d-%d",
				mask1_start, mask1_end, mask2_start, mask2_end);
		else
			snprintf(mask_env + len, sizeof(mask_env) - len, "%d-%d",
				mask1_start, mask1_end);
	} else {
		if (mask2_start < max_cpu)
			snprintf(mask_env + len, sizeof(mask_env) - len, "%d-%d",
				mask2_start, mask2_end);
		else {
			return -EINVAL;
		}
	}

	create_dir(irq_mask_dir);
	fptr = fopen(irq_mask_path, "w");

	if (!fptr) {
		fprintf(stderr, SD_ERR "Failed to open %s for writing: %s\n", irq_mask_path,
			strerror(errno));
		return -errno;
	}

	fprintf(fptr, "%s", mask_env);
	fclose(fptr);
	return 0;
}

static int write_slice_dropin(const char *dir_path,
								int cpu_start,
								int cpu_end)
{
	FILE *fptr cleanup_fclose = NULL;
	char dropin_file_path[FILE_PATH_LEN];

	snprintf(dropin_file_path, sizeof(dropin_file_path), "%s/%s", dir_path,
			DROPIN_FILE_NAME);
	fptr = fopen(dropin_file_path, "w");

	if (!fptr) {
		fprintf(stderr, SD_ERR "Failed to open %s for writing: %s\n", dropin_file_path,
				strerror(errno));
		return -errno;
	}

	fprintf(fptr, "\n[Slice]\n");
	fprintf(fptr, "AllowedCPUs=%d-%d\n", cpu_start, cpu_end);
	return 0;
}

int main(int argc, char **argv)
{
	int rc;
	int max_cpu;
	int pvm_boot_start = 0xFF, pvm_boot_end = -1;
	target_conf_t conf;
	const char *generator_abs_dir = "/run/systemd/generator";

	if (init_target_conf(&conf) != 0)
		return -1;

	for (int i = 0; i < conf.slice_count; ++i) {
		char slice_dir[FILE_PATH_LEN] = "";

		snprintf(slice_dir, sizeof(slice_dir), "%s/%s.d",
				generator_abs_dir, conf.slices[i].name);
		create_dir(slice_dir);
		rc = write_slice_dropin(slice_dir, conf.slices[i].boot_cpu_start,
					conf.slices[i].boot_cpu_end);

		if (rc) {
			fprintf(stderr, SD_ERR "Failed to write slice dropin file for %s\n",
					conf.slices[i].name);
			return rc;
		}

		if (pvm_boot_start > conf.slices[i].boot_cpu_start)
			pvm_boot_start = conf.slices[i].boot_cpu_start;
		if (pvm_boot_end < conf.slices[i].boot_cpu_end)
			pvm_boot_end = conf.slices[i].boot_cpu_end;
	}

	if (pvm_boot_start >= 0 && pvm_boot_end >= 0) {
		max_cpu = sysconf(_SC_NPROCESSORS_CONF);

		if (config_irqbalance_mask(max_cpu, pvm_boot_start, pvm_boot_end))
			fprintf(stderr, SD_ERR "Failed to config irqbalance!\n");
	}

	return 0;
}
