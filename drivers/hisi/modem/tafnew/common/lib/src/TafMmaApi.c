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
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "TafApi.h"

#include "MnCommApi.h"
#include "TafAppMma.h"

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "NasMultiInstanceApi.h"
#endif
#include "securec.h"



/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/

#define    THIS_FILE_ID PS_FILE_ID_TAF_MMA_API_C

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define TAF_GET_DEST_PID(usClientId, ulPid)  AT_GetDestPid(usClientId, ulPid)
#else
#define TAF_GET_DEST_PID(usClientId, ulPid)  NAS_MULTIINSTANCE_GetSpecModemPid(NAS_MULTIINSTANCE_GetCurrInstanceModemId(ulPid), ulPid)
#endif

/*****************************************************************************
   2 ????????????
*****************************************************************************/
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    extern VOS_UINT32 AT_GetDestPid(
        MN_CLIENT_ID_T                      usClientId,
        VOS_UINT32                          ulRcvPid
    );
#endif

/*****************************************************************************
   3 ????????
*****************************************************************************/




TAF_UINT32 Taf_PhonePinHandle ( MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                TAF_PH_PIN_DATA_STRU   *pPinData)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_OP_PIN_REQ,
                                   pPinData,
                                   sizeof(TAF_PH_PIN_DATA_STRU),
                                   I0_WUEPS_PID_MMA);
}



VOS_UINT32 Taf_MePersonalisationHandle(MN_CLIENT_ID_T          ClientId,
                                       MN_OPERATION_ID_T                 OpId,
                                       TAF_ME_PERSONALISATION_DATA_STRU *pMePersonalData)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_ME_PERSONAL_REQ,
                                   pMePersonalData,
                                   sizeof(TAF_ME_PERSONALISATION_DATA_STRU),
                                   I0_WUEPS_PID_MMA);
}


/* Taf_PhoneAttach */


