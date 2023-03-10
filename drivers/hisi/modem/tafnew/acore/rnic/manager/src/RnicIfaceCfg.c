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

#include "PsCommonDef.h"
#include "RnicMsgProc.h"
#include "RnicEntity.h"
#include "RnicMntn.h"
#include "RnicIfaceOndemand.h"
#include "RnicLog.h"
#include "BastetRnicInterface.h"
#include "rnic_ondemand_i.h"
#include "rnic_policy_manage.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_RNIC_IFACE_CFG_C


/*****************************************************************************
  2 ????????????
*****************************************************************************/

/*****************************************************************************
  3 ????????
*****************************************************************************/


VOS_VOID RNIC_IFACE_SetNapiCfg(RNIC_DEV_ID_ENUM_UINT8 enRmNetId)
{
    struct rnic_napi_config_s           stNapiCfg;

    stNapiCfg.devid             = enRmNetId;
    stNapiCfg.napi_enable       = RNIC_GET_NAPI_FEATURE(enRmNetId);
    stNapiCfg.gro_enable        = RNIC_GET_GRO_FEATURE(enRmNetId);
    stNapiCfg.napi_weight       = RNIC_GET_NAPI_WEIGHT(enRmNetId);
    stNapiCfg.napi_queue_length = RNIC_GET_NAPI_POLL_QUE_MAX_LEN(enRmNetId);

    rnic_set_dev_napi_config(&stNapiCfg);
    return;
}


VOS_VOID RNIC_IFACE_SetNapiLbCfg(
    RNIC_DEV_ID_ENUM_UINT8              enRmNetId
)
{
    struct rnic_lb_config_s        stNapiLbCfg;

    stNapiLbCfg.devid       = enRmNetId;
    stNapiLbCfg.enable      = RNIC_GET_NAPI_LB_FEATURE(enRmNetId);
    stNapiLbCfg.cpu_bitmask = RNIC_GET_NAPI_LB_CPUMASK(enRmNetId);

    TAF_MEM_CPY_S( stNapiLbCfg.level_cfg,
                   sizeof(struct rnic_lb_level_config_s) * RNIC_LB_MAX_LEVEL,
                   RNIC_GET_NAPI_LB_LEVEL_CFG(enRmNetId),
                   sizeof(RNIC_NAPI_LB_LEVEL_CFG_STRU) * RNIC_NVIM_NAPI_LB_MAX_LEVEL);

    rnic_set_dev_napi_lb_config(&stNapiLbCfg);
    return;
}


VOS_VOID RNIC_IFACE_SetNapiLbLevel(
    RNIC_DEV_ID_ENUM_UINT8              enRmNetId,
    VOS_UINT8                           ucLbLevel
)
{
    if (ucLbLevel != RNIC_GET_NAPI_LB_CUR_LEVEL(enRmNetId))
    {
        if (!rnic_set_dev_napi_lb_level(enRmNetId, ucLbLevel))
        {
            RNIC_SET_NAPI_LB_CUR_LEVEL(enRmNetId, ucLbLevel);
        }
    }
    return;
}


VOS_VOID RNIC_IFACE_SetNapiWeight(
    RNIC_DEV_ID_ENUM_UINT8              enRmNetId,
    VOS_UINT8                           ucWeight
)
{
    if (ucWeight != RNIC_GET_NAPI_WEIGHT(enRmNetId))
    {
        rnic_set_dev_napi_weight(enRmNetId, ucWeight);
        RNIC_SET_NAPI_WEIGHT(enRmNetId, ucWeight);
    }

    return;
}


VOS_VOID RNIC_IFACE_SetCpuFreqCtrlCfg(VOS_VOID)
{
    struct rnic_cpufreq_ctrl_config_s   stCpuFreqCtrlCfg;

    stCpuFreqCtrlCfg.enable    = g_stRnicCtx.stCpuFreqCtrlCfg.ucEnable;
    stCpuFreqCtrlCfg.cur_level = g_stRnicCtx.stCpuFreqCtrlCfg.ucCurLevel;

    TAF_MEM_CPY_S( stCpuFreqCtrlCfg.level_cfg,
                   sizeof(struct rnic_cpufreq_ctrl_level_config_s) * RNIC_CPU_FREQ_CTRL_MAX_LEVEL,
                   g_stRnicCtx.stCpuFreqCtrlCfg.astLevelCfg,
                   sizeof(RNIC_CPU_FREQ_CTRL_LEVEL_STRU) * RNIC_NVIM_CPU_FREQ_CTRL_MAX_LEVEL);

    rnic_set_dev_cpufreq_ctrl_config(&stCpuFreqCtrlCfg);
    return;
}


