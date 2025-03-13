/* SPDX-License-Identifier: GPL-2.0 */
#ifndef SETUP_H_INCLUDED
#define SETUP_H_INCLUDED

#include <linux/hashtable.h>
#include <linux/log2.h>

#include <um_host.h>

/* POSIX mandated with _POSIX_ARG_MAX that we can rely on 4096 chars in the
 * command line, so this choice is ok.
 */

#define COMMAND_LINE_SIZE 4096

struct um_subarch_capability {
	char *flag;
	bool enabled;
	struct hlist_node node;
};

#define UM_SUBARCH_CAP_COUNT	(ARRAY_SIZE(UM_SUBARCH_EXTENSIONS) +	\
				ARRAY_SIZE(UM_SUBARCH_CONSTRAINTS) +	\
				ARRAY_SIZE(UM_SUBARCH_SYSCALLS))
#define UM_SUBARCH_CAP_HASH_BITS order_base_2(UM_SUBARCH_CAP_COUNT)
extern DECLARE_HASHTABLE(um_subarch_cap_dict, UM_SUBARCH_CAP_HASH_BITS);

extern void um_subarch_setup(void);

#endif		/* SETUP_H_INCLUDED */