TAF_UINT32 Taf_PhonePlmnList (
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_PLMN_LIST_PARA_STRU            *pstPlmnListPara
)
{
    TAF_MMA_PLMN_LIST_REQ_STRU         *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstPlmnListPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_DETACH_REQ_STRU */
    pstMsg = (TAF_MMA_PLMN_LIST_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_PLMN_LIST_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_PLMN_LIST_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_PLMN_LIST_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stPlmnListPara), sizeof(pstMsg->stPlmnListPara), pstPlmnListPara, sizeof(TAF_MMA_PLMN_LIST_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPlmnListPara), sizeof(TAF_MMA_PLMN_LIST_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_AbortPlmnListReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_PLMN_LIST_ABORT_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PLMN_LIST_ABORT_REQ_STRU */
    pstMsg = (TAF_MMA_PLMN_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_PLMN_LIST_ABORT_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_PLMN_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PLMN_LIST_ABORT_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryLocInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_LOCATION_INFO_QRY_REQ_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MMA_LOCINFO_QRY_REQ */
    pstMsg = (TAF_MMA_LOCATION_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                   ulSenderPid,
                                                   sizeof(TAF_MMA_LOCATION_INFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_LOCATION_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_LOCATION_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_LOCATION_INFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_QryCipherReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CIPHER_QRY_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MMA_LOCINFO_QRY_REQ */
    pstMsg = (TAF_MMA_CIPHER_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_CIPHER_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CIPHER_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CIPHER_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CIPHER_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_SetPrefPlmnTypeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8       *penPrefPlmnType
)
{
    TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU */
    pstMsg = (TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                    ulSenderPid,
                                                    sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PREF_PLMN_TYPE_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->enPrefPlmnType              = *penPrefPlmnType;
    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#if (FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)

VOS_UINT32 TAF_MMA_MtPowerDownReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_MT_POWER_DOWN_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_MT_POWER_DOWN_REQ_STRU */
    pstMsg = (TAF_MMA_MT_POWER_DOWN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_MT_POWER_DOWN_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_MT_POWER_DOWN_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_MT_POWER_DOWN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_MT_POWER_DOWN_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#endif



VOS_UINT32 TAF_MMA_SetQuickStartReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSetValue
)
{
    TAF_MMA_QUICKSTART_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_QUICKSTART_SET_REQ_STRU */
    pstMsg = (TAF_MMA_QUICKSTART_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              ulSenderPid,
                                              sizeof(TAF_MMA_QUICKSTART_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_QUICKSTART_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_QUICKSTART_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_QUICKSTART_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->ulQuickStartMode            = ulSetValue;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryQuickStartReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_QUICKSTART_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_QUICKSTART_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_QUICKSTART_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_QUICKSTART_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_QUICKSTART_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_QUICKSTART_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_QUICKSTART_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}


/* ????Taf_UsimRestrictedAccessCommand?????????????? */



VOS_UINT32 TAF_MMA_QrySyscfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_SYSCFG_QRY_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_SYSCFG_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_SYSCFG_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_SYSCFG_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
       return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SYSCFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SYSCFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_SYSCFG_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 Taf_SetCopsFormatTypeReq(
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU                  *pstCopsFormatType
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_COPS_FORMAT_TYPE_SET_REQ,
                                  pstCopsFormatType,
                                  sizeof(TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}

#if (FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)

VOS_UINT32 TAF_SetUsimStub(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_USIM_STUB_SET_REQ_STRU     *pstUsimStub
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_USIM_STUB_SET_REQ,
                                  pstUsimStub,
                                  sizeof(TAF_MMA_USIM_STUB_SET_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}



VOS_UINT32 TAF_SetRefreshStub(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_REFRESH_STUB_SET_REQ_STRU  *pstRefreshStub
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_REFRESH_STUB_SET_REQ,
                                  pstRefreshStub,
                                  sizeof(TAF_MMA_REFRESH_STUB_SET_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}
#endif


VOS_UINT32 TAF_SetAutoReselStub(
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU                    *pstAutoReselStub
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_AUTO_RESEL_STUB_SET_REQ,
                                  pstAutoReselStub,
                                  sizeof(TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}



TAF_UINT32 TAF_QryUsimInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    if ( (TAF_PH_ICC_UNKNOW == pstInfo->Icctype)
      || (pstInfo->Icctype > TAF_PH_ICC_USIM))
    {
        return TAF_FAILURE;
    }

    if (pstInfo->enEfId > TAF_PH_OPL_FILE)
    {
        return TAF_FAILURE;
    }
    return MN_FillAndSndAppReqMsg( ClientId,
                             OpId,
                             TAF_MSG_MMA_USIM_INFO,
                             pstInfo,
                             sizeof(TAF_PH_QRY_USIM_INFO_STRU),
                             I0_WUEPS_PID_MMA);

}


TAF_UINT32 TAF_QryCpnnInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_ICC_TYPE                     IccType
)
{
    if ( (TAF_PH_ICC_UNKNOW == IccType)
      || (IccType > TAF_PH_ICC_USIM))
    {
        return TAF_FAILURE;
    }

    return MN_FillAndSndAppReqMsg( ClientId,
                             OpId,
                             TAF_MSG_MMA_CPNN_INFO,
                             &IccType,
                             sizeof(IccType),
                             I0_WUEPS_PID_MMA);
}



VOS_UINT32 TAF_MMA_PhoneModeSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PHONE_MODE_PARA_STRU       *pstPhoneModePara
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstPhoneModePara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_PHONE_MODE_SET_REQ_STRU */
    pstMsg = (TAF_MMA_PHONE_MODE_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_PHONE_MODE_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PHONE_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PHONE_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PHONE_MODE_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stPhoneModePara), sizeof(pstMsg->stPhoneModePara), pstPhoneModePara, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPhoneModePara), sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_QryPhoneModeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_PHONE_MODE_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PHONE_MODE_SET_REQ_STRU */
    pstMsg = (TAF_MMA_PHONE_MODE_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_PHONE_MODE_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PHONE_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PHONE_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PHONE_MODE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CSG)

VOS_UINT32 TAF_MMA_CsgListSearchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PLMN_LIST_PARA_STRU        *pstPlmnListPara
)
{
    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU   *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstPlmnListPara)
    {
        return VOS_FALSE;
    }

    /* ?????????? */
    pstMsg = (TAF_MMA_CSG_LIST_SEARCH_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_CSG_LIST_SEARCH_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_CSG_LIST_SEARCH_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    lMemResult = memcpy_s(&pstMsg->stPlmnListPara, sizeof(pstMsg->stPlmnListPara), pstPlmnListPara, sizeof(TAF_MMA_PLMN_LIST_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPlmnListPara), sizeof(TAF_MMA_PLMN_LIST_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_AbortCsgListSearchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CSG_LIST_ABORT_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_CSG_LIST_ABORT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_CSG_LIST_ABORT_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CSG_LIST_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->enMsgName                   = ID_TAF_MMA_CSG_LIST_ABORT_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetCsgIdSearch(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CSG_SPEC_SEARCH_INFO_STRU  *pstUserSelCsgId
)
{
    TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU   *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstUserSelCsgId)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU */
    pstMsg = (TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_CSG_SPEC_SEARCH_REQ_STRU, ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_CSG_SPEC_SEARCH_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    lMemResult = memcpy_s(&pstMsg->stCsgSpecSearchInfo, sizeof(pstMsg->stCsgSpecSearchInfo), pstUserSelCsgId, sizeof(pstMsg->stCsgSpecSearchInfo));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCsgSpecSearchInfo), sizeof(pstMsg->stCsgSpecSearchInfo));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCampCsgIdInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                    ulReceiverPid;
    VOS_UINT32                                    ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU */
    pstMsg = (TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_QRY_CAMP_CSG_ID_INFO_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


#endif

VOS_UINT32 TAF_MMA_SetSysCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstSysCfgPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_SYS_CFG_REQ_STRU */
    pstMsg = (TAF_MMA_SYS_CFG_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_SYS_CFG_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_SYS_CFG_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_SYS_CFG_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    lMemResult = memcpy_s(&(pstMsg->stSysCfgPara), sizeof(pstMsg->stSysCfgPara), pstSysCfgPara, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stSysCfgPara), sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryEonsUcs2Req(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_EONS_UCS2_REQ_STRU         *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_EONS_UCS2_REQ_STRU */
    pstMsg = (TAF_MMA_EONS_UCS2_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_EONS_UCS2_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_EONS_UCS2_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_EONS_UCS2_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_EONS_UCS2_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MSG_MMA_EONS_UCS2_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_DetachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_DETACH_PARA_STRU           *pstDetachPara
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstDetachPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_DETACH_REQ_STRU */
    pstMsg = (TAF_MMA_DETACH_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_DETACH_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_DETACH_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_DETACH_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stDetachPara), sizeof(pstMsg->stDetachPara), pstDetachPara, sizeof(TAF_MMA_DETACH_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stDetachPara), sizeof(TAF_MMA_DETACH_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 TAF_MMA_SetImsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_IMS_SWITCH_INFO_STRU       *pstImsSwitchInfo
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstImsSwitchInfo)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_IMS_SWITCH_SET_REQ_STRU */
    pstMsg = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_IMS_SWITCH_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SWITCH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SWITCH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_IMS_SWITCH_SET_REQ_STRU */
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_IMS_SWITCH_SET_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;
    pstMsg->stImsSwitchInfo     = *pstImsSwitchInfo;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryImsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_IMS_SWITCH_QRY_REQ_STRU    *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_IMS_SWITCH_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_IMS_SWITCH_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_IMS_SWITCH_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SWITCH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SWITCH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_IMS_SWITCH_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_SWITCH_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryRcsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_RCS_SWITCH_QRY_REQ_STRU    *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_IMS_SWITCH_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_RCS_SWITCH_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_RCS_SWITCH_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_RCS_SWITCH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_RCS_SWITCH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_RCS_SWITCH_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_RCS_SWITCH_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetVoiceDomainReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU  *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (enVoiceDomain >= TAF_MMA_VOICE_DOMAIN_BUTT)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU */
    pstMsg = (TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_VOICE_DOMAIN_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enVoiceDomain     = enVoiceDomain;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryVoiceDomainReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU  *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_VOICE_DOMAIN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetRoamImsSupportReq(
    VOS_UINT32                           ulModuleId,
    VOS_UINT16                           usClientId,
    VOS_UINT8                            ucOpId,
    TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32 enRoamImsSupport
)
{
    TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU  *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulSenderPid;
    errno_t                                 lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (TAF_MMA_ROAM_IMS_BUTT <= enRoamImsSupport)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU */
    pstMsg = (TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_ROAM_IMS_SUPPORT_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->enRoamingImsSupportFlag), sizeof(pstMsg->enRoamingImsSupportFlag), &enRoamImsSupport, sizeof(TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->enRoamingImsSupportFlag), sizeof(TAF_MMA_ROAM_IMS_SUPPORT_ENUM_UINT32));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetImsDomainCfgReq(
    VOS_UINT32                                   ulModuleId,
    VOS_UINT16                                   usClientId,
    VOS_UINT8                                    ucOpId,
    TAF_MMA_IMS_DOMAIN_CFG_TYPE_ENUM_UINT32      enImsDomainCfg
)
{
    TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                               ulReceiverPid;
    VOS_UINT32                               ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    if (enImsDomainCfg >= TAF_MMA_IMS_DOMAIN_CFG_TYPE_BUTT)
    {
        return VOS_FALSE;
    }

    /* ???????? */
    pstMsg = (TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
          0x00,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_IMS_DOMAIN_CFG_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_DOMAIN_CFG_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enImsDoaminCfg    = enImsDomainCfg;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryImsDomainCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU      *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                                ulReceiverPid;
    VOS_UINT32                                ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ????????*/
    pstMsg = (TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
          0x00,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

     /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetImsVtCapCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_IMS_VIDEO_CALL_CAP_STRU    *pstImsVtCap
)
{
    TAF_MMA_IMS_VIDEO_CALL_CAP_REQ_STRU                    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;
    errno_t                                                 lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    pstMsg = (TAF_MMA_IMS_VIDEO_CALL_CAP_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_IMS_VIDEO_CALL_CAP_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_VIDEO_CALL_CAP_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
          0x00,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_VIDEO_CALL_CAP_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_VIDEO_CALL_CAP_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    lMemResult = memcpy_s(&pstMsg->stImsVtCap, sizeof(pstMsg->stImsVtCap), pstImsVtCap, sizeof(TAF_MMA_IMS_VIDEO_CALL_CAP_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stImsVtCap), sizeof(TAF_MMA_IMS_VIDEO_CALL_CAP_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetImsSmsCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_IMS_SMS_CFG_STRU           *pstImsSmsCfg
)
{
    TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    pstMsg = (TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
          0x00,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_IMS_SMS_CFG_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_SMS_CFG_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stImsSmsCfg       = *pstImsSmsCfg;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryImsSmsCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_IMS_SMS_CFG_QRY_REQ_STRU   *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ????????*/
    pstMsg = (TAF_MMA_IMS_SMS_CFG_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_IMS_SMS_CFG_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SMS_CFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
          0x00,
          (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SMS_CFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_IMS_DOMAIN_CFG_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_SMS_CFG_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

     /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#endif


VOS_UINT32 TAF_MMA_AttachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType
)
{
    TAF_MMA_ATTACH_REQ_STRU            *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????????????????? */
    pstMsg = (TAF_MMA_ATTACH_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_ATTACH_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_ATTACH_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_ATTACH_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enAttachType      = enAttachType;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_AttachStatusQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enDomainType
)
{
    TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????????????????? */
    pstMsg = (TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????TAF_MMA_ATTACH_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_ATTACH_STATUS_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enDomainType      = enDomainType;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}


#if (OSA_CPU_CCPU == VOS_OSA_CPU)

MODULE_EXPORTED VOS_VOID TAF_MMA_SrvAcqReq(
    TAF_MMA_SRV_TYPE_ENUM_UINT8         enSrvType,
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstRatList,
    VOS_UINT32                          ulModuleId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MMA_SRV_ACQ_REQ_STRU           *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulSndPid;
    VOS_UINT32                          ulRcvPid;

    enModemId = NAS_MULTIINSTANCE_GetModemIdFromPid(ulModuleId);
    ulSndPid  = NAS_MULTIINSTANCE_GetSpecModemPid(enModemId, WUEPS_PID_TAF);
    ulRcvPid  = NAS_MULTIINSTANCE_GetSpecModemPid(enModemId, WUEPS_PID_MMA);

    /* ??????????TAF_MMA_SRV_ACQ_REQ_STRU */
    pstMsg = (TAF_MMA_SRV_ACQ_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSndPid,
                                             sizeof(TAF_MMA_SRV_ACQ_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {

        return;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSndPid;
    pstMsg->ulReceiverPid     = ulRcvPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_SRV_ACQ_REQ;

    pstMsg->stCtrl.ulModuleId = ulModuleId;

    pstMsg->enSrvType         = enSrvType;
    pstMsg->stRatList         = *pstRatList;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSndPid, pstMsg))
    {
        return;
    }

    return;
}


MODULE_EXPORTED VOS_VOID TAF_MMA_SrvAcqStop(
    VOS_UINT32                          ulModuleId
)
{
    TAF_MMA_STOP_SRVACQ_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulSndPid;
    VOS_UINT32                          ulRcvPid;

    enModemId = NAS_MULTIINSTANCE_GetCurrInstanceModemId(ulModuleId);
    ulSndPid  = NAS_MULTIINSTANCE_GetSpecModemPid(enModemId, WUEPS_PID_TAF);
    ulRcvPid  = NAS_MULTIINSTANCE_GetSpecModemPid(enModemId, WUEPS_PID_MMA);

    /* ??????????TAF_MMA_STOP_SRVACQ_NOTIFY_STRU */
    pstMsg = (TAF_MMA_STOP_SRVACQ_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSndPid, sizeof(TAF_MMA_STOP_SRVACQ_NOTIFY_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_STOP_SRVACQ_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_STOP_SRVACQ_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulSenderPid             = ulSndPid;
    pstMsg->ulReceiverPid           = ulRcvPid;
    pstMsg->ulMsgName               = ID_TAF_MMA_STOP_SRVACQ_NOTIFY;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSndPid, pstMsg);

    return;
}
#endif



VOS_UINT32 TAF_MMA_SetQuitCallBack(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MMA_QUIT_CALLBACK_SET_REQ */
    pstMsg = (TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_QUIT_CALLBACK_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



VOS_UINT32  TAF_MMA_ProcCFreqLockSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstCFreqLockPara
)
{
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstCFreqLockPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CFREQ_LOCK_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CFREQ_LOCK_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CFREQ_LOCK_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CFREQ_LOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CFREQ_LOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_CDMA_FREQ_LOCK_SET_REQ;
    pstMsg->ulModuleId        = ulModuleId;
    pstMsg->usClientId        = usClientId;
    pstMsg->ucOpId            = ucOpId;
    lMemResult = memcpy_s(&pstMsg->stCFreqLockPara, sizeof(pstMsg->stCFreqLockPara), pstCFreqLockPara, sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCFreqLockPara), sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcCFreqLockQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                         ulReceiverPid;
    VOS_UINT32                         ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CFREQ_LOCK_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                   ulSenderPid,
                                                   sizeof(TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcCdmaCsqSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CDMACSQ_PARA_STRU          *pstCdmaCsqPara
)
{
    TAF_MMA_CDMACSQ_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstCdmaCsqPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CDMA_CSQ_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CDMACSQ_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CDMACSQ_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CDMACSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CDMACSQ_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stCdmaCsqPara), sizeof(pstMsg->stCdmaCsqPara), pstCdmaCsqPara, sizeof(TAF_MMA_CDMACSQ_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCdmaCsqPara), sizeof(TAF_MMA_CDMACSQ_PARA_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcCdmaCsqQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CDMACSQ_QRY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CDMACSQ_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_CDMACSQ_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CDMACSQ_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CDMACSQ_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CDMACSQ_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CDMACSQ_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}


VOS_UINT32  TAF_MMA_Proc1xChanSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstCFreqLockPara
)
{
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstCFreqLockPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CFREQ_LOCK_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CFREQ_LOCK_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CFREQ_LOCK_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CFREQ_LOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CFREQ_LOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_1XCHAN_SET_REQ;
    pstMsg->ulModuleId        = ulModuleId;
    pstMsg->usClientId        = usClientId;
    pstMsg->ucOpId            = ucOpId;
    lMemResult = memcpy_s(&pstMsg->stCFreqLockPara, sizeof(pstMsg->stCFreqLockPara), pstCFreqLockPara, sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCFreqLockPara), sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_Proc1xChanQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_1XCHAN_QUERY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                         ulReceiverPid;
    VOS_UINT32                         ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MSG_MMA_CVER_QUERY_REQ */
    pstMsg = (TAF_MMA_1XCHAN_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_1XCHAN_QUERY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_1XCHAN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_1XCHAN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_1XCHAN_QUERY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcProRevInUseQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CVER_QUERY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                         ulReceiverPid;
    VOS_UINT32                         ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MSG_MMA_CVER_QUERY_REQ */
    pstMsg = (TAF_MMA_CVER_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_CVER_QUERY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CVER_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CVER_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CVER_QUERY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcStateQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_STATE_QUERY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                         ulReceiverPid;
    VOS_UINT32                         ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MSG_MMA_CVER_QUERY_REQ */
    pstMsg = (TAF_MMA_STATE_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_STATE_QUERY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_STATE_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_STATE_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_GETSTA_QUERY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcCHVerQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CHIGHVER_QUERY_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                         ulReceiverPid;
    VOS_UINT32                         ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MSG_MMA_CVER_QUERY_REQ */
    pstMsg = (TAF_MMA_CHIGHVER_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_CHIGHVER_QUERY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CHIGHVER_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CHIGHVER_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CHIGHVER_QUERY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}




/* ????CDMA???????? */
#if (FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)

VOS_UINT32 TAF_MMA_SetCSidList(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_OPER_LOCK_WHITE_SID_STRU   *pstWhiteSidList
)
{
    TAF_MMA_CSIDLIST_SET_REQ_STRU      *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MSG_MMA_CVER_QUERY_REQ */
    pstMsg = (TAF_MMA_CSIDLIST_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_CSIDLIST_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CSIDLIST_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CSIDLIST_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CSIDLIST_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    lMemResult = memcpy_s(&pstMsg->stWhiteSidInfo, sizeof(pstMsg->stWhiteSidInfo), pstWhiteSidList, sizeof(TAF_MMA_OPER_LOCK_WHITE_SID_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stWhiteSidInfo), sizeof(TAF_MMA_OPER_LOCK_WHITE_SID_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#endif

/* ????CDMA???????? */



VOS_UINT32 TAF_MMA_ProcHdrCsqSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_HDR_CSQ_PARA_STRU          *pstHdrCsqPara
)
{
    TAF_MMA_HDR_CSQ_SET_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CDMA_CSQ_SET_REQ_STRU */
    pstMsg = (TAF_MMA_HDR_CSQ_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_HDR_CSQ_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_HDR_CSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_HDR_CSQ_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_HDR_CSQ_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stHdrCsqSetting), sizeof(pstMsg->stHdrCsqSetting), pstHdrCsqPara, sizeof(TAF_MMA_HDR_CSQ_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stHdrCsqSetting), sizeof(TAF_MMA_HDR_CSQ_PARA_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_ProcHdrCsqQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CDMACSQ_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_HDR_CSQ_QRY_SETTING_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}



VOS_UINT32 TAF_MMA_QryCurrSidNid(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CURR_SID_NID_QRY_REQ_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_CURR_SID_NID_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                               sizeof(TAF_MMA_CURR_SID_NID_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_CURR_SID_NID_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_CURR_SID_NID_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_CURR_SID_NID_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}


VOS_UINT32 TAF_MMA_QryCtRoamInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU              *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                               sizeof(TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->enMsgName           = ID_TAF_MMA_CTCC_ROAMING_NW_INFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}


VOS_UINT32 TAF_MMA_SetCtOosCount(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulClOosCount,
    VOS_UINT32                          ulGulOosCount
)
{
    TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU                    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MMA_QUIT_CALLBACK_SET_REQ */
    pstMsg = (TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                sizeof(TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CTCC_OOS_COUNT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->enMsgName                   = ID_TAF_MMA_CTCC_OOS_COUNT_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->usClOosCount                = (VOS_UINT16)ulClOosCount;
    pstMsg->usGulOosCount               = (VOS_UINT16)ulGulOosCount;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetCtRoamInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCtRoamRtpFlag
)
{
    TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU      *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????ID_TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ */
    pstMsg = (TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                  sizeof(TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_CTCC_ROAMING_NW_INFO_RTP_CFG_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->ucCtRoamRtpFlag   = ucCtRoamRtpFlag;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_QryPrlIdInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_PRLID_QRY_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_PRLID_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                        sizeof(TAF_MMA_PRLID_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(TAF_MMA_PRLID_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_PRLID_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->enMsgName           = ID_TAF_MMA_PRLID_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryRatCombinedMode(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_RAT_COMBINED_MODE_QRY_REQ_STRU                 *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_RAT_COMBINED_MODE_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                     sizeof(TAF_MMA_RAT_COMBINED_MODE_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                   sizeof(TAF_MMA_RAT_COMBINED_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                   0x00,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_RAT_COMBINED_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->enMsgName           = ID_TAF_MMA_RAT_COMBINED_MODE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}




VOS_UINT32  TAF_MMA_ProcResetNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResetStep
)
{
    TAF_MMA_RESET_NTF_STRU             *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CFREQ_LOCK_SET_REQ_STRU */
    pstMsg = (TAF_MMA_RESET_NTF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_RESET_NTF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_RESET_NTF_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_RESET_NTF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_RESET_NTF;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->ucResetStep       = ucResetStep;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCLocInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                               sizeof(TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_CDMA_LOCINFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#endif


VOS_UINT32 TAF_MMA_QryCurrEmcCallBackMode(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_EMC_CALL_BACK_QRY_REQ_STRU                     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_EMC_CALL_BACK_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                                sizeof(TAF_MMA_EMC_CALL_BACK_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_EMC_CALL_BACK_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_EMC_CALL_BACK_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_EMC_CALL_BACK_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}



VOS_UINT32 TAF_MMA_SetFPlmnInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PH_FPLMN_OPERATE_STRU          *pstCFPlmnPara
)
{
    TAF_MMA_CFPLMN_SET_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstCFPlmnPara)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CDMA_CSQ_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CFPLMN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_CFPLMN_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CFPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CFPLMN_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stCFPlmnPara), sizeof(pstMsg->stCFPlmnPara), pstCFPlmnPara, sizeof(TAF_PH_FPLMN_OPERATE_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCFPlmnPara), sizeof(TAF_PH_FPLMN_OPERATE_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryFPlmnInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CFPLMN_QUERY_REQ_STRU      *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CDMACSQ_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_CFPLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              ulSenderPid,
                                              sizeof(TAF_MMA_CFPLMN_QUERY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CFPLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CFPLMN_QUERY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);
    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetCpolReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmn
)
{
    TAF_MMA_PREF_PLMN_SET_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstPrefPlmn)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_PREF_PLMN_SET_REQ_STRU */
    pstMsg = (TAF_MMA_PREF_PLMN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_PREF_PLMN_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PREF_PLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_PREF_PLMN_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    lMemResult = memcpy_s(&pstMsg->stPrefPlmn, sizeof(pstMsg->stPrefPlmn), pstPrefPlmn, sizeof(TAF_PH_SET_PREFPLMN_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPrefPlmn), sizeof(TAF_PH_SET_PREFPLMN_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QueryCpolReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU   *pstCpolInfo
)
{
    TAF_MMA_PREF_PLMN_QUERY_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstCpolInfo)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_PREF_PLMN_QUERY_REQ_STRU */
    pstMsg = (TAF_MMA_PREF_PLMN_QUERY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_PREF_PLMN_QUERY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PREF_PLMN_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_PREF_PLMN_QUERY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    lMemResult = memcpy_s(&pstMsg->stCpolInfo, sizeof(pstMsg->stCpolInfo), pstCpolInfo, sizeof(TAF_MMA_CPOL_INFO_QUERY_REQ_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCpolInfo), sizeof(TAF_MMA_CPOL_INFO_QUERY_REQ_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_TestCpolReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
)
{
    TAF_MMA_PREF_PLMN_TEST_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (MN_PH_PREF_PLMN_HPLMN < enPrefPlmnType)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_PREF_PLMN_TEST_REQ_STRU */
    pstMsg = (TAF_MMA_PREF_PLMN_TEST_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_PREF_PLMN_TEST_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PREF_PLMN_TEST_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PREF_PLMN_TEST_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_PREF_PLMN_TEST_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enPrefPlmnType    = enPrefPlmnType;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetCerssiReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_START_INFO_IND_STRU            *pstStartInfoInd
)
{
    TAF_MMA_CERSSI_SET_REQ_STRU        *pstCerssiCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstStartInfoInd)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CDMA_CSQ_SET_REQ_STRU */
    pstCerssiCfg = (TAF_MMA_CERSSI_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_CERSSI_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstCerssiCfg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstCerssiCfg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CERSSI_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CERSSI_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstCerssiCfg->ulSenderPid                 = ulSenderPid;
    pstCerssiCfg->ulReceiverPid               = ulReceiverPid;
    pstCerssiCfg->ulMsgName                   = ID_TAF_MMA_CERSSI_SET_REQ;

    pstCerssiCfg->stCtrl.ulModuleId           = ulModuleId;
    pstCerssiCfg->stCtrl.usClientId           = usClientId;
    pstCerssiCfg->stCtrl.ucOpId               = ucOpId;
    pstCerssiCfg->ucActionType                = pstStartInfoInd->ucActionType;
    pstCerssiCfg->ucRrcMsgType                = pstStartInfoInd->ucRrcMsgType;
    pstCerssiCfg->ucMinRptTimerInterval       = pstStartInfoInd->ucMinRptTimerInterval;
    pstCerssiCfg->ucSignThreshold             = pstStartInfoInd->ucSignThreshold;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstCerssiCfg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCerssiReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CERSSI_INFO_QRY_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PHONE_MODE_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CERSSI_INFO_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                ulSenderPid,
                                                sizeof(TAF_MMA_CERSSI_INFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CERSSI_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CERSSI_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CERSSI_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    pstMsg->ucNsaQryFlag                = VOS_FALSE;
#endif

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_NR)

VOS_UINT32 TAF_MMA_QryCserssiReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CERSSI_INFO_QRY_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PHONE_MODE_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CERSSI_INFO_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                ulSenderPid,
                                                sizeof(TAF_MMA_CERSSI_INFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CERSSI_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CERSSI_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CERSSI_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->ucNsaQryFlag                = VOS_TRUE;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#endif



VOS_UINT32 TAF_MMA_SetCindReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_START_INFO_IND_STRU            *pstStartInfoInd
)
{
    TAF_MMA_CIND_SET_REQ_STRU          *pstCindCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (VOS_NULL_PTR == pstStartInfoInd)
    {
        return VOS_FALSE;
    }

    /* ???????? */
    pstCindCfg = (TAF_MMA_CIND_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_CIND_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstCindCfg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstCindCfg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CIND_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CIND_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstCindCfg->ulSenderPid                 = ulSenderPid;
    pstCindCfg->ulReceiverPid               = ulReceiverPid;
    pstCindCfg->ulMsgName                   = ID_TAF_MMA_CIND_SET_REQ;

    pstCindCfg->stCtrl.ulModuleId           = ulModuleId;
    pstCindCfg->stCtrl.usClientId           = usClientId;
    pstCindCfg->stCtrl.ucOpId               = ucOpId;
    pstCindCfg->ucActionType                = pstStartInfoInd->ucActionType;
    pstCindCfg->ucRrcMsgType                = pstStartInfoInd->ucRrcMsgType;
    pstCindCfg->ucMinRptTimerInterval       = pstStartInfoInd->ucMinRptTimerInterval;
    pstCindCfg->ucSignThreshold             = pstStartInfoInd->ucSignThreshold;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstCindCfg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCrpnReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CRPN_QRY_PARA_STRU         *pstCrpnQryReq
)
{
    TAF_MMA_CRPN_QRY_REQ_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CRPN_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_CRPN_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CRPN_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
       return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CRPN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CRPN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CRPN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    if (VOS_NULL_PTR != pstCrpnQryReq)
    {
        lMemResult = memcpy_s(&pstMsg->stCrpnQryPara, sizeof(pstMsg->stCrpnQryPara), pstCrpnQryReq, sizeof(TAF_MMA_CRPN_QRY_PARA_STRU));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCrpnQryPara), sizeof(TAF_MMA_CRPN_QRY_PARA_STRU));
    }

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetCmmReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MM_TEST_AT_CMD_STRU                *pstTestAtCmd
)
{
    TAF_MMA_CMM_SET_REQ_STRU           *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CMM_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CMM_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CMM_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
       return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CMM_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CMM_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CMM_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    if (VOS_NULL_PTR != pstTestAtCmd )
    {
        lMemResult = memcpy_s(&pstMsg->stCmmSetReq, sizeof(pstMsg->stCmmSetReq), pstTestAtCmd, sizeof(MM_TEST_AT_CMD_STRU));
        TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCmmSetReq), sizeof(MM_TEST_AT_CMD_STRU));
    }

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryAcInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_AC_INFO_QRY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_AC_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                          sizeof(TAF_MMA_AC_INFO_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_AC_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_AC_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_AC_INFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCopnInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT16                          usFromIndex,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_COPN_INFO_QRY_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /*
    AT??MMA??????????????:
    ????????????????????????????????????????????????????????????????50????????????
    ??????????????????????0??????????????50????????????
    */

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_COPN_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_COPN_INFO_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_COPN_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_COPN_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_COPN_INFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;
    pstMsg->usFromIndex         = usFromIndex;
    pstMsg->usPlmnNum           = TAF_MMA_COPN_PLMN_MAX_NUM;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#if (FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)

VOS_UINT32 TAF_MMA_SimInsertReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_SIM_INSERT_STATE_ENUM_UINT32    enSimInsertState)
{

    TAF_MMA_SIM_INSERT_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_SIM_INSERT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                         sizeof(TAF_MMA_SIM_INSERT_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_SIM_INSERT_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SIM_INSERT_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_SIM_INSERT_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;
    pstMsg->enSimInsertState    = enSimInsertState;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#endif


VOS_UINT32 TAF_MMA_SetEOPlmnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnCfg
)
{
    TAF_MMA_EOPLMN_SET_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    if (VOS_NULL_PTR == pstEOPlmnCfg)
    {
        return VOS_FALSE;
    }

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_EOPLMN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                         sizeof(TAF_MMA_EOPLMN_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_EOPLMN_SET_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    lMemResult = memcpy_s(&(pstMsg->stEOPlmnSetPara), sizeof(pstMsg->stEOPlmnSetPara), pstEOPlmnCfg, sizeof(TAF_MMA_SET_EOPLMN_LIST_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stEOPlmnSetPara), sizeof(TAF_MMA_SET_EOPLMN_LIST_STRU));

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_QryEOPlmnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_EOPLMN_QRY_REQ_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_EOPLMN_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                         sizeof(TAF_MMA_EOPLMN_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_EOPLMN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_NetScanReq(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       ucOpId,
    TAF_MMA_NET_SCAN_SET_PARA_STRU_STRU                    *pstNetScanSetPara
)
{
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanReq = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    if (VOS_NULL_PTR == pstNetScanSetPara)
    {
        return VOS_FALSE;
    }

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstNetScanReq = (TAF_MMA_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                              sizeof(TAF_MMA_NET_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstNetScanReq)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S(((VOS_UINT8 *)pstNetScanReq + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstNetScanReq->ulReceiverPid       = ulReceiverPid;
    pstNetScanReq->ulSenderPid         = ulSenderPid;
    pstNetScanReq->ulMsgName           = ID_TAF_MMA_NET_SCAN_REQ;
    pstNetScanReq->stCtrl.ulModuleId   = ulModuleId;
    pstNetScanReq->stCtrl.usClientId   = usClientId;
    pstNetScanReq->stCtrl.ucOpId       = ucOpId;
    pstNetScanReq->stPara              = *pstNetScanSetPara;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstNetScanReq);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_NetScanAbortReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_NET_SCAN_ABORT_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_NET_SCAN_ABORT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                             sizeof(TAF_MMA_NET_SCAN_ABORT_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_NET_SCAN_ABORT_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_QrySpnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_SPN_QRY_REQ_STRU           *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_SPN_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                      sizeof(TAF_MMA_SPN_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_SPN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SPN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_SPN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}




VOS_UINT32 TAF_MMA_QryMMPlmnInfoReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_MMPLMNINFO_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_MMPLMNINFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                             sizeof(TAF_MMA_MMPLMNINFO_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_MMPLMNINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_MMPLMNINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_MMPLMNINFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryPlmnReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                    sizeof(TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_LAST_CAMP_PLMN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryUserSrvStateReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                    sizeof(TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_USER_SRV_STATE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_QryApPwrOnAndRegTimeReq(
    VOS_UINT32                          ulModuleId,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                  ulReceiverPid;
    VOS_UINT32                                  ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* Allocating memory for message */
    pstMsg = (TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                           sizeof(TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}



VOS_UINT32  TAF_MMA_SetAutoAttachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSetValue
)
{
    TAF_MMA_AUTO_ATTACH_SET_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_AUTO_ATTACH_SET_REQ_STRU */
    pstMsg = (TAF_MMA_AUTO_ATTACH_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_AUTO_ATTACH_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_AUTO_ATTACH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_AUTO_ATTACH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_AUTO_ATTACH_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->ulAutoAttachEnable          = ulSetValue;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_TestSysCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_SYSCFG_TEST_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_SYSCFG_TEST_REQ_STRU */
    pstMsg = (TAF_MMA_SYSCFG_TEST_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_SYSCFG_TEST_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SYSCFG_TEST_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SYSCFG_TEST_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_SYSCFG_TEST_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);
    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_QryAccessModeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_ACCESS_MODE_QRY_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_ACCESS_MODE_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_ACCESS_MODE_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_ACCESS_MODE_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_ACCESS_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_ACCESS_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_ACCESS_MODE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCopsInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_COPS_QRY_REQ_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_COPS_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_COPS_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_COPS_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_COPS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_COPS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_COPS_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetEflociInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_EFLOCIINFO_STRU            *pstEfLociInfo
)
{
    TAF_MMA_EFLOCIINFO_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_EFLOCIINFO_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_EFLOCIINFO_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFLOCIINFO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFLOCIINFO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_EFLOCIINFO_SET_REQ;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;

    lMemResult = memcpy_s(&(pstMsg->stEflociInfo),
                          sizeof(TAF_MMA_EFLOCIINFO_STRU),
                          pstEfLociInfo,
                          sizeof(TAF_MMA_EFLOCIINFO_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TAF_MMA_EFLOCIINFO_STRU), sizeof(TAF_MMA_EFLOCIINFO_STRU));

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryEflociInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_EFLOCIINFO_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_EFLOCIINFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_EFLOCIINFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFLOCIINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFLOCIINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_EFLOCIINFO_QRY_REQ;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetPsEflociInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_EFPSLOCIINFO_STRU          *pstPsefLociInfo
)
{
    TAF_MMA_EFPSLOCIINFO_SET_REQ_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_EFPSLOCIINFO_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_EFPSLOCIINFO_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFPSLOCIINFO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFPSLOCIINFO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_EFPSLOCIINFO_SET_REQ;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;

    lMemResult = memcpy_s(&(pstMsg->stPsEflociInfo),
                          sizeof(TAF_MMA_EFPSLOCIINFO_STRU),
                          pstPsefLociInfo,
                          sizeof(TAF_MMA_EFPSLOCIINFO_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TAF_MMA_EFPSLOCIINFO_STRU), sizeof(TAF_MMA_EFPSLOCIINFO_STRU));

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryPsEflociInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_EFPSLOCIINFO_QRY_REQ_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_EFPSLOCIINFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_EFPSLOCIINFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFPSLOCIINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_EFPSLOCIINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_EFPSLOCIINFO_QRY_REQ;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryDplmnListReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_DPLMN_QRY_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_DPLMN_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_DPLMN_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_DPLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_DPLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ?????????? */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_DPLMN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetDplmnListReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucSeq,
    VOS_UINT8                          *pucVersion,
    TAF_MMA_DPLMN_INFO_SET_STRU        *pstDplmnInfo
)
{
    TAF_MMA_DPLMN_SET_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_DPLMN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_TAF,
                                        sizeof(TAF_MMA_DPLMN_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    /* ???????????? */
    TAF_MEM_SET_S((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)sizeof(TAF_MMA_DPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)sizeof(TAF_MMA_DPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ?????????? */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_DPLMN_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = 0;

    /* ??????????????????*/
    pstMsg->ucSeq                       = ucSeq;
    lMemResult = memcpy_s(pstMsg->aucVersionId,
                          sizeof(pstMsg->aucVersionId),
                          pucVersion,
                          TAF_MMA_VERSION_INFO_LEN);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->aucVersionId), TAF_MMA_VERSION_INFO_LEN);

    if ( pstDplmnInfo->ucEhPlmnNum > TAF_MMA_MAX_EHPLMN_NUM )
    {
        pstDplmnInfo->ucEhPlmnNum = TAF_MMA_MAX_EHPLMN_NUM;
    }

    if ( pstDplmnInfo->usDplmnNum > TAF_MMA_MAX_DPLMN_NUM )
    {
        pstDplmnInfo->usDplmnNum = TAF_MMA_MAX_DPLMN_NUM;
    }

    /* ????HPLMN??????HPLMN??????????DPLMN??????DPLMN???? */
    pstMsg->stDplmnInfo.ucEhPlmnNum     = pstDplmnInfo->ucEhPlmnNum;
    pstMsg->stDplmnInfo.usDplmnNum      = pstDplmnInfo->usDplmnNum;
    lMemResult = memcpy_s(pstMsg->stDplmnInfo.astEhPlmnInfo,
                          sizeof(pstMsg->stDplmnInfo.astEhPlmnInfo),
                          pstDplmnInfo->astEhPlmnInfo,
                          sizeof(TAF_PLMN_ID_STRU) * pstDplmnInfo->ucEhPlmnNum);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stDplmnInfo.astEhPlmnInfo), sizeof(TAF_PLMN_ID_STRU) * pstDplmnInfo->ucEhPlmnNum);
    lMemResult = memcpy_s(pstMsg->stDplmnInfo.astDplmnList,
               sizeof(pstMsg->stDplmnInfo.astDplmnList),
               pstDplmnInfo->astDplmnList,
               sizeof(TAF_MMA_PLMN_WITH_SIM_RAT_STRU) * pstDplmnInfo->usDplmnNum );
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stDplmnInfo.astDplmnList), sizeof(TAF_MMA_PLMN_WITH_SIM_RAT_STRU) * pstDplmnInfo->usDplmnNum);

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetBorderInfoReq(
    VOS_UINT32                                              ulModuleId,
    VOS_UINT16                                              usClientId,
    TAF_MMA_SET_BORDER_INFO_OPERATE_TYPE_ENUM_UINT8         enOperateType,
    TAF_MMA_BORDER_INFO_STRU                               *pstBorderInfo
)
{
    TAF_MMA_BORDER_INFO_SET_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_BORDER_INFO_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_TAF,
                                        sizeof(TAF_MMA_BORDER_INFO_SET_REQ_STRU) + pstBorderInfo->ulBorderInfoLen - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    /* ???????????? */
    TAF_MEM_SET_S((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)sizeof(TAF_MMA_BORDER_INFO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH + pstBorderInfo->ulBorderInfoLen - 4,
                0x00,
               (VOS_SIZE_T)sizeof(TAF_MMA_BORDER_INFO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH + pstBorderInfo->ulBorderInfoLen - 4);

    /* ?????????? */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_BORDER_INFO_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = 0;

    /* ???????????? */
    pstMsg->enOperateType               = enOperateType;

    lMemResult = memcpy_s(&(pstMsg->stBorderInfo),
                          sizeof(TAF_MMA_BORDER_INFO_STRU) + pstBorderInfo->ulBorderInfoLen - 4,
                          pstBorderInfo,
                          sizeof(TAF_MMA_BORDER_INFO_STRU) + pstBorderInfo->ulBorderInfoLen - 4);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TAF_MMA_BORDER_INFO_STRU) + pstBorderInfo->ulBorderInfoLen - 4, sizeof(TAF_MMA_BORDER_INFO_STRU) + pstBorderInfo->ulBorderInfoLen - 4);

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryBorderInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_BORDER_INFO_QRY_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_BORDER_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_BORDER_INFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_BORDER_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_BORDER_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ?????????? */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_BORDER_INFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_UINT32 TAF_MMA_SetDsdsStateReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulEnable
)
{
    TAF_MMA_DSDS_STATE_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_DSDS_STATE_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_DSDS_STATE_SET_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    /* ???????????? */
    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_DSDS_STATE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_DSDS_STATE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ?????????? */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_DSDS_STATE_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = 0;

    /* ???????????? */
    pstMsg->ucEnable                    = (VOS_UINT8)ulEnable;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#endif


VOS_UINT32 TAF_MMA_QryRegStateReq(
    VOS_UINT32                                              ulModuleId,
    VOS_UINT16                                              usClientId,
    VOS_UINT8                                               ucOpId,
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enRegStaType
)
{
    TAF_MMA_REG_STATE_QRY_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_REG_STATE_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_REG_STATE_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              ulSenderPid,
                                              sizeof(TAF_MMA_REG_STATE_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_REG_STATE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_REG_STATE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_REG_STATE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    pstMsg->enQryRegStaType = enRegStaType;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryAutoAttachInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_AUTOATTACH_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ulSenderPid,
                                               sizeof(TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_AUTO_ATTACH_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QrySystemInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSysInfoExFlag
)
{
    TAF_MMA_SYSINFO_QRY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_SYSINFO_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_SYSINFO_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_SYSINFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SYSINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SYSINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_SYSINFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->ulSysInfoExFlag             = ulSysInfoExFlag;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
/* QryAntennaInfoReq ????MTA???? */


VOS_UINT32 TAF_MMA_QryApHplmnInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_HOME_PLMN_QRY_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_APHPLMN_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_HOME_PLMN_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              ulSenderPid,
                                              sizeof(TAF_MMA_HOME_PLMN_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_HOME_PLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_HOME_PLMN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_HOME_PLMN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

/* QryCsnrReq????MTA???? */


VOS_UINT32 TAF_MMA_QryCsqReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CSQ_QRY_REQ_STRU           *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CSQ_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_CSQ_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_CSQ_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CSQ_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CSQ_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CSQ_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;

}

/* QryCsqlvlReq????MTA???? */



VOS_UINT32 TAF_MMA_QryBatteryCapacityReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU                  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_CBC_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        ulSenderPid,
                                        sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_BATTERY_CAPACITY_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryHandShakeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_HAND_SHAKE_QRY_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_HS_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_HAND_SHAKE_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_HAND_SHAKE_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_HAND_SHAKE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_HAND_SHAKE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_HAND_SHAKE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}




VOS_UINT32 TAF_MMA_QryPacspReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_PACSP_QRY_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_PACSP_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_PACSP_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_PACSP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_PACSP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_PACSP_QRY_REQ;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#if(FEATURE_LTE == FEATURE_ON)

/*lint -save -e838 -specific(-e838)*/
VOS_UINT32 TAF_MMA_AcdcAppNotify(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_ACDC_APP_INFO_STRU         *pstAcdcAppInfo
)
{
    TAF_MMA_ACDC_APP_NOTIFY_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_ACDC_APP_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_ACDC_APP_NOTIFY_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_MMA_ACDC_APP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_ACDC_APP_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_ACDC_APP_NOTIFY;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;

    lMemResult = memcpy_s(&(pstMsg->stAcdcAppInfo),
                          sizeof(TAF_MMA_ACDC_APP_INFO_STRU),
                          pstAcdcAppInfo,
                          sizeof(TAF_MMA_ACDC_APP_INFO_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(TAF_MMA_ACDC_APP_INFO_STRU), sizeof(TAF_MMA_ACDC_APP_INFO_STRU));

    /* ????????*/
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
/*lint -restore*/
#endif


MODULE_EXPORTED VOS_VOID TAF_MMA_SndRestartReq(
    VOS_UINT32                          ulModuleId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    TAF_MMA_RESTART_REQ_STRU           *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulReceiverPid;

    if (MODEM_ID_0 == enModemId)
    {
        ulSenderPid      = I0_WUEPS_PID_TAF;
        ulReceiverPid    = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        ulSenderPid      = I1_WUEPS_PID_TAF;
        ulReceiverPid    = I1_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_2 == enModemId)
    {
        ulSenderPid      = I2_WUEPS_PID_TAF;
        ulReceiverPid    = I2_WUEPS_PID_MMA;
    }
    else
    {
        return;
    }

    pstMsg = (TAF_MMA_RESTART_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, sizeof(TAF_MMA_RESTART_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(TAF_MMA_RESTART_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  (VOS_SIZE_T)(sizeof(TAF_MMA_RESTART_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->enMsgName         = ID_TAF_MMA_RESTART_REQ;
    pstMsg->ulModuleId        = ulModuleId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return;
}


VOS_UINT32 TAF_MMA_ExchangeModemInfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    MODEM_ID_ENUM_UINT16                enFirstModemId,
    MODEM_ID_ENUM_UINT16                enSecondModemId
)
{
    TAF_MMA_EXCHANGE_MODEM_INFO_REQ_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ?????????? */
    pstMsg = (TAF_MMA_EXCHANGE_MODEM_INFO_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_EXCHANGE_MODEM_INFO_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    /* ???????????? */
    TAF_MEM_SET_S((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                  (VOS_SIZE_T)sizeof(TAF_MMA_EXCHANGE_MODEM_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  (VOS_SIZE_T)sizeof(TAF_MMA_EXCHANGE_MODEM_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ?????????? */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_EXCHANGE_MODEM_INFO_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = 0;
    pstMsg->enFirstModemId              = enFirstModemId;
    pstMsg->enSecondModemId             = enSecondModemId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_PlmnSearchReq(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_SEARCH_TYPE_ENUM_UINT32     enSearchType,
    TAF_PLMN_USER_SEL_STRU             *pstPlmnUserSel
)
{
    TAF_MMA_PLMN_SEARCH_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(pstCtrl->usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(pstCtrl->usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU */
    pstMsg = (TAF_MMA_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_PLMN_SEARCH_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PLMN_SEARCH_REQ;
    pstMsg->enSearchType                = enSearchType;

    /* ???????? */
    lMemResult = memcpy_s(&pstMsg->stCtrl, sizeof(pstMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCtrl), sizeof(TAF_MMA_CTRL_STRU));

    lMemResult = memcpy_s(&pstMsg->stPlmnUserSel, sizeof(pstMsg->stPlmnUserSel), pstPlmnUserSel, sizeof(TAF_PLMN_USER_SEL_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPlmnUserSel), sizeof(TAF_PLMN_USER_SEL_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_PlmnDetectReq(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_DETECT_PLMN_STRU               *pstPlmnDetect
)
{
    TAF_MMA_PLMN_DETECT_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid = TAF_GET_DEST_PID(pstCtrl->usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(pstCtrl->usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU */
    pstMsg = (TAF_MMA_PLMN_DETECT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            ulSenderPid,
                                            sizeof(TAF_MMA_PLMN_DETECT_REQ_STRU));

    /* ?????????????????? */
    if (pstMsg == VOS_NULL_PTR)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_PLMN_DETECT_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_PLMN_DETECT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PLMN_DETECT_NTF;

    /* ???????? */
    lMemResult = memcpy_s(&pstMsg->stCtrl, sizeof(pstMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stCtrl), sizeof(TAF_MMA_CTRL_STRU));

    lMemResult = memcpy_s(&pstMsg->stPlmnDetect, sizeof(pstMsg->stPlmnDetect), pstPlmnDetect, sizeof(TAF_DETECT_PLMN_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPlmnDetect), sizeof(TAF_DETECT_PLMN_STRU));

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

#if (OSA_CPU_CCPU == VOS_OSA_CPU)



VOS_VOID TAF_MMA_SendSmcNoEntityNtf(VOS_VOID)
{
    TAF_MMA_SMC_NO_ENTITY_NOTIFY_STRU  *pstMsg  = VOS_NULL_PTR;

    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId   = NAS_MULTIINSTANCE_GetCurrInstanceModemId(WUEPS_PID_TAF);

    pstMsg = (TAF_MMA_SMC_NO_ENTITY_NOTIFY_STRU*)NAS_MULTIINSTANCE_AllocMsgWithHdr(enModemId,
                                             WUEPS_PID_TAF,
                                             sizeof(TAF_MMA_SMC_NO_ENTITY_NOTIFY_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               sizeof(TAF_MMA_SMC_NO_ENTITY_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_SMC_NO_ENTITY_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid     = WUEPS_PID_MMA;
    pstMsg->enMsgName         = ID_TAF_MMA_SMC_NO_ENTITY_NOTIFY;

    /* ???????? */
    (VOS_VOID)NAS_MULTIINSTANCE_SendMsg(enModemId, pstMsg);

    return;
}

#if (FEATURE_IMS == FEATURE_ON)

VOS_VOID TAF_MMA_ImsRegDomainNotify(
    TAF_MMA_IMS_REG_DOMAIN_ENUM_UINT8           enImsRegDomain,
    TAF_MMA_IMS_REG_STATUS_ENUM_UINT8           enImsRegStatus
)
{
    TAF_MMA_IMS_REG_DOMAIN_NOTIFY_STRU *pstMsg  = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = NAS_MULTIINSTANCE_GetCurrInstanceModemId(WUEPS_PID_TAF);

    /* ??????????TAF_MMA_SRV_ACQ_REQ_STRU */
    pstMsg = (TAF_MMA_IMS_REG_DOMAIN_NOTIFY_STRU*)NAS_MULTIINSTANCE_AllocMsgWithHdr(enModemId,
                                             WUEPS_PID_TAF,
                                             sizeof(TAF_MMA_IMS_REG_DOMAIN_NOTIFY_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               sizeof(TAF_MMA_IMS_REG_DOMAIN_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_REG_DOMAIN_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid     = WUEPS_PID_MMA;
    pstMsg->enMsgName         = ID_TAF_MMA_IMS_REG_DOMAIN_NOTIFY;
    pstMsg->enImsRegDomain    = enImsRegDomain;

    pstMsg->enImsRegStatus    = enImsRegStatus;

    /* ???????? */
    if (VOS_OK != NAS_MULTIINSTANCE_SendMsg(enModemId, pstMsg))
    {
        return;
    }

    return;
}


VOS_VOID TAF_MMA_VolteEmc380FailNotify(VOS_VOID)
{
    TAF_MMA_VOLTE_EMC_380_FAIL_NTF_STRU                    *pstMsg  = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                                    enModemId;

    enModemId = NAS_MULTIINSTANCE_GetCurrInstanceModemId(WUEPS_PID_TAF);

    /* ??????????TAF_MMA_VOLTE_EMC_380_FAIL_NTF_STRU */
    pstMsg = (TAF_MMA_VOLTE_EMC_380_FAIL_NTF_STRU*)NAS_MULTIINSTANCE_AllocMsgWithHdr(enModemId,
                                             WUEPS_PID_TAF,
                                             sizeof(TAF_MMA_VOLTE_EMC_380_FAIL_NTF_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               sizeof(TAF_MMA_VOLTE_EMC_380_FAIL_NTF_STRU) - VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(TAF_MMA_VOLTE_EMC_380_FAIL_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid     = WUEPS_PID_MMA;
    pstMsg->ulMsgName         = ID_TAF_MMA_VOLTE_EMC_380_FAIL_NTF;

    /* ???????? */
    (VOS_VOID)NAS_MULTIINSTANCE_SendMsg(enModemId, pstMsg);

    return;
}

#endif

#endif


VOS_UINT32 TAF_MMA_SetCemodeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulSetValue
)
{
    TAF_MMA_CEMODE_SET_REQ_STRU        *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_SYS_CFG_REQ_STRU */
    pstMsg = (TAF_MMA_CEMODE_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_CEMODE_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CEMODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CEMODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ???????????????? TAF_MMA_CEMODE_SET_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_CEMODE_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->ucCeMode          = (VOS_UINT8)ulSetValue;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryCemodeReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_CEMODE_QRY_REQ_STRU        *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_SYS_CFG_REQ_STRU */
    pstMsg = (TAF_MMA_CEMODE_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_CEMODE_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CEMODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_CEMODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ???????????????? TAF_MMA_CEMODE_QRY_REQ_STRU */
    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_CEMODE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_QryRejinfoReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_REJINFO_QRY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_REJINFO_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_REJINFO_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              ulSenderPid,
                                              sizeof(TAF_MMA_REJINFO_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_SIZE_T)(sizeof(TAF_MMA_REJINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_REJINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_REJINFO_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32  TAF_MMA_SetEmRssiCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_EMRSSICFG_REQ_STRU         *psEmRssiCfgPara
)
{
    TAF_MMA_EMRSSICFG_SET_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ??????????TAF_MMA_EMRSSICFG_SET_REQ_STRU */
    pstMsg = (TAF_MMA_EMRSSICFG_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_EMRSSICFG_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    /* ?????? */
    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                    (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSICFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                    0x00,
                    (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSICFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ????????????????TAF_MMA_EMRSSICFG_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_EMRSSICFG_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    lMemResult = memcpy_s(&(pstMsg->stEmRssiCfg), sizeof(pstMsg->stEmRssiCfg), psEmRssiCfgPara, sizeof(TAF_MMA_EMRSSICFG_REQ_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stEmRssiCfg), sizeof(TAF_MMA_EMRSSICFG_REQ_STRU));

   /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryEmRssiCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_EMRSSICFG_QRY_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ??????????TAF_MMA_EMRSSICFG_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_EMRSSICFG_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_EMRSSICFG_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
       return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSICFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                    0x00,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSICFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_EMRSSICFG_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetEmRssiRptReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *pucEmRssiRptSwitch
)
{
    TAF_MMA_EMRSSIRPT_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                         ulReceiverPid;
    VOS_UINT32                         ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ??????????TAF_MMA_EMRSSIPRT_SET_REQ_STRU */
    pstMsg = (TAF_MMA_EMRSSIRPT_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_EMRSSIRPT_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSIRPT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                   0x00,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSIRPT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????ID_TAF_MMA_EMRSSIRPT_SET_REQ */
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_EMRSSIRPT_SET_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;
    pstMsg->ucEmRssiRptSwitch   = *pucEmRssiRptSwitch;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_QryEmRssiRptReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_EMRSSIRPT_QRY_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ??????????TAF_MMA_EMRSSICFG_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_EMRSSIRPT_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_EMRSSIRPT_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSIRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                   0x00,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_EMRSSIRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_EMRSSIRPT_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SetUlFreqRptReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucMode
)
{
    TAF_MMA_ULFREQRPT_SET_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_ULFREQRPT_SET_REQ_STRU */
    pstMsg = (TAF_MMA_ULFREQRPT_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_ULFREQRPT_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                  (VOS_SIZE_T)(sizeof(TAF_MMA_ULFREQRPT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(TAF_MMA_ULFREQRPT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????????????????ID_TAF_MMA_ULFREQRPT_SET_REQ */
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_ULFREQRPT_SET_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;
    pstMsg->stCtrl.ucOpId       = ucOpId;
    pstMsg->enMode              = ucMode;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_QryUlFreqRptReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_ULFREQRPT_QRY_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_ULFREQRPT_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_ULFREQRPT_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                            sizeof(TAF_MMA_ULFREQRPT_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_ULFREQRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                   0x00,
                   (VOS_SIZE_T)(sizeof(TAF_MMA_ULFREQRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulMsgName           = ID_TAF_MMA_ULFREQRPT_QRY_REQ;
    pstMsg->stCtrl.ulModuleId   = ulModuleId;
    pstMsg->stCtrl.usClientId   = usClientId;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_MMA_SetClDbDomainStatus(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucMode
)
{
    TAF_MMA_CL_DBDOMAIN_STATUS_SET_REQ_STRU                *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ???????? */
    if (1 < ucMode)
    {
        return VOS_FALSE;
    }

    /* ??????????TAF_MMA_CL_DBDOMAIN_STATUS_SET_REQ_STRU */
    pstMsg = (TAF_MMA_CL_DBDOMAIN_STATUS_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        ulSenderPid,
                                                        sizeof(TAF_MMA_CL_DBDOMAIN_STATUS_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                sizeof(TAF_MMA_CL_DBDOMAIN_STATUS_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CL_DBDOMAIN_STATUS_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_CL_DBDOMAIN_STATUSE_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    pstMsg->ucEnableFlag                = ucMode;

    /* ???????? */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstMsg);

    return VOS_TRUE;
}
#endif

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

VOS_UINT32 TAF_MMA_SetPsSceneReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PS_SCENE_PARA_STRU         *pstPsSrvStatePara
)
{
    TAF_MMA_PS_SCENE_SET_REQ_STRU      *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;
    errno_t                             lMemResult;

    ulReceiverPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid     = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);
    pstMsg          = (TAF_MMA_PS_SCENE_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_PS_SCENE_SET_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PS_SCENE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PS_SCENE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_PS_SCENE_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    lMemResult = memcpy_s(&(pstMsg->stPsStatePara), sizeof(pstMsg->stPsStatePara), pstPsSrvStatePara, sizeof(TAF_MMA_PS_SCENE_PARA_STRU));
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pstMsg->stPsStatePara), sizeof(TAF_MMA_PS_SCENE_PARA_STRU));

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_QryPsSceneReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
 )
{
    TAF_MMA_PS_SCENE_QRY_REQ_STRU      *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid     = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);
    pstMsg          = (TAF_MMA_PS_SCENE_QRY_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_PS_SCENE_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PS_SCENE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
            0x00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PS_SCENE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_PS_SCENE_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif

VOS_UINT32 TAF_MMA_QryRrcStatReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_RRCSTAT_QRY_REQ_STRU       *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

    ulReceiverPid = TAF_GET_DEST_PID(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = TAF_GET_DEST_PID(usClientId, WUEPS_PID_TAF);

    /* ??????????TAF_MMA_RRCSTAT_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_RRCSTAT_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_RRCSTAT_QRY_REQ_STRU));

    /* ?????????????????? */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                 (VOS_SIZE_T)(sizeof(TAF_MMA_RRCSTAT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                 0x00,
                 (VOS_SIZE_T)(sizeof(TAF_MMA_RRCSTAT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ????PID??????????WUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_RRCSTAT_QRY_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;

    /* ???????? */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



