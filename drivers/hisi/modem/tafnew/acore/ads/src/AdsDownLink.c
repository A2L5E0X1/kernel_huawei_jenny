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
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "mdrv.h"
#include "AcpuReset.h"
#include "AdsFilter.h"
#include "AdsDhcpInterface.h"
#include "AdsMntn.h"
#include "ads_mip_pif.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DOWNLINK_C


/*****************************************************************************
  2 ????????????
*****************************************************************************/
VOS_UINT32                              g_ulAdsDlDiscardPktFlag  = VOS_FALSE;   /* ADS???????????????? */

/*****************************************************************************
  3 ????????
*****************************************************************************/


VOS_INT ADS_DL_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             lUserData
)
{
    ADS_CCPU_RESET_IND_STRU                *pstMsg = VOS_NULL_PTR;

    /* ??????0?????????????? */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        ADS_TRACE_HIGH("before reset enter.\n");

        /* ???????? */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("before reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* ?????????? */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /* ?????? */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_TRACE_HIGH("before reset: send msg failed.\n");
            return VOS_ERROR;
        }

        /* ???????????????????????????????????????????????????????? */
        if (VOS_OK != VOS_SmP(ADS_GetDLResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_TRACE_HIGH("before reset VOS_SmP failed.\n");
            ADS_DBG_DL_RESET_LOCK_FAIL_NUM(1);
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("before reset succ.\n");
        return VOS_OK;
    }
    /* ?????? */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        ADS_TRACE_HIGH("after reset enter.\n");

        /* ???????? */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("after reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* ?????????? */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_END_IND;

        /* ?????? */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_TRACE_HIGH("after reset: send msg failed.\n");
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("after reset: succ.\n");
        ADS_DBG_DL_RESET_SUCC_NUM(1);
        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}


VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID)
{
    if (ADS_IPF_MODE_INT == ADS_GET_IPF_MODE())
    {
        ADS_DL_WakeLock();
        ADS_DL_ProcIpfResult();
        ADS_DL_WakeUnLock();
    }
    else
    {
        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
    }
    ADS_DBG_DL_RCV_IPF_RD_INT_NUM(1);

    return VOS_OK;
}


VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty)
{
    if (IPF_EMPTY_ADQ0 == eAdqEmpty)
    {
        ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(1);
    }
    else if (IPF_EMPTY_ADQ1 == eAdqEmpty)
    {
        ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(1);
    }
    else
    {
        ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(1);
        ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(1);
    }

    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_RCV_IPF_ADQ_EMPTY_INT_NUM(1);
    return VOS_OK;
}


VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* ????????ADQ?????????????? */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_ADQ_EMPTY_TMR_TIMEOUT_NUM(1);
    return;
}


VOS_VOID ADS_DL_RcvTiCcoreResetDelayExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    ADS_DL_RcvCcpuResetStartInd();
    return;
}


VOS_UINT32 ADS_DL_ConfigAdq(
    IPF_AD_TYPE_E                       enAdType,
    VOS_UINT                            ulIpfAdNum
)
{
    IPF_AD_DESC_S                      *pstAdDesc   = VOS_NULL_PTR;
    ADS_IPF_AD_RECORD_STRU             *pstAdRecord = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
    VOS_UINT32                          ulPoolId;
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulSlice;
    VOS_INT32                           lRslt;

    ulSlice = VOS_GetSlice();

    if (IPF_AD_0 == enAdType)
    {
        ulPoolId = ADS_IPF_MEM_POOL_ID_AD0;
        ulLen    = ADS_IPF_AD0_MEM_BLK_SIZE;
    }
    else
    {
        ulPoolId = ADS_IPF_MEM_POOL_ID_AD1;
        ulLen    = ADS_IPF_AD1_MEM_BLK_SIZE;
    }

    for (ulCnt = 0; ulCnt < ulIpfAdNum; ulCnt++)
    {
        pstImmZc = ADS_IPF_AllocMem(ulPoolId, ulLen, IMM_MAC_HEADER_RES_LEN);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_ADQ_ALLOC_MEM_FAIL_NUM(1);
            break;
        }

        ADS_DBG_DL_ADQ_ALLOC_MEM_SUCC_NUM(1);

        /* ????AD??????: OUTPUT0 ---> ????????; OUTPUT1 ---> SKBUFF */
        pstAdDesc = ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, ulCnt);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0))
#ifndef CONFIG_NEW_PLATFORM
        pstAdDesc->u32OutPtr0 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc->data);
        pstAdDesc->u32OutPtr1 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc);
#else
        pstAdDesc->OutPtr0 = (modem_phy_addr)(VOS_UINT_PTR)virt_to_phys((VOS_VOID *)pstImmZc->data);
        pstAdDesc->OutPtr1 = (modem_phy_addr)(VOS_UINT_PTR)virt_to_phys((VOS_VOID *)pstImmZc);
#endif
#else
#ifndef CONFIG_NEW_PLATFORM
        pstAdDesc->u32OutPtr0 = (VOS_UINT32)ADS_IPF_GetMemDma(pstImmZc);
        pstAdDesc->u32OutPtr1 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc);
#else
        pstAdDesc->OutPtr0 = (modem_phy_addr)ADS_IPF_GetMemDma(pstImmZc);
        pstAdDesc->OutPtr1 = (modem_phy_addr)(VOS_UINT_PTR)virt_to_phys((VOS_VOID *)pstImmZc);
