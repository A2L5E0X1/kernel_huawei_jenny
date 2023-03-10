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
  1 Include HeadFile
*****************************************************************************/
#include "msp_debug.h"
#include <mdrv.h>
#include <mdrv_diag_system.h>
#include <msp_errno.h>
#include <nv_stru_drv.h>
#include <acore_nv_stru_drv.h>
#include <nv_stru_pam.h>
#include "diag_common.h"
#include "diag_debug.h"
#include "diag_cfg.h"


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

#define    THIS_FILE_ID        MSP_FILE_ID_MSP_DEBUG_C

#define    DIAG_LOG_PATH       MODEM_LOG_ROOT"/drv/DIAG/"

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : PTR : Process Trace Record (????????????)
 Description     : ????????????????
*****************************************************************************/
extern OM_ACPU_DEBUG_INFO g_stAcpuDebugInfo;

extern DIAG_CHANNLE_PORT_CFG_STRU g_stPortCfg;

extern OM_VCOM_DEBUG_INFO g_stVComDebugInfo[3];

extern VOS_UINT32 g_ulDiagCfgInfo;


VOS_VOID DIAG_DebugCommon(VOS_VOID)
{
    void *pFile = VOS_NULL;
    VOS_UINT32 ret;
    VOS_CHAR *DirPath = DIAG_LOG_PATH;
    VOS_CHAR *FilePath = DIAG_LOG_PATH"DIAG_DebugCommon.bin";
    VOS_UINT32 ulValue;
    VOS_UINT8 *pData = VOS_NULL;
    VOS_UINT32 ullen,offset;
    VOS_CHAR   aucInfo[DIAG_DEBUG_INFO_LEN];

    /* ??????U32????A/C??PID???? */
    ullen =   sizeof(g_ulDiagCfgInfo)
            + sizeof(g_stPortCfg)
            + sizeof(VOS_UINT32) + sizeof(g_stAcpuDebugInfo);
     ullen += sizeof(VOS_UINT32) + sizeof(g_stVComDebugInfo);
    pData = (VOS_UINT8 *)VOS_MemAlloc(DIAG_AGENT_PID, DYNAMIC_MEM_PT, ullen);
    if(VOS_NULL == pData)
    {
        return;
    }

    /* ????DIAG?????????????????????? */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            diag_error("make file %s failed.\n", DIAG_LOG_PATH);
            VOS_MemFree(DIAG_AGENT_PID, pData);
            return ;
        }
    }

    pFile = mdrv_file_open(FilePath, "wb+");
    if(pFile == 0)
    {
        diag_error("open file %s failed.\n", FilePath);

        VOS_MemFree(DIAG_AGENT_PID, pData);

        return ;
    }

    ret = mdrv_diag_debug_file_header(pFile);
    if(VOS_OK != ret)
    {
        diag_error("add debug file header faile\n");
        (VOS_VOID)mdrv_file_close(pFile);
        VOS_MemFree(DIAG_AGENT_PID, pData);
        return ;
    }

    (VOS_VOID)VOS_MemSet_s(aucInfo, sizeof(aucInfo), 0, sizeof(aucInfo));
    (VOS_VOID)VOS_MemCpy_s(aucInfo, sizeof(aucInfo), "DIAG common info", VOS_StrNLen("DIAG common info", sizeof(aucInfo)-1));

    /* ???????? */
    ret = mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        diag_error(" mdrv_file_write DIAG number info failed.\n");
    }

    offset  = 0;

    /* ????DIAG?????????? */
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_ulDiagCfgInfo, sizeof(g_ulDiagCfgInfo));
    offset += sizeof(g_ulDiagCfgInfo);

    /* CPM???????????????????? */
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_stPortCfg, sizeof(g_stPortCfg));
    offset += sizeof(g_stPortCfg);

    /* USB?????????????????????? */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stAcpuDebugInfo);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_stAcpuDebugInfo, sizeof(g_stAcpuDebugInfo));
    offset += sizeof(g_stAcpuDebugInfo);

    /* netlink?????????????????????? */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stVComDebugInfo);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_stVComDebugInfo, sizeof(g_stVComDebugInfo));
    offset += sizeof(g_stVComDebugInfo);

    ret = mdrv_file_write(pData, 1, offset, pFile);
    if(ret != offset)
    {
        diag_error(" mdrv_file_write pData failed.\n");
    }

    mdrv_diag_debug_file_tail(pFile, FilePath);

    (VOS_VOID)mdrv_file_close(pFile);

    VOS_MemFree(DIAG_AGENT_PID, pData);

    return ;
}


extern VOS_UINT8 g_EventModuleCfg[DIAG_CFG_PID_NUM];

extern DIAG_CBT_INFO_TBL_STRU g_astCBTInfoTbl[EN_DIAG_DEBUG_INFO_MAX];



