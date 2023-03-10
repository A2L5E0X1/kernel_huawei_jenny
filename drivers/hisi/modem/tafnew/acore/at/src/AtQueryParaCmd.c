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
#include "mdrv.h"
#include "PppInterface.h"
#include "TafDrvAgent.h"
#include "Taf_Tafm_Remote.h"
#include "TtfMemAtInterface.h"
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtPhyInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "AtCheckFunc.h"
#include "AtSndMsg.h"
#include "AtRnicInterface.h"
#include "AtCheckFunc.h"
#include "AtInputProc.h"
#include "AtEventReport.h"
#include "AtDeviceCmd.h"
#include "AtTafAgentInterface.h"
#include "AppVcApi.h"
#include "TafOamInterface.h"
#include "TafIfaceApi.h"

#if (FEATURE_LTE == FEATURE_ON)
#include "msp_nvim.h"
#include "at_common.h"
#include "at_lte_common.h"
#endif

#include "nv_stru_sys.h"
#include "nv_stru_gas.h"
#include "nv_stru_msp_interface.h"
#include "acore_nv_stru_msp.h"

#include "CssAtInterface.h"

#include "AtMsgPrint.h"

#include "PsCommonDef.h"
#include "PsLib.h"
#include "product_config.h"
#include "AtCmdMiscProc.h"
#include "TafCcmApi.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/pm_wakeup.h>
#else
#include "Linuxstub.h"
#endif
#include "securec.h"

/*lint -esym(516,free,malloc)*/



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_QUERYPARACMD_C


/*****************************************************************************
   2 ????????????
*****************************************************************************/

/*????????????????????*/
extern TAF_UINT32                       gulErrType;

extern VOS_UINT32                       g_ulWifiFreq;
extern VOS_UINT32                       g_ulWifiMode;
extern VOS_UINT32                       g_ulWifiRate;
extern VOS_UINT32                       g_lWifiPower;
extern VOS_UINT32                       g_ulUcastWifiRxPkts;
extern VOS_UINT32                       g_ulMcastWifiRxPkts;


/*****************************************************************************
   3 ??????????????
*****************************************************************************/

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT8 NAS_GetPsRegContainDrx();
#endif
/*****************************************************************************
   4 ????????
*****************************************************************************/

VOS_UINT32 AT_QryGTimerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulGTimerLength;


    ulGTimerLength = 0;

    /* ????NV??en_NV_Item_GPRS_ActiveTimerLength????GPRS?????????? */
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_GPRS_ActiveTimerLength,
                              &ulGTimerLength,
                              sizeof(ulGTimerLength));
    if (ulRet != NV_OK)
    {
        AT_WARN_LOG("AT_QryGTimerPara: Fail to read en_NV_Item_GPRS_ActiveTimerLength");
        return AT_DEVICE_OTHER_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulGTimerLength);

    return AT_OK;
}


VOS_UINT32 AT_QryRsimPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ucCardStatus;
    VOS_UINT32                           ucCardType;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulGetModemIdRslt != VOS_OK)
    {
        AT_ERR_LOG("At_SetCardModePara:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* ???? SIM ???????????? */
    ucCardType   =  pstUsimInfoCtx->enCardType;
    ucCardStatus =  pstUsimInfoCtx->enCardStatus;

    AT_NORM_LOG1("AT_QryRsimPara: ucCardStatus is ", (VOS_INT32)ucCardStatus);
    AT_NORM_LOG1("AT_QryRsimPara: ucCardType is ",   (VOS_INT32)ucCardType);

    if (ucCardStatus == USIMM_CARDAPP_SERVIC_BUTT)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_BUSY);
        return AT_OK;
    }

    /* ????????????USIMM_CARD_ROM_SIM???????????????????????????? */
    if ((pstUsimInfoCtx->enCardMediumType == USIMM_CARD_MEDIUM_ROM)
     || (ucCardStatus == USIMM_CARDAPP_SERVIC_ABSENT))
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_ABSENT);
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_AVAILABLE);
    }

    return AT_OK;
}


VOS_UINT32 AT_QryBatVolPara(VOS_UINT8 ucIndex)
{

    /*???? ??????????*/
    if (AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_TBATVOLT_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT) == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBATVOLT_QRY;           /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (aucDeciDigit[ulLoop] > 9)
        {
            return VOS_ERR;
        }

        aucAscii[ulLoop] = aucDeciDigit[ulLoop] + '0';
    }

    return VOS_OK;
}


VOS_VOID AT_ConvertImsiDigit2String(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                          *pucImsiString,
    VOS_UINT32                          ulStrBufLen
)
{
    VOS_UINT8                           ucImsiLen;
    VOS_UINT32                          ulTempNum;
    VOS_UINT8                           aucImsiNum[NAS_IMSI_STR_LEN];
    VOS_UINT32                          i;

    AT_NORM_LOG("AT_ConvertImsiDigit2String enter.");

    if (ulStrBufLen <= NAS_IMSI_STR_LEN)
    {
        return;
    }

    memset_s(aucImsiNum, sizeof(aucImsiNum), 0x00, NAS_IMSI_STR_LEN);
    ulTempNum       = 0;

    ucImsiLen       = TAF_MIN(pucImsi[0], NAS_MAX_IMSI_LENGTH - 1);

    aucImsiNum[ulTempNum++] = (pucImsi[1] & 0xf0) >> 4;

    for (i = 2; i <= ucImsiLen; i++)
    {
        aucImsiNum[ulTempNum++] = pucImsi[i] & 0x0f;
        aucImsiNum[ulTempNum++] = (pucImsi[i] & 0xf0) >> 4;
    }

    /* ??'f'??IMSI???????????? */
    i = 0;

    AT_LOG1("AT_ConvertImsiDigit2String: ulTempNum", ulTempNum);

    while (i < ulTempNum)
    {
        if (aucImsiNum[i] != 0x0f)
        {
            if ((aucImsiNum[i] >= 10)
            &&  (aucImsiNum[i] < 15))
            {
                pucImsiString[i] = aucImsiNum[i] - 10 + 'A';
            }
            else
            {
                pucImsiString[i] = aucImsiNum[i] + '0';
            }

            i++;
        }
        else
        {
            break;
        }
    }

    AT_LOG1("AT_ConvertImsiDigit2String: i", i);

    pucImsiString[i] = '\0';

    /* GDPR????????????IMSI */

    return;
}


VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[])
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN + 1]; /* MAC????*/
    VOS_UINT32                          ulE5GwMacAddrOffset;
    VOS_UINT32                          ulMacOffset;
    errno_t                             lMemResult;


    memset_s(aucE5GwMacAddr, sizeof(aucE5GwMacAddr), 0x00, sizeof(aucE5GwMacAddr));

    /* ????MAC?????????? */
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    if (ulRet != NV_OK)
    {
        AT_WARN_LOG("AT_GetPhynumMac: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }

    /* MAC????????????: 7A:FE:E2:21:11:E4=>7AFEE22111E4 */
    ulMacOffset         = 0;
    ulE5GwMacAddrOffset = 0;
    for (ulLoop = 0; ulLoop < (1 + AT_PHYNUM_MAC_COLON_NUM); ulLoop++)
    {
        lMemResult = memcpy_s(&aucMac[ulMacOffset],
                              AT_PHYNUM_MAC_LEN + 1 - ulMacOffset,
                              &aucE5GwMacAddr[ulE5GwMacAddrOffset],
                              AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        TAF_MEM_CHK_RTN_VAL(lMemResult, AT_PHYNUM_MAC_LEN + 1 - ulMacOffset, AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        ulMacOffset         += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        ulE5GwMacAddrOffset += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS + VOS_StrLen(":");
    }

    aucMac[AT_PHYNUM_MAC_LEN] = '\0';

    return AT_OK;
}


VOS_UINT32 AT_QryPhyNumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    TAF_SVN_DATA_STRU                   stSvn;
    VOS_UINT8                           aucAsciiSvn[TAF_SVN_DATA_LENGTH + 1];
    VOS_UINT8                           aucMac[AT_PHYNUM_MAC_LEN + 1]; /* MAC????*/
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;


    memset_s(&stSvn, sizeof(stSvn), 0x00, sizeof(stSvn));


    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("AT_QryPhyNumPara: Get modem id fail.");
        return AT_ERROR;
    }

    /* ????NV??????IMEI */
    ulRet = AT_GetImeiValue(enModemId, aucAsciiImei);

    if (ulRet != VOS_OK)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
        return AT_ERROR;
    }

    /* ????NV??????SVN */
    ulRet = TAF_ACORE_NV_READ(enModemId, en_NV_Item_Imei_Svn, &stSvn, sizeof(stSvn));
    if (ulRet != NV_OK)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }
    else
    {
        if (stSvn.ucActiveFlag != NV_ITEM_ACTIVE)
        {
            /* nv????????????????????'0' */
            memset_s(aucAsciiSvn, sizeof(aucAsciiSvn), '0', TAF_SVN_DATA_LENGTH);
        }
        else
        {
            AT_DeciDigit2Ascii(stSvn.aucSvn, TAF_SVN_DATA_LENGTH, aucAsciiSvn);
        }

        aucAsciiSvn[TAF_SVN_DATA_LENGTH] = '\0';
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:IMEI,%s%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucAsciiImei, gaucAtCrLf);

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_SUPPORT )
    {
        ulRet = AT_GetPhynumMac(aucMac);
        if (ulRet != AT_OK)
        {
            AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
            return AT_ERROR;
        }

        /* MAC???????? */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:SVN,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       aucAsciiSvn);


    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

#if (FEATURE_RSTRIGGER_SMS == FEATURE_ON)

VOS_UINT32 AT_WriteActiveMessage(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo
)
{
    errno_t                             lMemResult;
    VOS_UINT32                          ulRet;
    VOS_INT32                           lRet;
    VOS_UINT8                          *pucActiveMessageInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucEvaluate = VOS_NULL_PTR;

    /*1.??????????????????????????NVIM??????????????????????????????NVIM????????*/
    if (pstOrgActiveMessageInfo->enActiveStatus == pstActiveMessageInfo->enActiveStatus)
    {
        if (pstOrgActiveMessageInfo->stUrl.ulLen == pstActiveMessageInfo->stUrl.ulLen)
        {
            if (pstOrgActiveMessageInfo->enMsgCoding == pstActiveMessageInfo->enMsgCoding)
            {
                lRet = VOS_MemCmp(pstOrgActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.ulLen);
                if (lRet == 0)
                {
                    return MN_ERR_NO_ERROR;
                }
            }
        }
    }

    /*2.????????????????NVIM??*/
    /*2.1 ??NVIM????????????????????*/
    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (pucActiveMessageInfo == VOS_NULL_PTR)
    {
        return MN_ERR_NOMEM;
    }

    /*2.2 ????????????????????????????NVIM????????????*/
    pucEvaluate  = pucActiveMessageInfo;
    *pucEvaluate = pstActiveMessageInfo->enActiveStatus;
    pucEvaluate++;

    *pucEvaluate = pstActiveMessageInfo->enMsgCoding;
    pucEvaluate++;

    *pucEvaluate = (VOS_UINT8)(pstActiveMessageInfo->stUrl.ulLen & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 8) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 16) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 24) & 0xff);
    pucEvaluate++;

    lMemResult = memcpy_s(pucEvaluate,
                          MN_MSG_ACTIVE_MESSAGE_PARA_LEN - 6,
                          pstActiveMessageInfo->stUrl.aucUrl,
                          (VOS_UINT16)pstActiveMessageInfo->stUrl.ulLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, MN_MSG_ACTIVE_MESSAGE_PARA_LEN - 6, (VOS_UINT16)pstActiveMessageInfo->stUrl.ulLen);

    /*2.3 ????????????????NVIM*/
    ulRet = TAF_ACORE_NV_WRITE(enModemId,
                               en_NV_Item_SMS_ActiveMessage_Para,
                               pucActiveMessageInfo,
                               MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (ulRet != NV_OK)
    {
        ulRet = MN_ERR_CLASS_SMS_NVIM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucActiveMessageInfo);
    return ulRet;
}


TAF_UINT32 AT_QryRstriggerPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT16                          usLength;
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessageInfo;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength  = 0;
    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRslt != VOS_OK)
    {
        AT_ERR_LOG("AT_SetRstriggerPara: Get modem id fail.");
        return AT_ERROR;
    }

    /*????NVIM????????????????????*/
    ulRet = AT_ReadActiveMessage(enModemId, &stActiveMessageInfo);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        AT_LOG1("AT_QryRstriggerPara: fail to get NVIM information, cause is %d",
                ulRet);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: 255,\"\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        if (stActiveMessageInfo.enActiveStatus != MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE)
        {
            stActiveMessageInfo.enActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
        }

        /*??????????????: ??????????????????URL????*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%d,\"",
                                            stActiveMessageInfo.enActiveStatus);

        usLength += (TAF_UINT16)At_PrintReportData(AT_CMD_MAX_LEN,
                                                   (TAF_INT8 *)pgucAtSndCodeAddr,
                                                   stActiveMessageInfo.enMsgCoding,
                                                   (pgucAtSndCodeAddr + usLength),
                                                   stActiveMessageInfo.stUrl.aucUrl,
                                                   (TAF_UINT16)stActiveMessageInfo.stUrl.ulLen);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"");
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
#endif


TAF_UINT32 At_QryClipPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* ?????? */
    memset_s(&para, sizeof(para), 0x00, sizeof(para));

    /* ????SsCode */
    para.SsCode = TAF_CLIP_SS_CODE;

    if(TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para) == AT_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIP_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryClirPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* ?????? */
    memset_s(&para, sizeof(para), 0x00, sizeof(para));

    /* ????SsCode */
    para.SsCode = TAF_CLIR_SS_CODE;

    if (TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId,
        0, &para) == TAF_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIR_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryColpPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* ?????? */
    memset_s(&para, sizeof(para), 0x00, sizeof(para));

    /* ????SsCode */
    para.SsCode = TAF_COLP_SS_CODE;

    para.OP_BsService = 0;

    if(TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para) == AT_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COLP_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryS0Para(TAF_UINT8 ucIndex)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstCcCtx->stS0TimeInfo.ucS0TimerLen);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS3Para
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS3Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS3);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS4Para
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS4Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS4);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS5Para
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS5Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS5);
    return AT_OK;
}

TAF_UINT32 At_QryS6Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS6);
    return AT_OK;
}

TAF_UINT32 At_QryS7Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS7);
    return AT_OK;
}