VOS_VOID RNIC_IFACE_ResetNapiConfig(RNIC_DEV_ID_ENUM_UINT8 enRmNetId)
{
    VOS_UINT8                           ucMinWeight = RNIC_GET_NAPI_WEIGHT_LEVEL1(enRmNetId);

    if (RNIC_FEATURE_ON == RNIC_GET_NAPI_FEATURE(enRmNetId))
    {
        if (0 != rnic_set_dev_napi_weight(enRmNetId, ucMinWeight))
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC,
                "RNIC_IFACE_ResetNapiConfig: set rnic_set_napi_weight fail!");
        }
        RNIC_SET_NAPI_WEIGHT(enRmNetId, ucMinWeight);
    }

    if (RNIC_FEATURE_ON == RNIC_GET_NAPI_LB_FEATURE(enRmNetId))
    {
        if (0 != rnic_set_dev_napi_lb_level(enRmNetId, 0))
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC,
                "RNIC_IFACE_ResetNapiConfig: set rnic_set_lb_level fail!");
        }
        RNIC_SET_NAPI_LB_CUR_LEVEL(enRmNetId, 0);
    }

    return;
}


VOS_VOID RNIC_IFACE_ResetCpufreqLevel(VOS_VOID)
{
    if (RNIC_FEATURE_ON == g_stRnicCtx.stCpuFreqCtrlCfg.ucEnable)
    {
        rnic_set_dev_cpufreq_level(0);
        g_stRnicCtx.stCpuFreqCtrlCfg.ucCurLevel = 0;
    }
}


VOS_UINT8 RNIC_IFACE_CalcNapiWeight(VOS_UINT8 ucRmNetId)
{
    VOS_UINT8                           ucWeight;
    VOS_UINT32                          ulDlNapiRecvPktNum;

    ucWeight           = RNIC_NAPI_POLL_DEFAULT_WEIGHT;
    ulDlNapiRecvPktNum = RNIC_GET_IFACE_PERIOD_RECV_PKT(ucRmNetId);

    /* ????4??:2/4/8/16
     * 150M bps????????????12300??????????????????????weight????????2??
     * 300M bps????????????24600????????[12300,24600]????????????weight????????4??
     * 450M bps????????????38400????????[24600,38400]????????????weight????????8??
     * 600M bps????????????49200??????????38400??weight????????????16??
     */

    if (ulDlNapiRecvPktNum <= RNIC_GET_DL_PKT_NUM_PER_SEC_LEVEL1(ucRmNetId))
    {
        ucWeight = RNIC_GET_NAPI_WEIGHT_LEVEL1(ucRmNetId);
    }
    else if ((ulDlNapiRecvPktNum > RNIC_GET_DL_PKT_NUM_PER_SEC_LEVEL1(ucRmNetId))
          && (ulDlNapiRecvPktNum <= RNIC_GET_DL_PKT_NUM_PER_SEC_LEVEL2(ucRmNetId)))
    {
        ucWeight = RNIC_GET_NAPI_WEIGHT_LEVEL2(ucRmNetId);
    }
    else if ((ulDlNapiRecvPktNum > RNIC_GET_DL_PKT_NUM_PER_SEC_LEVEL1(ucRmNetId))
          && (ulDlNapiRecvPktNum <= RNIC_GET_DL_PKT_NUM_PER_SEC_LEVEL3(ucRmNetId)))
    {
        ucWeight = RNIC_GET_NAPI_WEIGHT_LEVEL3(ucRmNetId);
    }
    else
    {
        ucWeight = RNIC_GET_NAPI_WEIGHT_LEVEL4(ucRmNetId);
    }

    return ucWeight;
}

VOS_VOID RNIC_IFACE_AdjustNapiWeight(VOS_UINT8 ucRmNetId)
{
    VOS_UINT8                           ucWeight;

    /* NAPI Weight??????????????????????weight??????????????????????????????default weight???? */
    if (NAPI_WEIGHT_ADJ_DYNAMIC_MODE == RNIC_GET_NAPI_WEIGHT_ADJ_MODE(ucRmNetId))
    {
        ucWeight = RNIC_IFACE_CalcNapiWeight(ucRmNetId);
        RNIC_IFACE_SetNapiWeight(ucRmNetId, ucWeight);
    }

    return;
}


