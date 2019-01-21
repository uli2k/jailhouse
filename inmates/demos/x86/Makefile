#
# Jailhouse, a Linux-based partitioning hypervisor
#
# Copyright (c) Siemens AG, 2013, 2014
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This work is licensed under the terms of the GNU GPL, version 2.  See
# the COPYING file in the top-level directory.
#

include $(INMATES_LIB)/Makefile.lib

INMATES := tiny-demo.bin apic-demo.bin ioapic-demo.bin 32-bit-demo.bin \
	pci-demo.bin e1000-demo.bin ivshmem-demo.bin smp-demo.bin rnc-demo.bin

tiny-demo-y	:= tiny-demo.o
apic-demo-y	:= apic-demo.o
ioapic-demo-y	:= ioapic-demo.o
pci-demo-y	:= pci-demo.o
e1000-demo-y	:= e1000-demo.o
ivshmem-demo-y	:= ivshmem-demo.o
smp-demo-y	:= smp-demo.o
rnc-demo-y	:= rnc-demo.o
rnc-demo-y	+= igb/e1000_82575.o igb/e1000_api.o igb/e1000_i210.o igb/e1000_mac.o igb/e1000_manage.o igb/e1000_mbx.o igb/e1000_nvm.o igb/e1000_phy.o
rnc-demo-y += soem/ethercatmain.o soem/ethercatbase.o soem/ethercatcoe.o soem/ethercatconfig.o soem/ethercatdc.o soem/ethercatfoe.o soem/ethercatprint.o soem/ethercatsoe.o
rnc-demo-y += igb/igb_main.o soem/nicdrv.o soem/osal.o soem/oshw.o

$(eval $(call DECLARE_32_BIT,32-bit-demo))
32-bit-demo-y	:= 32-bit-demo.o

$(eval $(call DECLARE_TARGETS,$(INMATES)))