TAF_UINT32 At_QryCusdPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    memset_s(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CUSD_RPT_TYPE;

    /* ??MTA????+cusd???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

TAF_UINT32 At_QryCcwaPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCcwaType);
    return AT_OK;
}

TAF_UINT32 At_QryCpinPara(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    memset_s(&stPinData, sizeof(stPinData), 0x00, sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_QUERY;

    stPinData.PinType = TAF_SIM_NON;


    if(Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData) == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



TAF_UINT32 At_QryIccidPara(TAF_UINT8 ucIndex)
{
    /* ???????????? */
    if(Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_ICC_ID,TAF_NULL_PTR) == AT_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ICCID_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCardTypePara(TAF_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    ulResult = SI_PIH_CardTypeQuery(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("SI_PIH_CardTypeQuery: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARDTYPE_QUERY;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCardTypeExPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    ulResult = SI_PIH_CardTypeExQuery(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("SI_PIH_CardTypeQuery: At_QryCardTypeExPara fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARDTYPEEX_QUERY;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryPNNPara (TAF_UINT8 ucIndex)
{

    return AT_OK;
}


TAF_UINT32 At_QryCPNNPara (TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_CPNN_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPNN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryOPLPara (TAF_UINT8 ucIndex)
{

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_QryCpinStatus
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---
*****************************************************************************/
TAF_UINT32 At_QryCpinStatus(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    memset_s(&stPinData, sizeof(stPinData), 0x00, sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_RemainTime;
    stPinData.PinType = TAF_SIM_NON;

    if(Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData) == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryCardlockPara
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---
*****************************************************************************/
TAF_UINT32 At_QryCardlockPara(TAF_UINT8 ucIndex)
{
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;

    memset_s(&stMePersonalisationData, sizeof(stMePersonalisationData), 0x00, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

    /* ?????????????????? */
    stMePersonalisationData.CmdType     = TAF_ME_PERSONALISATION_QUERY;
    /* ???????????????? */
    stMePersonalisationData.MePersonalType = TAF_OPERATOR_PERSONALISATION;
    /* ???????????? */
    if(Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData) == AT_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARD_LOCK_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCpin2Para(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    memset_s(&stPinData, sizeof(stPinData), 0x00, sizeof(stPinData));

    stPinData.CmdType = TAF_PIN2_QUERY;

    stPinData.PinType = TAF_SIM_NON;

    if(Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData) == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN2_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryCpbsPara(TAF_UINT8 ucIndex)
{
    gulPBPrintTag = VOS_TRUE;

    if(SI_PB_Query(gastAtClientTab[ucIndex].usClientId,0) == AT_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBS_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }

}

TAF_UINT32 At_QryCfunPara(TAF_UINT8 ucIndex)
{
    if(TAF_MMA_QryPhoneModeReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFUN_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

TAF_UINT32 At_QryCpamPara(TAF_UINT8 ucIndex)
{
    if(TAF_MMA_QryAccessModeReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPAM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif

TAF_UINT32 At_QryStsfPara(TAF_UINT8 ucIndex)
{
    USIMM_STK_CFG_STRU                  ProfileContent={0};
    TAF_UINT32                          Result ;
    TAF_UINT16                          NVLen = sizeof(USIMM_STK_CFG_STRU);
    TAF_UINT16                          Length = 0;
    MODEM_ID_ENUM_UINT16                usModemId;

    Result = TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &ProfileContent, NVLen);

    if(Result != NV_OK)
    {
        return AT_ERROR;
    }

    if (AT_GetModemIdFromClient(ucIndex, &usModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                "^STSF:%d,",
                                                ProfileContent.ucFuncEnable);

    if (AT_GetUsimInfoCtxFromModemId(usModemId)->enCardType == TAF_MMA_USIMM_CARD_USIM) {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                     (TAF_INT8 *)pgucAtSndCodeAddr,
                                                     (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                     ProfileContent.stUsimProfile.aucProfile,
                                                     TAF_MIN(ProfileContent.stUsimProfile.ucProfileLen,
                                                     sizeof(ProfileContent.stUsimProfile.aucProfile)));
    } else {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                     (TAF_INT8 *)pgucAtSndCodeAddr,
                                                     (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                     ProfileContent.stSimProfile.aucProfile,
                                                     TAF_MIN(ProfileContent.stSimProfile.ucProfileLen,
                                                     sizeof(ProfileContent.stSimProfile.aucProfile)));
    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                    ",%d",
                                                    ProfileContent.ucTimer);

    gstAtSendData.usBufLen = Length;

    return AT_OK;
}

#if ((FEATURE_PHONE_SC == FEATURE_OFF) || (defined(DMT)) || (defined(__PC_UT__)))
/*****************************************************************************
 Prototype      : At_QryStgiPara
 Description    :
 Input          : ucIndex --- ????????
 Output         :
 Return Value   : AT_XXX  --- ATC??????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryStgiPara(TAF_UINT8 ucIndex)
{
    if(g_ulSTKFunctionFlag == TAF_FALSE)
    {
        return AT_ERROR;
    }

    if(SI_STK_QuerySTKCommand(gastAtClientTab[ucIndex].usClientId,USAT_CMDQRYSTGI) == AT_SUCCESS)
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


TAF_UINT32 At_QryImsichgPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    if (SI_STKIsDualImsiSupport() == VOS_FALSE)
    {
        return AT_CMD_NOT_SUPPORT;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_IMSICHG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSICHG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCgclassPara(TAF_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"A\"");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

TAF_UINT32 At_QryCopsPara(TAF_UINT8 ucIndex)
{
    /* ????CL??????AT+COPS???????? */

    if(TAF_MMA_QryCopsInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryHplmnPara(VOS_UINT8 ucIndex)
{
    if(TAF_MMA_QryApHplmnInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EHPLMN_LIST_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


VOS_UINT32 AT_QryDplmnListPara(VOS_UINT8 ucIndex)
{
    if ( TAF_MMA_QryDplmnListReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPLMNLIST_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}



VOS_UINT32 AT_QryBorderInfoPara(VOS_UINT8 ucIndex)
{
    if ( TAF_MMA_QryBorderInfoReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_BORDERINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
#if (FEATURE_CSG == FEATURE_ON)

VOS_UINT32 At_QryCampCsgIdInfo(VOS_UINT8 ucIndex)
{
    if(TAF_MMA_QryCampCsgIdInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSG_ID_INFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}

#endif


VOS_UINT32 At_QryCgcattPara(VOS_UINT8 ucIndex)
{


    /* AT??MMA????????????????MMA????CS??PS?????????? */
    if (TAF_MMA_AttachStatusQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MMA_SERVICE_DOMAIN_CS_PS) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}

VOS_UINT32 At_QryCgattPara(VOS_UINT8 ucIndex)
{


    /* AT??MMA????????????????MMA????CS??PS?????????? */
    if (TAF_MMA_AttachStatusQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MMA_SERVICE_DOMAIN_PS) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


TAF_UINT32 AT_QryCgdnsPara(TAF_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetPdpDnsInfo(WUEPS_PID_AT,
                                        AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                        0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgautoPara(TAF_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetAnsModeInfo(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgtftPara(TAF_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetTftInfo(WUEPS_PID_AT,
                                     AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                     0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgactPara(TAF_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                             0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCgdcontPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetPrimPdpContextInfo(WUEPS_PID_AT,
                                                AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                                0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCgeqreqPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetUmtsQosInfo(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryCgeqminPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetUmtsQosMinInfo(WUEPS_PID_AT,
                                            AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                            0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_UINT32 AT_QryCgdscontPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetSecPdpContextInfo(WUEPS_PID_AT,
                                               AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                               0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCrcPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCrcType);
    return AT_OK;
}


TAF_UINT32 At_QryCbstPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->stCbstDataCfg.enSpeed,
                                                    pstSsCtx->stCbstDataCfg.enName,
                                                    pstSsCtx->stCbstDataCfg.enConnElem);

    return AT_OK;

}

TAF_UINT32 At_QryCmodPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->enCModType);
    return AT_OK;
}


TAF_UINT32 At_QryCstaPara(TAF_UINT8 ucIndex)
{

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,g_enAtCstaNumType);

    return AT_OK;
}


TAF_UINT32 At_QryCcugPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength = 0;
    TAF_UINT16                          usIndex;
    TAF_UINT16                          usInfo;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    usIndex = (TAF_UINT16)pstSsCtx->stCcugCfg.ulIndex;

    usInfo = (TAF_UINT16)((pstSsCtx->stCcugCfg.bSuppressPrefer << 1) | pstSsCtx->stCcugCfg.bSuppressOA);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSsCtx->stCcugCfg.bEnable);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usIndex);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usInfo);


    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


TAF_UINT32 At_QryCssnPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    memset_s(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CSSN_RPT_TYPE;

    /* ??MTA????^cssn???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCnmiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSmsCtx->stCnmiType.CnmiModeType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiMtType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBmType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiDsType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBfrType);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


TAF_UINT32 At_QryCmgfPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCmgfMsgFormat);

    return AT_OK;
}


VOS_UINT32 At_QryCscaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    MN_MSG_READ_COMM_PARAM_STRU         stReadParam;

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /*  ???????????????????????????????? :
    AT????????????????????????????????SIM????EFSMSP?????????????????????? */

    stReadParam.ulIndex = (VOS_UINT32)pstSmsCtx->stCscaCsmpInfo.ucDefaultSmspIndex;

    stReadParam.enMemStore  = MN_MSG_MEM_STORE_SIM;
    memset_s(stReadParam.aucReserve1, sizeof(stReadParam.aucReserve1), 0x00, sizeof(stReadParam.aucReserve1));

    /* ????????C?????????????????? */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_ReadSrvParam(gastAtClientTab[ucIndex].usClientId,
                                gastAtClientTab[ucIndex].opId,
                                &stReadParam);
    if (ulRet != MN_ERR_NO_ERROR)
    {
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCA_READ;
    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCsmsPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d,",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCsmsMsgVersion);
    At_PrintCsmsInfo(ucIndex);
    return AT_OK;
}


TAF_UINT32 At_QryCsmpPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (pstSmsCtx->stCscaCsmpInfo.bFoUsed == TAF_TRUE)
    {
        /* <fo> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstSmsCtx->stCscaCsmpInfo.ucFo);

        AT_GET_MSG_TP_VPF(enValidPeriod, pstSmsCtx->stCscaCsmpInfo.ucFo);

        /* <vp> */
        if (enValidPeriod == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            usLength += At_MsgPrintVp(&(pstSmsCtx->stCscaCsmpInfo.stVp), (pgucAtSndCodeAddr + usLength));
        }

    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    /* <pid>  <dcs> */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d,%d",
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid,
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

TAF_UINT32 At_QryCpmsPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (At_GetSmsStorage(ucIndex,
                                  pstSmsCtx->stCpmsInfo.enMemReadorDelete,
                                  pstSmsCtx->stCpmsInfo.enMemSendorWrite,
                                  pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore) != AT_OK)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMS_READ;
    return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
}


TAF_UINT32 At_QryCgsmsPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();

    ulRet                         = MN_MSG_GetSendDomain(gastAtClientTab[ucIndex].usClientId,
                                                         gastAtClientTab[ucIndex].opId);
    if (ulRet == MN_ERR_NO_ERROR)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGSMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmgdPara(TAF_UINT8 ucIndex)
{
    MN_MSG_LIST_PARM_STRU               stListPara;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    memset_s(&stListPara, sizeof(MN_MSG_LIST_PARM_STRU), 0x00, sizeof(MN_MSG_LIST_PARM_STRU));

    stListPara.bChangeFlag = VOS_FALSE;
    stListPara.enMemStore  = pstSmsCtx->stCpmsInfo.enMemReadorDelete;
    stListPara.enStatus    = MN_MSG_STATUS_NONE;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_MSG_Delete_Test(gastAtClientTab[ucIndex].usClientId,
                                         gastAtClientTab[ucIndex].opId,
                                         &stListPara) == MN_ERR_NO_ERROR)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGD_TEST;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmmsPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_GetLinkCtrl(gastAtClientTab[ucIndex].usClientId,
                               gastAtClientTab[ucIndex].opId);
    if (ulRet == MN_ERR_NO_ERROR)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if ((FEATURE_GCBS == FEATURE_ON) || (FEATURE_WCBS == FEATURE_ON))


VOS_UINT32 At_QryCscbPara(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();

    ulRet = MN_MSG_GetAllCbMids(gastAtClientTab[ucIndex].usClientId,
                             gastAtClientTab[ucIndex].opId);
    if (ulRet == MN_ERR_NO_ERROR)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCB_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


TAF_UINT32 At_QryCgregPara(TAF_UINT8 ucIndex)
{
    if (TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_PS) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if(FEATURE_LTE == FEATURE_ON)

VOS_UINT32 At_QryCeregPara(VOS_UINT8 ucIndex)
{
    if (TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_EPS) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#endif

#if (FEATURE_UE_MODE_NR == FEATURE_ON)

VOS_UINT32 At_QryC5gregPara(VOS_UINT8 ucIndex)
{
    if (TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_5GC) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_C5GREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryLendcPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ????????*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_LENDC_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryLendcPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LENDC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)
VOS_UINT32 AT_QryNrFreqLockPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ????????*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_NR_FREQLOCK_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryNrFreqLockPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NRFREQLOCK_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
#endif


VOS_UINT32 AT_QryC5gqosPara(VOS_UINT8 ucIndex)
{
    if( TAF_PS_Get5gQosInfo(WUEPS_PID_AT,
                                       AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                       0) != VOS_OK)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_C5GQOS_READ;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}




VOS_UINT32 AT_QryC5gPNssaiPara(
    VOS_UINT8                           ucIndex
)
{
    AT_MTA_5G_NSSAI_QRY_REQ_STRU        st5gNssaiQryReq;
    VOS_UINT32                          ulRslt;

    /* ?????? */
    memset_s(&st5gNssaiQryReq, sizeof(st5gNssaiQryReq), 0x00, sizeof(AT_MTA_5G_NSSAI_QRY_REQ_STRU));
    st5gNssaiQryReq.bitOpPlmn       = VOS_FALSE;
    st5gNssaiQryReq.enSNssaiQryType = AT_MTA_NSSAI_QRY_PREFER_NSSAI;

    ulRslt = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_5G_NSSAI_QRY_REQ,
                                    &st5gNssaiQryReq,
                                    (VOS_SIZE_T)sizeof(st5gNssaiQryReq),
                                    I0_UEPS_PID_MTA);

    if (ulRslt != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryC5gPNssaiPara: AT_FillAndSndAppReqMsg fail.");

        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_C5GPNSSAI_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryC5gNssaiPara(
    VOS_UINT8                           ucIndex
)
{
    AT_MTA_5G_NSSAI_QRY_REQ_STRU        st5gNssaiQryReq;
    VOS_UINT32                          ulRslt;

    /* ?????? */
    memset_s(&st5gNssaiQryReq, sizeof(st5gNssaiQryReq), 0x00, sizeof(AT_MTA_5G_NSSAI_QRY_REQ_STRU));
    st5gNssaiQryReq.bitOpPlmn       = VOS_FALSE;
    st5gNssaiQryReq.enSNssaiQryType = AT_MTA_NSSAI_QRY_DEF_CFG_NSSAI_ONLY;

    ulRslt = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_5G_NSSAI_QRY_REQ,
                                    &st5gNssaiQryReq,
                                    (VOS_SIZE_T)sizeof(st5gNssaiQryReq),
                                    I0_UEPS_PID_MTA);

    if (ulRslt != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryC5gNssaiPara: AT_FillAndSndAppReqMsg fail.");

        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_C5GNSSAI_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

#endif


VOS_UINT32 AT_QryRrcStatPara(VOS_UINT8 ucIndex)
{
    if (TAF_MMA_QryRrcStatReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RRCSTAT_QRY;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_UINT32 AT_QryTxPowerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_TXPOWER_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryTxPowerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ?????????????????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TXPOWER_QRY;
    return AT_WAIT_ASYNC_RETURN;
}

#if (FEATURE_UE_MODE_NR == FEATURE_ON)

VOS_UINT32 AT_QryNtxPowerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_NTXPOWER_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryNtxPowerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ?????????????????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NTXPOWER_QRY;
    return AT_WAIT_ASYNC_RETURN;
}
#endif


VOS_UINT32 AT_QryHfreqInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_HFREQINFO_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryHfreqinfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ?????????????????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HFREQINFO_QRY;
    return AT_WAIT_ASYNC_RETURN;
}

TAF_UINT32 At_QryCregPara(TAF_UINT8 ucIndex)
{
    if (TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_CS) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryCsdhPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucCsdhType);

    return AT_OK;
}

TAF_UINT32 At_QryCscsPara(TAF_UINT8 ucIndex)
{
    if(gucAtCscsType == AT_CSCS_IRA_CODE)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"IRA\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else if (gucAtCscsType == AT_CSCS_UCS2_CODE)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"UCS2\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"GSM\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    return AT_OK;
}


TAF_UINT32 At_QryCmeePara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,gucAtCmeeType);
    return AT_OK;
}


TAF_UINT32 At_QryParaCmd(TAF_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    if(g_stParseContext[ucIndex].pstCmdElement->pfnQryProc != TAF_NULL_PTR)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)g_stParseContext[ucIndex].pstCmdElement->pfnQryProc(ucIndex);

        if(ulResult == AT_WAIT_ASYNC_RETURN)
        {
            /* ???????? */
            if(At_StartTimer(g_stParseContext[ucIndex].pstCmdElement->ulQryTimeOut,ucIndex) != AT_SUCCESS)
            {
                AT_ERR_LOG("At_QryParaCmd:ERROR:Start Timer");
                return AT_ERROR;
            }

            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        }
        return ulResult;
    }
    else
    {
        return AT_ERROR;
    }
}

/* BEGIN: Added by liuyang id:48197, 2006/8/2   PN:A32D02883*/


TAF_UINT32 At_QryFPlmnPara(TAF_UINT8 ucIndex)
{
    if (TAF_MMA_QryFPlmnInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFPLMN_READ;           /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                         /* ???????????????? */
    }
    else
    {
        return AT_ERROR;                    /* ???????? */

    }
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 At_QryMaxFreelockSizePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C?????? MFREELOCKSIZE???? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_MFREELOCKSIZE_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("At_QryMaxFreelockSizePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MFREELOCKSIZE_READ;
    return AT_WAIT_ASYNC_RETURN;

}
#endif

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 At_QryCpuLoadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C?????? CPULOAD???? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CPULOAD_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("At_QryCpuLoadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPULOAD_READ;
    return AT_WAIT_ASYNC_RETURN;

}
#endif


VOS_UINT32 At_QryLcStartTimePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if (*pucSystemAppConfig != SYSTEM_APP_WEBUI)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_ulLcStartTime);
    return AT_OK;

}


TAF_UINT32 At_QryDialModePara(TAF_UINT8 ucIndex)
{
    VOS_UINT8   ucDialmode;
    VOS_UINT8   ucCdcSpec;
    VOS_UINT32  ulRst;

    /* ???????????????????????????????????????????????????????? */
    /* ucRst:       VOS_OK/VOS_ERR */
    /* ucDialmode:  0 - ????Modem????; 1 - ????NDIS????; 2 - Modem??NDIS???? */
    /* ucCdcSpec:   0 - Modem/NDIS??????CDC????; 1 - Modem????CDC????;
                    2 - NDIS????CDC????;         3 - Modem/NDIS??????CDC???? */


    ucDialmode = 0;
    ucCdcSpec  = 0;

    ulRst = (VOS_UINT32)DRV_GET_DIAG_MODE_VALUE(&ucDialmode, &ucCdcSpec);

    if (ulRst != VOS_OK)
    {
        AT_ERR_LOG("At_QryDialModePara:ERROR:DRV_GET_DIAG_MODE_VALUE Return Err!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucDialmode, ucCdcSpec);
    return AT_OK;
}



TAF_UINT32 At_QryPortSelPara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen =
        (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               "%s: %d",
                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                               gucAtPortSel);
    return AT_OK;
}


TAF_UINT32 At_QryCurcPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    AT_PR_LOGI("Rcv Msg");


    /* AT ??MTA ????CURC???????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_CURC_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("At_QryCurcPara: send Msg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURC_READ;

    return AT_WAIT_ASYNC_RETURN;

}


TAF_UINT32 At_QryTimePara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    memset_s(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_TIME_RPT_TYPE;

    /* ??MTA????^time???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCtzrPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    memset_s(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CTZR_RPT_TYPE;

    /* ??MTA????^ctzr???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryTimeQryPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength    = 0;
    VOS_UINT32                          ulNwSecond;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx   = VOS_NULL_PTR;
    NAS_MM_INFO_IND_STRU               *pstTimeInfo = VOS_NULL_PTR;

    pstNetCtx   = AT_GetModemNetCtxAddrFromModemId(MODEM_ID_0);
    pstTimeInfo = &(pstNetCtx->stTimeInfo);
    ulNwSecond  = pstNetCtx->ulNwSecond;

    /*????????????????C????MM INFO????????????*/
    if ((pstTimeInfo->ucIeFlg & NAS_MM_INFO_IE_UTLTZ) == NAS_MM_INFO_IE_UTLTZ)
    {
        usLength = AT_PrintNwTimeInfo(pstTimeInfo,(VOS_CHAR*)g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulNwSecond);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    /*??????????????MM INFO??????????????????C????PLMN*/
    if(TAF_MMA_QryPlmnReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TIMEQRY_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT16 AT_PrintNwTimeInfo(
    NAS_MM_INFO_IND_STRU               *pstMmInfo,
    CONST_T VOS_CHAR                   *pcCmd,
    VOS_UINT32                          ulNwSecond
)
{
    VOS_INT8                            cTimeZone;
    VOS_UINT8                           ucDST;
    VOS_UINT16                          usLength  = 0;
    NAS_MM_INFO_IND_STRU                stLocalAtTimeInfo;

    memset_s(&stLocalAtTimeInfo, sizeof(NAS_MM_INFO_IND_STRU), 0x00, sizeof(NAS_MM_INFO_IND_STRU));

    /*????????????: ^TIME: "yy/mm/dd,hh:mm:ss(+/-)tz,dst" */
    if ((pstMmInfo->ucIeFlg & NAS_MM_INFO_IE_UTLTZ) == NAS_MM_INFO_IE_UTLTZ)
    {
        AT_GetLiveTime(pstMmInfo, &stLocalAtTimeInfo, ulNwSecond);

        /*YY/MM/DD,HH:MM:SS*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d%d/%d%d/%d%d,%d%d:%d%d:%d%d",
                                           (VOS_CHAR *)pcCmd,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucYear / 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucYear % 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth / 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth % 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucDay / 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucDay % 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucHour / 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucHour % 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute / 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute % 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond / 10,
                                           stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond % 10);
        /* ???????? */
        if ((stLocalAtTimeInfo.ucIeFlg & NAS_MM_INFO_IE_LTZ) == NAS_MM_INFO_IE_LTZ)
        {
            cTimeZone = stLocalAtTimeInfo.cLocalTimeZone;
        }
        else
        {
             cTimeZone = stLocalAtTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone;
        }

        if (cTimeZone != AT_INVALID_TZ_VALUE)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%02d",
                                               (cTimeZone < 0)? "-" : "+",
                                               (cTimeZone < 0)? ( - cTimeZone) : cTimeZone);
        }

        /*??????????????????????*/
        if (((stLocalAtTimeInfo.ucIeFlg & NAS_MM_INFO_IE_DST) == NAS_MM_INFO_IE_DST) && (stLocalAtTimeInfo.ucDST > 0))
        {
            ucDST = stLocalAtTimeInfo.ucDST;
        }
        else
        {
            ucDST = 0;
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d%d",
                                           ucDST / 10, ucDST % 10);


    }
    return usLength;
}




VOS_UINT32 At_QryQuickStart(TAF_UINT8 ucIndex)
{

    AT_PR_LOGI("Rcv Msg");


    if(TAF_MMA_QryQuickStartReq(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) == VOS_TRUE)
    {
        /*???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CQST_READ;
        /* ???????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }

    else
    {
        /* ???????? */
        return AT_ERROR;
    }
}

VOS_UINT32 At_QryAutoAttach(TAF_UINT8 ucIndex)
{
    if(TAF_MMA_QryAutoAttachInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAATT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QrySysCfgExPara(VOS_UINT8 ucIndex)
{
    if (TAF_MMA_QrySyscfgReq(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFGEX_READ;             /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        return AT_ERROR;
    }

}


#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

TAF_UINT32 At_QrySysCfgPara(TAF_UINT8 ucIndex)
{

    if (TAF_MMA_QrySyscfgReq(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFG_READ;             /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}
#endif

#if(FEATURE_LTE == FEATURE_ON)

TAF_UINT32 At_QryCemode(TAF_UINT8 ucIndex)
{


    /* ??MMA???????????????????????????????????????????????????? */

    if (TAF_MMA_QryCemodeReq(WUEPS_PID_AT,
                                           AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                           0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEMODE_READ;             /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        PS_PRINTF_WARNING("<At_QryCemode> TAF_PS_GetCemodeInfo fail\n");
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryLtecsInfo(TAF_UINT8 ucIndex)
{

    if(TAF_PS_GetLteCsInfo(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0) == AT_SUCCESS)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTECS_READ;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif

VOS_UINT32 At_QryClvlPara(VOS_UINT8 ucIndex)
{
    if (APP_VC_GetVoiceVolume(gastAtClientTab[ucIndex].usClientId, 0) == VOS_OK)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLVL_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryVMSETPara(VOS_UINT8 ucIndex)
{
    /* ???????????????????????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*??????????????????????0 ??????1 ??????????2 ??????????3 ??????4 ??????5 PC???????? */
    if (APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0) == VOS_OK)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }

}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

TAF_UINT32 At_QryRRCVersion(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ????????ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ??AT???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RRC_VERSION_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


TAF_UINT32 At_QryCSNR(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? ID_AT_MTA_WRR_ANQUERY_QRY_REQ ?? MTA ???? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_CSNR_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNR_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

TAF_UINT32 At_QryFreqLock(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ????????ID_AT_MTA_WRR_FREQLOCK_QRY_REQ??AT???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_FREQLOCK_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FREQLOCK_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
#endif
#if (FEATURE_PROBE_FREQLOCK == FEATURE_ON)

TAF_UINT32 At_QryM2MFreqLock(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ????????ID_AT_MTA_QRY_M2M_FREQLOCK_REQ??AT???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_M2M_FREQLOCK_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_M2M_FREQLOCK_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


TAF_UINT32 At_QryU2DiagPara(TAF_UINT8 ucIndex)
{
    AT_USB_ENUM_STATUS_STRU             stUsbEnumStatus;
    nv_pid_enable_type                  stPidEnableType;


    stPidEnableType.ulPidEnabled = VOS_FALSE;

    memset_s(&stUsbEnumStatus, sizeof(stUsbEnumStatus), 0x00, sizeof(stUsbEnumStatus));


    /* ????PID????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_PID_Enable_Type,
                                   &stPidEnableType,
                                   sizeof(nv_pid_enable_type)) != NV_OK)
    {
        return AT_ERROR;
    }

    /* NV??????????????PID??????????????????????ERROR */
    if (stPidEnableType.ulPidEnabled != VOS_FALSE)
    {
        return AT_ERROR;
    }

    if(TAF_ACORE_NV_READ(MODEM_ID_0,
                                  en_NV_Item_USB_Enum_Status,
                                  &stUsbEnumStatus,
                                  sizeof(AT_USB_ENUM_STATUS_STRU)) != NV_OK)
    {
        return AT_ERROR;
    }

    if (stUsbEnumStatus.ulStatus == 0)
    {
        /* ??en_NV_Item_USB_Enum_Status????????????????????API????????????USB???????? */
        stUsbEnumStatus.ulValue = DRV_GET_U2DIAG_DEFVALUE();
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stUsbEnumStatus.ulValue);
    return AT_OK;
}


VOS_UINT32 At_QryPort(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucCount;
    VOS_UINT32                          ulResult;
    DRV_DYNAMIC_PID_TYPE_STRU           stDynamicPidType;
    nv_pid_enable_type                  stPidEnableType;

    usLength = 0;
    ucCount  = 0;


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    memset_s(&stDynamicPidType, sizeof(stDynamicPidType), 0x00, sizeof(DRV_DYNAMIC_PID_TYPE_STRU));

    /* ????PID????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_PID_Enable_Type,
                                   &stPidEnableType,
                                   sizeof(nv_pid_enable_type)) != NV_OK)
    {
        AT_ERR_LOG("At_QryPort:Read NV fail!");
        return AT_ERROR;
    }

    /* NV??????????????PID????????????????????????ERROR */
    if (stPidEnableType.ulPidEnabled != VOS_TRUE)
    {
        AT_WARN_LOG("At_QryPort:The PID is not enabled!");
        return AT_ERROR;
    }

    /* ???????????????? */
    ulResult = DRV_SET_PORT_QUIRY(&stDynamicPidType);
    if (ulResult != AT_SUCCESS)
    {
        AT_ERR_LOG("At_QryPort:Qry the pot type fail!");
        return AT_ERROR;
    }

    /* ^SETPORT: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* OLD PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_MAP_LEN; j++)
        {
            if (stDynamicPidType.aucFirstPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* ????1????????????????: */
                if (ucCount > 0)
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /* ???? */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;
                break;
            }
        }
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    ";");

    ucCount = 0;

    /* CUR PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_LEN; j++)
        {
            if (stDynamicPidType.aucRewindPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* ????1????????????????: */
                if (ucCount > 0)
                {
                    /* ???????? */
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /* ???? */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;

                break;
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


TAF_UINT32 At_QryPcscInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulPortState;

    /*PCSC ????????????, 0 ????; 1 ????*/
    if (AT_ExistSpecificPort(AT_DEV_PCSC) == VOS_TRUE)
    {
        ulPortState = VOS_TRUE;
    }
    else
    {
        ulPortState = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulPortState);
    return AT_OK;
}


VOS_UINT32 At_QryCellSearch(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? ID_AT_MTA_WRR_CELLSRH_QRY_REQ ?? DRV AGENT ?????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_WRR_CELLSRH_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAS_MNTN_QRY_CELLSRH;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



TAF_UINT32 At_QryGetportmodePara (TAF_UINT8 ucIndex)
{
     /*????????????????ERROR*/
     return AT_ERROR;
}


VOS_UINT32 At_QryCvoicePara (VOS_UINT8 ucIndex)
{
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*??????????????????????0 ??????1 ??????????2 ??????????3 ??????4 ???? */
    if (APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0) == VOS_OK)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }

}



VOS_UINT32 At_QryDdsetexPara(VOS_UINT8 ucIndex)
{
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (APP_VC_GetVoicePort(gastAtClientTab[ucIndex].usClientId, 0) == VOS_OK)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmsrPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucParaCmsr);
    return AT_OK;
}



TAF_UINT32 At_QryUssdModePara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* 0??USSD??????????????????????USSD????????????1??USSD??????????????????????USSD????????????????????)*/
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->usUssdTransMode);

    return AT_OK;
}


TAF_UINT32 At_QryAdcTempPara(TAF_UINT8 ucIndex)
{
    SPY_TEMP_PROTECT_NV_STRU stTempProtectNv;


    memset_s(&stTempProtectNv, sizeof(stTempProtectNv), 0x00, sizeof(stTempProtectNv));


    /*??????????????????NV??*/
    if(TAF_ACORE_NV_READ(MODEM_ID_0,
                                  en_NV_Item_USIM_TEMP_PROTECT_NEW,
                                  (VOS_VOID*)&stTempProtectNv,
                                  sizeof(SPY_TEMP_PROTECT_NV_STRU)) != NV_OK)
    {
        AT_ERR_LOG("Spy_SetTempPara: TAF_ACORE_NV_READ en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr,
                                                "^ADCTEMP: %d,%d,%d,%d",
                                                stTempProtectNv.ulIsEnable,
                                                stTempProtectNv.lCloseAdcThreshold,
                                                stTempProtectNv.lAlarmAdcThreshold,
                                                stTempProtectNv.lResumeAdcThreshold);

    return AT_OK;
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

TAF_UINT32 At_QryCommDebugPara(TAF_UINT8 ucIndex)
{
    TAF_AT_NVIM_COMMDEGBUG_CFG_STRU     stDebugFlag;


    stDebugFlag.ulCommDebugFlag = 0;

    if(TAF_ACORE_NV_READ(MODEM_ID_0,
                                  en_NV_Item_COMMDEGBUG_CFG,
                                  (VOS_VOID*)&(stDebugFlag.ulCommDebugFlag),
                                  sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)) != NV_OK)
    {
        AT_ERR_LOG("At_QryOamDebugPara: TAF_ACORE_NV_READ en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "^COMM: 0x%X", stDebugFlag.ulCommDebugFlag);

    return AT_OK;
}
#endif

TAF_UINT32 At_QryDwinsPara(TAF_UINT8 ucIndex)
{
    WINS_CONFIG_STRU                    stWins;


    memset_s(&stWins, sizeof(stWins), 0x00, sizeof(stWins));

    if(TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, sizeof(WINS_CONFIG_STRU)) != NV_OK)
    {
        return AT_ERROR;
    }

    if (stWins.ucStatus == 0)
    {
        /* ??en_NV_Item_WINS??????????????WINS?????????? */
        stWins.ucWins = WINS_CONFIG_ENABLE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stWins.ucWins);
    return AT_OK;
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

TAF_UINT32 At_QryYjcxPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ????DRV_AGENT_YJCX_QRY_REQ??????AT???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_YJCX_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (ulRst == VOS_OK)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_YJCX_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
#endif


VOS_UINT32 At_QryCplsPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstNetCtx->enPrefPlmnType);

    return AT_OK;

}


TAF_UINT32 At_QryCpolPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /*
    AT??MMA??????????????:
    ????????????????????????????????????????????????????????????????37????????????
    ??????????????????????0??????????????37????????????
    */
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    memset_s(&stCpolInfo, sizeof(stCpolInfo), 0x00, sizeof(stCpolInfo));

    stCpolInfo.enPrefPLMNType   = pstNetCtx->enPrefPlmnType;
    stCpolInfo.ulFromIndex      = 0;

    stCpolInfo.ulPlmnNum        = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;

    /* ??MMA???????????????????? */
    ulRet = TAF_MMA_QueryCpolReq(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0,
                                 &stCpolInfo);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }


    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_READ;

    return AT_WAIT_ASYNC_RETURN;

}


TAF_UINT32 AT_QryAuthdataPara(TAF_UINT8 ucIndex)
{
    if ( TAF_PS_GetAuthDataInfo(WUEPS_PID_AT,
                                          AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                          0) != VOS_OK )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryIpv6CapPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucIpv6Capability;

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;
            break;

        default:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucIpv6Capability);
    return AT_OK;
}


TAF_UINT32 At_QryCrpnPara(TAF_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_QryAlsPara( TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;
    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /*????TAF_CS_ALS_LINE_NO_QRY??????CCM????CCM??????????????????*/
    ulRst = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_QRY_ALS_REQ,
                                  0,
                                  enModemId);

    if(ulRst == VOS_OK)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_QRY_ALS_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
                    VOS_UINT16 usCurBandSwitch,
                    VOS_UINT32 *pulUserDivBandsLow,
                    VOS_UINT32 *pulUserDivBandsHigh
                    )
{
    *pulUserDivBandsLow      = 0;
    *pulUserDivBandsHigh     = 0;

    /*??????????????????????????:
        0x80000            GSM850
        0x300              GSM900
        0x80               DCS1800
        0x200000           PCS1900
        0x400000           WCDMA2100
        0x800000           WCDMA1900
        0x1000000          WCDMA1800
        0x2000000          WCDMA_AWS
        0x4000000          WCDMA850
        0x2000000000000    WCDMA900
        0x4000000000000    WCDMA1700
      ??MS??????????????????????:
        2100M/ bit1  1900M/bit2  1800M/bit3  1700M/bit4  1600M/bit5
        1500M/bit6   900M/bit7   850M/bit8   800M/bit9   450M/bit10
      ??????????????????????????????MS??????????
    */
    if ((usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_900) != 0)
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_VIII_900;
    }
    if ((usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_IX_1700) != 0)
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_IX_1700;
    }
    if ((usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_2100) != 0)
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_I_IMT_2100;
    }
    if ((usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1900) != 0)
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_II_PCS_1900;
    }
    if ((usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1800) != 0)
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_III_1800;
    }
    if ((usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_850) != 0)
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_V_850;
    }

    return;
}


VOS_UINT32 At_QryRxDiv(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ????????DRV_AGENT_HARDWARE_QRY??DRV AGENT?????????????????????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_RXDIV_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_RXDIV_QRY_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}


VOS_UINT32 At_QryCuus1Para(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????????????ID_TAF_CCM_QRY_CLPR_REQ??C?? */
    ulRst = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_QRY_UUSINFO_REQ,
                                  0,
                                  enModemId);

    if (ulRst == MN_ERR_NO_ERROR)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_SET_UUSINFO_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_UINT32 At_QryApHplmn( VOS_UINT8  ucIndex )
{
    if(TAF_MMA_QryApHplmnInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HOMEPLMN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryAnQuery( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    /* ???????? ID_AT_MTA_WRR_ANQUERY_QRY_REQ ?? MTA ???? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_ANQUERY_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANQUERY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


AT_CMD_ANTENNA_LEVEL_ENUM_UINT8 AT_CalculateAntennaLevel(
    VOS_INT16                           sRscp,
    VOS_INT16                           sEcio
)
{
    VOS_UINT16                          usRscp;
    VOS_UINT16                          usEcio;
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enRlstAntennaLevel;

/* RSCP and ECIO different Thresholds variables */
   VOS_INT32                            alRscpThreshold[AT_ANTEN_LEV_MAX_NUM] = {125, 108, 102, 96} ;
   VOS_INT32                            alEcioThreshold[AT_ANTEN_LEV_MAX_NUM] = {30, 16, 13, 10};

#if(FEATURE_LTE == FEATURE_ON)

    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    if ( *pucSystemAppConfig == SYSTEM_APP_WEBUI)
    {
        /* ???????? */
        usRscp                    = (VOS_UINT16)-sRscp;
        usEcio                    = (VOS_UINT16)-sEcio;

        /* 3 level of Signal */
        if ( (usEcio <= g_stEcioCfg.ssValue[3])
          && (usRscp <= g_stRscpCfg.ssValue[3]))
        {
            enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
        }
        /* 2 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[2]) && (usEcio > g_stEcioCfg.ssValue[3])
               && (usRscp <= g_stRscpCfg.ssValue[2]))
              || ((usRscp <= g_stRscpCfg.ssValue[2]) && (usRscp > g_stRscpCfg.ssValue[3])
               && (usEcio < g_stEcioCfg.ssValue[2])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
        }
        /* 1 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[1]) && (usEcio > g_stEcioCfg.ssValue[2])
               && (usRscp <= g_stRscpCfg.ssValue[1]))
              || ((usRscp <= g_stRscpCfg.ssValue[1]) && (usRscp > g_stRscpCfg.ssValue[2])
               && (usEcio < g_stEcioCfg.ssValue[1])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
        }
        else
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
        }
        return enRlstAntennaLevel;
    }
#endif

    enRlstAntennaLevel        = 0;

    /* ???????? */
    usRscp                    = (VOS_UINT16)-sRscp;
    usEcio                    = (VOS_UINT16)-sEcio;

    /* 3 level of Signal */
    if ( (usEcio <= alEcioThreshold[3])
      && (usRscp <= alRscpThreshold[3]))
    {
        enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
    }
    /* 2 level of Signal */
    else if (((usEcio <= alEcioThreshold[2]) && (usEcio > alEcioThreshold[3])
           && (usRscp <= alRscpThreshold[2]))
          || ((usRscp <= alRscpThreshold[2]) && (usRscp > alRscpThreshold[3])
           && (usEcio < alEcioThreshold[2])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
    }
    /* 1 level of Signal */
    else if (((usEcio <= alEcioThreshold[1]) && (usEcio > alEcioThreshold[2])
           && (usRscp <= alRscpThreshold[1]))
          || ((usRscp <= alRscpThreshold[1]) && (usRscp > alRscpThreshold[2])
           && (usEcio < alEcioThreshold[1])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
    }
    else
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
    }

    return enRlstAntennaLevel;

}

VOS_VOID AT_GetSmoothAntennaLevel(
    VOS_UINT8                           ucIndex,
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
)
{
    VOS_UINT8                               i;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* ?????? ????????  */
    if ( enLevel == AT_CMD_ANTENNA_LEVEL_0 )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        memset_s( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        return;
    }

    /* ????????????????  ????????  */
    if ( pstNetCtx->enCalculateAntennaLevel == AT_CMD_ANTENNA_LEVEL_0 )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        memset_s( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }

    /* ????????????????????, ??????????(????1??)?????????? */
    if ( enLevel > (pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] + 1) )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        memset_s( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else if (( enLevel + 1) < pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        memset_s( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else
    {
      /* Do nothing... */
    }


    /* ??????????????3???????????? */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM-1; i++ )
    {
         pstNetCtx->aenAntennaLevel[i] = pstNetCtx->aenAntennaLevel[i+1];
    }
    pstNetCtx->aenAntennaLevel[i] = enLevel;


    /* ?????????????????????????????????? */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM; i++ )
    {
        if ( pstNetCtx->enCalculateAntennaLevel == pstNetCtx->aenAntennaLevel[i] )
        {
            return;
        }
    }

    /* ?????????????? AT_ANTENNA_LEVEL_MAX_NUM ???????????? */
    pstNetCtx->enCalculateAntennaLevel = enLevel;
}


#if (FEATURE_LTE == FEATURE_ON)

TAF_VOID AT_CalculateLTESignalValue(
                                              VOS_INT16    *psRssi,
                                              VOS_UINT8    *pusLevel,
                                              VOS_INT16    *psRsrp,
                                              VOS_INT16    *psRsrq

)
{
        VOS_UINT8                           enCurAntennaLevel;
        VOS_INT16                           sRsrp;
        VOS_INT16                           sRsrq;

        /* ?? atSetAnlevelCnfSameProc????????*/
        /* ????????????:?? Rscp??Ecio????????????????Rscp??Ecio??-145??-32??????rssi??99??
        ????????0 */
        if ( (*psRsrp == TAF_PH_RSSIUNKNOW)
          || (*psRssi == TAF_PH_RSSIUNKNOW) )
        {
            /* ????????0, ?????????????? */
            enCurAntennaLevel       = AT_CMD_ANTENNA_LEVEL_0;
        }
        else
        {
            /* ???????? */
            sRsrp            = (-(*psRsrp));

            /* ????????AT_CalculateAntennaLevel??????D25?????????????????? */
            enCurAntennaLevel = AT_CalculateLTEAntennaLevel((VOS_INT16)(sRsrp));
        }

        /* ???????????? */
        *pusLevel = AT_GetSmoothLTEAntennaLevel(enCurAntennaLevel);



        if(*psRssi == AT_RSSI_UNKNOWN)
        {
            *psRssi = AT_RSSI_UNKNOWN;
        }
        else if(*psRssi >= AT_RSSI_HIGH)
        {
            *psRssi = AT_CSQ_RSSI_HIGH;
        }
        else if(*psRssi <= AT_RSSI_LOW)
        {
            *psRssi = AT_CSQ_RSSI_LOW;
        }
        else
        {
            *psRssi = ( VOS_INT16)((*psRssi - AT_RSSI_LOW) / 2);
        }

        sRsrp = (*psRsrp == 99)?99:(-(*psRsrp));
        sRsrq = (*psRsrq == 99)?99:(-(*psRsrq));

        *psRsrp = sRsrp;
        *psRsrq = sRsrq;

        return;

}
#endif




TAF_UINT32 At_QryGlastErrPara( TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* ??????????????????*/
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       gulErrType);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryTModePara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* ????????TMODE?????????? */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       1);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
#if (FEATURE_LTEV == FEATURE_ON)

TAF_UINT32 At_QryVModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ????????ID_AT_MTA_VMODE_QRY_REQ??AT???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_VMODE_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMODE_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }


}
#endif



TAF_UINT32  At_QryPlatForm(TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    NAS_NVIM_PLATFORM_STRU              stPlatform;



    stPlatform.usPlatform = 0;

    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_SubPlatFormInfo, &stPlatform.usPlatform, sizeof(stPlatform.usPlatform));
    if (ulRet != NV_OK)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    1,
                                                    stPlatform.usPlatform);

    return AT_OK;

}

VOS_UINT32  At_QryDataLock(VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_bAtDataLocked);

    return AT_OK;

}

VOS_UINT32  At_QrySD(VOS_UINT8 ucIndex )
{

    VOS_UINT32                          ulCurrentOprtStaus;

    ulCurrentOprtStaus = mdrv_sd_get_opptstatus();

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulCurrentOprtStaus);
    return AT_OK;
}

VOS_UINT32  At_DelCtlAndBlankCharWithEndPadding(
    VOS_UINT8                               *pucData,
    VOS_UINT16                              *pusCmdLen
)
{

    VOS_UINT16                          usOrigLen;
    errno_t                             lMemResult;

    usOrigLen = *pusCmdLen;

    /* ?????????? */
    if(At_ScanCtlChar(pucData, pusCmdLen) == AT_FAILURE)
    {
        return AT_FAILURE;
    }

    /* ???????????????????? */
    if(At_ScanBlankChar(pucData, pusCmdLen) == AT_FAILURE)
    {
        return AT_FAILURE;
    }

    lMemResult = memset_s(pucData + (*pusCmdLen), (VOS_SIZE_T)(usOrigLen - (*pusCmdLen)), 0x00, (VOS_SIZE_T)(usOrigLen - (*pusCmdLen)));
    TAF_MEM_CHK_RTN_VAL(lMemResult, usOrigLen - (*pusCmdLen), usOrigLen - (*pusCmdLen));

    return AT_SUCCESS;

}

VOS_UINT32  At_QryVersion(VOS_UINT8 ucIndex )
{

    AT_PR_LOGI("Rcv Msg");

    if(AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                            gastAtClientTab[ucIndex].opId,
                                            DRV_AGENT_VERSION_QRY_REQ,
                                            VOS_NULL_PTR,
                                            0,
                                            I0_WUEPS_PID_DRV_AGENT) == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VERSION_QRY;

        AT_PR_LOGI("Snd Msg");
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}



VOS_UINT32  At_QryBsn(VOS_UINT8 ucIndex )
{
    /* ????????????16,?????????????????????? */
    VOS_UINT8                            aucBsnSerialNum[17];
    VOS_UINT16                           usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;

    /* ???????? */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = sizeof(aucBsnSerialNum);

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("At_SetSDomainPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (TAF_ACORE_NV_READ(enModemId, en_NV_Item_ManufactureInfo, aucBsnSerialNum, usLength) != NV_OK)
    {
        AT_WARN_LOG("At_QryBsn:WARNING:NVIM Read en_NV_Item_Serial_Num falied!");
        return AT_ERROR;
    }
    else
    {
        aucBsnSerialNum[16]=0;/*??????????????????????'\0'*/
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s:",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",aucBsnSerialNum);
    }
    gstAtSendData.usBufLen = usLength;
    return AT_OK;

}

VOS_UINT32  At_QryCsVer(VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;


    stCsver.usCsver = 0;

    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_Csver, &stCsver, sizeof(VOS_UINT16));
    if (ulRet != NV_OK)
    {
        return AT_ERROR;
    }

   gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   stCsver.usCsver);

    return AT_OK;
}

VOS_UINT32  At_QryQosPara(VOS_UINT8 ucIndex )
{
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     stATTrafficClass;
    VOS_UINT16                          usReadLength;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;


    stATTrafficClass.ucStatus       = NV_ITEM_DEACTIVE;
    stATTrafficClass.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_SUBSCRIBE;


    /*????????????????*/
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*????NV????????stATTrafficClass??????????*/
    usReadLength = sizeof(stATTrafficClass);

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("At_QryQosPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (TAF_ACORE_NV_READ(enModemId, en_NV_Item_TRAFFIC_CLASS_Type, &stATTrafficClass, usReadLength) != NV_OK)
    {
        AT_WARN_LOG("At_QryQosPara:WARNING:NVIM Read en_NV_Item_TRAFFIC_CLASS_Type failed!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /*NV????????????,??????????????:AT_QOS_TRAFFIC_CLASS_INTERACTIVE*/
    if (stATTrafficClass.ucStatus == NV_ITEM_DEACTIVE)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_QOS_TRAFFIC_CLASS_SUBSCRIBE);


    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                         stATTrafficClass.ucTrafficClass);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32   At_QrySDomainPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;


    memset_s(&stMsClass, sizeof(stMsClass), 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = TAF_PH_MS_CLASS_A;

    /*????????????????*/
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*????NV*/
    usLength = sizeof(TAF_PH_MS_CLASS_TYPE);

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("At_QrySDomainPara: Get modem id fail.");
        return AT_ERROR;
    }
    if (TAF_ACORE_NV_READ(enModemId, en_NV_Item_MMA_MsClass, &stMsClass, sizeof(NAS_NVIM_MS_CLASS_STRU)) != NV_OK)
    {
        AT_WARN_LOG("At_QrySDomainPara:WARNING:NVIM Read en_NV_Item_MMA_MsClass failed!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /*??????NV????????MsClass??*/
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName, stMsClass.ucMsClass);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32   At_QryGPIOPL(VOS_UINT8 ucIndex)
{
    if (AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_GPIOPL_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT) == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GPIOPL_QRY;             /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryMDatePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    TAF_AT_NVIM_MANUFACTURE_DATE_STRU   stManufactrueDate;

    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_AT_MANUFACTURE_DATE,
                              &stManufactrueDate,
                              AT_MDATE_STRING_LENGTH);
    if (ulRet != NV_OK)
    {
        AT_WARN_LOG("AT_QryMDatePara: fail to read NVIM . ");
        return AT_ERROR;
    }

    /*??????????????: ????????????????????*/
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    stManufactrueDate.aucMDate[AT_MDATE_STRING_LENGTH - 1] = '\0';
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       stManufactrueDate.aucMDate);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryFacInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucFacInfo = TAF_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ????NV???????????????????? */
    pucFacInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FACINFO_STRING_LENGTH);
    if (pucFacInfo == VOS_NULL_PTR)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to alloc memory.");
        return AT_ERROR;
    }

    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_AT_FACTORY_INFO,
                              pucFacInfo,
                              AT_FACINFO_STRING_LENGTH);
    if (ulRet != NV_OK)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to read en_NV_Item_AT_FACTORY_INFO . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    /* ????????????????NV??INFO????????????*/
    *(pucFacInfo + (AT_FACINFO_STRING_LENGTH - 1))     = '\0';
    *(pucFacInfo + AT_FACINFO_INFO1_LENGTH)            = '\0';

    /* ??????????????: ?????????????????????? */
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:0,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pucFacInfo);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    /* ??????????????: ?????????????????????? */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:1,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       ((pucFacInfo + AT_FACINFO_INFO1_LENGTH) + 1));

    gstAtSendData.usBufLen = usLength;

    PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
    return AT_OK;
}


VOS_UINT32  At_ReadDpaCatFromNV(VOS_UINT8 *pucDpaRate)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    AT_DPACAT_PARA_STRU                 astDhpaCategory[AT_DPACAT_CATEGORY_TYPE_BUTT] = {
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_6,  PS_FALSE, 0, PS_FALSE},                                                           /* ????????????3.6M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_8,  PS_FALSE, 0, PS_FALSE},                                                           /* ????????????7.2M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_11, PS_FALSE, 0, PS_FALSE},                                                           /* ????????????1.8M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_FALSE, 0, PS_FALSE},                                                          /*  ????????????14.4M */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_TRUE,  AT_HSDSCH_PHY_CATEGORY_14, PS_FALSE}};           /*  ????????????21M */
    VOS_UINT8                           ucLoop;


    memset_s(&stUECapa, sizeof(stUECapa), 0x00, sizeof(stUECapa));


    /* ??????????????????*/
    if ( pucDpaRate == VOS_NULL_PTR )
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV: null PTR.");
        return VOS_ERR;
    }

    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_WAS_RadioAccess_Capa_New,
                                   &stUECapa,
                                   sizeof(AT_NVIM_UE_CAPA_STRU)) != NV_OK)
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV():en_NV_Item_WAS_RadioAccess_Capa NV Read Fail!");
        return VOS_ERR;
    }

    for (ucLoop = 0; ucLoop < AT_DPACAT_CATEGORY_TYPE_BUTT; ucLoop++)
    {
        if ((stUECapa.enHSDSCHSupport        == astDhpaCategory[ucLoop].enHSDSCHSupport)
         && (stUECapa.ucHSDSCHPhyCategory    == astDhpaCategory[ucLoop].ucHSDSCHPhyCategory)
         && (stUECapa.enMacEhsSupport        == astDhpaCategory[ucLoop].enMacEhsSupport)
         && (stUECapa.ucHSDSCHPhyCategoryExt == astDhpaCategory[ucLoop].ucHSDSCHPhyCategoryExt)
         && (stUECapa.enMultiCellSupport     == astDhpaCategory[ucLoop].enMultiCellSupport))
        {
            *pucDpaRate = ucLoop;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)


VOS_UINT32   At_QryDpaCat(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDpaRate;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ??????NV????????: At_ReadDpaCatFromNV,???????????? */
    ulWasResult = At_ReadDpaCatFromNV(&ucDpaRate);
    if (ulWasResult == VOS_OK)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucDpaRate);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_QryDpaCat:WARNING:WAS_MNTN_QueryDpaCat failed!");
        return AT_ERROR;
    }
}
#endif

VOS_UINT32 AT_ReadRrcVerFromNV(VOS_UINT8 *pucRrcVer)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;


    memset_s(&stUECapa, sizeof(stUECapa), 0x00, sizeof(stUECapa));


    /* ?????????????????? */
    if (pucRrcVer == VOS_NULL_PTR)
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: null PTR.");
        return VOS_ERR;
    }

    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_WAS_RadioAccess_Capa_New,
                                   &stUECapa,
                                   sizeof(AT_NVIM_UE_CAPA_STRU)) != NV_OK)
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: TAF_ACORE_NV_READ en_NV_Item_WAS_RadioAccess_Capa_New fail!");
        return VOS_ERR;
    }

    /* NV?????? */
    if (stUECapa.ulHspaStatus == VOS_FALSE)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
        return VOS_OK;
    }

    /* NV???? */
    /* HSPA+ */
    if ((stUECapa.enAsRelIndicator >= AT_PTL_VER_ENUM_R7)
     && (stUECapa.enEDCHSupport == VOS_TRUE)
     && (stUECapa.enHSDSCHSupport == VOS_TRUE))
    {
        *pucRrcVer = AT_RRC_VERSION_HSPA_PLUNS;
    }
    /* DPA/UPA */
    else if((stUECapa.enEDCHSupport == VOS_TRUE)
         && (stUECapa.enHSDSCHSupport == VOS_TRUE))
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
    }
    /* DPA */
    else if(stUECapa.enHSDSCHSupport == VOS_TRUE)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA;
    }
    /* WCDMA */
    else
    {
        *pucRrcVer = AT_RRC_VERSION_WCDMA;
    }


    return VOS_OK;
}



