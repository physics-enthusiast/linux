// SPDX-License-Identifier: GPL-2.0
#include <linux/types.h>
#include <linux/kbuild.h>

void um_constants(void)
{
	DEFINE(UM_UNSIGNED_INT_BITS, sizeof(unsigned int));
  DEFINE(UM_UINTPTR_T_BITS, sizeof(uintptr_t));
}