VOS_VOID RNIC_IFACE_AdjNapiLbLevel(VOS_UINT8 ucRmNetId)
{
    VOS_UINT32                          ulLbLevel;
    VOS_UINT32                          ulDlNapiRecvPktNum;

    /* NAPI??????????????????????????????????CPU?????? */
    if (RNIC_FEATURE_ON == RNIC_GET_NAPI_LB_FEATURE(ucRmNetId))
    {
        ulDlNapiRecvPktNum = RNIC_GET_IFACE_PERIOD_RECV_PKT(ucRmNetId);

        for (ulLbLevel = 0; ulLbLevel < (RNIC_NVIM_NAPI_LB_MAX_LEVEL - 1); ulLbLevel++)
        {
            if ((ulDlNapiRecvPktNum >= RNIC_GET_NAPI_LB_LEVEL_PPS(ucRmNetId, ulLbLevel))
             && (ulDlNapiRecvPktNum < RNIC_GET_NAPI_LB_LEVEL_PPS(ucRmNetId, ulLbLevel+1UL)))
                break;
        }

        RNIC_IFACE_SetNapiLbLevel(ucRmNetId, (VOS_UINT8)ulLbLevel);
    }

    return;
}


VOS_VOID RNIC_IFACE_UpdateTotalPps(
    RNIC_DSFLOW_STATS_STRU             *pstDsFlowTotalStats
)
{
    VOS_UINT32                          ulLbLevel;
    VOS_UINT32                          ulPeriodPps;

    if (RNIC_FEATURE_ON == g_stRnicCtx.stCpuFreqCtrlCfg.ucEnable)
    {
        ulPeriodPps = pstDsFlowTotalStats->ulPeriodRecvPktNum;

        for (ulLbLevel = 0; ulLbLevel < (RNIC_NVIM_CPU_FREQ_CTRL_MAX_LEVEL - 1); ulLbLevel++)
        {
            if ((ulPeriodPps >= g_stRnicCtx.stCpuFreqCtrlCfg.astLevelCfg[ulLbLevel].ulPps)
             && (ulPeriodPps < g_stRnicCtx.stCpuFreqCtrlCfg.astLevelCfg[ulLbLevel+1UL].ulPps))
                break;
        }

        if ((ulLbLevel != g_stRnicCtx.stCpuFreqCtrlCfg.ucCurLevel)
         || g_stRnicCtx.stCpuFreqCtrlCfg.astLevelCfg[ulLbLevel].ulIsolationDisable)
        {
            rnic_set_dev_cpufreq_level((VOS_UINT8)ulLbLevel);
            g_stRnicCtx.stCpuFreqCtrlCfg.ucCurLevel = (VOS_UINT8)ulLbLevel;
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_DATA_SERVICE_NEW_PLATFORM)

VOS_VOID RNIC_IFACE_NapiSchedule(VOS_ULONG ulUsrData)
{
    rnic_rx_complete((VOS_UINT8)ulUsrData);
    return;
}


VOS_INT RNIC_IFACE_RegRxHandler(RNIC_IFACE_CTX_STRU *pstIfaceCtx)
{
    struct ads_iface_rx_handler_s       stRxHandler;

    TAF_MEM_SET_S(&stRxHandler, sizeof(stRxHandler),
                  0x00, sizeof(struct ads_iface_rx_handler_s));

    stRxHandler.user_data      = pstIfaceCtx->enRmNetId;
    stRxHandler.rx_func        = RNIC_DataRxProc;
    stRxHandler.rx_cmplt_func  = RNIC_IFACE_NapiSchedule;

    return ads_iface_register_rx_handler(pstIfaceCtx->enIfaceId, &stRxHandler);
}


VOS_VOID RNIC_IFACE_SetNetDevUp(
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx,
    VOS_UINT8                           ucIpFamily
)
{
    struct rnic_ps_iface_config_s       stPsIfaceCfg;

    TAF_MEM_SET_S(&stPsIfaceCfg, sizeof(stPsIfaceCfg),
                  0x00, sizeof(struct rnic_ps_iface_config_s));

    stPsIfaceCfg.devid               = pstIfaceCtx->enRmNetId;
    stPsIfaceCfg.ip_family           = ucIpFamily;

    stPsIfaceCfg.info.iface_id       = pstIfaceCtx->enIfaceId;
    stPsIfaceCfg.info.pdu_session_id = (RNIC_IPV4_ADDR == ucIpFamily) ?
                                       pstIfaceCtx->stPsIfaceInfo.ucIpv4ExRabId :
                                       pstIfaceCtx->stPsIfaceInfo.ucIpv6ExRabId;
    stPsIfaceCfg.info.fc_head        = RNIC_GET_FC_HEAD_BY_MODEMID(pstIfaceCtx->stPsIfaceInfo.enModemId);
    stPsIfaceCfg.info.modem_id       = (VOS_UINT8)pstIfaceCtx->stPsIfaceInfo.enModemId;

#if ((FEATURE_ON == FEATURE_IMS) && (FEATURE_ON == FEATURE_DELAY_MODEM_INIT))
    if (RNIC_PS_RAT_TYPE_IWLAN == pstIfaceCtx->stPsIfaceInfo.enRatType)
    {
        stPsIfaceCfg.data_tx_func = RNIC_VoWifiDataTxProc;
    }
    else
#endif
    {
        stPsIfaceCfg.data_tx_func = (RNIC_IPV4_ADDR == ucIpFamily) ?
                                    RNIC_V4DataTxProc : RNIC_V6DataTxProc;
    }

    rnic_set_dev_ps_iface_up(&stPsIfaceCfg);

    return;
}


VOS_VOID RNIC_IFACE_SetNetDevDown(
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx,
    VOS_UINT8                           ucIpFamily
)
{
    struct rnic_ps_iface_config_s       stPsIfaceCfg;

    TAF_MEM_SET_S(&stPsIfaceCfg, sizeof(stPsIfaceCfg),
                  0x00, sizeof(struct rnic_ps_iface_config_s));

    stPsIfaceCfg.devid               = pstIfaceCtx->enRmNetId;
    stPsIfaceCfg.ip_family           = ucIpFamily;
    stPsIfaceCfg.info.iface_id       = RNIC_INVALID_IFACE_ID;
    stPsIfaceCfg.info.pdu_session_id = RNIC_INVALID_PDU_SESSION_ID;
    stPsIfaceCfg.info.fc_head        = RNIC_INVALID_FC_HEAD;
    stPsIfaceCfg.info.modem_id       = MODEM_ID_BUTT;
    stPsIfaceCfg.data_tx_func        = VOS_NULL_PTR;

    rnic_set_dev_ps_iface_down(&stPsIfaceCfg);

    RNIC_IFACE_ResetNapiConfig(pstIfaceCtx->enRmNetId);

    return;
}
#else

VOS_VOID RNIC_IFACE_NapiSchedule(VOS_UINT32 ulUsrData)
{
    rnic_rx_complete((VOS_UINT8)ulUsrData);
    return;
}


VOS_INT RNIC_IFACE_RegRxHandler(
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx,
    VOS_UINT8                           ucIpFamilyMask
)
{
    VOS_UINT8                           ucExRabId = RNIC_RAB_ID_INVALID;

    if (RNIC_BIT8_IS_SET(ucIpFamilyMask, RNIC_IPV4_ADDR))
    {
        ucExRabId = pstIfaceCtx->stPsIfaceInfo.ucIpv4ExRabId;
    }

    if (RNIC_BIT8_IS_SET(ucIpFamilyMask, RNIC_IPV6_ADDR))
    {
        ucExRabId = pstIfaceCtx->stPsIfaceInfo.ucIpv6ExRabId;
    }

    if (RNIC_PS_RAT_TYPE_3GPP == pstIfaceCtx->stPsIfaceInfo.enRatType)
    {
        /* ??????????????????ADS?????????????????????????? */
        (VOS_VOID)ADS_DL_RegDlDataCallback(ucExRabId,
                                 RNIC_DataRxProc,
                                 pstIfaceCtx->enRmNetId);

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
        /* NAPI?????????????? */
        if (RNIC_FEATURE_ON == RNIC_GET_NAPI_FEATURE(pstIfaceCtx->enRmNetId))
        {
            /* ????????NAPI?????????????? */
            (VOS_VOID)ADS_DL_RegNapiCallback(ucExRabId,
                                   RNIC_IFACE_NapiSchedule,
                                   pstIfaceCtx->enRmNetId);
        }
#endif
    }

    return VOS_OK;
}


VOS_VOID RNIC_IFACE_SetNetDevUp(
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx,
    VOS_UINT8                           ucIpFamily
)
{
    struct rnic_ps_iface_config_s       stPsIfaceCfg;

    TAF_MEM_SET_S(&stPsIfaceCfg, sizeof(stPsIfaceCfg),
                  0x00, sizeof(struct rnic_ps_iface_config_s));

    stPsIfaceCfg.devid     = pstIfaceCtx->enRmNetId;
    stPsIfaceCfg.ip_family = ucIpFamily;

    /* ?????????????????????????? */
#if ((FEATURE_ON == FEATURE_IMS) && (FEATURE_ON == FEATURE_DELAY_MODEM_INIT))
    if (RNIC_PS_RAT_TYPE_IWLAN == pstIfaceCtx->stPsIfaceInfo.enRatType)
    {
        stPsIfaceCfg.data_tx_func = RNIC_VoWifiDataTxProc;
    }
    else
#endif
    {
        stPsIfaceCfg.data_tx_func = (RNIC_IPV4_ADDR == ucIpFamily) ?
                                    RNIC_V4DataTxProc : RNIC_V6DataTxProc;
    }

    if (0 != rnic_set_dev_ps_iface_up(&stPsIfaceCfg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_IFACE_SetDevUp: set rnic_set_ps_iface_up fail!");
    }

    return;
}


VOS_VOID RNIC_IFACE_SetNetDevDown(
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx,
    VOS_UINT8                           ucIpFamily
)
{
    struct rnic_ps_iface_config_s       stPsIfaceCfg;

    TAF_MEM_SET_S(&stPsIfaceCfg, sizeof(stPsIfaceCfg),
                  0x00, sizeof(struct rnic_ps_iface_config_s));

    stPsIfaceCfg.devid        = pstIfaceCtx->enRmNetId;
    stPsIfaceCfg.ip_family    = ucIpFamily;
    stPsIfaceCfg.data_tx_func = VOS_NULL_PTR;

    if (0 != rnic_set_dev_ps_iface_down(&stPsIfaceCfg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC,
            "RNIC_IFACE_SetDevDown: set rnic_set_ps_iface_down fail!");
    }

    RNIC_IFACE_ResetNapiConfig(pstIfaceCtx->enRmNetId);

    return;
}
#endif /* FEATURE_ON == FEATURE_DATA_SERVICE_NEW_PLATFORM */





VOS_VOID RNIC_IFACE_SetFeatureCfg(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0 ; ulIndex <= RNIC_3GPP_NET_ID_MAX_NUM ; ulIndex++)
    {
        /* ????NAPI???? */
        RNIC_IFACE_SetNapiCfg((VOS_UINT8)ulIndex);
        RNIC_IFACE_SetNapiLbCfg((VOS_UINT8)ulIndex);

#if (FEATURE_OFF == FEATURE_DELAY_MODEM_INIT)
        /* ???????????????????? */
        RNIC_IFACE_RegTxDropCB((VOS_UINT8)ulIndex);
#endif
    }

    RNIC_IFACE_SetCpuFreqCtrlCfg();
    return;
}

VOS_VOID RNIC_IFACE_SetDsFlowStats(
    VOS_UINT8                           ucRmNetId,
    RNIC_DSFLOW_STATS_STRU             *pstDsFlowTotalStats
)
{
    struct rnic_dsflow_stats_s         *pstDsflowStats = VOS_NULL_PTR;

    /* ???????????????????????? */
    pstDsflowStats = rnic_get_dsflow_stats(ucRmNetId);

    if (VOS_NULL_PTR == pstDsflowStats)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_IFACE_SetDsFlowStats fail, get dsflow stats failed !");
        return;
    }

    g_stRnicCtx.astIfaceCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate   = pstDsflowStats->rx_bytes;
    g_stRnicCtx.astIfaceCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate   = pstDsflowStats->tx_bytes;
    g_stRnicCtx.astIfaceCtx[ucRmNetId].stDsFlowStats.ulPeriodRecvPktNum  = pstDsflowStats->rx_packets;
    /* ???????????????????????????????????????? */
    g_stRnicCtx.astIfaceCtx[ucRmNetId].stDsFlowStats.ulPeriodSendPktNum += pstDsflowStats->tx_packets;

    pstDsFlowTotalStats->ulCurrentRecvRate  += pstDsflowStats->rx_bytes;
    pstDsFlowTotalStats->ulCurrentSendRate  += pstDsflowStats->tx_bytes;
    pstDsFlowTotalStats->ulPeriodRecvPktNum += pstDsflowStats->rx_packets;
    pstDsFlowTotalStats->ulPeriodSendPktNum += pstDsflowStats->tx_packets;

    RNIC_NORMAL_LOG4(ACPU_PID_RNIC, "RNIC_IFACE_SetDsFlowStats: <rx_bytes, tx_bytes, rx_packets, tx_packets> ",
                    pstDsflowStats->rx_bytes,
                    pstDsflowStats->tx_bytes,
                    pstDsflowStats->rx_packets,
                    pstDsflowStats->tx_packets);

    return;
}


VOS_VOID RNIC_IFACE_ClearDsFlowFlux(VOS_UINT8 ucRmNetId)
{
    rnic_clear_dsflow_stats(ucRmNetId);
    return;
}


VOS_VOID RNIC_IFACE_ClearDsFlowStats(VOS_UINT8 ucRmNetId)
{
    RNIC_IFACE_CTX_STRU                 *pstIfaceCtx = VOS_NULL_PTR;

    pstIfaceCtx = RNIC_GET_IFACE_CTX_ADR(ucRmNetId);

    pstIfaceCtx->stDsFlowStats.ulCurrentRecvRate   = 0;
    pstIfaceCtx->stDsFlowStats.ulPeriodRecvPktNum  = 0;

    pstIfaceCtx->stDsFlowStats.ulCurrentSendRate   = 0;
    pstIfaceCtx->stDsFlowStats.ulPeriodSendPktNum  = 0;

    return;
}


VOS_VOID RNIC_IFACE_NetdevNotify(VOS_VOID)
{
    RNIC_DEV_READY_STRU                *pstSndMsg;

    /* ???????? */
    pstSndMsg = (RNIC_DEV_READY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_RNIC, sizeof(RNIC_DEV_READY_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendNetdevReadyInd: Malloc failed!");
        return;
    }

    /* ???????? */
    RNIC_CFG_INTRA_MSG_HDR(pstSndMsg, ID_RNIC_NETDEV_READY_IND);

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendNetdevReadyInd: Send msg failed!");
    }

    return;
}


VOS_VOID RNIC_IFACE_RegDevNotifyCB(VOS_VOID)
{
    struct rnic_deivce_notifier_s       stDevNotifier;

    stDevNotifier.dev_notifier_func = RNIC_IFACE_NetdevNotify;

    rnic_register_device_notifier(&stDevNotifier);
    return;
}


VOS_VOID RNIC_IFACE_RegOnDemandOpsCB(VOS_VOID)
{
    struct rnic_ondemand_cb_ops_s       stOndemandOpsCB;

    stOndemandOpsCB.dial_mode_cfg_func    = RNIC_IFACE_OndemandDialModeProc;
    stOndemandOpsCB.idle_time_cfg_func    = RNIC_IFACE_OndemandIdleTimeProc;
    stOndemandOpsCB.event_report_cfg_func = RNIC_IFACE_OndemandEventReportProc;

    rnic_register_ondemand_ops(&stOndemandOpsCB);
    return;
}


VOS_VOID RNIC_IFACE_RegTxDropCB(VOS_UINT8 ucRmNetId)
{
    struct rnic_ps_iface_drop_notifier_s    stDropNotify;

    /* ????0???????????????????????? */
    if (ucRmNetId == RNIC_DEV_ID_RMNET0)
    {
        stDropNotify.devid              = ucRmNetId;
        stDropNotify.drop_notifier_func = RNIC_TxDropProc;

        rnic_register_ps_iface_drop_notifier(&stDropNotify);
    }

    return;
}


VOS_VOID RNIC_IFACE_ResetPsIface(VOS_UINT8 ucRmNetId)
{
    struct rnic_ps_iface_config_s       stPsIfaceCfg;

    stPsIfaceCfg.devid                  = ucRmNetId;
    stPsIfaceCfg.data_tx_func           = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_DATA_SERVICE_NEW_PLATFORM)
    stPsIfaceCfg.info.iface_id          = RNIC_INVALID_IFACE_ID;
    stPsIfaceCfg.info.pdu_session_id    = RNIC_INVALID_PDU_SESSION_ID;
    stPsIfaceCfg.info.fc_head           = RNIC_INVALID_FC_HEAD;
    stPsIfaceCfg.info.modem_id          = MODEM_ID_BUTT;
#endif

    /* Down V4 ???? */
    stPsIfaceCfg.ip_family    = RNIC_IPV4_ADDR;
    rnic_set_dev_ps_iface_down(&stPsIfaceCfg);

    /* Down V6 ???? */
    stPsIfaceCfg.ip_family    = RNIC_IPV6_ADDR;
    rnic_set_dev_ps_iface_down(&stPsIfaceCfg);

    RNIC_IFACE_ResetNapiConfig(ucRmNetId);
    return;
}


