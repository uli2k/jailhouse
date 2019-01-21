/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2014
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 *
 * Append "-device e1000,addr=19,netdev=..." to the QEMU command line for
 * testing in the virtual machine. Adjust configs/x86/e1000-demo.c for real
 * machines as needed.
 */

#include <inmate.h>
#include "soem/ethercat.h"

#define MAX_BUFF_SIZE	1024

char buffer[MAX_BUFF_SIZE];

void inmate_main(void)
{
	printk("ec_init return: %d\n", ec_init(buffer));
	printk("ec_config_init return: %d\n", ec_config_init(FALSE));
	for(;;)
		halt();
}
