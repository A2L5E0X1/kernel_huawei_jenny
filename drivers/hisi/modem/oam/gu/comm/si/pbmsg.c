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

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : pbmsg.c
  Author       : zhuli
  Version      : V100R002
  Date         : 2008-5-15
  Description  : ??C??????????---????????????????????
  Function List:
  History      :
 ************************************************************************/

#include "si_pb.h"

#if (FEATURE_PHONE_SC == FEATURE_OFF)
#include "omprivate.h"
#if (VOS_OSA_CPU == OSA_CPU_CCPU)
#include "usimmglobal.h"
#endif
#endif
#include "AtOamInterface.h"
#include "TafOamInterface.h"

#if (VOS_OS_VER == VOS_WIN32)
#include "ut_mem.h"
#endif

/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID     PS_FILE_ID_PB_MSG_C
#define    THIS_MODU        mod_pam_pb


#if (FEATURE_PHONE_SC == FEATURE_OFF)

/*****************************************************************************
    ????????????
*****************************************************************************/

SI_PB_REQ_UINT_STRU             gstPBReqUnit;

/*??????????????????????A ???????????????? C ??????*/
SI_PB_CONTROL_STRU              gstPBCtrlInfo;
SI_PB_CTRL_INFO_ST              gstPBConfigInfo;

SI_PB_CONTENT_STRU              gastPBContent[SI_PB_MAX_NUMBER];
SI_EXT_CONTENT_STRU             gastEXTContent[SI_PB_MAX_NUMBER];
SI_ANR_CONTENT_STRU             gastANRContent[SI_PB_ANRMAX];
SI_EML_CONTENT_STRU             gstEMLContent;
SI_IAP_CONTENT_STRU             gstIAPContent;
SI_PB_INIT_STATE_STRU           gstPBInitState;
VOS_UINT8                       gucPBCStatus = VOS_TRUE;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
SI_PB_SEARCH_CTRL_STRU          gstPBSearchCtrlInfo;
VOS_UINT32                      gulPBFileCnt;
VOS_UINT32                      gulPBRecordCnt;
VOS_UINT32                      gulPBInitFileNum;
VOS_UINT32                      gulPBInitExtFileNum;
VOS_UINT32                      gulExtRecord;
#endif

extern USIMM_CARDAPP_SERVIC_ENUM_UINT32 g_enAcpuCardStatus;


VOS_UINT32 SI_PB_ErrorProc(VOS_VOID)
{
    USIMM_CARDAPP_SERVIC_ENUM_UINT32       ulCardStatus = USIMM_CARDAPP_SERVIC_BUTT;


#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulCardStatus = (VOS_UINT8)g_enAcpuCardStatus;
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    ulCardStatus = gstPBInitState.enCardService;
#endif

    if( PB_LOCKED == gstPBReqUnit.enPBLock )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: The PB is Locked");

        return TAF_ERR_UNSPECIFIED_ERROR;
    }
    else if((USIMM_CARDAPP_SERVIC_UNAVAILABLE == ulCardStatus)
         || (USIMM_CARDAPP_SERVIC_ABSENT      == ulCardStatus))
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: The Card Absent");

        return TAF_ERR_SIM_FAIL;
    }
    else if( USIMM_CARDAPP_SERVIC_SIM_PUK == ulCardStatus )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: PUK NEED");

        return TAF_ERR_NEED_PUK1;
    }
    else if( USIMM_CARDAPP_SERVIC_SIM_PIN == ulCardStatus )
    {
        PB_WARNING_LOG("SI_PB_ErrorProc: PIN NEED");

        return TAF_ERR_NEED_PIN1;
    }
    else
    {
        return TAF_ERR_NO_ERROR;
    }
}

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)||(defined(DMT)))

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID SI_PB_ReadXeccProc(VOS_UINT16 usIndexNum,VOS_UINT16 usIndexStar,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulValidFlag;
    VOS_UINT16                          i;
    VOS_UINT8                           *pucContent = VOS_NULL_PTR;
    errno_t                             ret;

    pucContent = gastPBContent[PB_XECC_CONTENT].pContent + ((usIndexStar-1)*gastPBContent[PB_XECC_CONTENT].ucRecordLen);
    ulValidFlag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)
    {
        pstCnfData->PBEvent.PBReadCnf.PBRecord.Index = i+usIndexStar;

        ulResult = SI_PB_CheckEccValidity(pucContent[0]);

        if(VOS_ERR == ulResult)
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
        }
        else
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_VALID;
            ulValidFlag = VOS_TRUE;

            SI_PB_BcdToAscii(3, pucContent, sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.Number),
                            pstCnfData->PBEvent.PBReadCnf.PBRecord.Number,
                            &pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberLength);/*Ecc??????????????*/

            pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberType = PB_NUMBER_TYPE_NORMAL;

            if(gastPBContent[PB_XECC_CONTENT].ucNameLen != 0)
            {
                SI_PB_DecodePBName(gastPBContent[PB_XECC_CONTENT].ucNameLen,&pucContent[3],
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTagType,
                                &pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

                (VOS_VOID)memset_s(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                   sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag),
                                   0xFF,
                                   sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag));

                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = PAM_GetMin(pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                                                                                      SI_PB_ALPHATAG_MAX_LEN);

                ret = memcpy_s(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                               SI_PB_ALPHATAG_MAX_LEN,
                               &pucContent[3],
                               pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
                PAM_PRINT_SECFUN_RESULT(ret);
            }
            else
            {
                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = 0;
            }
        }

        if(i == (usIndexNum-1))
        {
            pstCnfData->PBLastTag = VOS_TRUE;
            pstCnfData->PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        (VOS_VOID)SI_PBCallback(pstCnfData);

        pucContent += gastPBContent[PB_XECC_CONTENT].ucRecordLen;/*????????????????????????*/
    }

    return;
}
#endif


VOS_VOID SI_PB_ReadEccProc(VOS_UINT16 usIndexNum,VOS_UINT16 usIndexStar,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulValidFlag;
    VOS_UINT16                          i;
    VOS_UINT8                          *pucContent = VOS_NULL_PTR;
    errno_t                             ret;

    pucContent = gastPBContent[PB_ECC_CONTENT].pContent + ((usIndexStar-1)*gastPBContent[PB_ECC_CONTENT].ucRecordLen);
    ulValidFlag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)
    {
        pstCnfData->PBEvent.PBReadCnf.PBRecord.Index = i+usIndexStar;

        ulResult = SI_PB_CheckEccValidity(pucContent[0]);

        if (VOS_ERR == ulResult)
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
        }
        else
        {
            pstCnfData->PBEvent.PBReadCnf.PBRecord.ValidFlag = SI_PB_CONTENT_VALID;
            ulValidFlag = VOS_TRUE;

            SI_PB_BcdToAscii(3, pucContent, sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.Number),
                             pstCnfData->PBEvent.PBReadCnf.PBRecord.Number,
                            &pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberLength);/*Ecc??????????????*/

            pstCnfData->PBEvent.PBReadCnf.PBRecord.NumberType = PB_NUMBER_TYPE_NORMAL;

            if(gastPBContent[PB_ECC_CONTENT].ucNameLen != 0)
            {
                SI_PB_DecodePBName(gastPBContent[PB_ECC_CONTENT].ucNameLen,&pucContent[3],
                                   &pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTagType,
                                   &pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

                (VOS_VOID)memset_s(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                   sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag),
                                   0xFF,
                                   sizeof(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag));

                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = PAM_GetMin(pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                                                                                      SI_PB_ALPHATAG_MAX_LEN);

                ret = memcpy_s(pstCnfData->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                               SI_PB_ALPHATAG_MAX_LEN,
                               &pucContent[3],
                               pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

                PAM_PRINT_SECFUN_RESULT(ret);
            }
            else
            {
                pstCnfData->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength = 0;
            }
        }

        if(i == (usIndexNum-1))
        {
            pstCnfData->PBLastTag = VOS_TRUE;
            pstCnfData->PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        (VOS_VOID)SI_PBCallback(pstCnfData);

        pucContent += gastPBContent[PB_ECC_CONTENT].ucRecordLen;/*????????????????????????*/
    }

    return;
}


VOS_UINT32 SI_PB_ReadProc(PBMsgBlock *pMsg)
{
    SI_PB_READ_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT8                   ucPBoffset;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndexNum;
    VOS_UINT16                  i;
    VOS_UINT8                   *pucContent = VOS_NULL_PTR;
    VOS_UINT32                  ulValidFlag = VOS_FALSE;

    (VOS_VOID)memset_s((VOS_UINT8 *)&stCnfData,
                       sizeof(SI_PB_EVENT_INFO_STRU),
                       (VOS_CHAR)0,
                       sizeof(SI_PB_EVENT_INFO_STRU));

    pstMsg = (SI_PB_READ_REQ_STRU*)pMsg;

    stCnfData.ClientId    = pstMsg->usClient;

    stCnfData.OpId        =  pstMsg->ucOpID;

    stCnfData.PBEventType = SI_PB_EVENT_READ_CNF;

    stCnfData.Storage     = pstMsg->ulStorage;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;
    }
#endif

    else
    {
        stCnfData.PBError = SI_PB_ErrorProc();
    }

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)
    {
        PB_WARNING_LOG("SI_PB_ReadProc: Proc Error");

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex1, pstMsg->usIndex2, &ucPBoffset);

    if(VOS_OK != ulResult) /*????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_ReadProc: SI_PB_LocateRecord Return Error");

        stCnfData.PBError = ulResult;

        (VOS_VOID)SI_PBCallback(&stCnfData);

        return VOS_ERR;
    }

    if(0 == pstMsg->usIndex1)
    {
        usIndexNum       = gastPBContent[ucPBoffset].usTotalNum;

        pstMsg->usIndex1 = 1;/*????????????????*/

        pstMsg->usIndex2 = gastPBContent[ucPBoffset].usTotalNum;
    }
    else
    {
        usIndexNum = (pstMsg->usIndex2 - pstMsg->usIndex1) + 1;/*????????????????????????*/
    }

    stCnfData.PBEvent.PBReadCnf.RecordNum = 1;

    /*????????????????????Balong????????????*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_XECC == pstMsg->ulStorage))
    {
        SI_PB_ReadXeccProc(usIndexNum, pstMsg->usIndex1, &stCnfData);

        gstPBReqUnit.enPBLock = PB_UNLOCK;

        return VOS_OK;
    }
#endif

    if (PB_ECC == pstMsg->ulStorage)
    {
        SI_PB_ReadEccProc(usIndexNum, pstMsg->usIndex1, &stCnfData);

        gstPBReqUnit.enPBLock = PB_UNLOCK;

        return VOS_OK;
    }

    pucContent = gastPBContent[ucPBoffset].pContent + ((pstMsg->usIndex1-1) * gastPBContent[ucPBoffset].ucRecordLen);

    stCnfData.PBLastTag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)     /*????????????????????????????*/
    {
        (VOS_VOID)memset_s((VOS_UINT8 *)&stCnfData.PBEvent.PBReadCnf,
                           sizeof(SI_PB_EVENT_READ_CNF_STRU),
                           0,
                           sizeof(SI_PB_EVENT_READ_CNF_STRU));

        SI_PB_TransPBFromate(&gastPBContent[ucPBoffset], (VOS_UINT16)(pstMsg->usIndex1+i), pucContent, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        pucContent += gastPBContent[ucPBoffset].ucRecordLen;/*????????????????????????*/

        if(SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBoffset].pIndex, gastPBContent[ucPBoffset].indexSize, pstMsg->usIndex1+i))/*????Index????SI_PB_CONTENT_VALID == stCnfData.PBEvent.PBReadCnf.PBRecord.ValidFlag) */
        {
            ulValidFlag = VOS_TRUE;
        }

        if(i == (usIndexNum-1))
        {
            stCnfData.PBLastTag = VOS_TRUE;
            stCnfData.PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
        }

        (VOS_VOID)SI_PBCallback(&stCnfData); /*????????????*/
    }

    return VOS_OK;
}



VOS_UINT32 SI_PB_SearchHandle(SI_PB_SEARCH_REQ_STRU *pMsg,
                                      SI_PB_EVENT_INFO_STRU *pstCnfData,
                                      VOS_UINT8 ucOffset)
{
    VOS_UINT16  usMatchRecordNum = 0;
    VOS_UINT16  i;

    pstCnfData->PBError     = TAF_ERR_NO_ERROR;
    pstCnfData->PBLastTag   = VOS_FALSE;
    gstPBReqUnit.enPBLock   = PB_LOCKED;

    for( i = 0 ; i < gastPBContent[ucOffset].usTotalNum ; i++ )
    {
        if(VOS_ERR == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                                  gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen),
                                                  gastPBContent[ucOffset].ucRecordLen))
        {
            continue;
        }
        else if (gastPBContent[ucOffset].ucRecordLen >= pMsg->ucLength)
        {
            if ((VOS_OK == VOS_MemCmp(pMsg->aucContent, gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen), pMsg->ucLength))
             || (0 == pMsg->ucLength))
            {
                SI_PB_TransPBFromate(&gastPBContent[ucOffset], (VOS_UINT16)(i+1),
                                        gastPBContent[ucOffset].pContent + (i * gastPBContent[ucOffset].ucRecordLen),
                                        &pstCnfData->PBEvent.PBSearchCnf.PBRecord);

                usMatchRecordNum++;
                (VOS_VOID)SI_PBCallback(pstCnfData);
            }
        }
        else
        {
            continue;
        }
    }

    if(0 == usMatchRecordNum)
    {
        return TAF_ERR_PB_NOT_FOUND;
    }

    pstCnfData->PBLastTag = VOS_TRUE;
    pstCnfData->PBEvent.PBSearchCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;

    (VOS_VOID)SI_PBCallback(pstCnfData);

    return TAF_ERR_NO_ERROR;
}


VOS_UINT32 SI_PB_SearchReq(SI_PB_SEARCH_REQ_STRU *pMsg,
                                   SI_PB_EVENT_INFO_STRU *pstCnfData,
                                   VOS_UINT8 ucOffset)
{
    VOS_UINT8  ucSendReqFlag = PB_REQ_NOT_SEND;
    VOS_UINT8  ucRecord;
    VOS_UINT32 ulResult;
    VOS_UINT16 usFileId;
    errno_t    ret;

    if (pMsg->ucLength <= sizeof(gstPBReqUnit.aucXDNContent))
    {
        ret = memcpy_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), pMsg->aucContent, pMsg->ucLength);

        PAM_PRINT_SECFUN_RESULT(ret);
    }
    else
    {
        PB_WARNING_LOG("SI_PB_SearchReq: Text string too long");

        return TAF_ERR_PARA_ERROR;
    }

    gstPBReqUnit.usCurIndex     = 1;

    gstPBReqUnit.usSearchLen    = pMsg->ucLength;

    gstPBReqUnit.usIndex2       = gastPBContent[ucOffset].usTotalNum;

    gstPBReqUnit.enPBEventType  = SI_PB_EVENT_SEARCH_CNF;

    gstPBReqUnit.ucEqualFlag    = VOS_FALSE;

    gstPBReqUnit.enPBStoateType = pMsg->ulStorage;

    while(gstPBReqUnit.usCurIndex <= gstPBReqUnit.usIndex2)
    {
        if (SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucOffset].pIndex,
                                                       gastPBContent[ucOffset].indexSize,
                                                       gstPBReqUnit.usCurIndex))
        {
            ucSendReqFlag = PB_REQ_SEND;
            break;
        }

        gstPBReqUnit.usCurIndex++;
    }

    if (PB_REQ_SEND == ucSendReqFlag)
    {
        if(SI_PB_STORAGE_SM == pMsg->ulStorage)   /*??????ADN????????????????*/
        {
            ulResult = SI_PB_CountADNRecordNum(gstPBReqUnit.usCurIndex, &usFileId, &ucRecord);
        }
        else                                                                    /*??????????????*/
        {
            ulResult = SI_PB_GetXDNFileID(pMsg->ulStorage, &usFileId);

            ucRecord = (VOS_UINT8)gstPBReqUnit.usCurIndex;
        }

        if(VOS_ERR == ulResult)         /*????????????*/
        {
            PB_WARNING_LOG("SI_PB_SearchReq: Get the XDN File ID and Record Number is Error");

            pstCnfData->PBError = TAF_ERR_PARA_ERROR;

            return TAF_ERR_PARA_ERROR;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        PB_WARNING_LOG("SI_PB_SearchReq: Content not found!");

        return TAF_ERR_PB_NOT_FOUND;
    }

    return TAF_ERR_NO_ERROR;
}



