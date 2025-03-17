// SPDX-License-Identifier: GPL-2.0

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <os.h>
#include <um_host.h>

static void set_feature_bit(unsigned char *arr, unsigned int bit)
{
	arr[bit / 8] = arr[bit / 8] | (1 << (bit % 8));
}

static int is_power_of_2(unsigned long n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}


static void parse_host_cpu_flags(char *line)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(UM_SUBARCH_EXTENSIONS); i++) {
		if (strstr(line, UM_SUBARCH_EXTENSIONS[i])) {
			set_feature_bit(um_host_params.extensions, i);
		};
	};
	for (i = 0; i < ARRAY_SIZE(UM_SUBARCH_SYSCALLS); i++) {
		if (strstr(line, UM_SUBARCH_SYSCALLS[i])) {
			set_feature_bit(um_host_params.syscalls, i);
		};
	};
}
static void parse_cache_line(char *line)
{
	unsigned long res;
	char *to_parse = strstr(line, ":");
	if (to_parse) {
		to_parse++;
		while (*to_parse != 0 && isspace(*to_parse)) {
			to_parse++;
		}
		res = strtoul(to_parse, NULL, 10);
		if (is_power_of_2(res))
			um_host_params.cache_alignment = res;
	}
}

void os_subarch_load_cpuinfo(void)
{
	FILE *cpuinfo;
	char *line = NULL;
	size_t len = 0;
	int done_parsing = 0;

	cpuinfo = fopen("/proc/cpuinfo", "r");
	if (cpuinfo == NULL) {
		os_info("Failed to get host CPU features\n");
	} else {
		while ((getline(&line, &len, cpuinfo)) != -1) {
			if (strstr(line, "flags")) {
				parse_host_cpu_flags(line);
				done_parsing++;
			}
			if (strstr(line, "cache_alignment")) {
				parse_cache_line(line);
				done_parsing++;
			}
			free(line);
			line = NULL;
			if (done_parsing > 1)
				break;
		}
		fclose(cpuinfo);
	}
}
