// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"

// This length must fit absolute path of drop-in file.
// Drop-in file example file name: /run/systemd/generator/pvm.slice.d/override.conf

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
		fprintf(stderr, SD_ERR, "Failed to open %s for writing: %s\n", dropin_file_path,
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
			fprintf(stderr, SD_ERR, "Failed to write slice dropin file for %s\n",
					conf.slices[i].name);
			return rc;
		}
	}

	return 0;
}