VOS_UINT32 SI_PB_SearchProc(PBMsgBlock *pMsg)
{
    SI_PB_EVENT_INFO_STRU   stCnfData;
    VOS_UINT32              ulResult;
    VOS_UINT8               ucOffset = 0;

    stCnfData.ClientId              = ((SI_PB_SEARCH_REQ_STRU*)pMsg)->usClient;
    stCnfData.OpId                  = ((SI_PB_SEARCH_REQ_STRU*)pMsg)->ucOpID;
    stCnfData.PBEventType           = SI_PB_EVENT_SEARCH_CNF;
    stCnfData.PBLastTag             = VOS_TRUE;

    if( TAF_ERR_NO_ERROR != (ulResult = SI_PB_ErrorProc()))/*??????????????????????????????*/
    {
        stCnfData.PBError  = ulResult;
        stCnfData.PBLastTag = VOS_TRUE;
        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(VOS_OK != SI_PB_FindPBOffset(((SI_PB_SEARCH_REQ_STRU*)pMsg)->ulStorage, &ucOffset))
    {
        stCnfData.PBError  = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData); /*????????????*/
    }

    if( VOS_NULL_PTR == gastPBContent[ucOffset].pContent )
    {
        if(TAF_ERR_NO_ERROR !=
           (ulResult = SI_PB_SearchReq( (SI_PB_SEARCH_REQ_STRU*)pMsg, &stCnfData, ucOffset ) ) )
        {
            stCnfData.PBError  = ulResult;

            (VOS_VOID)SI_PBCallback(&stCnfData); /*????????????*/
        }

        return VOS_OK;
    }

    if(TAF_ERR_NO_ERROR !=
            (ulResult = SI_PB_SearchHandle( (SI_PB_SEARCH_REQ_STRU*)pMsg, &stCnfData, ucOffset ) ) )
    {
        stCnfData.PBError  = ulResult;

        (VOS_VOID)SI_PBCallback(&stCnfData); /*????????????*/
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_SReadEMLProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32  ulEMLContentOffset;
    VOS_UINT8 *pucEMLContent = VOS_NULL_PTR;
    VOS_UINT8 ucEMLRecordNum;
    VOS_UINT8 ucType2EMLFileCnt;
    VOS_UINT8   i;

    /*Email,????Type1??2????????????USED, ??????????????
    Type1 ????????Index??
    Type2 ????Index??IAP??????????????????????????????????????????*/
    if(0 == gstPBCtrlInfo.ulEMLFileNum)
    {
        PB_WARNING_LOG("SI_PB_SReadEMLProc: No Valid Email Record");
        return VOS_OK;
    }

    if(PB_FILE_TYPE1 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)/*Email??????????*/
    {
        /* ????TYPE1??????????????????????usIndex + usOffset????????EMAIL?????????? */
        if ((usIndex + usOffset) > gstEMLContent.usTotalNum)
        {
            PB_WARNING_LOG("SI_PB_SReadEMLProc: Email Record Index Large than Total Number.");
            return VOS_OK;
        }

        pucEMLContent = gstEMLContent.pContent
            +((usIndex+(usOffset-1))*gstEMLContent.ucRecordLen);
    }
    else
    {
        if(VOS_NULL_PTR == gstIAPContent.pIAPContent)
        {
            PB_ERROR_LOG("SI_PB_SReadEMLProc: IAP Storage NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*Type2 Email??????????gstIAPContent.pIAPContent??????ADN ??????EML????????????*/
        /*lint -e679*/
        ucEMLRecordNum = gstIAPContent.pIAPContent[(((usIndex+usOffset)-1)*gstIAPContent.ucRecordLen)
                                                    +(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum - 1)];
        /*lint +e679*/

        if (VOS_OK != SI_PB_GetFileCntFromIndex(usIndex + usOffset, &ucType2EMLFileCnt))
        {
            PB_WARNING_LOG("SI_PB_SReadEMLProc: SI_PB_GetFileCntFromIndex Return Error.");
            return VOS_OK;
        }

        if ((gstPBCtrlInfo.astEMLInfo[ucType2EMLFileCnt - 1].ucRecordNum < ucEMLRecordNum)
            || (0xFF == ucEMLRecordNum)||(0 == ucEMLRecordNum))
        {
            PB_INFO_LOG("SI_PB_SReadEMLProc: No Email Record");
            return VOS_OK;
        }

        ulEMLContentOffset = (ucEMLRecordNum - 1)
                        * gstPBCtrlInfo.astEMLInfo[ucType2EMLFileCnt - 1].ucRecordLen;

        /* ????EMAIL?????????????????????????????????????????????????? */
        for (i = 0; i < (ucType2EMLFileCnt - 1); i++)
        {
            ulEMLContentOffset += gstPBCtrlInfo.astEMLInfo[i].ucRecordLen
                        * gstPBCtrlInfo.astEMLInfo[i].ucRecordNum;
        }

        pucEMLContent = gstEMLContent.pContent + ulEMLContentOffset;
    }

    SI_PB_TransEMLFromate(gstEMLContent.ucDataLen, pucEMLContent, pstRecord);

    return VOS_OK;
}


VOS_UINT32 SI_PB_SReadANRProc(VOS_UINT16 usIndex, VOS_UINT16 usOffset, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32                          ulAnrContentOffset;
    VOS_UINT32                          i;
    VOS_UINT8                           j;
    VOS_UINT8                          *pucANRContent = VOS_NULL_PTR;
    VOS_UINT8                           ucType2ANRRecord;
    VOS_UINT8                           ucType2ANRFileCnt;

    /*ANR,??????????????????????????USED??????????????????????????????????
    ????????????????????*/
    for(i = 0; i < gstPBCtrlInfo.ulANRStorageNum; i++)
    {
        if(VOS_NULL == gastANRContent[i].pContent)
        {
            PB_ERROR_LOG("SI_PB_SReadANRProc: Storage NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*??????Type2????ANR??????????IAP??????????????????*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {
            if(VOS_NULL == gstIAPContent.pIAPContent)
            {
                PB_ERROR_LOG("SI_PB_SReadANRProc: Storage NULL");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            /*lint -e679*/
            ucType2ANRRecord = gstIAPContent.pIAPContent[(((usIndex+usOffset)-1)*gstIAPContent.ucRecordLen)
                                    +(gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)];
            /*lint +e679*/

            if (VOS_OK != SI_PB_GetFileCntFromIndex(usIndex + usOffset, &ucType2ANRFileCnt))
            {
                PB_WARNING_LOG("SI_PB_SReadANRProc: SI_PB_GetFileCntFromIndex Return Error.");

                continue;
            }

            /*Index??????Type2 ANR????*/
            if ((gstPBCtrlInfo.astANRInfo[ucType2ANRFileCnt - 1][i].ucRecordNum < ucType2ANRRecord)
                ||(0 == ucType2ANRRecord)||(0xFF == ucType2ANRRecord))
            {
                PB_NORMAL_LOG("SI_PB_SReadANRProc: Empty Type2 ANR Or Invalid");

                continue;
            }

            ulAnrContentOffset = (ucType2ANRRecord - 1)*gastANRContent[i].ucRecordLen;

            for (j = 0; j < (ucType2ANRFileCnt - 1); j++)
            {
                ulAnrContentOffset += gstPBCtrlInfo.astANRInfo[j][i].ucRecordNum
                                        * gstPBCtrlInfo.astANRInfo[j][i].ucRecordLen;
            }

            pucANRContent = gastANRContent[i].pContent + ulAnrContentOffset;
        }
        else
        {
            /* ????TYPE1??????ANR????????????????usIndex + usOffset????????ANR?????????? */
            if ((usIndex + usOffset) > gastANRContent[i].usTotalNum)
            {
                continue;
            }

            pucANRContent = gastANRContent[i].pContent
                            +(((usIndex+usOffset)-1)*gastANRContent[i].ucRecordLen);
        }

        SI_PB_TransANRFromate((VOS_UINT8)i, pucANRContent, pstRecord);
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_SReadProc(PBMsgBlock *pMsg)
{
    SI_PB_READ_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT8                   ucPBoffset;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndexNum;
    VOS_UINT16                  i;
    VOS_UINT8                   *pucContent = VOS_NULL_PTR;
    VOS_UINT8                   *pucTempContent = VOS_NULL_PTR;
    VOS_UINT32                  ulValidFlag = VOS_FALSE;

    (VOS_VOID)memset_s((VOS_UINT8 *)&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));

    pstMsg = (SI_PB_READ_REQ_STRU*)pMsg;

    stCnfData.ClientId    = pstMsg->usClient;

    stCnfData.OpId        =  pstMsg->ucOpID;

    stCnfData.PBEventType = SI_PB_EVENT_SREAD_CNF;

    stCnfData.Storage     = pstMsg->ulStorage;

    if((0 == gstPBConfigInfo.ucSPBFlag)||(SI_PB_STORAGE_SM != pstMsg->ulStorage))
    {
        /*????Operation not allowed*/
        stCnfData.PBError = TAF_ERR_CMD_TYPE_ERROR;

        PB_WARNING_LOG("SI_PB_SReadProc: Proc is Not Allow");

        return SI_PBCallback(&stCnfData);
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)
    {
        PB_WARNING_LOG("SI_PB_SReadProc: Proc Error");

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex1, pstMsg->usIndex2, &ucPBoffset);

    if(VOS_OK != ulResult) /*????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_LocateRecord Return Error");

        stCnfData.PBError = ulResult;

        (VOS_VOID)SI_PBCallback(&stCnfData);

        return VOS_ERR;
    }

    if(0 == pstMsg->usIndex1)
    {
        usIndexNum       = gastPBContent[ucPBoffset].usTotalNum;

        pstMsg->usIndex1 = 1;/*????????????????*/

        pstMsg->usIndex2 = gastPBContent[ucPBoffset].usTotalNum;
    }
    else
    {
        usIndexNum = (pstMsg->usIndex2 - pstMsg->usIndex1) + 1;/*????????????????????????*/
    }

    if(VOS_NULL == gastPBContent[ucPBoffset].pContent)/*ADN????????????*/
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_SReadProc: The ADN Memory Error");

        return SI_PBCallback(&stCnfData);
    }

    pucContent = gastPBContent[ucPBoffset].pContent + ((pstMsg->usIndex1-1) * gastPBContent[ucPBoffset].ucRecordLen);

    stCnfData.PBLastTag = VOS_FALSE;

    for(i=0; i<usIndexNum; i++)     /*????????????????????????????*/
    {
        stCnfData.PBError = VOS_OK;

        (VOS_VOID)memset_s((VOS_UINT8 *)&stCnfData.PBEvent.PBReadCnf,
                           sizeof(SI_PB_EVENT_READ_CNF_STRU),
                           0,
                           sizeof(SI_PB_EVENT_READ_CNF_STRU));

        stCnfData.PBEvent.PBReadCnf.RecordNum = 1;

        stCnfData.PBEvent.PBReadCnf.PBRecord.Index = (VOS_UINT16)(pstMsg->usIndex1+i);

        /*????????????????????????????*/
        if(SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBoffset].pIndex, gastPBContent[ucPBoffset].indexSize, pstMsg->usIndex1+i))/*??Index??????????????*/
        {
            if(i == (usIndexNum-1))/*????????????????*/
            {
                stCnfData.PBError = ((VOS_TRUE == ulValidFlag)?TAF_ERR_NO_ERROR:TAF_ERR_PB_NOT_FOUND);
                stCnfData.PBLastTag = VOS_TRUE;

                return SI_PBCallback(&stCnfData);
            }

            continue;
        }

        ulValidFlag = VOS_TRUE;

        pucTempContent = pucContent + (i*gastPBContent[ucPBoffset].ucRecordLen);/*????????????????????????*/

        SI_PB_TransPBFromate(&gastPBContent[ucPBoffset], (VOS_UINT16)(pstMsg->usIndex1+i), pucTempContent, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        /*ANR,??????????????????????????USED??????????????????????????????????
        ????????????????????*/
        ulResult = SI_PB_SReadANRProc(pstMsg->usIndex1, i, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        if(VOS_OK != ulResult)
        {
            stCnfData.PBError = ulResult;

            PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_SReadANRProc Return Error");

            return SI_PBCallback(&stCnfData);
        }

        ulResult = SI_PB_SReadEMLProc(pstMsg->usIndex1, i, &stCnfData.PBEvent.PBReadCnf.PBRecord);

        if(VOS_OK != ulResult)
        {
            stCnfData.PBError = ulResult;

            PB_WARNING_LOG("SI_PB_SReadProc: SI_PB_SReadEMLProc Return Error");

            return SI_PBCallback(&stCnfData);
        }

        /*????????????????????????????????????True*/
        if(i == (usIndexNum-1))
        {
            stCnfData.PBLastTag = VOS_TRUE;
        }

        (VOS_VOID)SI_PBCallback(&stCnfData); /*????????????*/
    }

    return VOS_OK;
}


VOS_UINT32 SI_PBUpdateAGlobal(PBMsgBlock *pMsg)
{
    SI_PB_UPDATEGLOBAL_IND_STRU        *pstMsg = VOS_NULL_PTR;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32                          i;
    VOS_UINT_PTR                        TempAddr;
#endif

    if (pMsg->ulLength < (sizeof(SI_PB_UPDATEGLOBAL_IND_STRU) - VOS_MSG_HEAD_LENGTH))
    {
        (VOS_VOID)memset_s(&gstPBCtrlInfo,  sizeof(gstPBCtrlInfo), 0, sizeof(gstPBCtrlInfo));
        (VOS_VOID)memset_s(&gstPBConfigInfo,sizeof(gstPBConfigInfo), 0, sizeof(gstPBConfigInfo));
        (VOS_VOID)memset_s(gastPBContent, sizeof(gastPBContent),  0,  sizeof(gastPBContent));
        (VOS_VOID)memset_s(gastEXTContent, sizeof(gastEXTContent), 0, sizeof(gastEXTContent));
        (VOS_VOID)memset_s(gastANRContent, sizeof(gastANRContent), 0, sizeof(gastANRContent));
        (VOS_VOID)memset_s(&gstEMLContent, sizeof(gstEMLContent), 0, sizeof(gstEMLContent));
        (VOS_VOID)memset_s(&gstIAPContent, sizeof(gstIAPContent), 0, sizeof(gstIAPContent));
        (VOS_VOID)memset_s(&gstPBInitState, sizeof(gstPBInitState), 0, sizeof(gstPBInitState));

        PB_ERROR1_LOG("SI_PBUpdateAGlobal: incorrect msg", pMsg->ulLength);

        return VOS_ERR;
    }

    pstMsg = (SI_PB_UPDATEGLOBAL_IND_STRU*)pMsg;

    (VOS_VOID)memcpy_s(&gstPBCtrlInfo,  sizeof(gstPBCtrlInfo), &pstMsg->stPBCtrlInfo,   sizeof(gstPBCtrlInfo));
    (VOS_VOID)memcpy_s(&gstPBConfigInfo,sizeof(gstPBConfigInfo), &pstMsg->stPBConfigInfo, sizeof(gstPBConfigInfo));
    (VOS_VOID)memcpy_s(gastPBContent, sizeof(gastPBContent),  pstMsg->astPBContent,   sizeof(gastPBContent));
    (VOS_VOID)memcpy_s(gastEXTContent, sizeof(gastEXTContent), pstMsg->astEXTContent,  sizeof(gastEXTContent));
    (VOS_VOID)memcpy_s(gastANRContent, sizeof(gastANRContent), pstMsg->astANRContent,  sizeof(gastANRContent));
    (VOS_VOID)memcpy_s(&gstEMLContent, sizeof(gstEMLContent), &pstMsg->stEMLContent,   sizeof(gstEMLContent));
    (VOS_VOID)memcpy_s(&gstIAPContent, sizeof(gstIAPContent), &pstMsg->stIAPContent,   sizeof(gstIAPContent));
    (VOS_VOID)memcpy_s(&gstPBInitState, sizeof(gstPBInitState), &pstMsg->stPBInitState,  sizeof(gstPBInitState));

#if (VOS_LINUX == VOS_OS_VER)
    for (i=0; i<PB_CONTENT_BUTT; i++)
    {
        gastPBContent[i].pContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->astPBContentAddr[i].ulContentAddr;

        gastPBContent[i].pContent   = (VOS_UINT8 *)TempAddr;

        gastPBContent[i].pIndex     = VOS_NULL_PTR;

        TempAddr = pstMsg->astPBContentAddr[i].ulIndexAddr;

        gastPBContent[i].pIndex     = (VOS_UINT8 *)TempAddr;

        if(VOS_NULL_PTR != gastPBContent[i].pContent)
        {
            gastPBContent[i].pContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastPBContent[i].pContent);
        }
        if (VOS_NULL_PTR != gastPBContent[i].pIndex)
        {
            gastPBContent[i].pIndex     = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastPBContent[i].pIndex);
        }
    }

    for (i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        gastEXTContent[i].pExtContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->aulExtContentAddr[i];

        gastEXTContent[i].pExtContent   = (VOS_UINT8 *)TempAddr;

        if(VOS_NULL_PTR != gastEXTContent[i].pExtContent)
        {
            gastEXTContent[i].pExtContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastEXTContent[i].pExtContent);
        }
    }

    for (i=0; i<SI_PB_ANRMAX; i++)
    {
        gastANRContent[i].pContent   = VOS_NULL_PTR;

        TempAddr = pstMsg->aulANRContentAddr[i];

        gastANRContent[i].pContent   = (VOS_UINT8*)TempAddr;

        if(VOS_NULL_PTR != gastANRContent[i].pContent)
        {
            gastANRContent[i].pContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gastANRContent[i].pContent);
        }
    }

    gstEMLContent.pContent  = VOS_NULL_PTR;

    TempAddr = pstMsg->ulEMLContentAddr;

    gstEMLContent.pContent      = (VOS_UINT8*)TempAddr;

    if(VOS_NULL_PTR != gstEMLContent.pContent)
    {
        gstEMLContent.pContent  = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gstEMLContent.pContent);
    }

    gstIAPContent.pIAPContent   = VOS_NULL_PTR;

    TempAddr = pstMsg->ulIAPContentAddr;

    gstIAPContent.pIAPContent   = (VOS_UINT8*)TempAddr;

    if(VOS_NULL_PTR != gstIAPContent.pIAPContent)
    {
        gstIAPContent.pIAPContent   = (VOS_UINT8*)mdrv_phy_to_virt(MEM_DDR_MODE, gstIAPContent.pIAPContent);
    }
#endif

    return VOS_OK;
}


VOS_UINT32 SI_PBUpdateACurPB(PBMsgBlock *pMsg)
{
    SI_PB_SETPB_IND_STRU *pstMsg = VOS_NULL_PTR;

    pstMsg = (SI_PB_SETPB_IND_STRU*)pMsg;

    gstPBCtrlInfo.enPBCurType = pstMsg->enPBCurType;

    return VOS_OK;
}
#endif

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)||(defined(DMT)))

VOS_VOID SI_PB_InitStatusInd(USIMM_PB_INIT_STATUS_ENUM_UINT16 enPBInitStatus)
{
    USIMM_PBINIT_STATUS_IND_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (USIMM_PBINIT_STATUS_IND_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                          sizeof(USIMM_PBINIT_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PB_WARNING_LOG("SI_PB_InitStatusInd: VOS_AllocMsg is Failed");

        return ;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_PBINIT_STATUS_IND;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;
    pstMsg->enPBInitStatus              = enPBInitStatus;
    pstMsg->usRsv                       = VOS_NULL;

    (VOS_VOID)VOS_SendMsg(MAPS_PB_PID, pstMsg);

    return ;
}


VOS_UINT8 SI_PB_AlphaTagTruncation(SI_PB_RECORD_STRU *pstRecord, VOS_UINT8 ucOffset)
{
    VOS_UINT8  uctemp;
    VOS_UINT8  ucLen;

    /*??????????????0????????Copy??????0*/
    if (0 == pstRecord->ucAlphaTagLength)
    {
        PB_INFO_LOG("SI_PB_AlphaTagTruncation: The Name Len is 0");
        return 0;
    }

    if (SI_PB_ALPHATAG_TYPE_UCS2_80 == pstRecord->AlphaTagType)
    {
        uctemp = gastPBContent[ucOffset].ucNameLen\
                    - ((gastPBContent[ucOffset].ucNameLen - 1)%2);

        return (pstRecord->ucAlphaTagLength > uctemp)?uctemp:pstRecord->ucAlphaTagLength;
    }
    else if (SI_PB_ALPHATAG_TYPE_GSM == pstRecord->AlphaTagType)
    {
        if(pstRecord->ucAlphaTagLength > gastPBContent[ucOffset].ucNameLen)
        {
            ucLen = gastPBContent[ucOffset].ucNameLen;

            ucLen = (SI_PB_ALPHATAG_TRANSFER_TAG == pstRecord->AlphaTag[ucLen-1]) ? (ucLen-1) : (ucLen);
        }
        else
        {
            ucLen = pstRecord->ucAlphaTagLength;
        }

        return ucLen;
    }
    else/*????81??82????????????*/
    {
        /*????????????????*/
        uctemp = (pstRecord->ucAlphaTagLength > gastPBContent[ucOffset].ucNameLen)?\
                  gastPBContent[ucOffset].ucNameLen:pstRecord->ucAlphaTagLength;

        pstRecord->AlphaTag[1] =  uctemp - ((0x81 == pstRecord->AlphaTag[0])?3:4);

        return uctemp;
    }
}


VOS_UINT32 SI_PB_UpdataXDNFile(VOS_UINT8 ucPBOffset, VOS_UINT16 usFileId, VOS_UINT16 usExtFileId,
                                        VOS_UINT8 ucRecord,SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT8                   ucCopyLen;
    VOS_UINT8                   ucExtRecord;
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulXDNContentOffset;
    VOS_UINT32                  ulExtInfoNum;
    SI_PB_SETFILE_INFO_STRU     stUpdateReq;
    errno_t                     ret;

    (VOS_VOID)memset_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), 0xFF, sizeof(gstPBReqUnit.aucXDNContent));
    (VOS_VOID)memset_s(gstPBReqUnit.aucEXTContent, sizeof(gstPBReqUnit.aucEXTContent), 0xFF, sizeof(gstPBReqUnit.aucEXTContent));

    ucCopyLen = SI_PB_AlphaTagTruncation(pstRecord, ucPBOffset);

    ret = memcpy_s(gstPBReqUnit.aucXDNContent,
                   sizeof(gstPBReqUnit.aucXDNContent),
                   pstRecord->AlphaTag,
                   ucCopyLen);

    if (ret != EOK)
    {
        PB_WARNING_LOG("SI_PB_UpdataXDNFile: the input name length is too long.");

        return VOS_ERR;
    }

    /* ??????aucXDNContent????????????????????????NameLen????????????????????????????????????13???? */
    if ((sizeof(gstPBReqUnit.aucXDNContent) - 13) <= gastPBContent[ucPBOffset].ucNameLen)
    {
        PB_WARNING_LOG("SI_PB_UpdataXDNFile: the name length is too long.");

        return VOS_ERR;
    }

    if(pstRecord->NumberLength != 0)
    {
        gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+1] = pstRecord->NumberType;
    }

    if( ( pstRecord->NumberLength > SI_PB_NUM_LEN ) && ( 0xFFFF != usExtFileId ) )
    {
        SI_PB_AsciiToBcd(pstRecord->Number,
                         SI_PB_NUM_LEN,
                        &gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+2],
                         sizeof(gstPBReqUnit.aucXDNContent) - (gastPBContent[ucPBOffset].ucNameLen+2),
                        &ucCopyLen);

        gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen] = ucCopyLen + 1;

        ulXDNContentOffset = ( pstRecord->Index - 1 ) * gastPBContent[ucPBOffset].ucRecordLen;

        (ucPBOffset == PB_BDN_CONTENT)?\
                (ulXDNContentOffset += gastPBContent[ucPBOffset].ucRecordLen - 2):
                (ulXDNContentOffset += gastPBContent[ucPBOffset].ucRecordLen - 1);

        /* ????????????????????????????????????EXT???????? */
        ucExtRecord  = gastPBContent[ucPBOffset].pContent[ulXDNContentOffset];
        ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;

        /* ????XDN??????????????????EXT??????????????????????????EXT???? */
        if((0xFF == ucExtRecord)||(0 == ucExtRecord))
        {
            /* ????????????EXT????????????????EXT?????????????????????????????????????? */
            ulResult = SI_PB_FindUnusedExtRecord( gastEXTContent + ulExtInfoNum, &ucExtRecord, 1);
        }
        else
        {
            ulResult = VOS_OK;
        }

        if ((ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum)
            && (VOS_OK == ulResult))
        {
            SI_PB_AsciiToBcd(pstRecord->Number + SI_PB_NUM_LEN, \
                             (VOS_UINT8)(pstRecord->NumberLength - SI_PB_NUM_LEN),\
                             gstPBReqUnit.aucEXTContent+2,
                             sizeof(gstPBReqUnit.aucEXTContent) - 2,
                             &ucCopyLen);

            gstPBReqUnit.aucEXTContent[0] = SI_PB_ADDITIONAL_NUM;
            gstPBReqUnit.aucEXTContent[1] = ucCopyLen;

            stUpdateReq.pucEfContent    = gstPBReqUnit.aucEXTContent;
            stUpdateReq.ucRecordNum     = ucExtRecord;
            stUpdateReq.ulEfLen         = SI_PB_EXT_LEN;
            stUpdateReq.usEfId          = usExtFileId;

            ulResult = SI_PB_SetFileReq(&stUpdateReq);
        }

        /* ??????EXT??????????ADN??????????????????EXT????????????????????????????FF */
        if(VOS_OK != ulResult)
        {
            gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+13] = 0xFF;
        }
        else
        {
            gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+13] = ucExtRecord;
            gstPBReqUnit.usExtIndex = ucExtRecord;
        }

        stUpdateReq.pucEfContent    = gstPBReqUnit.aucXDNContent;
        stUpdateReq.ucRecordNum     = ucRecord;
        stUpdateReq.ulEfLen         = gastPBContent[ucPBOffset].ucRecordLen;
        stUpdateReq.usEfId          = usFileId;

        /* ????????XDN????????????????????EXT?????????????? */
        return SI_PB_SetFileReq(&stUpdateReq);
    }

    SI_PB_AsciiToBcd(pstRecord->Number,
                     pstRecord->NumberLength,
                    &gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen+2],
                     sizeof(gstPBReqUnit.aucXDNContent) - (gastPBContent[ucPBOffset].ucNameLen+2),
                    &ucCopyLen);

    if(0 != pstRecord->NumberLength)
    {
        gstPBReqUnit.aucXDNContent[gastPBContent[ucPBOffset].ucNameLen] = ucCopyLen + 1;
    }

    stUpdateReq.pucEfContent    = gstPBReqUnit.aucXDNContent;
    stUpdateReq.ucRecordNum     = ucRecord;
    stUpdateReq.ulEfLen         = gastPBContent[ucPBOffset].ucRecordLen;
    stUpdateReq.usEfId          = usFileId;

    return SI_PB_SetFileReq(&stUpdateReq);
}


