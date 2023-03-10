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
  1 ??????????????
*****************************************************************************/
#include "v_typdef.h"
#include "IpsMntn.h"
#include "TTFComm.h"
#include "v_id.h"
#include "vos.h"
#include "NetfilterEx.h"
#include "TtfOamInterface.h"
#include "TtfIpComm.h"
#include "TTFUtil.h"
#include "nv_id_gucnas.h"
#include "nv_stru_gucnas.h"
#include "securec.h"
/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_IPS_MNTN_C
/*lint -e767 */

/*****************************************************************************
  2 ??????
*****************************************************************************/

/*******************************************************************************
  3 ????????
*******************************************************************************/

/*****************************************************************************
  2 ????????
*****************************************************************************/

/*****************************************************************************
  3 ????????????
*****************************************************************************/
IPS_MNTN_TRACE_CONFIG_REQ_STRU          g_stIpsTraceMsgCfg;     /*TCP/IP??????????????????????*/

IPS_MMTN_TRACE_CFG_NOTIFY_FUNC          g_treceCfgNotifyCb = VOS_NULL_PTR;


/*****************************************************************************
  4 ??????????
*****************************************************************************/

/*****************************************************************************
  5 ????????
*****************************************************************************/


/*****************************************************************************
  6 UNION????
*****************************************************************************/

/*****************************************************************************
  7 OTHERS????
*****************************************************************************/

/*****************************************************************************
  8 ????????
*****************************************************************************/


VOS_VOID IPS_MNTN_SndCfgCnf2Om
(
    VOS_UINT32            ulPrimId,
    VOS_UINT32            ulTransMsgContentLen,
    const VOS_VOID       *pTransMsgContent
)
{
    MsgBlock                *pSendMsg = VOS_NULL_PTR;

    /*??????????????*/
    pSendMsg = VOS_AllocMsg(ACPU_PID_NFEXT, ulTransMsgContentLen - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSendMsg)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_SndCfgCnf2Om, ERROR, Call VOS_AllocMsg fail!");
        return;
    }

    TTF_ACORE_SF_CHK(memcpy_s(pSendMsg, ulTransMsgContentLen, pTransMsgContent, ulTransMsgContentLen));

    if ( VOS_OK != VOS_SendMsg(ACPU_PID_NFEXT, pSendMsg) )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_SndCfgCnf2Om, ERROR, Call VOS_SendMsg fail!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_NFEXT)

VOS_UINT32 IPS_MNTN_GetPktLenByTraceCfg
(
    IPS_MNTN_TRACE_CONFIG_STRU     *pstTraceCfg,
    const VOS_UINT8                *pucPktData,
    VOS_UINT16                      usPktLen,
    VOS_UINT32                     *pulDataLen
)
{
    VOS_UINT32                          ulTraceDataLen;
    IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32   enChoice = pstTraceCfg->ulChoice;

    *pulDataLen    =   0;

    enChoice = PS_MIN(enChoice, IPS_MNTN_TRACE_MSG_HEADER_CHOSEN);

    /*??????????????????*/
    switch (enChoice)
    {
        case IPS_MNTN_TRACE_NULL_CHOSEN:
            return PS_FALSE;

        case IPS_MNTN_TRACE_MSG_HEADER_CHOSEN:
            ulTraceDataLen  = TTF_GetIpDataTraceLen(ACPU_PID_NFEXT, (VOS_UINT8 *)pucPktData, usPktLen);
            *pulDataLen     = TTF_MIN(ulTraceDataLen, usPktLen);
            break;

        case IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN:
            *pulDataLen     = TTF_MIN(pstTraceCfg->ulTraceDataLen, usPktLen);
            break;

        case IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN:
            *pulDataLen     = usPktLen;
            break;

        default:
            return PS_FALSE;
    }

    return PS_TRUE;
}



