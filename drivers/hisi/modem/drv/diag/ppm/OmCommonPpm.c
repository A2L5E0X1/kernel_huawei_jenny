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
**************************************************************************** */
#include "OmCommonPpm.h"
#include <linux/module.h>
#include "../../adrv/adrv.h"
#include <product_config.h>
#include <bsp_socp.h>
#include <bsp_nvim.h>
#include <bsp_slice.h>
#include <nv_stru_drv.h>
#include <acore_nv_stru_drv.h>
#include <securec.h>
#include <bsp_icc.h>
#include <bsp_slice.h>
#include "diag_port_manager.h"
#include "scm_ind_src.h"
#include "scm_ind_dst.h"
#include "scm_cnf_src.h"
#include "scm_cnf_dst.h"
#include "diag_system_debug.h"
#include "diag_port_manager.h"
#include "scm_common.h"
#include "OmUsbPpm.h"
#include "OmVcomPpm.h"
#include "OmPortSwitch.h"

/* ****************************************************************************
  2 ????????????
**************************************************************************** */

/* ????ACPU??USB??????UDI???? */
void *                               g_astOMPortUDIHandle[OM_PORT_HANDLE_BUTT];

/* USB??????OM IND?????????????????????????????????????? */
OM_PSEUDO_SYNC_STRU                     g_stUsbIndPseudoSync;

/* USB??????OM CNF?????????????????????????????????????? */
OM_PSEUDO_SYNC_STRU                     g_stUsbCfgPseudoSync;

u32                              g_ulUSBSendErrCnt   = 0;

/* ??????????????AT?????????????????????????? */
spinlock_t                            g_stPpmPortSwitchSpinLock;

OM_ACPU_DEBUG_INFO                      g_stAcpuDebugInfo;

u32                              g_ulOmAcpuDbgFlag = false;

/*****************************************************************************
  3 ????????????
*****************************************************************************/
extern spinlock_t                     g_stScmSoftDecodeDataRcvSpinLock;
extern spinlock_t                     g_stCbtScmDataRcvSpinLock;
PPM_DisconnectTLPortFuc g_disconnectCb = NULL;
/*****************************************************************************
  4 ????????
*****************************************************************************/
extern u32 PPM_SockPortInit(void);
void PPM_RegDisconnectCb(PPM_DisconnectTLPortFuc cb)
{
    g_disconnectCb = cb;
}

void PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel)
{
    if(g_disconnectCb)
    {
        if(g_disconnectCb())
        {
            diag_error("disconnect error\n");
        }
    }
    else
    {
        diag_error("disconnect func is null\n");
    }
    return;
}

void PPM_GetSendDataLen(SOCP_CODER_DST_ENUM_U32 enChanID, u32 ulDataLen, u32 *pulSendDataLen, CPM_PHY_PORT_ENUM_UINT32 *penPhyport)
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyport;

    if (SOCP_CODER_DST_OM_CNF == enChanID)
    {
        enPhyport = CPM_QueryPhyPort(CPM_OM_CFG_COMM);
    }
    else
    {
        enPhyport = CPM_QueryPhyPort(CPM_OM_IND_COMM);
    }


    /*????????????USB????????????????60k????????????????????????*/
    if (((CPM_IND_PORT == enPhyport) || (CPM_CFG_PORT == enPhyport))
        &&(ulDataLen > USB_MAX_DATA_LEN))
    {

        *pulSendDataLen = USB_MAX_DATA_LEN;
    }
    else
    {
        *pulSendDataLen = ulDataLen;  /*????????????????????????????????????sd??wifi*/
    }

    *penPhyport = enPhyport;
    return;
}


