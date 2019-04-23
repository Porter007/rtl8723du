/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#ifndef	__PHYDM_FEATURES_H__
#define __PHYDM_FEATURES

#define ODM_DC_CANCELLATION_SUPPORT		(ODM_RTL8188F | ODM_RTL8710B)
#define ODM_RECEIVER_BLOCKING_SUPPORT	(ODM_RTL8188E | ODM_RTL8192E)

#define PHYDM_LA_MODE_SUPPORT			0

/*20170103 YuChen add for FW API*/
#define PHYDM_FW_API_ENABLE_8822B			1
#define PHYDM_FW_API_FUNC_ENABLE_8822B		1
#define PHYDM_FW_API_ENABLE_8821C			1
#define PHYDM_FW_API_FUNC_ENABLE_8821C		1

#include	"phydm_features_ce.h"

#endif
