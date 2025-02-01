// SPDX-License-Identifier: GPL-2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <linux/kstrtox.h>
#include <linux/log2.h>

#include <asm/cpufeature.h>
#include <os.h>

void get_host_cpu_features(void)
{
	FILE *cpuinfo;
	char *line = NULL;
	size_t len = 0;
	int done_parsing = 0;
        int i;
        long res;
	char *to_parse = strstr(line, ":");

	cpuinfo = fopen("/proc/cpuinfo", "r");
	if (cpuinfo == NULL) {
		os_info("Failed to get host CPU features\n");
	} else {
		while ((getline(&line, &len, cpuinfo)) != -1) {
			if (strstr(line, "flags")) {
                        	for (i = 0; i < 32*NCAPINTS; i++) {
                        		if ((x86_cap_flags[i] != NULL) && strstr(line, x86_cap_flags[i]))
                        			set_cpu_cap(&boot_cpu_data, i);
                        	}
				done_parsing++;
			}
			if (strstr(line, "cache_alignment")) {
                        	if (to_parse) {
                        		to_parse++;
                        		while (*to_parse != 0 && isspace(*to_parse)) {
                        			to_parse++;
                        		}
                        		if (kstrtoul(to_parse, 10, &res) == 0 && is_power_of_2(res))
                        			boot_cpu_data.cache_alignment = res;
                        	}
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
