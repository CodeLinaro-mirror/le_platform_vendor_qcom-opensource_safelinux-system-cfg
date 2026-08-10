// SPDX-License-Identifier: BSD-3-Clause-Clear
// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.

#include "platform_cfgs.h"
#if IS_GEN5
#include "softsku_config.h"
#else
#include <glib.h>
#define strlcpy g_strlcpy
#endif

/* Gen 4 */
#define LEMANS_NONSAFE_IVI_FILE "/etc/lemans/nonsafe_ivi.ini"
#define LEMANS_FLEX_FILE "/etc/lemans/flex.ini"
#define LEMANS_ADAS_FILE "/etc/lemans/adas.ini"

/* Gen 5 */
#define NORD_NONSAFE_IVI_FILE "/etc/nord/nonsafe_ivi.ini"
#define NORD_FLEX_FILE "/etc/nord/flex.ini"
#define NORD_QCLGVM_FILE "/etc/nord/qclgvm.ini"
#define NORD_ADAS_FILE "/etc/nord/adas.ini"
#define NORD_SAFE_IVI_FILE "/etc/nord/safe_ivi.ini"
#define SECA_NONSAFE_IVI_FILE "/etc/seca/nonsafe_ivi.ini"
#define SECA_FLEX_FILE "/etc/seca/flex.ini"
#define SECA_ADAS_FILE "/etc/seca/adas.ini"
#define SECA_SAFE_IVI_FILE "/etc/seca/safe_ivi.ini"

char *sku_names[] = {"SAFE_IVI", "ADAS", "FLEX", "NONSAFE_IVI"};

target_conf_t nonsafe_ivi_conf_lemans_8255 = {
	.sku = "NONSAFE_IVI",
	.pvm_total_num_cpus = 8,
	.slice_count = 3,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 0, .total_cpu_num = 2 },
		{ .name = "gvm.slice",    .cpu_start = 2, .total_cpu_num = 1 },
		{ .name = "system.slice", .cpu_start = 2, .total_cpu_num = 1 },
	}
};

target_conf_t flex_conf_lemans_8775 = {
	.sku = "FLEX",
	.pvm_total_num_cpus = 8,
	.slice_count = 3,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 0, .total_cpu_num = 3 },
		{ .name = "gvm.slice",    .cpu_start = 3, .total_cpu_num = 1 },
		{ .name = "system.slice", .cpu_start = 3, .total_cpu_num = 1 },
	}
};

target_conf_t adas_conf_lemans_8650 = {
	.sku = "ADAS",
	.pvm_total_num_cpus = 8,
	.slice_count = 1,
	.slices = {
		{ .name = "pvm.slice", .cpu_start = 0, .total_cpu_num = 8 },
	}
};

target_conf_t safe_ivi_conf_nords = {
	.sku = "SAFE_IVI",
	.pvm_total_num_cpus = 6,
	.slice_count = 4,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 14, .total_cpu_num = 4 },
		{ .name = "gvm.slice",    .cpu_start = 12, .total_cpu_num = 2 },
		{ .name = "system.slice", .cpu_start = 12, .total_cpu_num = 2 },
		{ .name = "rt.slice",     .cpu_start = 12, .total_cpu_num = 6 },
	}
};

target_conf_t nonsafe_ivi_conf_nords = {
	.sku = "NONSAFE_IVI",
	.pvm_total_num_cpus = 6,
	.slice_count = 4,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 14, .total_cpu_num = 4 },
		{ .name = "gvm.slice",    .cpu_start = 12, .total_cpu_num = 2 },
		{ .name = "system.slice", .cpu_start = 12, .total_cpu_num = 2 },
		{ .name = "rt.slice",     .cpu_start = 12, .total_cpu_num = 6 },
	}
};

target_conf_t flex_conf_nords = {
	.sku = "FLEX",
	.pvm_total_num_cpus = 6,
	.slice_count = 4,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 14, .total_cpu_num = 4 },
		{ .name = "gvm.slice",    .cpu_start = 12, .total_cpu_num = 2 },
		{ .name = "system.slice", .cpu_start = 12, .total_cpu_num = 2 },
		{ .name = "rt.slice",     .cpu_start = 12, .total_cpu_num = 6 },
	}
};

