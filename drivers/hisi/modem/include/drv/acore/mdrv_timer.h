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

#ifndef __MDRV_ACORE_TIMER_H__
#define __MDRV_ACORE_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"

typedef enum {
    ACORE_SOFTTIMER_ID,         /* A core ????????timer id                lixiaojie */
    ACORE_WDT_TIMER_ID,         /* A CORE??????                           yangqiang */
    TIME_STAMP_ID,              /* P531????????A core C CORE M3??????,??fastboot???????? ??V7R2????BBP??????lixiaojie */
    ACORE_SOFTTIMER_NOWAKE_ID,  /* A core ??????????timer                 lixiaojie */
    ACORE_SYSTEM_TIMER_ID,      /* A CORE????????                        luting */
    ACORE_SOURCE_TIMER_ID,      /* A CORE ??????                        luting */
    TIMER_ACPU_CPUVIEW_ID,      /* A CORE CPU VIEW                      duxiaopeng */
    TIMER_ACPU_OSA_ID,          /* A CORE????????                        cuijunqiang */
    TIMER_ACPU_OM_TCXO_ID,      /* ????vos timer????????, xucheng    */
    TIMER_HIFI1_ID,
    TIMER_HIFI2_ID,
    TIMER_HRTIMER_ID,
    TIMER_ID_MAX
} DRV_TIMER_ID;

typedef enum {
    TIMER_ONCE_COUNT = 0,       /* ?????????????? */
    TIMER_PERIOD_COUNT,         /* ?????????????? */
    TIMER_FREERUN_COUNT,        /* ?????????????? */
    TIMER_COUNT_BUTT
} DRV_TIMER_MODE_E;

typedef enum {
    TIMER_UNIT_MS = 0,          /* 0????????ms???? */
    TIMER_UNIT_US,              /* 1????????us???? */
    TIMER_UNIT_NONE,            /* 2????????1????????????load??????????  */
    TIMER_UNIT_BUTT
} DRV_TIMER_UNIT_E;


void mdrv_timer_debug_register(unsigned int timer_id, FUNCPTR_1 routinue, int arg);


int mdrv_timer_start(unsigned int usrClkId, FUNCPTR_1 routine, int arg,
                     unsigned int timerValue, DRV_TIMER_MODE_E mode, DRV_TIMER_UNIT_E unitType);


int mdrv_timer_stop(unsigned int usrClkId);


int mdrv_timer_get_rest_time(unsigned int usrClkId, unsigned int unitType, unsigned int *pRestTime);

/*****************************************************************************
 * ????  : BSP_BBPGetCurTime
 * ????  : ????BBP????????????????OAM ????
 * ????  : void
 * ????  :
 *         pulLow32bitValue:    ??????????????????????????????????
 *         pulHigh32bitValue:   ?????????? ??????????32bit??????
 * ????  : int
 ******************************************************************************/
int mdrv_timer_get_accuracy_timestamp(unsigned int *pulHigh32bitValue, unsigned int *pulLow32bitValue);

/************************************************************************
 * FUNCTION: mdrv_timer_get_normal_timestamp
 * DESCRIPTION: GetSliceValue
 * INPUTS: NONE
 * OUTPUTS: NONE
 *   ????????????????????????????????
 **************************************************************************/
unsigned int mdrv_timer_get_normal_timestamp(void);

/************************************************************************
 * FUNCTION: mdrv_timer_get_hrt_timestamp
 * DESCRIPTION: GetHrtSliceValue
 * INPUTS: NONE
 * OUTPUTS: NONE
 *   ??????????????????????????????????0.5us????????????
 *   ??????????,??????????????????(lixiaojie\gebaizhang\xiajun????????)
 *************************************************************************/
unsigned int mdrv_timer_get_hrt_timestamp(void);

/************************************************************************
 * FUNCTION: mdrv_get_normal_timestamp_freq
 * DESCRIPTION: GetSliceFreq
 * INPUTS: NONE
 * OUTPUTS: NONE
 *   ????????????????
 *************************************************************************/
unsigned int mdrv_get_normal_timestamp_freq(void);

/************************************************************************
 * FUNCTION: mdrv_get_hrt_timestamp_freq
 * DESCRIPTION: GetHrtSliceFreq
 * INPUTS: NONE
 * OUTPUTS: NONE
 *   ????????????????????,??????????????????(lixiaojie\gebaizhang\xiajun????????)
 *************************************************************************/
unsigned int mdrv_get_hrt_timestamp_freq(void);

#ifdef __cplusplus
}
#endif

#endif