/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_PktInfoCB
(
    const VOS_UINT8                *pucNetIfName,
    const struct sk_buff           *skb,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16   enType
)
{
    VOS_UINT8                          *pucTraceData = VOS_NULL_PTR;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg  = VOS_NULL_PTR;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulNeedMemLen;
    VOS_UINT8                          *pucIpHeader = VOS_NULL_PTR;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    /*????????????????????????????*/
    if(ID_IPS_TRACE_INPUT_DATA_INFO == enType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPreRoutingTraceCfg);
    }
    else if(ID_IPS_TRACE_OUTPUT_DATA_INFO == enType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPostRoutingTraceCfg);
    }
    else if((enType >= ID_IPS_TRACE_BRIDGE_DATA_INFO) && (enType <= ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP))
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stLocalTraceCfg);
    }
    else
    {
        /*????????????,??????????????*/
        TTF_LOG( ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_PktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /* ????IP?? */
    pucIpHeader = skb_network_header(skb);

    /*??????????????????????????????????*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, pucIpHeader, skb->len, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*????????????*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_GRO_MAX_BYTE_LEN, ulDataLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulTransDataLen      += MAC_HEADER_LENGTH;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);
    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*????????????*/
    pstTraceMsg             = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = skb->len + MAC_HEADER_LENGTH;
    pstTraceMsg->usPrimId   = enType;
    TTF_ACORE_SF_CHK(memcpy_s(pstTraceMsg->aucNetIfName, sizeof(pstTraceMsg->aucNetIfName), pucNetIfName, IPS_IFNAMSIZ));

    /* ????????????(?????? pstTraceCfg->ulTraceDataLen ??0)??ulDataLen??0??????????????????????????????????????????????*/
    /*lint -e{416,426,669} */
    if ( ulDataLen )
    {
        if (0 > skb_copy_bits(skb, 0, (pstTraceMsg->aucData + MAC_HEADER_LENGTH), ulDataLen))
        {
            TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "IPS, IPS_MNTN_PktInfoCB, WARNING, Call skb_copy_bits fail!");

            NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
            return;
        }
    }

    /*  user??????????IP???? */
    TTF_MaskIpAddrTraces(ACPU_PID_NFEXT, pstTraceMsg->aucData + MAC_HEADER_LENGTH, (VOS_UINT16)ulDataLen);
    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;
}
/*lint +esym( 593, pucTraceData ) */


/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_BridgePktInfoCB
(
    const VOS_UINT8                        *pucSrcPort,
    const VOS_UINT8                        *pucDestPort,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{
    VOS_UINT8                          *pucTraceData = VOS_NULL_PTR;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg  = VOS_NULL_PTR;
    IPS_MNTN_BRIDGE_PKT_INFO_STRU      *pstTraceMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;



    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_BridgePktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    /*????????????????????????????*/
    if((enType >= ID_IPS_TRACE_BRIDGE_DATA_INFO) && (enType <= ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP))
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stBridgeArpTraceCfg);
    }
    else
    {
        /*????????????,??????????????*/
        TTF_LOG( ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_BridgePktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*??????????????????????????????????*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, pucPktData, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*????????????*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_BRIDGE_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*????????????*/
    pstTraceMsg             = (IPS_MNTN_BRIDGE_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;

    if (VOS_NULL_PTR != pucSrcPort)
    {
        TTF_ACORE_SF_CHK(memcpy_s(pstTraceMsg->aucSrcPort, IPS_END_NAME, pucSrcPort, IPS_END_NAME));
    }
    if (VOS_NULL_PTR != pucDestPort)
    {
        TTF_ACORE_SF_CHK(memcpy_s(pstTraceMsg->aucDestPort, IPS_END_NAME, pucDestPort, IPS_END_NAME));
    }

    if (ulDataLen > 0) {
        TTF_ACORE_SF_CHK(memcpy_s(pstTraceMsg->aucData , ulDataLen, pucPktData, ulDataLen));
    }

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;

}
/*lint +esym( 593, pucTraceData ) */


/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_CtrlPktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{

    VOS_UINT8                          *pucTraceData = VOS_NULL_PTR;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNeedMemLen;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CtrlPktInfoCB, ERROR, pucPktData is NULL ");
        return;
    }

    /* HIDS?????? */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;

    ulDataLen       =   PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, usPktLen);

    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* ??Linux???????????? */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*????????????*/
    pstTraceMsg             = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;
    TTF_ACORE_SF_CHK(memcpy_s(pstTraceMsg->aucNetIfName, IPS_IFNAMSIZ, pucNetIfName, IPS_IFNAMSIZ));

    if (ulDataLen > 0) {
        TTF_ACORE_SF_CHK(memcpy_s(pstTraceMsg->aucData, ulDataLen, pucPktData, ulDataLen));
    }

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);

    }

    return;
}
/*lint +esym( 593, pucTraceData ) */


