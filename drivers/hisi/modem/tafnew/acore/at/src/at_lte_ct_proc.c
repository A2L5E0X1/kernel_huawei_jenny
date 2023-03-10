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

/******************************************************************************
 */
/* PROJECT   :
 */
/* SUBSYSTEM :
 */
/* MODULE    :
 */
/* OWNER     :
 */
/******************************************************************************
 */
/*#include <stdlib.h>
 */
#include "osm.h"
#include "gen_msg.h"

#include "at_lte_common.h"
/*lint --e{7,64,537,322,958,734,813,718,746,830,438,409}*/
#include "ATCmdProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "nv_stru_lps.h"

#include "AtCtx.h"

#include "AtMtCommFun.h"

/*lint -e767 ????:Log????*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_CT_PROC_C
/*lint +e767 */

#if(FEATURE_ON == FEATURE_UE_MODE_NR)
extern AT_MT_INFO_STRU                         g_stMtInfoCtx;
#else
extern AT_DEVICE_CMD_CTRL_STRU                 g_stAtDevCmdCtrl;
#endif

#if(FEATURE_OFF == FEATURE_UE_MODE_NR)
/******************************************************************************
 */
/* ????????: ????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFTXONPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TXON_REQ_STRU stFTXONSetReq = {(FTM_TXON_SWT_ENUM)0, };
    VOS_UINT32 ulRst;

    // ????????


    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].usParaLen == 0)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFTXONSetReq.enSwtich          = (FTM_TXON_SWT_ENUM)(gastAtParaList[0].ulParaValue);
    /* ??????^FTXON=1 ???????? */
    if (stFTXONSetReq.enSwtich == EN_FTM_TXON_UL_RFBBP_OPEN )
    {
        stFTXONSetReq.enCltEnableFlg    = (FTM_CLT_ENABLE_ENUM_UINT8)g_stAtDevCmdCtrl.enCltEnableFlg;
    }  

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TXON_REQ, ucClientId, (VOS_VOID*)(&stFTXONSetReq), sizeof(stFTXONSetReq));

    if(ulRst == AT_SUCCESS)
    {
        /* ????????????????
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FTXON_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ????????????????????
 */
    }

    return AT_ERROR;
}
#endif

VOS_UINT32 atSetFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_TXON_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TXON_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ????????: ????????????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFTXONPara(VOS_UINT8 ucClientId)
{
    FTM_RD_TXON_REQ_STRU stFTXONQryReq = {0};
    VOS_UINT32 ulRst;


    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_RD_TXON_REQ,ucClientId, (VOS_VOID*)(&stFTXONQryReq), sizeof(stFTXONQryReq));

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FTXON_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_TXON_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_TXON_CNF_STRU *)pEvent->ulParam1;


    if(pstCnf == NULL)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FTXON:%d",
        pstCnf->enSwtich);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;



}

VOS_UINT32 atQryFPllStatusPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FPLLSTATUS_REQ_STRU stFPLLSTATUSQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FPLLSTATUS_REQ,ucClientId, (VOS_VOID*)(&stFPLLSTATUSQryReq), sizeof(stFPLLSTATUSQryReq));
    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_FPLLSTATUS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFPllStatusParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_FPLLSTATUS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FPLLSTATUS_CNF_STRU *)pEvent->ulParam1;

    if(pstCnf == NULL)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FPLLSTATUS: %d,%d",
        pstCnf->tx_status,pstCnf->rx_status);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}


/******************************************************************************
 */