VOS_UINT32 SI_PB_UpdataADN(SI_PB_RECORD_STRU        *pstRecord,
                                   SI_PB_SPBDATA_STRU       *pstSPBReq,
                                   VOS_UINT16               *pusExtUsedNum,
                                   SI_PB_SPB_UPDATE_STRU    *pstPBFid)
{
    VOS_UINT8  ucCopyLen;
    VOS_UINT8  ucNumberLen;
    VOS_UINT8  ucExtRecord;
    VOS_UINT16 *pusFileNum = VOS_NULL_PTR;
    VOS_UINT32 ulEXTContentOffset;
    VOS_UINT32 ulResult = VOS_OK;
    errno_t    ret;

    pusFileNum = &pstSPBReq->usFileNum;

    (VOS_VOID)memset_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), 0xFF, sizeof(gstPBReqUnit.aucXDNContent));

    ucCopyLen = SI_PB_AlphaTagTruncation(pstRecord, PB_ADN_CONTENT);

    ucCopyLen = (VOS_UINT8)PAM_GetMin(ucCopyLen, sizeof(gstPBReqUnit.aucXDNContent));

    /*??????????????????????????*/
    ret = memcpy_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), pstRecord->AlphaTag, ucCopyLen);

    PAM_PRINT_SECFUN_RESULT(ret);

    /*????ADN????*/
    if(0 != pstRecord->NumberLength)
    {
        gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucNameLen+1] = pstRecord->NumberType;

        ucNumberLen = (pstRecord->NumberLength > SI_PB_NUM_LEN)?SI_PB_NUM_LEN:pstRecord->NumberLength;

        /*??????????????????????????????*/
        SI_PB_AsciiToBcd(pstRecord->Number,
                         ucNumberLen,
                        &gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucNameLen+2],
                         sizeof(gstPBReqUnit.aucXDNContent) - (gastPBContent[PB_ADN_CONTENT].ucNameLen+2),
                        &ucCopyLen);

        gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucNameLen] = ucCopyLen + 1;
    }

    ulEXTContentOffset = ( pstRecord->Index - 1 ) * gastPBContent[PB_ADN_CONTENT].ucRecordLen;

    ulEXTContentOffset += gastPBContent[PB_ADN_CONTENT].ucRecordLen - 1;

    /* ????????????????????????????????????EXT???????? */
    ucExtRecord  = gastPBContent[PB_ADN_CONTENT].pContent[ulEXTContentOffset];
    ucExtRecord = ((ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum) ? (ucExtRecord) : 0xFF);

    (VOS_VOID)memset_s(gstPBReqUnit.aucEXTContent, sizeof(gstPBReqUnit.aucEXTContent), 0xFF, sizeof(gstPBReqUnit.aucEXTContent));

    /*ADN????????????*/
    if(pstRecord->NumberLength > SI_PB_NUM_LEN)
    {
        if ( VOS_NULL_PTR == gastEXTContent[PB_ADN_CONTENT].pExtContent)
        {
            /*????????*/
            /*Operation not allowed*/
            PB_WARNING_LOG("SI_PB_UpdataADN:Ext Content NULL");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*??????????????EXT????????????????????EXT????*/
        if(0xFF == ucExtRecord)
        {
            /* ????????????EXT????????????????EXT?????????????????????????????????????? */
            ulResult = SI_PB_FindUnusedExtRecord( &gastEXTContent[PB_ADN_CONTENT], &ucExtRecord, (VOS_UINT8)*pusExtUsedNum);

            (*pusExtUsedNum)++;
        }

        if(VOS_OK == ulResult)
        {
            SI_PB_AsciiToBcd(pstRecord->Number + SI_PB_NUM_LEN, \
                             (VOS_UINT8)(pstRecord->NumberLength - SI_PB_NUM_LEN),\
                             gstPBReqUnit.aucEXTContent+2,
                             sizeof(gstPBReqUnit.aucEXTContent) - 2,
                             &ucCopyLen);

            gstPBReqUnit.usExtIndex = ucExtRecord;
            gstPBReqUnit.aucEXTContent[0] = SI_PB_ADDITIONAL_NUM;
            gstPBReqUnit.aucEXTContent[1] = ucCopyLen;
            gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucRecordLen-1] = ucExtRecord;

            /*????????????EXT????????*/
            pstSPBReq->usFileID[*pusFileNum]  = pstPBFid->usExtFileId;
            pstSPBReq->usDataLen[*pusFileNum] = SI_PB_EXT_LEN;
            pstSPBReq->ucRecordNum[*pusFileNum] = ucExtRecord;
            pstSPBReq->pContent[*pusFileNum] = gstPBReqUnit.aucEXTContent;
            (*pusFileNum)++;
        }
        else
        {
            /*Buffer full*/
            PB_WARNING_LOG("SI_PB_UpdataADN:ADN Ext Number Full");
            return TAF_ERR_PB_STORAGE_FULL;
        }
    }
    else
    {
        /*??????????????????????????20????????????EXT????????*/
        if((0xFF != ucExtRecord)&&(0xFFFF != pstPBFid->usExtFileId))
        {
            gstPBReqUnit.aucEXTContent[0] = 0;
            gstPBReqUnit.usExtIndex = ucExtRecord;

            pstSPBReq->usFileID[*pusFileNum]  = pstPBFid->usExtFileId;
            pstSPBReq->usDataLen[*pusFileNum] = SI_PB_EXT_LEN;
            pstSPBReq->ucRecordNum[*pusFileNum] = ucExtRecord;
            pstSPBReq->pContent[*pusFileNum] = gstPBReqUnit.aucEXTContent;
            (*pusFileNum)++;
        }

        gstPBReqUnit.aucXDNContent[gastPBContent[PB_ADN_CONTENT].ucRecordLen-1] = 0xFF;
    }

    /*????????????ADN????????,??????EXT????????*/
    pstSPBReq->usFileID[*pusFileNum]  = pstPBFid->usADNFileId;
    pstSPBReq->ucRecordNum[*pusFileNum] = pstPBFid->ucRecordNum;
    pstSPBReq->usDataLen[*pusFileNum] = gastPBContent[PB_ADN_CONTENT].ucRecordLen;
    pstSPBReq->pContent[*pusFileNum] = gstPBReqUnit.aucXDNContent;
    (*pusFileNum)++;

    return VOS_OK;
}


VOS_UINT32 SI_PB_UpdataType2ANR(SI_PB_RECORD_STRU       *pstRecord,
                                            SI_PB_SPBDATA_STRU     *pstSPBReq,
                                            SI_PB_SPB_UPDATE_STRU  *pstPBFid,
                                            VOS_UINT32              i,
                                            VOS_UINT8              *pucFreeANRRecord)
{
    VOS_UINT32 ulType2ANROffset;
    errno_t    ret;

    if (0 == gstPBCtrlInfo.astADNInfo[0].ucRecordNum)
    {
        PB_WARNING_LOG("SI_PB_UpdataType2ANR:ucRecordNum is 0");

        return TAF_ERR_PB_WRONG_PARA;
    }

    if(VOS_NULL_PTR == gstIAPContent.pIAPContent)
    {
        PB_WARNING_LOG("SI_PB_UpdataType2ANR:IAP Content NULL");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    ulType2ANROffset = ((pstRecord->Index-1)*gstIAPContent.ucRecordLen)
            + (gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum - 1);

    if((0xFF == gstIAPContent.pIAPContent[ulType2ANROffset])
        &&(0 != pstRecord->AdditionNumber[i].NumberLength))
    {
        if(VOS_OK != SI_PB_GetFreeANRRecordNum(pstPBFid->ausANRFileId[i],
                     pucFreeANRRecord,
                     &pstSPBReq->usFileID[pstSPBReq->usFileNum]))
        {
            PB_WARNING_LOG("SI_PB_UpdataType2ANR:No Free ANR Record");
            return TAF_ERR_PB_STORAGE_FULL;
        }


        /*????????20??Type2????????*/
        if(sizeof(gstPBReqUnit.stSPBReq.aucIAPContent) < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_UpdataType2ANR:IAP ucRecordLen too long");

            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucIAPContent,
                       sizeof(gstPBReqUnit.stSPBReq.aucIAPContent),
                       &gstIAPContent.pIAPContent[(pstRecord->Index-1)*gstIAPContent.ucRecordLen],
                       gstIAPContent.ucRecordLen);

        PAM_PRINT_SECFUN_RESULT(ret);

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1] =
             *pucFreeANRRecord;

        /*??????????????????IAP????*/
        gstIAPContent.pIAPContent[ulType2ANROffset] = *pucFreeANRRecord;

        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = pstPBFid->ucRecordNum;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        pstSPBReq->usFileNum++;
    }
    /*??????????????????*/
    else if((0xFF == gstIAPContent.pIAPContent[ulType2ANROffset])
        &&(0 == pstRecord->AdditionNumber[i].NumberLength))
    {
        PB_INFO_LOG("SI_PB_UpdataType2ANR: The Record is not found");
        return TAF_ERR_PB_NOT_FOUND;
    }
    /*ANR????????????????????IAP??????????*/
    else if((0xFF != gstIAPContent.pIAPContent[ulType2ANROffset])
        &&(0 == pstRecord->AdditionNumber[i].NumberLength))
    {
        *pucFreeANRRecord = gstIAPContent.pIAPContent[ulType2ANROffset];

        /*????????20??Type2????????*/
        if(sizeof(gstPBReqUnit.stSPBReq.aucIAPContent) < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_DeleteHandleEmail:IAP ucRecordLen too long");

            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        if(VOS_OK != SI_PB_GetIAPFidFromANR(pstPBFid->ausANRFileId[i],
                               &pstSPBReq->usFileID[pstSPBReq->usFileNum]))
        {
            PB_WARNING_LOG("SI_PB_UpdataANR:No IAP");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucIAPContent,
                       sizeof(gstPBReqUnit.stSPBReq.aucIAPContent),
                      &gstIAPContent.pIAPContent[(pstRecord->Index-1)*gstIAPContent.ucRecordLen],
                       gstIAPContent.ucRecordLen);

        PAM_PRINT_SECFUN_RESULT(ret);

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1] = 0xFF;

        /*??????????????????IAP????*/
        gstIAPContent.pIAPContent[ulType2ANROffset] = 0xFF;

        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = pstPBFid->ucRecordNum;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        pstSPBReq->usFileNum++;
    }
    else
    {
        *pucFreeANRRecord = gstIAPContent.pIAPContent[ulType2ANROffset];
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_UpdateAnrExt(
    AnrUpdateProcPara                  *para,
    SI_PB_RECORD_STRU                  *record,
    SI_PB_SPBDATA_STRU                 *spbReq,
    VOS_UINT16                         *extUsedNum,
    SI_PB_SPB_UPDATE_STRU              *pbFid
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           extRecord;
    VOS_UINT16                         *fileNum = VOS_NULL_PTR;
    VOS_UINT32                          result;
    VOS_UINT8                           copyLen;

    i = para->index;
    extRecord = para->extRecord;

    fileNum = &spbReq->usFileNum;

    if (record->AdditionNumber[i].NumberLength > SI_PB_NUM_LEN)
    {
        if (gastEXTContent[PB_ADN_CONTENT].pExtContent == VOS_NULL_PTR)
        {
            /*????????*/
            /*Operation not allowed*/
            PB_WARNING_LOG("SI_PB_UpdateAnrExt:ANR Ext Content NULL");

            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        result = VOS_OK;

        /* ????XDN??????????????????EXT??????????????????????????EXT???? */
        if(extRecord == 0xFF)
        {
            /* ????????????EXT????????????????EXT?????????????????????????????????????? */
            result = SI_PB_FindUnusedExtRecord( &gastEXTContent[PB_ADN_CONTENT], &(extRecord), (VOS_UINT8)*extUsedNum);

            (*extUsedNum)++;
        }

        if (result == VOS_OK)
        {
            (VOS_VOID)memset_s(gstPBReqUnit.stSPBReq.aucANRExtContent[i], SI_PB_EXT_LEN, (VOS_CHAR)0xFF, SI_PB_EXT_LEN);

            SI_PB_AsciiToBcd(record->AdditionNumber[i].Number + SI_PB_NUM_LEN, \
                                (VOS_UINT8)(record->AdditionNumber[i].NumberLength - SI_PB_NUM_LEN),\
                                &gstPBReqUnit.stSPBReq.aucANRExtContent[i][2],
                                sizeof(gstPBReqUnit.stSPBReq.aucANRExtContent[i]) - 2,
                                &copyLen);

            gstPBReqUnit.stSPBReq.usANRExtIndex[i] = extRecord;
            gstPBReqUnit.stSPBReq.aucANRExtContent[i][0] = SI_PB_ADDITIONAL_NUM;
            gstPBReqUnit.stSPBReq.aucANRExtContent[i][1] = copyLen;
            gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen
                - ((PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)?3:1)] = extRecord;

            /*????????????EXT????????*/
            spbReq->usFileID[*fileNum]  = pbFid->usExtFileId;
            spbReq->usDataLen[*fileNum] = SI_PB_EXT_LEN;
            spbReq->ucRecordNum[*fileNum] = extRecord;
            spbReq->pContent[*fileNum] = gstPBReqUnit.stSPBReq.aucANRExtContent[i];
            spbReq->usFileNum++;
        }
        else
        {
            PB_WARNING_LOG("SI_PB_UpdateAnrExt:ANR Ext Buffer Full");

            return TAF_ERR_PB_STORAGE_FULL;
        }
    }
    else
    {
        /*??????????????????????????20????????????EXT????????*/
        if ((extRecord != 0xFF) && (pbFid->usExtFileId != 0xFFFF))
        {
            (VOS_VOID)memset_s(gstPBReqUnit.stSPBReq.aucANRExtContent[i], SI_PB_EXT_LEN, (VOS_CHAR)0xFF, SI_PB_EXT_LEN);

            gstPBReqUnit.stSPBReq.aucANRExtContent[i][0] = 0;
            gstPBReqUnit.stSPBReq.usANRExtIndex[i] = extRecord;

            spbReq->usFileID[*fileNum]  = pbFid->usExtFileId;
            spbReq->usDataLen[*fileNum] = SI_PB_EXT_LEN;
            spbReq->ucRecordNum[*fileNum] = extRecord;
            spbReq->pContent[*fileNum] = gstPBReqUnit.stSPBReq.aucANRExtContent[i];
            (*fileNum)++;
        }

        gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen
            - ((PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)?3:1)] = 0xFF;
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_UpdataANR(SI_PB_RECORD_STRU        *pstRecord,
                                    SI_PB_SPBDATA_STRU      *pstSPBReq,
                                    VOS_UINT16              *pusExtUsedNum,
                                    SI_PB_SPB_UPDATE_STRU   *pstPBFid)
{
    VOS_UINT32 i;
    VOS_UINT32 ulEXTContentOffset;
    VOS_UINT32 ulANROffset;
    VOS_UINT32 ulFileCnt;
    VOS_UINT32 ulResult = VOS_OK;
    VOS_UINT16 *pusFileId = VOS_NULL_PTR;
    VOS_UINT8  ucADNSfi = 0;
    VOS_UINT8  ucNumberLen;
    VOS_UINT8  ucCopyLen;
    VOS_UINT8  ucExtRecord;
    VOS_UINT8  ucFreeANRRecord;
    VOS_UINT32 copyLen;
    errno_t    ret;
    AnrUpdateProcPara para;

    pusFileId = &pstSPBReq->usFileNum;

    /*ANR??????????????????NV??????*/
    for(i = 0; i < gstPBConfigInfo.ucAnrMaxNum; i++)
    {
        /*??ANR??????????????*/
        if(0 == pstPBFid->ausANRFileId[i])
        {
            continue;
        }

        /*????Type2????ANR*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {
            ulResult = SI_PB_UpdataType2ANR(pstRecord, pstSPBReq, pstPBFid,i,&ucFreeANRRecord);

            if(VOS_OK != ulResult)
            {
                /*????ANR??????????*/
                if(TAF_ERR_PB_NOT_FOUND == ulResult)
                {
                    continue;
                }

                PB_ERROR_LOG("SI_PB_UpdataANR:UpdataType2ANR Error");
                return ulResult;
            }

            if(VOS_OK != SI_PB_GetADNSfi(&ucADNSfi, pstPBFid->usADNFileId))
            {
                /*????????*/
                PB_WARNING_LOG("SI_PB_UpdataANR: The SI_PB_GetADNSfi is not found SFI");
                return TAF_ERR_PB_STORAGE_OP_FAIL;
            }

            /*????????????????????????Type2 ANR????*/
            ulFileCnt = (pstRecord->Index-1)/gstPBCtrlInfo.astADNInfo[0].ucRecordNum;

            /*??????????????Type2 ANR??????????????????*/
            ulANROffset = (ulFileCnt*(gstPBCtrlInfo.astANRInfo[0][i].ucRecordNum*gstPBCtrlInfo.astANRInfo[0][i].ucRecordLen))
                          + ((ucFreeANRRecord-1)*gstPBCtrlInfo.astANRInfo[0][i].ucRecordLen);

            /*??????????????Type2 ANR??????????????????????????????????*/
            ulEXTContentOffset = ulANROffset + (gastANRContent[i].ucRecordLen - 3);
        }
        else
        {
            /*????????????????????????Type1 ANR????*/
            ucFreeANRRecord = pstPBFid->ucRecordNum;

            /*??????????????Type1 ANR??????????????????*/
            ulANROffset = (pstRecord->Index-1)*gastANRContent[i].ucRecordLen;

            /*??????????????Type1 ANR??????????????????????????????????*/
            ulEXTContentOffset = ulANROffset + (gastANRContent[i].ucRecordLen - 1);
        }

        copyLen = PAM_GetMin(gastANRContent[i].ucRecordLen, sizeof(gstPBReqUnit.stSPBReq.aucANRContent[i]));

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucANRContent[i],
                       sizeof(gstPBReqUnit.stSPBReq.aucANRContent[i]),
                      &gastANRContent[i].pContent[ulANROffset],
                       copyLen);
        PAM_PRINT_SECFUN_RESULT(ret);

        /*??????????*/
        if((0 != pstRecord->AdditionNumber[i].NumberLength)
           &&(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType))
        {
            gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen-2] = ucADNSfi;/*ADN SFI*/
            gstPBReqUnit.stSPBReq.aucANRContent[i][gastANRContent[i].ucRecordLen-1] = pstPBFid->ucRecordNum;
        }

        /*??ANR??????2??13??12????????????0xFF*/
        ret = memset_s(gstPBReqUnit.stSPBReq.aucANRContent[i] + 1,
                           sizeof(gstPBReqUnit.stSPBReq.aucANRContent[i]) - 1,
                           (VOS_CHAR)0xFF,
                           12);
        PAM_PRINT_SECFUN_RESULT(ret);

        /*????ANR????*/
        if(0xFF == gstPBReqUnit.stSPBReq.aucANRContent[i][0])
        {
            gstPBReqUnit.stSPBReq.aucANRContent[i][0] = 0;
        }

        gstPBReqUnit.stSPBReq.aucANRContent[i][2] = pstRecord->AdditionNumber[i].NumberType;

        ucNumberLen = (pstRecord->AdditionNumber[i].NumberLength>SI_PB_NUM_LEN)?SI_PB_NUM_LEN:pstRecord->AdditionNumber[i].NumberLength;

        SI_PB_AsciiToBcd(pstRecord->AdditionNumber[i].Number,
                         ucNumberLen,
                        &gstPBReqUnit.stSPBReq.aucANRContent[i][3],
                         sizeof(gstPBReqUnit.stSPBReq.aucANRContent[i]) - 3,
                        &ucCopyLen);

        gstPBReqUnit.stSPBReq.aucANRContent[i][1] = ucCopyLen + 1;

        /* ????????????????????????????????????EXT??????????????EXT???????????????? */

        ucExtRecord  = gastANRContent[i].pContent[ulEXTContentOffset];
        ucExtRecord = ((ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum) ? (ucExtRecord) : 0xFF);

        para.index = i;
        para.extRecord = ucExtRecord;

        /* ????ANR??EXT???? */
        ulResult = SI_PB_UpdateAnrExt(&para, pstRecord, pstSPBReq, pusExtUsedNum, pstPBFid);

        if (ulResult != VOS_OK)
        {
            return ulResult;
        }

        /*????????????ANR????????*/
        pstSPBReq->usFileID[*pusFileId]  = pstPBFid->ausANRFileId[i];
        pstSPBReq->ucRecordNum[*pusFileId] = ucFreeANRRecord;
        pstSPBReq->usDataLen[*pusFileId] = gastANRContent[i].ucRecordLen;
        pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucANRContent[i];
        (*pusFileId)++;
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_UpdateType2EML(
    SI_PB_RECORD_STRU                  *record,
    SI_PB_SPBDATA_STRU                 *spbReq,
    SI_PB_SPB_UPDATE_STRU              *pbFid
)
{
    VOS_UINT32                          type2EMLOffset;
    VOS_UINT16                         *fileNum = VOS_NULL_PTR;
    VOS_UINT8                           adnSfi;
    VOS_UINT8                           freeEMLRecord;
    errno_t                             ret;

    if (gstIAPContent.pIAPContent == VOS_NULL_PTR)
    {
        PB_WARNING_LOG("SI_PB_UpdateType2EML:IAP Content NULL");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    type2EMLOffset = ((record->Index-1)*gstIAPContent.ucRecordLen)
            + (gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum - 1);

    /*??????IAP??????????????????????????*/
    if (gstIAPContent.pIAPContent[type2EMLOffset] == 0)
    {
        gstIAPContent.pIAPContent[type2EMLOffset] = 0xFF;
    }

    fileNum = &spbReq->usFileNum;

    if ((gstIAPContent.pIAPContent[type2EMLOffset] == 0xFF) &&
        (record->Email.EmailLen != 0))
    {
        if(VOS_OK != SI_PB_GetFreeEMLRecordNum(pbFid->usEMLFileId,
                     &freeEMLRecord,&spbReq->usFileID[*fileNum]))
        {
            PB_WARNING_LOG("SI_PB_UpdateType2EML:No Free Email Record");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        /*??????????IAP????*/
        if(sizeof(gstPBReqUnit.stSPBReq.aucIAPContent) < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_UpdateType2EML:IAP ucRecordLen too long");

            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucIAPContent,
                       sizeof(gstPBReqUnit.stSPBReq.aucIAPContent),
                      &gstIAPContent.pIAPContent[(record->Index-1)*gstIAPContent.ucRecordLen],
                       gstIAPContent.ucRecordLen);

        PAM_PRINT_SECFUN_RESULT(ret);

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1] =
             freeEMLRecord;

        /*????????ANR????Type2????????????????????????????????????????IAP??????*/
        gstIAPContent.pIAPContent[type2EMLOffset] = freeEMLRecord;

        spbReq->ucRecordNum[*fileNum] = pbFid->ucRecordNum;
        spbReq->usDataLen[*fileNum] = gstIAPContent.ucRecordLen;
        spbReq->pContent[*fileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        (*fileNum)++;
    }
    else if((gstIAPContent.pIAPContent[type2EMLOffset] == 0xFF) &&
            (record->Email.EmailLen == 0))
    {
        PB_INFO1_LOG("SI_PB_UpdateType2EML:The Email is Null or Email Len is %d", (long)record->Email.EmailLen);
        return VOS_OK;
    }
    /*Email????????????????IAP??????????*/
    else if((gstIAPContent.pIAPContent[type2EMLOffset] != 0xFF) &&
            (record->Email.EmailLen == 0))
    {
        freeEMLRecord = gstIAPContent.pIAPContent[type2EMLOffset];

        /*??????????IAP????*/
        if(sizeof(gstPBReqUnit.stSPBReq.aucIAPContent) < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_UpdateType2EML:IAP ucRecordLen too long");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucIAPContent,
                       sizeof(gstPBReqUnit.stSPBReq.aucIAPContent),
                      &gstIAPContent.pIAPContent[(record->Index-1)*gstIAPContent.ucRecordLen],
                       gstIAPContent.ucRecordLen);

        PAM_PRINT_SECFUN_RESULT(ret);

        SI_PB_GetIAPFidFromEML(pbFid->usEMLFileId,&spbReq->usFileID[*fileNum]);

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1] = 0xFF;

        /*????????ANR????Type2????????????????????????????????????????IAP??????*/
        gstIAPContent.pIAPContent[type2EMLOffset] = 0xFF;

        spbReq->ucRecordNum[*fileNum] = pbFid->ucRecordNum;
        spbReq->usDataLen[*fileNum] = gstIAPContent.ucRecordLen;
        spbReq->pContent[*fileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        (*fileNum)++;
    }
    else
    {
        freeEMLRecord = gstIAPContent.pIAPContent[type2EMLOffset];
    }

    spbReq->ucRecordNum[*fileNum] = freeEMLRecord;

    if (SI_PB_GetADNSfi(&adnSfi, pbFid->usADNFileId) != VOS_OK)
    {
        /*????????*/
        PB_ERROR_LOG("SI_PB_UpdateType2EML:IAP ucRecordLen too long");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    /*??????????*/
    if(0 != record->Email.EmailLen)
    {
        gstPBReqUnit.stSPBReq.aucEMLContent[gstEMLContent.ucRecordLen-2] = adnSfi; /*ADN SFI*/
        gstPBReqUnit.stSPBReq.aucEMLContent[gstEMLContent.ucRecordLen-1] = pbFid->ucRecordNum;
    }

    return (VOS_UINT32)TAF_ERR_CODE_BUTT;
}


VOS_UINT32 SI_PB_UpdataEML(SI_PB_RECORD_STRU        *pstRecord,
                                    SI_PB_SPBDATA_STRU       *pstSPBReq,
                                    SI_PB_SPB_UPDATE_STRU    *pstPBFid)
{
    VOS_UINT16 *pusFileId = VOS_NULL_PTR;
    VOS_UINT8  ucCopyLen;
    VOS_UINT32 copyLen;
    VOS_UINT32 result;
    errno_t    ret;

    /*Email????????*/
    if(0 == pstPBFid->usEMLFileId)
    {
        if(0 == pstRecord->Email.EmailLen)
        {
            PB_NORMAL_LOG("SI_PB_UpdataEML:Needn't to Update EML");
            return VOS_OK;
        }

        PB_WARNING_LOG("SI_PB_UpdataEML:No Email Storage");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    pusFileId = &pstSPBReq->usFileNum;

    if(VOS_NULL_PTR == gstEMLContent.pContent)
    {
        PB_WARNING_LOG("SI_PB_UpdataEML:Email Content NULL");
        return TAF_ERR_PB_STORAGE_OP_FAIL;
    }

    copyLen = PAM_GetMin(gstEMLContent.ucRecordLen, SI_PB_EMAIL_MAX_LEN);

    ret = memset_s(gstPBReqUnit.stSPBReq.aucEMLContent, SI_PB_EMAIL_MAX_LEN, (VOS_CHAR)0xFF, copyLen);

    PAM_PRINT_SECFUN_RESULT(ret);

    if(PB_FILE_TYPE2 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)/*Type2*/
    {
        result = SI_PB_UpdateType2EML(pstRecord, pstSPBReq, pstPBFid);

        /* ??????VOS_OK?????????????????? */
        if ((VOS_UINT32)TAF_ERR_CODE_BUTT != result)
        {
            return result;
        }
    }
    else
    {
        pstSPBReq->ucRecordNum[*pusFileId] = pstPBFid->ucRecordNum;
    }

    ucCopyLen = ((VOS_UINT8)pstRecord->Email.EmailLen > gstEMLContent.ucDataLen)?gstEMLContent.ucDataLen:(VOS_UINT8)pstRecord->Email.EmailLen;

    if (VOS_NULL != ucCopyLen)
    {
        if(SI_PB_ALPHATAG_TRANSFER_TAG == pstRecord->Email.Email[ucCopyLen - 1])
        {
            pstRecord->Email.Email[ucCopyLen - 1] = 0xFF;
        }

        ucCopyLen = (VOS_UINT8)PAM_GetMin(ucCopyLen, sizeof(gstPBReqUnit.stSPBReq.aucEMLContent));

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucEMLContent, sizeof(gstPBReqUnit.stSPBReq.aucEMLContent), pstRecord->Email.Email, ucCopyLen);
        PAM_PRINT_SECFUN_RESULT(ret);
    }

    pstSPBReq->usDataLen[*pusFileId] = gstEMLContent.ucRecordLen;
    pstSPBReq->usFileID[*pusFileId] = pstPBFid->usEMLFileId;
    pstSPBReq->pContent[*pusFileId] = gstPBReqUnit.stSPBReq.aucEMLContent;

    (*pusFileId)++;

    return VOS_OK;
}


VOS_UINT32 SI_PB_UpdataSPBFile(SI_PB_SPB_UPDATE_STRU *pstPBFid,
                                        SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32            ulResult = VOS_OK;
    VOS_UINT16            usExtUsedNum = 1;
    SI_PB_SPBDATA_STRU    stSPBReq;/*????????????*/

    (VOS_VOID)memset_s((VOS_VOID*)(&stSPBReq), sizeof(SI_PB_SPBDATA_STRU), 0, sizeof(SI_PB_SPBDATA_STRU));

    /*????Email????,????NV????????????????????????*/
    if(gstPBConfigInfo.ucEmailFlag)
    {
        ulResult = SI_PB_UpdataEML(pstRecord,&stSPBReq,pstPBFid);

        if(VOS_OK != ulResult)
        {
            PB_WARNING_LOG("SI_PB_UpdataSPBFile:Update Email Fail");
            return ulResult;
        }
    }

    /*????ANR????*/
    ulResult = SI_PB_UpdataANR(pstRecord,&stSPBReq,&usExtUsedNum,pstPBFid);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_UpdataSPBFile:Update ANR Fail");
        return ulResult;
    }

    /*????ADN????*/
    ulResult = SI_PB_UpdataADN(pstRecord,&stSPBReq,&usExtUsedNum,pstPBFid);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_UpdataSPBFile:Update ADN Fail");
        return ulResult;
    }

    /*????USIMM????????????*/
    if (VOS_OK != SI_PB_SetSPBFileReq(&stSPBReq))
    {
        PB_WARNING_LOG("SI_PB_UpdataSPBFile: SI_PB_SetSPBFileReq Fail");
        return TAF_ERR_USIM_SIM_CARD_NOTEXIST;/*SIM Fail*/
    }

    return VOS_OK;
}


VOS_VOID SI_PB_DeleteHandleAnr(VOS_UINT16          usFileId,
                                        VOS_UINT16          usIndex,
                                        SI_PB_SPBDATA_STRU *pstSPBReq,
                                        VOS_UINT8           ucRecord)
{
    VOS_UINT32            i;
    VOS_UINT8             ucExtRecord;
    VOS_UINT8             ucANRRecord;
    VOS_UINT16            usANRFileId = 0;
    VOS_UINT32            ulRecordOffset;
    VOS_UINT32            ulType2ANRFileCnt;
    VOS_UINT32            ulXDNContentOffset;
    VOS_UINT8             aucContent[20] = {0}; /*??????????????F*/
    VOS_UINT32            copyLen;
    errno_t               ret;

    (VOS_VOID)memset_s(aucContent, sizeof(aucContent), 0xFF, sizeof(aucContent));/*??????????????*/

    for(i = 0; i < SI_PB_ANR_MAX; i++)
    {
        /*????ADN FID??ANR????????????????????????ANR??????FID*/
        (VOS_VOID)SI_PB_GetANRFidFromADN((VOS_UINT8)i,usFileId,&usANRFileId);

        if(0 == usANRFileId)/*??ANR????????????*/
        {
            continue;
        }

        /*Type2 ???? ANR????*/
        if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[0][i].enANRType)
        {
            ucANRRecord = gstIAPContent.pIAPContent[((usIndex-1)*gstIAPContent.ucRecordLen)
                            + (gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)];

            /*????ANR????????????????*/
            if(0xFF == ucANRRecord)
            {
                continue;
            }

            copyLen = PAM_GetMin(gstIAPContent.ucRecordLen, sizeof(gstPBReqUnit.stSPBReq.aucIAPContent));

            ret = memcpy_s(gstPBReqUnit.stSPBReq.aucIAPContent,
                           sizeof(gstPBReqUnit.stSPBReq.aucIAPContent),
                          &gstIAPContent.pIAPContent[(usIndex-1)*gstIAPContent.ucRecordLen],
                           copyLen);

            PAM_PRINT_SECFUN_RESULT(ret);

            /*??????????IAP????*/
            gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1] = 0xFF;

            /*??????????????????Email????Type2??????????????????????????????????*/
            gstIAPContent.pIAPContent[((usIndex-1)*gstIAPContent.ucRecordLen)
                                + (gstPBCtrlInfo.astANRInfo[0][i].ulANRTagNum-1)] = 0xFF;

            (VOS_VOID)SI_PB_GetIAPFidFromANR(usANRFileId,&pstSPBReq->usFileID[pstSPBReq->usFileNum]);

            pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = ucRecord;
            pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
            pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

            pstSPBReq->usFileNum++;

            /*????ANR??EXT????*/
            if (0 == gstPBCtrlInfo.astADNInfo[0].ucRecordNum)
            {
                ulType2ANRFileCnt = 0;
            }
            else
            {
                ulType2ANRFileCnt = (usIndex -1)/gstPBCtrlInfo.astADNInfo[0].ucRecordNum;
            }

            ulRecordOffset =  (ulType2ANRFileCnt*(gstPBCtrlInfo.astANRInfo[0][i].ucRecordNum*gastANRContent[i].ucRecordLen))
                                + ((ucANRRecord-1)*gastANRContent[i].ucRecordLen);

            ulXDNContentOffset = gastANRContent[i].ucRecordLen - 3;
        }
        else
        {
            ucANRRecord = ucRecord;

            /*????ANR??EXT????*/
            ulRecordOffset = (usIndex -1) * gastANRContent[i].ucRecordLen;

            ulXDNContentOffset = gastANRContent[i].ucRecordLen - 1;
        }

        /* ????ANR???????????????? */
        if (VOS_NULL_PTR == gastANRContent[i].pContent)
        {
            continue;
        }

        /*????????????????????????????????????EXT????????*/
        ucExtRecord  = gastANRContent[i].pContent[ulRecordOffset+ulXDNContentOffset];

        /*????????????ANR????????????????????????????EXT????????????EXT??????????????????????EXT????????*/
        if ( (ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum)
            && (0xFF != ucExtRecord) )
        {
            ret = memcpy_s(gstPBReqUnit.stSPBReq.aucANRExtContent[i], sizeof(gstPBReqUnit.stSPBReq.aucANRExtContent[i]), aucContent, SI_PB_EXT_LEN);

            PAM_PRINT_SECFUN_RESULT(ret);

            gstPBReqUnit.stSPBReq.aucANRExtContent[i][0] = 0;

            gstPBReqUnit.stSPBReq.usANRExtIndex[i] = ucExtRecord;

            pstSPBReq->usFileID[pstSPBReq->usFileNum]       = gastEXTContent[PB_ADN_CONTENT].usExtFileId;
            pstSPBReq->usDataLen[pstSPBReq->usFileNum]      = SI_PB_EXT_LEN;
            pstSPBReq->ucRecordNum[pstSPBReq->usFileNum]    = ucExtRecord;
            pstSPBReq->pContent[pstSPBReq->usFileNum]       = gstPBReqUnit.stSPBReq.aucANRExtContent[i];
            pstSPBReq->usFileNum++;
        }

        /*ANR??????????????????????????*/
        if(VOS_OK == SI_PB_CheckANRValidity(gastANRContent[i].pContent[ulRecordOffset], gastANRContent[i].pContent[ulRecordOffset + 1]))
        {
            copyLen = PAM_GetMin(gastANRContent[i].ucRecordLen, sizeof(gstPBReqUnit.stSPBReq.aucANRContent[i]));

            ret = memcpy_s(gstPBReqUnit.stSPBReq.aucANRContent[i], sizeof(gstPBReqUnit.stSPBReq.aucANRContent[i]), aucContent, copyLen);

            PAM_PRINT_SECFUN_RESULT(ret);

            /*????????????ANR????????*/
            pstSPBReq->usFileID[pstSPBReq->usFileNum]       = usANRFileId;
            pstSPBReq->ucRecordNum[pstSPBReq->usFileNum]    = ucANRRecord;
            pstSPBReq->usDataLen[pstSPBReq->usFileNum]      = gastANRContent[i].ucRecordLen;
            pstSPBReq->pContent[pstSPBReq->usFileNum]       = gstPBReqUnit.stSPBReq.aucANRContent[i];
            pstSPBReq->usFileNum++;
        }
    }
}



