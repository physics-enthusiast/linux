// SPDX-License-Identifier: GPL-2.0

#include <linux/hashtable.h>
#include <linux/log2.h>

#include <asm/cpufeature.h>
#include <asm/setup.h>

struct x86_cap_node {
    int idx;
    char flag;
    struct hlist_node node;
};

DEFINE_HASHTABLE(x86_cap_dict, roundup_pow_of_two(32*NCAPINTS));

void um_subarch_setup(void)
{
	int i;
	for (i = 0; i < 32*NCAPINTS; i++) {
		if (x86_cap_flags[i] != NULL)
			
	}
}
