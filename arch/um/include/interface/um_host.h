/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_H__
#define __UM_HOST_H__

struct boot_params {
	char machine[65];
	int nr_cpus;
	int cache_alignment;
	int page_shifts[8];
	long mem_size;
};

extern struct boot_params um_host_params;

#endif