VOS_VOID SI_PB_DeleteHandleEmail(VOS_UINT16         usIndex,
                                          SI_PB_SPBDATA_STRU *pstSPBReq,
                                          VOS_UINT8           ucRecord,
                                          VOS_UINT16          usFileId)
{
    VOS_UINT16            usEMLFileId = 0;
    VOS_UINT16            usIAPFileid = 0;
    VOS_UINT32            ulType2EMLIndex;
    VOS_UINT8             ucEMLRecord;
    VOS_UINT8             *pucEMLContent = VOS_NULL_PTR;
    VOS_UINT8             aucContent[SI_PB_EMAIL_MAX_LEN] = {0}; /*??????????????F*/
    VOS_UINT32            ulFreeSize = 0;
    VOS_UINT32            copyLen;
    errno_t               ret;

    (VOS_VOID)memset_s(aucContent, sizeof(aucContent), 0xFF, sizeof(aucContent));/*??????????????*/

    (VOS_VOID)SI_PB_GetEMLFIdFromADN(&usEMLFileId, usFileId);

    if(0 == usEMLFileId)
    {
        PB_NORMAL_LOG("SI_PB_DeleteHandleEmail:No Email");
        return;
    }

    if(PB_FILE_TYPE2 == gstPBCtrlInfo.astEMLInfo[0].enEMLType)
    {
        ulType2EMLIndex = (usIndex-1)*gstIAPContent.ucRecordLen;

        ucEMLRecord = gstIAPContent.pIAPContent[ulType2EMLIndex+(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1)];

        if((0xFF == ucEMLRecord)||(0x00 == ucEMLRecord))
        {
            return;
        }

        /*????Refresh MEM???? */

        /*??????????IAP????*/
        if(sizeof(gstPBReqUnit.stSPBReq.aucIAPContent) < gstIAPContent.ucRecordLen)
        {
            PB_ERROR_LOG("SI_PB_DeleteHandleEmail:IAP ucRecordLen too long");

            return;
        }

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucIAPContent,
                       sizeof(gstPBReqUnit.stSPBReq.aucIAPContent),
                      &gstIAPContent.pIAPContent[ulType2EMLIndex],
                       gstIAPContent.ucRecordLen);

        PAM_PRINT_SECFUN_RESULT(ret);

        gstPBReqUnit.stSPBReq.aucIAPContent[gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1] = 0xFF;

        /*??????????????????Email??ANR????????????????????????????????????*/
        gstIAPContent.pIAPContent[ulType2EMLIndex+(gstPBCtrlInfo.astEMLInfo[0].ulEMLTagNum-1)] = 0xFF;

        (VOS_VOID)SI_PB_GetIAPFidFromEML(usEMLFileId,&usIAPFileid);

        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum] = ucRecord;
        pstSPBReq->usFileID[pstSPBReq->usFileNum]   = usIAPFileid;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum] = gstIAPContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum] = gstPBReqUnit.stSPBReq.aucIAPContent;

        pstSPBReq->usFileNum++;
    }
    else
    {
        ucEMLRecord = ucRecord;
    }

    if(VOS_OK != SI_PB_GetEMLRecord(&pucEMLContent, usEMLFileId, ucEMLRecord, &ulFreeSize))
    {
        PB_NORMAL_LOG("SI_PB_DeleteHandleEmail:Search Email Storge Fail");
        return;
    }

    if(0xFF != pucEMLContent[0])/*????Email*/
    {
        copyLen = PAM_GetMin(gstEMLContent.ucRecordLen, SI_PB_EMAIL_MAX_LEN);

        ret = memcpy_s(gstPBReqUnit.stSPBReq.aucEMLContent, sizeof(gstPBReqUnit.stSPBReq.aucEMLContent), aucContent, copyLen);

        PAM_PRINT_SECFUN_RESULT(ret);

        /*????????????EML????????*/
        pstSPBReq->usFileID[pstSPBReq->usFileNum]       = usEMLFileId;
        pstSPBReq->ucRecordNum[pstSPBReq->usFileNum]    = ucEMLRecord;
        pstSPBReq->usDataLen[pstSPBReq->usFileNum]      = gstEMLContent.ucRecordLen;
        pstSPBReq->pContent[pstSPBReq->usFileNum]       = gstPBReqUnit.stSPBReq.aucEMLContent;
        pstSPBReq->usFileNum++;
    }

    return;
}


