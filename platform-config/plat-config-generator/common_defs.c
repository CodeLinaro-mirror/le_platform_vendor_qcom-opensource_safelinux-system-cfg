// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"
#include "softsku_config.h"

char *sku_names[] = {"SAFE_IVI", "ADAS", "FLEX", "NONSAFE_IVI"};

target_conf_t nonsafe_ivi_conf_lemans_8255 = {
	.sku = "NONSAFE_IVI",
	.slice_count = 3,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 3, .cpu_start = 0, .cpu_end = 1
		},
		{
			.name = "gvm.slice", .boot_cpu_start = 2,
			.boot_cpu_end = 3, .cpu_start = 2, .cpu_end = 3
		},
		{
			.name = "system.slice", .boot_cpu_start = 2,
			.boot_cpu_end = 3, .cpu_start = 2, .cpu_end = 3
		},
	}
};


target_conf_t flex_conf_lemans_8775 = {
	.sku = "FLEX",
	.slice_count = 3,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 3, .cpu_start = 0, .cpu_end = 1
		},
		{
			.name = "gvm.slice", .boot_cpu_start = 2,
			.boot_cpu_end = 3, .cpu_start = 2, .cpu_end = 3
		},
		{
			.name = "system.slice", .boot_cpu_start = 2,
			.boot_cpu_end = 3, .cpu_start = 2, .cpu_end = 3
		},
	}
};

target_conf_t adas_conf_lemans_8650 = {
	.sku = "ADAS",
	.slice_count = 1,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 7, .cpu_start = 0, .cpu_end = 7
		},
	}
};

target_conf_t safe_ivi_conf_nords = {
	.sku = "SAFE_IVI",
	.slice_count = 3,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 5, .cpu_start = 0, .cpu_end = 3
		},
		{
			.name = "gvm.slice", .boot_cpu_start = 4,
			.boot_cpu_end = 17, .cpu_start = 4, .cpu_end = 5
		},
		{
			.name = "system.slice", .boot_cpu_start = 4,
			.boot_cpu_end = 17, .cpu_start = 4, .cpu_end = 5
		},
	}
};

target_conf_t nonsafe_ivi_conf_nords = {
	.sku = "NONSAFE_IVI",
	.slice_count = 3,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 12,
			.boot_cpu_end = 17, .cpu_start = 14, .cpu_end = 17
		},
		{
			.name = "gvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 11, .cpu_start = 12, .cpu_end = 13
		},
		{
			.name = "system.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 11, .cpu_start = 12, .cpu_end = 13
		},
	}
};


target_conf_t flex_conf_nords = {
	.sku = "FLEX",
	.slice_count = 3,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 12,
			.boot_cpu_end = 17, .cpu_start = 14, .cpu_end = 17
		},
		{
			.name = "gvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 11, .cpu_start = 12, .cpu_end = 13
		},
		{
			.name = "system.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 11, .cpu_start = 12, .cpu_end = 13
		},
	}
};

target_conf_t adas_conf_nords = {
	.sku = "ADAS",
	.slice_count = 1,
	.slices = {
		{
			.name = "pvm.slice", .boot_cpu_start = 0,
			.boot_cpu_end = 17, .cpu_start = 0, .cpu_end = 17
		},
	}
};

void create_dir(char *gen_dir)
{
	// Assume argument dir pointer is valid
	if (mkdir(gen_dir, 0755) < 0) {
		if (errno != EEXIST) {
			fprintf(stderr, SD_ERR,
					"Failed to create %s: %s\n", gen_dir, strerror(errno));
			exit(0 - errno);
		}
	}
}

bool write_sysfs(const char *path, const char *value)
{
	ssize_t len;
	ssize_t write_status;

	int fd cleanup_close = open(path, O_WRONLY | O_CLOEXEC);

	if (fd < 0) {
		fprintf(stderr, SD_ERR, "Failed to open %s for writing: %s\n", path,
				strerror(errno));
		return false;
	}

	len = strlen(value);
	write_status = write(fd, value, len);

	if (write_status != len) {
		fprintf(stderr, SD_ERR, "Failed to write to %s: %s\n", path,
				strerror(errno));
		return false;
	}

	return true;
}

