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

#include "AtCheckFunc.h"
#include "AtTypeDef.h"
#include "at_common.h"
#include "AtCtx.h"
#include "securec.h"


#define    THIS_FILE_ID        PS_FILE_ID_AT_CHECKFUNC_C


VOS_UINT32 atCheckBasicCmdName( VOS_UINT8 Char )
{
    if(    (Char == 'e') || (Char == 'E') || (Char == 'v') || (Char == 'V')
        || (Char == 'a') || (Char == 'A') || (Char == 'h') || (Char == 'H')
        || (Char == '&') || (Char == 'F') || (Char == 'f')
        || (Char == 'i') || (Char == 'I') || (Char == 't') || (Char == 'T')
        || (Char == 'p') || (Char == 'P') || (Char == 'x') || (Char == 'X')
        || (Char == 'z') || (Char == 'Z') || (Char == 'c') || (Char == 'C')
        || (Char == 'd') || (Char == 'D') || (Char == 'q') || (Char == 'Q')
        || (Char == 's') || (Char == 'S') || (Char == 'o') || (Char == 'O')
        || (Char == 'l') || (Char == 'L') || (Char == 'm') || (Char == 'M')
      )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}





/******************************************************************************
 ????????: ??????????????????(0x??0X)

 ????????:
   Char [in] ????????????

 ?? ?? ??: AT_SUCCESS --- ????
           AT_FAILURE --- ????
******************************************************************************/
VOS_UINT32 atCheckHex(VOS_UINT8 Char)
{
    if(Char == 'x' || Char == 'X')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}


/******************************************************************************
 ????????: ??????????????????????

 ????????:
   Char [in] ????????????

 ?? ?? ??: AT_SUCCESS --- ????
           AT_FAILURE --- ????
******************************************************************************/
VOS_UINT32 atCheckHexNum(VOS_UINT8 Char)
{
    if(isdigit(Char)
        || (Char >= 'a' && Char <= 'f')
        || (Char >= 'A' && Char <= 'F'))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}



/******************************************************************************
 ????????: ??????????????????????????????

 ????????:
   Char [in] ????????????

 ?? ?? ??: AT_SUCCESS --- ????
           AT_FAILURE --- ????
******************************************************************************/
VOS_UINT32 atNoQuotLetter(VOS_UINT8 Char)
{
    if(Char == '@')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}



VOS_UINT32 atCheckblank( VOS_UINT8 Char )
{
    /* ????-???????????? */
    if(Char == ' ')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}



