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

#ifndef __ATCMDMISCPROC_H__
#define __ATCMDMISCPROC_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "AtMtaInterface.h"
#include "at_lte_common.h"

#include "mdrv.h"
#include "CssAtInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define AT_SECURE_STATE_NOT_SET                     0                         /* Secure State?????????? */
#define AT_SECURE_STATE_SECURE                      1                         /* ????Secure State??Secure */
#define AT_SECURE_STATE_RMA                         2                         /* ????Secure State??RMA */

#define AT_EFUSE_OK                                 0                         /* efuse???????? */
#define AT_EFUSE_REPEAT                             1                         /* efuse???????????? */

#define AT_DRV_SOCID_LEN                            32                        /* 256Bits??SOCID???????? */

#define AT_MODEM_YTD_LEN                            10                        /* ???????????????????? */
#define AT_MODEM_TIME_LEN                           8                         /* ???????????????????????????? */
#define AT_MODEM_YEAR_LEN                           4                         /* ???????????????? */
#define AT_MODEM_MONTH_LEN                          2                         /* ???????????????? */
#define AT_MODEM_DATE_LEN                           2                         /* ???????????????? */
#define AT_MODEM_HOUR_LEN                           2                         /* ???????????????? */
#define AT_MODEM_MIN_LEN                            2                         /* ???????????????? */
#define AT_MODEM_SEC_LEN                            2                         /* ?????????????? */
#define AT_MODEM_ZONE_LEN                           3                         /* ???????????????? */
#define AT_GET_MODEM_TIME_BUFF_LEN                  5

#define AT_MODEM_DEFALUT_AUX_MODE_YEAR_LEN          2                         /* "yy"?????? */
#define AT_MODEM_OTHER_AUX_MODE_YEAR_LEN            4                         /* "yyyy"?????? */
#define AT_MODEM_AUX_MODE_EXCEPT_YEAR_TIME_LEN      18                        /* "/mm/dd,hh:mm:ss+/-zz"?????? */

#define AT_MODEM_DEFALUT_AUX_MODE_YEAR_MAX          99                        /* "yy"?????????????? */
#define AT_MODEM_DEFALUT_AUX_MODE_YEAR_MIN          0                         /* "yy"?????????????? */

#define AT_MODEM_TIME_ZONE_MAX                      48                        /* ???????????????? */
#define AT_MODEM_TIME_ZONE_MIN                      (-48)                       /* ???????????????? */

#define AT_MODEM_YEAR_MAX                           2050                      /* ?????????????? */
#define AT_MODEM_YEAR_MIN                           1970                      /* ?????????????? */
#define AT_MODEM_MONTH_MAX                          12                        /* ?????????????? */
#define AT_MODEM_MONTH_MIN                          1                         /* ?????????????? */
#define AT_MODEM_DAY_MAX                            31                        /* ?????????????? */
#define AT_MODEM_DAY_MIN                            1                         /* ?????????????? */

#define AT_MODEM_HOUR_MAX                           23                        /* ???????????????? */
#define AT_MODEM_HOUR_MIN                           0                         /* ???????????????? */
#define AT_MODEM_MIN_MAX                            59                        /* ???????????????? */
#define AT_MODEM_MIN_MIN                            0                         /* ???????????????? */
#define AT_MODEM_SEC_MAX                            59                        /* ???????????????? */
#define AT_MODEM_SEC_MIN                            0                         /* ???????????????? */

#define AT_MODEM_ZONE_MAX                           12                        /* ???????????????? */
#define AT_MODEM_ZONE_MIN                           (-12)                       /* ???????????????? */

#define AT_TEMP_ZONE_DEFAULT                        31                        /* ?????????? ??????11111 */

#define AT_GMT_TIME_DEFAULT                         70                        /* ??????????????1900????1970 */

#define AT_SIM_LOCK_DATA_WRITEEX_MAX_TOTAL          42                        /* ??total??????????????????42??????????OSA????60k */