target_conf_t adas_conf_nords = {
	.sku = "ADAS",
	.pvm_total_num_cpus = 18,
	.slice_count = 2,
	.slices = {
		{ .name = "pvm.slice", .cpu_start = 0, .total_cpu_num = 18 },
		{ .name = "rt.slice",  .cpu_start = 0, .total_cpu_num = 18 },
	}
};

target_conf_t safe_ivi_conf_seca = {
	.sku = "SAFE_IVI",
	.pvm_total_num_cpus = 4,
	.slice_count = 3,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 9, .total_cpu_num = 3 },
		{ .name = "gvm.slice",    .cpu_start = 8, .total_cpu_num = 2 },
		{ .name = "system.slice", .cpu_start = 8, .total_cpu_num = 2 },
	}
};

target_conf_t nonsafe_ivi_conf_seca = {
	.sku = "NONSAFE_IVI",
	.pvm_total_num_cpus = 4,
	.slice_count = 3,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 9, .total_cpu_num = 3 },
		{ .name = "gvm.slice",    .cpu_start = 8, .total_cpu_num = 2 },
		{ .name = "system.slice", .cpu_start = 8, .total_cpu_num = 2 },
	}
};

target_conf_t flex_conf_seca = {
	.sku = "FLEX",
	.pvm_total_num_cpus = 4,
	.slice_count = 3,
	.slices = {
		{ .name = "pvm.slice",    .cpu_start = 9, .total_cpu_num = 3 },
		{ .name = "gvm.slice",    .cpu_start = 8, .total_cpu_num = 2 },
		{ .name = "system.slice", .cpu_start = 8, .total_cpu_num = 2 },
	}
};

target_conf_t adas_conf_seca = {
	.sku = "ADAS",
	.pvm_total_num_cpus = 12,
	.slice_count = 1,
	.slices = {
		{ .name = "pvm.slice", .cpu_start = 0, .total_cpu_num = 12 },
	}
};

