#include <inmate.h>
#include "e1000_api.h"

int igb_init(u8 mac[6]);
int igb_send(void *buffer, u16 size);
int igb_recv(void *buffer, u16 size);

#define RX_DESCRIPTORS		8
#define RX_BUFFER_SIZE		2048
#define TX_DESCRIPTORS		8

struct pci_device_id {
	u16 vendor, device;
	const char *name;
};
#define PCI_VDEVICE(ven, dev, name)	PCI_VENDOR_ID_##ven, (dev), (name)
#define PCI_VENDOR_ID_HP	0x103C
#define PCI_VENDOR_ID_DELL	0x1028
#define PCI_VENDOR_ID_INTEL	0x8086

static const struct pci_device_id igb_pci_tbl[] = {
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I354_BACKPLANE_1GBPS,		"I354_BACKPLANE_1GBPS") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I354_SGMII,				"I354_SGMII") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I354_BACKPLANE_2_5GBPS,	"I354_BACKPLANE_2_5GBPS") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_COPPER,				"I210_COPPER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_FIBER,				"I210_FIBER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_SERDES,				"I210_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_SGMII,				"I210_SGMII") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_COPPER_FLASHLESS,	"I210_COPPER_FLASHLESS") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_SERDES_FLASHLESS,	"I210_SERDES_FLASHLESS") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I211_COPPER,				"I211_COPPER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_COPPER,				"I350_COPPER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_FIBER,				"I350_FIBER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_SERDES,				"I350_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_SGMII,				"I350_SGMII") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_COPPER,				"82580_COPPER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_FIBER,				"82580_FIBER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_QUAD_FIBER,			"82580_QUAD_FIBER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_SERDES,				"82580_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_SGMII,				"82580_SGMII") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_COPPER_DUAL,		"82580_COPPER_DUAL") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_SGMII,			"DH89XXCC_SGMII") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_SERDES,			"DH89XXCC_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_BACKPLANE,		"DH89XXCC_BACKPLANE") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_SFP,				"DH89XXCC_SFP") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576,					"82576") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_NS,					"82576_NS") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_NS_SERDES,			"82576_NS_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_FIBER,				"82576_FIBER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_SERDES,				"82576_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_SERDES_QUAD,		"82576_SERDES_QUAD") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_QUAD_COPPER_ET2,	"82576_QUAD_COPPER_ET2") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_QUAD_COPPER,		"82576_QUAD_COPPER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82575EB_COPPER,			"82575EB_COPPER") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82575EB_FIBER_SERDES,		"82575EB_FIBER_SERDES") },
	{ PCI_VDEVICE(INTEL, E1000_DEV_ID_82575GB_QUAD_COPPER,		"82575GB_QUAD_COPPER") },
	/* required last entry */
	{0, }
};

static u8 buffer[RX_DESCRIPTORS * RX_BUFFER_SIZE];
static struct e1000_rx_desc rx_ring[RX_DESCRIPTORS] __attribute__((aligned(128)));
static struct e1000_tx_desc tx_ring[TX_DESCRIPTORS] __attribute__((aligned(128)));
static unsigned int rx_idx, tx_idx;

static int bdf;
struct e1000_hw hw;

#define IGB_RX_PTHRESH	((hw->mac.type == e1000_i354) ? 12 : 8)
#define IGB_RX_HTHRESH	8
#define IGB_RX_WTHRESH	4
#define IGB_TX_PTHRESH	((hw->mac.type == e1000_i354) ? 20 : 8)
#define IGB_TX_HTHRESH	1
#define IGB_TX_WTHRESH	((hw->mac.type == e1000_i354) ? 4 : 16)

#define E1000_TCTL_CT_DEF		0x000000F0
#define E1000_TCTL_COLD_DEF		0x00040000
#define E1000_TIPG_IPGT_DEF		0x0000000A
#define E1000_TIPG_IPGR1_DEF	0x00002800
#define E1000_TIPG_IPGR2_DEF	0x00A00000

u32 e1000_read_reg(struct e1000_hw *hw, u32 reg)
{
	u8 __iomem *hw_addr = READ_ONCE(hw->hw_addr);
	u32 value = 0;

	if (E1000_REMOVED(hw_addr))
		return ~value;

	value = readl(&hw_addr[reg]);

	/* reads should not return all F's */
	if (!(~value) && (!reg || !(~readl(hw_addr)))) {
		hw->hw_addr = NULL;
	}

	return value;
}