VOS_VOID IPS_MNTN_FlowCtrl(VOS_UINT32 ulFcType, TTF_MNTN_MSG_TYPE_ENUM_UINT16  enType)
{
    DIAG_TRANS_IND_STRU                 stTransData;
    IPS_MNTN_FLOW_CTRL_STRU             stFlowCtrlMsg;

    (VOS_VOID)memset_s(&stFlowCtrlMsg, sizeof(IPS_MNTN_FLOW_CTRL_STRU), 0x0, sizeof(IPS_MNTN_FLOW_CTRL_STRU));

    /* ???????? */
    stTransData.ulPid       = ACPU_PID_NFEXT;
    stTransData.ulMsgId     = enType;
    stTransData.ulModule    = DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM);
    stTransData.ulLength    = MNTN_FLOW_CTRL_INFO_LEN;
    stTransData.pData       = &stFlowCtrlMsg;

    stFlowCtrlMsg.ulFcType  = ulFcType;
    stFlowCtrlMsg.usPrimId  = enType;

    if ( VOS_OK != DIAG_TransReport(&stTransData) )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, DIAG_TransReport, ERROR, Call DIAG_TransReport fail!");
    }

    return;
}

#endif      /* #if (FEATURE_ON == FEATURE_NFEXT) */


VOS_UINT32 IPS_MNTN_TransMsg
(
    VOS_UINT8                              *pucTransMsg,
    VOS_UINT32                              ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enMsgName
)
{
    NF_EXT_DATA_RING_BUF_STRU               stBufData;
    DIAG_TRANS_IND_STRU                     *pstDiagTransData = VOS_NULL_PTR;

    /*????????*/
    pstDiagTransData            = (DIAG_TRANS_IND_STRU *)pucTransMsg;

    /* ???????? */
    pstDiagTransData->ulPid     = ACPU_PID_NFEXT;
    pstDiagTransData->ulMsgId   = enMsgName;
    pstDiagTransData->ulModule  = DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM);
    pstDiagTransData->ulLength  = ulTransMsgContentLen;
    pstDiagTransData->pData     = pucTransMsg + sizeof(DIAG_TRANS_IND_STRU);

    /* ????????????????????????????, ???????????????????? */
    if (VOS_FALSE != VOS_CheckInterrupt())
    {
        stBufData.pData         = (VOS_UINT8 *)pucTransMsg;

        if (VOS_OK != NFExt_AddDataToRingBuf(&stBufData))
        {
            return VOS_ERR;
        }
    }
    else
    {
        if ( VOS_OK != DIAG_TransReport(pstDiagTransData) )
        {
            TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "IPS, IPS_MNTN_TransMsg, WARNING, Call DIAG_TransReport fail!");

            return VOS_ERR;
        }

        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTransMsg);
    }

    return VOS_OK;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_BridgeTraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_TRACE_NULL_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stPreRoutingTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stPostRoutingTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stLocalTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stBridgeArpTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (WTTF_TRACE_MSG_YES < pRcvMsg->enAdsIPConfig)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceAdvancedCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    /*TCP/IP??????????????????????????*/
    if (PS_FALSE == IPS_MNTN_TraceCfgChkParam(pRcvMsg))
    {
        return PS_FALSE;
    }

    /*????????????????????????????*/
    if (PS_FALSE == IPS_MNTN_BridgeTraceCfgChkParam(pRcvMsg))
    {
        return  PS_FALSE;
    }

    if ((WTTF_TRACE_MSG_YES != pRcvMsg->enAdsIPConfig) && (WTTF_TRACE_MSG_NO != pRcvMsg->enAdsIPConfig))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


STATIC VOS_UINT8 IPS_MNTN_GetPrivacyFilterNvCfg(VOS_VOID)
{
    VOS_UINT8                          ucLogFilterFlag = VOS_TRUE;

    return ucLogFilterFlag;
}


VOS_VOID IPS_MNTN_TraceSensitiveAdjustSwitch(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pTraceCfg)
{
    VOS_UINT8                           ucAdjustFlg = PS_FALSE;

    /*  ?????????????????????? */
    if(VOS_TRUE != IPS_MNTN_GetPrivacyFilterNvCfg())
    {
        return;
    }

    /* ???????????????? */
    if ( pTraceCfg->stBridgeArpTraceCfg.ulChoice > IPS_MNTN_TRACE_MSG_HEADER_CHOSEN)
    {
        pTraceCfg->stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
        ucAdjustFlg = PS_TRUE;
    }

    if ( pTraceCfg->stPreRoutingTraceCfg.ulChoice > IPS_MNTN_TRACE_MSG_HEADER_CHOSEN)
    {
        pTraceCfg->stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
        ucAdjustFlg = PS_TRUE;
    }

    if ( pTraceCfg->stPostRoutingTraceCfg.ulChoice > IPS_MNTN_TRACE_MSG_HEADER_CHOSEN)
    {
        pTraceCfg->stPostRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
        ucAdjustFlg = PS_TRUE;
    }

    if ( pTraceCfg->stLocalTraceCfg.ulChoice > IPS_MNTN_TRACE_MSG_HEADER_CHOSEN)
    {
        pTraceCfg->stLocalTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
        ucAdjustFlg = PS_TRUE;
    }

    if(ucAdjustFlg == PS_TRUE)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR, "In Sensitive status, Some config has been modify");
    }

    return;
}