VOS_UINT32 atCheckComma( VOS_UINT8 Char )
{
    if( Char == ',' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}


VOS_UINT32 atCheckColon( VOS_UINT8 Char )
{
    if( Char == ':' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}



VOS_UINT32 atCheckChar0x2f( VOS_UINT8 Char )
{
    if( Char == '/')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}


/******************************************************************************
 ????????: ????????????????????

 ????????:
   usLen [in]     ????????
   pcTmp [in] ??????

 ?? ?? ??:
    AT_SUCCESS : ????
    AT_FAILURE : ??????
******************************************************************************/
static VOS_UINT32 checkHexNumString(VOS_UINT16 usLen,  VOS_UINT8 *pcData)
{
    VOS_UINT16 usLength = 2;          /* ??0x?????????? */
    VOS_UINT8 *pcTmp    = pcData + 2; /* ??0x?????????? */

    /* ????????????????????????NULL, ???????????? */

    while(usLength++ < usLen)
    {
        /* ?????????????? */
        if(isdigit(*pcTmp)
            || (*pcTmp >= 'A' && *pcTmp <= 'F')
            || (*pcTmp >= 'a' && *pcTmp <= 'f'))
        {
            pcTmp++;
        }
        else
        {
            return AT_FAILURE;
        }
    }

    return AT_SUCCESS;
}


/******************************************************************************
 ????????: ??????????????????

 ????????:
   usLen [in]     ????????
   pcTmp [in] ??????

 ?? ?? ??:
    AT_SUCCESS : ????
    AT_FAILURE : ??????
******************************************************************************/
static VOS_UINT32 checkDecNumString(VOS_UINT16 usLen,  VOS_UINT8 *pcData)
{
    VOS_UINT16 usLength = 0;      /* ??0?????????? */
    VOS_UINT8 *pcTmp    = pcData; /* ??0?????????? */

    /* ????????????????????????NULL, ???????????? */

    while(usLength++ < usLen)
    {
        /* ?????????????? */
        if(isdigit(*pcTmp))
        {
            pcTmp++;
        }
        else
        {
            return AT_FAILURE;
        }
    }

    return AT_SUCCESS;
}


/******************************************************************************
 ????????: ??????????????

 ????????:
   pData [in] ??????????????
   usLen [in] ????????????

 ?? ?? ??: AT_SUCCESS --- ????
           AT_FAILURE --- ????
******************************************************************************/
VOS_UINT32 atCheckNumString( VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT8 *pcTmp    = pData;

    if((pData == NULL) || (usLen == 0))
    {
        return AT_FAILURE;
    }

    pcTmp = pData;

    if(*pcTmp == '0')
    {
        if(usLen > 2 && ((*(pcTmp + 1) == 'x') || (*(pcTmp + 1) == 'X')))
        {
            return checkHexNumString(usLen, pcTmp);
        }
        else
        {
        }
    }

    return checkDecNumString(usLen, pcTmp);
}



VOS_UINT32 atCheckRightArrowStr( VOS_UINT8 *pData,VOS_UINT16 usLen )
{
    VOS_UINT16 usLength = 0;
    VOS_UINT8 *pcTmp    = pData;

    while( usLength++ < usLen )
    {
        /* ??????????MMI???? */
        if(*pcTmp == '>')
        {
            return AT_SUCCESS;
        }
        else
        {
            pcTmp++;
        }
    }
    return AT_FAILURE;
}


VOS_UINT32 atCheckMmiString( VOS_UINT8 *pData,VOS_UINT16 usLen )
{
    VOS_UINT16 usLength = 0;
    VOS_UINT8 *pcTmp    = pData;

    while( usLength++ < usLen )
    {
        /* ??????????MMI???? */
        if((*pcTmp == '*') || (*pcTmp == '#') )
        {
            return AT_SUCCESS;
        }
        else
        {
            pcTmp++;
        }
    }
    return AT_FAILURE;
}



VOS_UINT32 At_CheckStringPara( AT_PARSE_PARA_TYPE_STRU *pPara)
{
    VOS_UINT8 *pData = pPara->aucPara;

    /* ???????????????? */
    if (pPara->usParaLen < 2)
    {
        return AT_FAILURE;
    }

    if ( (*pData != '"') || (*((pData + pPara->usParaLen) - 1) != '"'))
    {
        return AT_FAILURE;
    }

    /* ???????????????? */
    pPara->usParaLen -= 2;       /*????????????*/
    TAF_MEM_MOVE_S(pData, sizeof(pPara->aucPara), pData+1, pPara->usParaLen);

    pData[pPara->usParaLen] = '\0';

    return AT_SUCCESS;
}


/******************************************************************************
 ????????: ????????????????????????????????

 ????????:
   pPara [in/out] ??????????????

 ?? ?? ??: AT_SUCCESS --- ???????????????? "
           AT_FAILURE --- ?????????????????? "
******************************************************************************/
VOS_UINT32 atCheckNoQuotStringPara( AT_PARSE_PARA_TYPE_STRU *pPara)
{
    VOS_UINT8 *pData = pPara->aucPara;

    /* ???????????????????????? */
    if ( (*pData == '"') && (*((pData + pPara->usParaLen) - 1) == '"'))
    {
        if (pPara->usParaLen < 2)
        {
            return AT_FAILURE;
        }

        /* ???????????????? */
        pPara->usParaLen -= 2;       /*????????????*/
        TAF_MEM_MOVE_S(pData, sizeof(pPara->aucPara), pData+1, pPara->usParaLen);

        pData[pPara->usParaLen] = '\0';
    }

    return AT_SUCCESS;
}



VOS_UINT32 atCheckNumPara(AT_PARSE_PARA_TYPE_STRU *pPara)
{
    VOS_UINT32 i  = 0;

    /* ?????????? */
    if(atCheckNumString(pPara->aucPara,pPara->usParaLen) == AT_SUCCESS)
    {
        if(atAuc2ul(pPara->aucPara,pPara->usParaLen,&pPara->ulParaValue) != AT_SUCCESS)
        {
            return AT_FAILURE;
        }

        for(i = 0; i< g_stATParseCmd.ucParaNumRangeIndex; i++)
        {
            /* ?????????????? */
            if( (g_stATParseCmd.astParaNumRange[i].ulSmall <= pPara->ulParaValue)
                && (pPara->ulParaValue <= g_stATParseCmd.astParaNumRange[i].ulBig) )
            {
                return AT_SUCCESS;
            }
        }
    }

    return AT_FAILURE;
}


VOS_UINT32 atCheckCharPara( AT_PARSE_PARA_TYPE_STRU *pPara)
{
    VOS_UINT8                           pBuf[AT_PARA_MAX_LEN + 1] = {0};
    errno_t                             lMemResult;
    VOS_UINT8                           ucIndex  = 0;

    lMemResult = memcpy_s(pBuf, sizeof(pBuf), pPara->aucPara, pPara->usParaLen);
    TAF_MEM_CHK_RTN_VAL(lMemResult, sizeof(pBuf), pPara->usParaLen);

    At_UpString(pBuf, pPara->usParaLen);

    pBuf[pPara->usParaLen] = '\0';

    for(ucIndex = 0; ucIndex < g_stATParseCmd.ucParaStrRangeIndex; ucIndex++)
    {
        if(AT_STRCMP((VOS_CHAR *)g_stATParseCmd.auStrRange[ucIndex],(VOS_CHAR *)pBuf) == 0)
        {
            pPara->ulParaValue = ucIndex;

            return AT_SUCCESS;
        }
    }

    return AT_FAILURE;
}


/*****************************************************************************
 Prototype      : At_CheckSemicolon
 Description    : ??????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckSemicolon( TAF_UINT8 Char )
{
    if( Char == ';' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckDialNum( TAF_UINT8 Char )
{
    if ((Char >= '0') && (Char <= '9'))
    {
        return AT_SUCCESS;
    }
    else if ((Char >= 'a') && (Char <= 'c'))
    {
        return AT_SUCCESS;
    }
    else if ((Char >= 'A') && (Char <= 'C'))
    {
        return AT_SUCCESS;
    }
    else if ((Char == '*') || (Char == '#') || (Char == '+'))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckDmChar( TAF_UINT8 Char )
{
    if( (Char != '*') && (Char != '#') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckCharStar
 Description    : ??????????????*
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckCharStar( TAF_UINT8 Char )
{
    if( Char == '*' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckCharWell
 Description    : ??????????????#
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckCharWell( TAF_UINT8 Char )
{
    if( Char == '#' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckCharRightArrow
 Description    : ??????????????>
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckCharRightArrow( TAF_UINT8 Char )
{
    if( Char == '>' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharG( TAF_UINT8 Char )
{
    if((Char == 'G') || (Char == 'g'))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharI( TAF_UINT8 Char )
{
    if((Char == 'I') || (Char == 'i'))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharS( TAF_UINT8 Char )
{
    if( (Char == 's') || (Char == 'S') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharD( TAF_UINT8 Char )
{
    if( (Char == 'd') || (Char == 'D') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckBasicCmdName( TAF_UINT8 Char )
{
    if( (Char == 'e') || (Char == 'E') || (Char == 'v') || (Char == 'V')
        || (Char == 'a') || (Char == 'A') || (Char == 'h') || (Char == 'H')
        || (Char == '&') || (Char == 'F') || (Char == 'f') || (Char == 'i')
        || (Char == 'I') || (Char == 'T') || (Char == 't') || (Char == 'P')
        || (Char == 'p') || (Char == 'X') || (Char == 'x') || (Char == 'Z')
        || (Char == 'z') || (Char == 'C') || (Char == 'c') || (Char == 'D')
        || (Char == 'd') || (Char == 'Q') || (Char == 'q')
        )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharA( TAF_UINT8 Char )
{
    if( (Char == 'a') || (Char == 'A') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharT( TAF_UINT8 Char )
{
    if( (Char == 't') || (Char == 'T') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharPlus( TAF_UINT8 Char )
{
    if( (Char == '+') || (Char == '^') || (Char == '$'))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckLeftBracket
 Description    : ??????????????(
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckLeftBracket( TAF_UINT8 Char )
{
    if(Char == '(')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckRightBracket
 Description    : ??????????????)
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckRightBracket( TAF_UINT8 Char )
{
    if(Char == ')')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckDigit( TAF_UINT8 Char )
{
    if( (Char >= '0') && (Char <= '9') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckLetter( TAF_UINT8 Char )
{
    if( ((Char >= 'a') && (Char <= 'z')) || ((Char >= 'A') && (Char <= 'Z')) || (Char == '_') || (Char == '&'))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckUpLetter( TAF_UINT8 Char )
{
    if( (Char >= 'A') && (Char <= 'Z') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckChar( TAF_UINT8 Char )
{
    if( ((Char >= 'a') && (Char <= 'z')) || ((Char >= 'A') && (Char <= 'Z')) || ((Char >= '0') && (Char <= '9')) || (Char == '*') || (Char == '#') || (Char == '-') || (Char == '.') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
 Prototype      : At_CheckAlpha
 Description    : ??????????????('a'~'z' ??'A'~'Z')
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2010-07-1
    Author      : ---
    Modification: Created function
*****************************************************************************/

TAF_UINT32 At_CheckAlpha( TAF_UINT8 Char )
{
    if( ((Char >= 'a') && (Char <= 'z')) || ((Char >= 'A') && (Char <= 'Z')) )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckColon
 Description    : ??????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckColon( TAF_UINT8 Char )
{
    if( Char == ',' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckCharSub
 Description    : ??????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckCharSub( TAF_UINT8 Char )
{
    if( Char == '-' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckQuot
 Description    : ??????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckQuot( TAF_UINT8 Char )
{
    if( Char == '"' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckHorizontalLine( TAF_UINT8 Char )
{
    if( Char == '-' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
 Prototype      : At_CheckEqu
 Description    : ??????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckEqu( TAF_UINT8 Char )
{
    if( Char == '=' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckReq
 Description    : ??????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckReq( TAF_UINT8 Char )
{
    if( Char == '?' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckNoQuot
 Description    : ????????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckNoQuot( TAF_UINT8 Char )
{
    if( Char != '"' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharE( TAF_UINT8 Char )
{
    if( (Char == 'e') || (Char == 'E') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckChar1
 Description    : ??????????????1
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckChar1( TAF_UINT8 Char )
{
    if( Char == '1')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckChar0
 Description    : ??????????????0
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckChar0( TAF_UINT8 Char )
{
    if( Char == '0')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharV( TAF_UINT8 Char )
{
    if( (Char == 'v') || (Char == 'V') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckCharF( TAF_UINT8 Char )
{
    if( (Char == 'f') || (Char == 'F') )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}
/*****************************************************************************
 Prototype      : At_CheckCharE
 Description    : ??????????????&
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckChar0x26( TAF_UINT8 Char )
{
    if( Char == '&')
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

TAF_UINT32 At_CheckNumString( TAF_UINT8 *pData,TAF_UINT16 usLen )
{
    TAF_UINT16 usLength = 0;
    TAF_UINT8 *pcTmp    = pData;

    if( (pData == TAF_NULL_PTR) || (usLen == 0) )
    {
        return AT_FAILURE;
    }

    pcTmp = pData;

    while( usLength++ < usLen )
    {
        /*??????????????*/
        if( (*pcTmp >= '0') && (*pcTmp <= '9') )
        {
            pcTmp++;
        }
        else
        {
            return AT_FAILURE;
        }
    }
    return AT_SUCCESS;
}


TAF_UINT32 At_CheckNumCharString( TAF_UINT8 *pData,TAF_UINT16 usLen )
{
    TAF_UINT16 usLength = 0;
    TAF_UINT8 *pcTmp    = pData;
    TAF_UINT32 ulCheckDigitRslt;
    TAF_UINT32 ulCheckCharRslt;

    if( (pData == TAF_NULL_PTR) || (usLen == 0) )
    {
        return AT_FAILURE;
    }

    pcTmp = pData;

    while( usLength++ < usLen )
    {
       ulCheckDigitRslt = At_CheckDigit(*pcTmp);
       ulCheckCharRslt = At_CheckAlpha(*pcTmp);

       if ((ulCheckDigitRslt == AT_SUCCESS)|| (ulCheckCharRslt == AT_SUCCESS))
       {
            pcTmp++;
       }
       else
       {
            return AT_FAILURE;
       }
    }
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_CheckRightArrowStr
 Description    : ??????????????
 Input          : pData --- ??????????????
                  usLen --- ????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckRightArrowStr( TAF_UINT8 *pData,TAF_UINT16 usLen )
{
    TAF_UINT16 usLength = 0;
    TAF_UINT8 *pcTmp    = pData;

    while( usLength++ < usLen )
    {
        /*??????????MMI????*/
        if(*pcTmp == '>')
        {
            return AT_SUCCESS;
        }
        else
        {
            pcTmp++;
        }
    }
    return AT_FAILURE;
}

TAF_UINT32 At_CheckMmiString( TAF_UINT8 *pData,TAF_UINT16 usLen )
{
    TAF_UINT16 usLength = 0;
    TAF_UINT8 *pcTmp    = pData;

    while( usLength++ < usLen )
    {
        /*??????????MMI????*/
        if((*pcTmp == '*') || (*pcTmp == '#') )
        {
            return AT_SUCCESS;
        }
        else
        {
            pcTmp++;
        }
    }
    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_CheckJuncture
 Description    : ????????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_CheckJuncture( VOS_UINT8 Char )
{
    if( Char == '-' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
 Prototype      : At_CheckEnd
 Description    : ????????????????
 Input          : Char---????????????
 Output         : ---
 Return Value   : AT_SUCCESS --- ????
                  AT_FAILURE --- ????
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_CheckEnd( VOS_UINT8 Char )
{
    if( Char == '\0' )
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}


VOS_UINT32 AT_CheckDateFormat(
    VOS_UINT8                           *pucDateStr,
    VOS_UINT32                          ulDateStrLen
)
{
    VOS_UINT8                           ucFirstJuncture;
    VOS_UINT8                           ucSecondJuncture;
    VOS_UINT8                           ucFirstColon;
    VOS_UINT8                           ucSecondColon;
    VOS_UINT8                           ucSpace;

    /* ??????2009-12-31 10:10:10????????????: ????????????19 */
    if (ulDateStrLen != 19)
    {
        AT_NORM_LOG1("AT_CheckDateFormat: length error.", (VOS_INT32)ulDateStrLen);
        return AT_ERROR;
    }

    /* ??????2009-12-31 10:10:10????????????: ??5????????'-', ??8????????'-' */
    ucFirstJuncture     = *(pucDateStr + 4);
    ucSecondJuncture    = *(pucDateStr + 7);
    if ((ucFirstJuncture != '-') || (ucSecondJuncture != '-'))
    {
        AT_NORM_LOG("AT_CheckDateFormat: Fail to check juncture.");
        return AT_ERROR;
    }

    /* ??????2009-12-31 10:10:10????????????: ??11????????' ' */
    ucSpace = *(pucDateStr + 10);
    if (ucSpace != ' ')
    {
        AT_NORM_LOG("AT_CheckDateFormat: Fail to check space.");
        return AT_ERROR;
    }

    /* ??????2009-12-31 10:10:10????????????: ??14????????':' ??17????????':' */
    ucFirstColon    = *(pucDateStr + 13);
    ucSecondColon   = *(pucDateStr + 16);
    if ((ucFirstColon != ':') || (ucSecondColon != ':'))
    {
        AT_NORM_LOG("AT_CheckDateFormat: Fail to check colon.");
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32 AT_GetDaysForEachMonth(
    VOS_UINT32                          ulYear,
    VOS_UINT32                          ulMonth
)
{
    if ((ulMonth == 1) || (ulMonth == 3) || (ulMonth == 5) || (ulMonth == 7)
     || (ulMonth == 8) || (ulMonth == 10) || (ulMonth == 12) )
    {
        /* 1,3,5,7,8,10,12????31?? */
        return 31;
    }
    else if ((ulMonth == 4) || (ulMonth == 6) || (ulMonth == 9) || (ulMonth == 11))
    {
        /* 4,6,9,11????30?? */
        return 30;
    }
    else
    {
        /* 2??????????????????????29??????????28?? */
        if ( (((ulYear % 4) == 0) && ((ulYear % 100) != 0)) || ((ulYear % 400) == 0))
        {
            /* ???? */
            return 29;
        }
        else
        {
            /* ?????? */
            return 28;
        }
    }
}


VOS_UINT32  AT_CheckDate(
    AT_DATE_STRU                        *pstDate
)
{
    VOS_UINT32                          ulDaysEachMonth;

    /* ??????????????: ????????????????0????????????12 */
    if ((pstDate->ulMonth > 12)
     || (pstDate->ulMonth == 0))
    {
        AT_NORM_LOG("AT_CheckDate: Fail to check month.");
        return AT_ERROR;
    }

    /* ??????????????: ????????????????0???????????????????????? */
    ulDaysEachMonth = AT_GetDaysForEachMonth(pstDate->ulYear, pstDate->ulMonth);
    if ((pstDate->ulDay > ulDaysEachMonth)
     || (pstDate->ulDay == 0))
    {
        AT_NORM_LOG("AT_CheckDate: Fail to check day.");
        return AT_ERROR;
    }

    /* ??????????????: ??????????????24????????????????????60 */
    if ((pstDate->ulHour >= 24)
     || (pstDate->ulMunite >= 60)
     || (pstDate->ulSecond >= 60))
    {
        AT_NORM_LOG("AT_CheckDate: Fail to check time.");
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32  AT_GetDate(
    VOS_UINT8                           *pucDateStr,
    VOS_UINT32                          ulDateStrLen,
    AT_DATE_STRU                        *pstDate
)
{
    VOS_UINT32                          ulRet;

    /* ????????????????: ????????4?????? */
    ulRet = At_Auc2ul(pucDateStr, 4, &pstDate->ulYear);
    if (ulRet != AT_SUCCESS)
    {
        AT_NORM_LOG("AT_GetDate: Fail to get year.");
        return AT_ERROR;
    }

    /* ????????????????: ????????2??????????????????????4????????'-'???????? */
    ulRet = At_Auc2ul((pucDateStr + 5), 2, &pstDate->ulMonth);
    if (ulRet != AT_SUCCESS)
    {
        AT_NORM_LOG("AT_GetDate: Fail to get month.");
        return AT_ERROR;
    }

    /* ????????????????: ????????2??????????????????????2????????'-'???????? */
    ulRet = At_Auc2ul((pucDateStr + 8), 2, &pstDate->ulDay);
    if (ulRet != AT_SUCCESS)
    {
        AT_NORM_LOG("AT_GetDate: Fail to get day.");
        return AT_ERROR;
    }

    /* ????????????????: ????????2??????????????????????2????????' '???????? */
    ulRet = At_Auc2ul((pucDateStr + 11), 2, &pstDate->ulHour);
    if (ulRet != AT_SUCCESS)
    {
        AT_NORM_LOG("AT_GetDate: Fail to get hour.");
        return AT_ERROR;
    }

    /* ????????????????: ????????2??????????????????????2????????':'???????? */
    ulRet = At_Auc2ul((pucDateStr + 14), 2, &pstDate->ulMunite);
    if (ulRet != AT_SUCCESS)
    {
        AT_NORM_LOG("AT_GetDate: Fail to get minute.");
        return AT_ERROR;
    }

    /* ????????????????: ????????2??????????????????????2????????':'???????? */
    ulRet = At_Auc2ul((pucDateStr + 17), 2, &pstDate->ulSecond);
    if (ulRet != AT_SUCCESS)
    {
        AT_NORM_LOG("AT_GetDate: Fail to get second.");
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32 At_CheckAndParsePara(
    AT_PARSE_PARA_TYPE_STRU             *pstAtPara,
    VOS_UINT8                           *pucBegain,
    VOS_UINT8                           *pucEnd
)
{
    VOS_UINT32                          ulParaLen;

    ulParaLen  = (VOS_UINT32)(pucEnd - pucBegain);

    if ((ulParaLen == 0)
     || (ulParaLen > AT_PARA_MAX_LEN))
    {
        return AT_ERROR;
    }

    pstAtPara->usParaLen = (VOS_UINT16)ulParaLen;

    At_RangeCopy(pstAtPara->aucPara, pucBegain, pucEnd);

    return AT_OK;

}


VOS_UINT32 AT_CheckStrStartWith(
    VOS_UINT8                          *pucLineStr,
    VOS_UINT16                          usLineStrLen,
    VOS_UINT8                          *pucPefixStr,
    VOS_UINT16                          usPefixStrLen
)
{
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usSafeLen;

    if (usLineStrLen < usPefixStrLen)
    {
        return VOS_FALSE;
    }

    usSafeLen = AT_MIN(usLineStrLen, usPefixStrLen);

    for (usLoop=0 ; (usLoop < usSafeLen) && (*pucLineStr != '\0') && (*pucPefixStr != '\0'); pucLineStr++, pucPefixStr++)
    {
        if (*pucLineStr != *pucPefixStr)
        {
            return VOS_FALSE;
        }

        usLoop++;
    }

    if (*pucPefixStr == '\0')
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