VOS_VOID RNIC_IFACE_PsIfaceUp(
    VOS_UINT8                           ucRmNetId,
    VOS_UINT8                           ucIpFamilyMask
)
{
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx    = VOS_NULL_PTR;
    RNIC_PS_IFACE_INFO_STRU            *pstPsIfaceInfo = VOS_NULL_PTR;

    pstIfaceCtx    = RNIC_GET_IFACE_CTX_ADR(ucRmNetId);
    pstPsIfaceInfo = RNIC_GET_IFACE_PDN_INFO_ADR(ucRmNetId);

    RNIC_NORMAL_LOG3(ACPU_PID_RNIC,
        "RNIC_IFACE_PsIfaceUp: <ucRmNetId, ucIpFamilyMask, ucRatType>",
        ucRmNetId, ucIpFamilyMask, pstPsIfaceInfo->enRatType);

    if (RNIC_BIT8_IS_SET(ucIpFamilyMask, RNIC_IPV4_ADDR))
    {
        RNIC_IFACE_SetNetDevUp(pstIfaceCtx, RNIC_IPV4_ADDR);

        /* ?????????????????????? */
        if (RNIC_DEV_ID_RMNET0 == ucRmNetId)
        {
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);
        }
    }

    if (RNIC_BIT8_IS_SET(ucIpFamilyMask, RNIC_IPV6_ADDR))
    {
        RNIC_IFACE_SetNetDevUp(pstIfaceCtx, RNIC_IPV6_ADDR);
    }

