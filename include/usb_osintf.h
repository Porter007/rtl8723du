/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#ifndef __USB_OSINTF_H
#define __USB_OSINTF_H

#include <usb_vendor_req.h>

#define USBD_HALTED(Status) ((ULONG)(Status) >> 30 == 3)


u8 usbvendorrequest(struct dvobj_priv *pdvobjpriv, RT_USB_BREQUEST brequest, RT_USB_WVALUE wvalue, u8 windex, void *data, u8 datalen, u8 isdirectionin);


#endif
