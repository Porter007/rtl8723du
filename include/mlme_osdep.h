/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#ifndef	__MLME_OSDEP_H_
#define __MLME_OSDEP_H_


#if defined(PLATFORM_MPIXEL)
	extern int time_after(systime now, systime old);
#endif

extern void rtw_os_indicate_disconnect(_adapter *adapter, u16 reason, u8 locally_generated);
extern void rtw_os_indicate_connect(_adapter *adapter);
void rtw_os_indicate_scan_done(_adapter *padapter, bool aborted);
extern void rtw_report_sec_ie(_adapter *adapter, u8 authmode, u8 *sec_ie);

void rtw_reset_securitypriv(_adapter *adapter);

#endif /* _MLME_OSDEP_H_ */