VOS_VOID IPS_MNTN_TraceCfgNotify(VOS_VOID)
{
    VOS_BOOL traceEnable = (WTTF_TRACE_MSG_YES == g_stIpsTraceMsgCfg.enAdsIPConfig) ? VOS_TRUE : VOS_FALSE;

    if (g_treceCfgNotifyCb != VOS_NULL_PTR) {
        g_treceCfgNotifyCb(traceEnable);
    }
}


VOS_VOID IPS_MNTN_TraceAdvancedCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                       enResult;

    OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU    *pRcvMsg = VOS_NULL_PTR;
    IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU    stIpsTraceCfgCnf;

    pRcvMsg = (OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU *)pMsg;

    /*????????????????????*/
    enResult = IPS_MNTN_TraceAdvancedCfgChkParam(&(pRcvMsg->stIpsAdvanceCfgReq));

    /* Fill DIAG trans msg header */
    stIpsTraceCfgCnf.stDiagHdr.ulSenderCpuId        = VOS_LOCAL_CPUID;
    stIpsTraceCfgCnf.stDiagHdr.ulSenderPid          = ACPU_PID_NFEXT;
    stIpsTraceCfgCnf.stDiagHdr.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    stIpsTraceCfgCnf.stDiagHdr.ulReceiverPid        = MSP_PID_DIAG_APP_AGENT;   /* ????????????????DIAG????DIAG??????????????????????????HIDS????*/
    stIpsTraceCfgCnf.stDiagHdr.ulLength             = sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsTraceCfgCnf.stDiagHdr.ulMsgId              = ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF;

    /* DIAG????????????????????*/
    stIpsTraceCfgCnf.stDiagHdr.usOriginalId         = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsTraceCfgCnf.stDiagHdr.usTerminalId         = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsTraceCfgCnf.stDiagHdr.ulTimeStamp          = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsTraceCfgCnf.stDiagHdr.ulSN                 = pRcvMsg->stDiagHdr.ulSN;

    if ( PS_FALSE == enResult )
    {
        /*??????????????????????OM????????????*/
        stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt  =   PS_FAIL;

        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_TraceAdvancedCfgReq check fail");

        return;
    }

#if (FEATURE_ON == FEATURE_NFEXT)
    enResult = NFExt_ConfigEffective(&(pRcvMsg->stIpsAdvanceCfgReq));
    if( PS_FALSE == enResult )
    {
        /*????????????????????????OM????????????*/
        stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt =   PS_FAIL;

        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_SetCallbackFunc fail");

        return;
    }
#endif

    /*????????????*/
    (VOS_VOID)memcpy_s(&g_stIpsTraceMsgCfg, sizeof(g_stIpsTraceMsgCfg), &(pRcvMsg->stIpsAdvanceCfgReq), sizeof(pRcvMsg->stIpsAdvanceCfgReq));

    /* ???????????????????????? */
    IPS_MNTN_TraceSensitiveAdjustSwitch(&g_stIpsTraceMsgCfg);

    IPS_MNTN_TraceCfgNotify();
    
    /*??OM????????????*/
    stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt = PS_SUCC;

    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

    return;

}


VOS_UINT32 IPS_MNTN_GetIPInfoCfg(TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType)
{
    if ((ID_IPS_TRACE_ADS_UL == enType)||(ID_IPS_TRACE_ADS_DL == enType))
    {
        if (WTTF_TRACE_MSG_YES == g_stIpsTraceMsgCfg.enAdsIPConfig)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

VOS_VOID IPS_MNTN_RegTraceCfgNotify(IPS_MMTN_TRACE_CFG_NOTIFY_FUNC notifyFunc)
{
    g_treceCfgNotifyCb = notifyFunc;
}
