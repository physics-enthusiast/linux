// SPDX-License-Identifier: GPL-2.0

#include <linux/string.h>
#include <linux/stringhash.h>

#include <asm/cpufeature.h>
#include <asm/setup.h>
#include <um_host.h>

void um_subarch_setup(void)
{
	int i;
	const char *flag;
	unsigned int hash;
	struct um_subarch_capability * current_cap;
	for (i = 0; i < 32*NCAPINTS; i++) {
		if (x86_cap_flags[i] != NULL) {
			flag = x86_cap_flags[i];
			hash = full_name_hash(NULL, flag, strlen(flag));
			hash_for_each_possible(um_subarch_cap_dict, current_cap, node, hash) {
				if (!strcmp(current_cap->flag, flag) && current_cap->present)
					set_cpu_cap(&boot_cpu_data, i);
			}
		}
	}
# if !IS_ENABLED(CONFIG_64BIT)
	if (!strcmp(um_host_params.machine, "x86_64")) {
		strncpy(um_host_params.machine, "i686",
			sizeof(um_host_params.machine));
		return;
	}
# else
	if (!strcmp(um_host_params.machine, "i686")) {
		strncpy(um_host_params.machine, "x86_64",
			sizeof(um_host_params.machine));
		return;
	}
# endif
}