VOS_UINT32   AT_QryHspaSpt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_DPAUPA_ERROR;
    }

    ulWasResult = AT_ReadRrcVerFromNV(&ucRRCVer);

    if (ulWasResult == VOS_OK)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucRRCVer);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_QryHspaSpt:WARNING:WAS_MNTN_QueryHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }
}


VOS_UINT32 At_QryCallSrvPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              stCustSrv;
    VOS_UINT16                          usLength;


    stCustSrv.ulStatus           = NV_ITEM_DEACTIVE;
    stCustSrv.ulCustomizeService = 0;


    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_CustomizeService, &stCustSrv, sizeof(stCustSrv)) != NV_OK)
    {
        AT_WARN_LOG("At_QryCallSrvPara():en_NV_Item_CustomizeService NV Read Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ????NV????????????????????????FALSE */
    if (stCustSrv.ulStatus == NV_ITEM_DEACTIVE)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          VOS_FALSE);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stCustSrv.ulCustomizeService);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 At_QryCsdfltPara(VOS_UINT8 ucIndex)
{

    /* ????????C??????SIMLOCK ???????? */
    if(Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    TAF_PH_SIMLOCK_VALUE_PARA,
                                    TAF_NULL_PTR) != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSDFLT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_JudgeU8ArrayZero(
    VOS_UINT8                           aucValue[],
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (aucValue[ulLoop] != 0)
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 AT_GetWifiNvValue(VOS_UINT16 *pusCsdValue)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiKey;
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLoop;

    /* ??????WIFI??????WIFI??NV???????????????????????? */
    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT)
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
        return VOS_OK;
    }

    memset_s(&stWifiKey, sizeof(stWifiKey), 0x00, sizeof(stWifiKey));
    memset_s(&stWifiSsid, sizeof(stWifiSsid), 0x00, sizeof(stWifiSsid));

    /* ????en_NV_Item_WIFI_KEY????????????????????????????????0:
       aucWifiWpapsk aucWifiWepKey1 aucWifiWepKey2 aucWifiWepKey3 aucWifiWepKey4 */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)) != NV_OK)
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    /* ????en_NV_Item_WIFI_STATUS_SSID????????????????????????????????0:
        aucWifiSsid
    */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)) != VOS_OK)
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWpapsk[ulLoop], sizeof(stWifiKey.aucWifiWpapsk[ulLoop]));
        if (ulRet != VOS_OK)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey1[ulLoop], sizeof(stWifiKey.aucWifiWepKey1[ulLoop]));
        if (ulRet != VOS_OK)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey2[ulLoop], sizeof(stWifiKey.aucWifiWepKey2[ulLoop]));
        if (ulRet != VOS_OK)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey3[ulLoop], sizeof(stWifiKey.aucWifiWepKey3[ulLoop]));
        if (ulRet != VOS_OK)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey4[ulLoop], sizeof(stWifiKey.aucWifiWepKey4[ulLoop]));
        if (ulRet != VOS_OK)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiSsid.aucWifiSsid[ulLoop], sizeof(stWifiSsid.aucWifiSsid[ulLoop]));
        if (ulRet != VOS_OK)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }
    }

    *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
    return VOS_OK;

}