/* ????????: ????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFRXONPara(VOS_UINT8 ucClientId)
{
    FTM_SET_RXON_REQ_STRU stFRXONSetReq = {0};
    VOS_UINT32 ulRst;

    /* ????????
 */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].usParaLen == 0)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    stFRXONSetReq.ulRxSwt = gastAtParaList[0].ulParaValue;

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_RXON_REQ,ucClientId, (VOS_VOID*)(&stFRXONSetReq), sizeof(stFRXONSetReq));

    if(ulRst == AT_SUCCESS)
    {
        /* ????????????????
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRXON_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ????????????????????
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_RXON_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_RXON_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ????????: ????????????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFRXONPara(VOS_UINT8 ucClientId)
{
    FTM_RD_RXON_REQ_STRU stFRXONQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_RD_RXON_REQ,ucClientId, (VOS_VOID*)(&stFRXONQryReq), sizeof(stFRXONQryReq));

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRXON_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_RXON_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_RXON_CNF_STRU *)pEvent->ulParam1;


    if(pstCnf == NULL)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FRXON:%d",
        pstCnf->ulRxSwt);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;



}

/******************************************************************************
 */
/* ????????: ????????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFCHANPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCHAN_REQ_STRU stFCHANSetReq = {(FCHAN_MODE_ENUM)0, };
    VOS_UINT32 ulRst;
    /* ????????
 */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gucAtParaIndex != 3)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[0].usParaLen == 0)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[1].usParaLen == 0)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[2].usParaLen == 0)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[3].usParaLen == 0)
    {
        gastAtParaList[3].ulParaValue = 0;
    }

    stFCHANSetReq.enFchanMode = (FCHAN_MODE_ENUM)(gastAtParaList[0].ulParaValue);
    stFCHANSetReq.ucBand = (VOS_UINT8)(gastAtParaList[1].ulParaValue);
    stFCHANSetReq.ulChannel = (gastAtParaList[2].ulParaValue);

    stFCHANSetReq.usListeningPathFlg = (VOS_UINT16)(gastAtParaList[3].ulParaValue);
#if(FEATURE_OFF == FEATURE_UE_MODE_NR)
    (VOS_VOID)AT_SetGlobalFchan((VOS_UINT8)(gastAtParaList[0].ulParaValue));
#endif

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCHAN_REQ,ucClientId, (VOS_VOID*)(&stFCHANSetReq), sizeof(stFCHANSetReq));

    if(ulRst == AT_SUCCESS)
    {
        /* ????????????????
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCHAN_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ????????????????????
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FCHAN_CNF_STRU *pstCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FCHAN_CNF_STRU *)pEvent->ulParam1;

    
    if(pstCnf->ulErrCode == ERR_MSP_SUCCESS)
    {
#if(FEATURE_OFF == FEATURE_UE_MODE_NR)
       (VOS_VOID)AT_SetGlobalFchan((VOS_UINT8)(pstCnf->enFchanMode));
#endif
    }
    

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ????????:
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFWAVEPara(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst;
    FTM_SET_FWAVE_REQ_STRU stFWaveSetReq = { 0 };

    /* ????????
 */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gucAtParaIndex != 2)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[0].usParaLen == 0)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[1].usParaLen == 0)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    stFWaveSetReq.usType  = gastAtParaList[0].ulParaValue;
    stFWaveSetReq.usPower = gastAtParaList[1].ulParaValue;

    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FWAVE_REQ,ucClientId,
        (VOS_VOID*)(&stFWaveSetReq), sizeof(stFWaveSetReq));


    if(ulRst == AT_SUCCESS)
    {
        /* ????????????????
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FWAVE_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ????????????????????
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FWAVE_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FWAVE_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}


/*******************************************************************************/

/* ????????: ???????????????? */

/* ????????:*/

/*   ulIndex [in] ... */

/* ?? ?? ??: */

/*    TODO: ... */
/*******************************************************************************/
VOS_UINT32 atQryFCHANPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FCHAN_REQ_STRU stFCHANQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCHAN_REQ,ucClientId, (VOS_VOID*)(&stFCHANQryReq), sizeof(stFCHANQryReq));

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCHAN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

#define AT_CT_FREQ_INVALID_VALUE                65536  /* 36.101 0-65535
 */

VOS_UINT32 atQryFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
     FTM_RD_FCHAN_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FCHAN_CNF_STRU *)pEvent->ulParam1;


    if(pstCnf == NULL)
    {
        return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FCHAN:%d,%d,%u,%u",
        pstCnf->enFchanMode,
        pstCnf->ucBand,
        pstCnf->ulUlChannel,
        pstCnf->ulDlChannel);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

/******************************************************************************
 */
