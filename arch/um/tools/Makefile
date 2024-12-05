# SPDX-License-Identifier: GPL-2.0-or-later

$(HOST_DIR)/built-in.a:
	$(Q)$(MAKE) $(build)=$(HOST_DIR) need-builtin=1 need-modorder=1

arch/um/os-Linux/built-in.a:
	$(Q)$(MAKE) $(build)=arch/um/os-Linux need-builtin=1 need-modorder=1

quiet_cmd_ld_vmlinux.arch.o = LD      $@
	cmd_ld_vmlinux.arch.o = $(LD) ${KBUILD_LDFLAGS} -r -o $@ --whole-archive $(filter-out FORCE,$^)

$(obj)/vmlinux.arch.o: $(HOST_DIR)/built-in.a arch/um/os-Linux/built-in.a FORCE
	$(call if_changed,ld_vmlinux.arch.o)

targets += vmlinux.arch.o

subdir- += ../os-Linux