VOS_VOID diag_numberinfo(const void *pFile)
{
    VOS_UINT32 ret;
    VOS_UINT32 ulValue;
    VOS_CHAR   aucInfo[DIAG_DEBUG_INFO_LEN];

    (VOS_VOID)VOS_MemSet_s(aucInfo, sizeof(aucInfo),0, DIAG_DEBUG_INFO_LEN);
    (VOS_VOID)VOS_MemCpy_s(aucInfo, sizeof(aucInfo), "DIAG number info", VOS_StrNLen("DIAG number info",sizeof(aucInfo)-1));

    /* ???????????? */
    ret = (VOS_UINT32)mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        diag_error(" mdrv_file_write DIAG number info failed.\n");
    }

    /* ??????slice */
    ulValue = VOS_GetSlice();
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        diag_error(" mdrv_file_write ulTime failed.\n");
    }

    /* ??????size */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_astCBTInfoTbl);
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        diag_error(" mdrv_file_write ulTime failed.\n");
    }

    /* ???????????????? */
    ret = (VOS_UINT32)mdrv_file_write(&g_astCBTInfoTbl[0], 1, sizeof(g_astCBTInfoTbl), pFile);
    if(ret != sizeof(g_astCBTInfoTbl))
    {
        diag_error(" mdrv_file_write g_astCBTInfoTbl failed.\n");
    }
}


VOS_VOID DIAG_DebugNoIndLog(VOS_VOID)
{
    void *pFile = VOS_NULL;
    VOS_UINT32 ret;
    VOS_CHAR *DirPath = DIAG_LOG_PATH;
    VOS_CHAR *FilePath = DIAG_LOG_PATH"DIAG_AcoreNoIndLog.bin";
    VOS_UINT32 ulValue;
    VOS_CHAR   aucInfo[DIAG_DEBUG_INFO_LEN];
    VOS_UINT8 *pData;
    VOS_UINT32 ullen,offset;

    /* ??????U32????A/C??PID???? */
    ullen = (2 * sizeof(VOS_UINT32))
            + sizeof(VOS_UINT32) + sizeof(g_ALayerSrcModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_CLayerSrcModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_ALayerDstModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_CLayerDstModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_stMsgCfg)
            + sizeof(VOS_UINT32) + sizeof(g_EventModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_PrintTotalCfg)
            + sizeof(VOS_UINT32) + sizeof(g_PrintModuleCfg);

    pData = VOS_MemAlloc(DIAG_AGENT_PID, DYNAMIC_MEM_PT, ullen);
    if(VOS_NULL == pData)
    {
        return;
    }

    /* ????DIAG?????????????????????? */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            diag_error(" mkdir %s failed.\n", DIAG_LOG_PATH);
            VOS_MemFree(DIAG_AGENT_PID, pData);
            return ;
        }
    }

    pFile = mdrv_file_open(FilePath, "wb+");
    if(pFile == 0)
    {
        diag_error("open %s failed.\n", FilePath);

        VOS_MemFree(DIAG_AGENT_PID, pData);

        return ;
    }

    ret = mdrv_diag_debug_file_header(pFile);
    if(VOS_OK != ret)
    {
        diag_error("add file header failed .\n");
        VOS_MemFree(DIAG_AGENT_PID, pData);
        (VOS_VOID)mdrv_file_close(pFile);
        return ;
    }

    (VOS_VOID)VOS_MemSet_s(aucInfo, sizeof(aucInfo), 0, sizeof(aucInfo));
    (VOS_VOID)VOS_MemCpy_s(aucInfo, sizeof(aucInfo), "DIAG config info", VOS_StrNLen("DIAG config info", sizeof(aucInfo)-1));

    /* ???????????? */
    ret = (VOS_UINT32)mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        diag_error(" mdrv_file_write DIAG config info failed.\n");
    }

    offset  = 0;

    /* A??PID???? */
    ulValue = VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND;
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    /* C??PID???? */
    ulValue = VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND;
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_ALayerSrcModuleCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_ALayerSrcModuleCfg[0], sizeof(g_ALayerSrcModuleCfg));
    offset += sizeof(g_ALayerSrcModuleCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_CLayerSrcModuleCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_CLayerSrcModuleCfg[0], sizeof(g_CLayerSrcModuleCfg));
    offset += sizeof(g_CLayerSrcModuleCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_ALayerDstModuleCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_ALayerDstModuleCfg[0], sizeof(g_ALayerDstModuleCfg));
    offset += sizeof(g_ALayerDstModuleCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_CLayerDstModuleCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_CLayerDstModuleCfg[0], sizeof(g_CLayerDstModuleCfg));
    offset += sizeof(g_CLayerDstModuleCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stMsgCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_stMsgCfg, sizeof(g_stMsgCfg));
    offset += sizeof(g_stMsgCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_EventModuleCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_EventModuleCfg[0], sizeof(g_EventModuleCfg));
    offset += sizeof(g_EventModuleCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_PrintTotalCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_PrintTotalCfg, sizeof(g_PrintTotalCfg));
    offset += sizeof(g_PrintTotalCfg);

    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_PrintModuleCfg);
    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);

    (VOS_VOID)VOS_MemCpy_s((pData + offset), (ullen - offset), &g_PrintModuleCfg[0], sizeof(g_PrintModuleCfg));
    offset += sizeof(g_PrintModuleCfg);

    ret = (VOS_UINT32)mdrv_file_write(pData, 1, offset, pFile);
    if(ret != offset)
    {
        diag_error(" mdrv_file_write pData failed.\n");
    }

    diag_numberinfo(pFile);

    /* ????5?????????????? */
    (VOS_VOID)VOS_TaskDelay(5000);

    diag_numberinfo(pFile);

    mdrv_diag_debug_file_tail(pFile, FilePath);

    (VOS_VOID)mdrv_file_close(pFile);

    VOS_MemFree(DIAG_AGENT_PID, pData);

    return ;
}