static int read_input_INIfile(target_conf_t *conf, const char *file_path)
{
	int ret_val, i;
	size_t num_skus = ARRAY_SIZE(sku_names);

	ret_val = ini_gets("sku", "name", "", conf->sku,
						sizeof(conf->sku), file_path);

	if (ret_val == 0) {
		fprintf(stderr, SD_ERR,
				"Failed to read sku name from %s\n", file_path);
		return -ENOENT;
	}

	conf->slice_count = ini_getl("sku", "slice_count", -1, file_path);

	if (conf->slice_count <= 0 || conf->slice_count > MAX_SLICES) {
		fprintf(stderr, SD_ERR,
				"Invalid slice count in %s\n", file_path);
		return -EINVAL;
	}

	for (i = 0; i < num_skus; i++) {
		if (strcmp(conf->sku, sku_names[i]) == 0)
			break;
	}

	if (i == num_skus) {
		fprintf(stderr, SD_ERR,
				"Invalid SKU name in %s\n", file_path);
		return -EINVAL;
	}

	for (int i = 0; i < conf->slice_count; ++i) {
		char section[16];

		snprintf(section, sizeof(section), "slice%d", i);
		ret_val = ini_gets(section, "name", "", conf->slices[i].name,
							sizeof(conf->slices[i].name), file_path);

		if (ret_val == 0) {
			fprintf(stderr, SD_ERR,
					"Failed to read slice name from %s\n", file_path);
			return -ENOENT;
		}

		conf->slices[i].boot_cpu_start = (int)ini_getl(section,
			"boot_cpu_start", -1, file_path);
		conf->slices[i].boot_cpu_end   = (int)ini_getl(section,
								"boot_cpu_end",   -1, file_path);

		if (conf->slices[i].boot_cpu_start < 0 || conf->slices[i].boot_cpu_end < 0) {
			fprintf(stderr, SD_ERR,
					"Failed to read boot_cpu_start and boot_cpu_end values from %s\n",
					file_path);
			return -EINVAL;
		}

		conf->slices[i].cpu_start = (int)ini_getl(section, "post_boot_cpu_start", -1, file_path);
		conf->slices[i].cpu_end   = (int)ini_getl(section, "post_boot_cpu_end", -1, file_path);

		if (conf->slices[i].cpu_start < 0 || conf->slices[i].cpu_end < 0) {
			fprintf(stderr, SD_ERR,
					"Failed to read post_boot_cpu_start and post_boot_cpu_end values from %s\n",
					file_path);
			return -EINVAL;
		}
	}

	return 0;
}

static int get_target_machine_name(char *machine_name)
{
	int bytes_read;
	int fd cleanup_close = open(MACHINE_PATH, O_RDONLY);

	if (fd < 0) {
		fprintf(stderr, SD_ERR "Failed to open machine file\n");
		return -1;
	}

	bytes_read = read(fd, machine_name, MACHINE_NAME_LEN - 1);

	if (bytes_read < 0) {
		fprintf(stderr, SD_ERR "Failed to read machine name\n");
		return -1;
	}

	machine_name[bytes_read] = '\0';
	return 0;
}

static void set_default_target_conf(const char *sku, const char *machine_name,
									target_conf_t *conf)
{
	if (strstr(machine_name, "8797") != NULL) {
		if (strcmp(sku, "SAFE_IVI") == 0)
			*conf = safe_ivi_conf_nords;
		else if (strcmp(sku, "NONSAFE_IVI") == 0)
			*conf = nonsafe_ivi_conf_nords;
		else if (strcmp(sku, "FLEX") == 0)
			*conf = flex_conf_nords;
		else if (strcmp(sku, "ADAS") == 0)
			*conf = adas_conf_nords;
		else
			fprintf(stderr, SD_ERR, "unsupported sku: %s\n", sku);
	} else if (strstr(machine_name, "8255") != NULL)
		*conf = nonsafe_ivi_conf_lemans_8255;
	else if (strstr(machine_name, "8775") != NULL)
		*conf = flex_conf_lemans_8775;
	else if (strstr(machine_name, "8650") != NULL)
		*conf = adas_conf_lemans_8650;
	else
		fprintf(stderr, SD_ERR, "unsupported machine or sku: %s\n", sku);
}

