/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_H__
#define __UM_HOST_H__

#include <um_host_arch.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

struct boot_params {
	char machine[65];
	int nr_cpus;
	int cache_alignment;
	int page_shifts[8];
	char extensions[ARRAY_SIZE(UM_ARCH_EXTENSIONS)];
	char constraints[ARRAY_SIZE(UM_ARCH_CONSTRAINTS)];
	char syscalls[ARRAY_SIZE(UM_ARCH_SYSCALLS)];
	um_arch_boot_params arch_data;
};

extern struct boot_params um_host_params;

#endif