VOS_UINT32 AT_GetCsdValue(
    VOS_BOOL                            bSimlockEnableFlg,
    VOS_UINT16                         *pusCsdValue)
{
    VOS_UINT32                          ulRet;

    /*????SIM LOCK Status????????????????????????DISABLE */
    /*????SIM Lock Status????????????????????????????*/
    if (bSimlockEnableFlg != VOS_FALSE)
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
        return VOS_OK;
    }

    /* ????WIFI??????NV?????????????? */
    ulRet = AT_GetWifiNvValue(pusCsdValue);

    return ulRet;
}


VOS_UINT32 AT_OutputCsdfltDefault(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bSimlockEnableFlg
)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulCsdfltFlg;
    VOS_UINT16                          usCsdfltValue;
    VOS_UINT32                          ulRslt;

    ulCsdfltFlg = VOS_TRUE;

    ulRslt = AT_GetCsdValue(bSimlockEnableFlg, &usCsdfltValue);

    if (ulRslt != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????????????????0:????????????????????????????????????;
                       1:?????????????????????????????????????? */
    if (usCsdfltValue == AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE)
    {
        ulCsdfltFlg = VOS_FALSE;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulCsdfltFlg);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_SimlockPlmnNumToAscii(
    const VOS_UINT8                     *pucPlmnRange,
    VOS_UINT8                           ucPlmnRangeLen,
    VOS_UINT8                            *pucAsciiStr
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;

    if ((pucPlmnRange == VOS_NULL_PTR)
     || (pucAsciiStr == VOS_NULL_PTR))
    {
        AT_WARN_LOG("At_SimlockPlmnNumToAscii: Parameter of the function is null.");
        return AT_FAILURE;
    }

    /*??????????????????????????0XFF????*/
    while (ucPlmnRangeLen > 1)
    {
        if (pucPlmnRange[ucPlmnRangeLen - 1] == 0xFF)
        {
            ucPlmnRangeLen--;
        }
        else
        {
            break;
        }
    }

    /*????pucPlmnRange????????????????????????????????????????1111??
    ??????????????????????????????????????*/
    if ((pucPlmnRange[ucPlmnRangeLen - 1] & 0x0F) == 0x0F)
    {
        ucLen = (VOS_UINT8)((ucPlmnRangeLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucPlmnRangeLen * 2);
    }

    /*????????*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*??????????????????????????????????????????0??????????*/
        if ((ucLoop % 2) == 0)
        {
            /*????????????????????????4??????*/
            ucBcdCode = ((pucPlmnRange[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*????????????????????????4??????*/
            ucBcdCode = (pucPlmnRange[(ucLoop / 2)] & 0x0F);
        }

        /*????????????Ascii??????*/
        if (ucBcdCode <= 9)
        {
            pucAsciiStr[ucLoop] = (ucBcdCode + '0');
        }
        else
        {
            return AT_FAILURE;
        }
    }

    pucAsciiStr[ucLoop] = '\0';      /*????????????0*/

    return AT_SUCCESS;
}


VOS_UINT32 At_QrySimLockPlmnInfo(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulPlmnIdx;
    VOS_UINT32                          ulRsltChkPlmnBegin;
    VOS_UINT32                          ulRsltChkPlmnEnd;
    VOS_UINT32                          ulTotalPlmnNum;
    VOS_BOOL                            abPlmnValidFlg[TAF_MAX_SIM_LOCK_RANGE_NUM] = {VOS_FALSE};
    VOS_UINT8                           aucAsciiNumBegin[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];
    VOS_UINT8                           aucAsciiNumEnd[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];


    memset_s(&stSimLockPlmnInfo, sizeof(stSimLockPlmnInfo), 0x00, sizeof(stSimLockPlmnInfo));


    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_CustomizeSimLockPlmnInfo,
                                   &stSimLockPlmnInfo,
                                   sizeof(stSimLockPlmnInfo)) != NV_OK)
    {
        return AT_ERROR;
    }

    ulTotalPlmnNum = 0;

    if (stSimLockPlmnInfo.ulStatus == NV_ITEM_DEACTIVE)
    {
        /* ??????????????????Plmn??????0 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);

        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }

    /*  ????Plmn???????????? */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        ucMncLen = stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum;

        ulRsltChkPlmnBegin = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        ulRsltChkPlmnEnd = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        if ((ulRsltChkPlmnBegin == AT_SUCCESS)
         && (ulRsltChkPlmnEnd == AT_SUCCESS)
         && ((ucMncLen <= 3) && (ucMncLen >= 2)))
        {
            abPlmnValidFlg[i] = VOS_TRUE;
            ++ ulTotalPlmnNum;
        }
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);


    if (ulTotalPlmnNum == 0)
    {
        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s", gaucAtCrLf);
    }


    ulPlmnIdx = 0;
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (abPlmnValidFlg[i] == VOS_FALSE)
        {
            continue;
        }

        ++ ulPlmnIdx;

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:%d,%d,%s,%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ulPlmnIdx,
                                    stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum,
                                    aucAsciiNumBegin,
                                    aucAsciiNumEnd);

        if (ulPlmnIdx < ulTotalPlmnNum)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%s", gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32 At_QryMaxLockTimes(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;


    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = 0;


    ulResult = TAF_ACORE_NV_READ(MODEM_ID_0,
                                 en_NV_Item_CustomizeSimLockMaxTimes,
                                 &stSimLockMaxTimes,
                                 sizeof(stSimLockMaxTimes));
    if (ulResult != NV_OK)
    {
        AT_WARN_LOG("At_QryMaxLockTimes():en_NV_Item_CustomizeSimLockMaxTimes TAF_ACORE_NV_READ Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }


    /* ????NV???????????????????????? 10 */
    if (stSimLockMaxTimes.ulStatus == NV_ITEM_DEACTIVE)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          TAF_PH_CARDLOCK_DEFAULT_MAXTIME);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stSimLockMaxTimes.ulLockMaxTimes);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryAppWronReg( VOS_UINT8 ucIndex )
{
    /* ??????????MMA?????????????? */
    if(TAF_MMA_QryApPwrOnAndRegTimeReq(WUEPS_PID_AT,
                                                   gastAtClientTab[ucIndex].usClientId,
                                                   0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REGISTER_TIME_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryNdisdupPara(
    VOS_UINT8                           ucIndex
)
{
    /* ??????PDP TYPE ????????????????????????OK */
    return AT_OK;
}


AT_PDP_STATUS_ENUM_UINT32 AT_NdisGetConnStatus(
    TAF_IFACE_STATE_ENUM_U8             enPdpState
)
{
    AT_PDP_STATUS_ENUM_UINT32           enConnStatus;

    enConnStatus                        = AT_PDP_STATUS_DEACT;

    if ( (enPdpState == TAF_IFACE_STATE_ACTED)
      || (enPdpState == TAF_IFACE_STATE_DEACTING) )
    {
        enConnStatus = AT_PDP_STATUS_ACT;
    }

    return enConnStatus;
}


VOS_UINT32  At_QryApDialModePara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DIAL_MODE_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    /* ????ID_RNIC_AT_DIAL_MODE_REQ???? */
    /*lint -save -e516 */
    pstMsg = (AT_RNIC_DIAL_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
    /*lint -restore */
    if (pstMsg == VOS_NULL_PTR)
    {
        AT_WARN_LOG("At_QryApDialModePara: alloc msg fail!");
        return VOS_ERR;
    }

    /* ?????????? */
    TAF_MEM_SET_S((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DIAL_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DIAL_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->ulMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
    pstMsg->usClientId      = gastAtClientTab[ucIndex].usClientId;

    /* ??ID_RNIC_AT_DIAL_MODE_REQ??????RNIC?????????????? */
    if (PS_SEND_MSG(WUEPS_PID_AT, pstMsg) == VOS_OK)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDIALMODE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApDialModePara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32  AT_QryAppdmverPara ( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* ????????C?????? PDM?????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_APPDMVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryAppdmverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APPDMVER_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32  AT_QryDislogPara ( VOS_UINT8 ucIndex )
{
    AT_DIAG_OPEN_FLAG_ENUM_U32          enDiagPortState;

#if (FEATURE_LTE == FEATURE_ON)
    VOS_UINT32                          ulRetDiag;
    VOS_UINT32                          ulRet3GDiag;
    VOS_UINT32                          ulRetGps;

    ulRet3GDiag   = AT_ExistSpecificPort(AT_DEV_DIAG);
    ulRetDiag     = AT_ExistSpecificPort(AT_DEV_4G_DIAG);
    ulRetGps      = AT_ExistSpecificPort(AT_DEV_4G_GPS);

    if ((ulRet3GDiag == VOS_TRUE)
      &&(ulRetDiag == VOS_TRUE)
      &&(ulRetGps == VOS_TRUE))
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
#else
    /* ??NV?????? DISLOG ????????????DIAG???????????? */

    /*DIAG ????????????, 0 ????; 1 ????*/
    if (AT_ExistSpecificPort(AT_DEV_DIAG) != VOS_TRUE)
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }

#endif

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enDiagPortState);
    return AT_OK;

}

#if (FEATURE_SECURITY_SHELL == FEATURE_ON)

VOS_UINT32 AT_QryShellPara (VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulShellStatus;


    ulShellStatus = AT_SHELL_CLOSE;


    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_AT_SHELL_OPEN_FLAG,
                                   &ulShellStatus,
                                   sizeof(ulShellStatus)) != NV_OK)
    {
        AT_WARN_LOG("AT_QryShellPara:WARNING:TAF_ACORE_NV_READ SHELL_OPEN_FLAG faild!");

        return AT_ERROR;
    }

    /* shell????????????0,1,2 */
    if (ulShellStatus > AT_SHELL_OPEN)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulShellStatus);
    return AT_OK;

}
#endif


VOS_UINT32 AT_QryWifiGlobalMacPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN+1]; /* MAC????*/

    /* ????????MAC????*/
    ulResult = TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    aucE5GwMacAddr[AT_MAC_ADDR_LEN] = '\0';

    if ( ulResult != NV_OK )
    {
        AT_WARN_LOG("AT_QryApMacPara:read en_NV_Item_GWMAC_ADDR failed or no need to updatee");
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucE5GwMacAddr);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}



VOS_UINT32 AT_QryDloadInfoPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* ????????C?????????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_DLOADINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryDloadInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DLOADINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAuthorityVerPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* ????????C???????????????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryAuthorityVerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYVER_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAuthorityIdPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* ????????C?????????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYID_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryAuthorityIdPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYID_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryFlashInfoPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* ????????C??????FLASH???? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_FLASHINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryFlashInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FLASHINFO_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryAuthverPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C??????SIMLOCK MANAGER???????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryAuthverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHVER_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryWiFiEnablePara(VOS_UINT8 ucIndex)
{
    /* ????????????????????WiFi?????? */
    VOS_UINT32                          ulWifiStatus;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    ulWifiStatus = (VOS_UINT32)WIFI_GET_STATUS();

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ulWifiStatus);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiModePara(VOS_UINT8 ucIndex)
{
    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    /* WIFI??????????B/G/N???? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiMode);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiBandPara(VOS_UINT8 ucIndex)
{
    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    /* ??????????20M???? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     AT_WIFI_BAND_20M);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiFreqPara(VOS_UINT8 ucIndex)
{
    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }


    /* ?????????? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiFreq);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiRatePara(VOS_UINT8 ucIndex)
{
    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    /* ?????????? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiRate);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiPowerPara(VOS_UINT8 ucIndex)
{
    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }



    /* ?????????? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_lWifiPower);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiTxPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8   ucWifiTxStatus;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    /* ????????????????????WiFi?????? */
    if (WIFI_GET_TCMD_MODE() == AT_WIFI_TX_MODE)
    {
        ucWifiTxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiTxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiTxStatus );
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiRxPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucWifiRxStatus;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }


    /* ????????????????????WiFi?????? */
    if (WIFI_GET_TCMD_MODE() == AT_WIFI_RX_MODE)
    {
        ucWifiRxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiRxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiRxStatus );
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiPacketPara(VOS_UINT8 ucIndex)
{
    VOS_UINT                                ulUcastWifiRxPkts;
    VOS_UINT                                ulMcastWifiRxPkts;
    VOS_UINT32                              ulWifiRxPkts;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }


    /* ?????????????????? */
    if (WIFI_GET_TCMD_MODE() != AT_WIFI_RX_MODE)
    {
        AT_WARN_LOG("AT_QryWiFiPacketPara: Not Rx Mode.");
        return AT_ERROR;
    }

    /* ???????????????????????? */
    WIFI_GET_RX_PACKET_REPORT(&ulUcastWifiRxPkts,  &ulMcastWifiRxPkts);
    ulWifiRxPkts = (ulUcastWifiRxPkts - g_ulUcastWifiRxPkts);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulWifiRxPkts,
                                                    0);


    return AT_OK;
}