#if (FEATURE_ON == FEATURE_DATA_SERVICE_NEW_PLATFORM)
    RNIC_IFACE_RegRxHandler(pstIfaceCtx);
#else
    RNIC_IFACE_RegRxHandler(pstIfaceCtx, ucIpFamilyMask);
#endif

    if (ucRmNetId <= RNIC_3GPP_NET_ID_MAX_NUM)
    {
        RNIC_StartTimer(TI_RNIC_DSFLOW_STATS, TI_RNIC_DSFLOW_STATS_LEN);
    }

    RNIC_BIT32_SET(g_stRnicCtx.ulDsflowTimerMask, ucRmNetId);

    return;
}


VOS_VOID RNIC_IFACE_PsIfaceDown(
    VOS_UINT8                           ucRmNetId,
    VOS_UINT8                           ucIpFamilyMask
)
{
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx = VOS_NULL_PTR;

    pstIfaceCtx = RNIC_GET_IFACE_CTX_ADR(ucRmNetId);

    RNIC_NORMAL_LOG2(ACPU_PID_RNIC,
        "RNIC_IFACE_PsIfaceDown: <ucRmNetId, ucIpFamilyMask>",
        ucRmNetId, ucIpFamilyMask);

    if (RNIC_BIT8_IS_SET(ucIpFamilyMask, RNIC_IPV4_ADDR))
    {
        RNIC_IFACE_SetNetDevDown(pstIfaceCtx, RNIC_IPV4_ADDR);

        /* RMNET0??IPV4????????????????????, ????down?????????????????????? */
        if (RNIC_DEV_ID_RMNET0 == ucRmNetId)
        {
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
            RNIC_CLEAR_TI_DIALDOWN_EXP_CONT();
        }
    }

    if (RNIC_BIT8_IS_SET(ucIpFamilyMask, RNIC_IPV6_ADDR))
    {
        RNIC_IFACE_SetNetDevDown(pstIfaceCtx, RNIC_IPV6_ADDR);
    }

    if ((RNIC_BIT_OPT_FALSE == RNIC_GET_IFACE_PDN_IPV4_ACT_STATE(ucRmNetId))
     && (RNIC_BIT_OPT_FALSE == RNIC_GET_IFACE_PDN_IPV6_ACT_STATE(ucRmNetId)))
    {
        RNIC_BIT32_CLR(g_stRnicCtx.ulDsflowTimerMask, ucRmNetId);

        /* ??????????????down?????????????????????????????????????? */
        if (!(g_stRnicCtx.ulDsflowTimerMask & RNIC_3GPP_NET_MAX_NUM_MASK))
        {
            RNIC_StopTimer(TI_RNIC_DSFLOW_STATS);
            RNIC_IFACE_ClearDsFlowStats(ucRmNetId);
            RNIC_IFACE_ResetCpufreqLevel();
        }
    }

    return;
}


