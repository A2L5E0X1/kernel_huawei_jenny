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

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "RnicTimerMgmt.h"
#include "RnicCtx.h"
#include "v_timer.h"
#include "RnicLog.h"
#include "mdrv.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_TIMERMGMT_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/

/*****************************************************************************
  3 ????????
*****************************************************************************/


VOS_VOID  RNIC_InitAllTimers(VOS_VOID)
{
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx = RNIC_GET_RNIC_TIMER_ADR();

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }
}


VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx = VOS_NULL_PTR;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;
    VOS_UINT32                          ulRet;

    pstRnicTimerCtx  = RNIC_GET_RNIC_TIMER_ADR();
    enTimerPrecision = VOS_TIMER_PRECISION_5;

    RNIC_NORMAL_LOG1(ACPU_PID_ADS_UL, "RNIC_StartTimer: enTimerId is ", enTimerId);

    /* ?????????????????????? */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        RNIC_ERROR_LOG1(ACPU_PID_ADS_UL, "RNIC_StartTimer: invalid enTimerId ", enTimerId);
        return;
    }

    /* ???????????????????????????????????????? */
    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        RNIC_WARNING_LOG1(ACPU_PID_ADS_UL, "RNIC_StartTimer: The timer is running ", enTimerId);
        return;
    }

    /* ???????????? */
    if (0 == ulLen)
    {
        RNIC_ERROR_LOG(ACPU_PID_ADS_UL, "RNIC_StartTimer:ulLen is 0 ");
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

     /* ????????????????????????????26M?????????????????? */
    if (TI_RNIC_DSFLOW_STATS == enTimerId)
    {
        enTimerPrecision = VOS_TIMER_NO_PRECISION;
    }

    /* VOS_StartRelTimer ?????????? */
    ulRet = VOS_StartRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer),
                              ACPU_PID_RNIC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              enTimerPrecision);
    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");
        return;
    }

    if (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId)
    {
        /* ???????????????? */
        RNIC_SET_IFACE_PERIOD_SEND_PKT(RNIC_DEV_ID_RMNET0, 0);
    }

    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_RUNING;

    /* ?????????????????? */

}



VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GET_RNIC_TIMER_ADR();

    /* ?????????????????????? */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* ???????????????????? */
    if (RNIC_TIMER_STATUS_RUNING  != pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* ????VOS??????: ????????????????????????????, ?????????????????????? */
    if (VOS_NULL_PTR != pstRnicTimerCtx[enTimerId].hTimer)
    {
        VOS_StopRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer));
    }

    pstRnicTimerCtx[enTimerId].hTimer        = VOS_NULL_PTR;
    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_STOP;

}



VOS_VOID  RNIC_StopAllTimer( VOS_VOID )
{

    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx   =  RNIC_GET_RNIC_TIMER_ADR();

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if (RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus)
        {
            /* ????VOS?????? */
            VOS_StopRelTimer(&(pstRnicTimerCtx[i].hTimer));

            pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
        }
    }

}



RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          ulLeftLen;

    pstRnicTimerCtx = RNIC_GET_RNIC_TIMER_ADR();
    ulLeftLen       = 0;

    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return RNIC_TIMER_STATUS_STOP;
    }

    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        if (VOS_OK != (VOS_GetRelTmRemainTime(&(pstRnicTimerCtx[enTimerId].hTimer), &ulLeftLen)))
        {
            RNIC_StopTimer(enTimerId);
            return RNIC_TIMER_STATUS_STOP;
        }
        else
        {
            return RNIC_TIMER_STATUS_RUNING;
        }
    }

    return RNIC_TIMER_STATUS_STOP;

}