#define AT_FINE_TIME_DEFAULT_NUM                    2

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
#define AT_NRPWRCTRL_MAX_DELETE_CA_NUM                     (-8)
#define AT_NRPWRCTRL_MAX_ADD_CA_NUM                        8

#define AT_NRPWRCTRL_DISABLE_REDUCE_RI                     0
#define AT_NRPWRCTRL_ENABLE_REDUCE_RI                      1

#define AT_NRPWRCTRL_MIN_SUPPORT_BSR_NUM                   0
#define AT_NRPWRCTRL_MAX_SUPPORT_BSR_NUM                   63
#endif

/*****************************************************************************
  3 ????????
*****************************************************************************/
#if (FEATURE_UE_MODE_NR == FEATURE_ON)
enum AT_NRPWRCTRL_MODE_TYPE_ENUM
{
    AT_NRPWRCTRL_MODE_CC_NUM_CTR      = 0,
    AT_NRPWRCTRL_MODE_RI_NUM_CTR      = 1,
    AT_NRPWRCTRL_MODE_BSR_NUM_CTR     = 2,
    AT_NRPWRCTRL_MODE_BUTT            = 3,
};
typedef  VOS_UINT32  AT_NRPWRCTRL_MODE_TYPE_ENUM_UINT32;

#endif

/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/

VOS_UINT32 AT_SetActiveModem(VOS_UINT8 ucIndex);