#endif
#endif/* (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0) */

        /* ?????????????? */
        if (enAdType < IPF_AD_MAX)
        {
            pstAdRecord = ADS_DL_GET_IPF_AD_RECORD_PTR(enAdType);

            if (pstAdRecord->ulPos >= ADS_IPF_AD_BUFF_RECORD_NUM)
            {
                pstAdRecord->ulPos = 0;
            }

            pstAdRecord->astAdBuff[pstAdRecord->ulPos].ulSlice      = ulSlice;
#ifndef CONFIG_NEW_PLATFORM
            pstAdRecord->astAdBuff[pstAdRecord->ulPos].ulPhyAddr    = pstAdDesc->u32OutPtr1;
#else
            pstAdRecord->astAdBuff[pstAdRecord->ulPos].pulPhyAddr   = (VOS_VOID *)pstAdDesc->OutPtr1;
#endif
            pstAdRecord->astAdBuff[pstAdRecord->ulPos].pstImmZc     = pstImmZc;
            pstAdRecord->ulPos++;
        }
    }

    if (0 == ulCnt)
    {
        return 0;
    }

    /* ??????AD??????????ADQ */
    lRslt = mdrv_ipf_config_dlad(enAdType, ulCnt, ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, 0));
    if (IPF_SUCCESS != lRslt)
    {
        /* ?????????????????? */
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt++)
        {
            pstAdDesc = ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, ulCnt);
#ifndef CONFIG_NEW_PLATFORM
            pstImmZc  = (IMM_ZC_STRU *)phys_to_virt((unsigned long)pstAdDesc->u32OutPtr1);
#else
            pstImmZc  = (IMM_ZC_STRU *)phys_to_virt((VOS_UINT_PTR)pstAdDesc->OutPtr1); //lint !e661
#endif
            IMM_ZcFreeAny(pstImmZc);
            ADS_DBG_DL_ADQ_FREE_MEM_NUM(1);
        }

        ADS_DBG_DL_ADQ_CFG_IPF_FAIL_NUM(1);
        return 0;
    }

    /* ??????????????AD???? */
    ADS_DBG_DL_ADQ_CFG_AD_NUM(ulCnt);
    ADS_DBG_DL_ADQ_CFG_IPF_SUCC_NUM(1);
    return ulCnt;
}


VOS_VOID ADS_DL_AllocMemForAdq(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT32                          ulIpfAd0Num;
    VOS_UINT32                          ulIpfAd1Num;
    VOS_UINT32                          ulActAd0Num;
    VOS_UINT32                          ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* ????????ADQ????????AD???? */
    lRslt = mdrv_ipf_get_dlad_num(&ulIpfAd0Num, &ulIpfAd1Num);
    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_ADQ_GET_FREE_AD_FAIL_NUM(1);
        return;
    }

    ADS_DBG_DL_ADQ_GET_FREE_AD_SUCC_NUM(1);

    /* ????????????????ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ulActAd1Num = ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num);
        ADS_DBG_DL_ADQ_CFG_AD1_NUM(ulActAd1Num);
    }

    /* ??????????????ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ulActAd0Num = ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num);
        ADS_DBG_DL_ADQ_CFG_AD0_NUM(ulActAd0Num);
    }

    /* AD0????????AD1?????????????????????? */
    if ( ((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
      || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)) )
    {
        /* ????????ADQ?????????????????????????????????? */
        ADS_StartTimer(TI_ADS_DL_ADQ_EMPTY, TI_ADS_DL_ADQ_EMPTY_LEN);
    }

    return;
}


VOS_VOID ADS_DL_SendNdClientDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_NDCLIENT_DATA_IND_STRU         *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* ???????? */
    pstMsg = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2);
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstMsg is NULL!");
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2 - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /* ???????????? */
    pstMsg->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstMsg->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);
    pstMsg->usLen         = (VOS_UINT16)ulDataLen;

    /* ???????????? */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    TAF_MEM_CPY_S(pstMsg->aucData, ulDataLen, pucData, ulDataLen);

    /* ???????? */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);
    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}


VOS_VOID ADS_DL_SendDhcpClientDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_DHCP_DATA_IND_STRU             *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* ???????? */
    pstMsg = (ADS_DHCP_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen);

    /* ?????????????????? */
    if( VOS_NULL_PTR == pstMsg )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpClientDataInd: pstMsg is NULL!");
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen - VOS_MSG_HEAD_LENGTH));

    /* ???????????? */
    pstMsg->ulReceiverPid = UEPS_PID_DHCP;
    pstMsg->enMsgId       = ID_ADS_DHCP_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);
    pstMsg->ulLen         = ulDataLen;

    /* ???????? */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    TAF_MEM_CPY_S(pstMsg->aucData, ulDataLen, pucData, ulDataLen);

    /* ????VOS???????? */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);
    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpClientDataInd: Send msg fail!");
    }

    return;
}


VOS_VOID ADS_DL_SendMipDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_MIP_DATA_IND_STRU              *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* ???????? */
    pstMsg = (ADS_MIP_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_MIP_DATA_IND_STRU) + ulDataLen - 4);

    /* ?????????????????? */
    if( VOS_NULL_PTR == pstMsg )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendMipDataInd: pstMsg is NULL!");
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(ADS_MIP_DATA_IND_STRU) + ulDataLen - 4 - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_MIP_DATA_IND_STRU) + ulDataLen - 4 - VOS_MSG_HEAD_LENGTH));

    /* ???????????? */
    pstMsg->ulReceiverPid = MSPS_PID_MIP;
    pstMsg->enMsgId       = ID_ADS_MIP_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);
    pstMsg->usLen         = (VOS_UINT16)ulDataLen;

    /* ???????? */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    TAF_MEM_CPY_S(pstMsg->aucData, ulDataLen, pucData, ulDataLen);

    /* ????VOS???????? */
    (VOS_VOID)PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);

    return;
}


VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    IPF_AD_DESC_S                      *pstAdDesc = VOS_NULL_PTR;

    ulAdNum = 0;

    pstAdDesc = (IPF_AD_DESC_S*)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                             sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE);

    if ( VOS_NULL_PTR == pstAdDesc )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FreeIpfUsedAd0: pstAdDesc is null");
        return;
    }

    TAF_MEM_SET_S(pstAdDesc, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE), 0x00, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE));

    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_0, (VOS_UINT32 *)&ulAdNum, pstAdDesc))
    {
        /* ????ADQ0?????? */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
#ifndef CONFIG_NEW_PLATFORM
            IMM_ZcFreeAny((IMM_ZC_STRU *)phys_to_virt((unsigned long)pstAdDesc[i].u32OutPtr1));
#else
            IMM_ZcFreeAny((IMM_ZC_STRU *)phys_to_virt((VOS_UINT_PTR)pstAdDesc[i].OutPtr1));
#endif
        }
    }
    else
    {
        ADS_DBG_DL_ADQ_GET_IPF_AD0_FAIL_NUM(1);
    }

    ADS_DBG_DL_ADQ_FREE_AD0_NUM(PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE));

    PS_MEM_FREE(ACPU_PID_ADS_DL, pstAdDesc);

    return;
}


VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    IPF_AD_DESC_S                      *pstAdDesc = VOS_NULL_PTR;

    ulAdNum = 0;

    pstAdDesc = (IPF_AD_DESC_S*)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                             sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE);

    if ( VOS_NULL_PTR == pstAdDesc )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FreeIpfUsedAd1: pstAdDesc is null");
        return;
    }

    TAF_MEM_SET_S(pstAdDesc, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE), 0x00, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE));

    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_1, (VOS_UINT32 *)&ulAdNum, pstAdDesc))
    {
        /* ????ADQ1?????? */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD1_DESC_SIZE); i++)
        {
#ifndef CONFIG_NEW_PLATFORM
            IMM_ZcFreeAny((IMM_ZC_STRU *)phys_to_virt((unsigned long)pstAdDesc[i].u32OutPtr1));
#else
            IMM_ZcFreeAny((IMM_ZC_STRU *)phys_to_virt((VOS_UINT_PTR)pstAdDesc[i].OutPtr1));
#endif
        }
    }
    else
    {
        ADS_DBG_DL_ADQ_GET_IPF_AD1_FAIL_NUM(1);
    }

    ADS_DBG_DL_ADQ_FREE_AD1_NUM(PS_MIN(ulAdNum, IPF_DLAD1_DESC_SIZE));

    PS_MEM_FREE(ACPU_PID_ADS_DL, pstAdDesc);

    return;
}


