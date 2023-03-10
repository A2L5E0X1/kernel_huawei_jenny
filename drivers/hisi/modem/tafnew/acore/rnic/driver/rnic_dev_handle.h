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

#ifndef __RNIC_DEV_HANDLE_H__
#define __RNIC_DEV_HANDLE_H__

/*****************************************************************************
  1. Other file included
*****************************************************************************/

#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include "rnic_dev_i.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  2. Macro definitions
*****************************************************************************/


/*****************************************************************************
  3. Enumerations declatations
*****************************************************************************/


/*****************************************************************************
  4. STRUCT and UNION declatations
*****************************************************************************/


/*******************************************************************************
  5. Function declarations
*******************************************************************************/

#if (defined(CONFIG_BALONG_SPE))
void rnic_spe_start_xmit(int port, struct sk_buff *skb);
#endif /* CONFIG_BALONG_SPE */

int rnic_napi_poll(struct napi_struct *napi, int budget);

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM_MBB))
int rnic_peth_ep_init(void);
#endif /* CONFIG_HISI_BALONG_EXTRA_MODEM_MBB */

#if (defined(CONFIG_HISI_BALONG_EXTRA_MODEM))
void rnic_tput_timer_start(struct rnic_dev_priv_s *priv);
void rnic_tput_timer_stop(struct rnic_dev_priv_s *priv);
void rnic_tput_timer_expire(unsigned long data);
int rnic_peth_rc_start_xmit(struct sk_buff *skb, uint8_t devid);
int rnic_peth_rc_init(void);
#endif /* CONFIG_HISI_BALONG_EXTRA_MODEM */

netdev_tx_t rnic_tx_hanlde(struct sk_buff *skb,
					struct rnic_dev_priv_s *priv);
void rnic_napi_dispatcher_cb(struct work_struct * work);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __RNIC_DEV_HANDLE_H__ */