void PPM_PortStatus(OM_PROT_HANDLE_ENUM_UINT32 enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort,ACM_EVT_E enPortState)
{
    OM_LOGIC_CHANNEL_ENUM_UINT32    enChannel;
    unsigned long                   ulLockLevel;
    bool                            ulSndMsg = false;
    u32                             ulSlicelow;

    if (ACM_EVT_DEV_SUSPEND == enPortState)
    {
        ulSlicelow = bsp_get_slice_value();

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutTime = ulSlicelow;

        diag_crit("Receive USB disconnect (chan %d) callback at slice 0x%x!\n",enHandle, ulSlicelow);

        scm_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

        ulSndMsg  = false;
        enChannel = OM_LOGIC_CHANNEL_BUTT;

        /* CFG????????GU??TL????????????????????GU??TL????????????????CPM?????? */
        if (OM_USB_CFG_PORT_HANDLE == enHandle)
        {
            if (enPhyPort == CPM_QueryPhyPort(CPM_OM_CFG_COMM))
            {
                ulSndMsg  = true;
                enChannel = OM_LOGIC_CHANNEL_CNF;
            }
        }
        /* IND??????????????????GU??TL?????? */
        else if (OM_USB_IND_PORT_HANDLE == enHandle)
        {
            if (enPhyPort == CPM_QueryPhyPort(CPM_OM_IND_COMM))
            {
                ulSndMsg  = true;
                enChannel = OM_LOGIC_CHANNEL_IND;
            }
        }
        else
        {

        }

        scm_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

        if (true == ulSndMsg)
        {
            PPM_DisconnectAllPort(enChannel);
        }
    }
    else if(ACM_EVT_DEV_READY == enPortState)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINTime = bsp_get_slice_value();
    }
    else
    {
        diag_error("The USB Port %d State %d is Unknow", (s32)enPhyPort, (s32)enPortState);

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrTime = bsp_get_slice_value();
    }

    return;
}


void PPM_PortCloseProc(OM_PROT_HANDLE_ENUM_UINT32  enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort)
{
    unsigned long                           ulLockLevel;
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    bool                            ulSndMsg = false;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseSlice = bsp_get_slice_value();

    if (!g_astOMPortUDIHandle[enHandle])
    {
        return;
    }
    bsp_acm_close(g_astOMPortUDIHandle[enHandle]);
    g_astOMPortUDIHandle[enHandle] = NULL;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkSlice = bsp_get_slice_value();

    scm_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    ulSndMsg  = false;
    enChannel = OM_LOGIC_CHANNEL_BUTT;

    /* CFG????????GU??TL????????????????????GU??TL????????????????CPM?????? */
    if (OM_USB_CFG_PORT_HANDLE == enHandle)
    {
        if (enPhyPort == CPM_QueryPhyPort(CPM_OM_CFG_COMM))
        {
            ulSndMsg  = true;
            enChannel = OM_LOGIC_CHANNEL_CNF;
        }
    }
    /* IND??????????????????GU??TL????????????????CPM?????? */
    else if (OM_USB_IND_PORT_HANDLE == enHandle)
    {
        if (enPhyPort == CPM_QueryPhyPort(CPM_OM_IND_COMM))
        {
            ulSndMsg  = true;
            enChannel = OM_LOGIC_CHANNEL_IND;
        }
    }
    else
    {

    }

    scm_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    if (true == ulSndMsg)
    {
        PPM_DisconnectAllPort(enChannel);
    }

    return;
}