#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
VOS_UINT32 AT_SetMBMSServiceOptPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetMBMSServiceStatePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetMBMSPreferencePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryMBMSSib16NetworkTimePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryMBMSBssiSignalLevelPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryMBMSNetworkInfoPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryMBMSModemStatusPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetMBMSCMDPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetMBMSEVPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetMBMSInterestListPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryMBMSCmdPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaMBMSServiceOptSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSServiceStateSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSPreferenceSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSSib16NetworkTimeQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSBssiSignalLevelQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSNetworkInfoQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSModemStatusQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSEVSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSServiceEventInd(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaMBMSInterestListSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaMBMSCmdQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID AT_ReportMBMSCmdQryCnf(
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU      *pstLrrcCnf,
    VOS_UINT8                                       ucIndex
);
VOS_UINT32 At_TestMBMSCMDPara(VOS_UINT8 ucIndex);
#endif
VOS_UINT32 AT_RcvMtaLteLowPowerSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_SetLteLowPowerPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_CheckIsmCoexParaValue(VOS_INT32 ulVal, VOS_UINT32 ulParaNum);
VOS_UINT32 AT_SetIsmCoexPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryIsmCoexPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaIsmCoexSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvL4AIsmCoexSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaIsmCoexQryCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_SetLL2ComCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetLL2ComQryPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaLL2ComCfgSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaLL2ComCfgQryCnf(
    VOS_VOID                           *pMsg
);
#if (FEATURE_UE_MODE_NR == FEATURE_ON)
VOS_UINT32 AT_SetNL2ComCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaNL2ComCfgSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_SetNL2ComQryPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaNL2ComCfgQryCnf(
    VOS_VOID                           *pMsg
);
#endif

VOS_UINT32 AT_SetLCaCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaLteCaCfgSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_QryLCaCellExPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaLteCaCellExQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaLteCaCellExInfoNtf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_SetLcaCellRptCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryLcaCellRptCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaCACellSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaCACellQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_SetFineTimeReqPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_RcvMtaFineTimeSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaSibFineTimeNtf(
    VOS_VOID                           *pstMsg
);
VOS_UINT32 AT_RcvMtaLppFineTimeNtf(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvMtaEpsNetworkInfoInd(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaEpsNetworkQryCnf(
    VOS_VOID                           *pMsg
);
#endif

VOS_UINT32 AT_SetLogEnablePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryLogEnable(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetActPdpStubPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetNVCHKPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_RcvDrvAgentSimlockWriteExSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSimlockDataReadExReadCnf(VOS_VOID *pMsg);
#if (FEATURE_PHONE_SC == FEATURE_ON)
VOS_UINT32 AT_SimLockDataReadExPara(VOS_UINT8 ucIndex);
#endif
VOS_UINT32 AT_SaveSimlockDataIntoCtx(
    AT_SIMLOCK_WRITE_EX_PARA_STRU *pstSimlockWriteExPara,
    VOS_UINT8                      ucIndex,
    VOS_UINT8                      ucNetWorkFlg);
VOS_UINT32 AT_SetSimlockDataWriteExPara(
    AT_SIMLOCK_WRITE_EX_PARA_STRU *pstSimlockWriteExPara,
    VOS_UINT8                      ucIndex,
    AT_SIMLOCK_TYPE_ENUM_UINT8     ucNetWorkFlg
);
VOS_UINT32  AT_ProcSimlockWriteExData(
    VOS_UINT8                          *pucSimLockData,
    VOS_UINT16                          usParaLen
);


VOS_UINT32 AT_RcvMtaAfcClkInfoCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_SetPhyComCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaPhyComCfgSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_SetSamplePara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSetSampleCnf(VOS_VOID *pMsg);


#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
extern VOS_UINT32 AT_SetEvdoSysEvent(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetDoSigMask(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_RcvMtaEvdoSysEventSetCnf(
    VOS_VOID                           *pMsg
);

extern VOS_UINT32 AT_RcvMtaEvdoSigMaskSetCnf(
    VOS_VOID                           *pMsg
);

extern VOS_UINT32 AT_RcvMtaEvdoRevARLinkInfoInd(
    VOS_VOID                           *pMsg
);

extern VOS_UINT32 AT_RcvMtaEvdoSigExEventInd(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaNoCardModeSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaNoCardModeQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_SetCdmaModemCapPara(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstSourceModemPlatform,
    PLATAFORM_RAT_CAPABILITY_STRU      *pstDestinationModemPlatform,
    MODEM_ID_ENUM_UINT16                enSourceModemId,
    MODEM_ID_ENUM_UINT16                enDestinationModemId,
    VOS_UINT8                           ucIndex
);
VOS_UINT32 At_SetCdmaCapResume(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryFactoryCdmaCap(VOS_UINT8 ucIndex);

#endif

VOS_VOID AT_ReadPlatFormPrint(
    MODEM_ID_ENUM_UINT16                enModemId,
    PLATAFORM_RAT_CAPABILITY_STRU       stPlatRat
);

VOS_UINT32 AT_SetFratIgnitionPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetModemTimePara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetRxTestModePara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_RcvMtaSetRxTestModeCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_SetMipiWrParaEx(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaMipiWrEXCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_SetMipiRdParaEx(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaMipiRdEXCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_QryLineIndexListPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_CheckLineIndexListBsPara(VOS_VOID);
VOS_UINT32 AT_CheckLineIndexListPara(VOS_VOID);
VOS_UINT32 AT_CheckLineDetailBsPara(VOS_VOID);
VOS_UINT32 AT_CheckLineDetailPara(VOS_VOID);
VOS_UINT32 AT_SetLineIndexListPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_SetLineDetailPara(
    VOS_UINT8                           ucIndex
);

#if (FEATURE_DSDS == FEATURE_ON)
VOS_UINT32 AT_RcvMmaDsdsStateSetCnf(
    VOS_VOID                           *pstMsg
);
VOS_UINT32 AT_RcvMmaDsdsStateNotify(
    VOS_VOID                           *pstMsg
);
#endif

extern VOS_UINT32 AT_SetCrrconnPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryCrrconnPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_RcvMtaSetCrrconnCnf(
    VOS_VOID                        *pMsg
);

extern VOS_UINT32 AT_RcvMtaQryCrrconnCnf(
    VOS_VOID                        *pMsg
);

extern VOS_UINT32 AT_RcvMtaCrrconnStatusInd(
    VOS_VOID                           *pMsg
);

extern VOS_UINT32 AT_SetVtrlqualrptPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_RcvMtaSetVtrlqualrptCnf(
    VOS_VOID                        *pMsg
);

extern VOS_UINT32 AT_RcvMtaRlQualityInfoInd(
    VOS_VOID                           *pMsg
);

extern VOS_UINT32 AT_RcvMtaVideoDiagInfoRpt(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_SetEccCfgPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetSmsDomainPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSmsDomainSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_QrySmsDomainPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSmsDomainQryCnf(
    VOS_VOID                        *pMsg
);

VOS_UINT32 AT_SetCenfsPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryCenfsPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetWs46Para(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryWs46Para(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestWs46Para( VOS_UINT8 ucIndex );

VOS_UINT32 AT_SetGameModePara(
    VOS_UINT8                           ucIndex
);

VOS_UINT32 AT_SetGpsLocSetPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaGpsLocSetCnf(VOS_VOID *pMsg);


VOS_UINT32 AT_SetVzwMruC(VOS_UINT8 ucIndex);
VOS_UINT32 AT_CheckVzwMruEPara(VOS_VOID);
VOS_UINT32 AT_SetVzwMruE(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryVzwMruE(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestVzwMruE(VOS_UINT8 ucIndex);
VOS_UINT32 AT_ConvertDecFormatPlmnId2HexFormat(
    CSS_AT_PLMN_ID_STRU                *pstPlmnId,
    VOS_UINT32                          ulPlmnId
);

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
VOS_UINT32 AT_SetLendcPara(VOS_UINT8 ucIndex);

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)
VOS_UINT32 At_SetNrFreqLockPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_GetNrFreqLockPara(
    VOS_UINT8                           ucClientId,
    AT_MTA_SET_NRFREQLOCK_REQ_STRU     *pstNrFreqLockInfo
);
#endif

#endif

extern VOS_VOID AT_PrintCclkTime(
    VOS_UINT8                           ucIndex,
    TIME_ZONE_TIME_STRU                *pstTimeZoneTime,
    MODEM_ID_ENUM_UINT16                enModemId
);
VOS_UINT32 AT_RcvMtaCclkQryCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaTempProtectInd(VOS_VOID *pMsg);

VOS_UINT32 AT_SetNvRefreshPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaNvRefreshSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_SetPseudBtsPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetSubClfsParamPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QrySubClfsParamPara(VOS_UINT8 ucIndex);

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
VOS_UINT32 AT_SetClDbDomainStatusPara(VOS_UINT8 ucIndex);
#endif

VOS_UINT32 AT_SetUlFreqRptPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryUlFreqPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMmaUlFreqRptSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMmaUlFreqChangeInd(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMmaUlFreqRptQryCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaPseudBtsIdentInd(VOS_VOID *pMsg);

VOS_UINT32 At_SetPsScenePara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_QryPsScenePara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_RcvMmaPsSceneSetCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMmaPsSceneQryCnf(VOS_VOID *pstMsg);

VOS_UINT32 AT_SetForceSyncPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaForceSyncSetCnf (VOS_VOID *pMsg);

VOS_UINT32 At_SetGnssNtyPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetLowPowerModePara(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetCcpuNidDisablePara(VOS_UINT8 ucIndex);
VOS_UINT32 At_SetAcpuNidDisablePara(VOS_UINT8 ucIndex);

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
VOS_UINT32 AT_SetNrrcCapCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetNrrcCapQryPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetNrPwrCtrlPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestNrPwrCtrlPara(VOS_UINT8 ucIndex);
#endif

VOS_UINT32 AT_RcvMtaTxPowerQryCnf(
    VOS_VOID                           *pstMsg
);

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
VOS_UINT32 AT_RcvMtaNtxPowerQryCnf(
    VOS_VOID                           *pstMsg
);
#endif

VOS_UINT32 AT_RcvMtaMcsSetCnf(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvMtaHfreqinfoQryCnf(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvMtaHfreqinfoInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvMmaRrcStatQryCnf(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvMmaRrcStatInd(
    VOS_VOID                           *pstMsg
);
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
VOS_UINT32 AT_RcvMta5gOptionSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMta5gOptionQryCnf(
    VOS_VOID                           *pMsg
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtCmdMiscProc.h */