VOS_VOID RNIC_IFACE_TetherInfo(
    RNIC_PS_IFACE_TETHER_INFO_STRU     *pstTetherInfo
)
{
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    RNIC_DEV_ID_ENUM_UINT8              enRmNetId;

    if(VOS_NULL_PTR == pstTetherInfo)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_IFACE_TetherInfo fail, pstTetherInfo is NULL!");
        return;
    }

    if (VOS_OK != rnic_get_devid_by_name((char *)pstTetherInfo->aucRmnetName, &enRmNetId))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_IFACE_TetherInfo fail, no such RmnetName!");
        return;
    }

    if (enRmNetId >= RNIC_DEV_ID_BUTT)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_IFACE_TetherInfo fail, invalid enRmNetId ", enRmNetId);
        return;
    }

    /* ??????????????GRO???? */
    if (AT_RNIC_USB_TETHER_CONNECTED == pstTetherInfo->enTetherConnStat)
    {
        /* ????????????????GRO???? */
        RNIC_SET_TETHER_ORIG_GRO_FEATURE(RNIC_GET_GRO_FEATURE(enRmNetId));

        RNIC_SET_GRO_FEATURE(enRmNetId, RNIC_FEATURE_OFF);
    }
    else if (AT_RNIC_USB_TETHER_DISCONNECT == pstTetherInfo->enTetherConnStat)
    {
        /* ??????????????GRO???? */
        RNIC_SET_GRO_FEATURE(enRmNetId, RNIC_GET_TETHER_ORIG_GRO_FEATURE());

        /* ??????Tethering???????????????????????? */
        RNIC_InitTetherInfo();
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_IFACE_TetherInfo fail, enTetherConnStat invalid!");
        return;
    }

    RNIC_IFACE_SetNapiCfg(enRmNetId);
