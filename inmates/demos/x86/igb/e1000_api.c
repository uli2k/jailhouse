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

#include "e1000_api.h"

/**
 * e1000_init_mac_params -初始化MAC函数指针
 * @hw:指向HW结构的指针
 *
 *这个函数初始化MAC函数集的函数指针。
 *由驱动程序或e1000_setup_init_funcs调用。
 **/
s32 e1000_init_mac_params(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;

	if (hw->mac.ops.init_params) {
		ret_val = hw->mac.ops.init_params(hw);
		if (ret_val) {
			DEBUGOUT("MAC Initialization Error\n");
			goto out;
		}
	} else {
		DEBUGOUT("mac.init_mac_params was NULL\n");
		ret_val = -E1000_ERR_CONFIG;
	}

out:
	return ret_val;
}

/**
 * e1000_init_nvm_params -初始化NVM函数指针
 * @hw:指向HW结构的指针
 *
 *这个函数初始化NVM函数集的函数指针。
 *由驱动程序或e1000_setup_init_funcs调用。
 **/
s32 e1000_init_nvm_params(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;

	if (hw->nvm.ops.init_params) {
		ret_val = hw->nvm.ops.init_params(hw);
		if (ret_val) {
			DEBUGOUT("NVM Initialization Error\n");
			goto out;
		}
	} else {
		DEBUGOUT("nvm.init_nvm_params was NULL\n");
		ret_val = -E1000_ERR_CONFIG;
	}

out:
	return ret_val;
}

/**
 * e1000_init_phy_params -初始化PHY函数指针
 * @hw:指向HW结构的指针
 *
 *这个函数初始化PHY函数集的函数指针。
 *由驱动程序或e1000_setup_init_funcs调用。
 **/
s32 e1000_init_phy_params(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;

	if (hw->phy.ops.init_params) {
		ret_val = hw->phy.ops.init_params(hw);
		if (ret_val) {
			DEBUGOUT("PHY Initialization Error\n");
			goto out;
		}
	} else {
		DEBUGOUT("phy.init_phy_params was NULL\n");
		ret_val =  -E1000_ERR_CONFIG;
	}

out:
	return ret_val;
}

/**
 * e1000_init_mbx_params -初始化邮箱函数指针
 * @hw:指向HW结构的指针
 *
 *这个函数初始化PHY函数集的函数指针。
 *由驱动程序或e1000_setup_init_funcs调用。
 **/
s32 e1000_init_mbx_params(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;

	if (hw->mbx.ops.init_params) {
		ret_val = hw->mbx.ops.init_params(hw);
		if (ret_val) {
			DEBUGOUT("Mailbox Initialization Error\n");
			goto out;
		}
	} else {
		DEBUGOUT("mbx.init_mbx_params was NULL\n");
		ret_val =  -E1000_ERR_CONFIG;
	}

out:
	return ret_val;
}

/**
 * e1000_set_mac_type -设置MAC类型
 * @hw:指向HW结构的指针
 *
 *此函数根据存储在hw结构中的设备ID设置适配器的mac类型。
 *必须首先调用函数(显式调用或通过e1000_setup_init_funcs()调用)。
 **/
