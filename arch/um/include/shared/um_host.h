/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_H__
#define __UM_HOST_H__

#include <um_host_arch.h>

struct um_host_info {
	char machine[65];
	arch_cpufeatures cpuinfo;
};

extern struct um_host_info um_host_params;

#endif