VOS_VOID ADS_DL_SndCdsErrorInd(
    VOS_UINT16                          usModemId,
    VOS_UINT32                          ulRabId
)
{
    ADS_CDS_ERR_IND_STRU               *pstMsg = VOS_NULL_PTR;

    /* ????OSA???? */
    pstMsg = (ADS_CDS_ERR_IND_STRU *)ADS_DL_ALLOC_MSG_WITH_HDR(
                                            sizeof(ADS_CDS_ERR_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SndCdsErrorInd: Alloc MSG failed.\n");\
        return;
    }

    /* ???????????? */
    TAF_MEM_SET_S(ADS_DL_GET_MSG_ENTITY(pstMsg), ADS_DL_GET_MSG_LENGTH(pstMsg),
                  0x00, ADS_DL_GET_MSG_LENGTH(pstMsg));

    /* ?????????? */
    ADS_DL_CFG_CDS_MSG_HDR(pstMsg, ID_ADS_CDS_ERR_IND);

    /* ???????????? */
    pstMsg->enModemId = usModemId;
    pstMsg->ucRabId   = (VOS_UINT8)ulRabId;

    /* ???????? */
    ADS_DL_SEND_MSG(pstMsg);
    return;
}


VOS_VOID ADS_DL_SndIntraPacketErrorInd(
    VOS_UINT32                          ulInstance,
    VOS_UINT16                          usBearerMask
)
{
    ADS_PACKET_ERROR_IND_STRU          *pstMsg = VOS_NULL_PTR;

    /* ????OSA???? */
    pstMsg = (ADS_PACKET_ERROR_IND_STRU *)ADS_DL_ALLOC_MSG_WITH_HDR(
                                            sizeof(ADS_PACKET_ERROR_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL,
            "ADS_DL_SndIntraPacketErrorInd: Alloc MSG failed.\n");
        return;
    }

    /* ?????????? */
    ADS_DL_CFG_INTRA_MSG_HDR(pstMsg, ID_ADS_PACKET_ERROR_IND);

    /* ???????????? */
    pstMsg->usModemId    = (VOS_UINT16)ulInstance;
    pstMsg->usBearerMask = usBearerMask;

    /* ???????? */
    ADS_DL_SEND_MSG(pstMsg);
    return;
}


VOS_VOID ADS_DL_RecordPacketErrorStats(IMM_ZC_STRU *pstImmZc)
{
    ADS_PACKET_ERROR_FEEDBACK_CFG_STRU *pstFeedbackCfg = VOS_NULL_PTR;
    ADS_BEARER_PACKET_ERROR_STATS_STRU *pstPktErrStats = VOS_NULL_PTR;
    ADS_DL_IMM_PRIV_CB_STRU            *pstImmPriv     = VOS_NULL_PTR;

    pstFeedbackCfg = ADS_DL_GET_PKT_ERR_FEEDBACK_CFG_PTR();
    if (VOS_FALSE == pstFeedbackCfg->ulEnabled)
    {
        return;
    }

    pstImmPriv = ADS_DL_IMM_PRIV_CB(pstImmZc);
    if (ADS_CDS_IPF_PKT_TYPE_IP == ADS_DL_GET_PKT_TYPE(pstImmPriv->ucModemId,
                                                       pstImmPriv->ucRabId))
    {
        pstPktErrStats = ADS_DL_GET_PKT_ERR_STATS_PTR(pstImmPriv->ucModemId,
                                                      pstImmPriv->ucRabId);
        if (pstImmPriv->u.usIpfResult & ADS_DL_IPF_RESULT_PKT_ERR_FEEDBACK_MASK)
        {
            if (0 == pstPktErrStats->ulErrorPktNum)
            {
                pstPktErrStats->ulMinDetectExpires =
                    ADS_CURRENT_TICK + pstFeedbackCfg->ulMinDetectDuration;
                pstPktErrStats->ulMaxDetectExpires =
                    ADS_CURRENT_TICK + pstFeedbackCfg->ulMaxDetectDuration;
            }

            pstPktErrStats->ulErrorPktNum++;
        }

        if (0 != pstPktErrStats->ulErrorPktNum)
        {
            pstPktErrStats->ulTotalPktNum++;
        }
    }
}


VOS_UINT32 ADS_DL_CalcPacketErrorRate(
    VOS_UINT32                          ulErrorPktNum,
    VOS_UINT32                          ulTotalPktNum
)
{
    VOS_UINT32                          ulPktErrRate;

    if ((0 == ulTotalPktNum) || (ulErrorPktNum > ulTotalPktNum))
    {
        ulPktErrRate = 100;
    }
    else if (ulErrorPktNum <= ADS_DL_ERROR_PACKET_NUM_THRESHOLD)
    {
        ulPktErrRate = ulErrorPktNum * 100 / ulTotalPktNum;
    }
    else
    {
        ulPktErrRate = ulErrorPktNum / (ulTotalPktNum / 100);
    }

    return ulPktErrRate;
}


VOS_VOID ADS_DL_FeedBackPacketErrorIfNeeded(VOS_VOID)
{
    ADS_PACKET_ERROR_FEEDBACK_CFG_STRU *pstFeedbackCfg = VOS_NULL_PTR;
    ADS_BEARER_PACKET_ERROR_STATS_STRU *pstPktErrStats = VOS_NULL_PTR;
    VOS_UINT32                          ulPktErrRate;
    VOS_UINT16                          usBearerMask;
    VOS_UINT32                           ulInstance;
    VOS_UINT32                           ulRabId;

    pstFeedbackCfg = ADS_DL_GET_PKT_ERR_FEEDBACK_CFG_PTR();
    if (VOS_FALSE == pstFeedbackCfg->ulEnabled)
    {
        return;
    }

    for (ulInstance = 0; ulInstance < ADS_INSTANCE_MAX_NUM; ulInstance++)
    {
        usBearerMask = 0;

        for (ulRabId = ADS_RAB_ID_MIN; ulRabId <= ADS_RAB_ID_MAX; ulRabId++)
        {
            pstPktErrStats = ADS_DL_GET_PKT_ERR_STATS_PTR(ulInstance, ulRabId);
            if (0 != pstPktErrStats->ulErrorPktNum)
            {
                if (ADS_TIME_IN_RANGE(ADS_CURRENT_TICK,
                        pstPktErrStats->ulMinDetectExpires,
                        pstPktErrStats->ulMaxDetectExpires))
                {
                    ulPktErrRate = ADS_DL_CalcPacketErrorRate(
                                        pstPktErrStats->ulErrorPktNum,
                                        pstPktErrStats->ulTotalPktNum);

                    if (ulPktErrRate >= pstFeedbackCfg->ulPktErrRateThres)
                    {
                        usBearerMask = ADS_BIT16_SET(usBearerMask, ulRabId);
                    }

                    pstPktErrStats->ulErrorPktNum = 0;
                    pstPktErrStats->ulTotalPktNum = 0;
                }

                if (ADS_TIME_AFTER(ADS_CURRENT_TICK,
                        pstPktErrStats->ulMaxDetectExpires))
                {
                    pstPktErrStats->ulErrorPktNum = 0;
                    pstPktErrStats->ulTotalPktNum = 0;
                    continue;
                }
            }
        }

        if (0 != usBearerMask)
        {
            ADS_DL_SndIntraPacketErrorInd(ulInstance, usBearerMask);
        }
    }

    return;
}


VOS_UINT32 ADS_DL_ValidateImmMem(IMM_ZC_STRU *pstImmZc)
{
    ADS_DL_IMM_PRIV_CB_STRU            *pstImmPriv = VOS_NULL_PTR;

    pstImmPriv = ADS_DL_IMM_PRIV_CB(pstImmZc);

    /* ????MODEMID */
    if (!ADS_IS_MODEMID_VALID(pstImmPriv->ucModemId))
    {
        ADS_DBG_DL_RMNET_MODEMID_ERR_NUM(1);
        return VOS_ERR;
    }

    /* ????RABID */
    if (!ADS_IS_RABID_VALID(pstImmPriv->ucRabId))
    {
        ADS_DBG_DL_RMNET_RABID_ERR_NUM(1);
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_PC5_DATA_CHANNEL)

VOS_VOID ADS_DL_ProcPc5Pkt(IMM_ZC_STRU *pstImmZc)
{
    ADS_MNTN_REC_DL_PC5_INFO(pstImmZc);

    (VOS_VOID)mdrv_pcv_xmit(pstImmZc);

    ADS_DBG_DL_RDQ_RX_PC5_PKT_NUM(1);
}
#endif


VOS_VOID ADS_DL_Xmit(
    IMM_ZC_STRU                         *pstImmZc,
    VOS_UINT32                           ulInstance,
    VOS_UINT32                           ulRabId
)
{
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc    = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    RCV_RD_LAST_DATA_FUNC               pRcvRdLstDataFunc = VOS_NULL_PTR;
#endif
    IMM_ZC_STRU                        *pstLstImmZc       = VOS_NULL_PTR;
    VOS_UINT32                          ulExParam;
    VOS_UINT16                          usIpfResult;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucExRabId;

    pRcvDlDataFunc    = ADS_DL_GET_DATA_CALLBACK_FUNC(ulInstance, ulRabId);
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    pRcvRdLstDataFunc = ADS_DL_GET_RD_LST_DATA_CALLBACK_FUNC(ulInstance, ulRabId);
#endif

    /* ?????????????? */
    pstLstImmZc = ADS_DL_GET_LST_DATA_PTR(ulInstance, ulRabId);
    if (VOS_NULL_PTR != pstLstImmZc)
    {
        usIpfResult = ADS_DL_GET_IPF_RESULT_FORM_IMM(pstLstImmZc);
        enIpType    = ADS_DL_GET_IPTYPE_FROM_IPF_RESULT(usIpfResult);
        ulExParam   = ADS_DL_GET_DATA_EXPARAM(ulInstance, ulRabId);
        ucExRabId   = ADS_BUILD_EXRABID(ulInstance, ulRabId);

        pRcvDlDataFunc = ADS_DL_GET_DATA_CALLBACK_FUNC(ulInstance, ulRabId);
        if (VOS_NULL_PTR != pRcvDlDataFunc)
        {
            (VOS_VOID)pRcvDlDataFunc(ucExRabId, pstLstImmZc, enIpType, ulExParam);

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
            /* ???????????? */
            pRcvRdLstDataFunc = ADS_DL_GET_RD_LST_DATA_CALLBACK_FUNC(ulInstance, ulRabId);
            if ((VOS_NULL_PTR == pstImmZc) && (VOS_NULL_PTR != pRcvRdLstDataFunc))
            {
                pRcvRdLstDataFunc(ulExParam);
            }
#endif
            ADS_DBG_DL_RMNET_TX_PKT_NUM(1);
        }
        else
        {
            IMM_ZcFreeAny(pstLstImmZc);
            ADS_DBG_DL_RMNET_NO_FUNC_FREE_PKT_NUM(1);
        }
    }

    ADS_DL_SET_LST_DATA_PTR(ulInstance, ulRabId, pstImmZc);

    return;
}


VOS_VOID ADS_DL_ProcTxData(IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT32                           ulInstance;
    VOS_UINT32                           ulRabId;

    if (VOS_NULL_PTR != pstImmZc)
    {
        ulInstance = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
        ulRabId    = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);

        ADS_DL_Xmit(pstImmZc, ulInstance, ulRabId);
    }
    else
    {
        for (ulInstance = 0; ulInstance < ADS_INSTANCE_MAX_NUM; ulInstance++)
        {
            for (ulRabId = ADS_RAB_ID_MIN; ulRabId <= ADS_RAB_ID_MAX; ulRabId++)
            {
                ADS_DL_Xmit(VOS_NULL_PTR, ulInstance, ulRabId);
            }
        }
    }

    return;
}


IMM_ZC_STRU* ADS_DL_RdDescTransImmMem(
    const IPF_RD_DESC_S                *pstRdDesc,
    VOS_UINT32                          ulSlice
)
{
    ADS_IPF_RD_RECORD_STRU             *pstRdRecord = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheLen;

    /* ??OUT??????????IMM???????? */
    pstImmZc = (IMM_ZC_STRU *)phys_to_virt((VOS_UINT_PTR)ADS_DL_GET_IPF_RD_DESC_OUT_PTR(pstRdDesc));
    if (VOS_NULL_PTR == pstImmZc)
    {
        return VOS_NULL_PTR;
    }

    /* ?????????????? */
    pstRdRecord = ADS_DL_GET_IPF_RD_RECORD_PTR();
    if (pstRdRecord->ulPos >= ADS_IPF_RD_BUFF_RECORD_NUM)
    {
        pstRdRecord->ulPos = 0;
    }

    pstRdRecord->astRdBuff[pstRdRecord->ulPos].ulSlice  = ulSlice;
    pstRdRecord->astRdBuff[pstRdRecord->ulPos].usAttr   = pstRdDesc->u16Attribute;
    pstRdRecord->astRdBuff[pstRdRecord->ulPos].usPktLen = pstRdDesc->u16PktLen;
    pstRdRecord->astRdBuff[pstRdRecord->ulPos].pstImmZc = pstImmZc;
    pstRdRecord->astRdBuff[pstRdRecord->ulPos].pOutPtr  = (VOS_VOID *)ADS_DL_GET_IPF_RD_DESC_OUT_PTR(pstRdDesc);
    pstRdRecord->ulPos++;

    /* ??????CACHE */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0))
    ulCacheLen = pstRdDesc->u16PktLen + IMM_MAC_HEADER_RES_LEN;
