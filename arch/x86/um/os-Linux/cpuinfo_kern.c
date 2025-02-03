// SPDX-License-Identifier: GPL-2.0

#include <linux/ctype.h>
#include <linux/kstrtox.h>
#include <linux/log2.h>
#include <asm/cpufeature.h>
#include <arch.h>
#include "cpuinfo_internal.h"

static void parse_host_cpu_flags(char *line)
{
	int i;
	for (i = 0; i < 32*NCAPINTS; i++) {
		if ((x86_cap_flags[i] != NULL) && strstr(line, x86_cap_flags[i]))
			set_cpu_cap(&boot_cpu_data, i);
	}
}
static void parse_cache_line(char *line)
{
	long res;
	char *to_parse = strstr(line, ":");
	if (to_parse) {
		to_parse++;
		while (*to_parse != 0 && isspace(*to_parse)) {
			to_parse++;
		}
		if (kstrtoul(to_parse, 10, &res) == 0 && is_power_of_2(res))
			boot_cpu_data.cache_alignment = res;
		else
			boot_cpu_data.cache_alignment = L1_CACHE_BYTES;
	}
}

void arch_load_cpuinfo(void)
{
	get_host_cpu_features(parse_host_cpu_flags, parse_cache_line);
}