void create_dir(char *gen_dir)
{
	// Assume argument dir pointer is valid
	if (mkdir(gen_dir, 0755) < 0) {
		if (errno != EEXIST) {
			fprintf(stderr, SD_ERR
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
		fprintf(stderr, SD_ERR "Failed to open %s for writing: %s\n", path,
				strerror(errno));
		return false;
	}

	len = strlen(value);
	write_status = write(fd, value, len);

	if (write_status != len) {
		fprintf(stderr, SD_ERR "Failed to write to %s: %s\n", path,
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
		fprintf(stderr, SD_ERR
				"Failed to read sku name from %s\n", file_path);
		return -ENOENT;
	}

	conf->slice_count = ini_getl("sku", "slice_count", -1, file_path);

	if (conf->slice_count <= 0 || conf->slice_count > MAX_SLICES) {
		fprintf(stderr, SD_ERR
				"Invalid slice count in %s\n", file_path);
		return -EINVAL;
	}

	for (i = 0; i < num_skus; i++) {
		if (strcmp(conf->sku, sku_names[i]) == 0)
			break;
	}

	if (i == num_skus) {
		fprintf(stderr, SD_ERR
				"Invalid SKU name in %s\n", file_path);
		return -EINVAL;
	}

	conf->pvm_total_num_cpus = (int)ini_getl("sku", "pvm_total_num_cpus", -1, file_path);

	if (conf->pvm_total_num_cpus <= 0) {
		fprintf(stderr, SD_ERR
				"Failed to read pvm_total_num_cpus from %s\n", file_path);
		return -EINVAL;
	}

	for (int i = 0; i < conf->slice_count; ++i) {
		char section[16];

		snprintf(section, sizeof(section), "slice%d", i);
		ret_val = ini_gets(section, "name", "", conf->slices[i].name,
							sizeof(conf->slices[i].name), file_path);

		if (ret_val == 0) {
			fprintf(stderr, SD_ERR
					"Failed to read slice name from %s\n", file_path);
			return -ENOENT;
		}

		conf->slices[i].cpu_start = (int)ini_getl(section, "post_boot_cpu_start", -1, file_path);
		conf->slices[i].total_cpu_num = (int)ini_getl(section, "total_cpu_num", -1, file_path);

		if (conf->slices[i].cpu_start < 0 || conf->slices[i].total_cpu_num <= 0) {
			fprintf(stderr, SD_ERR
					"Failed to read post_boot_cpu_start or total_cpu_num from %s\n",
					file_path);
			return -EINVAL;
		}

		conf->slices[i].allow_cross_cluster = (int)ini_getl(section,
				"allow_cross_cluster", 0, file_path);
	}

	return 0;
}

static bool is_qclgvm_mode(void)
{
	FILE *f = fopen("/proc/cmdline", "r");

	if (!f)
		return false;

	char buf[4096] = {0};
	bool found = false;

	if (fgets(buf, sizeof(buf), f)) {
		char *saveptr = NULL;
		char *token = strtok_r(buf, " \t\n", &saveptr);

		while (token) {
			if (strcmp(token, "osconfig=PVM+QCLGVM") == 0) {
				found = true;
				break;
			}
			token = strtok_r(NULL, " \t\n", &saveptr);
		}
	}

	fclose(f);
	return found;
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
			fprintf(stderr, SD_ERR "unsupported sku: %s\n", sku);
	} else if (strstr(machine_name, "8787") != NULL) {
		if (strcmp(sku, "SAFE_IVI") == 0)
			*conf = safe_ivi_conf_seca;
		else if (strcmp(sku, "NONSAFE_IVI") == 0)
			*conf = nonsafe_ivi_conf_seca;
		else if (strcmp(sku, "FLEX") == 0)
			*conf = flex_conf_seca;
		else if (strcmp(sku, "ADAS") == 0)
			*conf = adas_conf_seca;
		else
			fprintf(stderr, SD_ERR "unsupported sku: %s\n", sku);
	} else if (strstr(machine_name, "8255") != NULL)
		*conf = nonsafe_ivi_conf_lemans_8255;
	else if (strstr(machine_name, "8775") != NULL)
		*conf = flex_conf_lemans_8775;
	else if (strstr(machine_name, "8650") != NULL)
		*conf = adas_conf_lemans_8650;
	else
		fprintf(stderr, SD_ERR "unsupported machine or sku: %s\n", sku);
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

/* Returns the lowest logical CPU in the same cluster as cpu_idx, or
 * cpu_idx itself if the topology file cannot be read. */
static int get_cluster_start(int cpu_idx)
{
	char path[FILE_PATH_LEN];
	char buf[32];

	snprintf(path, sizeof(path), CPU_CLUSTER_CPUS_PATH, cpu_idx);

	FILE *f = fopen(path, "r");
	if (!f)
		return cpu_idx;

	bool ok = fgets(buf, sizeof(buf), f) != NULL;
	fclose(f);
	if (!ok)
		return cpu_idx;

	unsigned long long mask;
	if (sscanf(buf, "%llx", &mask) != 1 || mask == 0)
		return cpu_idx;

	/* Position of the least-significant set bit = first CPU in cluster */
	int lsb = __builtin_ctzll(mask);
	return lsb;
}

static void compute_cpu_ranges(target_conf_t *conf, int max_cpu)
{
	int pvm_boot_start, non_pvm_boot_end;

	if (conf->pvm_total_num_cpus >= max_cpu) {
		pvm_boot_start   = 0;
		non_pvm_boot_end = max_cpu - 1;
	} else {
		pvm_boot_start   = max_cpu - conf->pvm_total_num_cpus;
		non_pvm_boot_end = pvm_boot_start - 1;
	}

	for (int i = 0; i < conf->slice_count; i++) {
		if (conf->slices[i].cpu_start >= pvm_boot_start) {
			conf->slices[i].boot_cpu_start = pvm_boot_start;
			conf->slices[i].boot_cpu_end   = max_cpu - 1;
		} else {
			conf->slices[i].boot_cpu_start = 0;
			conf->slices[i].boot_cpu_end   = non_pvm_boot_end;
		}

		conf->slices[i].cpu_end = conf->slices[i].cpu_start + conf->slices[i].total_cpu_num - 1;
		if (conf->slices[i].cpu_end >= max_cpu)
			conf->slices[i].cpu_end = max_cpu - 1;

		if (!conf->slices[i].allow_cross_cluster) {
			int cluster_start = get_cluster_start(conf->slices[i].cpu_end);
			if (cluster_start > conf->slices[i].cpu_start) {
				int capped = cluster_start - 1;
				fprintf(stderr, SD_INFO
						"Capping %s cpu_end %d to cluster boundary %d\n",
						conf->slices[i].name, conf->slices[i].cpu_end,
						capped);
				conf->slices[i].cpu_end = capped;
			}
		}
	}
}

int init_target_conf(target_conf_t *conf)
{
	int ret;
	char sku[MAX_SKU_NAME];
	char machine_name[MACHINE_NAME_LEN] = {0};
	char target_conf_file[INI_FILE_PATH_MAX] = {0};
	bool supported = true;

	ret = get_target_machine_name(machine_name);

	if (ret) {
		fprintf(stderr, SD_ERR "Failed to get machine name\n");
		return -1;
	}

	if (strstr(machine_name, "8797") != NULL || strstr(machine_name, "8787") != NULL) {
#if IS_GEN5
		unsigned int sku_id_by_bits;
		bool is_nord = strstr(machine_name, "8797") != NULL;

		initialize_softsku_config();
		if (get_status_bits(softsku_spare_0, 8, 9, &sku_id_by_bits))
			fprintf(stderr, SD_INFO "Get status bit failed!\n");
		else {
			/*checking with sku id got from macros*/
			if (sku_id_by_bits != SW_CONFIG)
				fprintf(stderr, SD_INFO "Bit extraction verified.\n");
		}

		switch (SW_CONFIG) {
		case SW_CONFIG_TYPE_NONSAFE_IVI:
			strlcpy(sku, "NONSAFE_IVI", sizeof(sku));
			strlcpy(target_conf_file, is_nord ? NORD_NONSAFE_IVI_FILE : SECA_NONSAFE_IVI_FILE,
					sizeof(target_conf_file));
			break;
		case SW_CONFIG_TYPE_FLEX:
			strlcpy(sku, "FLEX", sizeof(sku));
			strlcpy(target_conf_file, is_nord ? NORD_FLEX_FILE : SECA_FLEX_FILE,
					sizeof(target_conf_file));
			break;
		case SW_CONFIG_TYPE_ADAS:
			strlcpy(sku, "ADAS", sizeof(sku));
			strlcpy(target_conf_file, is_nord ? NORD_ADAS_FILE : SECA_ADAS_FILE,
					sizeof(target_conf_file));
			break;
		case SW_CONFIG_TYPE_SAFE_IVI:
			strlcpy(sku, "SAFE_IVI", sizeof(sku));
			strlcpy(target_conf_file, is_nord ? NORD_SAFE_IVI_FILE : SECA_SAFE_IVI_FILE,
					sizeof(target_conf_file));
			break;
		default:
			supported = false;
			break;
		}

		/* qclgvm mode shares one config across all nord SKUs */
		if (supported && is_nord && is_qclgvm_mode())
			strlcpy(target_conf_file, NORD_QCLGVM_FILE,
					sizeof(target_conf_file));
#endif
	} else if (strstr(machine_name, "8255") != NULL) {
		strlcpy(sku, "NONSAFE_IVI", sizeof(sku));
		strlcpy(target_conf_file, LEMANS_NONSAFE_IVI_FILE,
					sizeof(target_conf_file));
	} else if (strstr(machine_name, "8775") != NULL) {
		strlcpy(sku, "FLEX", sizeof(sku));
		strlcpy(target_conf_file, LEMANS_FLEX_FILE,
					sizeof(target_conf_file));
	} else if (strstr(machine_name, "8650") != NULL) {
		strlcpy(sku, "ADAS", sizeof(sku));
		strlcpy(target_conf_file, LEMANS_ADAS_FILE,
				sizeof(target_conf_file));
	} else {
		supported = false;
	}

	if (!supported) {
		fprintf(stderr, SD_INFO "Machine %s not supported, skipping configuration\n",
				machine_name);
		conf->slice_count = 0;
		return 0;
	}

	ret = read_input_INIfile(conf, target_conf_file);

	if (ret != 0) {
		fprintf(stderr, SD_INFO
				"Failed to read input %s file\n", target_conf_file);
		set_default_target_conf(sku, machine_name, conf);
	}

	int max_cpu = get_max_cpu_index() + 1;

	if (max_cpu <= 0) {
		fprintf(stderr, SD_ERR "Failed to get max CPU index\n");
		return -1;
	}

	compute_cpu_ranges(conf, max_cpu);

return 0;
}