s32 e1000_set_mac_type(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_set_mac_type");

	switch (hw->device_id) {
	case E1000_DEV_ID_82575EB_COPPER:
	case E1000_DEV_ID_82575EB_FIBER_SERDES:
	case E1000_DEV_ID_82575GB_QUAD_COPPER:
		mac->type = e1000_82575;
		break;
	case E1000_DEV_ID_82576:
	case E1000_DEV_ID_82576_FIBER:
	case E1000_DEV_ID_82576_SERDES:
	case E1000_DEV_ID_82576_QUAD_COPPER:
	case E1000_DEV_ID_82576_QUAD_COPPER_ET2:
	case E1000_DEV_ID_82576_NS:
	case E1000_DEV_ID_82576_NS_SERDES:
	case E1000_DEV_ID_82576_SERDES_QUAD:
		mac->type = e1000_82576;
		break;
	case E1000_DEV_ID_82580_COPPER:
	case E1000_DEV_ID_82580_FIBER:
	case E1000_DEV_ID_82580_SERDES:
	case E1000_DEV_ID_82580_SGMII:
	case E1000_DEV_ID_82580_COPPER_DUAL:
	case E1000_DEV_ID_82580_QUAD_FIBER:
	case E1000_DEV_ID_DH89XXCC_SGMII:
	case E1000_DEV_ID_DH89XXCC_SERDES:
	case E1000_DEV_ID_DH89XXCC_BACKPLANE:
	case E1000_DEV_ID_DH89XXCC_SFP:
		mac->type = e1000_82580;
		break;
	case E1000_DEV_ID_I350_COPPER:
	case E1000_DEV_ID_I350_FIBER:
	case E1000_DEV_ID_I350_SERDES:
	case E1000_DEV_ID_I350_SGMII:
	case E1000_DEV_ID_I350_DA4:
		mac->type = e1000_i350;
		break;
	case E1000_DEV_ID_I210_COPPER_FLASHLESS:
	case E1000_DEV_ID_I210_SERDES_FLASHLESS:
	case E1000_DEV_ID_I210_COPPER:
	case E1000_DEV_ID_I210_COPPER_OEM1:
	case E1000_DEV_ID_I210_COPPER_IT:
	case E1000_DEV_ID_I210_FIBER:
	case E1000_DEV_ID_I210_SERDES:
	case E1000_DEV_ID_I210_SGMII:
		mac->type = e1000_i210;
		break;
	case E1000_DEV_ID_I211_COPPER:
		mac->type = e1000_i211;
		break;
	case E1000_DEV_ID_I354_BACKPLANE_1GBPS:
	case E1000_DEV_ID_I354_SGMII:
	case E1000_DEV_ID_I354_BACKPLANE_2_5GBPS:
		mac->type = e1000_i354;
		break;
	default:
		/* 不能在未知设备上加载 */
		ret_val = -E1000_ERR_MAC_INIT;
		break;
	}

	return ret_val;
}

/**
* e1000_setup_init_funcs -初始化函数指针
* @hw:指向HW结构的指针
* @init_device: true将初始化剩余的函数指针，使设备准备好使用。
*	false只设置MAC类型和其他init函数的函数指针。
*	传递false不会生成任何硬件读写。
*
*驱动程序必须调用此函数才能使用其余的“共享”代码文件。只由驱动程序调用。
 **/