#else
    ulCacheLen = pstRdDesc->u16PktLen;
#endif
    ADS_IPF_DL_MEM_UNMAP(pstImmZc, ulCacheLen);

    /* ???????????????? */
    IMM_ZcPut(pstImmZc, pstRdDesc->u16PktLen);

    /* ??????????????: u16Result/u16UsrField1 */
    ADS_DL_SAVE_RD_DESC_TO_IMM(pstImmZc, pstRdDesc);

    return pstImmZc;
}


VOS_VOID ADS_DL_ProcIpfFilterData(
    IMM_ZC_STRU                        *pstImmZc
)
{
    VOS_UINT32                          ulCacheLen;
    VOS_UINT16                          usIpfResult;

    /* ??????CACHE */
    usIpfResult = ADS_DL_GET_IPF_RESULT_FORM_IMM(pstImmZc);
    ulCacheLen  = IMM_ZcGetUsedLen(pstImmZc) + IMM_MAC_HEADER_RES_LEN;

    ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulCacheLen);

    /* ??????????????????????
     * BearId 19: NDClient??????????????NDClient
     * BearId 17: DHCPv6??????????????DHCP
     * [0, 15]????????????????;
     * [16, 18, 20, 21]????????????
     */
    if (CDS_ADS_DL_IPF_BEARER_ID_ICMPV6 == ADS_DL_GET_BEAREDID_FROM_IPF_RESULT(usIpfResult))
    {
        ADS_DL_SendNdClientDataInd(pstImmZc);
        ADS_DBG_DL_RDQ_RX_ND_PKT_NUM(1);
    }
    else if (CDS_ADS_DL_IPF_BEARER_ID_DHCPV6 == ADS_DL_GET_BEAREDID_FROM_IPF_RESULT(usIpfResult))
    {
        ADS_DL_SendDhcpClientDataInd(pstImmZc);
        ADS_DBG_DL_RDQ_RX_DHCP_PKT_NUM(1);
    }
    else if (CDS_ADS_DL_IPF_BEARER_ID_MIP_ADV == ADS_DL_GET_BEAREDID_FROM_IPF_RESULT(usIpfResult))
    {
        ADS_DL_SendMipDataInd(pstImmZc);
        ADS_DBG_DL_RDQ_RX_ND_PKT_NUM(1);
    }
    else if (CDS_ADS_DL_IPF_BEARER_ID_MIP_REG_REPLY == ADS_DL_GET_BEAREDID_FROM_IPF_RESULT(usIpfResult))
    {
        ADS_DL_SendMipDataInd(pstImmZc);
        ADS_DBG_DL_RDQ_RX_ND_PKT_NUM(1);
    }
    else
    {
        ADS_DBG_DL_RDQ_FILTER_ERR_PKT_NUM(1);
    }

    ADS_IPF_SPE_MEM_MAP(pstImmZc, ulCacheLen);
    IMM_ZcFreeAny(pstImmZc);

    return;

}


