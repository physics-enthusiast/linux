// SPDX-License-Identifier: GPL-2.0

#include <linux/seq_file.h>

#include <asm/cpufeature.h>

struct cpuinfo_x86 boot_cpu_data = {
	.x86_capability		= { 0 }
};

EXPORT_SYMBOL(boot_cpu_data);

void um_subarch_cpuinfo(struct seq_file *m)
{
	int i;

	seq_printf(m, "fpu\t\t: %s\n", cpu_has(&boot_cpu_data, X86_FEATURE_FPU) ? "yes" : "no");
	seq_printf(m, "flags\t\t:");
	for (i = 0; i < 32*NCAPINTS; i++)
		if (cpu_has(&boot_cpu_data, i) && (x86_cap_flags[i] != NULL))
			seq_printf(m, " %s", x86_cap_flags[i]);
	seq_printf(m, "\n");
}