VOS_UINT32 SI_PB_DeleteHandle(VOS_UINT16 usFileId, VOS_UINT8 ucRecord,
                                      VOS_UINT8 ucOffset,VOS_UINT16 usIndex)
{
    VOS_UINT16            usExtFileId;
    VOS_UINT8             ucExtRecord;
    VOS_UINT32            ulExtInfoNum;
    VOS_UINT8             *pucRecord = VOS_NULL_PTR;
    VOS_UINT8             ucRecordLen;
    VOS_UINT32            ulRecordOffset;
    VOS_UINT32            ulResult = VOS_OK;
    SI_PB_SPBDATA_STRU    stSPBReq = {{0}};/*????????????*/
    VOS_UINT8             aucContent[242] = {0}; /*??????????????F*/
    errno_t               ret;

    (VOS_VOID)memset_s(aucContent, sizeof(aucContent), 0xFF, sizeof(aucContent));/*??????????????*/

    (VOS_VOID)memset_s((VOS_VOID*)(&stSPBReq), sizeof(SI_PB_SPBDATA_STRU), 0, sizeof(SI_PB_SPBDATA_STRU));

    /*XDN ?? EXT????*/
    ucRecordLen = gastPBContent[ucOffset].ucRecordLen;
    ulRecordOffset = (usIndex -1) * ucRecordLen;
    pucRecord = gastPBContent[ucOffset].pContent + ulRecordOffset;

    /*??????????????????????????ADN????????*/
    if((1 == gstPBConfigInfo.ucSPBFlag)&&(PB_ADN_CONTENT == ucOffset))
    {
        /*ANR ?? EXT????*/
        SI_PB_DeleteHandleAnr(usFileId, usIndex, &stSPBReq, ucRecord);

        /*Email ????*/
        SI_PB_DeleteHandleEmail(usIndex, &stSPBReq, ucRecord, usFileId);

        ulResult = SI_PB_CheckContentValidity(&gastPBContent[ucOffset], pucRecord, gastPBContent[ucOffset].ucRecordLen);
    }

    ucExtRecord  = ((ucOffset == PB_BDN_CONTENT)?pucRecord[ucRecordLen - 2]:pucRecord[ucRecordLen - 1]);
    ulExtInfoNum = gastPBContent[ucOffset].ulExtInfoNum;
    usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    if((ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum)
        &&(0xFF != ucExtRecord )&&(0 != ucExtRecord)&&(0xFFFF != usExtFileId))
    {
        gstPBReqUnit.usExtIndex = ucExtRecord;

        ret = memcpy_s(gstPBReqUnit.aucEXTContent, sizeof(gstPBReqUnit.aucEXTContent), aucContent, SI_PB_EXT_LEN);
        PAM_PRINT_SECFUN_RESULT(ret);

        gstPBReqUnit.aucEXTContent[0] = 0;

        stSPBReq.usFileID[stSPBReq.usFileNum]  = usExtFileId;
        stSPBReq.usDataLen[stSPBReq.usFileNum] = SI_PB_EXT_LEN;
        stSPBReq.ucRecordNum[stSPBReq.usFileNum] = ucExtRecord;
        stSPBReq.pContent[stSPBReq.usFileNum] = gstPBReqUnit.aucEXTContent;
        stSPBReq.usFileNum++;
    }

    /*????????????????????????????????*/
    if(VOS_OK == ulResult)
    {
        ucRecordLen = (VOS_UINT8)PAM_GetMin(ucRecordLen, sizeof(gstPBReqUnit.aucXDNContent));

        ret = memcpy_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), aucContent, ucRecordLen);
        PAM_PRINT_SECFUN_RESULT(ret);

        stSPBReq.usFileID[stSPBReq.usFileNum]  = usFileId;
        stSPBReq.usDataLen[stSPBReq.usFileNum] = ucRecordLen;
        stSPBReq.ucRecordNum[stSPBReq.usFileNum] = ucRecord;
        stSPBReq.pContent[stSPBReq.usFileNum] = gstPBReqUnit.aucXDNContent;
        stSPBReq.usFileNum++;
    }

    /*????USIMM????????????*/
    if (VOS_OK != SI_PB_SetSPBFileReq(&stSPBReq))
    {
        return TAF_ERR_USIM_SIM_CARD_NOTEXIST;/*SIM Fail*/
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_QueryProc(PBMsgBlock *pMsg)
{
    SI_PB_QUERY_REQ_STRU *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT8             ucPBOffset;
    VOS_UINT16            usUsedNum;

    pstMsg = (SI_PB_QUERY_REQ_STRU*)pMsg;

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*????????????????????*/

    ulResult = SI_PB_FindPBOffset(pstMsg->ulStorage, &ucPBOffset);/*??????????????????*/

    stCnfData.ClientId          = pstMsg->usClient;        /*????????????????????????*/
    stCnfData.OpId              = pstMsg->ucOpID;
    stCnfData.PBEventType       = SI_PB_EVENT_QUERY_CNF;
    stCnfData.Storage           = pstMsg->ulStorage;

    if ( TAF_ERR_NO_ERROR != ulResult )
    {
        PB_WARNING_LOG("SI_PB_QUERYProc: Find the PhoneBook Content is Error");

        stCnfData.PBError = TAF_ERR_PB_NOT_FOUND;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_QUERYProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if( PB_INIT_FINISHED != gstPBInitState.enPBInitStep )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(PB_INITIALISED != gastPBContent[ucPBOffset].enInitialState)
    {
        PB_WARNING_LOG("SI_PB_QueryProc: Not Init.");

        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    if(PB_ADN_CONTENT == ucPBOffset)
    {
        usUsedNum = (VOS_UINT16)gstPBCtrlInfo.ulTotalUsed;
    }
    else
    {
        usUsedNum = gastPBContent[ucPBOffset].usUsedNum;
    }

    stCnfData.PBEvent.PBQueryCnf.InUsedNum    = usUsedNum;
    stCnfData.PBEvent.PBQueryCnf.TotalNum     = gastPBContent[ucPBOffset].usTotalNum;
    stCnfData.PBEvent.PBQueryCnf.TextLen      = gastPBContent[ucPBOffset].ucNameLen;
    stCnfData.PBEvent.PBQueryCnf.NumLen       = gastPBContent[ucPBOffset].ucNumberLen;
    stCnfData.PBEvent.PBQueryCnf.EMAILTextLen = gstEMLContent.ucDataLen;
    stCnfData.PBEvent.PBQueryCnf.ANRNumberLen = gastANRContent[0].ucNumberLen;

    return SI_PBCallback(&stCnfData);/*????????????*/
}


VOS_VOID SI_PB_SendSetCurPB(VOS_VOID)
{
    SI_PB_SETPB_IND_STRU *pstMsg = VOS_NULL_PTR;

    pstMsg = (SI_PB_SETPB_IND_STRU*)VOS_AllocMsg(MAPS_PB_PID,
                                sizeof(SI_PB_SETPB_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)  /*??????????????????*/
    {
        return;
    }

    pstMsg->ulReceiverPid = ACPU_PID_PB;
    pstMsg->ulMsgName     = SI_PB_UPDATE_CURPB;
    pstMsg->enPBCurType   = gstPBCtrlInfo.enPBCurType; /* ???????????????????????? */

    if(VOS_OK != VOS_SendMsg(MAPS_PB_PID, pstMsg))
    {
        PB_ERROR_LOG("SI_PB_SendSetCurPB: Send msg Error");
    }

    return;
}


VOS_UINT32 SI_PB_SetProc(PBMsgBlock *pMsg)
{
    SI_PB_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT8             ucPBOffset;

    pstMsg = (SI_PB_SET_REQ_STRU*)pMsg;

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*??????????????*/

    stCnfData.ClientId          = pstMsg->usClient;        /*????????????????????????*/
    stCnfData.OpId              = pstMsg->ucOpID;
    stCnfData.PBEventType       = SI_PB_EVENT_SET_CNF;
    stCnfData.Storage           = pstMsg->ulStorage;

    ulResult = SI_PB_FindPBOffset(stCnfData.Storage, &ucPBOffset);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        PB_WARNING_LOG("SI_PB_SetProc: Find the PhoneBook Content is Error");

        return SI_PBCallback(&stCnfData);                   /*????????????*/
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_SetProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if( PB_INIT_FINISHED != gstPBInitState.enPBInitStep )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(PB_INITIALISED != gastPBContent[ucPBOffset].enInitialState)
    {
        PB_WARNING_LOG("SI_PB_SetProc: Not Init.");

        stCnfData.PBError = TAF_ERR_SIM_BUSY;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    stCnfData.PBEvent.PBSetCnf.InUsedNum      = gastPBContent[ucPBOffset].usUsedNum;
    stCnfData.PBEvent.PBSetCnf.TotalNum       = gastPBContent[ucPBOffset].usTotalNum;
    stCnfData.PBEvent.PBSetCnf.TextLen        = gastPBContent[ucPBOffset].ucNameLen;
    stCnfData.PBEvent.PBSetCnf.NumLen         = gastPBContent[ucPBOffset].ucNumberLen;
    stCnfData.PBEvent.PBSetCnf.ANRNumberLen   = gastANRContent[0].ucNumberLen;
    stCnfData.PBEvent.PBQueryCnf.EMAILTextLen = gstEMLContent.ucDataLen;

    gstPBCtrlInfo.enPBCurType = pstMsg->ulStorage;      /*????????????????????*/

    SI_PB_SendSetCurPB();

    return SI_PBCallback(&stCnfData);                   /*????????????*/
}


VOS_UINT32 SI_PB_FindFreeIndex(VOS_UINT8 ucPBOffset, VOS_UINT16 *pusIndex)
{
    VOS_UINT32 i;

    for(i=1; i<=gastPBContent[ucPBOffset].usTotalNum; i++)/*??????????????????????????*/
    {
        if(SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex, gastPBContent[ucPBOffset].indexSize, i))
        {
            break;
        }
    }

    if(i > gastPBContent[ucPBOffset].usTotalNum) /*????????*/
    {
        return TAF_ERR_PB_STORAGE_FULL;/*????????????*/
    }

    *pusIndex = (VOS_UINT16)i;

    return VOS_OK;
}


VOS_UINT32 SI_PB_AddProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU    *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT16            usFileId;
    VOS_UINT16            usExtFileId = 0xFFFF;
    VOS_UINT8             ucRecord;
    VOS_UINT8             ucPBOffset;
    VOS_UINT16            i;
    VOS_UINT32            ulExtInfoNum;

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*??????????????*/

    stCnfData.ClientId      = pstMsg->usClient;    /*????????????????????*/
    stCnfData.OpId          = pstMsg->ucOpID;
    stCnfData.PBEventType   = SI_PB_EVENT_ADD_CNF;
    stCnfData.Storage       = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    /*????????????????????*/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#endif

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Proc Error");

        return SI_PBCallback(&stCnfData);       /*????????????*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)/*????????????*/
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Content is NULL");
        stCnfData.PBError = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData);       /*????????????*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    /*????????????*/
    ulResult = SI_PB_FindFreeIndex(ucPBOffset, &i);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    if(SI_PB_STORAGE_SM == pstMsg->ulStorage)   /*??????ADN????????????????*/
    {
        ulResult = SI_PB_CountADNRecordNum(i, &usFileId, &ucRecord);
    }
    else                                                                    /*??????????????*/
    {
        ulResult = SI_PB_GetXDNFileID(pstMsg->ulStorage, &usFileId);

        ucRecord = (VOS_UINT8)i;
    }

    if(VOS_ERR == ulResult)         /*????????????*/
    {
        PB_WARNING_LOG("SI_PB_ADDProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;
    usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;
    pstMsg->stRecord.Index  = i;

    ulResult = SI_PB_UpdataXDNFile(ucPBOffset, usFileId, usExtFileId,
                                    ucRecord, &pstMsg->stRecord);/*, (VOS_UINT32)SI_PB_ADD_REQ);????????????API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_ADDProc: SI_PB_UpdataXDNFile is Error");

        stCnfData.PBError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBEventType     = SI_PB_EVENT_ADD_CNF;    /*????????????*/

    gstPBReqUnit.enPBStoateType    = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID            = pstMsg->ucOpID;

    gstPBReqUnit.usClientID        = pstMsg->usClient;

    gstPBReqUnit.usIndex1          = i;

    return VOS_OK;
}


VOS_UINT32 SI_PB_GetANRInfo(SI_PB_ADDITION_NUM_STRU *pstANRNum,
                                    VOS_UINT16 usADNFid,
                                    VOS_UINT16 *pusANRFileId)
{
    VOS_UINT16 i;

    /*????????????????????FID????*/
    for(i = 0; i < gstPBConfigInfo.ucAnrMaxNum; i++)
    {
        if((0 < pstANRNum[i].NumberLength)&&(i >= gstPBCtrlInfo.ulANRStorageNum))
        {
            PB_WARNING_LOG("SI_PB_GetANRInfo:Not Allowed");

            return TAF_ERR_PB_STORAGE_OP_FAIL;/*????????????*/
        }

        if(pstANRNum[i].NumberLength > gastANRContent[i].ucNumberLen)
        {
            PB_WARNING_LOG("SI_PB_GetANRInfo:Para Wrong");

            return TAF_ERR_PB_DIAL_STRING_TOO_LONG;
        }

        pusANRFileId[i] = 0;

        (VOS_VOID)SI_PB_GetANRFidFromADN((VOS_UINT8)i, usADNFid, &pusANRFileId[i]);/*????ADN FID????ANR FID*/

        if((0 == pusANRFileId[i])&&(0 != pstANRNum[i].NumberLength))
        {
            PB_WARNING_LOG("SI_PB_GetANRInfo:No ANR");
            return TAF_ERR_PB_STORAGE_OP_FAIL;
        }
    }

    return VOS_OK;
}


VOS_UINT32 SI_PB_CheckSAddPara(VOS_UINT32 storage)
{
    VOS_UINT32  errType;

    if ((gstPBConfigInfo.ucSPBFlag == 0) || (storage != SI_PB_STORAGE_SM))
    {
        /*????Operation not allowed*/
        return TAF_ERR_CMD_TYPE_ERROR;
    }

    errType = SI_PB_ErrorProc();

    if ((errType == TAF_ERR_NO_ERROR) &&
        (gstPBInitState.enPBInitStep != PB_INIT_FINISHED))
    {
        errType = TAF_ERR_SIM_BUSY;
    }

    return errType;
}


VOS_UINT32 SI_PB_SAddProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU    *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU stCnfData;
    VOS_UINT32            ulResult;
    VOS_UINT8             ucRecord;
    VOS_UINT8             ucPBOffset;
    VOS_UINT16            usIndex;
    VOS_UINT32            ulExtInfoNum;
    SI_PB_SPB_UPDATE_STRU stSPBFid;

    (VOS_VOID)memset_s(&stSPBFid, sizeof(stSPBFid), 0, sizeof(stSPBFid));

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*??????????????*/

    stCnfData.ClientId      = pstMsg->usClient;    /*????????????????????*/
    stCnfData.OpId          = pstMsg->ucOpID;
    stCnfData.PBEventType   = SI_PB_EVENT_SADD_CNF;
    stCnfData.Storage       = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_CheckSAddPara(pstMsg->ulStorage);

    if (TAF_ERR_NO_ERROR != stCnfData.PBError)/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_SAddProc: SI_PB_CheckSAddPara Error");

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);
    }

    if(VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)/*????????????*/
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Content is NULL");
        stCnfData.PBError = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData);
    }


    /*????????????*/
    ulResult = SI_PB_FindFreeIndex(ucPBOffset, &usIndex);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    /*??????????????Index??*/
    pstMsg->stRecord.Index = usIndex;

    /*ADN??????FID????????????*/
    ulResult = SI_PB_CountADNRecordNum(usIndex, &stSPBFid.usADNFileId, &ucRecord);

    if(VOS_ERR == ulResult)/*????????*/
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    /*????????????????????ID????*/
    ulResult = SI_PB_GetANRInfo(pstMsg->stRecord.AdditionNumber,stSPBFid.usADNFileId,stSPBFid.ausANRFileId);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: Get the ANR Info Fail");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    /*Email ????FID????,????NV????????????????????????*/
    if(gstPBConfigInfo.ucEmailFlag)
    {
        if(0 < pstMsg->stRecord.Email.EmailLen)
        {
            (VOS_VOID)SI_PB_GetEMLFIdFromADN(&stSPBFid.usEMLFileId,stSPBFid.usADNFileId);

            if (0 == stSPBFid.usEMLFileId)
            {
                PB_WARNING_LOG("SI_PB_SModifyProc:No Email");

                stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

                return SI_PBCallback(&stCnfData);
            }
        }
    }

    /*EXT ????FID????*/
    ulExtInfoNum          = gastPBContent[ucPBOffset].ulExtInfoNum;
    stSPBFid.usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    gstPBReqUnit.enPBLock = PB_LOCKED;

    stSPBFid.ucRecordNum = ucRecord;

    ulResult = SI_PB_UpdataSPBFile(&stSPBFid,&pstMsg->stRecord);/*??????????????API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SAddProc: SI_PB_UpdataXDNFile is Error");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBEventType     = SI_PB_EVENT_ADD_CNF;    /*????????????*/

    gstPBReqUnit.enPBStoateType    = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID            = pstMsg->ucOpID;

    gstPBReqUnit.usClientID        = pstMsg->usClient;

    gstPBReqUnit.usIndex1          = usIndex;

    return VOS_OK;
}


VOS_UINT32 SI_PB_ModifyProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU     *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU  stCnfData;
    VOS_UINT32             ulResult;
    VOS_UINT16             usFileId;
    VOS_UINT16             usExtFileId = 0xFFFF;
    VOS_UINT8              ucRecord;
    VOS_UINT8              ucPBOffset;
    VOS_UINT32             ulExtInfoNum;

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*??????????????*/

    stCnfData.ClientId     = pstMsg->usClient;    /*????????????????????*/
    stCnfData.OpId         = pstMsg->ucOpID;
    stCnfData.PBEventType  = SI_PB_EVENT_MODIFY_CNF;
    stCnfData.Storage      = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    /*????????????????????*/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#endif

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)  /*??????????????????*/
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    if(SI_PB_STORAGE_SM == pstMsg->ulStorage)/*????????ADN??????????????*/
    {
        ulResult = SI_PB_CountADNRecordNum(pstMsg->stRecord.Index, &usFileId, &ucRecord);
    }
    else                                                            /*??????????????*/
    {
        ulResult = SI_PB_GetXDNFileID(pstMsg->ulStorage, &usFileId);

        ucRecord = (VOS_UINT8)pstMsg->stRecord.Index;
    }

    if(VOS_ERR == ulResult)                         /*????????*/
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;
    usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    ulResult = SI_PB_UpdataXDNFile(ucPBOffset, usFileId, usExtFileId, ucRecord, &pstMsg->stRecord);/*??????????????API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_ModifyProc: SI_PB_UpdataXDNFile is Error");

        stCnfData.PBError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBEventType          = SI_PB_EVENT_MODIFY_CNF;/*????????????????????????*/

    gstPBReqUnit.enPBStoateType         = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID                 = pstMsg->ucOpID;

    gstPBReqUnit.usClientID             = pstMsg->usClient;

    gstPBReqUnit.usIndex1               = pstMsg->stRecord.Index;

    return VOS_OK;
}


VOS_UINT32 SI_PB_SModifyProc(PBMsgBlock *pMsg)
{
    SI_PB_ADD_REP_STRU     *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU   stCnfData;
    VOS_UINT32              ulResult;
    VOS_UINT8               ucRecord;
    VOS_UINT8               ucPBOffset;
    VOS_UINT32              ulExtInfoNum;
    SI_PB_SPB_UPDATE_STRU   stSPBFid;

    (VOS_VOID)memset_s(&stSPBFid, sizeof(stSPBFid), 0, sizeof(stSPBFid));

    pstMsg = (SI_PB_ADD_REP_STRU *)pMsg;

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*??????????????*/

    stCnfData.ClientId     = pstMsg->usClient;    /*????????????????????*/
    stCnfData.OpId         = pstMsg->ucOpID;
    stCnfData.PBEventType  = SI_PB_EVENT_SMODIFY_CNF;
    stCnfData.Storage      = pstMsg->ulStorage;

    if((0 == gstPBConfigInfo.ucSPBFlag)||(SI_PB_STORAGE_SM != pstMsg->ulStorage))
    {
        /*????Operation not allowed*/
        stCnfData.PBError = TAF_ERR_CMD_TYPE_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->stRecord.Index, pstMsg->stRecord.Index, &ucPBOffset);

    if(VOS_OK != ulResult)  /*??????????????????*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Find the PhoneBook Content is Error");
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    /*ADN??????????????????*/
    if(pstMsg->stRecord.NumberLength > gastPBContent[ucPBOffset].ucNumberLen)
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Number Too Long");
        stCnfData.PBError = TAF_ERR_PB_DIAL_STRING_TOO_LONG;

        return SI_PBCallback(&stCnfData);
    }

    if(VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)/*????????????*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Content is NULL");
        stCnfData.PBError = TAF_ERR_UNSPECIFIED_ERROR;

        return SI_PBCallback(&stCnfData);       /*????????????*/
    }

    /*ADN??????FID????????????*/
    ulResult = SI_PB_CountADNRecordNum(pstMsg->stRecord.Index, &stSPBFid.usADNFileId, &ucRecord);

    if(VOS_ERR == ulResult)/*????????*/
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    /*????????????????????FID????*/
    ulResult = SI_PB_GetANRInfo(pstMsg->stRecord.AdditionNumber,stSPBFid.usADNFileId,stSPBFid.ausANRFileId);

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: Get the ANR Info Fail");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    /*Email ????FID????,??????????????????????Email????????????SI_PB_UpdataSPBFile??????*/
    if(gstPBConfigInfo.ucEmailFlag)
    {
        (VOS_VOID)SI_PB_GetEMLFIdFromADN(&stSPBFid.usEMLFileId,stSPBFid.usADNFileId);
    }
    else
    {
        stSPBFid.usEMLFileId = 0;
    }

    /*EXT????FID????*/
    ulExtInfoNum          = gastPBContent[ucPBOffset].ulExtInfoNum;
    stSPBFid.usExtFileId  = gastEXTContent[ulExtInfoNum].usExtFileId;

    gstPBReqUnit.enPBLock = PB_LOCKED;

    stSPBFid.ucRecordNum = ucRecord;

    ulResult = SI_PB_UpdataSPBFile(&stSPBFid,&pstMsg->stRecord);/*??????????????API*/

    if(VOS_OK != ulResult)
    {
        PB_WARNING_LOG("SI_PB_SModifyProc: SI_PB_UpdataSPBFile is Error");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    gstPBReqUnit.enPBEventType          = SI_PB_EVENT_MODIFY_CNF;/*????????????????????????*/

    gstPBReqUnit.enPBStoateType         = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID                 = pstMsg->ucOpID;

    gstPBReqUnit.usClientID             = pstMsg->usClient;

    gstPBReqUnit.usIndex1               = pstMsg->stRecord.Index;

    return VOS_OK;
}


VOS_UINT32 SI_PB_DeleteProc(PBMsgBlock *pMsg)
{
    SI_PB_DELETE_REQ_STRU *pstMsg = VOS_NULL_PTR;
    SI_PB_EVENT_INFO_STRU  stCnfData;
    VOS_UINT32             ulResult;
    VOS_UINT16             usFileId;
    VOS_UINT8              ucRecord;
    VOS_UINT8              ucPBOffset;
    VOS_UINT8              aucContent[100]; /*??????????????F*/

    pstMsg = (SI_PB_DELETE_REQ_STRU *)pMsg;

    (VOS_VOID)memset_s(aucContent, sizeof(aucContent), 0xFF, sizeof(aucContent));/*??????????????*/

    (VOS_VOID)memset_s(&stCnfData, sizeof(SI_PB_EVENT_INFO_STRU), 0, sizeof(SI_PB_EVENT_INFO_STRU));/*??????????????*/

    stCnfData.ClientId      = pstMsg->usClient;        /*????????????????????????*/
    stCnfData.OpId          = pstMsg->ucOpID;
    stCnfData.PBEventType   = SI_PB_EVENT_DELETE_CNF;
    stCnfData.Storage       = pstMsg->ulStorage;

    stCnfData.PBError = SI_PB_ErrorProc();

    if( ( TAF_ERR_NO_ERROR == stCnfData.PBError )
        && ( PB_INIT_FINISHED != gstPBInitState.enPBInitStep ) )
    {
        stCnfData.PBError = TAF_ERR_SIM_BUSY;
    }

    /*????????????????????*/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((PB_ECC == pstMsg->ulStorage)
     || (PB_XECC == pstMsg->ulStorage))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#else
    if (PB_ECC == pstMsg->ulStorage)
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
    }