VOS_UINT32 AT_QryWiFiSsidPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucSsidNum;
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               aucSsidLen[AT_WIFI_MAX_SSID_NUM];

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    memset_s(&stWifiSsid, sizeof(stWifiSsid), 0x00 ,sizeof(stWifiSsid));

    /*????WIFI SSID??????NV??*/
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)) != VOS_OK)
    {
        AT_WARN_LOG("AT_SetWiFiSsidPara:READ NV ERROR");
        return AT_ERROR;
    }

    ucSsidNum = 0;
    memset_s(aucSsidLen, sizeof(aucSsidLen), 0x00, sizeof(aucSsidLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        aucSsidLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSsid.aucWifiSsid[ulLoop]);

        if (aucSsidLen[ulLoop] != 0)
        {
            ucSsidNum++ ;
        }
    }

    usLen = 0;
    usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                    (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                    "%s:%d%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ucSsidNum,
                                    gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (aucSsidLen[ulLoop] != 0)
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSsid.aucWifiSsid[ulLoop],
                                            gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}


VOS_UINT32 AT_QryWiFiLogPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT16                                              usLen;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    memset_s(&stWifiSec, sizeof(stWifiSec), 0x00, sizeof(stWifiSec));
    memset_s(&stWifiSsid, sizeof(stWifiSsid), 0x00, sizeof(stWifiSsid));

    /* ????WIFI SSID??????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)) != VOS_OK)
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    usLen = 0;

    usLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:0,%s%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   stWifiSsid.aucWifiSsid[0],
                                   gaucAtCrLf);

    /* ????WIFI key??????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)) != VOS_OK)
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    /* KEY1??????NV????????KEY1???? */
    if (VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey1[0]) != 0)
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:1,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey1[0],
                                        gaucAtCrLf);
    }

    /* KEY2??????NV????????KEY2???? */
    if (VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey2[0]) != 0)
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:2,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey2[0],
                                        gaucAtCrLf);
    }
    /* KEY3??????NV????????KEY3???? */
    if (VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey3[0]) != 0)
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:3,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey3[0],
                                        gaucAtCrLf);
    }
    /* KEY4??????NV????????KEY3???? */
    if (VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey4[0]) != 0)
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:4,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey4[0],
                                        gaucAtCrLf);
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}

VOS_UINT32 AT_QryWiFiKeyPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT8                                               ucWifiKeyNum;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               aucWpapskLen[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT32                                              ulLoop;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    memset_s(&stWifiSec, sizeof(stWifiSec), 0x00, sizeof(stWifiSec));

    /* ????WIFI key??????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)) != VOS_OK)
    {
        AT_WARN_LOG("AT_QryWiFiSsidPara:READ NV FAIL");
        return AT_ERROR;
    }


    ucWifiKeyNum = 0;
    memset_s(aucWpapskLen, sizeof(aucWpapskLen), 0x00, sizeof(aucWpapskLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {

        /* KEY1??????NV????????KEY1???? */
        aucWpapskLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWpapsk[ulLoop]);

        if (aucWpapskLen[ulLoop] != 0)
        {
            ucWifiKeyNum++ ;
        }
    }

    /* ????????????????????????0?? */
    if (g_bAtDataLocked == VOS_TRUE)
    {
        ucWifiKeyNum = 0;
        memset_s(aucWpapskLen, sizeof(aucWpapskLen), 0x00, sizeof(aucWpapskLen));
    }

    usLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucWifiKeyNum,
                                   gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (aucWpapskLen[ulLoop] != 0)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSec.aucWifiWpapsk[ulLoop],
                                            gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLen;


    return AT_OK;
}


VOS_UINT32 AT_QryWifiPaRangePara (VOS_UINT8 ucIndex)
{
    AT_WIFI_MODE_ENUM_UINT8             ucCurWifiMode;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }


    /* ????????????????????????????WIFI???? */
    ucCurWifiMode   = (VOS_UINT8)WIFI_GET_PA_CUR_MODE();

    if (ucCurWifiMode == AT_WIFI_MODE_ONLY_PA)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "h");
    }
    else if (ucCurWifiMode == AT_WIFI_MODE_ONLY_NOPA)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "l");
    }
    else
    {
        return AT_ERROR;
    }

    return AT_OK;
}

 
VOS_UINT32 AT_QryProdTypePara(VOS_UINT8 ucIndex)
{
    if (AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_PRODTYPE_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT) == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;             /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryTmmiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucFacInfo[AT_FACTORY_INFO_LEN];
    VOS_UINT8                           ucMmiFlag;
    VOS_UINT32                          ulResult;

    ulResult = TAF_ACORE_NV_READ(MODEM_ID_0,
                                 en_NV_Item_Factory_Info,
                                 aucFacInfo,
                                 AT_FACTORY_INFO_LEN);

    if (ulResult != NV_OK)
    {
        return AT_ERROR;
    }

    if (VOS_MemCmp(&aucFacInfo[AT_MMI_TEST_FLAG_OFFSET],
                             AT_MMI_TEST_FLAG_SUCC,
                             AT_MMI_TEST_FLAG_LEN) == VOS_OK)
    {
        ucMmiFlag = VOS_TRUE;
    }
    else
    {
        ucMmiFlag = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s:%d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ucMmiFlag);

    return AT_OK;
}


VOS_UINT32 AT_QryChrgInfoPara(VOS_UINT8 ucIndex)
{

    VOS_INT32                           lChargeState;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    /* ???????????????????????? */
    lChargeState = mdrv_misc_get_charging_status();

    /* ???????? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr),
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    lChargeState);

    return AT_OK;

}

VOS_UINT32 AT_QryChrgEnablePara(VOS_UINT8 ucIndex)
{
    VOS_INT32                             ucChargeEnable;

    if (mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) == BSP_MODULE_UNSUPPORT )
    {
        return AT_ERROR;
    }

    /* ???????????????????????? */

    ucChargeEnable = mdrv_misc_get_charge_state();
    /* ???????? */
    /* ????TRUE/FLASE???????????????? */
    if((ucChargeEnable == TRUE)||( ucChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s:%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ucChargeEnable);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_GetWcdmaBandStr(
    VOS_UINT8                          *pucGsmBandstr,
    VOS_UINT32                          ulGsmBandLen,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;
    ulLen = 0;

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_I_2100 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC1,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_II_1900 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC2,");
    }


    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_III_1800 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC3,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IV_1700 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC4,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_V_850 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC5,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VI_800 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC6,");
    }


    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VII_2600 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC7,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VIII_900 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC8,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IX_J1700 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC9,");
    }

    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XI_1500 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC11,");
    }
    if (pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XIX_850 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "BC19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }


VOS_UINT32 AT_GetWcdmaDivBandStr(
    VOS_UINT8                          *pucGsmBandstr,
    VOS_UINT32                          ulGsmBandLen
)
{
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulBand;

    AT_WCDMA_PREF_BAND_STRU            *pstBitBand = VOS_NULL_PTR;

    /* ????UMTS??????????????????
        V3R2??????en_NV_Item_W_RF_DIV_BAND??V3R1??en_NV_Item_ANTENNA_CONFIG */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_W_RF_DIV_BAND, &ulBand, sizeof(ulBand)) != NV_OK)
    {
        AT_WARN_LOG("AT_GetWcdmaDivBandStr: Read NVIM Smss Error");
        return 0;
    }

    ulLen = 0;
    pstBitBand = (AT_WCDMA_PREF_BAND_STRU *)&ulBand;

    /* ??????????????BAND ????????????????????????????????????
        ??????????????Band1??2??3??????*/

    if (pstBitBand->BandWCDMA_I_2100 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U1,");
    }

    if (pstBitBand->BandWCDMA_II_1900 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U2,");
    }


    if (pstBitBand->BandWCDMA_III_1800 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U3,");
    }

    if (pstBitBand->BandWCDMA_IV_1700 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U4,");
    }

    if (pstBitBand->BandWCDMA_V_850 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U5,");
    }

    if (pstBitBand->BandWCDMA_VI_800 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U6,");
    }


    if (pstBitBand->BandWCDMA_VII_2600 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U7,");
    }

    if (pstBitBand->BandWCDMA_VIII_900 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U8,");
    }

    if (pstBitBand->BandWCDMA_IX_J1700 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U9,");
    }

    if (pstBitBand->BandWCDMA_XI_1500 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U11,");
    }

    if (pstBitBand->BandWCDMA_XIX_850 == 1)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }


VOS_UINT32 AT_GetGsmBandStr(
    VOS_UINT8                          *pucGsmBandstr,
    VOS_UINT32                          ulGsmBandLen,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;

    ulLen = 0;

    if (pstBandCapa->unGRFSptBand.BitBand.BandGsm450 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "450,");
    }

    if (pstBandCapa->unGRFSptBand.BitBand.BandGsm480 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "480,");
    }


    if (pstBandCapa->unGRFSptBand.BitBand.BandGsm850 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "850,");
    }


    if (pstBandCapa->unGRFSptBand.BitBand.BandGsmP900 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "P900,");
    }
    if (pstBandCapa->unGRFSptBand.BitBand.BandGsmR900 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "R900,");
    }
    if (pstBandCapa->unGRFSptBand.BitBand.BandGsmE900 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "E900,");
    }
    if (pstBandCapa->unGRFSptBand.BitBand.BandGsm1800 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1800,");
    }
    if (pstBandCapa->unGRFSptBand.BitBand.BandGsm1900 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1900,");
    }
    if (pstBandCapa->unGRFSptBand.BitBand.BandGsm700 == 1)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "700,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
}
 
