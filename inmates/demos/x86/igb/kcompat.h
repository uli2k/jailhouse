/*******************************************************************************

	Intel(R) Gigabit Ethernet Linux Driver
	Copyright(c) 2007 - 2018 Intel Corporation.

	This program is free software; you can redistribute it and/or modify it
	under the terms and conditions of the GNU General Public License,
	version 2, as published by the Free Software Foundation.

	This program is distributed in the hope it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
	more details.

	The full GNU General Public License is included in this distribution in
	the file called "COPYING".

	Contact Information:
	Linux NICS <linux.nics@intel.com>
	e1000-devel Mailing List <e1000-devel@lists.sourceforge.net>
	Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

*******************************************************************************/

#ifndef _KCOMPAT_H_
#define _KCOMPAT_H_

#include <inmate.h>

/* e1000_ dependency */

#define __iomem

#define READ_ONCE(x)	(*(volatile typeof(x) *) &(x))

#define readb(c)		({ u8  __v = mmio_read8(c); __v; })
#define readw(c)		({ u16 __v = mmio_read16(c); __v; })
#define readl(c)		({ u32 __v = mmio_read32(c); __v; })
#define writeb(v,c)		({ mmio_write8(c,v); })
#define writew(v,c)		({ mmio_write16(c,v); })
#define writel(v,c)		({ mmio_write32(c,v); })

#define unlikely(_x)	_x

#endif /* _KCOMPAT_H_ */