#endif

    if( TAF_ERR_NO_ERROR != stCnfData.PBError )/*??????????????????????????????*/
    {
        PB_WARNING_LOG("SI_PB_DeleteProc: Proc Error");

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    ulResult = SI_PB_LocateRecord(pstMsg->ulStorage, pstMsg->usIndex, pstMsg->usIndex, &ucPBOffset);

    if(VOS_OK != ulResult)     /*????????????????*/
    {
        PB_WARNING_LOG("SI_PB_DeleteProc: Find the PhoneBook Content is Error");

        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    if(SI_PB_STORAGE_SM == pstMsg->ulStorage) /*????????????????ADN??????????????*/
    {
        ulResult = SI_PB_CountADNRecordNum(pstMsg->usIndex, &usFileId, &ucRecord);
    }
    else                                                        /*??????????????????????*/
    {
        ulResult = SI_PB_GetXDNFileID(pstMsg->ulStorage, &usFileId);

        ucRecord = (VOS_UINT8)pstMsg->usIndex;
    }

    if(VOS_ERR == ulResult)         /*????????*/
    {
        PB_WARNING_LOG("SI_PB_DeleteProc: Get the XDN File ID and Record Number is Error");

        stCnfData.PBError = TAF_ERR_PARA_ERROR;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }


    if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex,
                                                     gastPBContent[ucPBOffset].indexSize,
                                                    (VOS_UINT32)pstMsg->usIndex))
    {
        stCnfData.PBError = TAF_ERR_NO_ERROR;

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBLock = PB_LOCKED;

    /*????????????????????????ADN????????????????????*/
    ulResult = SI_PB_DeleteHandle(usFileId,ucRecord,ucPBOffset,pstMsg->usIndex);

    if(VOS_OK != ulResult)
    {
        stCnfData.PBError = ulResult;

        return SI_PBCallback(&stCnfData);
    }

    gstPBReqUnit.enPBEventType      = SI_PB_EVENT_DELETE_CNF;/*????????????*/

    gstPBReqUnit.enPBStoateType     = pstMsg->ulStorage;

    gstPBReqUnit.ucOpID             = pstMsg->ucOpID;

    gstPBReqUnit.usClientID         = pstMsg->usClient;

    gstPBReqUnit.usIndex1           = pstMsg->usIndex;

    return VOS_OK;
}


VOS_UINT32 SI_PB_RefreshALLContent(VOS_VOID)
{
    VOS_UINT32             ulResult  = VOS_ERR;

    SI_PB_ClearPBContent(SI_CLEARALL);

    SI_PB_ClearSPBContent(SI_CLEARALL);

    SI_PB_InitGlobeVariable();

    SI_PB_InitStatusInd(USIMM_PB_IDLE);

    gulPBFileCnt = 0;

    if ( VOS_OK != SI_PB_InitPBStatusJudge())/*????????????????????????*/
    {
        PB_ERROR_LOG("SI_PB_RefreshProc:Card Status Error");

        return VOS_ERR;
    }

    if ( PB_INIT_EFPBR == gstPBInitState.enPBInitStep )/*USIM??*/
    {
        ulResult = SI_PB_InitEFpbrReq();
    }
    else                                        /*SIM??*/
    {
        ulResult = SI_PB_InitXDNSpaceReq();
    }

    return ulResult;
}


VOS_UINT32 SI_PB_FDNCheckProc(PBMsgBlock *pMsg)
{
    PB_FDN_CHECK_CNF_STRU              *pstFDNCheckCnf = VOS_NULL_PTR;
    SI_PB_FDN_CHECK_REQ_STRU           *pstFDNCheckReq = VOS_NULL_PTR;
    VOS_UINT32                          ulResult1 = VOS_OK;
    VOS_UINT32                          ulResult2 = VOS_OK;
    VOS_UINT32                          ulUsimFdnStatus;
    VOS_UINT32                          ulCsimFdnStatus;
    SI_PIH_CARD_SLOT_ENUM_UINT32        enSlotId;

    pstFDNCheckReq = (SI_PB_FDN_CHECK_REQ_STRU *)pMsg;

    pstFDNCheckCnf = (PB_FDN_CHECK_CNF_STRU *)VOS_AllocMsg(MAPS_PB_PID,sizeof(PB_FDN_CHECK_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstFDNCheckCnf)
    {
        PB_ERROR_LOG("SI_PB_FDNCheckProc: alloc msg failed.");

        return VOS_ERR;
    }

    enSlotId = USIMM_GetSlotIdByModemId(MODEM_ID_0);

    /*????FDN??????????????VOS_OK*/
    USIMM_FdnQuery(enSlotId, &ulUsimFdnStatus, &ulCsimFdnStatus);

    pstFDNCheckCnf->ulReceiverPid   = pstFDNCheckReq->ulSenderPid;
    pstFDNCheckCnf->ulMsgName       = SI_PB_EVENT_FDNCHECK_CNF;
    pstFDNCheckCnf->enAppType       = pstFDNCheckReq->enAppType;
    pstFDNCheckCnf->ulSendPara      = pstFDNCheckReq->ulSendPara;
    pstFDNCheckCnf->ulContextIndex  = pstFDNCheckReq->ulContextIndex;

    if (USIMM_CDMA_APP == pstFDNCheckReq->enAppType)
    {
        if (USIMM_FDNSTATUS_OFF == ulCsimFdnStatus)
        {
            PB_INFO_LOG("SI_PB_CheckFdn: CSIM FDN is disable.");
        }
        else
        {
            PB_WARNING_LOG("SI_PB_CheckFdn: CSIM FDN is Enable, Now return NO Check.");
        }
    }

    if (USIMM_GUTL_APP == pstFDNCheckReq->enAppType)
    {
        if (USIMM_FDNSTATUS_OFF == ulUsimFdnStatus)
        {
            PB_INFO_LOG("SI_PB_CheckFdn: USIM FDN is disable.");
        }
        else
        {
            PB_INFO_LOG("SI_PB_CheckFdn: USIM FDN is Enable.");

            /* ?????????????? */
            ulResult1 = SI_PB_CheckFdn(pstFDNCheckReq->stFDNNum.aucNum1, pstFDNCheckReq->stFDNNum.ulNum1Len);

            /* ??????????????????????0???????????????? */
            if (pstFDNCheckReq->stFDNNum.ulNum2Len > 0)
            {
                ulResult2 = SI_PB_CheckFdn(pstFDNCheckReq->stFDNNum.aucNum2, pstFDNCheckReq->stFDNNum.ulNum2Len);
            }
        }
    }

    if((VOS_OK != ulResult1)&&(VOS_OK != ulResult2))
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_BOTH_NUM_FAIL;
    }
    else if(VOS_OK != ulResult1)
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_NUM1_FAIL;
    }
    else if(VOS_OK != ulResult2)
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_NUM2_FAIL;
    }
    else
    {
        pstFDNCheckCnf->enResult    = PB_FDN_CHECK_SUCC;
    }

    return VOS_SendMsg(MAPS_PB_PID, pstFDNCheckCnf);
}



VOS_UINT32 SI_PB_EcallNumberQryProc(PBMsgBlock *pMsg)
{
    SI_PB_ECALLQRY_REQ_STRU            *pstEcallQryReq = VOS_NULL_PTR;
    SI_PB_ECALLQRY_CNF_STRU            *pstEcallQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT8                           ucPBOffset;

    pstEcallQryReq = (SI_PB_ECALLQRY_REQ_STRU *)pMsg;

    ulRslt = SI_PB_EcallNumberErrProc(pstEcallQryReq->enStorage, pstEcallQryReq->ucListLen, pstEcallQryReq->aucList, &ucPBOffset);

    /* ????????????????????????????????????????NAS????????????????FDN/SDN???? */
    ulRecordNum = (TAF_ERR_NO_ERROR == ulRslt)?pstEcallQryReq->ucListLen:0;

/*lint -save -e961 */
    pstEcallQryCnf = (SI_PB_ECALLQRY_CNF_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                sizeof(SI_PB_ECALLQRY_CNF_STRU)-VOS_MSG_HEAD_LENGTH
                                                + ((sizeof(SI_PB_ECALL_NUM_STRU) * ulRecordNum)));
/*lint -restore */
    if (VOS_NULL_PTR == pstEcallQryCnf)
    {
        PB_ERROR_LOG("SI_PB_EcallNumberQryProc: alloc msg failed.");

        return VOS_ERR;
    }

    pstEcallQryCnf->ulReceiverPid   = pstEcallQryReq->ulSenderPid;
    pstEcallQryCnf->ulMsgName       = SI_PB_EVENT_ECALLQUERY_CNF;
    pstEcallQryCnf->enStorage       = pstEcallQryReq->enStorage;
    pstEcallQryCnf->ulRecordNum     = VOS_NULL;
    pstEcallQryCnf->ulRslt          = ulRslt;
    pstEcallQryCnf->enAppType       = USIMM_GUTL_APP;

    if (TAF_ERR_NO_ERROR == ulRslt)
    {
        pstEcallQryCnf->ulRecordNum     = pstEcallQryReq->ucListLen;

        /*lint -e613 */
        (VOS_VOID)memset_s(pstEcallQryCnf->astECallNumber,
                           sizeof(SI_PB_ECALL_NUM_STRU) * ulRecordNum,
                            0,
                            sizeof(SI_PB_ECALL_NUM_STRU) * ulRecordNum);
        /*lint +e613 */

        SI_PB_GetEcallNumber(gastPBContent + ucPBOffset, pstEcallQryCnf->astECallNumber, pstEcallQryReq->ucListLen, pstEcallQryReq->aucList);
    }

    return VOS_SendMsg(MAPS_PB_PID, pstEcallQryCnf);
}


VOS_VOID SI_PB_JudgeTotalUsedNum(VOS_UINT8 ucPBOffset,SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    if ((SI_PB_EVENT_ADD_CNF == gstPBReqUnit.enPBEventType)
        ||(SI_PB_EVENT_SADD_CNF == gstPBReqUnit.enPBEventType))
    {
        if(PB_ADN_CONTENT == ucPBOffset)
        {
            gstPBCtrlInfo.ulTotalUsed++;
        }

        pstCnfData->PBEvent.PBAddCnf.Index = gstPBReqUnit.usIndex1;

        SI_PB_SetBitToBuf(gastPBContent[ucPBOffset].pIndex, gastPBContent[ucPBOffset].indexSize, gstPBReqUnit.usIndex1, SI_PB_CONTENT_VALID);
    }
    else if (SI_PB_EVENT_DELETE_CNF == gstPBReqUnit.enPBEventType)
    {
        if(PB_ADN_CONTENT == ucPBOffset)
        {
            gstPBCtrlInfo.ulTotalUsed--;
        }

        SI_PB_SetBitToBuf(gastPBContent[ucPBOffset].pIndex,
                          gastPBContent[ucPBOffset].indexSize,
                          gstPBReqUnit.usIndex1,SI_PB_CONTENT_INVALID);

        (VOS_VOID)memset_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), 0xFF, sizeof(gstPBReqUnit.aucXDNContent));
    }
    else if ((SI_PB_EVENT_MODIFY_CNF == gstPBReqUnit.enPBEventType)
             ||(SI_PB_EVENT_SMODIFY_CNF == gstPBReqUnit.enPBEventType))
    {

        if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex,
                                                         gastPBContent[ucPBOffset].indexSize,
                                                         gstPBReqUnit.usIndex1))
        {
            /*gastPBContent[ucPBOffset].usUsedNum++;
 */

            if(PB_ADN_CONTENT == ucPBOffset)
            {
                gstPBCtrlInfo.ulTotalUsed++;
            }

            SI_PB_SetBitToBuf(gastPBContent[ucPBOffset].pIndex,
                              gastPBContent[ucPBOffset].indexSize,
                              gstPBReqUnit.usIndex1,SI_PB_CONTENT_VALID);
        }
    }
    else
    {
        /*should not*/
    }

    return;
}


VOS_VOID SI_PB_RefreshADNUsedNum(VOS_UINT8 *pucDstStorage, VOS_UINT32 destSize, VOS_UINT8 *pucSrcReq, VOS_UINT32 srcSize, VOS_UINT8 ucOffset)
{
   /*????????????(??????????????????)??PBreq????*/
    /*????????????????????????????????????*/
    if(VOS_OK == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                            pucDstStorage,
                                            destSize))
    {
        if(VOS_OK != SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                                pucSrcReq,
                                                srcSize))
        {
            gastPBContent[ucOffset].usUsedNum--;
        }
    }
    /*????????????????????????????????????*/
    else
    {
        if(VOS_OK == SI_PB_CheckContentValidity(&gastPBContent[ucOffset],
                                                pucSrcReq,
                                                srcSize))
        {
            gastPBContent[ucOffset].usUsedNum++;
        }
    }

    return;
}


VOS_VOID SI_PB_RefreshEXTUsedNum(VOS_UINT8 *pucDstStorage, VOS_UINT8 *pucSrcReq, VOS_UINT8 ucOffset)
{
    if((0x0 != pucDstStorage[0])&&(0xFF != pucDstStorage[1]))/*????*/
    {
        if((0x0 == pucSrcReq[0])||(0xFF == pucSrcReq[1]))
        {
            gastEXTContent[ucOffset].usExtUsedNum--;
        }
    }
    else
    {
        if((0x0 != pucSrcReq[0])&&(0xFF != pucSrcReq[1]))
        {
            gastEXTContent[ucOffset].usExtUsedNum++;
        }
    }

    return;
}


VOS_VOID SI_PB_RefreshANRUsedNum(VOS_UINT32 dstResult, VOS_UINT8 srcReq1, VOS_UINT8 srcReq2, VOS_UINT8 offset)
{
    if(VOS_OK == dstResult)/*????*/
    {
        if(VOS_OK != SI_PB_CheckANRValidity(srcReq1, srcReq2))
        {
            gastANRContent[offset].usUsedNum--;
        }
    }
    else
    {
        if(VOS_OK == SI_PB_CheckANRValidity(srcReq1, srcReq2))
        {
            gastANRContent[offset].usUsedNum++;
        }
    }

    return;
}


VOS_VOID SI_PB_RefreshEMLUsedNum(VOS_UINT8 dstStorage, VOS_UINT8 srcReq)
{
    if(0xFF != dstStorage)/*????*/
    {
        if(0xFF == srcReq)
        {
            gstEMLContent.usUsedNum--;
        }
    }
    else
    {
        if(0xFF != srcReq)
        {
            gstEMLContent.usUsedNum++;
        }
    }

    return;
}


VOS_VOID SI_PB_XDN_ProcessUsedNum(
    VOS_UINT8                           ucOffset,
    VOS_UINT8                          *pucDstStorage,
    VOS_UINT32                          dataSize
)
{
    if(SI_PB_EVENT_ADD_CNF == gstPBReqUnit.enPBEventType)
    {
        gastPBContent[ucOffset].usUsedNum++;
    }

    if(SI_PB_EVENT_DELETE_CNF == gstPBReqUnit.enPBEventType)
    {
        gastPBContent[ucOffset].usUsedNum--;
        (VOS_VOID)memset_s(gstPBReqUnit.aucXDNContent, sizeof(gstPBReqUnit.aucXDNContent), 0xFF, sizeof(gstPBReqUnit.aucXDNContent));
    }

    if(SI_PB_EVENT_MODIFY_CNF == gstPBReqUnit.enPBEventType)
    {
        if(VOS_OK != SI_PB_CheckContentValidity(&gastPBContent[ucOffset], pucDstStorage, dataSize) )
        {
             gastPBContent[ucOffset].usUsedNum++;
        }
    }

    return;
}




VOS_UINT32 SI_PB_Is_XdnFileId(
    VOS_UINT16                          usFileId
)
{
    if ((EFFDN == usFileId) || (EFBDN == usFileId) || (EFMSISDN == usFileId))
    {
        return VOS_OK;
    }

    return VOS_ERR;

}


VOS_UINT32 SI_PB_RefreshMemory(VOS_UINT16 usFileId,VOS_UINT16 usRecordLen,VOS_UINT8 ucOffset,VOS_UINT8 ucRecordNum)
{
    VOS_UINT8  *pucSrcReq = VOS_NULL_PTR;
    VOS_UINT8  *pucDstStorage = VOS_NULL_PTR;
    VOS_UINT16 usMemOffset;
    VOS_UINT8  ucSuffix;
    VOS_UINT8  ucFileCnt;
    VOS_UINT32 ulFreeSize = 0;
    VOS_UINT32 ulDestOffset = 0;
    VOS_UINT32 result;
    VOS_UINT32 copyLen;
    errno_t    ret;

    /*??????????????????????????*/
    if(VOS_OK == SI_PB_JudgeADNFid(usFileId))/*ADN*/
    {
        usMemOffset   = (VOS_UINT16)((gstPBReqUnit.usIndex1-1)*gastPBContent[ucOffset].ucRecordLen);
        pucSrcReq     = gstPBReqUnit.aucXDNContent;
        pucDstStorage = &gastPBContent[ucOffset].pContent[usMemOffset];

        if (gastPBContent[ucOffset].ulContentSize < usMemOffset)
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory: gastPBContent No Enough Space.");
            return VOS_ERR;
        }

        ulFreeSize = gastPBContent[ucOffset].ulContentSize - usMemOffset;

        SI_PB_RefreshADNUsedNum(pucDstStorage, ulFreeSize, pucSrcReq, sizeof(gstPBReqUnit.aucXDNContent), ucOffset);
    }
    else if(VOS_OK == SI_PB_JudgeEXTFid(usFileId, ucOffset))/*EXT*/
    {
        /*????EXT??????Record????????????gstPBReqUnit????????????*/
        if(VOS_OK != SI_PB_GetEXTContentFromReq(ucRecordNum,&pucSrcReq))
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory:SI_PB_GetEXTContentFromReq ERROR.");
            return VOS_ERR;
        }

        usMemOffset   = (ucRecordNum-1)*SI_PB_EXT_LEN;
        pucDstStorage = &gastEXTContent[ucOffset].pExtContent[usMemOffset];

        if (gastEXTContent[ucOffset].ulContentSize < usMemOffset)
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory:gastEXTContent No Enough Space.");
            return VOS_ERR;
        }

        SI_PB_RefreshEXTUsedNum(pucDstStorage, pucSrcReq, ucOffset);

        ulFreeSize = gastEXTContent[ucOffset].ulContentSize - usMemOffset;
    }
    else if(VOS_OK == SI_PB_GetANRSuffix(&ucFileCnt,&ucSuffix,usFileId))/*ANR*/
    {
        pucSrcReq     = gstPBReqUnit.stSPBReq.aucANRContent[ucSuffix];

        usMemOffset   = (VOS_UINT16)(((ucFileCnt*gstPBCtrlInfo.astANRInfo[ucFileCnt][ucSuffix].ucRecordNum)
             +(ucRecordNum - 1))*gastANRContent[ucSuffix].ucRecordLen);

        pucDstStorage = &gastANRContent[ucSuffix].pContent[usMemOffset];

        if (gastANRContent[ucSuffix].ulContentSize < usMemOffset)
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory:gastANRContent No Enough Space.");
            return VOS_ERR;
        }

        result = SI_PB_CheckANRValidity(pucDstStorage[0], pucDstStorage[1]);

        SI_PB_RefreshANRUsedNum(result, pucSrcReq[0], pucSrcReq[1], ucSuffix);

        ulFreeSize = gastANRContent[ucSuffix].ulContentSize - usMemOffset;
    }
    else if(VOS_OK == SI_PB_GetEMLRecord(&pucDstStorage , usFileId, ucRecordNum, &ulFreeSize))/*Email*/
    {
        pucSrcReq = gstPBReqUnit.stSPBReq.aucEMLContent;

        SI_PB_RefreshEMLUsedNum(pucDstStorage[0], pucSrcReq[0]);
    }
    else if(VOS_OK == SI_PB_JudgeIAPFid(usFileId))
    {
        pucSrcReq = gstPBReqUnit.stSPBReq.aucIAPContent;

        pucDstStorage = &gstIAPContent.pIAPContent[(gstPBReqUnit.usIndex1-1)*gstIAPContent.ucRecordLen];

        PB_NORMAL_LOG("SI_PB_RefreshMemory:IAP File.");

        ulDestOffset = (gstPBReqUnit.usIndex1-1)*gstIAPContent.ucRecordLen;

        if (gstIAPContent.ulContentSize < ulDestOffset)
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory:gstIAPContent No Enough Space.");
            return VOS_ERR;
        }

        ulFreeSize = gstIAPContent.ulContentSize - ulDestOffset;
    }
    else if(VOS_OK == SI_PB_Is_XdnFileId(usFileId))
    {
        pucSrcReq = gstPBReqUnit.aucXDNContent;
        pucDstStorage = gastPBContent[ucOffset].pContent + ((gstPBReqUnit.usIndex1-1)* gastPBContent[ucOffset].ucRecordLen);

        ulDestOffset = (gstPBReqUnit.usIndex1-1)* gastPBContent[ucOffset].ucRecordLen;

        if (gastPBContent[ucOffset].ulContentSize < ulDestOffset)
        {
            PB_WARNING_LOG("SI_PB_RefreshMemory:gastPBContent No Enough Space.");
            return VOS_ERR;
        }

        ulFreeSize = gastPBContent[ucOffset].ulContentSize - ulDestOffset;

        SI_PB_XDN_ProcessUsedNum(ucOffset, pucDstStorage, ulFreeSize);
    }
    else
    {
        PB_WARNING_LOG("SI_PB_RefreshMemory:Unknown PB Type.");
        return VOS_ERR;
    }

    copyLen = PAM_GetMin(ulFreeSize, usRecordLen);

    ret = memcpy_s(pucDstStorage, ulFreeSize, pucSrcReq, copyLen);
    PAM_PRINT_SECFUN_RESULT(ret);

    return VOS_OK;
}