u32 PPM_ReadPortData(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, void* UdiHandle, OM_PROT_HANDLE_ENUM_UINT32 enHandle)
{
    ACM_WR_ASYNC_INFO                   stInfo={NULL,NULL,0,NULL};
    u32 ret = 0xFFFFFFFF;

    diag_PTR(EN_DIAG_PTR_PPM_READDATA, 0, 0, 0);

    if (NULL == UdiHandle)
    {
        diag_error("Input HANDLE is err\n");

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleErr++;

        diag_PTR(EN_DIAG_PTR_PPM_ERR1, 0, 0, 0);

        return (u32)BSP_ERROR;
    }

    (void)memset_s(&stInfo, sizeof(stInfo), 0, sizeof(stInfo));

    /* ????USB??IO CTRL?????????? */

    if (BSP_OK != bsp_acm_ioctl(UdiHandle, ACM_IOCTL_GET_RD_BUFF, &stInfo))
    {
        diag_error("Call ioctl Failed\n");
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadGetBufferErr++;
        diag_PTR(EN_DIAG_PTR_PPM_ERR2, 0, 0, 0);
        return (u32)BSP_ERROR;
    }

    OM_ACPU_DEBUG_CHANNEL_TRACE(enPhyPort, (u8*)stInfo.pVirAddr, stInfo.u32Size,OM_ACPU_USB_CB,OM_ACPU_DATA);

    ret = CPM_ComRcv(enPhyPort, (u8*)stInfo.pVirAddr, stInfo.u32Size);
    if(BSP_OK != ret)
    {
        diag_error("CPM_ComRcv fail(0x%x), PhyPort is %d\n", ret, (s32)enPhyPort);
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiCommRcvNullPtrErr++;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktByte += stInfo.u32Size;

    if(BSP_OK != bsp_acm_ioctl(UdiHandle, ACM_IOCTL_RETURN_BUFF, &stInfo))
    {
        diag_error("ioctl Fail\n");
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadBufferFreeErr++;
    }

    return BSP_OK;
}



void PPM_PortPseudoSyncGetSmp(OM_PROT_HANDLE_ENUM_UINT32 enHandle)
{
    return;
}

u32 PPM_UdiRegCallBackFun(void* enHandle, u32 ulCmdType, void* pFunc)
{
    if (NULL == pFunc)
    {
        return BSP_OK;
    }

    if (BSP_OK != bsp_acm_ioctl(enHandle, ulCmdType, pFunc))
    {
        diag_error("mdrv_udi_ioctl Failed\n");
        return (u32)BSP_ERROR;
    }

    return BSP_OK;
}


#define OM_SOCP_CNF_BUFFER_SIZE          (8*1024)
#define OM_SOCP_CNF_BUFFER_NUM           (8)

#define OM_SOCP_IND_BUFFER_SIZE          (2*1024)
#define OM_SOCP_IND_BUFFER_NUM           (2)

/*****************************************************************************
 ?? ?? ??  : PPM_ReadPortDataInit
 ????????  : ??????????OM??????????
 ????????  : enPhyPort: ??????????
             enHandle: ??????????
             pReadCB: ????????????????????????
             pWriteCB: ??????????????????????????
             pStateCB: ????????????????????????
 ????????  : ??
 ?? ?? ??  : BSP_OK/BSP_ERROR
*****************************************************************************/
void PPM_ReadPortDataInit(CPM_PHY_PORT_ENUM_UINT32        enPhyPort,
                                    OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                    void                            *pReadCB,
                                    void                            *pWriteCB,
                                    void                            *pStateCB)
{
    UDI_OPEN_PARAM_S                    stUdiPara;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;

    /*????????????????USB????*/
    if (CPM_IND_PORT == enPhyPort)
    {
        stReadBuffInfo.u32BuffSize = OM_SOCP_IND_BUFFER_SIZE;
        stReadBuffInfo.u32BuffNum  = OM_SOCP_IND_BUFFER_NUM;
        stUdiPara.devid            = UDI_ACM_LTE_DIAG_ID;
    }
    else if (CPM_CFG_PORT == enPhyPort)
    {
        stReadBuffInfo.u32BuffSize = OM_SOCP_CNF_BUFFER_SIZE;
        stReadBuffInfo.u32BuffNum  = OM_SOCP_CNF_BUFFER_NUM;
        stUdiPara.devid            = UDI_ACM_GPS_ID;
    }
    else
    {
        diag_error("Open Wrong Port %d\n", (s32)enPhyPort);

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice = mdrv_timer_get_normal_timestamp();

    if (NULL != g_astOMPortUDIHandle[enHandle])
    {
        diag_crit("The UDI Handle is not Null\n");
        return;
    }

    /* ????OM??????USB???? */
    g_astOMPortUDIHandle[enHandle] = bsp_acm_open(stUdiPara.devid);

    if (NULL == g_astOMPortUDIHandle[enHandle])
    {
        diag_error("Open UDI ACM failed!");

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice = mdrv_timer_get_normal_timestamp();

    /* ????OM??????USB???????? */
    if (BSP_OK != bsp_acm_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
    {
        diag_error("mdrv_udi_ioctl Failed\n");

        return;
    }

    /* ????OM??????USB?????????????? */
    if (BSP_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_READ_CB, pReadCB))
    {
        diag_error("mdrv_udi_ioctl Failed\r\n");

        return;
    }

#ifdef BSP_CONFIG_PHONE_TYPE
    if(BSP_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_WRITE_CB, pWriteCB))
    {
        diag_error("mdrv_udi_ioctl Failed\r\n");

        return;
    }
#else
    if(enHandle == OM_USB_IND_PORT_HANDLE)
    {
        if(BSP_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_WRITE_INFO_CB, pWriteCB))
        {
            diag_error("mdrv_udi_ioctl Failed\r\n");
            return;
        }
    }
    else
    {
	    if(BSP_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_WRITE_CB, pWriteCB))
	    {
	        diag_error("mdrv_udi_ioctl Failed\r\n");

	        return;
        }
    }
#endif

    if(BSP_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_EVT_CB, pStateCB))
    {
        diag_error("mdrv_udi_ioctl Failed\r\n");

        return;
    }

    if (BSP_OK != bsp_acm_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_WRITE_DO_COPY, NULL))
    {
        diag_error("mdrv_udi_ioctl Failed\r\n");

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice = mdrv_timer_get_normal_timestamp();

    return;
}


