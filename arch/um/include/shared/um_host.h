/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_H__
#define __UM_HOST_H__

#include <um_host_arch.h>

struct boot_params {
	char machine[65];
	int nr_cpus;
	int cache_alignment;
	int page_shifts[8];
	arch_boot_params arch_data;
};

extern struct boot_params um_host_params;

#endif