#else
    (VOS_VOID)pstTetherInfo;
#endif

    return;
}


VOS_INT RNIC_BST_GetModemInfo(
    const char                         *pNetDevName,
    BST_RNIC_MODEM_INFO_STRU           *pstModemInfo
)
{
    RNIC_IFACE_CTX_STRU                *pstIfaceCtx = VOS_NULL_PTR;
    RNIC_DEV_ID_ENUM_UINT8              enRmNetId;

    if (VOS_NULL_PTR == pNetDevName)
    {
        return VOS_ERROR;
    }

    if (VOS_NULL_PTR == pstModemInfo)
    {
        return VOS_ERROR;
    }

    if (VOS_OK != rnic_get_devid_by_name(pNetDevName, &enRmNetId))
    {
         RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_BST_GetModemInfo fail, no such RmnetName!");
        return VOS_ERROR;
    }

    if (enRmNetId >= RNIC_DEV_ID_BUTT)
    {
        return VOS_NULL_PTR;
    }

    pstIfaceCtx = RNIC_GET_IFACE_CTX_ADR(enRmNetId);

    pstModemInfo->enIPv4State = (RNIC_BIT_OPT_FALSE == pstIfaceCtx->stPsIfaceInfo.bitOpIpv4Act) ?
                                BST_RNIC_PDP_STATE_INACTIVE : BST_RNIC_PDP_STATE_ACTIVE;
    pstModemInfo->usModemId   = pstIfaceCtx->stPsIfaceInfo.enModemId;
    pstModemInfo->ucRabId     = pstIfaceCtx->stPsIfaceInfo.ucIpv4RabId;

    return VOS_OK;
}



