# SPDX-License-Identifier: GPL-2.0-or-later

SUBARCH_DIR := arch/$(HEADER_ARCH)/um
UM_DIR := arch/um

$(SUBARCH_DIR)/built-in.a:
	$(Q)$(MAKE) $(build)=$(SUBARCH_DIR)

$(UM_DIR)/os-Linux/built-in.a:
	$(Q)$(MAKE) $(build)=$(UM_DIR)/os-Linux

quiet_cmd_ld_vmlinux_arch.o = LD      $@
	cmd_ld_vmlinux_arch.o = $(LD) ${KBUILD_LDFLAGS} -r -o $@ --whole-archive $(filter-out FORCE, $^)

$(obj)/vmlinux.arch.o: $(SUBARCH_DIR)/built-in.a $(UM_DIR)/os-Linux/built-in.a FORCE
	$(call if_changed,ld_vmlinux.arch.o)
