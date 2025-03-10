/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_H__
#define __UM_HOST_H__

#include <um_host_arch.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define BITFIELD_SIZE_CHAR(x) DIV_ROUND_UP(ARRAY_SIZE(x), CHAR_BIT)

struct boot_params {
	char machine[65];
	int nr_cpus;
	int cache_alignment;
	int page_shifts[8];
	char extensions[BITFIELD_SIZE_CHAR(UM_SUBARCH_EXTENSIONS)];
	char constraints[BITFIELD_SIZE_CHAR(UM_SUBARCH_CONSTRAINTS)];
	char syscalls[BITFIELD_SIZE_CHAR(UM_SUBARCH_SYSCALLS)];
	um_subarch_boot_params subarch_data;
};

extern struct boot_params um_host_params;

#endif