/* ????????: AT^TSELRF  ????????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
extern VOS_UINT32 g_ulWifiRF;

VOS_UINT32 atSetTselrfPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TSELRF_REQ_STRU stTselrfSetReq = { 0 };
    VOS_UINT32 ulRst = AT_SUCCESS;
    VOS_UINT32 Rst;
    VOS_UINT8 ulPath;

    
    VOS_CHAR acCmd[200]={0};

    

    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if((gucAtParaIndex != 1) &&
       (gucAtParaIndex != 2))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(gastAtParaList[0].usParaLen == 0)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulPath = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    if((ulPath == FTM_TSELRF_FDD_LTE_MAIN)
        || (ulPath == FTM_TSELRF_TDD_LTE_MAIN)
        || (ulPath == FTM_TSELRF_FDD_LTE_SUB)
        || (ulPath == FTM_TSELRF_TDD_LTE_SUB)
        || (ulPath == FTM_TSELRF_FDD_LTE_MIMO)
        || (ulPath == FTM_TSELRF_TDD_LTE_MIMO)
        || (ulPath == FTM_TSELRF_TD))

    {
        stTselrfSetReq.ucPath  = ulPath;
        stTselrfSetReq.ucGroup = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    }
    else if(ulPath == FTM_TSELRF_WIFI)
    {
        /*lint -e774*/
        if(ulRst == ERR_MSP_SUCCESS)
        /*lint +e774*/
        {
            /*WIFI??Enable????????????*/
            if((VOS_UINT32)WIFI_GET_STATUS() == VOS_FALSE)
            {
                return AT_ERROR;
            }

            if((gastAtParaList[1].ulParaValue != 0) && (gastAtParaList[1].ulParaValue != 1))
            {
                return AT_ERROR;
            }

            g_ulWifiRF = gastAtParaList[1].ulParaValue;


            Rst = (VOS_UINT32)VOS_sprintf_s(acCmd, (VOS_SIZE_T)sizeof(acCmd), "wl txchain %d", (gastAtParaList[1].ulParaValue + 1));
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            Rst = (VOS_UINT32)VOS_sprintf_s(acCmd, (VOS_SIZE_T)sizeof(acCmd), "wl rxchain %d", (gastAtParaList[1].ulParaValue + 1));
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);


            Rst = (VOS_UINT32)VOS_sprintf_s(acCmd, (VOS_SIZE_T)sizeof(acCmd), "wl txant %d", gastAtParaList[1].ulParaValue);
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            Rst = (VOS_UINT32)VOS_sprintf_s(acCmd, (VOS_SIZE_T)sizeof(acCmd), "wl antdiv %d", gastAtParaList[1].ulParaValue);
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            return AT_OK;
        }
    }
    else
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TSELRF_REQ, ucClientId,(VOS_VOID*)(&stTselrfSetReq), sizeof(stTselrfSetReq));

    if(ulRst == AT_SUCCESS)
    {
        /* ????????????????
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TSELRF_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ????????????????????
 */
    }

    return ulRst;
}
VOS_UINT32 atSetTselrfParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_TSELRF_CNF_STRU* pstCnf = NULL;

    HAL_SDMLOG("\n enter atSetTselrfParaCnfProc !!!\n");

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TSELRF_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ????????: AT^TSELRF  ????????????????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */

VOS_UINT32 atQryTselrfPara(VOS_UINT8 ucClientId)
{
/*
????????????????????????????????????????????????NV??????:
10000 NV_WG_RF_MAIN_BAND
0xD22C NV_ID_UE_CAPABILITY
0xD304 EN_NV_ID_TDS_SUPPORT_FREQ_BAND
*/
    return AT_OK;
}
/******************************************************************************
 */