static int get_max_cpu_index(void)
{
	FILE *f = fopen("/sys/devices/system/cpu/online", "r");
	if (!f) {
		return -1;
	}
	char buf[64];
	if (!fgets(buf, sizeof(buf), f)) {
		fclose(f);
		return -1;
	}
	fclose(f);

	char *dash = strchr(buf, '-');
	if (!dash) {
		return -1;
	}
	int max;
	if (sscanf(dash + 1, "%d", &max) != 1) {
		return -1;
	}
	return max;
}

int init_target_conf(target_conf_t *conf)
{
	int ret;
	char sku[MAX_SKU_NAME];
	int max_cpus;
	char machine_name[MACHINE_NAME_LEN] = {0};
	char target_conf_file[INI_FILE_PATH_MAX] = {0};
	unsigned int sku_id_by_bits;
	bool supported = true;

	ret = get_target_machine_name(machine_name);

	if (ret) {
		fprintf(stderr, SD_ERR "Failed to get machine name\n");
		return -1;
	}

	if (strstr(machine_name, "8797") != NULL) {
		initialize_softsku_config();

		if (get_status_bits(softsku_spare_0, 8, 9, &sku_id_by_bits))
			fprintf(stderr, SD_INFO, "Get status bit failed!\n");
		else {
			/*checking with sku id got from macros*/
			if (sku_id_by_bits != SW_CONFIG)
				fprintf(stderr, SD_INFO, "Bit extraction verified.\n");
		}

		if (SW_CONFIG_TYPE_NONSAFE_IVI) {
			strlcpy(sku, "NONSAFE_IVI", sizeof(sku));
			strlcpy(target_conf_file, "/etc/target_conf_nonsafe_ivi.ini",
					sizeof(target_conf_file));
		} else if (SW_CONFIG_TYPE_FLEX) {
			strlcpy(sku, "FLEX", sizeof(sku));
			strlcpy(target_conf_file, "/etc/target_conf_flex.ini",
					sizeof(target_conf_file));
		} else if (SW_CONFIG_TYPE_ADAS) {
			strlcpy(sku, "ADAS", sizeof(sku));
			strlcpy(target_conf_file, "/etc/target_conf_adas.ini",
					sizeof(target_conf_file));
		} else if (SW_CONFIG_TYPE_SAFE_IVI) {
			strlcpy(sku, "SAFE_IVI", sizeof(sku));
			strlcpy(target_conf_file, "/etc/target_conf_safe_ivi.ini",
					sizeof(target_conf_file));
		} else {
			supported = false;
		}
	} else if (strstr(machine_name, "8255") != NULL) {
		//will be added later for 8255 target config. for now just return error.
		supported = false;
	} else if (strstr(machine_name, "8775") != NULL) {
		//will be added later for 8775 target config. for now just return error.
		supported = false;
	} else if (strstr(machine_name, "8650") != NULL) {
		//will be added later for 8650 target config. for now just return error.
		supported = false;
	} else {
		supported = false;
	}

	if (!supported) {
		fprintf(stderr, SD_ERR "Machine not supported\n");
		return -EINVAL;
	}

	ret = read_input_INIfile(conf, target_conf_file);

	if (ret != 0) {
		fprintf(stderr, SD_INFO,
				"Failed to read input %s file\n", target_conf_file);
		set_default_target_conf(sku, machine_name, conf);
	}

	/* Apply CPU adjustment only for Nord (8797) platforms */
	if (strstr(machine_name, "8797") != NULL) {
		int max_cpu = get_max_cpu_index();
		if (max_cpu == 16) {
			for (int i = 0; i < conf->slice_count; i++) {
				if (conf->slices[i].boot_cpu_end == 17) {
					conf->slices[i].boot_cpu_end = 16;
				}
				if (conf->slices[i].cpu_end == 17) {
					conf->slices[i].cpu_end = 16;
				}
			}
		}
	}

return 0;
}