VOS_UINT32 AT_QryFeaturePara(VOS_UINT8 ucIndex)
{
    if (AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             ID_AT_MTA_SFEATURE_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_UEPS_PID_MTA) == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SFEATURE_QRY;           /*???????????????? */
        return AT_WAIT_ASYNC_RETURN;                                            /* ???????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryProdNamePara(VOS_UINT8 ucIndex)
{
    TAF_AT_PRODUCT_ID_STRU              stProductId;
    VOS_UINT32                          ulRet;

    memset_s(&stProductId, sizeof(stProductId), 0x00,sizeof(TAF_AT_PRODUCT_ID_STRU));

    /* ??NV50048?????????????? */
    /* ????NV??en_NV_Item_PRODUCT_ID???????????? */
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_PRODUCT_ID,
                              &stProductId,
                              sizeof(stProductId.ulNvStatus) + sizeof(stProductId.aucProductId));

    if (ulRet != NV_OK)
    {
        AT_WARN_LOG("AT_QryProdNamePara: Fail to read en_NV_Item_PRODUCT_ID");
        return AT_ERROR;
    }

    /*??NV????????*/
    if (stProductId.ulNvStatus != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProductId.aucProductId);

    return AT_OK;
}


VOS_UINT32 AT_QryEqverPara(VOS_UINT8 ucIndex)
{
    /*<version>?????????? AT????????????????????????????????????0~9????????????
    ????????????????????????AT????????????????????????????
    114 ??????????AT????????????????????????
    balong????????115*/
    VOS_UINT32                          ulRet;
    TAF_AT_EQ_VER_STRU                  stEqver;

    stEqver.usEqver = 0;

    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_Eqver, &stEqver.usEqver, sizeof(stEqver.usEqver));
    if (ulRet != NV_OK)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stEqver.usEqver);

    return AT_OK;
}



VOS_UINT32 AT_QryApRptSrvUrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApRptSrvUrl[AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1];
    VOS_UINT32                          ulRet;
    errno_t                             lMemResult;
    TAF_AT_NVIM_AP_RPT_SRV_URL_STRU     stApRptSrvUrl;

    memset_s(aucApRptSrvUrl, sizeof(aucApRptSrvUrl), 0x00, (VOS_SIZE_T)(AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1));

    memset_s(&stApRptSrvUrl, sizeof(stApRptSrvUrl), 0x00, sizeof(stApRptSrvUrl));

    /* ??NV:en_NV_Item_AP_RPT_SRV_URL*/
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_AP_RPT_SRV_URL,
                              &stApRptSrvUrl,
                              AT_AP_NVIM_XML_RPT_SRV_URL_LEN);

    if (ulRet != NV_OK)
    {
        AT_ERR_LOG("AT_QryApRptSrvUrlPara:Read NV fail");
        return AT_ERROR;
    }
    lMemResult = memcpy_s(aucApRptSrvUrl, sizeof(aucApRptSrvUrl), stApRptSrvUrl.aucApRptSrvUrl, AT_AP_NVIM_XML_RPT_SRV_URL_LEN);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(aucApRptSrvUrl), AT_AP_NVIM_XML_RPT_SRV_URL_LEN);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:\"%s\"",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApRptSrvUrl);

    return AT_OK;
}


VOS_UINT32 AT_QryApXmlInfoTypePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApXmlInfoType[AT_AP_XML_RPT_INFO_TYPE_LEN + 1];
    VOS_UINT32                          ulRet;
    errno_t                             lMemResult;
    TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU   stApXmlInfoType;

    memset_s(aucApXmlInfoType, sizeof(aucApXmlInfoType), 0x00, (VOS_SIZE_T)(AT_AP_XML_RPT_INFO_TYPE_LEN + 1));

    memset_s(&stApXmlInfoType, sizeof(stApXmlInfoType), 0x00, sizeof(stApXmlInfoType));

    /* ??NV:en_NV_Item_AP_XML_INFO_TYPE*/
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_AP_XML_INFO_TYPE,
                              &stApXmlInfoType,
                              AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    if (ulRet != NV_OK)
    {
        AT_ERR_LOG("AT_QryApXmlInfoTypePara:Read NV fail");
        return AT_ERROR;
    }

    lMemResult = memcpy_s(aucApXmlInfoType, sizeof(aucApXmlInfoType), stApXmlInfoType.aucApXmlInfoType, AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(aucApXmlInfoType), AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApXmlInfoType);

    return AT_OK;
}


VOS_UINT32 AT_QryApXmlRptFlagPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_RPT_FLG_STRU     stApXmlRptFlg;

    stApXmlRptFlg.ucApXmlRptFlg = VOS_FALSE;

    /* ??NV:en_NV_Item_AP_XML_RPT_FLAG*/
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_AP_XML_RPT_FLAG,
                              &stApXmlRptFlg,
                              sizeof(TAF_AT_NVIM_AP_XML_RPT_FLG_STRU));

    if (ulRet != NV_OK)
    {
        AT_ERR_LOG("AT_QryApXmlRptFlagPara:Read NV fail");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stApXmlRptFlg.ucApXmlRptFlg);

    return AT_OK;
}



VOS_UINT32 AT_QryFastDormPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* ????MN_FillAndSndAppReqMsg()??????RABM?????? */
    ulRslt = AT_SndQryFastDorm(gastAtClientTab[ucIndex].usClientId,gastAtClientTab[ucIndex].opId);
    if (ulRslt == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FASTDORM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 AT_QryAcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    PS_PRINTF_INFO("<AT_QryAcpuMemInfoPara> at cmd\n");

    /*????????????????*/
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_DEVICE_OTHER_ERROR;
    }



    return AT_OK;

}



VOS_UINT32 AT_QryCcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    PS_PRINTF_INFO("<AT_QryCcpuMemInfoPara> at cmd\n");

    /*????????????????*/
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ????????C??????CCPU???????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_QRY_CCPU_MEM_INFO_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (ulRet == TAF_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCPUMEMINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("AT_QryCcpuMemInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryCipherPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ????????MMA????Cipher???? */
    ulResult = TAF_MMA_QryCipherReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);

    /* ???????????? */
    if (ulResult == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIPERQRY_READ;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


VOS_UINT32 AT_QryLocinfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ????????MMA????????UE?????????? */
    ulResult = TAF_MMA_QryLocInfoReq(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0);

    /* ???????????? */
    if (ulResult == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LOCINFO_READ;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryNvResumePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvResumeFlag;


    usNvResumeFlag = AT_NV_RESUME_SUCC;


    /* ????en_NV_Resume_Flag */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Resume_Flag, &usNvResumeFlag, sizeof(VOS_UINT16)) != NV_OK)
    {
        AT_WARN_LOG("AT_QryNvResumePara:READ NV FAIL");
        return AT_ERROR;
    }

    /* ??????????????0????1 */
    if ((usNvResumeFlag != AT_NV_RESUME_SUCC)
     && (usNvResumeFlag != AT_NV_RESUME_FAIL))
    {
        AT_WARN_LOG("AT_QryNvResumePara:PARA IS INVALID");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     usNvResumeFlag);
    return AT_OK;
}


VOS_UINT32 AT_QryNvBackupStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C??????????NV???????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NVBACKUPSTAT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryNvBackupStatusPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVBACKUPSTAT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryNandBadBlockPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C??????NAND FLASH?????????????????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDBBC_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryNandBadBlockPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDBBC_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryNandDevInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C??????NAND FLASH?????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryNandDevInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDVER_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryChipTempPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ????????C??????PA??SIM?????????????????? */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CHIPTEMP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryChipTempPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIPTEMP_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryApRptPortSelectPara(VOS_UINT8 ucIndex)
{
    AT_PORT_RPT_CFG_STRU                stRptCfg;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg = VOS_NULL_PTR;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl = VOS_NULL_PTR;
    VOS_UINT8                           i;

    memset_s(&stRptCfg, sizeof(stRptCfg), 0x00, sizeof(stRptCfg));

    /* ???????? */
    if (AT_IsApPort(ucIndex) == VOS_FALSE)
    {
        return AT_ERROR;
    }

    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);

        if (pstClientCfg->ucReportFlg == VOS_TRUE)
        {
            stRptCfg.aulRptCfgBit32[0] |= pstCfgMapTbl->ulRptCfgBit32[0];
            stRptCfg.aulRptCfgBit32[1] |= pstCfgMapTbl->ulRptCfgBit32[1];
            stRptCfg.aulRptCfgBit32[2] |= pstCfgMapTbl->ulRptCfgBit32[2];
        }
    }

    /* ???????????? */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %08X, %08X, %08X",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stRptCfg.aulRptCfgBit32[0],
                                                    stRptCfg.aulRptCfgBit32[1],
                                                    stRptCfg.aulRptCfgBit32[2]);


    return AT_OK;
}


VOS_UINT32 At_QryUsbSwitchPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucUsbStatus;
    VOS_UINT32                          ulResult;


    ucUsbStatus = USB_SWITCH_OFF;

    /* ???????? */
    if (AT_IsApPort(ucIndex) == VOS_FALSE)
    {
        return AT_ERROR;
    }

    if (DRV_USB_PHY_SWITCH_GET(&ucUsbStatus) != VOS_OK)
    {
        return AT_ERROR;
    }

    ulResult = (ucUsbStatus == USB_SWITCH_ON)?AT_USB_SWITCH_SET_VBUS_VALID:\
                                              AT_USB_SWITCH_SET_VBUS_INVALID;

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "+USBSWITCH: %X", ulResult);

    return AT_OK;
}


VOS_UINT32 AT_QryAntState(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usAntState;

    AT_PR_LOGI("Rcv Msg");

    /* ???????? */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_CMD_NO_PARA)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    usAntState = 0;

    ulRet = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    AT_PR_LOGI("Call interface success!");
    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("AT_QryAntState: TAF_AGENT_GetAntState fail");

        return AT_ERROR;
    }

    /* ????????????????????????0????????????1 */
    if ((usAntState & AT_CMD_MAX_ANT_BIT_MASK) == 0)
    {
        AT_NORM_LOG("AT_QryAntState: usAntState Set to 0");
        usAntState = 0;
    }
    else
    {
        AT_NORM_LOG("AT_QryAntState: usAntState Set to 1");
        usAntState = 1;
    }

    /* AT???? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    usAntState);
    return AT_OK;
}


VOS_UINT32 AT_QrySARReduction(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usUETestMode;
    AT_MODEM_MT_INFO_CTX_STRU          *pstMtInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT16                          usAntState;

    usUETestMode = VOS_FALSE;

    /* ????NV???????????????????? */
    ulRet = TAF_ACORE_NV_READ(MODEM_ID_0,
                              en_NV_Item_RF_SAR_BACKOFF_TESTMODE,
                              &usUETestMode,
                              sizeof(usUETestMode));

    if (ulRet != NV_OK)
    {
        AT_ERR_LOG("AT_QrySARReduction:Read NV fail");
        return AT_ERROR;
    }


    enModemId  = MODEM_ID_0;

    ulRet   = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    pstMtInfoCtx = AT_GetModemMtInfoCtxAddrFromModemId(enModemId);

    usAntState   = 0;
    ulRet        = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (ulRet != VOS_OK)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    if ((usAntState == AT_ANT_CONDUCTION_MODE) && (usUETestMode != VOS_TRUE))
    {
        AT_ERR_LOG("AT_QrySARReduction: ant state wrong");
        return AT_ERROR;
    }

    /* AT???? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%u",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstMtInfoCtx->ulSarReduction);

    return AT_OK;
}

#if (FEATURE_LTE == FEATURE_ON)

VOS_UINT32  AT_QryRsrpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSRP_CFG_STRU stRsrpCfg;
    VOS_UINT32 i =0;

    memset_s(&stRsrpCfg, sizeof(stRsrpCfg), 0x00, sizeof(stRsrpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (TAF_ACORE_NV_READ(MODEM_ID_0, EN_NV_ID_RSRP_CFG, &stRsrpCfg,sizeof(stRsrpCfg)) != NV_OK)
        {
            PS_PRINTF_WARNING("read RSRP_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRsrpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRsrpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}

VOS_UINT32  AT_QryRscpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSCP_CFG_STRU stRscpCfg;
    VOS_UINT32 i =0;

    memset_s(&stRscpCfg, sizeof(stRscpCfg), 0x00, sizeof(stRscpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                       EN_NV_ID_RSCP_CFG,
                                       &stRscpCfg,
                                       sizeof(stRscpCfg)) != NV_OK)
        {
            return AT_ERROR;
        }


        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                "%s:",
                                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRscpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRscpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}

VOS_UINT32  AT_QryEcioCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_ECIO_CFG_STRU stEcioCfg;
    VOS_UINT32 i =0;

    memset_s(&stEcioCfg, sizeof(stEcioCfg), 0x00, sizeof(stEcioCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                       EN_NV_ID_ECIO_CFG,
                                       &stEcioCfg,
                                       sizeof(stEcioCfg)) != NV_OK)
        {
            PS_PRINTF_WARNING("read ECIO_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  "%s:",
                                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stEcioCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stEcioCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR; /* ????????????????????ERROR */
    }

    return AT_OK;
}

/* ????AT_QryCellRoamPara */


VOS_UINT32 AT_QryPdprofmodPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}
#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 At_QrySfm(VOS_UINT8 ucIndex)
{
    OM_SW_VER_FLAG_STRU  stCustomVersion;


    stCustomVersion.ulNvSwVerFlag = 0;

    if ( TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_SW_VERSION_FLAG, &stCustomVersion.ulNvSwVerFlag, sizeof(stCustomVersion.ulNvSwVerFlag)) != VOS_OK )
    {
        return AT_ERROR;
    }
    else
    {

        /* AT??????NV???????????????? */
        if (stCustomVersion.ulNvSwVerFlag == 0)
        {

            /* 1 ???????????? */
            stCustomVersion.ulNvSwVerFlag = 1;

        }
        else
        {

            /* 0 ???????????? */
            stCustomVersion.ulNvSwVerFlag = 0;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
            (TAF_CHAR *)pgucAtSndCodeAddr,"^SFM: %d", stCustomVersion.ulNvSwVerFlag);

        return AT_OK;
    }
}
#endif
#endif

#if (FEATURE_PHONE_SC == FEATURE_ON)

VOS_UINT32 AT_QryPhoneSimlockInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (AT_IsApPort(ucIndex) == VOS_FALSE)
    {
        return AT_ERROR;
    }

    AT_PR_LOGI("Rcv Msg");

    /* ??????????????C??, ???????????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryPhoneSimlockInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    AT_PR_LOGI("Snd Msg");

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONESIMLOCKINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QrySimlockDataReadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (AT_IsApPort(ucIndex) == VOS_FALSE)
    {
        return AT_ERROR;
    }

    AT_PR_LOGI("Rcv Msg");

    /* ??????????????C??, ???????????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QrySimlockDataReadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    AT_PR_LOGI("Snd Msg");

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMLOCKDATAREAD_READ;
    return AT_WAIT_ASYNC_RETURN;
}
#endif



#if (VOS_WIN32 == VOS_OS_VER)
VOS_UINT8 NAS_GetTinType(VOS_VOID);


VOS_UINT32 At_QryTinTypeStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucTinType;

#if (FEATURE_LTE == FEATURE_ON)
    ucTinType = NAS_GetTinType();
#endif
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucTinType);
    return AT_OK;

}


VOS_UINT32 AT_QryPsRegisterContainDrxStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDrx;

    ucDrx = NAS_GetPsRegContainDrx();
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucDrx);
    return AT_OK;

}


#endif



VOS_UINT32 AT_QryCposrPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ????+CPOSR???????????????????? */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAgpsCtx->enCposrReport);

    return AT_OK;
}


VOS_UINT32 AT_QryXcposrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ??MTA????+xcposr???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ID_AT_MTA_XCPOSR_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryXcposrPara: send Msg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XCPOSR_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryXcposrRptPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ??MTA???????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ID_AT_MTA_XCPOSRRPT_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryXcposrRptPara: send Msg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XCPOSRRPT_QRY;

    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryCPsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_PS_GetPsCallErrCause(ucIndex));

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryCmutPara(VOS_UINT8 ucIndex)
{
    if (APP_VC_GetMuteStatus(gastAtClientTab[ucIndex].usClientId, 0) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMUT_READ;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCCsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_GetCsCallErrCause(ucIndex));

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_QryCerssiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_MMA_QryCerssiReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId);

    /* ???????????? */
    if (ulResult == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CERSSI_READ;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if (FEATURE_UE_MODE_NR == FEATURE_ON)

VOS_UINT32 At_QryCserssiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_MMA_QryCserssiReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId);

    /* ???????????? */
    if (ulResult == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSERSSI_READ;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


#if(FEATURE_LTE == FEATURE_ON)


VOS_UINT32 At_QryCecellidPara(VOS_UINT8 ucIndex)
{
    /* ????L ???????? */
    return At_QryCellIdPara(ucIndex);
}
#endif



VOS_UINT32 AT_QryCbgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT ??VC ???????????????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_FOREGROUND_QRY,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryCbgPara: send Msg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBG_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAcInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ????????MMA????????UE?????????? */
    ulResult = TAF_MMA_QryAcInfoReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);
    /* ???????????? */
    if (ulResult == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ACINFO_READ;

        /* ???????????????????? */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 AT_QryCLteRoamAllowPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                       ucLteRoamAllow;
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU    stNvimLteRoamAllowedFlg;


    /* ?????????????? */
    ucLteRoamAllow          = VOS_FALSE;
    stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg = VOS_FALSE;


    /* ????NV, ??NV???????? NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU, ????????1?????? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_Lte_Internation_Roam_Config,
                                   &stNvimLteRoamAllowedFlg,
                                   sizeof(NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU)) != NV_OK)
    {
        AT_WARN_LOG("AT_QryCLteRoamAllowPara(): en_NV_Item_Lte_Internation_Roam_Config TAF_ACORE_NV_READ Error");
        return AT_ERROR;
    }


    /* ????????, NV??????VOS_FALSE??????????????, ?????????????????????? */
    if (stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg == VOS_FALSE)
    {
        ucLteRoamAllow = VOS_FALSE;
    }
    else
    {
        ucLteRoamAllow = VOS_TRUE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucLteRoamAllow);
    return AT_OK;
}
#endif