/* ????????: ??????????LNA??????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFLNAPara(VOS_UINT8 ucClientId)
{
    FTM_SET_AAGC_REQ_STRU stFLNASetReq = {0};
    VOS_UINT32 ulRst;

    /* ????????
 */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].usParaLen == 0)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFLNASetReq.ucAggcLvl = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_AAGC_REQ,ucClientId, (VOS_VOID*)(&stFLNASetReq), sizeof(stFLNASetReq));

    if(ulRst == AT_SUCCESS)
    {
        /* ????????????????
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FLNA_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ????????????????????
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_AAGC_CNF_STRU *pstCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_AAGC_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ????????: ??????????LNA??????
 */
/*
 */
/* ????????:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* ?? ?? ??:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFLNAPara(VOS_UINT8 ucClientId)
{
    FTM_RD_AAGC_REQ_STRU stFLNAQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_RD_AAGC_REQ,ucClientId, (VOS_VOID*)(&stFLNAQryReq), sizeof(stFLNAQryReq));

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FLNA_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_AAGC_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_AAGC_CNF_STRU *)pEvent->ulParam1;


    if(pstCnf == NULL)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FLNA:%d",
        pstCnf->ucAggcLvl);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}

/*******************************************************************************/

/* ????????: ????RSSI*/

/* ????????: */

/*   ulIndex [in] ... */

/* ?? ?? ??: */

/*    TODO: ... */

/*******************************************************************************/
VOS_UINT32 atQryFRSSIPara(VOS_UINT8 ucClientId)
{
    FTM_FRSSI_REQ_STRU stFRssiQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_FRSSI_REQ,ucClientId, (VOS_VOID*)(&stFRssiQryReq), sizeof(stFRssiQryReq));

    if(ulRst == AT_SUCCESS)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRSSI_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFRSSIParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_FRSSI_CNF_STRU *pstCnf = NULL;
    VOS_UINT16 usLength;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_FRSSI_CNF_STRU *)pEvent->ulParam1;

    if(pstCnf == NULL)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;

    /* ????V7R5????4RX??????GU??????????????????0??L????FTM??????????????4RX????????4??????????????????1???? */
#if (FEATURE_LTE_4RX == FEATURE_ON)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                                        "^FRSSI:%d,%d,%d,%d",
                                        pstCnf->lValue1,
                                        pstCnf->lValue2,
                                        pstCnf->lValue3,
                                        pstCnf->lValue4);
#elif (FEATURE_LTE_8RX == FEATURE_ON)
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                                        "^FRSSI:%d",
                                        pstCnf->lValue1);
#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                                        "^FRSSI:%d", pstCnf->lValue1);
#endif

    CmdErrProc(ucClientId, pstCnf->ulErrCode,usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}


VOS_UINT32 AT_GetLteFeatureInfo(AT_FEATURE_SUPPORT_ST*pstFeATure)
{
    VOS_UINT32 ulRst;

    VOS_UINT8 ucBandStr[AT_FEATURE_BAND_STR_LEN_MAX] = {0};
    VOS_UINT8 ucBandFlag = 0;

    VOS_UINT32 ulStrlen1=0;
    VOS_UINT32 i =0;

    VOS_UINT32  ulBandNv = 0;
    VOS_UINT32  ulBandNum[AT_FEATURE_LTE_MAX_SUPPORT_BAND + 1]={0};
    LRRC_NV_UE_EUTRA_CAP_STRU *pstEutraCap = NULL;

    pstEutraCap = VOS_MemAlloc(WUEPS_PID_AT, (DYNAMIC_MEM_PT), sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));

    if( pstEutraCap == NULL)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    MSP_MEMSET(pstEutraCap, (VOS_SIZE_T)sizeof(LRRC_NV_UE_EUTRA_CAP_STRU), 0x00, (VOS_SIZE_T)sizeof(LRRC_NV_UE_EUTRA_CAP_STRU ));

    ulRst = TAF_ACORE_NV_READ(MODEM_ID_0, EN_NV_ID_UE_CAPABILITY,pstEutraCap,sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
        return ERR_MSP_FAILURE;
    }

    /* RRC_MAX_NUM_OF_BANDS */

    pstEutraCap->stRfPara.usCnt = AT_MIN(pstEutraCap->stRfPara.usCnt, RRC_MAX_NUM_OF_BANDS);
    for( i = 0; i < pstEutraCap->stRfPara.usCnt; i++ )
    {
        if( pstEutraCap->stRfPara.astSuppEutraBandList[i].ucEutraBand > 0 )
        {
            ulBandNv=pstEutraCap->stRfPara.astSuppEutraBandList[i].ucEutraBand;
            if( ulBandNv < (AT_FEATURE_LTE_MAX_SUPPORT_BAND + 1) )
            {
                ulBandNum[ulBandNv]=1;
                ucBandFlag++;
            }
        }
    }

    /*????????LTE band????
 */
    if( ucBandFlag > 0 )
    {
        pstFeATure[AT_FEATURE_LTE].ucFeatureFlag = AT_FEATURE_EXIST;
    }
    else
    {
        VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
        return ERR_MSP_FAILURE;
    }

    for( i = 1 ; i < AT_FEATURE_LTE_MAX_SUPPORT_BAND + 1; i++ )
    {
        if( ulBandNum[i] == 1 )
        {
            ulStrlen1 +=(VOS_UINT32) At_sprintf(AT_FEATURE_BAND_STR_LEN_MAX,(VOS_CHAR* )ucBandStr,(VOS_CHAR* )(ucBandStr+ulStrlen1),"B%d,",i);
        }
    }

    for( i = 1 ; i < ulStrlen1; i++ )
    {
        pstFeATure[AT_FEATURE_LTE].aucContent[i - 1] = ucBandStr[i - 1];
    }

    for( i = 0 ; i < ulStrlen1; i++ )
    {
        ucBandStr[i] = 0;
    }

    ulStrlen1 = 0;

    VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
    return ERR_MSP_SUCCESS;

}


