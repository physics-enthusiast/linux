// SPDX-License-Identifier: GPL-2.0

extern void get_host_cpu_features(
	void (*flags_helper_func)(char *line),
	void (*cache_helper_func)(char *line));
