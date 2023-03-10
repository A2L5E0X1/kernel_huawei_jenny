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
#include "AtCmdAgpsProc.h"
#include "ATCmdProc.h"
#include "AtCmdAgpsProc.h"
#include "AtMsgPrint.h"
#include "securec.h"


/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_AGPS_PROC_C

/*****************************************************************************
  2 ????????????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/

VOS_UINT32 At_SetEpduPara(VOS_UINT8 ucIndex)
{
    errno_t                             lMemResult;
    AT_MTA_EPDU_SET_REQ_STRU            stAtCmd;
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usEpduLen;

    /* ???????? */
    if (gucAtParaIndex != AT_CMD_EPDU_PARA_NUM)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[7].usParaLen > AT_MTA_EPDU_NAME_LENGTH_MAX)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[10].usParaLen > AT_MTA_EPDU_CONTENT_STRING_LEN_MAX)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* gastAtParaList[8].ulParaValue????total???? gastAtParaList[9].ulParaValue????index??
       ????total??????index??????????
    */
    if (gastAtParaList[8].ulParaValue < gastAtParaList[9].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usEpduLen = 0;

    /* AT??????MTA?????????????? */
    memset_s(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_EPDU_SET_REQ_STRU));
    stAtCmd.usTransactionId     = (VOS_UINT16)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMsgBodyType       = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucCommonIEValidFlg  = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucEndFlag           = (VOS_UINT8)gastAtParaList[3].ulParaValue;
    stAtCmd.ucLocSource         = (VOS_UINT8)gastAtParaList[4].ulParaValue;
    stAtCmd.ucLocCalcErr        = (VOS_UINT8)gastAtParaList[5].ulParaValue;
    stAtCmd.ucId                = (VOS_UINT8)gastAtParaList[6].ulParaValue;
    stAtCmd.ucTotalNum          = (VOS_UINT8)gastAtParaList[8].ulParaValue;
    stAtCmd.ucIndex             = (VOS_UINT8)gastAtParaList[9].ulParaValue;

    if (gastAtParaList[7].usParaLen != 0)
    {
        stAtCmd.ucNameLength    = (VOS_UINT8)gastAtParaList[7].usParaLen;
        lMemResult = memcpy_s(stAtCmd.aucName, AT_MTA_EPDU_NAME_LENGTH_MAX, gastAtParaList[7].aucPara, gastAtParaList[7].usParaLen);
        TAF_MEM_CHK_RTN_VAL(lMemResult, AT_MTA_EPDU_NAME_LENGTH_MAX, gastAtParaList[7].usParaLen);
    }

    if (gastAtParaList[10].usParaLen != 0)
    {
        usEpduLen = gastAtParaList[10].usParaLen;

        if (At_AsciiNum2HexString(gastAtParaList[10].aucPara, &usEpduLen) == AT_FAILURE)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        stAtCmd.usEpduLength = usEpduLen;
        lMemResult = memcpy_s(stAtCmd.aucEpduContent, AT_MTA_EPDU_CONTENT_LENGTH_MAX, gastAtParaList[10].aucPara, usEpduLen);
        TAF_MEM_CHK_RTN_VAL(lMemResult, AT_MTA_EPDU_CONTENT_LENGTH_MAX, usEpduLen);
    }

    /* ??????????C?????? */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_EPDU_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_EPDU_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EPDU_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

VOS_UINT32 AT_RcvMtaEpduDataInd(
    VOS_VOID                           *pMsg
)
{
    errno_t                             lMemResult;
    VOS_UINT8                          *pucName                 = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                    *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_EPDU_DATA_IND_STRU          *pstMtaAtEpduDataInd     = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ?????? */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtEpduDataInd     = (MTA_AT_EPDU_DATA_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex                 = 0;
    usLength                = 0;

    /* ????ClientId????ucIndex */
    if ( At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex) == AT_FAILURE )
    {
        AT_WARN_LOG("AT_RcvMtaEpduDataInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ????^EPDUR: */
    /* transaction_id, msg_type, common_info_valid_flg, end_flag, id*/
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d,%d,",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_EPDUR].pucText,
                                       pstMtaAtEpduDataInd->usTransactionID,
                                       pstMtaAtEpduDataInd->ucMsgBodyType,
                                       pstMtaAtEpduDataInd->ucCommonIEValidFlg,
                                       pstMtaAtEpduDataInd->ucEndFlg,
                                       pstMtaAtEpduDataInd->ucID
                                       );

    /* name */
    if (pstMtaAtEpduDataInd->ucNameLength > 0)
    {
        pucName = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, pstMtaAtEpduDataInd->ucNameLength + 1);

        /* ?????????????????????? */
        if (pucName == VOS_NULL_PTR)
        {
            AT_ERR_LOG("AT_RcvMtaEpduDataInd: name, Alloc mem fail");

            return VOS_ERR;
        }

        lMemResult = memcpy_s(pucName, pstMtaAtEpduDataInd->ucNameLength,pstMtaAtEpduDataInd->aucName, pstMtaAtEpduDataInd->ucNameLength);
        TAF_MEM_CHK_RTN_VAL(lMemResult, pstMtaAtEpduDataInd->ucNameLength, pstMtaAtEpduDataInd->ucNameLength);

        pucName[pstMtaAtEpduDataInd->ucNameLength] = '\0';

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "\"%s\"",
                                       pucName
                                       );

        PS_MEM_FREE(WUEPS_PID_AT, pucName);
    }

    /* total, index */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",%d,%d,",
                                   pstMtaAtEpduDataInd->ucTotal,
                                   pstMtaAtEpduDataInd->ucIndex
                                   );

    for (i = 0; i < pstMtaAtEpduDataInd->usDataLength; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%02X",
                                           pstMtaAtEpduDataInd->aucData[i]);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "%s",
                                  gaucAtCrLf
                                  );

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaEpduSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg     = VOS_NULL_PTR;
    MTA_AT_EPDU_SET_CNF_STRU           *pstEpduSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ?????? */
    pstRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstEpduSetCnf         = (MTA_AT_EPDU_SET_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex               = 0;
    ulResult              = AT_ERROR;

    /* ????clientid????index */
    if (At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex) == AT_FAILURE)
    {
        AT_WARN_LOG("AT_RcvMtaEpduSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEpduSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ????AT???????????????????? */
    if (gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_EPDU_SET)
    {
        AT_WARN_LOG("AT_RcvMtaEpduSetCnf : Current Option is not AT_CMD_EPDU_SET.");
        return VOS_ERR;
    }

    /* ????AT???? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?????????????? */
    gstAtSendData.usBufLen = 0;

    if (pstEpduSetCnf->enResult == MTA_AT_RESULT_NO_ERROR)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


