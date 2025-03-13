// SPDX-License-Identifier: GPL-2.0

#include <linux/string.h>

#include <asm/cpufeature.h>
#include <asm/setup.h>

void um_subarch_setup(void)
{
	int i;
	char *flag;
	unsigned int hash;
	struct um_subarch_capability * current;
	for (i = 0; i < 32*NCAPINTS; i++) {
		if (x86_cap_flags[i] != NULL) {
			flag = x86_cap_flags[i];
			hash = full_name_hash(NULL, flag, strlen(flag));
			hash_for_each_possible(um_subarch_cap_dict, current, node, hash) {
				if (!strcmp(cur->flag, flag) && cur->present)
					set_cpu_cap(&boot_cpu_data, i);
			}
		}
	}
}
