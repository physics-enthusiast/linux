/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __UM_HOST_ARCH_H__
#define __UM_HOST_ARCH_H__

struct arch_boot_params {
	unsigned char x86_model;
	unsigned char x86_family;
	unsigned char x86_vendor;
	/*
	 * The features_* arrays below must be large enough to contain
	 * bitfields their respective set of UM_X86_FEATURES_* flags
	 */
	unsigned char features_extension[15];
	unsigned char features_breaking[1];
	unsigned char features_syscall[1];
};

/*
 * Host-independent subset of arch/x86/include/asm/cpufeatures.h.
 * Generally, "host-independent" means that it is possible to do useful work
 * in Ring-3 without regularly trapping to Ring-0. Only mark these as available
 * if they are enabled by the host.
 *
 * These are sorted roughly chronologically by when the feature becomes
 * accessible to ring-3. This is generally when support is first merged into
 * the kernel, unless it starts off as a privileged extension that later on
 * allows some degree of unpriviledged interaction (e.g. aperfmperf MSRs
 * becoming readable via RDPRU).
 */
static const char * const UM_X86_FEATURES_EXTENSION[] = {
	"fpu",
	"cx8",
	"cpuid",
	"mmx",
	"tsc",
	"cmov",
	"cxmmx",
	"3dnow",
	"fxsr",
	"3dnowext",
	"clflush",
	"mmxext",
	"sse",
	"sse2",
	"ace",
	"rng",
	"lm",
	"cx16",
	"lahf_lm",
	"pni",
	"rdtscp",
	"ace2",
	"phe",
	"pmm",
	"3dnowprefetch",
	"abm",
	"misalignsse",
	"popcnt",
	"sse4a",
	"sse4_1",
	"sse4_2",
	"lfence_rdtsc",
	"xsave",
	"aes",
	"avx",
	"fma",
	"pclmulqdq",
	"movbe",
	"f16c",
	"rdrand",
	"fsgsbase",
	"xsaveopt",
	"xop",
	"fma4",
	"lwp",
	"tbm",
	"erms",
	"avx2",
	"bmi1",
	"bmi2",
	"hle",
	"rtm",
	"adx",
	"rdseed",
	"mpx",
	"avx512cd",
	"avx512er",
	"avx512f",
	"avx512pf",
	"clflushopt",
	"xgetbv1",
	"xsavec",
	"clwb",
	"sha_ni",
	"clzero",
	"pku",
	"avx512bw",
	"avx512dq",
	"avx512vl",
	"avx512_4fmaps",
	"avx512_4vnniw",
	"avx512ifma",
	"avx512vbmi",
	"rdpid",
	"avx512_vpopcntdq",
	"la57",
	"avx512_bitalg",
	"avx512_vnni",
	"gfni",
	"vaes",
	"vpclmulqdq",
	"xsaveerptr",
	"cldemote",
	"movdiri",
	"movdir64b",
	"md_clear",
	"fdp_excptn_only",
	"zero_fcs_fds",
	"avx512_bf16",
	"avx512_vp2intersect",
	"aperfmperf",
	"rdpru",
	"fsrm",
	"serialize",
	"tsxldtrk",
	"enqcmd",
	"avx512_fp16",
	"avx_vnni",
	"rtm_always_abort",
	"amx_tile",
	"amx_bf16",
	"amx_int8",
	"cmpccxadd",
	"amx_fp16",
	"avx_ifma",
	"fsrc",
	"fsrs",
	"fzrm",
	"null_sel_clr_base",
	"lam",
	"sha512",
	"sm3",
	"sm4"
};

/*
 * These are similar to UM_X86_FEATURES_EXTENSION, but they also make certain
 * sequences of instructions globally invalid. If it is possible to enable or
 * disable a particular one on a address-space-by-address-space basis, leave
 * the bit as 0 and use the kernel module to determine which address spaces
 * want it enabled
 */
static const char * const UM_X86_FEATURES_BREAKING[] = {
	"umip",
	"split_lock_detect",
	"bus_lock_detect",
	"shstk"
};

/*
 * We need to intercept all syscalls regardless of the state of these flags to
 * maintain guest/host separation, but specifying them informs userspace
 * programs which read /proc/cpuinfo (instead of calling CPUID) of their
 * availability
 */
static const char * const UM_X86_FEATURES_SYSCALL[] = {
	"sep",
	"syscall",
};

#endif