void e1000_read_pci_cfg(struct e1000_hw *hw, u32 reg, u16 *value)
{
	*value = pci_read_config(bdf, reg, 2);
}

void e1000_write_pci_cfg(struct e1000_hw *hw, u32 reg, u16 *value)
{
	pci_write_config(bdf, reg, *value, 2);
}

s32 e1000_read_pcie_cap_reg(struct e1000_hw *hw, u32 reg, u16 *value)
{
	return -E1000_ERR_CONFIG;
}

s32 e1000_write_pcie_cap_reg(struct e1000_hw *hw, u32 reg, u16 *value)
{
	return -E1000_ERR_CONFIG;
}

// Configure a receive ring after Reset
static void igb_configure_rx_ring(struct e1000_hw *hw)
{
	u32 rxdctl = 0, rctl;

	/* disable the queue */
	E1000_WRITE_REG(hw, E1000_RXDCTL(0), 0);
	E1000_WRITE_FLUSH(hw);
	msec_delay(10);

	/* Set DMA base address registers */
	E1000_WRITE_REG(hw, E1000_RDBAL(0), (u64)&rx_ring);
	E1000_WRITE_REG(hw, E1000_RDBAH(0), ((u64)&rx_ring) >> 32);
	E1000_WRITE_REG(hw, E1000_RDLEN(0), sizeof(rx_ring));

	/* initialize head and tail */
	E1000_WRITE_REG(hw, E1000_RDH(0), 0);
	E1000_WRITE_REG(hw, E1000_RDT(0), 0);

	rxdctl |= IGB_RX_PTHRESH;
	rxdctl |= IGB_RX_HTHRESH << 8;
	rxdctl |= IGB_RX_WTHRESH << 16;

	/* enable receive descriptor fetching */
	rxdctl |= E1000_RXDCTL_QUEUE_ENABLE;
	E1000_WRITE_REG(hw, E1000_RXDCTL(0), rxdctl);

	rctl = E1000_READ_REG(hw, E1000_RCTL);
	rctl |= E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_SZ_2048 | E1000_RCTL_SECRC;	// Receive Control: enable, broadcast enable, buffer size 2048, Strip Ethernet CRC
	E1000_WRITE_REG(hw, E1000_RCTL, rctl);

	E1000_WRITE_REG(hw, E1000_RDT(0), RX_DESCRIPTORS - 1);
}

// Configure a transmit ring after Reset
static void igb_configure_tx_ring(struct e1000_hw *hw)
{
	u32 txdctl = 0, tctl;

	/* disable the queue */
	E1000_WRITE_REG(hw, E1000_TXDCTL(0), 0);
	E1000_WRITE_FLUSH(hw);
	msec_delay(10);

	/* Set DMA base address registers */
	E1000_WRITE_REG(hw, E1000_TDBAL(0), (u64)&tx_ring);
	E1000_WRITE_REG(hw, E1000_TDBAH(0), ((u64)&tx_ring) >> 32);
	E1000_WRITE_REG(hw, E1000_TDLEN(0), sizeof(tx_ring));

	/* initialize head and tail */
	E1000_WRITE_REG(hw, E1000_TDH(0), 0);
	E1000_WRITE_REG(hw, E1000_TDT(0), 0);

	txdctl |= IGB_TX_PTHRESH;
	txdctl |= IGB_TX_HTHRESH << 8;
	txdctl |= IGB_TX_WTHRESH << 16;

	/* enable transmit descriptor fetching */
	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	E1000_WRITE_REG(hw, E1000_TXDCTL(0), txdctl);

	tctl = E1000_READ_REG(hw, E1000_TCTL);
	tctl |= E1000_TCTL_EN | E1000_TCTL_PSP | E1000_TCTL_CT_DEF | E1000_TCTL_COLD_DEF;	// Transmit Control: enable, pad short packets, collision threshold, collision distance
	E1000_WRITE_REG(hw, E1000_TCTL, tctl);
	E1000_WRITE_REG(hw, E1000_TIPG, E1000_TIPG_IPGT_DEF | E1000_TIPG_IPGR1_DEF | E1000_TIPG_IPGR2_DEF);
}