VOS_VOID SI_PB_UsimSetFileProc(USIMM_UPDATEFILE_CNF_STRU    *pstMsg,
                                        VOS_UINT8                   ucPBOffset,
                                        SI_PB_EVENT_INFO_STRU       *pstCnfData)
{
    VOS_UINT16          usEFId;

    SI_PB_GetEFIDFromPath(&pstMsg->stFilePath, &usEFId);

    if(VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
        PB_WARNING_LOG("SI_PB_UsimSetFileProc:Usimm Cnf ERROR.");
        return;
    }

    SI_PB_JudgeTotalUsedNum(ucPBOffset,pstCnfData);

    if(VOS_NULL_PTR != gastPBContent[ucPBOffset].pContent)
    {
        if(VOS_OK != SI_PB_RefreshMemory(usEFId, pstMsg->usEFLen, ucPBOffset, pstMsg->ucRecordNum))
        {
            pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
            PB_WARNING_LOG("SI_PB_UsimSetFileProc:SI_PB_RefreshMemory ERROR.");
            return;
        }
    }

    if(VOS_OK == SI_PB_CheckADNFileID(usEFId))
    {
        SI_PB_IncreaceCCValue(1,pstMsg->ucRecordNum);
    }

    return;
}


VOS_VOID SI_PB_UsimSetExtFileProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg, VOS_UINT8 ucPBOffset)
{
    VOS_UINT8   *ptemp = VOS_NULL_PTR;
    VOS_UINT32  ulExtInfoNum;
    VOS_UINT32  ulFreeSize;
    VOS_UINT32  ulDestOffset;
    errno_t     ret;

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;

    if(VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        ulDestOffset = (gstPBReqUnit.usExtIndex - 1) * SI_PB_EXT_LEN;

        if (gastEXTContent[ucPBOffset].ulContentSize < ulDestOffset)
        {
            PB_WARNING_LOG("WARNING:SI_PB_UsimSetExtFileProc: No enough space");
            return;
        }

        ulFreeSize = gastEXTContent[ucPBOffset].ulContentSize - ulDestOffset;

        ptemp = gastEXTContent[ucPBOffset].pExtContent + ulDestOffset;

        if(SI_PB_EVENT_ADD_CNF == gstPBReqUnit.enPBEventType)
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum++;
        }

        if(SI_PB_EVENT_DELETE_CNF == gstPBReqUnit.enPBEventType)
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum--;
        }

        if( (SI_PB_EVENT_MODIFY_CNF == gstPBReqUnit.enPBEventType)
            && ( 0xFF == *(ptemp+1)) )
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum++;
        }

        ret = memcpy_s(ptemp, ulFreeSize, gstPBReqUnit.aucEXTContent, SI_PB_EXT_LEN);

        PAM_PRINT_SECFUN_RESULT(ret);
    }
    else
    {
        PB_WARNING_LOG("WARNING:SI_PB_UsimSetExtFileProc ERROR.");
    }
}


VOS_VOID SI_PB_RefreshCardIndMsgSnd(VOS_VOID)
{
    USIMM_CARDSTATUS_IND_STRU          *pUsimMsg = VOS_NULL_PTR;
    SI_PIH_CARD_SLOT_ENUM_UINT32        enSlotId;

    pUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                               sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pUsimMsg)
    {
        return;
    }

    /*lint -e426*/
    (VOS_VOID)memset_s(&pUsimMsg->ulMsgName,
                        sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                        0,
                        sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    /*lint +e426*/

    enSlotId = USIMM_GetSlotIdByModemId(MODEM_ID_0);

    pUsimMsg->ulMsgName                         = USIMM_CARDSTATUS_IND;    /* ???????????? */
    pUsimMsg->enPhyCardType                     = USIMM_CCB_GetCardType(enSlotId);
    pUsimMsg->stUsimSimInfo.enCardAppService    = USIMM_CCB_GetAppService(enSlotId, USIMM_GUTL_APP);
    pUsimMsg->stCsimUimInfo.enCardAppService    = USIMM_CARDAPP_SERVIC_ABSENT;
    pUsimMsg->stIsimInfo.enCardAppService       = USIMM_CARDAPP_SERVIC_ABSENT;
    pUsimMsg->stAddInfo.enMediumType            = USIMM_GetCardMediumType(enSlotId);
    pUsimMsg->stAddInfo.enStatusType            = USIMM_CARD_STATUS_INIT_IND;
    pUsimMsg->ulReceiverPid                     = MAPS_PB_PID;

    (VOS_VOID)VOS_SendMsg(MAPS_PIH_PID, pUsimMsg);

    return;
}