VOS_UINT32 At_QryMmPlmnInfoPara(VOS_UINT8 ucIndex)
{
    if(TAF_MMA_QryMMPlmnInfoReq(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMPLMNINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryEonsUcs2Para(VOS_UINT8 ucIndex)
{
    if(TAF_MMA_QryEonsUcs2Req(
                    WUEPS_PID_AT,
                    gastAtClientTab[ucIndex].usClientId,
                    0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EONSUCS2_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryPlmnPara(VOS_UINT8 ucIndex)
{
    if(TAF_MMA_QryPlmnReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 At_QryXlemaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????????C?????????????????? */
    ulRst = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_QRY_XLEMA_REQ,
                                  0,
                                  enModemId);

    if (ulRst != MN_ERR_NO_ERROR)
    {
        AT_WARN_LOG("At_QryXlemaPara: TAF_CCM_CallCommonReq fail.");
        return AT_ERROR;
    }

    /* ????????????????OK */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XLEMA_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryBodySarOnPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_enAtBodySarState);
    return AT_OK;
}


VOS_UINT32 AT_FillBodySarWcdmaQryPara(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara)
{
    VOS_UINT32                          ulLoop1;
    VOS_UINT8                           ucLoop2;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_UINT32                          ulTmpBand;

    memset_s(&stWGBand, sizeof(stWGBand), 0x00, sizeof(stWGBand));
    ulTmpBand       = 0;

    /* ????WCDMA Band?????? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_WG_RF_MAIN_BAND,
                                   &stWGBand,
                                   sizeof(stWGBand)) != NV_OK)
    {
        AT_ERR_LOG("AT_FillBodySarWcdmaQryPara: Read NV fail!");
        return VOS_ERR;
    }

    for (ulLoop1 = 0; ulLoop1 < (VOS_UINT32)TAF_MIN(pstBodySarPara->usWBandNum, MTA_BODY_SAR_WBAND_MAX_NUM); ulLoop1++) {
        for (ucLoop2 = 0; ucLoop2 < (VOS_UINT32)TAF_MIN(pstBodySarWcdmaPara->ucParaNum, AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM); ucLoop2++) {
            if (pstBodySarPara->astWBandPara[ulLoop1].sPower == pstBodySarWcdmaPara->asPower[ucLoop2]) {
                break;
            }
        }

        if ((ucLoop2 == pstBodySarWcdmaPara->ucParaNum) && (ucLoop2 < AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM)) {
            pstBodySarWcdmaPara->ucParaNum++;
            pstBodySarWcdmaPara->asPower[ucLoop2] =pstBodySarPara->astWBandPara[ulLoop1].sPower;
        }

        if (ucLoop2 < AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM) {
            pstBodySarWcdmaPara->aulBand[ucLoop2] |= 0x00000001U << (pstBodySarPara->astWBandPara[ulLoop1].enBand - 1);
            ulTmpBand |= pstBodySarWcdmaPara->aulBand[ucLoop2];
        }
    }

    /* ?????????????????????????? */
    ulTmpBand = stWGBand.unWcdmaBand.ulBand & (~ulTmpBand);
    if ((ulTmpBand != 0) && (pstBodySarWcdmaPara->ucParaNum < AT_BODYSARWCDMA_MAX_PARA_GROUP_NUM)) {
        pstBodySarWcdmaPara->aulBand[pstBodySarWcdmaPara->ucParaNum] = ulTmpBand;
        pstBodySarWcdmaPara->asPower[pstBodySarWcdmaPara->ucParaNum] = AT_WCDMA_BAND_DEFAULT_POWER;
        pstBodySarWcdmaPara->ucParaNum++;
    }

    return VOS_OK;
}


VOS_UINT32 AT_QryBodySarWcdmaPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    memset_s(&stBodySarPara, sizeof(stBodySarPara), 0x00, sizeof(stBodySarPara));
    memset_s(&stBodySarWcdmaPara, sizeof(stBodySarWcdmaPara), 0x00, sizeof(stBodySarWcdmaPara));
    usLength        = 0;

    /* ??NV????????Body SAR?????????? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_BODY_SAR_PARA,
                                   &stBodySarPara,
                                   sizeof(stBodySarPara)) != NV_OK)
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ??Body SAR??????????????^BODYSARWCDMA?????????????? */
    if (AT_FillBodySarWcdmaQryPara(&stBodySarPara, &stBodySarWcdmaPara) != VOS_OK)
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: AT_FillBodySarWcdmaQryPara fail!");
        return AT_ERROR;
    }

    /* ?????????? */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????WCDMA????Body SAR???? */
    if (stBodySarWcdmaPara.ucParaNum == 1)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarWcdmaPara.ucParaNum; ucLoop++)
    {
        if (ucLoop != 0)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[ucLoop],
                                           stBodySarWcdmaPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_FillBodySarGsmDefaultPower(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT32                          ulGBandCapa;
    VOS_UINT32                          ulTmpBand;

    ulGBandCapa     = 0;
    ulTmpBand       = 0;

    /* ????GSM Band?????? */
    if (AT_GetGsmBandCapa(&ulGBandCapa) != VOS_OK)
    {
        AT_ERR_LOG("AT_FillBodySarGsmDefaultPower: AT_GetGsmBandCapa fail!");
        return VOS_ERR;
    }

    ulTmpBand = ulGBandCapa & (~pstBodySarPara->ulGBandMask);

    if ((AT_BODY_SAR_GBAND_GPRS_850_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_850_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_850].sGPRSPower = AT_GSM_GPRS_850_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_EDGE_850_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_850_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_850].sEDGEPower = AT_GSM_EDGE_850_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_GPRS_900_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_900].sGPRSPower = AT_GSM_GPRS_900_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_EDGE_900_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_900].sEDGEPower = AT_GSM_EDGE_900_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_GPRS_1800_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_1800_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1800].sGPRSPower = AT_GSM_GPRS_1800_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_EDGE_1800_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_1800_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1800].sEDGEPower = AT_GSM_EDGE_1800_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_GPRS_1900_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_1900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1900].sGPRSPower = AT_GSM_GPRS_1900_DEFAULT_POWER;
    }

    if ((AT_BODY_SAR_GBAND_EDGE_1900_MASK & ulTmpBand) != 0)
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_1900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1900].sEDGEPower = AT_GSM_EDGE_1900_DEFAULT_POWER;
    }

    return VOS_OK;
}


VOS_VOID AT_FillBodySarGsmByModulationMode(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    VOS_UINT8                           ucModulationOffset,
    AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;

    for (ucLoop1 = AT_GSM_850; ucLoop1 < AT_GSM_BAND_BUTT; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarGsmPara->ucParaNum; ucLoop2++)
        {
            if (ucModulationOffset == AT_GSM_GPRS_BAND_OFFSET)
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
            else
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
        }

        if (ucLoop2 == pstBodySarGsmPara->ucParaNum)
        {
            pstBodySarGsmPara->ucParaNum++;
            if (ucModulationOffset == AT_GSM_GPRS_BAND_OFFSET)
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower;
            }
            else
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower;
            }
        }
        pstBodySarGsmPara->aulBand[ucLoop2]   |= 0x00000001U << (ucLoop1 + ucModulationOffset);
    }

    return;
}


VOS_UINT32 AT_QryBodySarGsmPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARGSM_SET_PARA_STRU         stBodySarGsmPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    memset_s(&stBodySarPara, sizeof(stBodySarPara), 0x00, sizeof(stBodySarPara));
    memset_s(&stBodySarGsmPara, sizeof(stBodySarGsmPara), 0x00, sizeof(stBodySarGsmPara));
    usLength        = 0;

    /* ??NV????????Body SAR?????????? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_BODY_SAR_PARA,
                                   &stBodySarPara,
                                   sizeof(stBodySarPara)) != NV_OK)
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ????GSM????Body SAR?????????? */
    if (AT_FillBodySarGsmDefaultPower(&stBodySarPara) != VOS_OK)
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: AT_FillBodySarGsmDefaultPower fail!");
        return AT_ERROR;
    }

    /* ??Body SAR??????????????^BODYSARGSM?????????????? */
    /* GPRS???????? */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_GPRS_BAND_OFFSET, &stBodySarGsmPara);

    /* EDGE???????? */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_EDGE_BAND_OFFSET, &stBodySarGsmPara);

    /* ?????????? */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ????GSM????Body SAR???? */
    if (stBodySarGsmPara.ucParaNum == 1)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarGsmPara.ucParaNum; ucLoop++)
    {
        if (ucLoop != 0)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[ucLoop],
                                           stBodySarGsmPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_QryIMEIVerifyPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? ID_AT_MTA_IMEI_VERIFY_QRY_REQ ?? MTA ?????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_IMEI_VERIFY_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMEI_VERIFY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryNCellMonitorPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ??MTA????^NCELLMONITOR???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_NCELL_MONITOR_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NCELL_MONITOR_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryUserSrvStatePara(VOS_UINT8 ucIndex)
{
    if(TAF_MMA_QryUserSrvStateReq(WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0) == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_USER_SRV_STATE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryRefclkfreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (AT_IsApPort(ucIndex) == VOS_FALSE)
    {
        return AT_ERROR;
    }

    /* ??????????????C??, ????GPS???????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_REFCLKFREQ_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("At_QryRefclkfreqPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REFCLKFREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryHandleDect(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;

    /* ????NV???????????????? */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

    /* ??ANDROID?????????? */
    if ( *pucSystemAppConfig != SYSTEM_APP_ANDROID)
    {
        return AT_CMD_NOT_SUPPORT;
    }

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ???????? ID_AT_MTA_HANDLEDECT_QRY_REQ ??MTA???? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_MTA_HANDLEDECT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HANDLEDECT_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryLogNvePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulEnable;
    VOS_UINT32                          ulTimeout;
    VOS_UINT32                          ulBufferSize;
    SOCP_ENC_DST_BUF_LOG_CFG_STRU       stLogCfg = {0};

    ulEnable                            = 0;
    ulTimeout                           = 0;
    ulBufferSize                        = 0;


    ulResult = mdrv_socp_get_sd_logcfg(&stLogCfg);

    if (ulResult != VOS_OK)
    {
        return AT_ERROR;
    }

    ulEnable = stLogCfg.logOnFlag;
    /*dts??????????????????????????????*/
    if((stLogCfg.logOnFlag==1)||(stLogCfg.logOnFlag==2))
    {
        ulEnable = 1;
    }
    ulTimeout= stLogCfg.ulCurTimeout;
    ulBufferSize = stLogCfg.BufferSize;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulEnable,
                                      ulTimeout,
                                      ulBufferSize);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 AT_QryCiregPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   PS_PID_IMSA);

    if (ulRst != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryCiregPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREG_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryCirepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   PS_PID_IMSA);

    if (ulRst != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryCirepPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREP_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryImsRegDomainPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    /* ???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_IMSA_IMS_REG_DOMAIN_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      PS_PID_IMSA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryImsRegDomainPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSREGDOMAIN_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryImsDomainCfgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* AT ??MMA ???????????????? */
    ulResult = TAF_MMA_QryImsDomainCfgReq(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0);

    if (ulResult == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSDOMAINCFG_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryImsEmcRdpPara(VOS_UINT8 ucIndex)
{
    AT_IMS_EMC_RDP_STRU                *pstImsEmcRdp = VOS_NULL_PTR;
    VOS_CHAR                            acIpv4AddrStr[TAF_MAX_IPV4_ADDR_STR_LEN];
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT16                          usLength = 0;

    memset_s(acIpv4AddrStr, sizeof(acIpv4AddrStr), 0x00, sizeof(acIpv4AddrStr));
    memset_s(aucIpv6AddrStr, sizeof(aucIpv6AddrStr), 0x00, sizeof(aucIpv6AddrStr));

    /* ????IMS EMC RDP */
    pstImsEmcRdp = AT_GetImsEmcRdpByClientId(ucIndex);
    if (pstImsEmcRdp == VOS_NULL_PTR)
    {
        AT_WARN_LOG("AT_QryImsEmcRdpPara: ImsEmcRdp not found.");
        return AT_ERROR;
    }

    /* ??????????????IMS EMC PDN???? */
    if ( (pstImsEmcRdp->bitOpIPv4PdnInfo != VOS_TRUE)
      && (pstImsEmcRdp->bitOpIPv6PdnInfo != VOS_TRUE) )
    {
        return AT_ERROR;
    }

    if (pstImsEmcRdp->bitOpIPv4PdnInfo == VOS_TRUE)
    {
        /* ^IMSEMCRDP: */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        /* IP Type */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           "\"IPV4\"");
        /* IP Addr */
        AT_Ipv4AddrItoa(acIpv4AddrStr, sizeof(acIpv4AddrStr), pstImsEmcRdp->stIPv4PdnInfo.aucIpAddr);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           acIpv4AddrStr);

        /* Primary DNS */
        AT_Ipv4AddrItoa(acIpv4AddrStr, sizeof(acIpv4AddrStr), pstImsEmcRdp->stIPv4PdnInfo.aucDnsPrimAddr);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           acIpv4AddrStr);

        /* Secondary DNS */
        AT_Ipv4AddrItoa(acIpv4AddrStr, sizeof(acIpv4AddrStr), pstImsEmcRdp->stIPv4PdnInfo.aucDnsSecAddr);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           acIpv4AddrStr);

        /* MTU */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstImsEmcRdp->stIPv4PdnInfo.usMtu);
    }

    if ( (pstImsEmcRdp->bitOpIPv4PdnInfo == VOS_TRUE)
      && (pstImsEmcRdp->bitOpIPv6PdnInfo == VOS_TRUE) )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           gaucAtCrLf);
    }

    if (pstImsEmcRdp->bitOpIPv6PdnInfo == VOS_TRUE)
    {
        /* ^IMSEMCRDP: */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* IP Type */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           "\"IPV6\"");

        /* IP Addr */
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstImsEmcRdp->stIPv6PdnInfo.aucIpAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           aucIpv6AddrStr);

        /* Primary DNS */
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstImsEmcRdp->stIPv6PdnInfo.aucDnsPrimAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           aucIpv6AddrStr);

        /* Secondary DNS */
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstImsEmcRdp->stIPv6PdnInfo.aucDnsSecAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           aucIpv6AddrStr);

        /* MTU */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstImsEmcRdp->stIPv6PdnInfo.usMtu);
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
#endif


VOS_UINT32 AT_QryClccPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                               ulRet;
    TAF_CTRL_STRU                            stCtrl;
    TAF_CALL_QRY_CALL_INFO_REQ_PARA_STRU     stQryCallInfoPara;
    MODEM_ID_ENUM_UINT16                     enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));
    memset_s(&stQryCallInfoPara, sizeof(stQryCallInfoPara), 0x00, sizeof(stQryCallInfoPara));

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    stQryCallInfoPara.enGetCallInfoType = TAF_CALL_GET_CALL_INFO_TYPE_CLCC;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????????C?????????????????????? */
    ulRet = TAF_CCM_CallCommonReq(&stCtrl,
                                  &stQryCallInfoPara,
                                  ID_TAF_CCM_QRY_CALL_INFO_REQ,
                                  sizeof(stQryCallInfoPara),
                                  enModemId);

    if (ulRet != VOS_OK)
    {
        AT_WARN_LOG("AT_QryClccPara: MN_CALL_GetCallInfos fail.");
        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 AT_QryClccEconfInfo(VOS_UINT8 ucIndex)
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT32                          ulRst;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(TAF_CTRL_STRU));

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* AT??CCM?????????????????????????? */
    ulRst   = TAF_CCM_CallCommonReq(&stCtrl,
                                    VOS_NULL_PTR,
                                    ID_TAF_CCM_QRY_ECONF_CALLED_INFO_REQ,
                                    0,
                                    enModemId);

    if (ulRst != VOS_OK)
    {
        AT_WARN_LOG("AT_QryClccEconfInfo: TAF_CCM_CallCommonReq fail.");

        return AT_ERROR;
    }

    /* ????AT???????????????????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCCECONF_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryEconfErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usLength;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx     = VOS_NULL_PTR;
    AT_ECONF_INFO_STRU                 *pstEconfInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT8                           ucErrNum;

    ucErrNum     = 0;
    usLength     = 0;
    pstCcCtx     = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstEconfInfo = &(pstCcCtx->stEconfInfo);
    ucNumOfCalls = pstEconfInfo->ucNumOfCalls;
    memset_s(aucAsciiNum, sizeof(aucAsciiNum), 0x00, sizeof(aucAsciiNum));

    for (i = 0; ((i < ucNumOfCalls) && (i < TAF_CALL_MAX_ECONF_CALLED_NUM)); i++)
    {
        /* ?????????????? */
        if ((pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen != 0)
         && (pstEconfInfo->astCallInfo[i].enCause != TAF_CS_CAUSE_SUCCESS))
        {
            /* <CR><LF> */
            if (ucErrNum != 0)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            AT_BcdNumberToAscii(pstEconfInfo->astCallInfo[i].stCallNumber.aucBcdNum,
                                pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen,
                                (VOS_CHAR *)aucAsciiNum);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: \"%s\",%d,%d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               aucAsciiNum,
                                               (pstEconfInfo->astCallInfo[i].stCallNumber.enNumType | AT_NUMBER_TYPE_EXT),
                                               pstEconfInfo->astCallInfo[i].enCause);

            ucErrNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 AT_QryImsSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* AT ??MMA ???????????????? */
    ulRst = TAF_MMA_QryImsSwitchReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);
    if (ulRst == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMS_SWITCH_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryCevdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* AT ??MMA ???????????????? */
    ulRst = TAF_MMA_QryVoiceDomainReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0);
    if (ulRst == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VOICE_DOMAIN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryRoamImsServicePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ???????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_IMSA_ROAMING_IMS_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      PS_PID_IMSA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryRoamImsServicePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ROAM_IMS_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#endif


VOS_UINT32 AT_QryUserCfgOPlmnPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ???????? ID_AT_MTA_HANDLEDECT_QRY_REQ ??MTA???? */
    ulRst = TAF_MMA_QryEOPlmnReq(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0);
    if (ulRst == VOS_TRUE)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EOPLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if (FEATURE_AT_HSUART == FEATURE_ON)

VOS_UINT32 AT_QryIprPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ?????? */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* ???????? */
    if (AT_CheckHsUartUser(ucIndex) != VOS_TRUE)
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %u",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stPhyConfig.enBaudRate);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryIcfPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ?????? */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* ???????? */
    if (AT_CheckHsUartUser(ucIndex) != VOS_TRUE)
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stPhyConfig.stFrame.enFormat,
                                      pstUartCtx->stPhyConfig.stFrame.enParity);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryIfcPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ?????? */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* ???????? */
    if (AT_CheckHsUartUser(ucIndex) != VOS_TRUE)
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stFlowCtrl.enDceByDte,
                                      pstUartCtx->stFlowCtrl.enDteByDce);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
#endif