int igb_send(void *buffer, u16 size)
{
	unsigned int idx = tx_idx;

	memset(&tx_ring[idx], 0, sizeof(struct e1000_tx_desc));
	tx_ring[idx].buffer_addr = (u64)buffer;
	tx_ring[idx].lower.data = size | E1000_TXD_CMD_EOP | E1000_TXD_CMD_IFCS | E1000_TXD_CMD_RS;
	tx_idx = (tx_idx + 1) % TX_DESCRIPTORS;
	E1000_WRITE_REG(&hw, E1000_TDT(0), tx_idx);

	while (!(tx_ring[idx].upper.data & E1000_TXD_STAT_DD))
		cpu_relax();
	// printk("\nSend %d byte: ", size);
	// for (u16 i = 0; i < size; i++)
	// 	printk("%02x,", ((u8*)buffer)[i]);
	return size;
}

int igb_recv(void *buffer, u16 size)
{
	unsigned int idx = rx_idx;

	if (!(rx_ring[idx].status & E1000_RXD_STAT_DD))
		return 0;
	memcpy(buffer, (void *)rx_ring[idx].buffer_addr, size);
	rx_ring[idx].status &= ~E1000_RXD_STAT_DD;
	rx_idx = (rx_idx + 1) % RX_DESCRIPTORS;
	E1000_WRITE_REG(&hw, E1000_RDT(0), idx);
	// printk("\nRecv %d byte: ", size);
	// for (u16 i = 0; i < size; i++)
	// 	printk("%02x,", ((u8*)buffer)[i]);
	return size;
}

int igb_init(u8 mac[6])
{
	u64 bar;
	void *mmiobar;

	for (;;)
	{
		bdf = pci_find_device(PCI_ID_ANY, PCI_ID_ANY, bdf);	// 查找PCI设备
		if (bdf < 0) {
			printk("No device found!\n");
			return 0;
		}
		u16 vendor = pci_read_config(bdf, PCI_CFG_VENDOR_ID, 2);
		u16 device = pci_read_config(bdf, PCI_CFG_DEVICE_ID, 2);
		printk("Found %04x:%04x at %02x:%02x.%x\n", vendor, device,
			bdf >> 8, (bdf >> 3) & 0x1f, bdf & 0x3);
		for (const struct pci_device_id *id = igb_pci_tbl; id->vendor != 0; id++)
		{
			if (vendor == id->vendor && device == id->device)
			{
				hw.vendor_id = vendor;
				hw.device_id = device;
				printk("Found Supported NIC: %s\n", id->name);
				goto found_nic;
			}
		}
	}

found_nic:
	bar = pci_read_config(bdf, PCI_CFG_BAR, 4);	// 读取设备配置
	if ((bar & 0x6) == 0x4)
		bar |= (u64)pci_read_config(bdf, PCI_CFG_BAR + 4, 4) << 32;
	mmiobar = (void *)(bar & ~0xfUL);
	map_range(mmiobar, 128 * 1024, MAP_UNCACHED);	// 映射寄存器空间
	hw.hw_addr = mmiobar;
	printk("MMIO register BAR at %p\n", mmiobar);

	pci_write_config(bdf, PCI_CFG_COMMAND, PCI_CMD_MEM | PCI_CMD_MASTER, 2);

	e1000_setup_init_funcs(&hw, true);	// 初始化函数指针
	e1000_reset_hw(&hw);	// 重启网卡芯片
	e1000_setup_fiber_serdes_link_generic(&hw);	// 配置碰撞距离和流量控制
	e1000_setup_link_generic(&hw);	// 设置流控制和链接设置
	e1000_power_up_phy(&hw);	// 断电时恢复链接

	printk("Waiting for link...");
	for (;;)
	{
		msec_delay(10);
		u32 status = E1000_READ_REG(&hw, E1000_STATUS);
		if (status & E1000_STATUS_LU)	// 读取当前状态寄存器取得链接状态
			break;
	}
	printk(" OK\n");

	u16 speed, duplex;
	e1000_get_speed_and_duplex_copper_generic(&hw, &speed, &duplex);	// 读取当前速度/双工的状态寄存器
	printk("speed: %d, duplex: %d\n", speed, duplex);

	e1000_rar_set(&hw, mac, 0);	// 设置MAC地址

	for (unsigned int i = 0; i < RX_DESCRIPTORS; i++)
		rx_ring[i].buffer_addr = (u64)&buffer[i * RX_BUFFER_SIZE];
	igb_configure_rx_ring(&hw);
	igb_configure_tx_ring(&hw);

	return 1;
}