u32 PPM_PortSendCheckParm(OM_PROT_HANDLE_ENUM_UINT32 enHandle, u8 *pucVirAddr, u8 *pucPhyAddr, u32 ulDataLen)
{
    if((OM_USB_CFG_PORT_HANDLE == enHandle)
        || (OM_HSIC_CFG_PORT_HANDLE == enHandle))
    {
        diag_PTR(EN_DIAG_PTR_PPM_PORTSEND, 1, enHandle, ulDataLen);
    }

    if ((NULL == pucVirAddr) || (NULL == pucPhyAddr))
    {
        diag_error("Vir or Phy Addr is Null \n");
        return CPM_SEND_PARA_ERR;
    }

    if(!g_astOMPortUDIHandle[enHandle])
    {
        g_stAcpuDebugInfo.ulInvaldChannel++;
        return CPM_SEND_ERR;
    }

    return ERR_MSP_SUCCESS;
}

u32 PPM_PortSend(OM_PROT_HANDLE_ENUM_UINT32 enHandle, u8 *pucVirAddr, u8 *pucPhyAddr, u32 ulDataLen)
{
    s32           lRet;
    ACM_WR_ASYNC_INFO   stVcom;
    u32          ulInSlice;
    u32          ulOutSlice;
    u32          ulWriteSlice;

    lRet = (s32)PPM_PortSendCheckParm(enHandle, pucVirAddr, pucPhyAddr, ulDataLen);
    if(lRet)
    {
        return (u32)lRet;
    }

    stVcom.pVirAddr = (char*)pucVirAddr;
    stVcom.pPhyAddr = (char*)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = NULL;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum1++;

    if(OM_USB_IND_PORT_HANDLE == enHandle)
    {
        g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendLen += ulDataLen;
        diag_system_debug_usb_len(ulDataLen);
		diag_system_debug_send_data_end();
        diag_system_debug_send_usb_start();
    }
    else
    {
        g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendLen += ulDataLen;
    }

    ulInSlice = bsp_get_slice_value();

    /* ?????????????????????????????? */
    lRet = (s32)bsp_acm_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_WRITE_ASYNC, &stVcom);

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum2++;

    ulOutSlice = bsp_get_slice_value();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = (0xffffffff - ulInSlice) + ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }

    if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime = ulWriteSlice;
    }


    if (MDRV_OK == lRet)     /*????????????*/
    {
        /* ?????????????????????? */
        PPM_PortPseudoSyncGetSmp(enHandle);
        if(OM_USB_IND_PORT_HANDLE == enHandle)
        {
            diag_system_debug_usb_ok_len(ulDataLen);
        }
        return CPM_SEND_AYNC;

    }
    else if(MDRV_OK > lRet)    /*????????*/
    {
        if(OM_USB_IND_PORT_HANDLE == enHandle)
        {
            diag_system_debug_usb_fail_len(ulDataLen);
        }
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrValue  = (u32)lRet;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrTime   = bsp_get_slice_value();

        g_ulUSBSendErrCnt++;

        return CPM_SEND_FUNC_NULL; /*??????????????????????NULL????????*/
    }
    else    /*????????????????????*/
    {
        if(OM_USB_IND_PORT_HANDLE == enHandle)
        {
            diag_system_debug_usb_fail_len(ulDataLen);
        }

        return CPM_SEND_ERR;
    }
}