VOS_UINT32 AT_QryModemStatusPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_QryRATCombinePara(VOS_UINT8 ucIndex)
{
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           usRatMode;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stNVData, sizeof(stNVData), 0x00, sizeof(stNVData));

    if (AT_GetModemIdFromClient(ucIndex, &enModemId) != VOS_OK)
    {
        AT_ERR_LOG("AT_QryRATCombinePara: Get modem id fail.");

        return AT_ERROR;
    }

    if (TAF_ACORE_NV_READ(enModemId, en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)) != NV_OK)
    {
        AT_ERR_LOG("AT_QryRATCombinePara: Get en_NV_Item_LC_Ctrl_PARA id fail.");

        return AT_ERROR;
    }

    if (stNVData.ucLCEnableFlg != VOS_TRUE)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (stNVData.enRatCombined == TAF_NVIM_LC_RAT_COMBINED_CL)
    {
        usRatMode = 0;
    }
    else if (stNVData.enRatCombined == TAF_NVIM_LC_RAT_COMBINED_GUL)
    {
        usRatMode = 1;
    }
    else
    {
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      usRatMode);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 AT_QryMipiClkValue(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT ??MTA ???????????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_MIPICLK_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryMipiClkValue: send Msg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MIPI_CLK_QRY;

    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryBestFreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_BUTT;
    ulRslt    = AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId);

    /* ????ModemID??????????????Modem0?????????? */
    if ((enModemId != MODEM_ID_0)
     || (ulRslt != VOS_OK))
    {
        AT_WARN_LOG("AT_QryBestFreqPara: Not  Modem0 or fail to get current ModemID!");
        return AT_ERROR;
    }

    /* AT ??MTA???????????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_BESTFREQ_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryBestFreqPara: send Msg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_BESTFREQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_VOID Show_Time(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    PS_PRINTF_INFO("Time:\n");
    PS_PRINTF_INFO("ucIeFlg: %d\n",pstNetCtx->stTimeInfo.ucIeFlg);
    PS_PRINTF_INFO("cLocalTimeZone: %d\n",pstNetCtx->stTimeInfo.cLocalTimeZone);
    PS_PRINTF_INFO("ucDST: %d\n",pstNetCtx->stTimeInfo.ucDST);
#if (FEATURE_DEBUG_PRINT_ADDRESS == FEATURE_ON)
    PS_PRINTF_INFO("ucLSAID: %p\n",pstNetCtx->stTimeInfo.ucLSAID);
#endif
    PS_PRINTF_INFO("cTimeZone: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone);
    PS_PRINTF_INFO("ucYear: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear);
    PS_PRINTF_INFO("ucMonth: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth);
    PS_PRINTF_INFO("ucDay: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay);
    PS_PRINTF_INFO("ucHour: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour);
    PS_PRINTF_INFO("ucMinute: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute);
    PS_PRINTF_INFO("ucSecond: %d\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond);

    return;
}

VOS_UINT32 AT_QryCclkPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    TIME_ZONE_TIME_STRU                 stTime;

    enModemId = MODEM_ID_0;
    memset_s(&stTime, sizeof(stTime), 0x00, sizeof(stTime));

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (ulRslt != VOS_OK)
    {
        AT_ERR_LOG("AT_QryCclkPara: Get modem id fail.");
        return AT_ERROR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    if ((pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_UTLTZ) != NAS_MM_INFO_IE_UTLTZ)
    {
        /* AT ??MTA???????????????? */
        ulRslt = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                        0,
                                        ID_AT_MTA_CCLK_QRY_REQ,
                                        VOS_NULL_PTR,
                                        0,
                                        I0_UEPS_PID_MTA);

        if (ulRslt != TAF_SUCCESS)
        {
            AT_WARN_LOG("AT_QryCclkPara: send Msg fail.");
            return AT_ERROR;
        }

        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCLK_QRY;

        return AT_WAIT_ASYNC_RETURN;

    }

    /* ???????? */
    stTime.cTimeZone = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone;

    /* ?????????? Local time zone,???????????? Local time zone */
    if ((pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_LTZ) == NAS_MM_INFO_IE_LTZ)
    {
        stTime.cTimeZone   = pstNetCtx->stTimeInfo.cLocalTimeZone;
    }

    stTime.ucYear   = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear;
    stTime.ucMonth  = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth;
    stTime.ucDay    = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay;
    stTime.ucHour   = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour;
    stTime.ucMinute = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute;
    stTime.ucSecond = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond;

    AT_PrintCclkTime(ucIndex, &stTime, enModemId);

    return AT_OK;
}

#if (FEATURE_HUAWEI_VP == FEATURE_ON)

VOS_UINT32 AT_QryVoicePreferPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* ????MN_FillAndSndAppReqMsg()??????RABM?????? */
    ulRslt = AT_SndQryVoicePrefer(gastAtClientTab[ucIndex].usClientId,gastAtClientTab[ucIndex].opId);
    if (ulRslt == VOS_OK)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VOICEPREFER_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
#endif
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryCLocInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ??MMA???????????????????? */
    ulRet = TAF_MMA_QryCLocInfoReq(WUEPS_PID_AT,
                                   gastAtClientTab[ucIndex].usClientId,
                                   0);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLOCINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;

}
#endif



VOS_UINT32 AT_QryEmcCallBack( VOS_UINT8 ucIndex  )
{
    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_MMA_QryCurrEmcCallBackMode(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EMCCBM_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#if ((FEATURE_UE_MODE_CDMA == FEATURE_ON)&&(FEATURE_CHINA_TELECOM_VOICE_ENCRYPT == FEATURE_ON))


VOS_UINT32 AT_QryEncryptCallCap( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????ID_TAF_CCM_ECC_SRV_CAP_QRY_REQ???? */
    ulRet = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_ECC_SRV_CAP_QRY_REQ,
                                  0,
                                  enModemId);

    if (ulRet != VOS_OK)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECCAP_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
#if  (FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE == FEATURE_ON)


VOS_UINT32 AT_QryEncryptCallRandom( VOS_UINT8 ucIndex )
{

    VOS_UINT32                          ulRet;

    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????ID_TAF_CCM_GET_EC_RANDOM_REQ???? */
    ulRet = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_GET_EC_RANDOM_REQ,
                                  0,
                                  enModemId);

    if (ulRet != VOS_OK)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECRANDOM_QRY;

    return AT_WAIT_ASYNC_RETURN;

}

VOS_UINT32 AT_QryEncryptCallKmc( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????ID_TAF_CCM_GET_EC_KMC_REQ???? */
    ulRet = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_GET_EC_KMC_REQ,
                                  0,
                                  enModemId);
    if (ulRet != VOS_OK)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECKMC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_UINT32  AT_QryEccTestMode( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????ID_TAF_CCM_GET_EC_TEST_MODE_REQ???? */
    ulRet = TAF_CCM_CallCommonReq(&stCtrl,
                                  VOS_NULL_PTR,
                                  ID_TAF_CCM_GET_EC_TEST_MODE_REQ,
                                  0,
                                  enModemId);

    if (ulRet != VOS_OK)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECCTEST_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
#endif
#endif
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryPrivacyModePreferred(VOS_UINT8 ucIndex)
{
    TAF_CTRL_STRU                       stCtrl;
    MODEM_ID_ENUM_UINT16                enModemId;

    memset_s(&stCtrl, sizeof(stCtrl), 0x00, sizeof(stCtrl));

    /* ???????????????????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCtrl.ulModuleId                   = WUEPS_PID_AT;
    stCtrl.usClientId                   = gastAtClientTab[ucIndex].usClientId;
    stCtrl.ucOpId                       = gastAtClientTab[ucIndex].opId;

    if (AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ????ID_TAF_CCM_PRIVACY_MODE_QRY_REQ???? */
    if (TAF_CCM_CallCommonReq(&stCtrl,
                                       VOS_NULL_PTR,
                                       ID_TAF_CCM_PRIVACY_MODE_QRY_REQ,
                                       0,
                                       enModemId) == VOS_OK)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMP_QRY;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
#endif

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 AT_QryCFreqLockInfo(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_ProcCFreqLockQryReq(WUEPS_PID_AT,
                                                 gastAtClientTab[ucIndex].usClientId,
                                                 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFREQLOCK_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif

}
#endif
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryCdmaCsqPara(VOS_UINT8 ucIndex)
{
    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_ProcCdmaCsqQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CDMACSQ_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


VOS_UINT32 AT_QryTTYModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* AT ??VC ???????????????????? */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_QRY_TTYMODE_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryTTYModePara: send Msg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TTYMODE_READ;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryCtaPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ???????????? */
    if (TAF_PS_GetCtaInfo(WUEPS_PID_AT,
                                    AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                    0) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CTA_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;

#else
    return AT_ERROR;
#endif

}



VOS_UINT32 At_QryRatRfSwitch(VOS_UINT8 ucIndex)
{
    NAS_NV_TRI_MODE_ENABLE_STRU  stTriModeEnableStru;
    NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU  stTriModeFemProfileIdStru;

    memset_s(&stTriModeEnableStru, sizeof(stTriModeEnableStru), 0x00, sizeof(stTriModeEnableStru));
    memset_s(&stTriModeFemProfileIdStru, sizeof(stTriModeFemProfileIdStru), 0x00, sizeof(stTriModeFemProfileIdStru));

    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }


    /* ????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_TRI_MODE_ENABLE, &stTriModeEnableStru, sizeof(stTriModeEnableStru)) != NV_OK)
    {
        AT_WARN_LOG("At_QryRatRfSwitch:read en_NV_Item_TRI_MODE_ENABLE failed");
        return AT_ERROR;
    }

    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &stTriModeFemProfileIdStru, sizeof(stTriModeFemProfileIdStru)) != NV_OK)
    {
        AT_WARN_LOG("At_QryRatRfSwitch:read en_NV_Item_TRI_MODE_FEM_PROFILE_ID failed");
        return AT_ERROR;
    }

    /* ????*/
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d,%u",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            stTriModeEnableStru.usEnable,
                                            stTriModeFemProfileIdStru.ulProfileId);
    return AT_OK;
}

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 AT_Qry1xChanPara(VOS_UINT8 ucIndex)
{
    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_Proc1xChanQryReq(WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_1XCHAN_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }

}
#endif
#endif


VOS_UINT32 AT_QryProRevInUse(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_ProcProRevInUseQryReq(WUEPS_PID_AT,
                                                   gastAtClientTab[ucIndex].usClientId,
                                                   0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVER_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryCasState(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_ProcStateQryReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GETSTA_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryProGetEsn(VOS_UINT8 ucIndex)
{
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_INT32                           slIndex;
    VOS_UINT32                          ulEsn;

    ulEsn = 0;
    memset_s(&stEsnMeId, sizeof(stEsnMeId), 0x00, sizeof(NV_ESN_MEID_STRU));

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ????en_NV_Item_ESN_MEID */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(NV_ESN_MEID_STRU)) != NV_OK)
    {
        AT_WARN_LOG("AT_QryProGetEsn:Read Nvim Failed");
        return AT_ERROR;
    }

    /* ????????????????????????0 ??? */
    if ((stEsnMeId.enEsnMeIDFlag == ESN_ME_ENABLE_FLAG)
     || (stEsnMeId.enEsnMeIDFlag == ESN_MEID_ENABLE_BOTH))
    {
        /* Read from high to low */
        for (slIndex = PS_MIN(stEsnMeId.aucEsn[0], sizeof(stEsnMeId.aucEsn) - 1); slIndex > 0; slIndex--)
        {
            /* Update the current value */
            ulEsn <<= sizeof(stEsnMeId.aucEsn[0]) * 8;

            /* Add lower bits */
            ulEsn |= stEsnMeId.aucEsn[slIndex];
        }

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        ulEsn);

    }
    else
    {
        AT_WARN_LOG("AT_QryProGetEsn: ESN is disabled");
    }

    return AT_OK;
}


VOS_UINT32 AT_QryProGetMeid(VOS_UINT8 ucIndex)
{
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_UINT8                           aucMeId[2*AT_MEID_OCTET_NUM + 1];

    memset_s(&stEsnMeId, sizeof(stEsnMeId), 0x00, sizeof(NV_ESN_MEID_STRU));

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ????en_NV_Item_ESN_MEID */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(NV_ESN_MEID_STRU)) != NV_OK)
    {
        AT_WARN_LOG("AT_QryProGetMeid:Read Nvim Failed");
        return AT_ERROR;
    }

    /* ????????????????????????0 ??? */
    if ((stEsnMeId.enEsnMeIDFlag == MEID_ME_ENABLE_FLAG)
     || (stEsnMeId.enEsnMeIDFlag == ESN_MEID_ENABLE_BOTH))
    {
        AT_Hex2Ascii_Revers(&(stEsnMeId.aucMeID[1]), AT_MEID_OCTET_NUM, aucMeId);
        aucMeId[2*AT_MEID_OCTET_NUM] = '\0';

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %s%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        aucMeId,
                                                        gaucAtCrLf);

    }
    else
    {
        AT_WARN_LOG("AT_QryProGetMeid: MEID is disabled");
    }

    return AT_OK;
}
#endif


VOS_UINT32 AT_QryHighVer(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_ProcCHVerQryReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIGHVER_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryTransModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ????????*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_TRANSMODE_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryTransModePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TRANSMODE_READ;

    return AT_WAIT_ASYNC_RETURN;
}


#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryCdmaDormTimerVal(VOS_UINT8 ucIndex)
{
    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ???????????? */
    if (TAF_PS_ProcCdmaDormTimerQryReq(WUEPS_PID_AT,
                                                 AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                                 0) != VOS_OK)
    {
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DORMTIMER_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}

#endif


VOS_UINT32 AT_QryMccFreqPara(
    VOS_UINT8                           ucIndex
)
{
    AT_CSS_MCC_VERSION_INFO_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        AT_ERR_LOG("AT_QryMccFreqPara: Invalid Cmd Type");

        return AT_ERROR;
    }

    /* Allocating memory for message */
    /*lint -save -e516 */
    pstMsg = (AT_CSS_MCC_VERSION_INFO_REQ_STRU *)AT_ALLOC_MSG_WITH_HDR(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU));
    /*lint -restore */
    if (pstMsg == VOS_NULL_PTR)
    {
        AT_ERR_LOG("AT_QryMccFreqPara: Mem Alloc failed");

        return AT_ERROR;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ?????????? */
    AT_CFG_MSG_HDR(pstMsg, PS_PID_CSS, ID_AT_CSS_MCC_VERSION_INFO_REQ);

    pstMsg->usClientId          = gastAtClientTab[ucIndex].usClientId;

    AT_SEND_MSG(pstMsg);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MCCFREQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryBlackCellListPara(
    VOS_UINT8                           ucIndex
)
{
    AT_CSS_BLACK_CELL_LIST_QUERY_REQ_STRU                  *pstMsg = VOS_NULL_PTR;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        AT_ERR_LOG("AT_QryBlackCellListPara: Invalid Cmd Type");

        return AT_ERROR;
    }

    /* Allocating memory for message */
    /*lint -save -e516 */
    pstMsg = (AT_CSS_BLACK_CELL_LIST_QUERY_REQ_STRU *)AT_ALLOC_MSG_WITH_HDR(sizeof(AT_CSS_BLACK_CELL_LIST_QUERY_REQ_STRU));
    /*lint -restore */

    if (pstMsg == VOS_NULL_PTR)
    {
        AT_ERR_LOG("AT_QryBlackCellListPara: Mem Alloc failed");

        return AT_ERROR;
    }

    TAF_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(AT_CSS_BLACK_CELL_LIST_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(AT_CSS_BLACK_CELL_LIST_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    AT_CFG_MSG_HDR(pstMsg, PS_PID_CSS, ID_AT_CSS_BLACK_CELL_LIST_QUERY_REQ);

    pstMsg->usClientId          = gastAtClientTab[ucIndex].usClientId;

    AT_SEND_MSG(pstMsg);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_BLACKCELLLIST_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryUECenterPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    /* ????????*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_UE_CENTER_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (ulResult != TAF_SUCCESS)
    {
        AT_WARN_LOG("At_QryUEModePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ???????????????? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UE_CENTER_QRY;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryHdrCsqPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_ProcHdrCsqQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HDR_CSQ_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* ???????????????????? */
    }

    return AT_ERROR;

#else
   return AT_ERROR;
#endif

}



VOS_UINT32 AT_QryCurrSidNid(VOS_UINT8 ucIndex)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryCurrSidNid(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNID_QRY;

    return AT_WAIT_ASYNC_RETURN;
#else
        return AT_ERROR;
#endif
}

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryCtRoamInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryCtRoamInfo(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CTROAMINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_UINT32 AT_QryPRLID(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryPrlIdInfo(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRLID_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#endif



VOS_UINT32 AT_QryAfcClkInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);
    if (ulRet != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AFCCLKINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryFratIgnitionInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_FRAT_IGNITION_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryFratIgnitionInfo: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FRATIGNITION_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryPacspPara(VOS_UINT8 ucIndex)
{
    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (TAF_MMA_QryPacspReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PACSP_QRY;

    /* ???????????????????? */
    return AT_WAIT_ASYNC_RETURN;
}


#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 AT_QryNoCardMode(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_NO_CARD_MODE_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);
    if (ulRet != TAF_SUCCESS)
    {
        AT_WARN_LOG("AT_QryNoCardMode: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NOCARDMODE_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryRatCombinedMode(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryRatCombinedMode(WUEPS_PID_AT,
                                       gastAtClientTab[ucIndex].usClientId,
                                       0);
    if (ulRet != VOS_TRUE)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RATCOMBINEDMODE_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#endif


VOS_UINT32 AT_QryFclassPara(VOS_UINT8 ucIndex)
{
    AT_WARN_LOG("AT_QryFclassPara: Not support this command!");
    (VOS_VOID)ucIndex;
    return AT_ERROR;
}


VOS_UINT32 AT_QryGciPara(VOS_UINT8 ucIndex)
{
    AT_WARN_LOG("AT_QryGciPara: Not support this command!");
    (VOS_VOID)ucIndex;
    return AT_ERROR;
}


VOS_UINT32 AT_QryRsrp(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;
    AT_MTA_RS_INFO_QRY_REQ_STRU         stRsInfoQryReq;

    stRsInfoQryReq.enRsInfoType = AT_MTA_RSRP_TYPE;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_RS_INFO_QRY_REQ,
                                   &stRsInfoQryReq,
                                   (VOS_UINT32)sizeof(AT_MTA_RS_INFO_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);
    if (ulRet != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RSRP_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryRsrq(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;
    AT_MTA_RS_INFO_QRY_REQ_STRU         stRsInfoQryReq;

    stRsInfoQryReq.enRsInfoType = AT_MTA_RSRQ_TYPE;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_RS_INFO_QRY_REQ,
                                   &stRsInfoQryReq,
                                   (VOS_UINT32)sizeof(AT_MTA_RS_INFO_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);
    if (ulRet != TAF_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RSRQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCsdfPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstNetCtx->stCsdfCfg.ucMode,
                                                    pstNetCtx->stCsdfCfg.ucAuxMode);


    return AT_OK;
}


VOS_UINT32 AT_QryRejInfoPara(VOS_UINT8 ucIndex)
{

    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (TAF_MMA_QryRejinfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0) == VOS_TRUE)
    {
        /* ???????????????? */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REJINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryLteAttachInfoPara(VOS_UINT8 ucIndex)
{
    /* ???????????? */
    if ( TAF_PS_GetLteAttchInfo(WUEPS_PID_AT,
                                            AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                            gastAtClientTab[ucIndex].opId) != VOS_OK )
    {
        AT_WARN_LOG("AT_QryLteAttachInfoPara: TAF_PS_GetLteAttchInfo fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTEATTACHINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)

VOS_UINT32 AT_QryWakelock(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulWakelockStatu;

    /* ???????? */
    if (g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_READ_CMD)
    {
        return AT_ERROR;
    }

    if (g_stAtWakeLock.active)
    {
        ulWakelockStatu = 1;
    }
    else
    {
        ulWakelockStatu = 0;
    }


    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    "^WAKELOCK",
                                                    ulWakelockStatu,
                                                    gaucAtCrLf);


    return AT_OK;
}
#endif