VOS_VOID ADS_DL_ProcIpfFilterQue(VOS_VOID)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;

    for ( ; ; )
    {
        pstImmZc = IMM_ZcDequeueHead(ADS_GET_IPF_FILTER_QUE());
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        ADS_DL_ProcIpfFilterData(pstImmZc);
    }

    return;
}


VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID)
{
    ADS_DL_IPF_RESULT_STRU             *pstIpfResult    = VOS_NULL_PTR;
    IPF_RD_DESC_S                      *pstRdDesc       = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc        = VOS_NULL_PTR;
    VOS_UINT32                          ulRdNum         = IPF_DLRD_DESC_SIZE;
    VOS_UINT32                          ulTxTimeout     = 0;
    VOS_UINT32                          ulCnt;
    VOS_ULONG                           ulLockLevel;
    VOS_UINT32                          ulRnicNapiPollQueLen;
    VOS_UINT32                          ulSlice;

    /*
     * IPF_RD_DESC_S??u16Result????
     * [15]pkt_len_err     IP??????????????????
     * [14]bd_cd_noeq      BD??len??CD??????????????????
     * [13]pkt_parse_err   ????????????????
     * [12]bd_pkt_noeq     BD??len??IP??????????len????????????
     * [11]head_len_err    IPV4??????????????????IPV6??????????
     * [10]version_err     ??????????????
     * [9]ip_type          IP????????
     *                     0 ????IPV4
     *                     1 ????IPV6
     * [8]ff_type          ??????????????????????????????????
     *                     0 ??????????????????????????????(IP??????????????0)
     *                     1 ??????????????????????????????
     * [7:6]pf_type        IP??????????????
     *                     0 ????IP????????
     *                     1 ????IP????????????????????????
     *                     2 ????????????????????????????
     *                     3 ??????????????????????
     * [0:5]bear_id        ??????????????0x3F????????????????????
     */

    /* ????RD DESC */
    pstRdDesc = ADS_DL_GET_IPF_RD_DESC_PTR(0);
    mdrv_ipf_get_dlrd(&ulRdNum, pstRdDesc);

    /* ??????RD??0 */
    if (0 == ulRdNum)
    {
        ADS_DBG_DL_RDQ_GET_RD0_NUM(1);
        return;
    }

#if (FEATURE_OFF == FEATURE_LTE)
    mdrv_wdt_feed(0);
#endif

    /* ????RD???????? */
    ADS_DBG_DL_RDQ_RX_RD_NUM(ulRdNum);

    /* ??????AD????????RD */
    /*lint -e571*/
    VOS_SpinLockIntLock(&(g_stAdsCtx.stAdsIpfCtx.stAdqSpinLock), ulLockLevel);
    /*lint +e571*/
    ADS_DL_AllocMemForAdq();
    VOS_SpinUnlockIntUnlock(&(g_stAdsCtx.stAdsIpfCtx.stAdqSpinLock), ulLockLevel);

    ulSlice = VOS_GetSlice();

    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt++)
    {
        pstRdDesc = ADS_DL_GET_IPF_RD_DESC_PTR(ulCnt);

        /* ??????IMM???? */
        pstImmZc = ADS_DL_RdDescTransImmMem(pstRdDesc, ulSlice);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_RDQ_TRANS_MEM_FAIL_NUM(1);
            continue;
        }

#if (FEATURE_ON == FEATURE_PC5_DATA_CHANNEL)
        /* ????????PC5 IPF???????? */
        if (IPF_LTEV_DLFC == pstRdDesc->fc_head)
        {
            ADS_DL_ProcPc5Pkt(pstImmZc);
        }
        else
#endif
        {
            /* ????IMM???? */
            if (VOS_OK != ADS_DL_ValidateImmMem(pstImmZc))
            {
                IMM_ZcFreeAny(pstImmZc);
                continue;
            }

            /* ???????????? */
            ADS_DL_RecordPacketErrorStats(pstImmZc);

            /* ???????????????????????????????????????????? */
            ADS_RECV_DL_PERIOD_PKT_NUM(pstRdDesc->u16PktLen);

            /* ?????? */
            ulRnicNapiPollQueLen = 0;

            ADS_MNTN_REC_DL_IP_INFO(pstImmZc,
                                    ADS_DL_GET_IPF_RSLT_USR_FIELD1_FROM_IMM(pstImmZc),
                                    pstRdDesc->u32UsrField2,
                                    pstRdDesc->u32UsrField3,
                                    ulRnicNapiPollQueLen);

            /* ????IPF RESULT */
            pstIpfResult = (ADS_DL_IPF_RESULT_STRU *)&(pstRdDesc->u16Result);

            /* BearId 0x3F: ????????????????????????NDIS/PPP/RNIC*/
            if (CDS_ADS_DL_IPF_BEARER_ID_INVALID == pstIpfResult->usBearedId)
            {
                if (pstRdDesc->u16Result & ADS_DL_IPF_RESULT_PKT_ERR_MASK)
                {
                    ADS_DBG_DL_RDQ_RX_ERR_PKT_NUM(1);
                }

                ulTxTimeout = ADS_DL_TX_WAKE_LOCK_TMR_LEN;

                if (VOS_TRUE == g_ulAdsDlDiscardPktFlag)
                {
                    IMM_ZcFreeAny(pstImmZc);
                    continue;
                }

                ADS_DL_ProcTxData(pstImmZc);
                ADS_DBG_DL_RDQ_RX_NORM_PKT_NUM(1);
            }
            else
            {
                if (VOS_FALSE != VOS_CheckInterrupt())
                {
                    /* ???????????? */
                    IMM_ZcQueueTail(ADS_GET_IPF_FILTER_QUE(), pstImmZc);
                }
                else
                {
                    ADS_DL_ProcIpfFilterData(pstImmZc);
                }
            }
        }
    }

    /* ???????????????? */
    ADS_DL_ProcTxData(VOS_NULL_PTR);

    if (0 != IMM_ZcQueueLen(ADS_GET_IPF_FILTER_QUE()))
    {
        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_FILTER_DATA_PROC);
    }

    /* ???????????????????? */
    ADS_DL_FeedBackPacketErrorIfNeeded();

    ADS_MNTN_RPT_ALL_DL_PKT_INFO();

    ADS_DL_EnableTxWakeLockTimeout(ulTxTimeout);
    return;
}


VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;
    VOS_UINT32                          ulRslt = VOS_FALSE;

    /* ???????????????? */
    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    if (0 != pstFcAssemInfo->ulEnableMask)
    {
        pstFcAssemInfo->ulRdCnt += ulRdNum;

        if (ADS_TIME_AFTER_EQ(ADS_CURRENT_TICK, (pstFcAssemInfo->ulTmrCnt + pstFcAssemInfo->ulExpireTmrLen)))
        {
            if (VOS_FALSE == pstFcAssemInfo->ulFcActiveFlg)
            {
                if (pstFcAssemInfo->ulRdCnt >= pstFcAssemInfo->ulRateUpLev)
                {
                    ADS_DBG_DL_FC_ACTIVATE_NUM(1);
                    pstFcAssemInfo->ulFcActiveFlg = VOS_TRUE;
                    ulRslt = VOS_TRUE;
                }
            }
            else
            {
                if (pstFcAssemInfo->ulRdCnt <= pstFcAssemInfo->ulRateDownLev)
                {
                    pstFcAssemInfo->ulFcActiveFlg = VOS_FALSE;
                }
            }

            ADS_DBG_DL_FC_TMR_TIMEOUT_NUM(1);
            pstFcAssemInfo->ulTmrCnt = ADS_CURRENT_TICK;
            pstFcAssemInfo->ulRdCnt = 0;
        }
    }

    return ulRslt;
}


VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucExRabId,
    RCV_DL_DATA_FUNC                    pFunc,
    VOS_UINT32                          ulExParam
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulInstance;
    VOS_UINT32                          ulRabId;

    /* ????MODEMID */
    ulInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_MODEMID_VALID(ulInstance))
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_RegDlDataCallback: ModemId is invalid! <ModemId>", ulInstance);
        return VOS_ERR;
    }

    /* ????RABID */
    ulRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ulRabId))
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_DL,
            "ADS_DL_RegDlDataCallback: RabId is invalid! <ModemId>,<RabId>", ulInstance, ulRabId);
        return VOS_ERR;
    }

    /* ???????????????????? */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ulInstance, ulRabId);
    pstDlRabInfo->ulRabId           = ulRabId;
    pstDlRabInfo->ulExParam         = ulExParam;
    pstDlRabInfo->pRcvDlDataFunc    = pFunc;

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT32                          ulInstanceIndex;
    VOS_UINT32                          ulRealRabId;

    /* ucRabId????2??bit????modem id*/
    ulInstanceIndex = ADS_GET_MODEMID_FROM_EXRABID(ucRabId);
    ulRealRabId     = ADS_GET_RABID_FROM_EXRABID(ucRabId);

    /* RabId?????????? */
    if (!ADS_IS_RABID_VALID(ulRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegFilterDataCallback: ucRabId is", ulRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ulInstanceIndex, ulRealRabId);

    /* ????ADS???????????????????? */
    pstDlRabInfo->ulRabId               = ulRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = pFunc;

    /* ???????????????? */
    ADS_FILTER_SaveIPAddrInfo(pstFilterIpAddr);

    return VOS_OK;
}


VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT32 ulRabId)
{
    ADS_DL_RAB_INFO_STRU                 *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT32                           ulInstanceIndex;
    VOS_UINT32                           ulRealRabId;

    /* ucRabId????2??bit????modem id*/
    ulInstanceIndex = ADS_GET_MODEMID_FROM_EXRABID(ulRabId);
    ulRealRabId     = ADS_GET_RABID_FROM_EXRABID(ulRabId);

    /* RabId?????????? */
    if (!ADS_IS_RABID_VALID(ulRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_DeregFilterDataCallback: ulRabId is", ulRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ulInstanceIndex, ulRealRabId);

    /* ??????ADS???????????????????? */
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    /* ???????????? */
    ADS_FILTER_Reset();

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)

VOS_UINT32 ADS_DL_RegNapiCallback(
    VOS_UINT8                           ucExRabId,
    RCV_RD_LAST_DATA_FUNC               pLastDataFunc,
    VOS_UINT32                          ulExParam
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulInstance;
    VOS_UINT32                          ulRabId;

    /* ????MODEMID */
    ulInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_MODEMID_VALID(ulInstance))
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_RegRdLastDataCallback: ModemId is invalid! <ModemId>", ulInstance);
        return VOS_ERR;
    }

    /* ????RABID */
    ulRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ulRabId))
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_DL,
            "ADS_DL_RegRdLastDataCallback: RabId is invalid! <ModemId>,<RabId>", ulInstance, ulRabId);
        return VOS_ERR;
    }

    /* ???????????????????? */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ulInstance, ulRabId);
    pstDlRabInfo->ulRabId            = ulRabId;
    pstDlRabInfo->ulExParam          = ulExParam;
    pstDlRabInfo->pRcvRdLstDataFunc  = pLastDataFunc;

    return VOS_OK;
}
#endif


VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd = VOS_NULL_PTR;
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo    = VOS_NULL_PTR;
    VOS_UINT32                          ulInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    enPktType       = ADS_CDS_IPF_PKT_TYPE_IP;
    ulInstanceIndex = pstPdpStatusInd->enModemId;

    /* RabId?????????? */
    if (!ADS_IS_RABID_VALID(pstPdpStatusInd->ucRabId))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvTafPdpStatusInd: Rab Id is invalid");
        return VOS_ERR;
    }

    if (ADS_PDP_PPP == pstPdpStatusInd->enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ulInstanceIndex, pstPdpStatusInd->ucRabId);

    /* PDP???? */
    if (ADS_PDP_STATUS_ACT == pstPdpStatusInd->enPdpStatus)
    {
        /* ????ADS??????????????RABID */
        pstDlRabInfo->ulRabId           = pstPdpStatusInd->ucRabId;
        pstDlRabInfo->enPktType         = enPktType;
    }
    /* PDP??????  */
    else if (ADS_PDP_STATUS_DEACT == pstPdpStatusInd->enPdpStatus)
    {
        /* ????ADS???????????????? */
        pstDlRabInfo->ulRabId           = ADS_RAB_ID_INVALID;
        pstDlRabInfo->enPktType         = ADS_CDS_IPF_PKT_TYPE_IP;
        pstDlRabInfo->ulExParam         = 0;

        if (ADS_CLEAN_RCV_CB_FUNC_TURE == pstPdpStatusInd->enCleanRcvCbFlag)
        {
            pstDlRabInfo->pRcvDlDataFunc    = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
            pstDlRabInfo->pRcvRdLstDataFunc  = VOS_NULL_PTR;
#endif
        }
        else
        {
            ADS_NORMAL_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvTafPdpStatusInd: Not clean ADS DL data call back func");
        }
    }
    else
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvTafPdpStatusInd: Pdp Status is invalid");
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(VOS_VOID)
{
    VOS_UINT32                           ulIndex;

    ADS_TRACE_HIGH("proc reset msg: enter.\n");

    /* ???????????????????? */
    for (ulIndex = 0; ulIndex < ADS_MAX_TIMER_NUM; ulIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, ulIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /* ?????????????? */
    ADS_ResetDlCtx();

    /* ????IPF??AD */
    ADS_DL_FreeIpfUsedAd1();
    ADS_DL_FreeIpfUsedAd0();

    for (ulIndex = 0; ulIndex < ADS_DL_ADQ_MAX_NUM; ulIndex++)
    {
        TAF_MEM_SET_S(ADS_DL_GET_IPF_AD_RECORD_PTR(ulIndex),
                      sizeof(ADS_IPF_AD_RECORD_STRU),
                      0x00,
                      sizeof(ADS_IPF_AD_RECORD_STRU));
    }

    /* ????????????????????API???????????? */
    VOS_SmV(ADS_GetDLResetSem());

    ADS_TRACE_HIGH("proc reset msg: leave.\n");
    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(
    MsgBlock                           *pstMsg
)
{
    VOS_ULONG                           ulLockLevel;
    ADS_TRACE_HIGH("proc reset msg: enter.\n");

    TAF_MEM_SET_S(ADS_DL_GET_IPF_RD_RECORD_PTR(),
                  sizeof(ADS_IPF_RD_RECORD_STRU),
                  0x00,
                  sizeof(ADS_IPF_RD_RECORD_STRU));

    /* ????IPF */
    mdrv_ipf_reinit_dlreg();

    /* ??????????ADQ */
    /*lint -e571*/
    VOS_SpinLockIntLock(&(g_stAdsCtx.stAdsIpfCtx.stAdqSpinLock), ulLockLevel);
    /*lint +e571*/
    ADS_DL_AllocMemForAdq();
    VOS_SpinUnlockIntUnlock(&(g_stAdsCtx.stAdsIpfCtx.stAdqSpinLock), ulLockLevel);

    ADS_TRACE_HIGH("proc reset msg: leave.\n");
    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvTafMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_DL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg)
{
    /* ???????????????????????????????????????????? */
    return VOS_ERR;
}


VOS_VOID ADS_DL_ProcIntraPacketErrorInd(MsgBlock* pMsg)
{
    ADS_PACKET_ERROR_IND_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRabId;

    pstMsg = (ADS_PACKET_ERROR_IND_STRU *)pMsg;

    for (ulRabId = ADS_RAB_ID_MIN; ulRabId <= ADS_RAB_ID_MAX; ulRabId++)
    {
        if (ADS_BIT16_IS_SET(pstMsg->usBearerMask, ulRabId))
        {
            ADS_DL_SndCdsErrorInd(pstMsg->usModemId, ulRabId);
        }
    }

    return;
}


VOS_UINT32 ADS_DL_RcvAdsDlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            /* ????IPF????????????????ADS_DL????????????????1?? */
            ADS_StartTimer(TI_ADS_DL_CCORE_RESET_DELAY, ADS_DL_GET_CCORE_RESET_DELAY_TIMER_LEN());
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            ADS_DL_RcvCcpuResetEndInd(pMsg);
            break;

        case ID_ADS_PACKET_ERROR_IND:
            ADS_DL_ProcIntraPacketErrorInd(pMsg);
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RcvAdsDlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ?????????????? */
    switch ( pMsg->ulSenderPid )
    {
        /* ????APS?????? */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_DL_RcvTafMsg(pMsg);
            return;

        /* ????CDS?????? */
        case UEPS_PID_CDS:
            ADS_DL_RcvCdsMsg(pMsg);
            return;

        /* ????ADS DL?????? */
        case ACPU_PID_ADS_DL:
            ADS_DL_RcvAdsDlMsg(pMsg);
            return;

        default:
            return;
    }
}





