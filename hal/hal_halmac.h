/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2015 - 2017 Realtek Corporation */

#ifndef _HAL_HALMAC_H_
#define _HAL_HALMAC_H_

#include <drv_types.h>		/* adapter_to_dvobj(), struct intf_hdl and etc. */
#include <hal_data.h>		/* struct hal_spec_t */
#include "halmac/halmac_api.h"	/* PHALMAC_ADAPTER and etc. */

/* HALMAC Definition for Driver */
#define RTW_HALMAC_H2C_MAX_SIZE		8
#define RTW_HALMAC_BA_SSN_RPT_SIZE	4

#define dvobj_set_halmac(d, mac)	((d)->halmac = (mac))
#define dvobj_to_halmac(d)		((PHALMAC_ADAPTER)((d)->halmac))
#define adapter_to_halmac(p)		dvobj_to_halmac(adapter_to_dvobj(p))

/* for H2C cmd */
#define MAX_H2C_BOX_NUMS 4
#define MESSAGE_BOX_SIZE 4
#define EX_MESSAGE_BOX_SIZE 4

typedef enum _RTW_HALMAC_MODE {
	RTW_HALMAC_MODE_NORMAL,
	RTW_HALMAC_MODE_WIFI_TEST,
} RTW_HALMAC_MODE;

union rtw_phy_para_data {
	struct _mac {
		u32	value;
		u32	msk;
		u16	offset;
		u8	msk_en;	/* Enable bit mask(msk) or not */
		u8	size;	/* Unit is bytes, and value should be 1/2/4 */
	} mac;
	struct _bb {
		u32	value;
		u32	msk;
		u16	offset;
		u8	msk_en;
		u8	size;
	} bb;
	struct _rf {
		u32	value;
		u32	msk;
		u8	offset;
		u8	msk_en;
		/*
		 * 0: path A
		 * 1: path B
		 * 2: path C
		 * 3: path D
		 */
		u8	path;
	} rf;
	struct _delay {
		/*
		 * 0: microsecond (us)
		 * 1: millisecond (ms)
		 */
		u8	unit;
		u16	value;
	} delay;
};

struct rtw_phy_parameter {
	/*
	 * 0: MAC register
	 * 1: BB register
	 * 2: RF register
	 * 3: Delay
	 * 0xFF: Latest(End) command
	 */
	u8 cmd;
	union rtw_phy_para_data data;
};

struct rtw_halmac_bcn_ctrl {
	u8 rx_bssid_fit:1;	/* 0:HW handle beacon, 1:ignore */
	u8 txbcn_rpt:1;		/* Enable TXBCN report in ad hoc and AP mode */
	u8 tsf_update:1;	/* Update TSF when beacon or probe response */
	u8 enable_bcn:1;	/* Enable beacon related functions */
	u8 rxbcn_rpt:1;		/* Enable RXBCNOK report */
	u8 p2p_ctwin:1;		/* Enable P2P CTN WINDOWS function */
	u8 p2p_bcn_area:1;	/* Enable P2P BCN area on function */
};

extern HALMAC_PLATFORM_API rtw_halmac_platform_api;

/* HALMAC API for Driver(HAL) */
u8 rtw_halmac_read8(struct intf_hdl *, u32 addr);
u16 rtw_halmac_read16(struct intf_hdl *, u32 addr);
u32 rtw_halmac_read32(struct intf_hdl *, u32 addr);
void rtw_halmac_read_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *pmem);
int rtw_halmac_write8(struct intf_hdl *, u32 addr, u8 value);
int rtw_halmac_write16(struct intf_hdl *, u32 addr, u16 value);
int rtw_halmac_write32(struct intf_hdl *, u32 addr, u32 value);

/* Software Information */
void rtw_halmac_get_version(char *str, u32 len);

/* Software Initialization */
int rtw_halmac_init_adapter(struct dvobj_priv *, PHALMAC_PLATFORM_API);
int rtw_halmac_deinit_adapter(struct dvobj_priv *);

/* Get operations */
int rtw_halmac_get_hw_value(struct dvobj_priv *, HALMAC_HW_ID hw_id, VOID *pvalue);
int rtw_halmac_get_tx_fifo_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_rx_fifo_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_rsvd_drv_pg_bndy(struct dvobj_priv *d, u16 *bndy);
int rtw_halmac_get_page_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_tx_agg_align_size(struct dvobj_priv *d, u16 *size);
int rtw_halmac_get_rx_agg_align_size(struct dvobj_priv *d, u8 *size);
int rtw_halmac_get_rx_drv_info_sz(struct dvobj_priv *, u8 *sz);
int rtw_halmac_get_tx_desc_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_rx_desc_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_ori_h2c_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_oqt_size(struct dvobj_priv *d, u8 *size);
int rtw_halmac_get_ac_queue_number(struct dvobj_priv *d, u8 *num);
int rtw_halmac_get_mac_address(struct dvobj_priv *d, enum _hw_port hwport, u8 *addr);
int rtw_halmac_get_network_type(struct dvobj_priv *d, enum _hw_port hwport, u8 *type);
int rtw_halmac_get_bcn_ctrl(struct dvobj_priv *d, enum _hw_port hwport, struct rtw_halmac_bcn_ctrl *bcn_ctrl);
/*int rtw_halmac_get_wow_reason(struct dvobj_priv *, u8 *reason);*/

