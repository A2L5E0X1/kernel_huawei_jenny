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

#include "product_config.h"
#include <mdrv_diag_system.h>
#include "NVIM_Interface.h"
#include "AtAppVcomInterface.h"
#include "nv_stru_sys.h"
#include "acore_nv_stru_msp.h"
#include "msp_diag_comm.h"
#include "msp_diag.h"
#include <eagleye.h>
#include "chr_om.h"
#include "chr_cfg.h"
//#include <msp_tag.h>




#define    THIS_FILE_ID        PS_FILE_ID_OM_ERRORLOG_C

#undef THIS_MODU
#define THIS_MODU "mdm_chr"

#if (FEATURE_ON == FEATURE_CHR_OM)

VOS_UINT32                              g_ulChrOmAcpuDbgFlag = VOS_FALSE;

OM_APP_MSG_RECORD_STRU                  g_stOmAppMsgRecord; /* OM????AP???????????????????????? */

struct semaphore                        g_stOmRxErrorLogBuffSem;

OM_VCOM_DEBUG_INFO                      g_stErrLogVcomDebugInfo   = {0};

OM_ERR_LOG_DEBUG_INFO                   g_stRcvUESendAP           = {0};

HTIMER                                  g_AcpuErrLogFullTmr       = VOS_NULL_PTR ;/*????????????????*/

HTIMER                                  g_AcpuCltInfoFullTmr      = VOS_NULL_PTR ;/*????????????????*/

/* ???????????????????????????????????????????????????? */
VOS_UINT64                              g_ulTriggerTime64Bit = 0;

NV_ID_CHR_CONFIG_CTRL_INFO_STRU         g_stChrFaultMapGutl = {0};
NV_ID_CHR_C_CONFIG_CTRL_INFO_STRU       g_stChrFaultMapCdma = {0};

/* 1??????????????????????????????MTA????????????????OM???? */
VOS_UINT32                              g_AcpuCtlInfoCnfNotNeedProcess = 0;
VOS_UINT8                               g_ucErrRptFlag[256] = {0};