VOS_BOOL SI_PB_SimRefreshFileCheck(VOS_UINT16 usPathLen, VOS_UINT8 *pcFilePath)
{
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, usPathLen, (VOS_CHAR *)pcFilePath, &enFileID))
    {
        PB_WARNING_LOG("SI_PB_SimRefreshFileCheck: USIMM_ChangePathToDefFileID is ERROR.");

        return VOS_FALSE;
    }

    if (  (enFileID == USIMM_TELE_EFADN_ID)
        ||(enFileID == USIMM_TELE_EFFDN_ID)
        ||(enFileID == USIMM_TELE_EFBDN_ID)
        ||(enFileID == USIMM_TELE_EFMSISDN_ID))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL SI_PB_UsimRefreshFileCheck(
    VOS_UINT16                          usPathLen,
    VOS_UINT8                           *pcFilePath,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_CHAR                            aucGlobalPath[] = {'3','F','0','0','7','F','1','0','5','F','3','A'};
    VOS_CHAR                            aucLocallPath[] = {'3','F','0','0','7','F','F','F','5','F','3','A'};
    VOS_INT32                           lRslt1 = VOS_ERR;
    VOS_INT32                           lRslt2 = VOS_ERR;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    if (usPathLen >= sizeof(aucGlobalPath))
    {
        lRslt1 = VOS_MemCmp(aucGlobalPath, pcFilePath, sizeof(aucGlobalPath));
    }

    if (usPathLen >= sizeof(aucLocallPath))
    {
        lRslt2 = VOS_MemCmp(aucLocallPath, pcFilePath, sizeof(aucLocallPath));
    }

    if ((VOS_OK == lRslt1) || (VOS_OK == lRslt2))
    {
        return VOS_TRUE;
    }

    if (VOS_OK != USIMM_ChangePathToDefFileID(enAppType, usPathLen, (VOS_CHAR *)pcFilePath, &enFileID))
    {
        PB_WARNING_LOG("SI_PB_SimRefreshFileCheck: USIMM_ChangePathToDefFileID is ERROR.");

        return VOS_FALSE;
    }

    if ((enFileID == USIMM_TELE_EFFDN_ID)
     || (enFileID == USIMM_TELE_EFBDN_ID)
     || (enFileID == USIMM_TELE_EFMSISDN_ID)
     || (enFileID == USIMM_USIM_EFFDN_ID)
     || (enFileID == USIMM_USIM_EFBDN_ID)
     || (enFileID == USIMM_USIM_EFMSISDN_ID))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL SI_PB_RefreshFileCheck(USIMM_STKREFRESH_IND_STRU *pstMsg)
{
    VOS_UINT16                          i;

    if (USIMM_CARD_SIM == gstPBInitState.enCardType)
    {
        for (i=0; i<pstMsg->usEfNum; i++)
        {
            if (VOS_TRUE == SI_PB_SimRefreshFileCheck(pstMsg->astEfId[i].usPathLen, pstMsg->astEfId[i].aucPath))
            {
                return VOS_TRUE;
            }
        }
    }
    else
    {
        for (i=0; i<pstMsg->usEfNum; i++)
        {
            if (VOS_TRUE == SI_PB_UsimRefreshFileCheck(pstMsg->astEfId[i].usPathLen,
                                                        pstMsg->astEfId[i].aucPath,
                                                        pstMsg->astEfId[i].enAppType))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


VOS_VOID SI_PB_PihRefreshIndProc(USIMM_STKREFRESH_IND_STRU *pstMsg)
{
    VOS_UINT32                          ulPbRefreshFlag;

    if (USIMM_REFRESH_ALL_FILE == pstMsg->enRefreshType)
    {
        ulPbRefreshFlag = VOS_TRUE;
    }
    else if (USIMM_REFRESH_3G_SESSION_RESET == pstMsg->enRefreshType)
    {
        ulPbRefreshFlag = VOS_FALSE;
    }
    else if (USIMM_REFRESH_FILE_LIST == pstMsg->enRefreshType)
    {
        if (VOS_FALSE == SI_PB_RefreshFileCheck(pstMsg))
        {
            ulPbRefreshFlag = VOS_FALSE;
        }
        else
        {
            ulPbRefreshFlag = VOS_TRUE;
        }
    }
    else
    {
        ulPbRefreshFlag = VOS_FALSE;
    }

    if (VOS_TRUE == ulPbRefreshFlag)
    {
        SI_PB_ReleaseAll();

        SI_PB_InitStatusInd(USIMM_PB_IDLE);

        SI_PB_RefreshCardIndMsgSnd();
    }

    return;
}

VOS_VOID SI_PB_UsimSetSPBFileProc(USIMM_SETMUTILFILE_CNF_STRU *pstPBMsg,
                                             SI_PB_EVENT_INFO_STRU       *pstCnfData,
                                             VOS_UINT8                   ucOffset)
{
    VOS_UINT32 i;

    /*????USIMM??????????????????????????????????????*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
        PB_WARNING_LOG("SI_PB_UsimSetSPBFileProc:Usimm Cnf ERROR.");
        return;
    }

    SI_PB_JudgeTotalUsedNum(ucOffset,pstCnfData);

    /*??????????????????????????????????????????????????????????????????????????????????*/
    for(i = 0; i < pstPBMsg->ucFileNum; i++)
    {
        if(VOS_OK != SI_PB_RefreshMemory(pstPBMsg->ausEfId[i],
                                        pstPBMsg->ausEfLen[i],
                                         ucOffset,
                                         pstPBMsg->aucRecordNum[i]))
        {
            pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;
            PB_WARNING_LOG("SI_PB_UsimSetSPBFileProc:SI_PB_RefreshMemory ERROR.");
            return;
        }

        if(VOS_OK == SI_PB_CheckADNFileID(pstPBMsg->ausEfId[i]))
        {
            SI_PB_IncreaceCCValue(1,pstPBMsg->aucRecordNum[i]);
        }
    }

    return;
}


VOS_VOID SI_PB_UsimGetFileProc(USIMM_READFILE_CNF_STRU *pstMsg,
                                        VOS_UINT8               ucPBOffset,
                                        SI_PB_EVENT_INFO_STRU   *pstCnfData)
{
    if(VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_UsimGetFileProc: USIMM Cnf Error");

        return;
    }

    SI_PB_TransPBFromate(&gastPBContent[ucPBOffset],
                        gstPBReqUnit.usCurIndex,
                        pstMsg->aucEf,
                        &pstCnfData->PBEvent.PBReadCnf.PBRecord);

    pstCnfData->PBEvent.PBReadCnf.RecordNum
            = (gstPBReqUnit.usIndex2 - gstPBReqUnit.usIndex1) + 1;

    if(gstPBReqUnit.usCurIndex == gstPBReqUnit.usIndex2)
    {
        pstCnfData->PBLastTag = VOS_TRUE;
    }
    else
    {
        pstCnfData->PBLastTag = VOS_FALSE;

        gstPBReqUnit.usCurIndex++;
    }

    return ;
}

VOS_VOID SI_PB_UsimSearchFileProc(USIMM_READFILE_CNF_STRU *pstMsg,
                                            VOS_UINT8               ucPBOffset,
                                            SI_PB_EVENT_INFO_STRU   *pstCnfData)
{
    if(VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstCnfData->PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        PB_WARNING_LOG("SI_PB_UsimSearchFileProc: USIMM Cnf Error");

        return;
    }

    pstCnfData->PBEvent.PBSearchCnf.RecordNum
            = (gstPBReqUnit.usIndex2 - gstPBReqUnit.usIndex1) + 1;

    if (pstMsg->usEfLen >= gstPBReqUnit.usSearchLen)
    {
        if ((VOS_OK == VOS_MemCmp(pstMsg->aucEf, gstPBReqUnit.aucXDNContent, gstPBReqUnit.usSearchLen))
         || (0 == gstPBReqUnit.usSearchLen))
        {
            SI_PB_TransPBFromate(&gastPBContent[ucPBOffset], gstPBReqUnit.usCurIndex,
                                 pstMsg->aucEf, &pstCnfData->PBEvent.PBSearchCnf.PBRecord);

            gstPBReqUnit.ucEqualFlag = VOS_TRUE;
        }
        else
        {
            pstCnfData->PBEvent.PBSearchCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
        }
    }
    else
    {
        pstCnfData->PBEvent.PBSearchCnf.PBRecord.ValidFlag = SI_PB_CONTENT_INVALID;
    }

    if(gstPBReqUnit.usCurIndex == gstPBReqUnit.usIndex2)
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        if (VOS_TRUE != gstPBReqUnit.ucEqualFlag)
        {
            pstCnfData->PBError = TAF_ERR_PB_NOT_FOUND;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_FALSE;

        gstPBReqUnit.usCurIndex++;
    }

    return;
}

VOS_VOID SI_PB_UsimGetIndexFile(VOS_UINT8 ucPBOffset, SI_PB_EVENT_INFO_STRU *pstCnfData)
{
    VOS_UINT32                  ulResult;
    VOS_UINT8                   ucSendReqFlag = PB_REQ_NOT_SEND;
    VOS_UINT8                   ucRecord;
    VOS_UINT16                  usFileId;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /*????????????????,??????????????*/
    if ((VOS_OK != pstCnfData->PBError)||(VOS_TRUE == pstCnfData->PBLastTag))
    {
        return;
    }

    while(gstPBReqUnit.usCurIndex <= gstPBReqUnit.usIndex2)
    {
        if (SI_PB_CONTENT_VALID == SI_PB_GetBitFromBuf(gastPBContent[ucPBOffset].pIndex,
                                                       gastPBContent[ucPBOffset].indexSize,
                                                       gstPBReqUnit.usCurIndex))
        {
            ucSendReqFlag = PB_REQ_SEND;
            break;
        }

        gstPBReqUnit.usCurIndex++;
    }

    if (PB_REQ_SEND == ucSendReqFlag)
    {
        if(SI_PB_STORAGE_SM == gstPBReqUnit.enPBStoateType)   /*??????ADN????????????????*/
        {
            ulResult = SI_PB_CountADNRecordNum(gstPBReqUnit.usCurIndex, &usFileId, &ucRecord);
        }
        else                                                                    /*??????????????*/
        {
            ulResult = SI_PB_GetXDNFileID(gstPBReqUnit.enPBStoateType, &usFileId);

            ucRecord = (VOS_UINT8)gstPBReqUnit.usCurIndex;
        }

        if(VOS_ERR == ulResult)         /*????????????*/
        {
            PB_WARNING_LOG("SI_PB_SearchReq: Get the XDN File ID and Record Number is Error");

            pstCnfData->PBError = TAF_ERR_PARA_ERROR;

            return;
        }

        stGetFileInfo.ucRecordNum   = ucRecord;
        stGetFileInfo.usEfId        = usFileId;

        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        if (VOS_OK != ulResult)
        {
            pstCnfData->PBError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;
        }
    }
    else
    {
        pstCnfData->PBLastTag = VOS_TRUE;

        if ((SI_PB_EVENT_SEARCH_CNF == gstPBReqUnit.enPBEventType)
             &&(VOS_TRUE != gstPBReqUnit.ucEqualFlag))
        {
            pstCnfData->PBError = TAF_ERR_PB_NOT_FOUND;
        }
    }

    return;
}


VOS_VOID SI_PBSendGlobalToAcpu(VOS_VOID)
{
    SI_PB_UPDATEGLOBAL_IND_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          i;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSystemAppConfig = {0};

    /* ????ANDROID 64??????????????????????????A???? */
    if (VOS_OK != mdrv_nv_read(en_NV_Item_System_APP_Config, &stSystemAppConfig, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        return;
    }

    if (SYSTEM_APP_ANDROID == stSystemAppConfig.usSysAppConfigType)
    {
        return;
    }

    pstMsg = (SI_PB_UPDATEGLOBAL_IND_STRU*)VOS_AllocMsg(MAPS_PB_PID,
                                sizeof(SI_PB_UPDATEGLOBAL_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid = ACPU_PID_PB;
    pstMsg->ulMsgName     = SI_PB_UPDATE_AGOBAL;

    /*???????? Acpu ??????????????????*/
    (VOS_VOID)memcpy_s(&pstMsg->stPBCtrlInfo,   sizeof(gstPBCtrlInfo),      &gstPBCtrlInfo,  sizeof(gstPBCtrlInfo));
    (VOS_VOID)memcpy_s(&pstMsg->stPBConfigInfo, sizeof(gstPBConfigInfo),    &gstPBConfigInfo,sizeof(gstPBConfigInfo));
    (VOS_VOID)memcpy_s(pstMsg->astPBContent,    sizeof(gastPBContent),      gastPBContent,   sizeof(gastPBContent));
    (VOS_VOID)memcpy_s(pstMsg->astEXTContent,   sizeof(gastEXTContent),     gastEXTContent,  sizeof(gastEXTContent));
    (VOS_VOID)memcpy_s(pstMsg->astANRContent,   sizeof(gastANRContent),     gastANRContent,  sizeof(gastANRContent));
    (VOS_VOID)memcpy_s(&pstMsg->stEMLContent,   sizeof(gstEMLContent),      &gstEMLContent,  sizeof(gstEMLContent));
    (VOS_VOID)memcpy_s(&pstMsg->stIAPContent,   sizeof(gstIAPContent),      &gstIAPContent,  sizeof(gstIAPContent));
    (VOS_VOID)memcpy_s(&pstMsg->stPBInitState,  sizeof(gstPBInitState),     &gstPBInitState, sizeof(gstPBInitState));

    for(i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        pstMsg->astPBContentAddr[i].ulIndexAddr     = (VOS_UINT32)gastPBContent[i].pIndex;
        pstMsg->astPBContentAddr[i].ulContentAddr   = (VOS_UINT32)gastPBContent[i].pContent;

        pstMsg->aulExtContentAddr[i] = (VOS_UINT32)gastEXTContent[i].pExtContent;
    }

    for(i=0; i<SI_PB_ANRMAX; i++)
    {
        pstMsg->aulANRContentAddr[i] = (VOS_UINT32)gastANRContent[i].pContent;
    }

    pstMsg->ulEMLContentAddr = (VOS_UINT32)gstEMLContent.pContent;
    pstMsg->ulIAPContentAddr = (VOS_UINT32)gstIAPContent.pIAPContent;

    if(VOS_OK != VOS_SendMsg(MAPS_PB_PID, pstMsg))
    {
        PB_ERROR_LOG("SI_PBSendGobalToAcpu: Send msg Error");
    }

    return;
}


VOS_VOID SI_PB_EcallInitInd(VOS_VOID)
{
    SI_PB_ECALLINIT_IND_STRU           *pstEcallIndMsg = VOS_NULL_PTR;

    pstEcallIndMsg = (SI_PB_ECALLINIT_IND_STRU *)VOS_AllocMsg(MAPS_PB_PID, sizeof(SI_PB_ECALLINIT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstEcallIndMsg)
    {
        PB_ERROR_LOG("SI_PB_EcallInitInd: Alloc Msg Fail");

        return;
    }

    pstEcallIndMsg->ulReceiverPid       = WUEPS_PID_TAF;
    pstEcallIndMsg->ulMsgName           = SI_PB_EVENT_ECALLINIT_IND;
    pstEcallIndMsg->usFdnRecordNum      = gastPBContent[PB_FDN_CONTENT].usTotalNum;
    pstEcallIndMsg->usSdnRecordNum      = gastPBContent[PB_SDN_CONTENT].usTotalNum;

    (VOS_VOID)VOS_SendMsg(MAPS_PB_PID, pstEcallIndMsg);

    return;
}


VOS_VOID SI_PB_ReleaseAll(VOS_VOID)
{
    gstPBInitState.enPBInitStep = PB_INIT_PB_STATUS;

    SI_PB_ClearPBContent(SI_CLEARALL);

    SI_PB_ClearSPBContent(SI_CLEARALL);

    SI_PB_InitGlobeVariable();

    SI_PBSendGlobalToAcpu();
}


VOS_UINT32 SI_PBUsimCnfMsgProc(PBMsgBlock *pMsg)
{
    VOS_UINT8                   ucPBOffset;
    SI_PB_EVENT_INFO_STRU       stCnfData;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usEFId;

    (VOS_VOID)memset_s(&stCnfData, sizeof(stCnfData), 0, sizeof(stCnfData));

    stCnfData.ClientId          = gstPBReqUnit.usClientID;

    stCnfData.OpId              = gstPBReqUnit.ucOpID;

    stCnfData.PBError           = TAF_ERR_NO_ERROR;

    stCnfData.PBEventType       = gstPBReqUnit.enPBEventType;

    stCnfData.Storage           = gstPBReqUnit.enPBStoateType;

    ulResult = SI_PB_FindPBOffset(gstPBReqUnit.enPBStoateType, &ucPBOffset);

    if((VOS_OK != ulResult)&&(USIMM_CARDSTATUS_IND != pMsg->ulMsgName))
    {
        stCnfData.PBError = TAF_ERR_PB_STORAGE_OP_FAIL;

        return SI_PBCallback(&stCnfData);/*????????????*/
    }

    switch (pMsg->ulMsgName)
    {
        case USIMM_UPDATEFILE_CNF:
            SI_PB_GetEFIDFromPath(&((USIMM_UPDATEFILE_CNF_STRU *)pMsg)->stFilePath, &usEFId);

            if(VOS_OK == SI_PB_CheckSYNCHFileID(usEFId))
            {
                 return VOS_OK;
            }

            if(VOS_OK == SI_PB_CheckExtFileID(usEFId))
            {
                SI_PB_UsimSetExtFileProc((USIMM_UPDATEFILE_CNF_STRU*)pMsg, ucPBOffset);

                return VOS_OK;
            }

            SI_PB_UsimSetFileProc((USIMM_UPDATEFILE_CNF_STRU*)pMsg,ucPBOffset,&stCnfData);

            break;

        case USIMM_READFILE_CNF:
            if (SI_PB_EVENT_READ_CNF == stCnfData.PBEventType)
            {
                SI_PB_UsimGetFileProc((USIMM_READFILE_CNF_STRU*)pMsg,ucPBOffset,&stCnfData);
            }
            else
            {
                SI_PB_UsimSearchFileProc((USIMM_READFILE_CNF_STRU*)pMsg,ucPBOffset,&stCnfData);
            }

            SI_PB_UsimGetIndexFile(ucPBOffset, &stCnfData);

            break;

        case USIMM_SETMUTILFILE_CNF:
            SI_PB_UsimSetSPBFileProc((USIMM_SETMUTILFILE_CNF_STRU *)pMsg,&stCnfData,ucPBOffset);
            break;

        default:
            PB_WARNING_LOG("SI_PBUsimCnfMsgProc:Msg Name is unknow");
            return VOS_ERR;
    }

    return SI_PBCallback(&stCnfData);/*????????????*/
}


VOS_UINT32 SI_PBUsimMsgProc(PBMsgBlock *pMsg)
{
    VOS_UINT32                   ulResult;
    USIMM_CARDSTATUS_IND_STRU   *pStStatusMsg = VOS_NULL_PTR;

    /* ??Refresh??????????????????ECC???????????????????? */
    if (USIMM_ECCNUMBER_IND == pMsg->ulMsgName)
    {
        /* ?????????????????????????????????????????? */
        if(VOS_NULL_PTR != gastPBContent[PB_ECC_CONTENT].pContent)
        {
            (VOS_VOID)PB_FREE(gastPBContent[PB_ECC_CONTENT].pContent);

            gastPBContent[PB_ECC_CONTENT].pContent = VOS_NULL_PTR;
        }

        ulResult = SI_PB_InitEccProc(pMsg);
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (USIMM_XECCNUMBER_IND == pMsg->ulMsgName)
    {
        /* ?????????????????????????????????????????? */
        if(VOS_NULL_PTR != gastPBContent[PB_XECC_CONTENT].pContent)
        {
            (VOS_VOID)PB_FREE(gastPBContent[PB_XECC_CONTENT].pContent);

            gastPBContent[PB_XECC_CONTENT].pContent = VOS_NULL_PTR;
        }

        ulResult = SI_PB_InitXeccProc(pMsg);
    }
#endif
    else if (USIMM_CARDSTATUS_IND == pMsg->ulMsgName)
    {
        pStStatusMsg = (USIMM_CARDSTATUS_IND_STRU *)pMsg;

        if ((USIMM_CARDAPP_SERVIC_ABSENT == pStStatusMsg->stUsimSimInfo.enCardAppService)
          &&(USIMM_CARDAPP_SERVIC_ABSENT == pStStatusMsg->stCsimUimInfo.enCardAppService))
        {
            PB_WARNING_LOG("SI_PBUsimMsgProc:Card Absent");

            SI_PB_ReleaseAll();

            SI_PB_InitStatusInd(USIMM_PB_IDLE);
        }

        ulResult = VOS_OK;
    }
    else if (USIMM_STKREFRESH_IND == pMsg->ulMsgName)
    {
        /* ????Pb??????MMA */
        SI_PB_PbStatusInd(VOS_FALSE);

        SI_PB_PihRefreshIndProc((USIMM_STKREFRESH_IND_STRU *)pMsg);

        ulResult = VOS_OK;
    }
    else
    {
        ulResult = SI_PBUsimCnfMsgProc(pMsg);
    }

    return ulResult;
}



SI_PB_INIT_LIST_STRU    gastPBInitProc[] =
{
    {PB_INIT_PB_STATUS,     SI_PB_InitPBStatusJudge,    SI_PB_InitPBStatusProc},
    {PB_INIT_EFPBR,         SI_PB_InitEFpbrReq,         SI_PB_InitEFpbrProc},
    {PB_INIT_XDN_SPACE,     SI_PB_InitXDNSpaceReq,      SI_PB_InitXDNSpaceMsgProc},
    {PB_INIT_ANR_SPACE,     SI_PB_InitANRSpaceReq,      SI_PB_InitANRSpaceMsgProc},
    {PB_INIT_EML_SPACE,     SI_PB_InitEMLSpaceReq,      SI_PB_InitEMLSpaceMsgProc},
    {PB_INIT_IAP_SPACE,     SI_PB_InitIAPSpaceReq,      SI_PB_InitIAPSpaceMsgProc},
    {PB_INIT_EXT_SPACE,     SI_PB_InitEXTSpaceReq,      SI_PB_InitEXTSpaceMsgProc},
    {PB_INIT_IAP_CONTENT,   SI_PB_InitIAPContentReq,    SI_PB_InitIAPContentMsgProc},
    {PB_INIT_EML_CONTENT,   SI_PB_InitEMLContentReq,    SI_PB_InitEMLContentMsgProc},
    {PB_INIT_ANR_CONTENT,   SI_PB_InitANRContentReq,    SI_PB_InitANRContentMsgProc},
    {PB_INIT_EXTR_CONTENT,  SI_PB_InitEXTRContentReq,   SI_PB_InitEXTRContentMsgProc},
    {PB_INIT_XDN_CONTENT,   SI_PB_InitXDNContentReq,    SI_PB_InitXDNContentMsgProc},
    {PB_INIT_EXT_CONTENT,   SI_PB_InitEXTContentReq,    SI_PB_InitEXTContentMsgProc},
    {PB_INIT_PBC_CONTENT,   SI_PB_InitPBCContentReq,    SI_PB_InitPBCContentMsgProc},
    {PB_INIT_IAP_SEARCH,    SI_PB_InitIAPSearchReq,     SI_PB_InitIAPSearchMsgProc},
    {PB_INIT_IAP_CONTENT2,  SI_PB_InitIAPContentReq2,   SI_PB_InitIAPContentMsgProc2},
    {PB_INIT_EML_SEARCH,    SI_PB_InitEmailSearchReq,   SI_PB_InitEmailSearchMsgProc},
    {PB_INIT_EML_CONTENT2,  SI_PB_InitEmailContentReq,  SI_PB_InitEmailContentMsgProc},
    {PB_INIT_ANR_SEARCH,    SI_PB_InitANRSearchReq,     SI_PB_InitANRSearchMsgProc},
    {PB_INIT_ANR_CONTENT2,  SI_PB_InitANRContentReq2,   SI_PB_InitANRContentMsgProc2},
    {PB_INIT_XDN_SEARCH,    SI_PB_InitXDNSearchReq,     SI_PB_InitXDNSearchMsgProc},
    {PB_INIT_XDN_CONTENT2,  SI_PB_InitXDNContentReq2,   SI_PB_InitXDNContentMsgProc2},
    {PB_INIT_PBC_SEARCH,    SI_PB_InitPBCSearchReq,     SI_PB_InitPBCSearchMsgProc},
    {PB_INIT_PBC_CONTENT2,  SI_PB_InitPBCContentReq2,   SI_PB_InitPBCContentMsgProc2},
    {PB_INIT_SYNCH,         SI_PB_InitSYNCHReq,         SI_PB_InitSYNCHProc},
    {PB_INIT_INFO_APP,      SI_PB_InitInfoApp,          SI_PB_InitInfoAppDebug}
};

VOS_UINT32 SI_PBInitMsgProc (PBMsgBlock *pMsg)
{
    VOS_UINT32                          ulResult = VOS_OK;

    switch (pMsg->ulMsgName)
    {
        case USIMM_CARDSTATUS_IND:/*??????????????????????????????*/
        case USIMM_QUERYFILE_CNF:
        case USIMM_READFILE_CNF:
        case USIMM_UPDATEFILE_CNF:
        case USIMM_SEARCHFILE_CNF:
            if (USIMM_CARDSTATUS_IND == pMsg->ulMsgName)
            {
                gstPBInitState.enPBInitStep = PB_INIT_PB_STATUS;
            }

            gstPBInitState.enReqStatus = PB_REQ_NOT_SEND;

            gastPBInitProc[gstPBInitState.enPBInitStep].pInitProcFun(pMsg);

            SI_PB_InitPBStateProc(gstPBInitState.enPBInitState);

            while( PB_REQ_SEND != gstPBInitState.enReqStatus )
            {
                if ( VOS_OK != gastPBInitProc[gstPBInitState.enPBInitStep].pReqFun())
                {
                    PB_ERROR_LOG("SI_PBInitMsgProc:Send Init Request Error");

                    break;
                }
            }

            break;
        case USIMM_ECCNUMBER_IND:
            ulResult = SI_PB_InitEccProc(pMsg);
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case USIMM_XECCNUMBER_IND:
            ulResult = SI_PB_InitXeccProc(pMsg);
            break;
#endif


        case USIMM_STKREFRESH_IND:
            SI_PB_PihRefreshIndProc((USIMM_STKREFRESH_IND_STRU *)pMsg);
            break;

        default:
            break;
    }

    if(VOS_OK !=  ulResult)
    {
        PB_ERROR_LOG("SI_PBInitMsgProc:Process Message Error");
    }

    return ulResult;
}
#endif


VOS_VOID SI_PB_InitGlobeVariable(VOS_VOID)
{
    (VOS_VOID)memset_s(&gstIAPContent, sizeof(gstIAPContent), 0, sizeof(gstIAPContent));

    (VOS_VOID)memset_s(&gstPBCtrlInfo, sizeof(gstPBCtrlInfo), 0, sizeof(gstPBCtrlInfo));

    (VOS_VOID)memset_s(&gstPBInitState, sizeof(gstPBInitState), 0, sizeof(gstPBInitState));

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    if ((PB_INITIALISED != gastPBContent[PB_ECC_CONTENT].enInitialState)
      &&(PB_INITIALISED != gastPBContent[PB_XECC_CONTENT].enInitialState))
    {
        (VOS_VOID)memset_s(&gastPBContent[PB_ECC_CONTENT], sizeof(gastPBContent), 0, sizeof(gastPBContent));
    }
    else
    {
        (VOS_VOID)memset_s(&gastPBContent[PB_ADN_CONTENT], sizeof(SI_PB_CONTENT_STRU), 0, sizeof(SI_PB_CONTENT_STRU));
        (VOS_VOID)memset_s(&gastPBContent[PB_FDN_CONTENT], sizeof(SI_PB_CONTENT_STRU), 0, sizeof(SI_PB_CONTENT_STRU));
        (VOS_VOID)memset_s(&gastPBContent[PB_BDN_CONTENT], sizeof(SI_PB_CONTENT_STRU), 0, sizeof(SI_PB_CONTENT_STRU));
        (VOS_VOID)memset_s(&gastPBContent[PB_MSISDN_CONTENT], sizeof(SI_PB_CONTENT_STRU), 0, sizeof(SI_PB_CONTENT_STRU));
        (VOS_VOID)memset_s(&gastPBContent[PB_SDN_CONTENT], sizeof(SI_PB_CONTENT_STRU), 0, sizeof(SI_PB_CONTENT_STRU));
    }

    (VOS_VOID)memset_s(&gstPBSearchCtrlInfo, sizeof(SI_PB_SEARCH_CTRL_STRU), (VOS_CHAR)0xFF, sizeof(SI_PB_SEARCH_CTRL_STRU));

    /*????PB????????NV??*/
    if(NV_OK != mdrv_nv_read(en_NV_Item_Usim_PB_Ctrl_Info,
                        (VOS_VOID*)&gstPBConfigInfo, sizeof(SI_PB_CTRL_INFO_ST)))
    {
        /*????????????????*/
        gstPBConfigInfo.ucSPBFlag = 0;

        PB_ERROR_LOG("SI_PB_InitGlobeVariable:Read NV Fail!!");
    }

    if(gstPBConfigInfo.ucAnrMaxNum > SI_PB_ANRMAX)
    {
        gstPBConfigInfo.ucAnrMaxNum = 1;
    }
#endif

    (VOS_VOID)memset_s(&gastEXTContent[0], SI_PB_MAX_NUMBER * sizeof(SI_EXT_CONTENT_STRU), 0, SI_PB_MAX_NUMBER * sizeof(SI_EXT_CONTENT_STRU));

    (VOS_VOID)memset_s(&gastANRContent[0], SI_PB_ANRMAX * sizeof(SI_ANR_CONTENT_STRU), 0, SI_PB_ANRMAX * sizeof(SI_ANR_CONTENT_STRU));

    (VOS_VOID)memset_s(&gstEMLContent, sizeof(SI_EML_CONTENT_STRU), 0, sizeof(SI_EML_CONTENT_STRU));

    (VOS_VOID)memset_s(&gstPBReqUnit, sizeof(SI_PB_REQ_UINT_STRU), 0, sizeof(SI_PB_REQ_UINT_STRU));

    (VOS_VOID)memset_s(gstPBCtrlInfo.astADNInfo, sizeof(gstPBCtrlInfo.astADNInfo), 0xFF, sizeof(gstPBCtrlInfo.astADNInfo));

    gstPBCtrlInfo.enPBCurType = SI_PB_STORAGE_SM;

    /*????????????????????????????????????????*/
    gastPBContent[PB_ECC_CONTENT].enPBType         = PB_ECC;

    gastPBContent[PB_ECC_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_ADN_CONTENT].enPBType         = PB_ADN;

    gastPBContent[PB_ADN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_FDN_CONTENT].enPBType         = PB_FDN;

    gastPBContent[PB_FDN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_BDN_CONTENT].enPBType         = PB_BDN;

    gastPBContent[PB_BDN_CONTENT].enActiveStatus   = SI_PB_ACTIVE;

    gastPBContent[PB_MSISDN_CONTENT].enPBType       = PB_MISDN;

    gastPBContent[PB_MSISDN_CONTENT].enActiveStatus = SI_PB_ACTIVE;

    gastPBContent[PB_SDN_CONTENT].enPBType          = PB_SDN;

    gastPBContent[PB_SDN_CONTENT].enActiveStatus    = SI_PB_ACTIVE;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    gastPBContent[PB_XECC_CONTENT].enPBType         = PB_XECC;

    gastPBContent[PB_XECC_CONTENT].enActiveStatus   = SI_PB_ACTIVE;
#endif

    return;
}


VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase)
{
    switch (InitPhrase)
    {
        case   VOS_IP_LOAD_CONFIG:
            SI_PB_InitGlobeVariable();
            break;

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)||(VOS_WIN32 == VOS_OS_VER))
        case   VOS_IP_RESTART:
            break;
#endif

        default:
            break;
    }
    return VOS_OK;

}



#if (OSA_CPU_ACPU == VOS_OSA_CPU)
SI_PB_PROC_LIST_STRU    gastPBReqProc[] =
{
    {SI_PB_READ_REQ,        SI_PB_ReadProc},        /*??????????*/
    {SI_PB_SEARCH_REQ,      SI_PB_SearchProc},      /*??????????*/
    {SI_PB_SREAD_REQ,       SI_PB_SReadProc},       /*??????????????*/
    {SI_PB_UPDATE_AGOBAL,   SI_PBUpdateAGlobal},    /*????????????*/
    {SI_PB_UPDATE_CURPB,    SI_PBUpdateACurPB},     /*??????????????????*/
};
#endif    /*(OSA_CPU_ACPU == VOS_OSA_CPU)*/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
SI_PB_PROC_LIST_STRU    gastPBReqProc[] =
{
    {SI_PB_SET_REQ,         SI_PB_SetProc},         /*??????????????*/
    {SI_PB_MODIFY_REQ,      SI_PB_ModifyProc},      /*??????????*/
    {SI_PB_DELETE_REQ,      SI_PB_DeleteProc},      /*??????????*/
    {SI_PB_QUERY_REQ,       SI_PB_QueryProc},       /*??????????????????*/
    {SI_PB_ADD_REQ,         SI_PB_AddProc},         /*??????????*/
    {SI_PB_SMODIFY_REQ,     SI_PB_SModifyProc},     /*??????????????*/
    {SI_PB_SADD_REQ,        SI_PB_SAddProc},        /*??????????*/
    {SI_PB_FDN_CHECK_REQ,   SI_PB_FDNCheckProc},    /*FDN????????*/
    {SI_PB_ECALL_QRY_REQ,   SI_PB_EcallNumberQryProc}, /*ECALL????????*/
};
#endif    /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/

VOS_VOID I0_SI_PB_PidMsgProc(struct MsgCB *pstPBMsg)
{
    VOS_UINT32 ulResult = VOS_ERR;
    VOS_UINT32 i;

    /*????Ccpu????????USIMM??????????*/
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    USIMM_CARDSTATUS_IND_STRU          *pstCardMsg = VOS_NULL_PTR;

    if (pstPBMsg == VOS_NULL_PTR)
    {
        PB_WARNING_LOG("I0_SI_PB_PidMsgProc: null msg");

        return;
    }

    if ((WUEPS_PID_USIM == pstPBMsg->ulSenderPid) || (MAPS_PIH_PID == pstPBMsg->ulSenderPid))
    {
        if (USIMM_CARDSTATUS_IND == ((PBMsgBlock*)pstPBMsg)->ulMsgName)
        {
            pstCardMsg = (USIMM_CARDSTATUS_IND_STRU*)pstPBMsg;

            if (USIMM_CARD_STATUS_INIT_IND != pstCardMsg->stAddInfo.enStatusType)
            {
                PB_NORMAL1_LOG("I0_SI_PB_PidMsgProc:No Need Init Pb ", pstCardMsg->stAddInfo.enStatusType);

                return;
            }
        }

        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_2, pstPBMsg->ulSenderPid, MAPS_PB_PID, ((PBMsgBlock*)pstPBMsg)->ulMsgName);

        if(PB_INIT_FINISHED != gstPBInitState.enPBInitStep) /*????????????????????*/
        {
            ulResult = SI_PBInitMsgProc((PBMsgBlock*)pstPBMsg);
        }
        else
        {
            ulResult = SI_PBUsimMsgProc((PBMsgBlock*)pstPBMsg);
        }

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_2);
    }
    else
#endif
    {
        for(i=0; i<(sizeof(gastPBReqProc)/sizeof(SI_PB_PROC_LIST_STRU)); i++)
        {
            if(gastPBReqProc[i].ulMsgType == ((PBMsgBlock*)pstPBMsg)->ulMsgName)
            {
                ulResult = gastPBReqProc[i].pProcFun((PBMsgBlock*)pstPBMsg); /*????????????*/
                break;
            }
        }
    }

    if(VOS_OK !=  ulResult)
    {
        PB_ERROR_LOG("SI_PB_PidMsgProc:Process Message Error");
    }

    return;
}


extern TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent);

VOS_UINT32 SI_PBCallback(SI_PB_EVENT_INFO_STRU *pstEvent)
{
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    MN_APP_PB_AT_CNF_STRU   *pstMsg = VOS_NULL_PTR; /*??????AT??????*/
#endif

    if(pstEvent->PBError != TAF_ERR_NO_ERROR)
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*????*/
    }
    else if((pstEvent->PBEventType != SI_PB_EVENT_READ_CNF)&&
            (pstEvent->PBEventType != SI_PB_EVENT_SREAD_CNF)&&
            (pstEvent->PBEventType != SI_PB_EVENT_SEARCH_CNF))
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*????*/
    }
    else if(pstEvent->PBLastTag == VOS_TRUE)
    {
        gstPBReqUnit.enPBLock = PB_UNLOCK;/*????*/
    }
    else
    {

    }

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)||(VOS_OS_VER == VOS_WIN32))
    At_PbCallBackFunc(pstEvent);
#endif

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)&&(VOS_OS_VER != VOS_WIN32))
    pstMsg = (MN_APP_PB_AT_CNF_STRU*)VOS_AllocMsg(MAPS_PB_PID,
                                    sizeof(MN_APP_PB_AT_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)  /*??????????????????*/
    {
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = WUEPS_PID_AT;
    pstMsg->ulMsgId       = PB_AT_EVENT_CNF;

    (VOS_VOID)memcpy_s(&pstMsg->stPBAtEvent, sizeof(SI_PB_EVENT_INFO_STRU), pstEvent, sizeof(SI_PB_EVENT_INFO_STRU));

    if(VOS_OK != VOS_SendMsg(MAPS_PB_PID, pstMsg))
    {
        PB_ERROR_LOG("SI_PBCallback:Send AT Msg Error");

        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

#endif /* (FEATURE_OFF == FEATURE_PHONE_SC) */