void PPM_PortWriteAsyCB(OM_PROT_HANDLE_ENUM_UINT32 enHandle, PPM_BUFF_ADDR_STRU* retAddr)
{
    u32      ulRlsLen;
    OM_SOCP_CHANNEL_DEBUG_INFO *pstCnfDebugInfo;
    OM_SOCP_CHANNEL_DEBUG_INFO *pstIndDebugInfo;

    pstCnfDebugInfo = &g_stAcpuDebugInfo.stCnfDebugInfo;
    pstIndDebugInfo = &g_stAcpuDebugInfo.stIndDebugInfo;

    if(retAddr->len < 0)
    {
        ulRlsLen = 0;
    }
    else
    {
        ulRlsLen = (u32)retAddr->len;
    }

    /* ???????????????????? */
    if(OM_USB_IND_PORT_HANDLE == enHandle)
    {
        diag_ThroughputSave(EN_DIAG_THRPUT_DATA_CHN_CB, ulRlsLen);
        diag_system_debug_usb_free_len(ulRlsLen);

        diag_system_debug_send_usb_end();
    }

    /* ?????????????????????? */
    if (OM_USB_IND_PORT_HANDLE == enHandle)
    {
        g_stUsbIndPseudoSync.ulLen          = ulRlsLen;
        g_stUsbIndPseudoSync.pucAsyncCBData = retAddr->virAddr;

	    pstIndDebugInfo->ulUSBSendRealLen += ulRlsLen;
        scm_rls_ind_dst_buff(ulRlsLen);
    }
    else if (OM_USB_CFG_PORT_HANDLE == enHandle)
    {
        g_stUsbCfgPseudoSync.ulLen          = ulRlsLen;
        g_stUsbCfgPseudoSync.pucAsyncCBData = retAddr->virAddr;

	pstCnfDebugInfo->ulUSBSendRealLen += ulRlsLen;
        scm_rls_cnf_dst_buff(ulRlsLen);
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteCBNum++;

    return;
}


OM_PSEUDO_SYNC_STRU * PPM_ComPpmGetSyncInfo(void)
{
    return &g_stUsbIndPseudoSync;
}

OM_ACPU_DEBUG_INFO * PPM_ComPpmGetDebugInfo(void)
{
    return &g_stAcpuDebugInfo;
}

/*****************************************************************************
 ?? ?? ??  : PPM_InitPhyPort
 ????????  : ??????????????
 ????????  : void
 ????????  : ??
 ?? ?? ??  : BSP_OK:????????????????
 ????????:
*****************************************************************************/
int PPM_InitPhyPort(void)
{
    if (BSP_OK != PPM_PortInit())
    {
        diag_error("PPM_PortInit failed\n");
        return BSP_ERROR;
    }

#if ((defined(FEATURE_HISOCKET))&&(FEATURE_HISOCKET == FEATURE_ON))||(defined(FEATURE_SVLSOCKET))
    if(BSP_OK != PPM_SockPortInit())
    {
        diag_crit("ppm socket not init\n");
    }
#endif

    if(BSP_OK != PPM_PortSwtichInit())
    {
        diag_error("PPM_PortSwtichInit fail\n");
        return BSP_ERROR;
    }

    diag_crit("diag ppm init ok\n");
    return BSP_OK;
}

u32 PPM_PortInit(void)
{
    (void)memset_s(&g_stAcpuDebugInfo, sizeof(g_stAcpuDebugInfo), 0, sizeof(g_stAcpuDebugInfo));

    (void)memset_s(g_astOMPortUDIHandle, sizeof(g_astOMPortUDIHandle), 0, sizeof(g_astOMPortUDIHandle));
    scm_SpinLockInit(&g_stPpmPortSwitchSpinLock);

    /* USB?????????????????????????? */
    PPM_UsbPortInit();

    /* Vcom?????????????????????????? */
    PPM_VComPortInit();


    return BSP_OK;
}


/*****************************************************************************
 ?? ?? ??  : OmOpenLog
 ????????  : ????????OM??????????
 ????????  :
 ????????  :
 ?? ?? ??  :
 ????????  :
 ????????  :
 ????????  :
*****************************************************************************/
void OmOpenLog(u32 ulFlag)
{
    g_ulOmAcpuDbgFlag = ulFlag;

    return;
}



void PPM_OmPortInfoShow(OM_PROT_HANDLE_ENUM_UINT32  enHandle)
{
    diag_crit("Invalidchanel num is             %d\n",   g_stAcpuDebugInfo.ulInvaldChannel);

    diag_crit("The Port Write num 1 is          %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum1);
    diag_crit("The Port Write num 2 is          %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum2);
    diag_crit("The Port Write Max Time is       0x%x\n", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime);

    diag_crit("The Port Write CB Num is         %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteCBNum);

    diag_crit("The Port Write Err Time is       %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrTime);
    diag_crit("The Port Write Err Num  is       %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrNum);
    diag_crit("The Port Write Err Value is      0x%x\n", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrValue);
    diag_crit("The Port Write Err Len is        0x%x\n", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrLen);

    diag_crit("The Port In CB Num is            %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINNum);
    diag_crit("The Port In CB Time is           0x%x\n", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINTime);
    diag_crit("The Port Out CB Num is           %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutNum);
    diag_crit("The Port Out CB Time is          0x%x\n", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutTime);
    diag_crit("The Port State CB Err Num is     %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrNum);
    diag_crit("The Port State CB Err Time is    0x%x\n", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrTime);

    diag_crit("The Port Open num is            %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum);
    diag_crit("The Port Open slice is          0x%x\n",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice);

    diag_crit("The Port Open OK num is         %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum);
    diag_crit("The Port Open OK slice is       0x%x\n",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice);

    diag_crit("The Port Open OK2 num is        %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num);
    diag_crit("The Port Open OK2 slice is      0x%x\n",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice);

    diag_crit("The Port Close num is           %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseNum);
    diag_crit("The Port Close slice is         0x%x\n",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseSlice);

    diag_crit("The Port Close OK num is        %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkNum);
    diag_crit("The Port Close OK slice is      0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkSlice);

    diag_crit("USB IND Pseudo sync fail num is   %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBIndPseudoSyncFailNum);
    diag_crit("USB IND Pseudo sync fail slice is 0x%x\n",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBIndPseudoSyncFailSlice);
    diag_crit("USB CFG Pseudo sync fail num is   %d\n",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCnfPseudoSyncFailNum);
    diag_crit("USB CFG Pseudo sync fail slice is 0x%x\n",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCnfPseudoSyncFailSlice);

    diag_crit("The Port UDI Handle Err num is %d\n",                 g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleErr);
    diag_crit("The Port UDI Handle Get Buffer Err num is %d\n",      g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadGetBufferErr);
    diag_crit("The Port UDI Handle Comm Rcv Null Ptr num is %d\n",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiCommRcvNullPtrErr);
    diag_crit("The Port UDI Handle Read Buffer Free Err num is %d\n",g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadBufferFreeErr);

    diag_crit("The Port UDI Handle Total Rcv Pkt num is %d\n",       g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktNum);
    diag_crit("The Port UDI Handle Total Rcv Byte is %d.\n",          g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktByte);

    return;
}
EXPORT_SYMBOL(PPM_OmPortInfoShow);


void PPM_OmPortDebugInfoShow(void)
{
    diag_crit("IND ulOmDiscardNum %d, len %d; ulUSBSendErrNum %d, Len %d; ulUSBSendNum %d, len %d, reallen %d.\n",
    g_stAcpuDebugInfo.stIndDebugInfo.ulOmDiscardNum, g_stAcpuDebugInfo.stIndDebugInfo.ulOmDiscardLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendErrNum, g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendErrLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendNum, g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendRealLen);

    diag_crit("CNF ulOmDiscardNum %d, len %d; ulUSBSendErrNum %d, Len %d; ulUSBSendNum %d, len %d, Reallen %d.\n",
    g_stAcpuDebugInfo.stCnfDebugInfo.ulOmDiscardNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulOmDiscardLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendErrNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendErrLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendRealLen);
}
EXPORT_SYMBOL(PPM_OmPortDebugInfoShow);





