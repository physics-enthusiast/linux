/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_ARCH_H__
#define __UM_HOST_ARCH_H__

struct arch_boot_params {
	unsigned char x86_model;
	unsigned char x86_family;
	unsigned char x86_vendor;
};

#endif