VOS_UINT32 atSetTBATPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TBAT_REQ_STRU stTbatSet ={0};
    FTM_RD_TBAT_REQ_STRU  stTbatRd={0};

    VOS_UINT8  ucType;
    VOS_UINT8  ucOpr;
    VOS_UINT16 usValue = 0;
    VOS_UINT32 ulRst;

    /* ???????? */
    if(g_stATParseCmd.ucCmdOptType != AT_CMD_OPT_SET_PARA_CMD)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex > 4)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((gastAtParaList[0].usParaLen == 0) ||
       (gastAtParaList[1].usParaLen == 0) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucType = (VOS_UINT8)(gastAtParaList[0].ulParaValue);
    ucOpr = (VOS_UINT8)(gastAtParaList[1].ulParaValue);

    if( ucOpr == 1 )
    {
        /* ???? */
        if(gastAtParaList[2].usParaLen != 0)
        {
            usValue = gastAtParaList[2].usParaLen;

            stTbatSet.ucOpr = ucOpr;
            stTbatSet.ucType = ucType;
            stTbatSet.usValueMin = (VOS_UINT16)gastAtParaList[2].ulParaValue;
            stTbatSet.usValueMax = (VOS_UINT16)gastAtParaList[3].ulParaValue;

            HAL_SDMLOG("\n stTbatSet.usValueMin=%d,stTbatSet.usValueMax=%d\n",stTbatSet.usValueMin,stTbatSet.usValueMax);

            ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TBAT_REQ,ucClientId, (VOS_VOID*)(&stTbatSet), sizeof(stTbatSet));
            if(ulRst == AT_SUCCESS)
            {
                gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TBAT_SET;
                return AT_WAIT_ASYNC_RETURN;
            }
            return AT_ERROR;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else if( ucOpr == 0 )
    {
        /* ???? */
        usValue = (VOS_UINT16)gastAtParaList[2].usParaLen;

        stTbatRd.ucOpr = ucOpr;
        stTbatRd.ucType = ucType;
        stTbatRd.usValue = usValue;

        ulRst = atSendFtmDataMsg(I0_MSP_SYS_FTM_PID, ID_MSG_FTM_RD_TBAT_REQ,ucClientId, (VOS_VOID*)(&stTbatRd), sizeof(stTbatRd));
        if(ulRst == AT_SUCCESS)
        {
            gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TBAT_READ;
            return AT_WAIT_ASYNC_RETURN;
        }
        return AT_ERROR;

    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
}


VOS_UINT32 atSetTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_SET_TBAT_CNF_STRU *pstCnf=NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TBAT_CNF_STRU *)pEvent->ulParam1;
    HAL_SDMLOG("\n enter into atSetTbatCnf\n");
    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    return AT_OK;
}