/* Set operations */
int rtw_halmac_config_rx_info(struct dvobj_priv *, HALMAC_DRV_INFO);
int rtw_halmac_set_max_dl_fw_size(struct dvobj_priv *d, u32 size);
int rtw_halmac_set_mac_address(struct dvobj_priv *d, enum _hw_port hwport, u8 *addr);
int rtw_halmac_set_bssid(struct dvobj_priv *d, enum _hw_port hwport, u8 *addr);
int rtw_halmac_set_tx_address(struct dvobj_priv *d, enum _hw_port hwport, u8 *addr);
int rtw_halmac_set_network_type(struct dvobj_priv *d, enum _hw_port hwport, u8 type);
int rtw_halmac_reset_tsf(struct dvobj_priv *d, enum _hw_port hwport);
int rtw_halmac_set_bcn_interval(struct dvobj_priv *d, enum _hw_port hwport, u32 space);
int rtw_halmac_set_bcn_ctrl(struct dvobj_priv *d, enum _hw_port hwport, struct rtw_halmac_bcn_ctrl *bcn_ctrl);
int rtw_halmac_set_aid(struct dvobj_priv *d, enum _hw_port hwport, u16 aid);
int rtw_halmac_set_bandwidth(struct dvobj_priv *d, u8 channel, u8 pri_ch_idx, u8 bw);
int rtw_halmac_set_edca(struct dvobj_priv *d, u8 queue, u8 aifs, u8 cw, u16 txop);

/* Functions */
int rtw_halmac_poweron(struct dvobj_priv *);
int rtw_halmac_poweroff(struct dvobj_priv *);
int rtw_halmac_init_hal(struct dvobj_priv *);
int rtw_halmac_init_hal_fw(struct dvobj_priv *, u8 *fw, u32 fwsize);
int rtw_halmac_init_hal_fw_file(struct dvobj_priv *, u8 *fwpath);
int rtw_halmac_deinit_hal(struct dvobj_priv *);
int rtw_halmac_self_verify(struct dvobj_priv *);
int rtw_halmac_txfifo_wait_empty(struct dvobj_priv *d, u32 timeout);
int rtw_halmac_dlfw(struct dvobj_priv *, u8 *fw, u32 fwsize);
int rtw_halmac_dlfw_from_file(struct dvobj_priv *, u8 *fwpath);
int rtw_halmac_dlfw_mem(struct dvobj_priv *d, u8 *fw, u32 fwsize, enum fw_mem mem);
int rtw_halmac_dlfw_mem_from_file(struct dvobj_priv *d, u8 *fwpath, enum fw_mem mem);
int rtw_halmac_phy_power_switch(struct dvobj_priv *, u8 enable);
int rtw_halmac_send_h2c(struct dvobj_priv *, u8 *h2c);
int rtw_halmac_c2h_handle(struct dvobj_priv *, u8 *c2h, u32 size);

/* eFuse */
int rtw_halmac_get_available_efuse_size(struct dvobj_priv *d, u32 *size);
int rtw_halmac_get_physical_efuse_size(struct dvobj_priv *, u32 *size);
int rtw_halmac_read_physical_efuse_map(struct dvobj_priv *, u8 *map, u32 size);
int rtw_halmac_read_physical_efuse(struct dvobj_priv *, u32 offset, u32 cnt, u8 *data);
int rtw_halmac_write_physical_efuse(struct dvobj_priv *, u32 offset, u32 cnt, u8 *data);
int rtw_halmac_get_logical_efuse_size(struct dvobj_priv *, u32 *size);
int rtw_halmac_read_logical_efuse_map(struct dvobj_priv *, u8 *map, u32 size, u8 *maskmap, u32 masksize);
int rtw_halmac_write_logical_efuse_map(struct dvobj_priv *, u8 *map, u32 size, u8 *maskmap, u32 masksize);
int rtw_halmac_read_logical_efuse(struct dvobj_priv *, u32 offset, u32 cnt, u8 *data);
int rtw_halmac_write_logical_efuse(struct dvobj_priv *, u32 offset, u32 cnt, u8 *data);

int rtw_halmac_write_bt_physical_efuse(struct dvobj_priv *, u32 offset, u32 cnt, u8 *data);
int rtw_halmac_read_bt_physical_efuse_map(struct dvobj_priv *, u8 *map, u32 size);

int rtw_halmac_dump_fifo(struct dvobj_priv *d, u8 fifo_sel, u32 addr, u32 size, u8 *buffer);
int rtw_halmac_rx_agg_switch(struct dvobj_priv *, u8 enable);

/* Specific function APIs*/
int rtw_halmac_download_rsvd_page(struct dvobj_priv *dvobj, u8 pg_offset, u8 *pbuf, u32 size);
int rtw_halmac_fill_hal_spec(struct dvobj_priv *, struct hal_spec_t *);
int rtw_halmac_p2pps(struct dvobj_priv *dvobj, PHAL_P2P_PS_PARA pp2p_ps_para);
int rtw_halmac_iqk(struct dvobj_priv *d, u8 clear, u8 segment);
int rtw_halmac_cfg_phy_para(struct dvobj_priv *d, struct rtw_phy_parameter *para);

u8 rtw_halmac_usb_get_bulkout_id(struct dvobj_priv *, u8 *buf, u32 size);
int rtw_halmac_usb_get_txagg_desc_num(struct dvobj_priv *d, u8 *num);
u8 rtw_halmac_switch_usb_mode(struct dvobj_priv *d, enum RTW_USB_SPEED usb_mode);

#ifdef CONFIG_SUPPORT_TRX_SHARED
void dump_trx_share_mode(void *sel, _adapter *adapter);
#endif
#endif /* _HAL_HALMAC_H_ */