#define CHR_LogReport(fmt, ...)  \
    DIAG_LogReport(DIAG_GEN_LOG_MODULE(0, 0, 1), MSP_PID_CHR, "chr_om", __LINE__, "%s:"fmt, __FUNCTION__, ##__VA_ARGS__)
#define OM_ERRLOG_MAX_CFG_LEN 1024


VOS_VOID  OM_ChrOpenLog(VOS_UINT32 ulFlag)
{
    g_ulChrOmAcpuDbgFlag = ulFlag;

    return;
}


VOS_VOID OM_AcpuRcvMsgFinish(VOS_VOID)
{
    OM_APP_REPORT_STATUS_STRU               stOmAppReportStatus={{0,},0,0,0,0,0,0};

    (VOS_VOID)VOS_MemSet_s(&stOmAppReportStatus, sizeof(stOmAppReportStatus), 0, (VOS_UINT32)(sizeof(OM_APP_REPORT_STATUS_STRU)));

    stOmAppReportStatus.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_ERR_REPORT_END;
    stOmAppReportStatus.stOmHeader.ulMsgSN   = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;
    stOmAppReportStatus.stOmHeader.ulMsgLen  = (sizeof(OM_APP_REPORT_STATUS_STRU) - sizeof(OM_ALARM_MSG_HEAD_STRU));
    stOmAppReportStatus.usModemID            = g_stOmAppMsgRecord.usModemId;
    stOmAppReportStatus.usFaultID            = g_stOmAppMsgRecord.usFaultId;
    stOmAppReportStatus.ulReportStatus       = g_stOmAppMsgRecord.ulErrLogReportSend;
   (VOS_VOID)mdrv_timer_get_accuracy_timestamp(&stOmAppReportStatus.ulTrigHighSlice,&stOmAppReportStatus.ulTrigLowSlice);

    OM_AcpuSendVComData((VOS_UINT8 *)&stOmAppReportStatus,(VOS_UINT32)sizeof(OM_APP_REPORT_STATUS_STRU));
    VOS_MemSet_s(g_ucErrRptFlag, sizeof(g_ucErrRptFlag),OM_MSG_RECEIVE_FLAG, 256*sizeof(VOS_UINT8));
    /* ?????????????????????? */
    g_stOmAppMsgRecord.ulErrLogReportSend   = OM_AP_SEND_MSG_FINISH;
    g_stOmAppMsgRecord.ulErrLogState        = ERRLOG_IDLE;
    chr_print("success!\r\n ");
    return ;
}



VOS_VOID OM_AcpuSendAppResult(VOS_UINT32 ulRest, VOS_UINT16  usModemId)
{
    OM_APP_RESULT_CNF_STRU               stOmAppResultCnf={{0,},0,0,0,0};


    (VOS_VOID)VOS_MemSet_s(&stOmAppResultCnf, sizeof(stOmAppResultCnf), 0, (VOS_UINT32)sizeof(OM_APP_RESULT_CNF_STRU));

    stOmAppResultCnf.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_RESULT;
    stOmAppResultCnf.stOmHeader.ulMsgSN   = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;
    stOmAppResultCnf.stOmHeader.ulMsgLen  = (sizeof(OM_APP_RESULT_CNF_STRU) - sizeof(OM_ALARM_MSG_HEAD_STRU));
    stOmAppResultCnf.usModemID            = usModemId;
    stOmAppResultCnf.ulStatus             = ulRest;

    OM_AcpuSendVComData((VOS_UINT8 *)&stOmAppResultCnf, (VOS_UINT32)sizeof(OM_APP_RESULT_CNF_STRU));
    chr_print("Result response success. status = 0x%x!\r\n ",ulRest);
    return ;
}


VOS_VOID OM_AcpuSetRptFlag(VOS_UINT id)
{
    VOS_UINT i,j;

    i = id/32;
    j = id%32;

    g_stOmAppMsgRecord.ulErrRptFlag[i] |= 1<<j;

    return;
}


VOS_VOID OM_AcpuSendSkipPid(VOS_UINT32 index)
{
    if(g_stOmAppMsgRecord.ulErrLogReportSend > 0)
    {
        OM_AcpuSetRptFlag(index);
        g_stOmAppMsgRecord.ulErrLogReportSend--;
    }
}


VOS_INT OM_AcpuRcvAppMsgCheck(APP_OM_REQ_ERR_LOG_STRU *pstAppOmReqErrLog)
{

    /* ???????????????? */
    if ((OM_AP_SEND_MSG_FINISH != g_stOmAppMsgRecord.ulErrLogReportSend)
        || (ERRLOG_IDLE != g_stOmAppMsgRecord.ulErrLogState))
    {

        chr_print("error log report not end. reportsend = %d!\r\n ", g_stOmAppMsgRecord.ulErrLogReportSend);

        return OM_APP_REPORT_NOT_FINISH_ERR;
    }

    return VOS_OK;
}

VOS_VOID OM_AcpuClearSendFlagAll(VOS_VOID)
{
    VOS_MemSet_s(g_stOmAppMsgRecord.ulErrSendFlag, 4*sizeof(VOS_UINT32), 0, 4*sizeof(VOS_UINT32));
    VOS_MemSet_s(g_stOmAppMsgRecord.ulErrRptFlag, 4*sizeof(VOS_UINT32), 0, 4*sizeof(VOS_UINT32));
    return;
}

VOS_VOID OM_AcpuSetSendFlag(VOS_UINT id)
{
    VOS_UINT i,j;

    i = id/32;
    j = id%32;

    g_stOmAppMsgRecord.ulErrSendFlag[i] |= 1<<j;

    return;
}


VOS_BOOL OM_AcpuChkRptFlag(VOS_UINT id)
{
    VOS_UINT i,j;

    i = id/32;
    j = id%32;

    if(g_stOmAppMsgRecord.ulErrRptFlag[i] & (1<<j))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_INT OM_AcpuGetFaultMap(VOS_UINT32 ulModemId,VOS_UINT32 ulFaultId, VOS_UINT* ulFaultIdNum, FAULTID_MAP **FaultMap)
{
    VOS_UINT ulRest;

    if(ulFaultId < CHR_FAULTID_GUTL_MAX)
    {
        if(0 == g_stChrFaultMapGutl.ulFaultIdNum)
        {
            ulRest = mdrv_nv_readex(ulModemId, NV_ID_ErrLogGutlCtrlInfo,
                           (VOS_VOID*)&g_stChrFaultMapGutl,
                           sizeof(NV_ID_CHR_CONFIG_CTRL_INFO_STRU));
        }

        *ulFaultIdNum = g_stChrFaultMapGutl.ulFaultIdNum;
        *FaultMap     = g_stChrFaultMapGutl.aucFaulIdMap;

        return VOS_OK;
    }
    else if(ulFaultId < CHR_FAULTID_CDMA_MAX)
    {
        if(0 == g_stChrFaultMapCdma.ulFaultIdNum)
        {
            ulRest = mdrv_nv_readex(ulModemId, NV_ID_ErrLogCdmaCtrlInfo,
                           (VOS_VOID*)&g_stChrFaultMapCdma,
                           sizeof(NV_ID_CHR_C_CONFIG_CTRL_INFO_STRU));
        }

        *ulFaultIdNum = g_stChrFaultMapCdma.ulFaultIdNum;
        *FaultMap     = g_stChrFaultMapCdma.aucFaulIdMap;

        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

VOS_INT OM_AcpuGetFaultCfg(VOS_UINT32 ulFaultId, VOS_UINT32 ulModemId, VOS_UINT32 *ulNvId,
                           NV_ID_CHR_FAULTID_CONFIG_STRU *pFaultCfg)
{
    VOS_UINT    ulRest;
    VOS_UINT    i = 0;
    VOS_UINT    ulFaultIdNum;
    FAULTID_MAP *FaultMap = VOS_NULL_PTR;
    VOS_UINT nvid = (VOS_UINT32)(-1);
  //  OM_APP_MSG_RECORD_STRU *pstAppOmReqErrLog = &g_stOmAppMsgRecord;

    ulRest = OM_AcpuGetFaultMap(ulModemId,ulFaultId, &ulFaultIdNum, &FaultMap);
    if(VOS_OK != ulRest)
    {
        chr_print("get faultmap error. faultid =  %d!\n",ulFaultId);
        return OM_APP_GET_NVID_ERR;
    }

    if(CHR_FAULTID_NUM_MAX < ulFaultIdNum)
    {
        chr_print("faultid num is too large. faultidnum =  %d, faultid = %d!\n",ulFaultIdNum, ulFaultId);
        return OM_APP_GET_NVID_ERR;
    }

    for(i=0 ;i<ulFaultIdNum; i++)
    {
        if(ulFaultId == FaultMap[i].usFaultId)
        {
            nvid = FaultMap[i].ulNvId;
        }
    }
    if((VOS_UINT32)(-1) == nvid)
    {
        chr_print("no nvid matched. faultidnum = %d. faultid = %d!\n",ulFaultIdNum, ulFaultId);
        return OM_APP_READ_NV_ERR;
    }
    *ulNvId = nvid;

    ulRest = mdrv_nv_readex(ulModemId, nvid, (VOS_VOID*)pFaultCfg,
                        sizeof(NV_ID_CHR_FAULTID_CONFIG_STRU));
    if (VOS_OK != ulRest)
    {
        chr_print("alarmid nv read failed. nvid = %d, modemid = %d!\n",nvid, ulModemId);
        return OM_APP_READ_NV_ERR;
    }

    if(ulFaultId != pFaultCfg->ulFaultId)
    {
        chr_print("pFaultCfg->ulFaultId wrong!nvid = %d, modemid = %d, faultid = %d, cfgfaultid = %d!\n",
            nvid, ulModemId, ulFaultId, pFaultCfg->ulFaultId);

        return OM_APP_READ_NV_ERR;
    }

    return VOS_OK;
}

VOS_INT OM_AcpuSendReq(VOS_UINT32 *pulSendCount)
{
    NV_ID_CHR_FAULTID_CONFIG_STRU      *pFaultCfg = &g_stOmAppMsgRecord.stFaultCfg;
    OM_ERR_LOG_REPORT_REQ_STRU         *pstOmErrLogReportReq = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          RecvPid;
    VOS_UINT32                          AlarmId;
    VOS_UINT32                          ulSendPidCount = 0;

    for (i=0; i<pFaultCfg->ulAlarmNum; i++)
    {

        RecvPid = pFaultCfg->aucAlarmMap[i].ulPid;
        AlarmId = pFaultCfg->aucAlarmMap[i].ulAlarmId;

        /* if pid is invalid, skip it! */
        if(VOS_PID_AVAILABLE != VOS_CheckPidValidity(RecvPid))
        {
            OM_AcpuSendSkipPid(i);
            chr_print("Index[%d]: Pid 0x%x Alarmid 0x%x is invalid, Skip it!\n",
                i, RecvPid, AlarmId);
            continue;
        }

        /* ????????PID???????? */
        ulSendPidCount++;
        pstOmErrLogReportReq  = (OM_ERR_LOG_REPORT_REQ_STRU*)VOS_AllocMsg(MSP_PID_CHR,
                                 (sizeof(OM_ERR_LOG_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH));
        if (VOS_NULL_PTR == pstOmErrLogReportReq)
        {
            chr_print("Alloc Req Msg failed!\n");
            return OM_APP_MEM_ALLOC_MSG_ERR;
        }

        pstOmErrLogReportReq->ulReceiverPid = RecvPid;
        pstOmErrLogReportReq->ulMsgName     = ID_OM_ERR_LOG_REPORT_REQ;
        pstOmErrLogReportReq->usModemID     = g_stOmAppMsgRecord.usModemId;
        pstOmErrLogReportReq->usFaultID     = g_stOmAppMsgRecord.usFaultId;
        pstOmErrLogReportReq->usAlarmID     = AlarmId;
        pstOmErrLogReportReq->ulMsgSN       = g_stOmAppMsgRecord.ulMsgSN;

        if(VOS_OK != VOS_SendMsg(MSP_PID_CHR, pstOmErrLogReportReq))
        {
            chr_print("send pid 0x%x, Alarmid 0x%x  !\n", RecvPid,AlarmId);
        }
        OM_AcpuSetSendFlag(i);
        chr_print("send pid 0x%x, Alarmid 0x%x  !\n", RecvPid,AlarmId);
    }

    *pulSendCount = ulSendPidCount;

    return VOS_OK;
}


VOS_INT OM_AcpuStartTimer(VOS_VOID)
{
    /* ??5s?????? */
    g_AcpuErrLogFullTmr = VOS_NULL_PTR;
    if (VOS_OK != VOS_StartRelTimer(&g_AcpuErrLogFullTmr, MSP_PID_CHR, OM_ERRLOG_TIMER_LENTH,
                                    OM_ERRORLOG_TIMER_NAME, OM_ERRORLOG_TIMER_PARA, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5))
    {

        chr_print("StartDrxTimer fail\n");

        return OM_APP_ERRLOG_START_TIMER_ERR;
    }
    chr_print("start timer success!\n");

    return VOS_OK;
}



VOS_INT OM_AcpuReportErrLogMsg(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    APP_OM_REQ_ERR_LOG_STRU            *pstAppOmReqErrLog = VOS_NULL_PTR;
    VOS_UINT32                          ulSendPidCount = 0;
    VOS_INT                             ulRest;
    VOS_UINT32                          *pulNvId = &g_stOmAppMsgRecord.ulFaultNv;
    NV_ID_CHR_FAULTID_CONFIG_STRU       *pFaultCfg = &g_stOmAppMsgRecord.stFaultCfg;

    if(VOS_NULL_PTR == pucData)
    {
        chr_print("input data is NULL !\n");
        return OM_APP_PARAM_INAVALID;
    }

    if(ulLen < sizeof(APP_OM_REQ_ERR_LOG_STRU))
    {
        chr_print("input length too short !\n");
        return OM_APP_MSG_LENGTH_ERR;

    }
     /* ????AP???????? */
    pstAppOmReqErrLog = (APP_OM_REQ_ERR_LOG_STRU*)pucData;

    /*??????????????????*/
    if(ulLen != (pstAppOmReqErrLog->stOmHeader.ulMsgLen + sizeof(OM_ALARM_MSG_HEAD_STRU)))
    {

          chr_print("input length not match !\n");
          return OM_APP_MSG_LENGTH_ERR;
    }

    /*????????????????????OM????????BUSY????*/
    ulRest = OM_AcpuRcvAppMsgCheck(pstAppOmReqErrLog);
    if (VOS_OK != ulRest)
    {
        chr_print("check req failed. status = 0x%x,fauiltid = %d, modemid = %d!\n", ulRest,
            pstAppOmReqErrLog->usFaultId,pstAppOmReqErrLog->usModemID);
        return ulRest;
    }
    else
    {
        g_stOmAppMsgRecord.ulErrLogState = ERRLOG_BUSY;
        g_stOmAppMsgRecord.ulMsgSN ++;
        g_stOmAppMsgRecord.usFaultId = pstAppOmReqErrLog->usFaultId;
        g_stOmAppMsgRecord.usModemId = pstAppOmReqErrLog->usModemID;
        g_stOmAppMsgRecord.ulAlarmIdNum = 0;
        pFaultCfg->ulAlarmNum = 0;
    }

    chr_print("modem:0x%x,faultid:0x%x!\n",pstAppOmReqErrLog->usModemID,pstAppOmReqErrLog->usFaultId);

    ulRest = OM_AcpuGetFaultCfg(pstAppOmReqErrLog->usFaultId,
                                pstAppOmReqErrLog->usModemID,
                                pulNvId, pFaultCfg);
    if(VOS_OK != ulRest)
    {
        chr_print("get fault cfg failed.status = %d, faultid = %d, modemid = %d!\n", ulRest, pstAppOmReqErrLog->usFaultId, pstAppOmReqErrLog->usModemID);
        g_stOmAppMsgRecord.ulErrLogState = ERRLOG_IDLE;
        return ulRest;
    }
    else
    {
        g_stOmAppMsgRecord.ulAlarmIdNum       = pFaultCfg->ulAlarmNum;
        g_stOmAppMsgRecord.ulErrLogReportSend = pFaultCfg->ulAlarmNum;
        OM_AcpuClearSendFlagAll();
        chr_print("faultnv = %d ulAlarmIdNum = %d!\n",*pulNvId,pFaultCfg->ulAlarmNum);
    }

    /* ??????????????????????PID???????? */
    ulRest = OM_AcpuSendReq(&ulSendPidCount);
    if(VOS_OK != ulRest)
    {
        g_stOmAppMsgRecord.ulErrLogState = ERRLOG_IDLE;
        return ulRest;
    }

    /* ??????????????????PID????????AP???????????????? */
    if (0 == ulSendPidCount)
    {
        chr_print("no PID send.\n");
        OM_AcpuRcvMsgFinish();
        return VOS_OK;
    }
    /* ??timer?????? */
    ulRest = OM_AcpuStartTimer();
    if(VOS_OK != ulRest)
    {
        chr_print("start timer failed\n");
        return ulRest;
    }

    return VOS_OK;
}


VOS_VOID OM_AcpuErrLogHook(VOS_UINT8 *pucData, VOS_UINT32 ulLen, VOS_UINT32 ulDateType)
{
    DIAG_TRANS_IND_STRU stTrans = {0};

    stTrans.ulModule    = DIAG_GEN_MODULE_EX(0, DIAG_MODE_LTE, DIAG_MSG_TYPE_MSP);
    stTrans.ulPid       = MSP_PID_CHR;
    stTrans.ulMsgId     = OM_APP_ERRLOG_HOOK_IND | ulDateType;
    stTrans.ulLength    = ulLen;
    stTrans.pData       = pucData;

    DIAG_TransReport_Ex(&stTrans);

    return;
}


VOS_VOID OM_AcpuSendVComData(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    /* ????????????????Vcom?????? */
    g_stErrLogVcomDebugInfo.ulVCOMSendNum++;
    g_stErrLogVcomDebugInfo.ulVCOMSendLen += ulLen;

    OM_ACPU_CHR_DEBUG_TRACE((VOS_UINT8*)pucData, ulLen, OM_ACPU_ERRLOG_SEND);


    /* ????Trans???? */
    OM_AcpuErrLogHook(pucData, ulLen, OM_ERRLOG_SEND_MSG);

    if(VOS_OK != APP_VCOM_SEND(APP_VCOM_DEV_INDEX_ERRLOG, pucData, ulLen))
    {
        g_stErrLogVcomDebugInfo.ulVCOMSendErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMSendErrLen += ulLen;


        (VOS_VOID)chr_print("Send vcom Msg failed.\n");


        return ;
    }
    return ;
}


VOS_UINT32 OM_AcpuRcvErrLogMsgCheck(OM_RCV_REPORT_STRU *pstOmRcvDataInfo, VOS_UINT32 *pulSendPidCount)
{
    NV_ID_CHR_FAULTID_CONFIG_STRU       *pFaultCfg = &g_stOmAppMsgRecord.stFaultCfg;
    VOS_UINT32   i;

    if(ERRLOG_IDLE == g_stOmAppMsgRecord.ulErrLogState)
    {
        chr_print("state is idle, drop the message!\n");
        return VOS_ERR;
    }

    /* ?????????????????????? */
    for (i=0; i<g_stOmAppMsgRecord.ulAlarmIdNum; i++)
    {
        if ((pFaultCfg->aucAlarmMap[i].ulPid     == pstOmRcvDataInfo->stChrRcvOmHeader.ulSenderPid)
            && (pFaultCfg->aucAlarmMap[i].ulAlarmId == pstOmRcvDataInfo->stChrRcvOmHeader.usAlarmId)
            && (g_stOmAppMsgRecord.ulMsgSN          == pstOmRcvDataInfo->ulMsgSN)
            && (OM_AcpuChkRptFlag(i)))
        {
            (*pulSendPidCount)++;
            OM_AcpuSetRptFlag(i);
            g_stOmAppMsgRecord.ulErrLogReportSend--;

            g_stRcvUESendAP.ulErrLogSendNum++;
            g_stRcvUESendAP.ulErrLogSendLen += pstOmRcvDataInfo->ulRptLen;

            break;
        }
    }

    return VOS_OK;
}



VOS_UINT32 OM_AcpuRcvMsgCheck(OM_RCV_REPORT_STRU *pstOmRcvDataInfo)
{
    VOS_UINT32                          ulSendPidCount = 0;

    switch(pstOmRcvDataInfo->unComChrType.ulMsgType)
    {
        case OM_ERR_LOG_MSG_ERR_REPORT:
            /* Error Log ???? */
            if(VOS_OK != OM_AcpuRcvErrLogMsgCheck(pstOmRcvDataInfo, &ulSendPidCount))
            {
                return VOS_ERR;
            }
            break;

        case OM_ERR_LOG_MSG_FAULT_REPORT:
            /* ???????????????????? */
            ulSendPidCount++;
            break;

        case OM_ERR_LOG_MSG_ALARM_REPORT:
            /* ???????????????????? */
            ulSendPidCount++;
            break;

        default:
            /* ???? */
            (VOS_VOID)chr_print("Msg type wrong!\r\n ");

            return VOS_ERR;
    }

    /* ????????????,???????? */
    if (OM_AP_NO_MSG_SEND == ulSendPidCount)
    {

        (VOS_VOID)chr_print("No msg Send!\r\n ");

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_INT OM_AcpuReportErrLog(VOS_UINT16 usModemID, VOS_UINT16 usFaultId)
{
    APP_OM_REQ_ERR_LOG_STRU              stAppOmCtrlStatus;

    VOS_INT ret;
    (VOS_VOID)VOS_MemSet_s(&stAppOmCtrlStatus, sizeof(stAppOmCtrlStatus), 0, (VOS_UINT32)(sizeof(APP_OM_REQ_ERR_LOG_STRU)));


    stAppOmCtrlStatus.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_SET_ERR_REPORT;
    stAppOmCtrlStatus.stOmHeader.ulMsgSN   = 2;
    stAppOmCtrlStatus.stOmHeader.ulMsgLen  = 2*sizeof(VOS_UINT32);
    stAppOmCtrlStatus.ulMsgModuleID        = 0x01;
    stAppOmCtrlStatus.usModemID            = usModemID;
    stAppOmCtrlStatus.usFaultId            = usFaultId;


    ret = OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, (VOS_UINT8*)&stAppOmCtrlStatus, sizeof(APP_OM_REQ_ERR_LOG_STRU));
    if(VOS_ERR == ret)
    {
        chr_print("read vcom data failed!\n");
    }
    return ret;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuCfgBlackListTest
 ????????  : ??????????:????AP??????????????
 ????????  : usModemID : MODEM id
             usFaultId :??????????

 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_INT OM_AcpuCfgBlackListTest(VOS_UINT32  ulMsgModuleID, VOS_UINT16  usAlarmId, VOS_UINT16  usAlmType)
{
    VOS_INT ret;
    VOS_UINT  allocSize;

    OM_APP_BLACK_LIST_STRU              *pstAppOmCfgBlackList = VOS_NULL_PTR;
    CHR_LIST_INFO_S                     *pstBlackListInfo = VOS_NULL_PTR;
    VOS_UINT8                           *pucAppOmCfgBlackList = VOS_NULL_PTR;
    allocSize = sizeof( OM_APP_BLACK_LIST_STRU) + sizeof(CHR_LIST_INFO_S);

    pucAppOmCfgBlackList = (VOS_UINT8 *)VOS_MemAlloc(MSP_PID_CHR, DYNAMIC_MEM_PT, allocSize);
    if (VOS_NULL_PTR == pucAppOmCfgBlackList)
    {
        chr_print("failed to malloc\n");
        return VOS_ERR;
    }
    (VOS_VOID)VOS_MemSet_s(pucAppOmCfgBlackList, allocSize, 0, allocSize);

    pstAppOmCfgBlackList = (OM_APP_BLACK_LIST_STRU *)pucAppOmCfgBlackList;

    pstAppOmCfgBlackList->stOmHeader.ulMsgType = OM_ERR_LOG_MSG_BLACK_LIST;
    pstAppOmCfgBlackList->stOmHeader.ulMsgSN   = 0;
    pstAppOmCfgBlackList->stOmHeader.ulMsgLen  = sizeof(CHR_LIST_INFO_S) ;


    pstBlackListInfo = (CHR_LIST_INFO_S *)(pstAppOmCfgBlackList->stBlackList);

    pstBlackListInfo->ulMsgModuleID = ulMsgModuleID;
    pstBlackListInfo->usAlarmId     = usAlarmId;
    pstBlackListInfo->usAlmType     = usAlmType;

    ret = OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, pucAppOmCfgBlackList, allocSize);
    if(VOS_ERR == ret)
    {
        chr_print("read vcom data failed!\n");
       (VOS_VOID)VOS_MemFree(MSP_PID_CHR, pucAppOmCfgBlackList);
        return VOS_ERR;
    }
    (VOS_VOID)VOS_MemFree(MSP_PID_CHR, pucAppOmCfgBlackList);

    return ret;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuCfgPriorityTest
 ????????  : ??????????:????AP????????????
 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_INT OM_AcpuCfgPriorityTest(VOS_UINT32  ulMsgModuleID, VOS_UINT16  usAlarmId ,VOS_UINT8 ucSn,VOS_UINT16 usAlmType)
{
    VOS_INT ret;
    VOS_UINT  allocSize;

    OM_APP_PRIORITY_CFG_STRU              *pstAppOmCfgPriority = VOS_NULL_PTR;
    CHR_PRIORITY_INFO_S                   *pstPriorityInfo = VOS_NULL_PTR;
    VOS_UINT8                             *pucAppOmCfgPriority = VOS_NULL_PTR;

    allocSize = sizeof( OM_APP_PRIORITY_CFG_STRU) + sizeof(CHR_PRIORITY_INFO_S);
    pucAppOmCfgPriority = (VOS_UINT8 *)VOS_MemAlloc(MSP_PID_CHR, DYNAMIC_MEM_PT, allocSize);
    if (VOS_NULL_PTR == pucAppOmCfgPriority)
    {
        chr_print("failed to malloc\n");
        return VOS_ERR;
    }
    (VOS_VOID)VOS_MemSet_s(pucAppOmCfgPriority, allocSize, 0, allocSize);

    pstAppOmCfgPriority =(OM_APP_PRIORITY_CFG_STRU *)pucAppOmCfgPriority;

    pstAppOmCfgPriority->stOmHeader.ulMsgType = OM_ERR_LOG_MSG_PRIORITY_CFG;
    pstAppOmCfgPriority->stOmHeader.ulMsgSN   = 0;
    pstAppOmCfgPriority->stOmHeader.ulMsgLen  = allocSize - sizeof(OM_ALARM_MSG_HEAD_STRU);
    pstAppOmCfgPriority->ucCount = 1;
    pstAppOmCfgPriority->ucPacketSN = ucSn;

    pstPriorityInfo = (CHR_PRIORITY_INFO_S *)(pstAppOmCfgPriority->alarmMap);

    pstPriorityInfo->ulModuleId    = ulMsgModuleID;
    pstPriorityInfo->usAlarmId     = usAlarmId;
    pstPriorityInfo->usAlmType     = usAlmType;

    ret = OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, (VOS_UINT8*)pucAppOmCfgPriority, allocSize);
    if(VOS_ERR == ret)
    {
        chr_print("read vcom data failed!\n");
       (VOS_VOID)VOS_MemFree(MSP_PID_CHR, pucAppOmCfgPriority);
        return VOS_ERR;
    }
    (VOS_VOID)VOS_MemFree(MSP_PID_CHR, pucAppOmCfgPriority);

    return ret;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuCfgPeriodTest
 ????????  : ??????????:????AP????????????????
 ????????  :
 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_INT OM_AcpuCfgPeriodTest(VOS_UINT32  ulMsgModuleID, VOS_UINT32  ulCount ,VOS_UINT8 ucSn)
{
    VOS_INT ret;
    VOS_UINT  allocSize;

    OM_APP_PERIOD_CFG_STRU              *pstAppOmCfgPeriod = VOS_NULL_PTR;
    CHR_PERIOD_CFG_STRU                 *pstPeriodInfo = VOS_NULL_PTR;
    VOS_UINT8                           *pucAppOmCfgPeriod = VOS_NULL_PTR;

    allocSize = sizeof( OM_APP_PERIOD_CFG_STRU) + sizeof(CHR_PERIOD_CFG_STRU);
    pucAppOmCfgPeriod = (VOS_UINT8 *)VOS_MemAlloc(MSP_PID_CHR, DYNAMIC_MEM_PT, allocSize);
    if (VOS_NULL_PTR == pucAppOmCfgPeriod)
    {
        chr_print("failed to malloc\n");
        return VOS_ERR;
    }
    (VOS_VOID)VOS_MemSet_s(pucAppOmCfgPeriod, allocSize, 0, allocSize);

    pstAppOmCfgPeriod =(OM_APP_PERIOD_CFG_STRU *)pucAppOmCfgPeriod;

    pstAppOmCfgPeriod->stOmHeader.ulMsgType = OM_ERR_LOG_MSG_PERIOD_CFG;
    pstAppOmCfgPeriod->stOmHeader.ulMsgSN   = 0;
    pstAppOmCfgPeriod->stOmHeader.ulMsgLen  = allocSize - sizeof(OM_ALARM_MSG_HEAD_STRU);
    pstAppOmCfgPeriod->ucCount = 1;
    pstAppOmCfgPeriod->ucMsgSN = ucSn;
    pstAppOmCfgPeriod->ucperiod =1 ;

    pstPeriodInfo = (CHR_PERIOD_CFG_STRU *)(pstAppOmCfgPeriod->alarmMap);

    pstPeriodInfo->ulModuleId    = ulMsgModuleID;
    pstPeriodInfo->ulCount       = ulCount;


    ret = OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, (VOS_UINT8*)pucAppOmCfgPeriod, allocSize);
    if(VOS_ERR == ret)
    {
        chr_print("read vcom data failed!\n");
       (VOS_VOID)VOS_MemFree(MSP_PID_CHR, pucAppOmCfgPeriod);
        return VOS_ERR;
    }
    (VOS_VOID)VOS_MemFree(MSP_PID_CHR, pucAppOmCfgPeriod);

    return ret;
}

/* ?????????????????????????????????? */
VOS_VOID OM_AcpuCltInfoCnfNotNeedProcessSetFlag(VOS_VOID)
{
    g_AcpuCtlInfoCnfNotNeedProcess = OM_CLTINFO_CNF_NOT_NEED_PROCESS;
}

/* ?????????????????????????????????? */
VOS_VOID OM_AcpuCltInfoCnfNotNeedProcessReSetFlag(VOS_VOID)
{
    g_AcpuCtlInfoCnfNotNeedProcess = OM_CLTINFO_CNF_NEED_PROCESS;
}
/* ?????????????????????????????????? */
VOS_UINT32 OM_AcpuCltInfoCnfGetNotNeedProcessFlag(VOS_VOID)
{
    return g_AcpuCtlInfoCnfNotNeedProcess;
}

/* ????modemID????????MTA??pid ??????????????????MTA */
VOS_UINT32 OM_AcpuCltInfoGetMTAPid(VOS_UINT32 modemId)
{
    if (modemId == 0)
        return I0_UEPS_PID_MTA;
    else if (modemId == 1)
        return I1_UEPS_PID_MTA;
    else if (modemId == 2)
        return I2_UEPS_PID_MTA;
    else
        return OM_CLTINFO_INVALID_PID;
}


/* OM???????????????????????? */
VOS_INT OM_AcpuCltInfoReqMsgProc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    APP_OM_INFO_CLT_REQ_STRU *pOMCltInfo = NULL;
    OM_INFO_CLT_REPORT_REQ_STRU *pVOSCltInfo = NULL;
    VOS_UINT allocSize = 0;

    if(VOS_NULL_PTR == pucData)
    {
        return VOS_ERR;
    }
    if(ulLen < sizeof(APP_OM_INFO_CLT_REQ_STRU)-sizeof(pOMCltInfo->aucMsgContent))
    {
        return VOS_ERR;
    }
    pOMCltInfo = (APP_OM_INFO_CLT_REQ_STRU *)pucData;
    if(ulLen - (sizeof(APP_OM_INFO_CLT_REQ_STRU)-sizeof(pOMCltInfo->aucMsgContent)) < pOMCltInfo->ulMsgLength )
    {
        return VOS_ERR;
    }

    allocSize = sizeof(OM_INFO_CLT_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH - sizeof(pOMCltInfo->aucMsgContent) + pOMCltInfo->ulMsgLength;

    pVOSCltInfo = (OM_INFO_CLT_REPORT_REQ_STRU *)VOS_AllocMsg(MSP_PID_CHR, allocSize);

    if (VOS_NULL_PTR == pVOSCltInfo) {
        chr_print("pVOSCltInfo is null!\n");
        return VOS_ERR;
    }

    pVOSCltInfo->ulReceiverPid = OM_AcpuCltInfoGetMTAPid(pOMCltInfo->usModemID);

    if (pVOSCltInfo->ulReceiverPid == OM_CLTINFO_INVALID_PID) {
        chr_print("OM_AcpuCltInfoGetMTAPid failed\n");
        (VOS_VOID)VOS_FreeMsg(MSP_PID_CHR, pVOSCltInfo);
        return OM_APP_SEND_MODEM_ID_ERR;
    }
    pVOSCltInfo->ulMsgName     = ID_OM_INFO_CLT_REPORT_REQ;
    pVOSCltInfo->usModemID     = pOMCltInfo->usModemID;
    pVOSCltInfo->enSceneType   = pOMCltInfo->usInfoID;
    pVOSCltInfo->ulMsgLen      = pOMCltInfo->ulMsgLength;
    (VOS_VOID)VOS_MemCpy_s(pVOSCltInfo->aucContent, pVOSCltInfo->ulMsgLen, pOMCltInfo->aucMsgContent, pVOSCltInfo->ulMsgLen);

    (VOS_VOID)VOS_SendMsg(MSP_PID_CHR, pVOSCltInfo);
    OM_AcpuCltInfoCnfNotNeedProcessReSetFlag();
    g_stOmAppMsgRecord.usModemId=pOMCltInfo->usModemID;

    /* ??5s?????? */
    g_AcpuCltInfoFullTmr = VOS_NULL_PTR;
    if (VOS_OK != VOS_StartRelTimer(&g_AcpuCltInfoFullTmr, MSP_PID_CHR, OM_CLTINFO_TIMER_LENTH,
                                OM_CLTINFO_TIMER_NAME, OM_CLTINFO_TIMER_PARA, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5))
    {
        chr_print("VOS_StartRelTimer failed.\n");
        return OM_APP_ERRLOG_START_TIMER_ERR;
    }

    return VOS_OK;
}

/* ??????????????????????????msgType 0x11 */
VOS_VOID OM_AcpuRcvCltInfoFinish(VOS_VOID)
{
    OM_APP_REPORT_STATUS_STRU               stOmAppReportStatus = {};

    stOmAppReportStatus.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_INFO_CLT_END;
    stOmAppReportStatus.stOmHeader.ulMsgSN   = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;
    stOmAppReportStatus.stOmHeader.ulMsgLen  = (sizeof(OM_APP_REPORT_STATUS_STRU) - sizeof(OM_ALARM_MSG_HEAD_STRU));
    stOmAppReportStatus.usModemID            = g_stOmAppMsgRecord.usModemId;
    stOmAppReportStatus.ulReportStatus       = 0;
    stOmAppReportStatus.usFaultID            = g_stOmAppMsgRecord.usFaultId;
    stOmAppReportStatus.ulTrigLowSlice       = (VOS_UINT32)(g_ulTriggerTime64Bit & 0xffffffff);
    stOmAppReportStatus.ulTrigHighSlice      = (VOS_UINT32)((g_ulTriggerTime64Bit >> 32) & 0xffffffff);

    OM_AcpuSendVComData((VOS_UINT8 *)&stOmAppReportStatus, sizeof(OM_APP_REPORT_STATUS_STRU));

    return ;
}

/* ?????????????????????????????????????? */
VOS_INT OM_AcpuReportCltInfo(VOS_UINT16 modemID, VOS_UINT16 infoId, VOS_UINT32 mcc, VOS_UINT32 mnc)
{
    APP_OM_INFO_CLT_REQ_STRU *cltInfoReq = NULL;
    OM_INFO_CLT_PLMN_ID_STRU *cltInfoPLMN = NULL;

    VOS_INT ret;
    void *cltInfoalloc = NULL;
    VOS_UINT32 allocSize = sizeof(APP_OM_INFO_CLT_REQ_STRU) + 4; /* mcc/mnc ??8???? */

    cltInfoalloc  = VOS_MemAlloc(MSP_PID_CHR, DYNAMIC_MEM_PT, allocSize);

    if (NULL == cltInfoalloc){
        chr_print("failed to malloc\n");
        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemSet_s(cltInfoalloc, allocSize, 0, allocSize);

    cltInfoReq = (APP_OM_INFO_CLT_REQ_STRU *)cltInfoalloc;
    cltInfoReq->stOmHeader.ulMsgType = 0x10;
    cltInfoReq->stOmHeader.ulMsgSN   = 2;
    cltInfoReq->stOmHeader.ulMsgLen  = 4*sizeof(VOS_UINT32);

    cltInfoReq->usModemID            = modemID;
    cltInfoReq->usInfoID             = infoId;
    cltInfoReq->ulMsgLength          = 8;

    cltInfoPLMN = (OM_INFO_CLT_PLMN_ID_STRU *)(cltInfoReq->aucMsgContent);
    cltInfoPLMN->ulMcc = mcc;
    cltInfoPLMN->ulMnc = mnc;
    ret = OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, (VOS_UINT8*)cltInfoalloc,allocSize);
    if( VOS_ERR == ret)
    {
       (VOS_VOID)VOS_MemFree(MSP_PID_CHR, cltInfoalloc);
       chr_print("read vcom data failed!\n");
       return VOS_ERR ;
    }
    (VOS_VOID)VOS_MemFree(MSP_PID_CHR, cltInfoalloc);
    return ret;
}

//#endif


VOS_VOID OM_AcpuErrLogTimeoutShowPid(VOS_VOID)
{
    VOS_UINT32 i;


    /* ?????????????????????? */
    for (i=0; i<g_stOmAppMsgRecord.ulAlarmIdNum; i++)
    {
        if (OM_AcpuChkRptFlag(i))
        {
            (void)chr_print("Pid = 0x%x, AlarmId = 0x%x!\n",
                             g_stOmAppMsgRecord.stFaultCfg.aucAlarmMap[i].ulPid,
                             g_stOmAppMsgRecord.stFaultCfg.aucAlarmMap[i].ulAlarmId);
        }
    }
    return;
}


VOS_VOID OM_AcpuErrLogTimeoutProc(VOS_VOID)
{
    OM_AcpuErrLogTimeoutShowPid();
    OM_AcpuRcvMsgFinish();
    (void)chr_print("OM not receive all msg, timer is on!\n");

    return ;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuErrLogReqProc
 ????????  : ????ap????????????????????????chr acore????
 ????????  :  pucData    : ????????
              ulLen : ????????

 ????????  : ??
 ?? ?? ??  : VOS_ERR/VOS_OK

*****************************************************************************/
VOS_INT OM_AcpuErrLogReqProc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
     CHR_APP_REQ_STRU     *pReqMsg;

     /* ????????PID???????? */
     pReqMsg  = (CHR_APP_REQ_STRU*)VOS_AllocMsg(MSP_PID_CHR,
                        (((sizeof(CHR_APP_REQ_STRU)) - VOS_MSG_HEAD_LENGTH) + ulLen));
     if (VOS_NULL_PTR == pReqMsg)
     {
          (VOS_VOID)chr_print("Alloc msg failed!\n");
          return OM_APP_MEM_ALLOC_MSG_ERR;
     }
     pReqMsg->ulReceiverPid = MSP_PID_CHR;
     pReqMsg->ulMsgName     = CHR_ID_ERR_LOG_REQ;
     pReqMsg->ulMsgLen      = ulLen;

     (void)VOS_MemCpy_s(pReqMsg->aucData, ulLen, pucData, ulLen);
     (void)VOS_SendMsg(MSP_PID_CHR, pReqMsg);

     (void)chr_print("success!\n ");
     return VOS_OK;

}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuBlackListReqProc
 ????????  : ????ap??????????????????????????chr acore????
 ????????  :  pucData    : ????????
              ulLen : ????????

 ????????  : ??
 ?? ?? ??  : VOS_ERR/VOS_OK

*****************************************************************************/
VOS_INT OM_AcpuBlackListReqProc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
     CHR_APP_REQ_STRU     *pReqMsg;

     /* ????????PID???????? */
     pReqMsg  = (CHR_APP_REQ_STRU*)VOS_AllocMsg(MSP_PID_CHR,
                        (((sizeof(CHR_APP_REQ_STRU)) - VOS_MSG_HEAD_LENGTH) + ulLen));
     if (VOS_NULL_PTR == pReqMsg)
     {

          chr_print("alloc mem fail!\n");
          return OM_APP_MEM_ALLOC_MSG_ERR;
     }
     pReqMsg->ulReceiverPid = MSP_PID_CHR;
     pReqMsg->ulMsgName     = CHR_ID_BLACKLIST_REQ;
     pReqMsg->ulMsgLen      = ulLen;

     (void)VOS_MemCpy_s(pReqMsg->aucData, ulLen, pucData, ulLen);
     (void)VOS_SendMsg(MSP_PID_CHR, pReqMsg);

     (void)chr_print("success!\n ");
     return VOS_OK;

}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuPriorityReqProc
 ????????  : ????ap????????????????????????????chr acore????
 ????????  :  pucData    : ????????
              ulLen : ????????

 ????????  : ??
 ?? ?? ??  : VOS_ERR/VOS_OK

*****************************************************************************/
VOS_INT OM_AcpuPriorityReqProc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
     CHR_APP_REQ_STRU     *pReqMsg;

     /* ????????PID???????? */
     pReqMsg  = (CHR_APP_REQ_STRU*)VOS_AllocMsg(MSP_PID_CHR,
                        (((sizeof(CHR_APP_REQ_STRU)) - VOS_MSG_HEAD_LENGTH) + ulLen));
     if (VOS_NULL_PTR == pReqMsg)
     {
          return OM_APP_MEM_ALLOC_MSG_ERR;
     }
     pReqMsg->ulReceiverPid = MSP_PID_CHR;
     pReqMsg->ulMsgName     = CHR_ID_PRIORITY_REQ;
     pReqMsg->ulMsgLen      = ulLen;

     (void)VOS_MemCpy_s(pReqMsg->aucData, ulLen, pucData, ulLen);
     (void)VOS_SendMsg(MSP_PID_CHR, pReqMsg);

     (void)chr_print("success!\n ");
     return VOS_OK;

}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuPeriodReqProc
 ????????  : ????ap????????????????????????????chr acore????
 ????????  :  pucData    : ????????
              ulLen : ????????

 ????????  : ??
 ?? ?? ??  : VOS_ERR/VOS_OK

*****************************************************************************/
VOS_INT OM_AcpuPeriodReqProc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
     CHR_APP_REQ_STRU     *pReqMsg;

     /* ????????PID???????? */
     pReqMsg  = (CHR_APP_REQ_STRU*)VOS_AllocMsg(MSP_PID_CHR,
                        (((sizeof(CHR_APP_REQ_STRU)) - VOS_MSG_HEAD_LENGTH) + ulLen));
     if (VOS_NULL_PTR == pReqMsg)
     {
          return OM_APP_MEM_ALLOC_MSG_ERR;
     }
     pReqMsg->ulReceiverPid = MSP_PID_CHR;
     pReqMsg->ulMsgName     = CHR_ID_PERIOD_REQ;
     pReqMsg->ulMsgLen      = ulLen;

     (void)VOS_MemCpy_s(pReqMsg->aucData, ulLen, pucData, ulLen);
     (void)VOS_SendMsg(MSP_PID_CHR, pReqMsg);

     (void)chr_print("success!\n ");
     return VOS_OK;

}

VOS_INT OM_AcpuReadVComData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    OM_ALARM_MSG_HEAD_STRU             *pstOmAlarmMsgHead = NULL;
    COVERITY_TAINTED_SET(pucData);
    if(NULL == pucData)
    {
        (VOS_VOID)chr_print("data is null\n");
        return VOS_ERR;
    }

    if (APP_VCOM_DEV_INDEX_ERRLOG != ucDevIndex)
    {

        (VOS_VOID)chr_print("PhyPort  is wrong. devindex = %d\n", ucDevIndex);
        return VOS_ERR;
    }

    down(&g_stOmRxErrorLogBuffSem);

    if (ulLen > OM_ERRLOG_MAX_CFG_LEN) {
        chr_print("len too long\n");
        return VOS_ERR;
    }

    if (ulLen < sizeof(OM_ALARM_MSG_HEAD_STRU))
    {

        (VOS_VOID)chr_print(" len is too short. len = %d.\n", ulLen);

        up(&g_stOmRxErrorLogBuffSem);

        return VOS_ERR;
    }

     /* ?????????????????????? */
    pstOmAlarmMsgHead = (OM_ALARM_MSG_HEAD_STRU *)pucData;
    if (ulLen!= pstOmAlarmMsgHead->ulMsgLen +sizeof(OM_ALARM_MSG_HEAD_STRU))
    {

        (VOS_VOID)chr_print(" len not match. len = %d.\n", ulLen);
        up(&g_stOmRxErrorLogBuffSem);

        return VOS_ERR;
    }

    CHR_LogReport("receive msg. Msgtype:0x%x,MsgLen:0x%x,len:0x%x!\n",
        pstOmAlarmMsgHead->ulMsgType,pstOmAlarmMsgHead->ulMsgLen,ulLen);

    /*????????????*/

    OM_ACPU_CHR_DEBUG_TRACE((VOS_UINT8*)pucData, ulLen, OM_ACPU_ERRLOG_RCV);

    /* ????Trans???? */
    OM_AcpuErrLogHook(pucData, ulLen, OM_ERRLOG_RCV_MSG);

    g_stErrLogVcomDebugInfo.ulVCOMRcvNum++;
    g_stErrLogVcomDebugInfo.ulVCOMRcvLen += ulLen;
    g_stErrLogVcomDebugInfo.ulVCOMRcvSn = pstOmAlarmMsgHead->ulMsgSN;


    if(OM_ERR_LOG_MSG_SET_ERR_REPORT == pstOmAlarmMsgHead->ulMsgType)
    {
        up(&g_stOmRxErrorLogBuffSem);
        return OM_AcpuErrLogReqProc(pucData, ulLen);
    }
    else if(OM_ERR_LOG_MSG_INFO_CLT_REQ == pstOmAlarmMsgHead->ulMsgType)
    {
        up(&g_stOmRxErrorLogBuffSem);
        return OM_AcpuCltInfoReqMsgProc(pucData, ulLen);
    }
    else if(OM_ERR_LOG_MSG_BLACK_LIST == pstOmAlarmMsgHead->ulMsgType)
    {
        up(&g_stOmRxErrorLogBuffSem);
        return OM_AcpuBlackListReqProc(pucData, ulLen);
    }
    else if(OM_ERR_LOG_MSG_PRIORITY_CFG == pstOmAlarmMsgHead->ulMsgType)
    {
        up(&g_stOmRxErrorLogBuffSem);
        return OM_AcpuPriorityReqProc(pucData, ulLen);
    }
    else if(OM_ERR_LOG_MSG_PERIOD_CFG == pstOmAlarmMsgHead->ulMsgType)
    {
        up(&g_stOmRxErrorLogBuffSem);
        return OM_AcpuPeriodReqProc(pucData, ulLen);
    }
    else
    {
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += ulLen;

        (VOS_VOID)chr_print("Recv msg type is wrong\n");

        OM_AcpuSendAppResult(OM_APP_MSG_TYPE_ERR, MODEM_ID_BUTT);
        up(&g_stOmRxErrorLogBuffSem);
        return VOS_ERR;
    }
}

/*****************************************************************************
 ?? ?? ??  : OM_AcpuErrLogMsgProc
 ????????  : OM??????????????????????????
 ????????  : pMsg: ????????

 ????????  : ??

*****************************************************************************/
VOS_VOID OM_AcpuErrLogMsgProc(MsgBlock* pMsg)
{

    OM_RCV_REPORT_STRU              *pstOmRcvDataInfo;

    pstOmRcvDataInfo = (OM_RCV_REPORT_STRU*)pMsg;
    
    /*??????????????????????????????*/
    if ((ID_OM_ERR_LOG_REPORT_CNF != pstOmRcvDataInfo->stChrRcvOmHeader.ulMsgName)
         && (ID_OM_FAULT_ERR_LOG_IND != pstOmRcvDataInfo->stChrRcvOmHeader.ulMsgName)
         && (ID_OM_ALARM_ERR_LOG_IND != pstOmRcvDataInfo->stChrRcvOmHeader.ulMsgName))
    {
        CHR_LogReport("not chr Log msg.\n");
        return ;
    }

    /*  ???????????????????????? */
    if (VOS_OK !=OM_AcpuRcvMsgCheck(pstOmRcvDataInfo))
    {
        CHR_LogReport("rcv msg wrong!\r\n ");
        return ;
    }
    /*????ap??x??????*/

    pstOmRcvDataInfo->unComChrType.stComChrType.usMsgType = pstOmRcvDataInfo->unComChrType.ulMsgType&0xffff;
    pstOmRcvDataInfo->unComChrType.stComChrType.usFaultId = pstOmRcvDataInfo->stChrRcvOmHeader.usFaultId;

    OM_AcpuSendVComData((VOS_UINT8 *)&pstOmRcvDataInfo->unComChrType.ulMsgType,

       pstOmRcvDataInfo->ulRptLen + sizeof(OM_ALARM_MSG_HEAD_STRU));

    CHR_LogReport("rcv msg Send Success,Msgname 0x%x, Type 0x%x, AlarmTyep 0x%x, Alarmid 0x%x,Pid 0x%x, Cnt 0x%x,modulid 0x%x\n",
        pstOmRcvDataInfo->stChrRcvOmHeader.ulMsgName,
        pstOmRcvDataInfo->unComChrType.stComChrType.usMsgType,
        pstOmRcvDataInfo->stChrRcvOmHeader.usAlmType,
        pstOmRcvDataInfo->stChrRcvOmHeader.usAlarmId,
        pstOmRcvDataInfo->stChrRcvOmHeader.ulSenderPid,
        g_stOmAppMsgRecord.ulErrLogReportSend,
        pstOmRcvDataInfo->stChrRcvOmHeader.ulModuleId);

    chr_print("rcv msg Alarmid 0x%x,Pid 0x%x, modulid 0x%x\n",
        pstOmRcvDataInfo->stChrRcvOmHeader.usAlarmId,
        pstOmRcvDataInfo->stChrRcvOmHeader.ulSenderPid,
        pstOmRcvDataInfo->stChrRcvOmHeader.ulModuleId);

     if ((OM_ERR_LOG_MSG_ERR_REPORT == pstOmRcvDataInfo->unComChrType.stComChrType.usMsgType)
        && ( OM_AP_SEND_MSG_FINISH==g_stOmAppMsgRecord.ulErrLogReportSend))
    {
        /* ????????*/

       (void)VOS_StopRelTimer(&g_AcpuErrLogFullTmr);

        OM_AcpuRcvMsgFinish();
        CHR_LogReport("Report all msg, Stop timer\n");
    }

    return;
}


/* ???????????????????????? */
VOS_VOID OM_AcpuCltInfoCnfMsgProc(MsgBlock* pMsg)
{

    OM_INFO_CLT_REPORT_CNF_STRU *pCltInfoCnf = NULL;
    VOS_UINT16 sendSize = 0;

    pCltInfoCnf = (OM_INFO_CLT_REPORT_CNF_STRU *)pMsg;
    if ((!pCltInfoCnf) || (ID_OM_INFO_CLT_REPORT_CNF != pCltInfoCnf->ulMsgName))
    {
        return ;
    }

    pCltInfoCnf->ulMsgSN = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;
    sendSize = pCltInfoCnf->ulRptLen + sizeof(OM_ALARM_MSG_HEAD_STRU);

    if (OM_AcpuCltInfoCnfGetNotNeedProcessFlag() == OM_CLTINFO_CNF_NEED_PROCESS)
    {
        OM_AcpuSendVComData((VOS_UINT8*)&pCltInfoCnf->ulMsgType, sendSize);

        if (OM_ERR_LOG_MSG_INFO_CLT_CNF == pCltInfoCnf->ulMsgType)
        {
            /* ???????? */
            VOS_StopRelTimer(&g_AcpuCltInfoFullTmr);
            OM_AcpuRcvCltInfoFinish();
        }
    }

    return;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuErrLogRcvMsgProc
 ????????  : OM??????????????????????????
 ????????  : pMsg    : ????????

 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_VOID OM_AcpuErrLogRcvMsgProc(MsgBlock* pMsg)
{
      VOS_UINT32 ulRest;
      CHR_APP_REQ_STRU *pReq = (CHR_APP_REQ_STRU*)pMsg;

      ulRest = OM_AcpuReportErrLogMsg(pReq->aucData, pReq->ulMsgLen);
      if(OM_APP_MSG_OK !=ulRest)
      {
         OM_AcpuSendAppResult(ulRest, MODEM_ID_BUTT);
         chr_print("errlog msg failed. err code = 0x%x!\n",ulRest);
         return;
      }

      return;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuBlackListRcvMsgProc
 ????????  : OM????????????????????????
 ????????  : pMsg    : ????????

 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_VOID OM_AcpuBlackListRcvMsgProc(MsgBlock* pMsg)
{
      VOS_UINT32 ulRet;
      CHR_APP_REQ_STRU *pReq = (CHR_APP_REQ_STRU*)pMsg;

      ulRet = OM_AcpuBlackListProc(pReq->aucData, pReq->ulMsgLen);
      if(OM_APP_MSG_OK != ulRet)
      {
         OM_AcpuSendAppcfgResult(ulRet);
         chr_print("blacklist msg failed. err code = 0x%x!\n",ulRet);
         return;
      }
      /*????????????????apk??????vcom??*/
      OM_AcpuSendAppcfgResult(OM_APP_MSG_OK);
      return;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuPriorityRcvMsgProc
 ????????  : OM??????????????????????????????
 ????????  : pMsg    : ????????

 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_VOID OM_AcpuPriorityRcvMsgProc(MsgBlock* pMsg)
{
      VOS_UINT32 ulRet;
      CHR_APP_REQ_STRU *pReq = (CHR_APP_REQ_STRU*)pMsg;

      ulRet =OM_AcpuPriorityCfgProc(pReq->aucData, pReq->ulMsgLen);

      if(OM_APP_MSG_OK != ulRet)
      {
         OM_AcpuSendAppcfgResult(ulRet);
         chr_print("prio msg failed. err code = 0x%x!\n",ulRet);
         return;
      }
      /*????????????????apk??????vcom??*/
      OM_AcpuSendAppcfgResult(OM_APP_MSG_OK);
      return;
}
/*****************************************************************************
 ?? ?? ??  : OM_AcpuPeriodRcvMsgProc
 ????????  : OM??????????????????????????????
 ????????  : pMsg    : ????????

 ????????  : ??
 ?? ?? ??  :
 ????????  :
 ????????  :

*****************************************************************************/
VOS_VOID OM_AcpuPeriodRcvMsgProc(MsgBlock* pMsg)
{
      VOS_UINT32 ulRet;
      CHR_APP_REQ_STRU *pReq = (CHR_APP_REQ_STRU*)pMsg;

      ulRet = OM_AcpuPeriodCfgProc(pReq->aucData, pReq->ulMsgLen);

      if(OM_APP_MSG_OK != ulRet)
      {
         OM_AcpuSendAppcfgResult(ulRet);
         chr_print("period msg failed. err code = 0x%x!\n",ulRet);
         return;
      }
      /*????????????????apk??????vcom??*/
      OM_AcpuSendAppcfgResult(OM_APP_MSG_OK);

      return;
}

VOS_VOID OM_AcpuChrMsgProc(MsgBlock* pMsgBlock)
{

    REL_TIMER_MSG *pTimer =NULL;
    CHR_APP_REQ_STRU  *pReqMsg = NULL;
    COVERITY_TAINTED_SET((VOS_VOID *)(pMsgBlock->aucValue));
    /*????????*/
    if (NULL == pMsgBlock)
    {
        return;
    }

    /*????????PID??????????????*/
    switch(pMsgBlock->ulSenderPid)
    {
        /*??????????????????????????????????*/
        case DOPRA_PID_TIMER:

            pTimer   = (REL_TIMER_MSG*)pMsgBlock;

            if((OM_ERRORLOG_TIMER_NAME == pTimer->ulName) && (OM_ERRORLOG_TIMER_PARA == pTimer->ulPara))
            {
                OM_AcpuErrLogTimeoutProc();
            }
            else if((OM_CLTINFO_TIMER_NAME == pTimer->ulName) && (OM_CLTINFO_TIMER_PARA == pTimer->ulPara))
            {
                OM_AcpuCltInfoCnfNotNeedProcessSetFlag();
                OM_AcpuRcvCltInfoFinish();
            }
            break;
        case MSP_PID_CHR:

            pReqMsg =(CHR_APP_REQ_STRU *)pMsgBlock;
            if(CHR_ID_ERR_LOG_REQ ==  pReqMsg->ulMsgName)
            {
                OM_AcpuErrLogRcvMsgProc(pMsgBlock);

            }
            else if(CHR_ID_BLACKLIST_REQ ==  pReqMsg->ulMsgName)
            {
                OM_AcpuBlackListRcvMsgProc(pMsgBlock);

            }
            else if(CHR_ID_PRIORITY_REQ == pReqMsg->ulMsgName)
            {
                OM_AcpuPriorityRcvMsgProc(pMsgBlock);
            }
            else if(CHR_ID_PERIOD_REQ == pReqMsg->ulMsgName)
            {
                OM_AcpuPeriodRcvMsgProc(pMsgBlock);
            }
            else if(CHR_ID_RESET_CCORE == pReqMsg->ulMsgName)
            {
                OM_AcpuResetProc();
            }
            break;
        default:
        {
            OM_AcpuErrLogMsgProc(pMsgBlock);
            OM_AcpuCltInfoCnfMsgProc(pMsgBlock);
        }
           break;

    }

   return ;
}


VOS_UINT32 OM_AcpuChrInit(enum VOS_INIT_PHASE_DEFINE ip)
{

    VOS_UINT32 ulRest = 0;

    if(ip == VOS_IP_LOAD_CONFIG)
    {
        /* ????ERR LOG?????????????????? */
        g_stOmAppMsgRecord.ulErrLogReportSend = 0;/* ????Err Log???????????? */

        g_stOmAppMsgRecord.usModemId          = MODEM_ID_BUTT;
        g_stOmAppMsgRecord.ulErrLogState      = ERRLOG_IDLE;
        g_stOmAppMsgRecord.ulMsgSN            = 0;

        sema_init(&g_stOmRxErrorLogBuffSem, 1);


        /* ??????Vcom Error log??????NAS */
        ulRest = APP_VCOM_REG_DATA_CALLBACK(APP_VCOM_DEV_INDEX_ERRLOG, (SEND_UL_AT_FUNC)OM_AcpuReadVComData);
        if(VOS_OK != ulRest)
        {
            chr_print("RegDataCallback failed\n");
        }

        ulRest = CHR_Cfg_Init();

        if(VOS_OK != ulRest)
        {
            chr_print("chr init failed\n");
        }
    }

    return ulRest;

}



VOS_VOID OM_AcpuErrLogInfoShow(VOS_VOID)
{

    (VOS_VOID)chr_print("VCom Send sn is           %d\n", g_stErrLogVcomDebugInfo.ulVCOMSendSn);
    (VOS_VOID)chr_print("VCom Send num is           %d\n", g_stErrLogVcomDebugInfo.ulVCOMSendNum);
    (VOS_VOID)chr_print("VCom Send Len is           %d\n", g_stErrLogVcomDebugInfo.ulVCOMSendLen);
    (VOS_VOID)chr_print("VCom Send Error num is         %d\n", g_stErrLogVcomDebugInfo.ulVCOMSendErrNum);
    (VOS_VOID)chr_print("VCom Send Error Len is         %d\n", g_stErrLogVcomDebugInfo.ulVCOMSendErrLen);
    (VOS_VOID)chr_print("VCom receive sn is           %d\n", g_stErrLogVcomDebugInfo.ulVCOMRcvSn);
    (VOS_VOID)chr_print("VCom receive num is           %d\n", g_stErrLogVcomDebugInfo.ulVCOMRcvNum);
    (VOS_VOID)chr_print("VCom receive Len is           %d\n", g_stErrLogVcomDebugInfo.ulVCOMRcvLen);
    (VOS_VOID)chr_print("VCom receive Error num is         %d\n", g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum);
    (VOS_VOID)chr_print("VCom receive Error Len is         %d\n", g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen);
    (VOS_VOID)chr_print("OM Send Err log msg num is         %d\n", g_stRcvUESendAP.ulErrLogSendNum);
    (VOS_VOID)chr_print("OM Send Err log msg len is         %d\n", g_stRcvUESendAP.ulErrLogSendLen);

    return;
}
EXPORT_SYMBOL(OM_AcpuReportErrLog);
EXPORT_SYMBOL(OM_AcpuReportCltInfo);
EXPORT_SYMBOL(OM_AcpuErrLogInfoShow);
EXPORT_SYMBOL(OM_ChrOpenLog);
EXPORT_SYMBOL(OM_AcpuCfgBlackListTest);
EXPORT_SYMBOL(OM_AcpuCfgPriorityTest);
EXPORT_SYMBOL(OM_AcpuCfgPeriodTest);
#endif

VOS_UINT32 MSP_AppChrFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{

#if (FEATURE_ON == FEATURE_CHR_OM)
     VOS_UINT32 ulRelVal = 0;
     switch (ip)
     {
         case VOS_IP_LOAD_CONFIG:
            ulRelVal = VOS_RegisterPIDInfo(MSP_PID_CHR, (Init_Fun_Type) OM_AcpuChrInit, (Msg_Fun_Type)OM_AcpuChrMsgProc);
            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }

            ulRelVal = VOS_RegisterMsgTaskPrio(MSP_FID_CHR_ACPU, VOS_PRIORITY_M2);
            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }
            break;
          default:
            break;

     }
#endif
     return VOS_OK;
}


