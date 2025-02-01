/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __UM_PROCESSOR_H
#define __UM_PROCESSOR_H
#include <linux/time-internal.h>
#include <linux/seq_file.h>

/* include faultinfo structure */
#include <sysdep/faultinfo.h>

#ifdef CONFIG_X86_32
# include "processor_32.h"
#else
# include "processor_64.h"
#endif

#define KSTK_EIP(tsk) KSTK_REG(tsk, HOST_IP)
#define KSTK_ESP(tsk) KSTK_REG(tsk, HOST_SP)
#define KSTK_EBP(tsk) KSTK_REG(tsk, HOST_BP)

#define ARCH_IS_STACKGROW(address) \
       (address + 65536 + 32 * sizeof(unsigned long) >= UPT_SP(&current->thread.regs.regs))

#include <asm/user.h>

/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static __always_inline void rep_nop(void)
{
	__asm__ __volatile__("rep;nop": : :"memory");
}

static __always_inline void cpu_relax(void)
{
	if (time_travel_mode == TT_MODE_INFCPU ||
	    time_travel_mode == TT_MODE_EXTERNAL)
		time_travel_ndelay(1);
	else
		rep_nop();
}

#define task_pt_regs(t) (&(t)->thread.regs)

#include <asm/processor-generic.h>
#include <asm/cpufeatures.h>

struct cpuinfo_x86 {
	union {
		__u32		x86_capability[NCAPINTS + NBUGINTS];
		unsigned long	x86_capability_alignment;
	};
};

extern struct cpuinfo_x86 boot_cpu_data_extended;

extern void arch_show_cpuinfo(struct seq_file *m);

#endif