s32 e1000_setup_init_funcs(struct e1000_hw *hw, bool init_device)
{
	s32 ret_val;

	/* 在不知道MAC类型的情况下什么也做不了。 */
	ret_val = e1000_set_mac_type(hw);
	if (ret_val) {
		DEBUGOUT("ERROR: MAC type could not be set properly.\n");
		goto out;
	}

	if (!hw->hw_addr) {
		DEBUGOUT("ERROR: Registers not mapped\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	/* 初始化泛型实现的函数指针。我们首先允许驱动模块在之后覆盖它。 */
	e1000_init_mac_ops_generic(hw);
	e1000_init_phy_ops_generic(hw);
	e1000_init_nvm_ops_generic(hw);
	e1000_init_mbx_ops_generic(hw);

	/* 设置init函数指针。这些是适配器家族文件中的函数，用于为该家族中的其他函数设置函数指针。 */
	switch (hw->mac.type) {
	case e1000_82575:
	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
		e1000_init_function_pointers_82575(hw);
		break;
	case e1000_i210:
	case e1000_i211:
		e1000_init_function_pointers_i210(hw);
		break;
	default:
		DEBUGOUT("Hardware not supported\n");
		ret_val = -E1000_ERR_CONFIG;
		break;
	}

	/* 初始化其余的函数指针。在某些情况下，这需要一些寄存器读/写。 */
	if (!(ret_val) && init_device) {
		ret_val = e1000_init_mac_params(hw);
		if (ret_val)
			goto out;

		ret_val = e1000_init_nvm_params(hw);
		if (ret_val)
			goto out;

		ret_val = e1000_init_phy_params(hw);
		if (ret_val)
			goto out;

		ret_val = e1000_init_mbx_params(hw);
		if (ret_val)
			goto out;
	}

out:
	return ret_val;
}

/**
 * e1000_get_bus_info -获取适配器的总线信息
 * @hw:指向HW结构的指针
 *
 *这将获取有关适配器所连接的HW总线的信息，并将其存储在HW结构中。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_get_bus_info(struct e1000_hw *hw)
{
	if (hw->mac.ops.get_bus_info)
		return hw->mac.ops.get_bus_info(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_clear_vfta -清除VLAN筛选表
 * @hw:指向HW结构的指针
 *
 *这将清除适配器上的VLAN筛选表。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
void e1000_clear_vfta(struct e1000_hw *hw)
{
	if (hw->mac.ops.clear_vfta)
		hw->mac.ops.clear_vfta(hw);
}

/**
 * e1000_write_vfta -写入值到VLAN筛选表
 * @hw:指向HW结构的指针
 * @offset:写入值的32位偏移量。
 * @value:要在位置偏移处写入的32位值。
 *
 *将32位值写入VLAN筛选表中的32位偏移量。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
void e1000_write_vfta(struct e1000_hw *hw, u32 offset, u32 value)
{
	if (hw->mac.ops.write_vfta)
		hw->mac.ops.write_vfta(hw, offset, value);
}

/**
 * e1000_update_mc_addr_list -更新组播地址
 * @hw:指向HW结构的指针
 * @mc_addr_list:要编程的多播地址数组
 * @mc_addr_count:要编程的组播地址的数量
 *
 *更新组播表数组。
 *调用方必须有一个打包的多播地址mc_addr_list。
 **/
void e1000_update_mc_addr_list(struct e1000_hw *hw, u8 *mc_addr_list,
			       u32 mc_addr_count)
{
	if (hw->mac.ops.update_mc_addr_list)
		hw->mac.ops.update_mc_addr_list(hw, mc_addr_list,
						mc_addr_count);
}

/**
 * e1000_force_mac_fc -强制MAC流量控制
 * @hw:指向HW结构的指针
 *
 *强制MAC的流量控制设置。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_force_mac_fc(struct e1000_hw *hw)
{
	return e1000_force_mac_fc_generic(hw);
}

/**
 * e1000_check_for_link -检查/存储链接连接
 * @hw:指向HW结构的指针
 *
 *这将检查适配器的链接条件，并将结果存储在hw->mac结构中。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_check_for_link(struct e1000_hw *hw)
{
	if (hw->mac.ops.check_for_link)
		return hw->mac.ops.check_for_link(hw);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_check_mng_mode -检查管理模式
 * @hw:指向HW结构的指针
 *
 *这将检查适配器是否启用了可管理性。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
bool e1000_check_mng_mode(struct e1000_hw *hw)
{
	if (hw->mac.ops.check_mng_mode)
		return hw->mac.ops.check_mng_mode(hw);

	return false;
}

/**
 * e1000_mng_write_dhcp_info -将DHCP信息写入主机接口
 * @hw:指向HW结构的指针
 * @buffer:指向主机接口的指针
 * @length:缓冲区的大小
 *
 *将DHCP信息写入主机接口。
 **/
s32 e1000_mng_write_dhcp_info(struct e1000_hw *hw, u8 *buffer, u16 length)
{
	return e1000_mng_write_dhcp_info_generic(hw, buffer, length);
}

/**
 * e1000_reset_hw -复位硬件
 * @hw:指向HW结构的指针
 *
 *这将硬件重置为已知状态。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_reset_hw(struct e1000_hw *hw)
{
	if (hw->mac.ops.reset_hw)
		return hw->mac.ops.reset_hw(hw);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_init_hw -初始化硬件
 * @hw:指向HW结构的指针
 *
 *这是为操作做准备的硬件。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_init_hw(struct e1000_hw *hw)
{
	if (hw->mac.ops.init_hw)
		return hw->mac.ops.init_hw(hw);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_setup_link -配置链接和流控制
 * @hw:指向HW结构的指针
 *
 *配置适配器的链接和流控制设置。
 *这是一个由驱动程序调用的函数指针入口点。
 *虽然模块也可以调用这个函数，但是它们可能调用自己版本的函数。
 **/
s32 e1000_setup_link(struct e1000_hw *hw)
{
	if (hw->mac.ops.setup_link)
		return hw->mac.ops.setup_link(hw);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_get_speed_and_double -返回当前速度和双工
 * @hw:指向HW结构的指针
 * @speed:指向存储速度的16位值的指针
 * @duplex:指向存储双工的16位值的指针。
 *
 *这将返回传入的两个“out”变量中适配器的速度和双工。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_get_speed_and_duplex(struct e1000_hw *hw, u16 *speed, u16 *duplex)
{
	if (hw->mac.ops.get_link_up_info)
		return hw->mac.ops.get_link_up_info(hw, speed, duplex);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_setup_led -配置SW可控LED
 * @hw:指向HW结构的指针
 *
 *这将为使用SW可控LED做好准备，并保存LED的当前状态，以便以后恢复。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_setup_led(struct e1000_hw *hw)
{
	if (hw->mac.ops.setup_led)
		return hw->mac.ops.setup_led(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_cleanup_led -恢复SW可控LED
 * @hw:指向HW结构的指针
 *
 *这将恢复由e1000_setup_led保存的SW可控LED的值。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_cleanup_led(struct e1000_hw *hw)
{
	if (hw->mac.ops.cleanup_led)
		return hw->mac.ops.cleanup_led(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_blink_led -闪烁SW可控LED
 * @hw:指向HW结构的指针
 *
 *这将启动适配器LED闪烁。要求LED先setup后cleanup。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_blink_led(struct e1000_hw *hw)
{
	if (hw->mac.ops.blink_led)
		return hw->mac.ops.blink_led(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_id_led_init -在SW中存储LED配置
 * @hw:指向HW结构的指针
 *
 *在SW中初始化LED配置。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_id_led_init(struct e1000_hw *hw)
{
	if (hw->mac.ops.id_led_init)
		return hw->mac.ops.id_led_init(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_led_on -打开SW可控LED
 * @hw:指向HW结构的指针
 *
 *打开SW定义的LED。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_led_on(struct e1000_hw *hw)
{
	if (hw->mac.ops.led_on)
		return hw->mac.ops.led_on(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_led_off -关闭SW可控LED
 * @hw:指向HW结构的指针
 *
 *关闭SW定义的LED。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_led_off(struct e1000_hw *hw)
{
	if (hw->mac.ops.led_off)
		return hw->mac.ops.led_off(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_reset_adaptive -重置自适应IFS
 * @hw:指向HW结构的指针
 *
 *重置自适应IFS。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
void e1000_reset_adaptive(struct e1000_hw *hw)
{
	e1000_reset_adaptive_generic(hw);
}

/**
 * e1000_update_adaptive -更新自适应IFS
 * @hw:指向HW结构的指针
 *
 *更新自适应IFS。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
void e1000_update_adaptive(struct e1000_hw *hw)
{
	e1000_update_adaptive_generic(hw);
}

/**
 * e1000_disable_pcie_master -禁用PCI-Express主访问
 * @hw:指向HW结构的指针
 *
 *禁用PCI-Express主访问，并验证没有挂起的请求。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_disable_pcie_master(struct e1000_hw *hw)
{
	return e1000_disable_pcie_master_generic(hw);
}

/**
 * e1000_config_collision_dist -配置冲突距离
 * @hw:指向HW结构的指针
 *
 *将碰撞距离配置为默认值，用于链路设置。
 **/
void e1000_config_collision_dist(struct e1000_hw *hw)
{
	if (hw->mac.ops.config_collision_dist)
		hw->mac.ops.config_collision_dist(hw);
}

/**
 * e1000_rar_set -设置一个接收地址寄存器
 * @hw:指向HW结构的指针
 * @addr:将RAR设置为的地址
 * @index:要设置的RAR
 *
 *将接收地址寄存器(RAR)设置为指定地址。
 **/
int e1000_rar_set(struct e1000_hw *hw, u8 *addr, u32 index)
{
	if (hw->mac.ops.rar_set)
		return hw->mac.ops.rar_set(hw, addr, index);

	return E1000_SUCCESS;
}

/**
 * e1000_validate_mdi_set -确保有效的MDI/MDIX SW状态
 * @hw:指向HW结构的指针
 *
 *确保MDI/MDIX SW状态有效。
 **/
s32 e1000_validate_mdi_setting(struct e1000_hw *hw)
{
	if (hw->mac.ops.validate_mdi_setting)
		return hw->mac.ops.validate_mdi_setting(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_hash_mc_addr -确定多播表中的地址位置
 * @hw:指向HW结构的指针
 * @mc_addr:要散列的多播地址。
 *
 *这散列一个地址来确定它在多播表中的位置。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
u32 e1000_hash_mc_addr(struct e1000_hw *hw, u8 *mc_addr)
{
	return e1000_hash_mc_addr_generic(hw, mc_addr);
}

/**
 * e1000_enable_tx_pkt_filtering -在TX上启用数据包过滤
 * @hw:指向HW结构的指针
 *
 *在启用可管理性和主机接口的情况下，对传输数据包启用数据包过滤。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
bool e1000_enable_tx_pkt_filtering(struct e1000_hw *hw)
{
	return e1000_enable_tx_pkt_filtering_generic(hw);
}

/**
 * e1000_mng_host_if_write -写入可管理性主机接口
 * @hw:指向HW结构的指针
 * @buffer:指向主机接口缓冲区的指针
 * @length:缓冲区的大小
 * @offset:写入缓冲区中的位置
 * @sum:数据的和(非校验和)
 *
 *这个函数将缓冲区内容写入主机上给定的偏移量。
 *它还考虑了对齐问题，以便以最有效的方式进行写操作。
 *也在*buffer参数中填充缓冲区的和。
 **/
s32 e1000_mng_host_if_write(struct e1000_hw *hw, u8 *buffer, u16 length,
			    u16 offset, u8 *sum)
{
	return e1000_mng_host_if_write_generic(hw, buffer, length, offset, sum);
}

/**
 * e1000_mng_write_cmd_header -写可管理性命令头
 * @hw:指向HW结构的指针
 * @hdr:指向主机接口命令头的指针
 *
 *在执行校验和计算之后写入命令头。
 **/
s32 e1000_mng_write_cmd_header(struct e1000_hw *hw,
			       struct e1000_host_mng_command_header *hdr)
{
	return e1000_mng_write_cmd_header_generic(hw, hdr);
}

/**
 * e1000_mng_enable_host_if -检查主机接口是否启用
 * @hw:指向HW结构的指针
 *
 *成功返回E1000_success，否则返回E1000_ERR_HOST_INTERFACE_COMMAND
 *
 *此函数检查主机是否启用命令操作，并检查前一个命令是否完成。
 *它忙着等待，以防前面的命令没有完成。
 **/
s32 e1000_mng_enable_host_if(struct e1000_hw *hw)
{
	return e1000_mng_enable_host_if_generic(hw);
}

/**
 * e1000_check_reset_block -验证PHY是否可以重置
 * @hw:指向HW结构的指针
 *
 *检查PHY是否处于可以重置的状态，或者可管理性是否已将其绑定。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_check_reset_block(struct e1000_hw *hw)
{
	if (hw->phy.ops.check_reset_block)
		return hw->phy.ops.check_reset_block(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_read_phy_reg -读取PHY寄存器
 * @hw:指向HW结构的指针
 * @offset:要读取的寄存器
 * @data:存储16位读的缓冲区。
 *
 *读取PHY寄存器并返回数据中的值。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_read_phy_reg(struct e1000_hw *hw, u32 offset, u16 *data)
{
	if (hw->phy.ops.read_reg)
		return hw->phy.ops.read_reg(hw, offset, data);

	return E1000_SUCCESS;
}

/**
 * e1000_write_phy_reg -写入PHY寄存器
 * @hw:指向HW结构的指针
 * @offset:要写入的寄存器
 * @data:要写入的值。
 *
 *用数据中的值在偏移处写入PHY寄存器。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_write_phy_reg(struct e1000_hw *hw, u32 offset, u16 data)
{
	if (hw->phy.ops.write_reg)
		return hw->phy.ops.write_reg(hw, offset, data);

	return E1000_SUCCESS;
}

/**
 * e1000_release_phy -通用发布PHY
 * @hw:指向HW结构的指针
 *
 *如果访问PHY时silicon family不需要信号量，则返回。
 **/
void e1000_release_phy(struct e1000_hw *hw)
{
	if (hw->phy.ops.release)
		hw->phy.ops.release(hw);
}

/**
 * e1000_acquire_phy -通用获取PHY
 * @hw:指向HW结构的指针
 *
 *如果访问PHY时silicon family不需要信号量，返回success。
 **/
s32 e1000_acquire_phy(struct e1000_hw *hw)
{
	if (hw->phy.ops.acquire)
		return hw->phy.ops.acquire(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_read_kmrn_reg -使用Kumeran接口读取寄存器
 * @hw:指向HW结构的指针
 * @offset:要读取的寄存器
 * @data:存储读取的16位值的位置。
 *
 *从Kumeran接口读取寄存器。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_read_kmrn_reg(struct e1000_hw *hw, u32 offset, u16 *data)
{
	return e1000_read_kmrn_reg_generic(hw, offset, data);
}

/**
 * e1000_write_kmrn_reg—使用Kumeran接口写入寄存器
 * @hw:指向HW结构的指针
 * @offset:要写入的寄存器
 * @data:要写入的值。
 *
 *向Kumeran接口写入寄存器。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_write_kmrn_reg(struct e1000_hw *hw, u32 offset, u16 data)
{
	return e1000_write_kmrn_reg_generic(hw, offset, data);
}

/**
 * e1000_get_cable_length -检索电缆长度估计
 * @hw:指向HW结构的指针
 *
 *此函数估计电缆长度并存储在hw->phy中。min_length和hw->phy.max_length。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_get_cable_length(struct e1000_hw *hw)
{
	if (hw->phy.ops.get_cable_length)
		return hw->phy.ops.get_cable_length(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_get_phy_info -从寄存器中检索PHY信息
 * @hw:指向HW结构的指针
 *
 *这个函数从各个PHY寄存器获取一些信息，并用它填充hw->PHY值。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_get_phy_info(struct e1000_hw *hw)
{
	if (hw->phy.ops.get_info)
		return hw->phy.ops.get_info(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_phy_hw_reset -硬PHY复位
 * @hw:指向HW结构的指针
 *
 *执行硬物理复位。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_phy_hw_reset(struct e1000_hw *hw)
{
	if (hw->phy.ops.reset)
		return hw->phy.ops.reset(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_phy_commit -软PHY复位
 * @hw:指向HW结构的指针
 *
 *对应用程序执行软PHY重置。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_phy_commit(struct e1000_hw *hw)
{
	if (hw->phy.ops.commit)
		return hw->phy.ops.commit(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_set_d0_lplu_state -设置D0的低功耗连接状态
 * @hw:指向HW结构的指针
 * @active:用于启用/禁用lplu的布尔值
 *
 *成功返回0，失败返回1
 *
 *将低功耗链路(lplu)状态设置为功耗管理级别D0，
 *为活动状态时禁用SmartSpeed，否则清除lplu为D0，启用SmartSpeed。
 *LPLU和Smartspeed是互斥的。LPLU用于功率守恒最重要的Dx状态。
 *在驱动程序活动期间，应该启用SmartSpeed，以保持性能。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_set_d0_lplu_state(struct e1000_hw *hw, bool active)
{
	if (hw->phy.ops.set_d0_lplu_state)
		return hw->phy.ops.set_d0_lplu_state(hw, active);

	return E1000_SUCCESS;
}

/**
 * e1000_set_d3_lplu_state -设置D3的低功耗连接状态
 * @hw:指向HW结构的指针
 * @active:用于启用/禁用lplu的布尔值
 *
 *成功返回0，失败返回1
 *
 *将低功耗链路(lplu)状态设置为电源管理级别D3，
 *为活动状态时禁用SmartSpeed，否则清除lplu为D3，启用SmartSpeed。
 *LPLU和Smartspeed是互斥的。LPLU用于功率守恒最重要的Dx状态。
 *在驱动程序活动期间，应该启用SmartSpeed，以保持性能。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_set_d3_lplu_state(struct e1000_hw *hw, bool active)
{
	if (hw->phy.ops.set_d3_lplu_state)
		return hw->phy.ops.set_d3_lplu_state(hw, active);

	return E1000_SUCCESS;
}

/**
 * e1000_read_mac_addr -读取MAC地址
 * @hw:指向HW结构的指针
 *
 *从适配器中读取MAC地址并将其存储在HW结构中。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_read_mac_addr(struct e1000_hw *hw)
{
	if (hw->mac.ops.read_mac_addr)
		return hw->mac.ops.read_mac_addr(hw);

	return e1000_read_mac_addr_generic(hw);
}

/**
 * e1000_read_pba_string -读取设备部件编号字符串
 * @hw:指向HW结构的指针
 * @pba_num:指向设备部件号的指针
 * @pba_num_size:零件号缓冲区的大小
 *
 *从EEPROM中读取产品板部件(PBA)编号，并将其值存储在pba_num中。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_read_pba_string(struct e1000_hw *hw, u8 *pba_num, u32 pba_num_size)
{
	return e1000_read_pba_string_generic(hw, pba_num, pba_num_size);
}

/**
 * e1000_read_pba_length -读取设备部件编号字符串长度
 * @hw:指向HW结构的指针
 * @pba_num_size:零件号缓冲区的大小
 *
 *从EEPROM中读取产品板部件(PBA)的编号长度，并将其值存储在pba_num中。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_read_pba_length(struct e1000_hw *hw, u32 *pba_num_size)
{
	return e1000_read_pba_length_generic(hw, pba_num_size);
}

/**
 * e1000_validate_nvm_checksum -验证NVM(EEPROM)校验和
 * @hw:指向HW结构的指针
 *
 *验证NVM校验和是否正确。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_validate_nvm_checksum(struct e1000_hw *hw)
{
	if (hw->nvm.ops.validate)
		return hw->nvm.ops.validate(hw);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_update_nvm_checksum -更新NVM(EEPROM)校验和
 * @hw:指向HW结构的指针
 *
 *更新NVM校验和。
 *目前没有func指针存在，所有实现都在这个函数的泛型版本中处理。
 **/
s32 e1000_update_nvm_checksum(struct e1000_hw *hw)
{
	if (hw->nvm.ops.update)
		return hw->nvm.ops.update(hw);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_reload_nvm -重新加载EEPROM
 * @hw:指向HW结构的指针
 *
 *通过在扩展控制寄存器中设置“从EEPROM重新初始化”位来重新加载EEPROM。
 **/
void e1000_reload_nvm(struct e1000_hw *hw)
{
	if (hw->nvm.ops.reload)
		hw->nvm.ops.reload(hw);
}

/**
 * e1000_read_nvm -读取NVM(EEPROM)
 * @hw:指向HW结构的指针
 * @offset:要读取的单词offset
 * @words:需要读取的16位单词的数量
 * @data:指向正确大小的数据缓冲区的指针。
 *
 *从NVM(EEPROM)中读取16位数据块。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_read_nvm(struct e1000_hw *hw, u16 offset, u16 words, u16 *data)
{
	if (hw->nvm.ops.read)
		return hw->nvm.ops.read(hw, offset, words, data);

	return -E1000_ERR_CONFIG;
}

/**
 * e1000_write_nvm -写入NVM(EEPROM)
 * @hw:指向HW结构的指针
 * @offset:要读取的单词offset
 * @words:要写的16位单词的数量
 * @data:指向正确大小的数据缓冲区的指针。
 *
 *将16位数据块写入NVM(EEPROM)。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_write_nvm(struct e1000_hw *hw, u16 offset, u16 words, u16 *data)
{
	if (hw->nvm.ops.write)
		return hw->nvm.ops.write(hw, offset, words, data);

	return E1000_SUCCESS;
}

/**
 * e1000_write_8bit_ctrl_reg -写8位控制寄存器
 * @hw:指向HW结构的指针
 * @reg: 32位寄存器偏移量
 * @offset:要写入的寄存器
 * @data:要写入的值。
 *
 *用数据中的值在偏移处写入PHY寄存器。
 *这是一个由驱动程序调用的函数指针入口点。
 **/
s32 e1000_write_8bit_ctrl_reg(struct e1000_hw *hw, u32 reg, u32 offset,
			      u8 data)
{
	return e1000_write_8bit_ctrl_reg_generic(hw, reg, offset, data);
}

/**
 * e1000_power_up_phy -在PHY断电时恢复链接
 * @hw:指向HW结构的指针
 *
 * phy可能会被关闭以节省电力，当驱动程序卸载时关闭链接，或者局域网唤醒未被激活(等等)。
 **/
void e1000_power_up_phy(struct e1000_hw *hw)
{
	if (hw->phy.ops.power_up)
		hw->phy.ops.power_up(hw);

	e1000_setup_link(hw);
}

/**
 * e1000_power_down_phy -断电PHY
 * @hw:指向HW结构的指针
 *
 * phy可能会被关闭以节省电力，当驱动程序卸载时关闭链接，或者局域网唤醒未被激活(等等)。
 **/
void e1000_power_down_phy(struct e1000_hw *hw)
{
	if (hw->phy.ops.power_down)
		hw->phy.ops.power_down(hw);
}

/**
 * e1000_power_up_fiber_serdes_link -上电收发器链接
 * @hw:指向HW结构的指针
 *
 *上电光学元件和PCS。
 **/
void e1000_power_up_fiber_serdes_link(struct e1000_hw *hw)
{
	if (hw->mac.ops.power_up_serdes)
		hw->mac.ops.power_up_serdes(hw);
}

/**
 * e1000_shutdown_fiber_serdes_link -在断电期间删除链接
 * @hw:指向HW结构的指针
 *
 *在驱动程序卸载时关闭光学元件和PCS。
 **/
void e1000_shutdown_fiber_serdes_link(struct e1000_hw *hw)
{
	if (hw->mac.ops.shutdown_serdes)
		hw->mac.ops.shutdown_serdes(hw);
}

/**
 * e1000_get_thermal_sensor_data -采集热传感器数据
 * @hw:指向HW结构的指针
 *
 *更新mac.thermal_sensor_data中的温度
 **/
s32 e1000_get_thermal_sensor_data(struct e1000_hw *hw)
{
	if (hw->mac.ops.get_thermal_sensor_data)
		return hw->mac.ops.get_thermal_sensor_data(hw);

	return E1000_SUCCESS;
}

/**
 * e1000_init_thermal_sensor_thresh -设置热传感器阈值
 * @hw:指向HW结构的指针
 *
 *根据NVM映射设置热传感器阈值
 **/
s32 e1000_init_thermal_sensor_thresh(struct e1000_hw *hw)
{
	if (hw->mac.ops.init_thermal_sensor_thresh)
		return hw->mac.ops.init_thermal_sensor_thresh(hw);

	return E1000_SUCCESS;
}
