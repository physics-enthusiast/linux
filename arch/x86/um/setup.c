// SPDX-License-Identifier: GPL-2.0

#include <linux/hashtable.h>
#include <linux/log2.h>
#include <linux/string.h>
#include <linux/stringhash.h>
#include <linux/types.h>

#include <asm/cpufeature.h>
#include <asm/setup.h>

struct x86_cap_node {
    int idx;
    char flag;
    struct hlist_node node;
};

struct x86_cap_node x86_cap_nodes[32*NCAPINTS];

DEFINE_HASHTABLE(x86_cap_dict, roundup_pow_of_two(32*NCAPINTS));

void um_subarch_setup(void)
{
	int i;
	char *flag;
	unsigned int hash;
	for (i = 0; i < 32*NCAPINTS; i++) {
		if (x86_cap_flags[i] != NULL) {
			flag = x86_cap_flags[i];
			x86_cap_nodes[i].idx = i;
			x86_cap_nodes[i].flag = flag;
			hash = full_name_hash(NULL, flag, strlen(flag));
			hash_add(x86_cap_dict, &x86_cap_nodes[i].node, hash);
	}
}
