/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_H__
#define __UM_HOST_H__

#include <um_host_arch.h>

/* Prepended to avoid inferfering with other macros */
#define UM_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define UM_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define UM_BITFIELD_CHARS(x) UM_DIV_ROUND_UP(UM_ARRAY_SIZE(x), CHAR_BIT)

struct boot_params {
	char machine[65];
	int nr_cpus;
	int cache_alignment;
	int page_shifts[8];
	unsigned char extensions[UM_BITFIELD_CHARS(UM_SUBARCH_EXTENSIONS)];
	unsigned char constraints[UM_BITFIELD_CHARS(UM_SUBARCH_CONSTRAINTS)];
	unsigned char syscalls[UM_BITFIELD_CHARS(UM_SUBARCH_SYSCALLS)];
	um_subarch_boot_params subarch_data;
};

extern struct boot_params um_host_params;

#endif
