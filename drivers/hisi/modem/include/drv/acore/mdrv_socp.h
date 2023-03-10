/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __MDRV_ACORE_SOCP_H__
#define __MDRV_ACORE_SOCP_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_socp_common.h"
/*****************************************************************************
* ?? ?? ??  : mdrv_socp_compress_enable
* ????????  :??????????????deflate????
* ????????  : u32DestChanID:????????ID??
* ????????  : ??
* ?? ?? ??  : SOCP_OK:????deflate????????
 SOCP_ERROR :????deflate????????
*****************************************************************************/
int mdrv_socp_compress_enable(unsigned int u32DestChanID);
/*****************************************************************************
* ?? ?? ??  : mdrv_socp_compress_unable
* ????????  :??????????????deflate????
* ????????  : u32DestChanID:????????ID??
* ????????  : ??
* ?? ?? ??  : SOCP_OK:????deflate????????
 SOCP_ERROR :????deflate????????
*****************************************************************************/
int mdrv_socp_compress_disable(unsigned int u32DestChanID);

/*****************************************************************************
* ?? ?? ??  : mdrv_deflate_set_ind_mode
* ????????  :??????????????deflate????????
* ????????  : u32SrcChanID:??????ID??
* ????????  : ??
* ?? ?? ??  : ??
*****************************************************************************/

int mdrv_deflate_set_ind_mode(SOCP_IND_MODE_ENUM eMode);
/*****************************************************************************
* ?? ?? ??  : mdrv_socp_compress_status
*
* ????????  : ????????????????
*
* ????????  : ????????
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
int mdrv_socp_compress_status(void);

/*****************************************************************************
* ?? ?? ??  : mdrv_deflate_get_log_ind_mode
*
* ????????  : ????????????????
*
* ????????  : ????????
*
* ????????  : ??
*
* ?? ?? ??  : SOCP_OK:????deflate????????
     SOCP_ERROR:????deflate????????
*****************************************************************************/
int mdrv_deflate_get_log_ind_mode(unsigned int *eMode);

/*****************************************************************************
* ?? ?? ??  : mdrv_socp_get_log_ind_mode
*
* ????????  : ????????????????
*
* ????????  : ????????
*
* ????????  : ??
*
* ?? ?? ??  : ??
*****************************************************************************/
int mdrv_socp_get_log_ind_mode(unsigned int *eMode);



/*****************************************************************************
* ?? ?? ??  : mdrv_socp_bbpmemenable
*
* ????????  : bbp????????????????
*
* ????????  : ????????
*
* ????????  : ??
*
* ?? ?? ??  :
*****************************************************************************/
int mdrv_socp_bbpmemenable(void);

void mdrv_SocpEncDstQueryIntInfo(unsigned int *TrfInfo, unsigned int *ThrOvfInfo);

void mdrv_clear_socp_encdst_int_info(void);



#ifdef __cplusplus
}
#endif
#endif