VOS_UINT32 atRdTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_RD_TBAT_CNF_STRU *pstCnf=NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_TBAT_CNF_STRU *)pEvent->ulParam1;
    HAL_SDMLOG("\n enter into atRdTbatCnf\n");
    HAL_SDMLOG("\n pstCnf->ucType=%d,pstCnf->usValue=%d \n",(VOS_INT)pstCnf->ucType,(VOS_INT)pstCnf->usValue);

    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "^TBAT:%d,%d",
                                               pstCnf->ucType,pstCnf->usValue
                                             );

    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);

    return AT_OK;
}

#if(FEATURE_OFF == FEATURE_UE_MODE_NR)

VOS_UINT32 At_ProcLteTxCltInfoReport(VOS_VOID *pMsgBlock)
{
    FTM_CLT_INFO_IND_STRU              *pstTxCltInfoInd = VOS_NULL_PTR;
    OS_MSG_STRU                        *pstpOsMsg       = VOS_NULL_PTR;

    pstpOsMsg       = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstTxCltInfoInd = (FTM_CLT_INFO_IND_STRU *)pstpOsMsg->ulParam1;

    /* ?????????????? */
    MSP_MEMSET(&g_stAtDevCmdCtrl.stCltInfo, sizeof(g_stAtDevCmdCtrl.stCltInfo), 0x0, sizeof(AT_TX_CLT_INFO_STRU));

    /* ????CLT???????????? */
    g_stAtDevCmdCtrl.stCltInfo.ulInfoAvailableFlg   = VOS_TRUE;   

    /* ?????????????????????????????????? */
    g_stAtDevCmdCtrl.stCltInfo.shwGammaReal             = pstTxCltInfoInd->shwGammaReal;                 /* ???????????? */  
    g_stAtDevCmdCtrl.stCltInfo.shwGammaImag             = pstTxCltInfoInd->shwGammaImag;                 /* ???????????? */
    g_stAtDevCmdCtrl.stCltInfo.ushwGammaAmpUc0          = pstTxCltInfoInd->ushwGammaAmpUc0;              /* ????????????0???????????? */   
    g_stAtDevCmdCtrl.stCltInfo.ushwGammaAmpUc1          = pstTxCltInfoInd->ushwGammaAmpUc1;              /* ????????????1???????????? */
    g_stAtDevCmdCtrl.stCltInfo.ushwGammaAmpUc2          = pstTxCltInfoInd->ushwGammaAmpUc2;              /* ????????????2???????????? */
    g_stAtDevCmdCtrl.stCltInfo.ushwGammaAntCoarseTune   = pstTxCltInfoInd->ushwGammaAntCoarseTune;       /* ???????????? */
    g_stAtDevCmdCtrl.stCltInfo.ulwFomcoarseTune         = pstTxCltInfoInd->ulwFomcoarseTune;             /* ????FOM?? */
    g_stAtDevCmdCtrl.stCltInfo.ushwCltAlgState          = pstTxCltInfoInd->ushwCltAlgState;              /* ???????????????? */
    g_stAtDevCmdCtrl.stCltInfo.ushwCltDetectCount       = pstTxCltInfoInd->ushwCltDetectCount;           /* ?????????????? */
    g_stAtDevCmdCtrl.stCltInfo.ushwDac0                 = pstTxCltInfoInd->ushwDac0;                     /* DAC0 */
    g_stAtDevCmdCtrl.stCltInfo.ushwDac1                 = pstTxCltInfoInd->ushwDac1;                     /* DAC1 */
    g_stAtDevCmdCtrl.stCltInfo.ushwDac2                 = pstTxCltInfoInd->ushwDac2;                     /* DAC2 */
    g_stAtDevCmdCtrl.stCltInfo.ushwDac3                 = pstTxCltInfoInd->ushwDac3;                     /* DAC3 */

    return VOS_TRUE;
}
#endif


