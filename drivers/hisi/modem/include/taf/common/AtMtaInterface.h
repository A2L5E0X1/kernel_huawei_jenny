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

#ifndef __ATMTAINTERFACE_H__
#define __ATMTAINTERFACE_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "PsTypeDef.h"
#include "AtMnInterface.h"
#include "MtaCommInterface.h"
#include "nv_stru_sys.h"
#include "nv_stru_gucnas.h"

#include "AtParse.h"
#include "NasCommPacketSer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define MTA_CPOS_XML_MAX_LEN            (1024)              /* MTA????AT??????XML???????????? */
#define MTA_CPOSR_XML_MAX_LEN           (1024)              /* MTA??AT??????XML??????????????1024 */
#define MTA_SIMLOCK_PASSWORD_LEN        (16)                /* ?????????????????????? */
#define MTA_MAX_EPDU_NAME_LEN           (32)                /* EPDU??????????Name?????? */
#define MTA_MAX_EPDU_BODY_LEN           (500)               /* EPDU???????? */

#define MTA_CLIENTID_BROADCAST          (0xFFFF)
#define MTA_INVALID_TAB_INDEX           (0x00)


#define AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM          (10) /* autotest???????????????????? */
#define MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM         (20) /* autotest???????????????????? */
#define MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM       (8)  /* ?????????????????????????? */
#define MTA_AT_WRR_MAX_MEANRPT_NUM                (10) /* ?????????????????????????? */

#define MTA_AT_WRR_MAX_NCELL_NUM                  (8)

#define AT_MTA_GAS_AUTOTEST_MAX_PARA_NUM          (10)
#define MTA_AT_GAS_AUTOTEST_MAX_RSULT_NUM         (20) /* autotest???????????????????? */

#define AT_MTA_RPT_CFG_MAX_SIZE                   (8)

#define AT_MTA_HANDLEDECT_MIN_TYPE                (0)
#define AT_MTA_HANDLEDECT_MAX_TYPE                (4)

#define AT_RSA_CIPHERTEXT_LEN           (256)

#define  AT_MTA_INTEREST_FREQ_MAX_NUM         (0x05)
#define  AT_MTA_MBMS_AVL_SERVICE_MAX_NUM      (0x10)
#define  AT_MTA_ISMCOEX_BANDWIDTH_NUM         (0x06)

#define AT_MTA_MEID_DATA_LEN                         (7)

#define MTA_AT_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define MTA_AT_EFRUIMID_OCTET_LEN_FIVE                    (5)

#define MTA_AT_UIMID_OCTET_LEN                            (4)

#define AT_MTA_GPS_XO_COEF_NUM                       (4)

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
#define MTA_FREQLOCK_MAX_MODE                     (4)
#endif

#define MTA_AT_MAX_BESTFREQ_GROUPNUM        (8)

#define MTA_AT_MAX_DIE_ID_LEN               (32)

#define MTA_AT_MAX_RFFE_DIE_ID_LEN          (16)
#define MTA_AT_MAX_RFFE_DIE_ID_COUNT        (4)
#define MTA_AT_RFFE_DIE_ID_VALID            (1)

#define MTA_PMU_MAX_DIE_SN_LEN              (20)

#define AT_MAX_RS_INFO_NUM                  (32)    /* LRRC????RS???????? */
#define AT_RS_INFO_MULTI                    (100)   /* LRRC??RSRP??RSRQ??????100????????MTA */

#define AT_MTA_PSEUCELL_PLMN_LEN_FIVE       (5)
#define AT_MTA_PSEUCELL_PLMN_LEN_SIX        (6)
#define AT_MTA_PSEUCELL_LAC_LEN             (4)
#define AT_MTA_PSEUCELL_CELLID_LEN          (8)
#define AT_MTA_PLMN_MCC_LEN                 (3)
#define AT_MTA_PLMN_MNC_LEN_TWO             (2)
#define AT_MTA_PLMN_MNC_LEN_THREE           (3)

#define MTA_AT_PESN_NV_DATA_LEN             (4)
#define MTA_AT_MEID_NV_DATA_LEN_NEW         (7)

#define AT_MTA_EPDU_NAME_LENGTH_MAX         (32)
#define AT_MTA_EPDU_CONTENT_LENGTH_MAX      (250)
#define AT_MTA_EPDU_CONTENT_STRING_LEN_MAX  (500)

#define AT_MTA_MAX_BAND_NUM                 (8)     /* ????????8??Band */
#define AT_MTA_BAND_INFO_OFFSET             (3)     /* band?????????????? */
#define AT_MTA_MAX_SUB_BAND_NUM             (4)     /* ????Band??????????????4????BAND */
#define AT_MTA_BAND_INFO_LEN                (72)    /* ????Band?????????????? */
#define MTA_AT_CA_MAX_CELL_NUM              (8)
#define MTA_AT_UTC_MAX_LENGTH               (21)

#define MTA_AT_BOOSTER_IND_MAX_NUM          (248)      /* Booster????????????LRRC??MTA????248???????? */
#define MTA_AT_BOOSTER_QRY_CNF_MAX_NUM      (40)      /* Booster???????????????????????????? */

#define MTA_AT_EPS_NETWORK_BYTE             (2)

#define MTA_AT_MAX_STATEII_LEVEL_ITEM          4

#define AT_MTA_VERSION_INFO_LEN             (10)      /* ?????????????????????????????? */

#define UCOM_NV_DCXO_SAMPLE_H_MAX_NUM               ( 40 )

#define AT_MTA_UECAP_MAX_NR_BAND_NUM          (32)

#define AT_MTA_NRRCCAP_PARA_MAX_NUM           (10)

#define MTA_AT_MAX_CC_NUMBER                  (4)
#define MTA_AT_MAX_CODE_NUMBER                (2)
#define MTA_AT_INVALID_MCS_VALUE              (0xFF)

#define MTA_AT_MAX_ALLOWED_AND_CFG_NSSAI_PLMN_NUM           16

/*****************************************************************************
  3 ????????
*****************************************************************************/

enum AT_MTA_MSG_TYPE_ENUM
{
    /* ???????? */                      /* ????ID */        /* ????, ????ASN */
    /* AT????MTA?????? */
    ID_AT_MTA_CPOS_SET_REQ              = 0x0000,           /* _H2ASN_MsgChoice AT_MTA_CPOS_REQ_STRU        */
    ID_AT_MTA_CGPSCLOCK_SET_REQ         = 0x0001,           /* _H2ASN_MsgChoice AT_MTA_CGPSCLOCK_REQ_STRU   */
    ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ     = 0x0003,           /* _H2ASN_MsgChoice AT_MTA_SIMLOCKUNLOCK_REQ_STRU */

    ID_AT_MTA_QRY_NMR_REQ               = 0x0004,           /* _H2ASN_MsgChoice AT_MTA_QRY_NMR_REQ_STRU */

    ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF  = 0x0005,           /* _H2ASN_MsgChoice AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU */
    ID_AT_MTA_WRR_AUTOTEST_QRY_REQ      = 0x0006,           /* _H2ASN_MsgChoice AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU */
    ID_AT_MTA_WRR_CELLINFO_QRY_REQ      = 0x0007,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_MEANRPT_QRY_REQ       = 0x0008,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_FREQLOCK_SET_REQ      = 0x0009,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_CTRL_STRU     */
    ID_AT_MTA_WRR_RRC_VERSION_SET_REQ   = 0x000A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_CELLSRH_SET_REQ       = 0x000B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_FREQLOCK_QRY_REQ      = 0x000C,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ   = 0x000D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_CELLSRH_QRY_REQ       = 0x000E,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_BODY_SAR_SET_REQ          = 0x000F,           /* _H2ASN_MsgChoice AT_MTA_BODY_SAR_SET_REQ_STRU */
    ID_AT_MTA_CURC_SET_NOTIFY           = 0x0010,           /* _H2ASN_MsgChoice AT_MTA_CURC_SET_NOTIFY_STRU */
    ID_AT_MTA_CURC_QRY_REQ              = 0x0011,           /* _H2ASN_MsgChoice AT_MTA_CURC_QRY_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_SET_REQ   = 0x0012,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ   = 0x0013,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU */

    ID_AT_MTA_IMEI_VERIFY_QRY_REQ       = 0x0014,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CGSN_QRY_REQ              = 0x0015,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NCELL_MONITOR_SET_REQ     = 0x0016,           /* _H2ASN_MsgChoice AT_MTA_NCELL_MONITOR_SET_REQ_STRU */
    ID_AT_MTA_NCELL_MONITOR_QRY_REQ     = 0x0017,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_REFCLKFREQ_SET_REQ        = 0x0018,           /* _H2ASN_MsgChoice AT_MTA_REFCLKFREQ_SET_REQ_STRU */
    ID_AT_MTA_REFCLKFREQ_QRY_REQ        = 0x0019,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_HANDLEDECT_SET_REQ        = 0x001A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_HANDLEDECT_QRY_REQ        = 0x001B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_ECID_SET_REQ              = 0x001C,           /* _H2ASN_MsgChoice AT_MTA_ECID_SET_REQ_STRU */

    ID_AT_MTA_MIPICLK_QRY_REQ           = 0x001D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_DPDTTEST_FLAG_REQ     = 0x001E,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU */
    ID_AT_MTA_SET_DPDT_VALUE_REQ        = 0x001F,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDT_VALUE_REQ_STRU */
    ID_AT_MTA_QRY_DPDT_VALUE_REQ        = 0x0020,           /* _H2ASN_MsgChoice AT_MTA_QRY_DPDT_VALUE_REQ_STRU */

    ID_AT_MTA_RRC_PROTECT_PS_REQ        = 0x0021,
    ID_AT_MTA_PHY_INIT_REQ              = 0x0022,

    ID_AT_MTA_SET_JAM_DETECT_REQ        = 0x0023,           /* _H2ASN_MsgChoice AT_MTA_SET_JAM_DETECT_REQ_STRU */

    ID_AT_MTA_SET_FREQ_LOCK_REQ         = 0x0024,           /* _H2ASN_MsgChoice AT_MTA_SET_FREQ_LOCK_REQ_STRU */

    ID_AT_MTA_SET_GSM_FREQLOCK_REQ      = 0x0025,          /* _H2ASN_MsgChoice AT_MTA_SET_GSM_FREQLOCK_REQ_STRU */
    ID_AT_MTA_SET_FEMCTRL_REQ           = 0x0026,

    ID_AT_MTA_NVWRSECCTRL_SET_REQ       = 0x0027,

    ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ   = 0x0028,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU */
    ID_AT_MTA_MBMS_PREFERENCE_SET_REQ       = 0x0029,      /* _H2ASN_MsgChoice AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU */
    ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ    = 0x002A,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ     = 0x002B,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NETWORK_INFO_QRY_REQ          = 0x002C,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_EMBMS_STATUS_QRY_REQ          = 0x002D,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ  = 0x002E,      /* _H2ASN_MsgChoice AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU */
    ID_AT_MTA_LTE_LOW_POWER_SET_REQ         = 0x002F,      /* _H2ASN_MsgChoice AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU */
    ID_AT_MTA_INTEREST_LIST_SET_REQ         = 0x0030,      /* _H2ASN_MsgChoice AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU */
    ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ    = 0x0031,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU */
    ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ = 0x0032,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_SET_REQ         = 0x0033,      /* _H2ASN_MsgChoice AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ         = 0x0034,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_FR_REQ                = 0x0035,

    ID_AT_MTA_MEID_SET_REQ              = 0x0036,     /* _H2ASN_MsgChoice AT_MTA_MEID_SET_REQ_STRU */
    ID_AT_MTA_MEID_QRY_REQ              = 0x0037,

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_AT_MTA_SET_M2M_FREQLOCK_REQ      = 0x0038,           /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_REQ_STRU */
    ID_AT_MTA_QRY_M2M_FREQLOCK_REQ      = 0x0039,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
#endif

    ID_AT_MTA_TRANSMODE_QRY_REQ         = 0x0044,

    ID_AT_MTA_UE_CENTER_SET_REQ         = 0x0045,     /* _H2ASN_MsgChoice AT_MTA_SET_UE_CENTER_REQ_STRU */
    ID_AT_MTA_UE_CENTER_QRY_REQ         = 0x0046,

    ID_AT_MTA_SET_NETMON_SCELL_REQ      = 0x0047,
    ID_AT_MTA_SET_NETMON_NCELL_REQ      = 0x0048,

    ID_AT_MTA_RFICSSIRD_QRY_REQ         = 0x0049,

    ID_AT_MTA_ANQUERY_QRY_REQ           = 0x004A,
    ID_AT_MTA_CSNR_QRY_REQ              = 0x004B,
    ID_AT_MTA_CSQLVL_QRY_REQ            = 0x004C,

    ID_AT_MTA_EVDO_SYS_EVENT_SET_REQ    = 0x004d,     /* _H2ASN_MsgChoice AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU */
    ID_AT_MTA_EVDO_SIG_MASK_SET_REQ     = 0x004e,     /* _H2ASN_MsgChoice AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU */

    ID_AT_MTA_XCPOSR_SET_REQ            = 0x004F,                               /* _H2ASN_MsgChoice AT_MTA_SET_XCPOSR_REQ_STRU */
    ID_AT_MTA_XCPOSR_QRY_REQ            = 0x0050,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_XCPOSRRPT_SET_REQ         = 0x0051,                               /* _H2ASN_MsgChoice AT_MTA_SET_XCPOSRRPT_REQ_STRU */
    ID_AT_MTA_XCPOSRRPT_QRY_REQ         = 0x0052,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CLEAR_HISTORY_FREQ_REQ    = 0x0053,       /* _H2ASN_MsgChoice AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU */

    ID_AT_MTA_SET_SENSOR_REQ            = 0x0054,                               /* _H2ASN_MsgChoice AT_MTA_SET_SENSOR_REQ_STRU*/
    ID_AT_MTA_SET_SCREEN_REQ            = 0x0055,                               /* _H2ASN_MsgChoice AT_MTA_SET_SCREEN_REQ_STRU*/
    ID_AT_MTA_FRAT_IGNITION_QRY_REQ     = 0x0056,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_QRY_CNF_STRU */
    ID_AT_MTA_FRAT_IGNITION_SET_REQ     = 0x0057,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_SET_CNF_STRU */

    ID_AT_MTA_MODEM_TIME_SET_REQ        = 0x0058,

    ID_AT_MTA_RX_TEST_MODE_SET_REQ      = 0x0059,

    ID_AT_MTA_SLAVE_SET_REQ             = 0x005A,

    ID_AT_MTA_BESTFREQ_SET_REQ          = 0x005B,           /* AT_MTA_BESTFREQ_SET_REQ_STRU */
    ID_AT_MTA_BESTFREQ_QRY_REQ          = 0x005C,

    ID_AT_MTA_RFIC_DIE_ID_QRY_REQ       = 0x005D,

    ID_AT_MTA_CRRCONN_SET_REQ           = 0x005E,
    ID_AT_MTA_CRRCONN_QRY_REQ           = 0x005F,
    ID_AT_MTA_VTRLQUALRPT_SET_REQ       = 0x0060,

    ID_AT_MTA_PMU_DIE_SN_QRY_REQ        = 0x0061,

    ID_AT_MTA_MODEM_CAP_UPDATE_REQ      = 0x0062,

    ID_AT_MTA_TAS_CFG_REQ               = 0x0063,
    ID_AT_MTA_TAS_QRY_REQ               = 0x0064,

    ID_AT_MTA_MIPI_WREX_REQ              = 0x0065,
    ID_AT_MTA_MIPI_RDEX_REQ              = 0x0066,

    ID_AT_MTA_RS_INFO_QRY_REQ           = 0x0067,

    ID_AT_MTA_PHY_COM_CFG_SET_REQ       = 0x0068,

    ID_AT_MTA_ERRCCAP_CFG_SET_REQ       = 0x0069,
    ID_AT_MTA_ERRCCAP_QRY_SET_REQ       = 0x006A,

    ID_AT_MTA_QRY_GSM_FREQLOCK_REQ      = 0x006B,
    ID_AT_MTA_DEL_CELLENTITY_REQ        = 0x006C,
    ID_AT_MTA_PSEUCELL_INFO_SET_REQ     = 0x006D,

    ID_AT_MTA_POWER_DET_QRY_REQ         = 0x006E,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_MIPIREAD_SET_REQ          = 0x006F,

    ID_AT_MTA_NO_CARD_MODE_SET_REQ      = 0x0070,
    ID_AT_MTA_NO_CARD_MODE_QRY_REQ      = 0x0071,

    ID_AT_MTA_CHRALARMRLAT_CFG_SET_REQ  = 0x0072,           /* _H2ASN_MsgChoice AT_MTA_CHR_ALARM_RLAT_CFG_SET_REQ_STRU */

    ID_AT_MTA_ECC_CFG_SET_REQ           = 0x0073,

    ID_AT_MTA_EPDU_SET_REQ              = 0x0074,

    ID_AT_MTA_LTE_CA_CELL_RPT_CFG_SET_REQ = 0x0075,
    ID_AT_MTA_LTE_CA_CELL_RPT_CFG_QRY_REQ = 0x0076,
    ID_AT_MTA_LTE_CA_CFG_SET_REQ          = 0x0077,
    ID_AT_MTA_LTE_CA_CELLEX_QRY_REQ       = 0x0078,

    ID_AT_MTA_FINE_TIME_SET_REQ           = 0x0079,
    ID_AT_MTA_GAS_AUTOTEST_QRY_REQ        = 0x0080,               /* _H2ASN_MsgChoice AT_MTA_GAS_AUTOTEST_QRY_PARA_STRU    */

    ID_AT_MTA_COMM_BOOSTER_SET_REQ     = 0x0081,           /* _H2ASN_MsgChoice AT_MTA_COMM_BOOSTER_SET_REQ_STRU */
    ID_AT_MTA_COMM_BOOSTER_QRY_REQ     = 0x0082,           /* _H2ASN_MsgChoice AT_MTA_COMM_BOOSTER_QUERY_REQ_STRU */


    ID_AT_MTA_NVLOAD_SET_REQ           = 0x0083,

    ID_AT_MTA_SMS_DOMAIN_SET_REQ         = 0x0084,
    ID_AT_MTA_SMS_DOMAIN_QRY_REQ         = 0x0085,
    ID_AT_MTA_EPS_NETWORK_QRY_REQ       = 0x0086,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_SAMPLE_REQ             = 0x0087,

    ID_AT_MTA_GPS_LOCSET_SET_REQ        = 0x0088,

    ID_AT_MTA_CCLK_QRY_REQ              = 0x0089,


    ID_AT_MTA_GAME_MODE_SET_REQ         = 0x008A,           /* _H2ASN_MsgChoice AT_MTA_COMM_GAME_MODE_SET_STRU */

    ID_AT_MTA_PSEUDBTS_SET_REQ          = 0x008B,

    ID_AT_MTA_SUBCLFSPARAM_SET_REQ      = 0x008C,
    ID_AT_MTA_SUBCLFSPARAM_QRY_REQ      = 0x008D,

    ID_AT_MTA_NV_REFRESH_SET_REQ         = 0x008E,           /* _H2ASN_MsgChoice AT_MTA_NV_REFRESH_SET_REQ_STRU */

#if(FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)
    ID_AT_MTA_SLT_TEST_SET_REQ         = 0X008F,
#endif

    ID_AT_MTA_CDMA_MODEM_CAP_SET_REQ    = 0x0090,

    ID_AT_MTA_CDMA_CAP_RESUME_SET_REQ   = 0x0091,

    ID_AT_MTA_PHYMIPIWRITE_SET_REQ      = 0x0092,

    ID_AT_MTA_FORCESYNC_SET_REQ      = 0x0093,

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_LENDC_QRY_REQ          = 0x0094,
    ID_AT_MTA_NR_FREQLOCK_SET_REQ    = 0x0095,
    ID_AT_MTA_NR_FREQLOCK_QRY_REQ    = 0x0096,
#endif

    ID_AT_MTA_SET_LTEPWRDISS_REQ        = 0x0097,

    ID_AT_MTA_GNSS_NTY                  = 0x0098,

    ID_AT_MTA_SFEATURE_QRY_REQ          = 0x0099,
    ID_AT_MTA_LOW_PWR_MODE_SET_REQ      = 0x009A,
    ID_AT_MTA_LL2_COM_CFG_SET_REQ       = 0x009D,
    ID_AT_MTA_LL2_COM_CFG_QRY_REQ       = 0x009E,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_NL2_COM_CFG_SET_REQ       = 0x009F,
    ID_AT_MTA_NL2_COM_CFG_QRY_REQ       = 0x00A0,

    ID_AT_MTA_NRRCCAP_CFG_SET_REQ       = 0x00A1,
    ID_AT_MTA_NRRCCAP_QRY_REQ           = 0x00A2,
    ID_AT_MTA_NRPWRCTRL_SET_REQ         = 0x00A3,
#endif

    ID_AT_MTA_SARREDUCTION_NTF          = 0x00A4,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_SET_TRX_TAS_REQ           = 0x00A5,
    ID_AT_MTA_QRY_TRX_TAS_REQ           = 0x00A6,
    ID_AT_MTA_MULTI_PMU_DIE_ID_SET_REQ  = 0x00A7,
    ID_AT_MTA_5G_OPTION_CFG_REQ         = 0X00A8,
    ID_AT_MTA_5G_OPTION_QRY_REQ         = 0X00A9,

    ID_AT_MTA_5G_NSSAI_SET_REQ          = 0x00AA,
    ID_AT_MTA_5G_NSSAI_QRY_REQ          = 0x00AB,
#endif
    ID_AT_MTA_VMODE_SET_REQ              = 0x00AC,
    ID_AT_MTA_VMODE_QRY_REQ              = 0x00AD,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_SET_NETMON_SSCELL_REQ     = 0x00AE,
#endif

    ID_AT_MTA_RFFE_DIE_ID_QRY_REQ       = 0x00AF,

    ID_AT_MTA_NV_REFRESH_RSP             = 0x2002,           /* ????AT->MTA??????????ID_MTA_NV_REFRESH_RSP????????*/

    /* MTA????AT?????? */
    ID_MTA_AT_CPOS_SET_CNF              = 0x1000,           /* _H2ASN_MsgChoice MTA_AT_CPOS_CNF_STRU        */
    ID_MTA_AT_CGPSCLOCK_SET_CNF         = 0x1001,           /* _H2ASN_MsgChoice MTA_AT_CGPSCLOCK_CNF_STRU   */
    ID_MTA_AT_CPOSR_IND                 = 0x1002,           /* _H2ASN_MsgChoice MTA_AT_CPOSR_IND_STRU       */
    ID_MTA_AT_XCPOSRRPT_IND             = 0x1003,           /* _H2ASN_MsgChoice MTA_AT_XCPOSRRPT_IND_STRU   */
    ID_MTA_AT_APSEC_SET_CNF             = 0x1004,           /* _H2ASN_MsgChoice MTA_AT_APSEC_CNF_STRU       */
    ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF     = 0x1005,           /* _H2ASN_MsgChoice MTA_AT_SIMLOCKUNLOCK_CNF_STRU */

    ID_MTA_AT_QRY_NMR_CNF               = 0x1006,           /* _H2ASN_MsgChoice MTA_AT_QRY_NMR_CNF_STRU */

    ID_MTA_AT_WRR_AUTOTEST_QRY_CNF      = 0x1007,           /* _H2ASN_MsgChoice MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_CELLINFO_QRY_CNF      = 0x1008,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLINFO_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_MEANRPT_QRY_CNF       = 0x1009,           /* _H2ASN_MsgChoice MTA_AT_WRR_MEANRPT_QRY_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_SET_CNF      = 0x100A,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_SET_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_SET_CNF   = 0x100B,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_SET_CNF       = 0x100C,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_SET_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_QRY_CNF      = 0x100D,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF   = 0x100E,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_QRY_CNF       = 0x100F,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_QRY_CNF_STRU        */

    ID_MTA_AT_BODY_SAR_SET_CNF          = 0x1010,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_CURC_QRY_CNF              = 0x1011,           /* _H2ASN_MsgChoice MTA_AT_CURC_QRY_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_SET_CNF   = 0x1012,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF   = 0x1013,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU */

    ID_MTA_AT_IMEI_VERIFY_QRY_CNF       = 0x1014,            /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_MTA_AT_CGSN_QRY_CNF              = 0x1015,            /* _H2ASN_MsgChoice MTA_AT_CGSN_QRY_CNF_STRU */
    ID_MTA_AT_NCELL_MONITOR_SET_CNF     = 0x1016,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_QRY_CNF     = 0x1017,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_QRY_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_IND         = 0x1018,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_IND_STRU        */

    ID_MTA_AT_REFCLKFREQ_SET_CNF        = 0x1019,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_QRY_CNF        = 0x101A,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_QRY_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_IND            = 0x101B,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_IND_STRU */

    ID_MTA_AT_HANDLEDECT_SET_CNF        = 0x101C,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_SET_CNF_STRU */
    ID_MTA_AT_HANDLEDECT_QRY_CNF        = 0x101D,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_QRY_CNF_STRU */

    ID_MTA_AT_PS_TRANSFER_IND           = 0x101E,           /* _H2ASN_MsgChoice MTA_AT_PS_TRANSFER_IND_STRU */

    ID_MTA_AT_ECID_SET_CNF              = 0x101F,           /* _H2ASN_MsgChoice MTA_AT_ECID_SET_CNF_STRU */

    ID_MTA_AT_MIPICLK_QRY_CNF           = 0x1020,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_CNF_STRU */
    ID_MTA_AT_MIPICLK_INFO_IND          = 0x1021,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_IND_STRU */

    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF     = 0x1022,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU */
    ID_MTA_AT_SET_DPDT_VALUE_CNF        = 0x1023,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDT_VALUE_CNF_STRU */
    ID_MTA_AT_QRY_DPDT_VALUE_CNF        = 0x1024,           /* _H2ASN_MsgChoice MTA_AT_QRY_DPDT_VALUE_CNF_STRU */

    ID_MTA_AT_RRC_PROTECT_PS_CNF        = 0x1025,
    ID_MTA_AT_PHY_INIT_CNF              = 0x1026,

    ID_MTA_AT_SET_JAM_DETECT_CNF        = 0x1027,           /* _H2ASN_MsgChoice MTA_AT_SET_JAM_DETECT_CNF_STRU */
    ID_MTA_AT_JAM_DETECT_IND            = 0x1028,           /* _H2ASN_MsgChoice MTA_AT_JAM_DETECT_IND_STRU */

    ID_MTA_AT_SET_FREQ_LOCK_CNF         = 0x1029,           /* _H2ASN_MsgChoice MTA_AT_SET_FREQ_LOCK_CNF_STRU */

    ID_MTA_AT_SET_GSM_FREQLOCK_CNF      = 0x102A,           /* _H2ASN_MsgChoice MTA_AT_SET_GSM_FREQLOCK_CNF_STRU */

    ID_AT_MTA_SET_FEMCTRL_CNF           = 0x102B,

    ID_MTA_AT_XPASS_INFO_IND            = 0x102C,

    ID_MTA_AT_NVWRSECCTRL_SET_CNF       = 0x102D,

    ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF   = 0x102E,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_PREFERENCE_SET_CNF       = 0x102F,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF    = 0x1030,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU */
    ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF     = 0x1031,       /* _H2ASN_MsgChoice MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU */
    ID_MTA_AT_NETWORK_INFO_QRY_CNF          = 0x1032,       /* _H2ASN_MsgChoice MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU */
    ID_MTA_AT_EMBMS_STATUS_QRY_CNF          = 0x1033,       /* _H2ASN_MsgChoice MTA_AT_EMBMS_STATUS_QRY_CNF_STRU */
    ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF  = 0x1034,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_EVENT_IND        = 0x1035,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SERVICE_EVENT_IND_STRU */
    ID_MTA_AT_LTE_LOW_POWER_SET_CNF         = 0x1036,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_INTEREST_LIST_SET_CNF         = 0x1037,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF    = 0x1038,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF = 0x1039,       /* _H2ASN_MsgChoice MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_SET_CNF         = 0x103A,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF         = 0x103B,       /* _H2ASN_MsgChoice MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU */

    ID_MTA_AT_SET_FR_CNF                = 0x103C,

    ID_MTA_AT_MEID_SET_CNF              = 0x103d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_RFICSSIRD_QRY_CNF         = 0x103e,

    ID_MTA_AT_MEID_QRY_CNF              = 0x103f,     /* _H2ASN_MsgChoice MTA_AT_MEID_QRY_CNF_STRU */

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_MTA_AT_SET_M2M_FREQLOCK_CNF      = 0x1040,           /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_CNF_STRU */
    ID_MTA_AT_QRY_M2M_FREQLOCK_CNF      = 0x1041,           /* _H2ASN_MsgChoice MTA_AT_QRY_FREQLOCK_CNF_STRU */
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_LENDC_QRY_CNF             = 0x1042,
    ID_MTA_AT_LENDC_INFO_IND            = 0x1043,
    ID_MTA_AT_NR_FREQLOCK_SET_CNF       = 0x1044,
    ID_MTA_AT_NR_FREQLOCK_QRY_CNF       = 0x1045,
#endif

    ID_MTA_AT_TRANSMODE_QRY_CNF         = 0x1052,

    ID_MTA_AT_UE_CENTER_SET_CNF         = 0x1053,
    ID_MTA_AT_UE_CENTER_QRY_CNF         = 0x1054,     /* _H2ASN_MsgChoice MTA_AT_QRY_UE_CENTER_CNF_STRU */

    ID_MTA_AT_SET_NETMON_SCELL_CNF      = 0x1055,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */
    ID_MTA_AT_SET_NETMON_NCELL_CNF      = 0x1056,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */

    ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ = 0x1057, /* _H2ASN_MsgChoice AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU */
    ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF = 0x1058, /* _H2ASN_MsgChoice MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU */
    ID_MTA_AT_ANQUERY_QRY_CNF           = 0x1059,       /* _H2ASN_MsgChoice MTA_AT_ANTENNA_INFO_QRY_CNF_STRU */
    ID_MTA_AT_CSNR_QRY_CNF              = 0x105A,       /* _H2ASN_MsgChoice MTA_AT_CSNR_QRY_CNF_STRU */
    ID_MTA_AT_CSQLVL_QRY_CNF            = 0x105B,       /* _H2ASN_MsgChoice MTA_AT_CSQLVL_QRY_CNF_STRU */

    ID_MTA_AT_EVDO_SYS_EVENT_CNF        = 0x105c,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_EVDO_SIG_MASK_CNF         = 0x105d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_EVDO_REVA_RLINK_INFO_IND  = 0x105e,
    ID_MTA_AT_EVDO_SIG_EXEVENT_IND      = 0x105f,

    ID_MTA_AT_XCPOSR_SET_CNF            = 0x1060,                               /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_XCPOSR_QRY_CNF            = 0x1061,                               /* _H2ASN_MsgChoice MTA_AT_QRY_XCPOSR_CNF_STRU */
    ID_MTA_AT_XCPOSRRPT_SET_CNF         = 0x1062,                               /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_XCPOSRRPT_QRY_CNF         = 0x1063,                               /* _H2ASN_MsgChoice MTA_AT_QRY_XCPOSRRPT_CNF_STRU */
    ID_MTA_AT_CLEAR_HISTORY_FREQ_CNF    = 0x1064,   /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_SET_SENSOR_CNF           = 0x1065,     /* _H2ASN_MsgChoice MTA_AT_SET_SENSOR_CNF_STRU */
    ID_MTA_AT_SET_SCREEN_CNF           = 0x1066,     /* _H2ASN_MsgChoice MTA_AT_SET_SCREEN_CNF_STRU */
    ID_MTA_AT_FRAT_IGNITION_QRY_CNF     = 0x1067,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_QRY_CNF_STRU */
    ID_MTA_AT_FRAT_IGNITION_SET_CNF     = 0x1068,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_SET_CNF_STRU */

    ID_MTA_AT_SET_MODEM_TIME_CNF              = 0x1069,

    ID_MTA_AT_RX_TEST_MODE_SET_CNF      = 0x106A,

    ID_MTA_AT_AFC_CLK_UNLOCK_CAUSE_IND  = 0x106B,

    ID_MTA_AT_SIB16_TIME_UPDATE_IND     = 0x106C,

    ID_MTA_AT_SLAVE_SET_CNF             = 0x106D,

    ID_MTA_AT_BESTFREQ_SET_CNF          = 0x106E,
    ID_MTA_AT_BEST_FREQ_INFO_IND        = 0x106F,                             /* _H2ASN_MsgChoice MTA_AT_BEST_FREQ_CASE_STRU */
    ID_MTA_AT_BESTFREQ_QRY_CNF          = 0x1070,

    ID_MTA_AT_RFIC_DIE_ID_QRY_CNF       = 0x1071,

    ID_MTA_AT_CRRCONN_SET_CNF           = 0x1072,
    ID_MTA_AT_CRRCONN_QRY_CNF           = 0x1073,
    ID_MTA_AT_CRRCONN_STATUS_IND        = 0x1074,
    ID_MTA_AT_VTRLQUALRPT_SET_CNF       = 0x1075,
    ID_MTA_AT_RL_QUALITY_INFO_IND       = 0x1076,
    ID_MTA_AT_VIDEO_DIAG_INFO_RPT       = 0x1077,

    ID_MTA_AT_PMU_DIE_SN_QRY_CNF        = 0x1078,

    ID_MTA_AT_MODEM_CAP_UPDATE_CNF      = 0x1079,

    ID_MTA_AT_LTE_CATEGORY_INFO_IND     = 0x107A,                               /* _H2ASN_MsgChoice MTA_AT_LTE_CATEGORY_INFO_IND_STRU */

    ID_MTA_AT_TAS_TEST_CFG_CNF          = 0x1080,
    ID_MTA_AT_TAS_TEST_QRY_CNF          = 0x1081,

    ID_MTA_AT_ACCESS_STRATUM_REL_IND    = 0x1082,

    ID_MTA_AT_MIPI_WREX_CNF             = 0x1083,
    ID_MTA_AT_MIPI_RDEX_CNF             = 0x1084,

    ID_MTA_AT_RS_INFO_QRY_CNF           = 0x1085,

    ID_MTA_AT_PHY_COM_CFG_SET_CNF       = 0x1086,

    ID_MTA_AT_ERRCCAP_CFG_SET_CNF       = 0x1087,
    ID_MTA_AT_ERRCCAP_QRY_SET_CNF       = 0x1088,

    ID_MTA_AT_QRY_GSM_FREQLOCK_CNF      = 0x1089,                               /* _H2ASN_MsgChoice MTA_AT_QRY_GSM_FREQLOCK_CNF_STRU */
    ID_MTA_AT_DEL_CELLENTITY_CNF        = 0x108A,

    ID_MTA_AT_POWER_DET_QRY_CNF         = 0x108B,


    ID_MTA_AT_PSEUCELL_INFO_SET_CNF     = 0x108C,

    ID_MTA_AT_MIPIREAD_SET_CNF          = 0x108D,

    ID_MTA_AT_NO_CARD_MODE_SET_CNF      = 0x108E,
    ID_MTA_AT_NO_CARD_MODE_QRY_CNF      = 0x108F,

    ID_MTA_AT_CHRALARMRLAT_CFG_SET_CNF  = 0x1090,

    ID_MTA_AT_ECC_CFG_SET_CNF           = 0x1091,
    ID_MTA_AT_ECC_STATUS_IND            = 0x1092,

    ID_MTA_AT_EPDU_SET_CNF              = 0x1093,
    ID_MTA_AT_EPDUR_DATA_IND            = 0x1094,

    ID_MTA_AT_LTE_CA_CFG_SET_CNF        = 0x1095,
    ID_MTA_AT_LTE_CA_CELLEX_QRY_CNF     = 0x1096,
    ID_MTA_AT_LTE_CA_CELLEX_INFO_NTF    = 0x1097,

    ID_MTA_AT_LTE_CA_CELL_RPT_CFG_SET_CNF = 0x1098,
    ID_MTA_AT_LTE_CA_CELL_RPT_CFG_QRY_CNF = 0x1099,

    ID_MTA_AT_FINE_TIME_SET_CNF         = 0x109A,
    ID_MTA_AT_SIB_FINE_TIME_NTF         = 0x109B,
    ID_MTA_AT_LPP_FINE_TIME_NTF         = 0x109C,

    ID_MTA_AT_PHY_COMM_ACK_IND          = 0x109D,

    ID_MTA_AT_GAS_AUTOTEST_QRY_CNF      = 0x109E,                   /* _H2ASN_MsgChoice MTA_AT_GAS_AUTOTEST_QRY_CNF_STRU */

    ID_MTA_AT_COMM_BOOSTER_SET_CNF     = 0x109F,  /* _H2ASN_MsgChoice MTA_AT_COMM_BOOSTER_SET_CNF_STRU */
    ID_MTA_AT_COMM_BOOSTER_IND         = 0x10A0,  /* _H2ASN_MsgChoice MTA_AT_COMM_BOOSTER_IND_STRU */
    ID_MTA_AT_COMM_BOOSTER_QUERY_CNF   = 0x10A1,  /* _H2ASN_MsgChoice MTA_AT_COMM_BOOSTER_QUERY_CNF_STRU */

    ID_MTA_AT_NVLOAD_SET_CNF           = 0x10A2,

    ID_MTA_AT_SMS_DOMAIN_SET_CNF       = 0x10A3,          /* _H2ASN_MsgChoice MTA_AT_SMS_DOMAIN_SET_CNF_STRU */
    ID_MTA_AT_SMS_DOMAIN_QRY_CNF       = 0x10A4,          /* _H2ASN_MsgChoice MTA_AT_SMS_DOMAIN_QRY_CNF_STRU */

    ID_MTA_AT_EPS_NETWORK_QRY_CNF       = 0x10A5,                               /* _H2ASN_MsgChoice MTA_AT_EPS_NETWORK_QRY_CNF_STRU */
    ID_MTA_AT_EPS_NETWORK_INFO_IND      = 0x10A6,                               /* _H2ASN_MsgChoice MTA_AT_EPS_NETWORK_INFO_IND_STRU */

    ID_MTA_AT_SET_SAMPLE_CNF           = 0x10A7,

    ID_MTA_AT_GPS_LOCSET_SET_CNF       = 0x10A8,

    ID_MTA_AT_CCLK_QRY_CNF         = 0x10A9,

    ID_MTA_AT_TEMP_PROTECT_IND         = 0x10AA,

    ID_AT_MTA_GAME_MODE_SET_CNF         = 0x10AB,           /* _H2ASN_MsgChoice MTA_AT_GAME_MODE_SET_CFN_STRU */

    ID_MTA_AT_PSEUDBTS_SET_CNF          = 0x10AC,

    ID_MTA_AT_SUBCLFSPARAM_SET_CNF      = 0X10AD,
    ID_MTA_AT_SUBCLFSPARAM_QRY_CNF      = 0X10AE,

    ID_MTA_AT_NV_REFRESH_SET_CNF         = 0x10AF,          /* _H2ASN_MsgChoice MTA_AT_NV_REFRESH_SET_CNF_STRU */

#if(FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)
    ID_AT_MTA_SLT_TEST_SET_CNF         = 0x10B0,
#endif

    ID_MTA_AT_CDMA_MODEM_CAP_SET_CNF    = 0x10B1,

    ID_MTA_AT_CDMA_CAP_RESUME_SET_CNF   = 0x10B2,

    ID_MTA_AT_PHYMIPIWRITE_SET_CNF      = 0x10B3,

    ID_MTA_AT_SFEATURE_QRY_CNF          = 0x10B4,
    ID_MTA_AT_LOW_PWR_MODE_SET_CNF      = 0x10B5,

    ID_MTA_AT_LL2_COM_CFG_SET_CNF         = 0x10B8,
    ID_MTA_AT_LL2_COM_CFG_QRY_CNF         = 0x10B9,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_NL2_COM_CFG_SET_CNF         = 0x10BA,
    ID_MTA_AT_NL2_COM_CFG_QRY_CNF         = 0x10BB,

    ID_MTA_AT_NRRCCAP_CFG_SET_CNF         = 0x10BC,
    ID_MTA_AT_NRRCCAP_QRY_CNF             = 0x10BD,
    ID_MTA_AT_NRPWRCTRL_SET_CNF           = 0x10BE,
#endif

    ID_AT_MTA_QRY_JAM_DETECT_REQ        = 0x1100,
    ID_MTA_AT_QRY_JAM_DETECT_CNF        = 0x1101,

    ID_MTA_AT_PSEUD_BTS_IDENT_IND       = 0x1102,

    ID_MTA_AT_FORCESYNC_SET_CNF         = 0X1103,

    ID_AT_MTA_SET_LTEPWRDISS_CNF        = 0X1104,

    ID_AT_MTA_DCXO_SAMPLE_QRY_REQ         = 0X1105,
    ID_MTA_AT_DCXO_SAMPLE_QRY_CNF         = 0X1106,

    ID_AT_MTA_MCS_SET_REQ                 = 0X1107,
    ID_MTA_AT_MCS_SET_CNF                 = 0X1108,
    ID_AT_MTA_TXPOWER_QRY_REQ             = 0X1109,
    ID_MTA_AT_TXPOWER_QRY_CNF             = 0X110A,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_NTXPOWER_QRY_REQ            = 0X110B,
    ID_MTA_AT_NTXPOWER_QRY_CNF            = 0X110C,
#endif
    ID_AT_MTA_HFREQINFO_QRY_REQ           = 0X110D,
    ID_MTA_AT_HFREQINFO_QRY_CNF           = 0X110E,
    ID_MTA_AT_HFREQINFO_IND               = 0X110F,

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_SET_TRX_TAS_CNF             = 0X1110,
    ID_MTA_AT_QRY_TRX_TAS_CNF             = 0X1111,


#endif

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_5G_OPTION_SET_CNF           = 0X1112,
    ID_MTA_AT_5G_OPTION_QRY_CNF           = 0X1113,
    ID_MTA_AT_5G_NSSAI_SET_CNF            = 0X1114,
    ID_MTA_AT_5G_NSSAI_QRY_CNF            = 0X1115,
#endif

    ID_MTA_AT_VMODE_SET_CNF               = 0x1116,
    ID_MTA_AT_VMODE_QRY_CNF               = 0x1117,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_SET_NETMON_SSCELL_CNF       = 0x1118,
#endif
    ID_MTA_AT_RFFE_DIE_ID_QRY_CNF         = 0x1119,
    /* ???????????? */
    ID_AT_MTA_MSG_TYPE_BUTT

};
typedef VOS_UINT32 AT_MTA_MSG_TYPE_ENUM_UINT32;


enum AT_SET_SLT_TEST_TYPE_ENUM
{
    AT_SET_SGMII_TEST                   = 1,    /* SGMII???????????????? */
    AT_SET_RGMII_TEST                   = 2,    /* RGMII???????????????? */
    AT_SET_PCIE_TEST                    = 3,    /* PCIe????PHY???????????? */
    AT_SET_SPI_TEST                     = 4,    /* SPI master??slave???????????? */
    AT_SET_SDCARD_TEST                  = 5,    /* MMC0??????SD?????????? */
    AT_SET_L2CACHE_TEST                 = 6,    /* L2CACHE???? */
    AT_SET_HIFI_TEST                    = 7,    /* HIFI????*/
    AT_SET_SLT_SERDES_TEST              = 8,    /* SERDES ???? */
    AT_SET_SLT_ALINK_TEST               = 9,    /* alink ???? */
    AT_SET_SLT_TEST_BUTT
};
typedef VOS_UINT8  AT_SET_SLT_TEST_TYPE_ENUM_UINT8;



enum MTA_AT_RESULT_ENUM
{
    /* ??AT???????????????????? */
    MTA_AT_RESULT_NO_ERROR                      = 0x000000,                     /* ???????????? */
    MTA_AT_RESULT_ERROR,                                                        /* ???????????? */
    MTA_AT_RESULT_INCORRECT_PARAMETERS,
    MTA_AT_RESULT_OPTION_TIMEOUT,
    MTA_AT_RESULT_OPERATION_NOT_ALLOWED,                                        /* ?????????????? */
    MTA_AT_RESULT_FUNC_DISABLE,                                                 /* ???????????????? */
    /* ????????AT?????????????? */

    /* ?????????????????? */
    MTA_AT_RESULT_DEVICE_ERROR_BASE             = 0x100000,
    MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL,                                     /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL,                                    /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT,                                      /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT,                              /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_LEN_ERROR,                               /* ?????????????? */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_VALUE_ERROR,                             /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_TYPE_ERROR,                              /* ?????????????? */
    MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL,                                  /* RSA???????? */
    MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL,                                  /* RSA???????? */
    MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL,                              /* ??????????????(crypto_rand) */
    MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL,                                    /* HUK???????? */
    MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR,                                       /* Flash???? */
    MTA_AT_RESULT_DEVICE_SEC_NV_ERROR,                                          /* NV???????? */
    MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR,                                       /* ???????? */


    /* ?????????????????? */
    MTA_AT_RESULT_PRICMD_ERROR_BASE             = 0x200000,

    MTA_AT_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_RESULT_ENUM_UINT32;


enum AT_MTA_VMODE_RAT_TYPE
{
    AT_MTA_VMODE_RAT_LTEV               = 0x00,
    AT_MTA_VMODE_RAT_BUTT
};
typedef VOS_UINT8 AT_MTA_VMODE_RAT_TYPE_UINT8;


enum AT_MTA_VMODE_PWMODE_TYPE
{
    AT_MTA_VMODE_POWEROFF               = 0x00,
    AT_MTA_VMODE_POWERON                = 0x01,
    AT_MTA_VMODE_PWMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_VMODE_PWMODE_TYPE_UINT8;


enum MTA_AT_RESULT_TYPE_ENUM
{
    MTA_AT_RESULT_TYPE_NULL             = 0x00,
    MTA_AT_RESULT_TYPE_LTE              = 0x01,
    MTA_AT_RESULT_TYPE_NR               = 0x02,
    MTA_AT_RESULT_TYPE_DC               = 0x03,
    MTA_AT_RESULT_TYPE_BUTT
};
typedef VOS_UINT8 MTA_AT_RESULT_TYPE_ENUM_UINT8;

enum MTA_AT_CGPSCLOCK_ENUM
{
    MTA_AT_CGPSCLOCK_STOP           = 0,
    MTA_AT_CGPSCLOCK_START,
    MTA_AT_CGPSCLOCK_BUTT
};
typedef VOS_UINT32 MTA_AT_CGPSCLOCK_ENUM_UINT32;



enum MTA_AT_CPOS_OPERATE_TYPE_ENUM
{
    MTA_AT_CPOS_SEND                = 0,
    MTA_AT_CPOS_CANCEL,
    MTA_AT_CPOS_BUTT
};
typedef VOS_UINT32 MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32;


enum AT_MTA_PERS_CATEGORY_ENUM
{
    AT_MTA_PERS_CATEGORY_NETWORK                    = 0x00,                     /* Category: ???? */
    AT_MTA_PERS_CATEGORY_NETWORK_SUBSET             = 0x01,                     /* Category: ?????? */
    AT_MTA_PERS_CATEGORY_SERVICE_PROVIDER           = 0x02,                     /* Category: ??SP */
    AT_MTA_PERS_CATEGORY_CORPORATE                  = 0x03,                     /* Category: ?????? */
    AT_MTA_PERS_CATEGORY_SIM_USIM                   = 0x04,                     /* Category: ??(U)SIM?? */

    AT_MTA_PERS_CATEGORY_BUTT
};
typedef VOS_UINT8 AT_MTA_PERS_CATEGORY_ENUM_UINT8;


enum AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
{
    AT_MTA_RPT_GENERAL_CONTROL_NO_REPORT      = 0x00,                           /* ?????????????????? */
    AT_MTA_RPT_GENERAL_CONTROL_REPORT         = 0x01,                           /* ?????????????????? */
    AT_MTA_RPT_GENERAL_CONTROL_CUSTOM         = 0x02,                           /* ??BIT???????????????????????? */

    AT_MTA_RPT_GENERAL_CONTROL_BUTT
};
typedef VOS_UINT8 AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8;


enum AT_MTA_RPT_SET_TYPE_ENUM
{
    AT_MTA_SET_MODE_RPT_TYPE            = 0,                                 /* Category: ???????????????????????? */
    AT_MTA_SET_SRVST_RPT_TYPE,
    AT_MTA_SET_RSSI_RPT_TYPE,
    AT_MTA_SET_TIME_RPT_TYPE,
    AT_MTA_SET_CTZR_RPT_TYPE,
    AT_MTA_SET_SIMST_RPT_TYPE,
    AT_MTA_SET_CREG_RPT_TYPE,
    AT_MTA_SET_CGREG_RPT_TYPE,
    AT_MTA_SET_CEREG_RPT_TYPE,
    AT_MTA_SET_CSID_RPT_TYPE,
    AT_MTA_SET_CLOCINFO_RPT_TYPE,
    AT_MTA_SET_MTREATTACH_RPT_TYPE,
    AT_MTA_SET_CENFS_RPT_TYPE,
    AT_MTA_SET_C5GREG_RPT_TYPE,

    AT_MTA_SET_LENDC_RPT_TYPE,

    AT_MTA_SET_RRCSTAT_RPT_TYPE,
    AT_MTA_SET_HFREQINFO_RPT_TYPE,

    AT_MTA_SET_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_SET_TYPE_ENUM_UINT32;


enum AT_MTA_RPT_QRY_TYPE_ENUM
{
    AT_MTA_QRY_TIME_RPT_TYPE = 0,
    AT_MTA_QRY_CTZR_RPT_TYPE,
    AT_MTA_QRY_CSSN_RPT_TYPE,
    AT_MTA_QRY_CUSD_RPT_TYPE,
    AT_MTA_QRY_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_QRY_TYPE_ENUM_UINT32;



enum AT_MTA_CMD_RPT_FLG_ENUM
{
    AT_MTA_CMD_RPT_FLG_OFF              = 0,                        /* AT?????????????? */
    AT_MTA_CMD_RPT_FLG_ON,                                          /* AT???????????? */
    AT_MTA_CMD_RPT_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RPT_FLG_ENUM_UINT8;

enum AT_MTA_CLEAR_FREQ_FLG_ENUM
{
    AT_MTA_CLEAR_FREQ_FLG_NOT_CSG_HISTORY_FREQ              = 0,                /* ??????CSG???????? */
    AT_MTA_CLEAR_FREQ_FLG_CSG_HISTORY_FREQ,                                     /* ????CSG???????? */
    AT_MTA_CLEAR_FREQ_FLG_ALL_FREQ,                                         /* ???????????????? */
    AT_MTA_CLEAR_FREQ_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CLEAR_FREQ_FLG_ENUM_UINT8;



enum AT_MTA_CMD_RATMODE_ENUM
{
    AT_MTA_CMD_RATMODE_GSM              = 0,
    AT_MTA_CMD_RATMODE_WCDMA,
    AT_MTA_CMD_RATMODE_LTE,
    AT_MTA_CMD_RATMODE_TD,
    AT_MTA_CMD_RATMODE_CDMA,
    AT_MTA_CMD_RATMODE_NR,
    AT_MTA_CMD_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RATMODE_ENUM_UINT8;


enum AT_MTA_CMD_SIGNALING_ENUM
{
    AT_MTA_CMD_SIGNALING_MODE           = 0,                                    /* ???????? */
    AT_MTA_CMD_NONSIGNALING_MODE        = 1,                                    /* ?????????? */

    AT_MTA_CMD_NONSIGNALING_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_SIGNALING_ENUM_UINT8;


enum AT_MTA_TRX_TAS_CMD_ENUM
{
    AT_MTA_TRX_TAS_CMD_CLOSE_ALGORITHM  = 0,                                    /* ???????? */
    AT_MTA_TRX_TAS_CMD_SET_PARA         = 1,                                    /* ???????? */
    AT_MTA_TRX_TAS_CMD_OPEN_ALGORITHM   = 2,                                    /* ???????? */

    AT_MTA_TRX_TAS_CMD_BUTT
};
typedef VOS_UINT8 AT_MTA_TRX_TAS_CMD_ENUM_UINT8;


enum MTA_AT_JAM_RESULT_ENUM
{
    MTA_AT_JAM_RESULT_JAM_DISAPPEARED        = 0x00,                            /* ?????????????? */
    MTA_AT_JAM_RESULT_JAM_DISCOVERED,                                           /* ???????? */

    MTA_AT_JAM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_JAM_RESULT_ENUM_UINT32;


enum AT_MTA_FREQLOCK_RATMODE_ENUM
{
    AT_MTA_FREQLOCK_RATMODE_GSM         = 0x01,
    AT_MTA_FREQLOCK_RATMODE_WCDMA,
    AT_MTA_FREQLOCK_RATMODE_LTE,
    AT_MTA_FREQLOCK_RATMODE_CDMA1X,
    AT_MTA_FREQLOCK_RATMODE_TD,
    AT_MTA_FREQLOCK_RATMODE_WIMAX,
    AT_MTA_FREQLOCK_RATMODE_EVDO,

    AT_MTA_FREQLOCK_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8;


enum AT_MTA_GSM_BAND_ENUM
{
    AT_MTA_GSM_BAND_850                 = 0x00,
    AT_MTA_GSM_BAND_900,
    AT_MTA_GSM_BAND_1800,
    AT_MTA_GSM_BAND_1900,

    AT_MTA_GSM_BAND_BUTT
};
typedef VOS_UINT16 AT_MTA_GSM_BAND_ENUM_UINT16;


enum AT_MTA_CFG_ENUM
{
    AT_MTA_CFG_DISABLE                  = 0,
    AT_MTA_CFG_ENABLE                   = 1,
    AT_MTA_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_CFG_ENUM_UINT8;


enum AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ACTIVE       = 0,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE     = 1,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL = 2,
    AT_MTA_MBMS_SERVICE_STATE_SET_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8;


enum AT_MTA_MBMS_CAST_MODE_ENUM
{
    AT_MTA_MBMS_CAST_MODE_UNICAST       = 0,
    AT_MTA_MBMS_CAST_MODE_MULTICAST     = 1,
    AT_MTA_MBMS_CAST_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_CAST_MODE_ENUM_UINT8;


enum MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
{
    MTA_AT_EMBMS_FUNTIONALITY_OFF       = 0,
    MTA_AT_EMBMS_FUNTIONALITY_ON        = 1,
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_BUTT
};
typedef VOS_UINT8 MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8;


enum MTA_AT_MBMS_SERVICE_EVENT_ENUM
{
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_CHANGE       = 0,
    MTA_AT_MBMS_SERVICE_EVENT_NO_SERVICE           = 1,
    MTA_AT_MBMS_SERVICE_EVENT_ONLY_UNICAST         = 2,
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_AVAILABLE    = 3,
    MTA_AT_MBMS_SERVICE_EVENT_BUTT
};
typedef VOS_UINT8 MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8;


enum AT_MTA_COEX_BW_TYPE_ENUM
{
    AT_MTA_COEX_BAND_WIDTH_6RB          = 0,                                    /* ????1.4M */
    AT_MTA_COEX_BAND_WIDTH_15RB         = 1,                                    /* ????3M */
    AT_MTA_COEX_BAND_WIDTH_25RB         = 2,                                    /* ????5M */
    AT_MTA_COEX_BAND_WIDTH_50RB         = 3,                                    /* ????10M */
    AT_MTA_COEX_BAND_WIDTH_75RB         = 4,                                    /* ????15M */
    AT_MTA_COEX_BAND_WIDTH_100RB        = 5,                                    /* ????20M */
    AT_MTA_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_BW_TYPE_ENUM_UINT16;


enum AT_MTA_COEX_CFG_ENUM
{
    AT_MTA_COEX_CFG_DISABLE             = 0,
    AT_MTA_COEX_CFG_ENABLE              = 1,
    AT_MTA_COEX_CFG_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_CFG_ENUM_UINT16;


enum AT_MTA_LTE_LOW_POWER_ENUM
{
    AT_MTA_LTE_LOW_POWER_NORMAL         = 0,
    AT_MTA_LTE_LOW_POWER_LOW            = 1,
    AT_MTA_LTE_LOW_POWER_BUTT
};
typedef VOS_UINT8 AT_MTA_LTE_LOW_POWER_ENUM_UINT8;


enum AT_MTA_MBMS_PRIORITY_ENUM
{
    AT_MTA_MBMS_PRIORITY_UNICAST        = 0,
    AT_MTA_MBMS_PRIORITY_MBMS           = 1,
    AT_MTA_MBMS_PRIORITY_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_PRIORITY_ENUM_UINT8;


enum AT_MTA_UE_CENTER_TYPE_ENUM
{
    AT_MTA_UE_CENTER_VOICE_CENTRIC                          = 0,
    AT_MTA_UE_CENTER_DATA_CENTRIC                           = 1,
    AT_MTA_UE_CENTER_BUTT
};
typedef VOS_UINT32 AT_MTA_UE_CENTER_TYPE_ENUM_UINT32;


enum AT_MTA_BODY_SAR_STATE_ENUM
{
    AT_MTA_BODY_SAR_OFF                 = 0,                                    /* Body SAR???????? */
    AT_MTA_BODY_SAR_ON,                                                         /* Body SAR???????? */
    AT_MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 AT_MTA_BODY_SAR_STATE_ENUM_UINT16;


enum MTA_AT_REFCLOCK_STATUS_ENUM
{
    MTA_AT_REFCLOCK_UNLOCKED            = 0,                                    /* GPS?????????????????????? */
    MTA_AT_REFCLOCK_LOCKED,                                                     /* GPS???????????????????? */
    MTA_AT_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 MTA_AT_REFCLOCK_STATUS_ENUM_UINT16;


enum MTA_AT_GPHY_XPASS_MODE_ENUM
{
    MTA_AT_GPHY_XPASS_MODE_DISABLE      = 0,                                    /* ??XPASS?????????????? */
    MTA_AT_GPHY_XPASS_MODE_ENABLE,                                              /* XPASS?????????????? */
    MTA_AT_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16;


enum MTA_AT_WPHY_HIGHWAY_MODE_ENUM
{
    MTA_AT_WPHY_HIGHWAY_MODE_DISABLE    = 0,                                    /* W?????????? */
    MTA_AT_WPHY_HIGHWAY_MODE_ENABLE,                                            /* W???????? */
    MTA_AT_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16;


enum MTA_AT_NETMON_GSM_STATE_ENUM
{
   MTA_AT_NETMON_GSM_STATE_INIT   = 0,
   MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO  = 1,
   MTA_AT_NETMON_GSM_STATTE_WAIT_TA  = 2,
   MTA_AT_NETMON_GSM_STATTE_BUTT
};

typedef VOS_UINT32 MTA_AT_NETMON_GSM_STATE_ENUM_UINT32;



enum MTA_AT_NETMON_CELL_INFO_RAT_ENUM
{
    MTA_AT_NETMON_CELL_INFO_GSM         = 0,
    MTA_AT_NETMON_CELL_INFO_UTRAN_FDD   = 1,
    MTA_AT_NETMON_CELL_INFO_UTRAN_TDD   = 2,
    MTA_AT_NETMON_CELL_INFO_LTE         = 3,
    MTA_AT_NETMON_CELL_INFO_NR          = 4,
    MTA_AT_NETMON_CELL_INFO_RAT_BUTT
};
typedef VOS_UINT32 MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32;




enum MTA_TAF_CTZR_TYPE
{
    MTA_TAF_CTZR_OFF            = 0x00,            /* CTZR?????? */
    MTA_TAF_CTZR_CTZV           = 0x01,            /* CTZR:CTZV */
    MTA_TAF_CTZR_CTZE           = 0x02,            /* CTZR:CTZE */
    MTA_TAF_CTZR_BUTT
};
typedef VOS_UINT32 MTA_TAF_CTZR_TYPE_ENUM_UINT32;


enum AT_MTA_AFC_CLK_STATUS_ENUM
{
    AT_MTA_AFC_CLK_UNLOCKED           = 0,                                     /* AFC UNLOCKED */
    AT_MTA_AFC_CLK_LOCKED,                                                     /* AFC LOCKED */

    AT_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT32 AT_MTA_AFC_CLK_STATUS_ENUM_UINT32;


enum AT_MTA_XCPOSR_CFG_ENUM
{
    AT_MTA_XCPOSR_CFG_DISABLE        = 0,                                       /* ?????????????? */
    AT_MTA_XCPOSR_CFG_ENABLE,                                                   /* ???????????? */
    AT_MTA_XCPOSR_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_XCPOSR_CFG_ENUM_UNIT8;


enum AT_MTA_FRAT_IGNITION_ENUM
{
    AT_MTA_FRAT_IGNITION_STATT_OFF        = 0,                                  /* ?????????????? */
    AT_MTA_FRAT_IGNITION_STATT_ON,                                                   /* ???????????? */
    AT_MTA_FRAT_IGNITION_STATT_BUTT
};
typedef VOS_UINT8 AT_MTA_FRAT_IGNITION_ENUM_UNIT8;



enum MTA_AT_AFC_CLK_UNLOCK_CAUSE_ENUM
{
    MTA_AT_AFC_CLK_UNLOCK_CAUSE_SLEEP,

    MTA_AT_AFC_CLK_UNLOCK_CAUSE_BUTT
};
typedef VOS_UINT16  MTA_AT_AFC_CLK_UNLOCK_CAUSE_ENUM_UINT16;


enum MTA_AT_MODEM_ID_ENUM
{
    MTA_AT_MODEM_ID_0  = 0,
    MTA_AT_MODEM_ID_1,
    MTA_AT_MODEM_ID_2,

    MTA_AT_MODEM_ID_BUTT
};
typedef VOS_UINT8 MTA_AT_MODEM_ID_ENUM_UINT8;


enum MTA_AT_RAT_MODE_ENUM
{
    MTA_AT_RAT_MODE_GSM         = 0,
    MTA_AT_RAT_MODE_WCDMA       = 1,
    MTA_AT_RAT_MODE_LTE         = 2,
    MTA_AT_RAT_MODE_TDSCDMA     = 3,
    MTA_AT_RAT_MODE_CDMA_1X     = 4,
    MTA_AT_RAT_MODE_HRPD        = 5,
    MTA_AT_RAT_MODE_NR          = 6,
    MTA_AT_RAT_MODE_BUTT
};
typedef VOS_UINT8 MTA_AT_RAT_MODE_ENUM_UINT8;


enum MTA_AT_DAY_LIGHT_SAVING_IND_ENUM
{
    MTA_AT_NO_ADJUST                  = 0,
    MTA_AT_ONE_HOUR                   = 1,
    MTA_AT_TWO_HOUR                   = 2,
    MTA_AT_HOUR_BUTT
};
typedef VOS_UINT8   MTA_AT_DAY_LIGHT_SAVING_IND_ENUM_UINT8;


enum MTA_AT_TIME_TYPE_ENUM
{
    MTA_AT_LOCAL_TIME                 = 1,
    MTA_AT_GPS_TIME                   = 2,
    MTA_AT_LOCAL_GPS_TIME             = 3,
    MTA_AT_TIME_BUTT
};
typedef VOS_UINT8   MTA_AT_TIME_TYPE_ENUM_UINT8;


enum AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM
{
    AT_MTA_MODEM_CAP_UPDATE_TYPE_CDMA_MODEM_SWITCH   = 0x00U,       /* AT^CDMAMODEMSWITCH?????????????????? */
    AT_MTA_MODEM_CAP_UPDATE_TYPE_ACTIVE_MODEM        = 0x01U,       /* AT^ACTIVEMODEM?????????????????? */

    AT_MTA_MODEM_CAP_UPDATE_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM_UINT8;


enum AT_MTA_RS_INFO_TYPE_ENUM
{
    AT_MTA_RSRP_TYPE                     = 0,
    AT_MTA_RSRQ_TYPE                     = 1,
    AT_MTA_RS_INFO_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RS_INFO_TYPE_ENUM_UINT32;


enum AT_MTA_PSEUCELL_NOTIFY_TYPE_ENUM
{
    AT_MTA_PSEUCELL_NOTIFY_TYPE_BY_MESSAGE = 0,
    AT_MTA_PSEUCELL_NOTIFY_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_PSEUCELL_NOTIFY_TYPE_ENUM_UINT8;


enum AT_MTA_SYS_MODE_ENUM
{
    AT_MTA_SYS_MODE_GSM                 = 1,
    AT_MTA_SYS_MODE_1X                  = 2,
    AT_MTA_SYS_MODE_WCDMA               = 3,
    AT_MTA_SYS_MODE_TDSCDMA             = 4,
    AT_MTA_SYS_MODE_WIMAX               = 5,
    AT_MTA_SYS_MODE_LTE                 = 6,
    AT_MTA_SYS_MODE_HRPD                = 7,
    AT_MTA_SYS_MODE_BUTT
};
typedef VOS_UINT32 AT_MTA_SYS_MODE_ENUM_UINT32;


enum AT_MTA_CHR_ALARM_RLAT_OP_ENUM
{
    AT_MTA_CHR_ALARM_RLAT_OP_READ       = 0,
    AT_MTA_CHR_ALARM_RLAT_OP_WRITE      = 1,

    AT_MTA_CHR_ALARM_RLAT_OP_BUTT
};
typedef VOS_UINT32 AT_MTA_CHR_ALARM_RLAT_OP_ENUM_UINT32;


enum MTA_AT_BAND_WIDTH_ENUM
{
    MTA_AT_BAND_WIDTH_1DOT4M                    = 0,            /* ??????1.4MHz */
    MTA_AT_BAND_WIDTH_3M,                                       /* ??????3MHz */
    MTA_AT_BAND_WIDTH_5M,                                       /* ??????5MHz */
    MTA_AT_BAND_WIDTH_10M,                                      /* ??????10MHz */
    MTA_AT_BAND_WIDTH_15M,                                      /* ??????15MHz */
    MTA_AT_BAND_WIDTH_20M,                                      /* ??????20MHz */
    MTA_AT_BAND_WIDTH_BUTT
};
typedef VOS_UINT8 MTA_AT_BAND_WIDTH_ENUM_UINT8;


enum MTA_AT_FINE_TIME_RAT_ENUM
{
    MTA_AT_FINE_TIME_RAT_GSM         = 0,
    MTA_AT_FINE_TIME_RAT_WCDMA       = 1,
    MTA_AT_FINE_TIME_RAT_LTE         = 2,
    MTA_AT_FINE_TIME_RAT_TDS_CDMA    = 3,
    MTA_AT_FINE_TIME_RAT_CDMA_1X     = 4,
    MTA_AT_FINE_TIME_RAT_HRPD        = 5,
    MTA_AT_FINE_TIME_RAT_NR          = 6,
    MTA_AT_FINE_TIME_RAT_BUTT
};
typedef VOS_UINT8 MTA_AT_FINE_TIME_RAT_ENUM_UINT8;

/*****************************************************************************
 ??????    : MTA_AT_PROTOCOL_STATE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : ??????????????
*****************************************************************************/
enum MTA_AT_PROTOCOL_STATE_ENUM
{
    MTA_AT_PROTOCOL_STATE_IDLE          = 0,
    MTA_AT_PROTOCOL_STATE_CONNECTED     = 1,
    MTA_AT_PROTOCOL_STATE_INACTIVE      = 2,

    MTA_AT_PROTOCOL_STATE_BUTT
};
typedef VOS_UINT8 MTA_AT_PROTOCOL_STATE_ENUM_UINT8;

/*****************************************************************************
 ??????    : AT_MTA_FINETIME_PARA_ENUM
 ????????  :
 ASN.1???? :
 ????????  : FINETIME PARA
*****************************************************************************/
enum AT_MTA_FINETIME_PARA_ENUM
{
    AT_MTA_FINETIME_PARA_0      = 0,
    AT_MTA_FINETIME_PARA_1      = 1,
    AT_MTA_FINETIME_PARA_2      = 2,

    AT_MTA_FINETIME_PARA_BUTT
};
typedef VOS_UINT8 AT_MTA_FINETIME_PARA_ENUM_UINT8;


enum TAF_MTA_NV_CARRIER_OPT_RESULT_ENUM
{
    TAF_MTA_NV_CARRIER_OPT_NO_ERROR                  = 0x00000000,
    TAF_MTA_NV_CARRIER_OPT_INVALID_PARA              = 0x10100002, /* ?????????? */
    TAF_MTA_NV_CARRIER_OPT_NOT_FIND_FILE             = 0x10100006, /* ?????????? */
    TAF_MTA_NV_CARRIER_OPT_NOT_FIND_NV               = 0x10100016, /* ????????NV */
    TAF_MTA_NV_CARRIER_OPT_WRITE_NV_TIMEOUT          = 0x10100035, /* ??NV????,(??????????????????????) */
    TAF_MTA_NV_CARRIER_OPT_WRITE_NV_NOT_SUPPORT_ERR  = 0x10100037, /* ?????????? */
    TAF_MTA_NV_CARRIER_OPT_MODEM_ID_ERROR            = 0x10100039, /* modem id ???????? */

    TAF_MTA_NV_CARRIER_OPT_BUTT
};
typedef VOS_UINT32 TAF_MTA_NV_CARRIER_OPT_RESULT_ENUM_UINT32;


enum AT_MTA_SMS_DOMAIN_ENUM
{
    AT_MTA_SMS_DOMAIN_NOT_USE_SMS_OVER_IP                  = 0,                 /**< not to use SMS over ip */
    AT_MTA_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP            = 1,                 /**< prefer to use SMS over ip, CS/PS SMS as secondary */

    AT_MTA_SMS_DOMAIN_BUTT
};
typedef VOS_UINT8 AT_MTA_SMS_DOMAIN_ENUM_UINT8;


enum MTA_AT_TIME_INFO_RPT_OPT_ENUM
{
    MTA_AT_TIME_INFO_RPT_OPT_MMINFO                         = 0,                /* ^TIME???? */
    MTA_AT_TIME_INFO_RPT_OPT_SIB16TIME                      = 1,                /* ^SIB16TIME???? */
    MTA_AT_TIME_INFO_RPT_OPT_BUTT
};
typedef VOS_UINT8 MTA_AT_TIME_INFO_RPT_OPT_ENUM_UINT8;


enum AT_MTA_NV_REFRESH_REASON_ENUM
{
    AT_MTA_NV_REFRESH_USIM_DEPENDENT                  = 0,       /* ???????? */
    AT_MTA_NV_REFRESH_BUTT
};
typedef VOS_UINT8 AT_MTA_NV_REFRESH_REASON_ENUM_UINT8;


enum AT_MTA_JAM_DETECT_MODE_ENUM
{
    AT_MTA_JAM_DETECT_MODE_STOP     = 0,                /* ???????????? */
    AT_MTA_JAM_DETECT_MODE_START    = 1,                /* ???????????? */
    AT_MTA_JAM_DETECT_MODE_UPDATE   = 2,                /* ???????????????? */
    AT_MTA_JAM_DETECT_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_JAM_DETECT_MODE_ENUM_UINT8;


enum AT_MTA_DCXO_SAMPLE_TYPE_ENUM
{
    AT_MTA_DCXO_SAMPLE_H             = 0,                /* ?????? */
    AT_MTA_DCXO_SAMPLE_M             = 1,                /* ?????? */
    AT_MTA_DCXO_SAMPLE_L             = 2,                /* ?????? */
    AT_MTA_DCXO_SAMPLE_INITFREQ      = 3,                /* ???????????? */
    AT_MTA_DCXO_SAMPLE_BUTT
};
typedef VOS_UINT16 AT_MTA_DCXO_SAMPLE_TYPE_ENUM_UINT16;


enum MTA_AT_DCXO_SAMPLE_RESULT_ENUM
{
    MTA_AT_DCXO_SAMPLE_RESULT_NO_ERROR          = 0,                /* ???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_ERROR             = 1,                /* ???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_PARA_ERROR        = 2,                /* ???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_OPTION_TIMEOUT    = 3,                /* ?????????? */
    MTA_AT_DCXO_SAMPLE_RESULT_BUTT
};
typedef VOS_UINT16 MTA_AT_DCXO_SAMPLE_RESULT_ENUM_UINT16;


enum AT_MTA_LOW_PWR_MODE_RAT_ENUM
{
    AT_MTA_LOW_PWR_MODE_RAT_LTE         = 0,                                    /* LTE */
    AT_MTA_LOW_PWR_MODE_RAT_NR          = 1,                                    /* NR */

    AT_MTA_LOW_PWR_MODE_RAT_BUTT
};
typedef VOS_UINT8 AT_MTA_LOW_PWR_MODE_RAT_ENUM_UINT8;



enum MTA_AT_UL_MODE_ENUM
{
    MTA_AT_UL_MODE_NULL                 = 0,                /* ???????????? */
    MTA_AT_UL_MODE_UL_ONLY,                                 /* ??????????UL???? */
    MTA_AT_UL_MODE_SUL_ONLY,                                /* ??????????SUL???? */
    MTA_AT_UL_MODE_BOTH,                                    /* ?????????????????? */
    MTA_AT_UL_MODE_BUTT
};
typedef VOS_UINT32 MTA_AT_UL_MODE_ENUM_UINT32;


enum MTA_AT_INDEX_TABLE_ENUM
{
    /* 3GPP TS38.214 5.1.3.1 3???? */
    MTA_AT_INDEX_TABLE_ONE             = 0,
    MTA_AT_INDEX_TABLE_TWO,
    MTA_AT_INDEX_TABLE_THREE,
    /* 3GPP TS38.214 6.1.4.1 2???? */
    MTA_AT_INDEX_TABLE_FOUR,
    MTA_AT_INDEX_TABLE_FIVE,
    MTA_AT_INDEX_TABLE_BUTT
};
typedef VOS_UINT8 MTA_AT_INDEX_TABLE_ENUM_UINT8;


enum MTA_AT_NR_SCS_TYPE_COMM_ENUM
{
    MTA_AT_NR_SCS_TYPE_COMM_15   = 0x00,
    MTA_AT_NR_SCS_TYPE_COMM_30   = 0x01,
    MTA_AT_NR_SCS_TYPE_COMM_60   = 0x02,
    MTA_AT_NR_SCS_TYPE_COMM_120  = 0x03,
    MTA_AT_NR_SCS_TYPE_COMM_240  = 0x04,
    MTA_AT_NR_SCS_TYPE_COMM_BUTT
};
typedef VOS_UINT8 MTA_AT_NR_SCS_TYPE_COMM_ENUM_UINT8;


enum AT_MTA_NSSAI_QRY_TYPE_ENUM
{
    AT_MTA_NSSAI_QRY_DEF_CFG_NSSAI_ONLY                        = 0x00, /* ??????default config nssai */
    AT_MTA_NSSAI_QRY_DEF_CFG_AND_REJ_NSSAI                     = 0x01, /* ????default config nssai && reject nssai*/
    AT_MTA_NSSAI_QRY_DEF_CFG_AND_REJ_AND_CFG_NSSAI             = 0x02, /* ????default config nssai && reject nssai && Cfg nssai*/
    AT_MTA_NSSAI_QRY_DEF_CFG_AND_REJ_AND_CFG_AND_ALLOWED_NSSAI = 0x03, /* ????default config nssai && reject nssai && Cfg nssai && Allowed nssai*/

    AT_MTA_NSSAI_QRY_PREFER_NSSAI                              = 0x04, /* ????prefer nssai */

    AT_MTA_NSSAI_QRY_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_NSSAI_QRY_TYPE_ENUM_UINT32;


enum AT_MTA_NSSAI_SET_TYPE_ENUM
{
    AT_MTA_NSSAI_SET_PREFER_NSSAI                              = 0x00, /* ????prefer nssai???? */
    AT_MTA_NSSAI_SET_DEF_CFG_NSSAI                             = 0x01, /* ????default config nssai */

    AT_MTA_NSSAI_SET_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_NSSAI_SET_TYPE_ENUM_UINT32;


enum MTA_AT_NETMON_MEAS_RS_TYPE_ENUM
{
    MTA_AT_NETMON_MEAS_RS_TYPE_SSB          = 0,
    MTA_AT_NETMON_MEAS_RS_TYPE_CSI_RS,
    MTA_AT_NETMON_MEAS_RS_TYPE_BUTT
};
typedef VOS_UINT8 MTA_AT_NETMON_MEAS_RS_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 ????????????
*****************************************************************************/
/*****************************************************************************
  5 ??????????
*******************************s**********************************************/
/*****************************************************************************
  6 ????????
*****************************************************************************/
/*****************************************************************************
  7 STRUCT????
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* ?????? */
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucContent[4];                          /* ???????? */
} AT_MTA_MSG_STRU;


typedef struct
{
    MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32    enCposOpType;
    VOS_UINT32                              ulXmlLength;
    VOS_CHAR                                acXmlText[MTA_CPOS_XML_MAX_LEN];
} AT_MTA_CPOS_REQ_STRU;


typedef struct
{
    AT_MTA_LOW_PWR_MODE_RAT_ENUM_UINT8  enRat;
    VOS_UINT8                           aucRcv[3];
} AT_MTA_LOW_PWR_MODE_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_LOW_PWR_MODE_CNF_STRU;



typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????????? */
} MTA_AT_CPOS_CNF_STRU;


typedef struct
{
    /* AT??MTA??????XML??????????????1024???????????????????????????????????????????? */
    VOS_CHAR                            acXmlText[MTA_CPOSR_XML_MAX_LEN + 1];
    VOS_UINT8                           aucRsv[3];
} MTA_AT_CPOSR_IND_STRU;

typedef struct
{
    VOS_UINT16                                   usTransactionID;
    VOS_UINT8                                    ucMsgBodyType;
    VOS_UINT8                                    ucCommonIEValidFlg;
    VOS_UINT8                                    ucEndFlg;
    VOS_UINT8                                    ucID;
    VOS_UINT8                                    ucReserved;
    VOS_UINT8                                    ucNameLength;
    VOS_UINT8                                    aucName[MTA_MAX_EPDU_NAME_LEN]; /* ????????????'\0' */
    VOS_UINT8                                    ucTotal;
    VOS_UINT8                                    ucIndex;
    VOS_UINT16                                   usDataLength;
    VOS_UINT8                                    aucData[MTA_MAX_EPDU_BODY_LEN];
} MTA_AT_EPDU_DATA_IND_STRU;

typedef struct
{
    VOS_UINT32                          ulClearFlg;
} MTA_AT_XCPOSRRPT_IND_STRU;


typedef struct
{
    MTA_AT_CGPSCLOCK_ENUM_UINT32        enGpsClockState;                        /* RF????GPS???????? */
} AT_MTA_CGPSCLOCK_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????????? */

    MTA_AT_MODEM_ID_ENUM_UINT8          enModemId;
    MTA_AT_RAT_MODE_ENUM_UINT8          enRatMode;

    VOS_UINT8                           aucReserved[2];
} MTA_AT_CGPSCLOCK_CNF_STRU;


typedef struct
{
    AT_MTA_PERS_CATEGORY_ENUM_UINT8     enCategory;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPassword[MTA_SIMLOCK_PASSWORD_LEN];
} AT_MTA_SIMLOCKUNLOCK_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????????? */
} MTA_AT_SIMLOCKUNLOCK_CNF_STRU;



typedef struct
{
    VOS_UINT8                           ucRatType;
    VOS_UINT8                           aucReserve[3];                          /* ???????????? */
}AT_MTA_QRY_NMR_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32         enResult;
    VOS_UINT8                         ucTotalIndex;
    VOS_UINT8                         ucCurrIndex;
    VOS_UINT16                        usNMRLen;                                 /* NMR???????? */
    VOS_UINT8                         aucNMRData[4];                            /* NMR?????????? */
}MTA_AT_QRY_NMR_CNF_STRU;




typedef struct
{
    VOS_UINT8                                   ucOffsetFlg;                    /* 0:??????1:????*/
    VOS_UINT8                                   aucReserve[3];                  /* ???????????? */
}AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU;


typedef struct
{
    VOS_UINT8                           ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM];
}AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU;


typedef struct
{
    VOS_UINT8                           ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[AT_MTA_GAS_AUTOTEST_MAX_PARA_NUM];
}AT_MTA_GAS_AUTOTEST_QRY_PARA_STRU;


typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM];
}MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU   stWrrAutoTestRslt;
} MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[MTA_AT_GAS_AUTOTEST_MAX_RSULT_NUM];
}MTA_AT_GAS_AUTOTEST_QRY_RSLT_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_GAS_AUTOTEST_QRY_RSLT_STRU   stGrrAutoTestRslt;
} MTA_AT_GAS_AUTOTEST_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT16                      usCellFreq;
    VOS_UINT16                      usPrimaryScramCode;
    VOS_INT16                       sCpichRscp;
    VOS_INT16                       sCpichEcN0;

}MTA_AT_WRR_CELLINFO_STRU;


typedef struct
{
     VOS_UINT32                     ulCellNum;
     MTA_AT_WRR_CELLINFO_STRU       astWCellInfo[MTA_AT_WRR_MAX_NCELL_NUM];         /*????????W 8????????????*/

} MTA_AT_WRR_CELLINFO_RSLT_STRU;

typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_CELLINFO_RSLT_STRU       stWrrCellInfo;
} MTA_AT_WRR_CELLINFO_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT16                      usEventId;                                  /*??????????????*/
    VOS_UINT16                      usCellNum;
    VOS_UINT16                      ausPrimaryScramCode[MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM];
}MTA_AT_WRR_MEANRPT_STRU;


typedef struct
{
    VOS_UINT32                      ulRptNum;
    MTA_AT_WRR_MEANRPT_STRU         astMeanRptInfo[MTA_AT_WRR_MAX_MEANRPT_NUM];
}MTA_AT_WRR_MEANRPT_RSLT_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_MEANRPT_RSLT_STRU        stMeanRptRslt;
} MTA_AT_WRR_MEANRPT_QRY_CNF_STRU;


typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}MTA_AT_ANTENNA_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucFreqLockEnable;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLockedFreq;
} MTA_AT_WRR_FREQLOCK_CTRL_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_FREQLOCK_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_FREQLOCK_CTRL_STRU       stFreqLockInfo;
} MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRrcVersion;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_CELLSRH_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCellSearchType;
    VOS_UINT8                           aucReserve[3];
} MTA_AT_WRR_CELLSRH_QRY_CNF_STRU;


typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucRssi;                                 /* Rssi, GU??????*/
    VOS_UINT8                           aucReserve[3];

}AT_MTA_ANQUERY_2G_3G_PARA_STRU;


typedef struct
{
    VOS_INT16                           sRsrp;                                  /* ??????(-141,-44), 99?????? */
    VOS_INT16                           sRsrq;                                  /* ??????(-40, -6) , 99?????? */
    VOS_INT16                           sRssi;                                  /* Rssi, LTE??????*/
    VOS_UINT8                           aucReserve[2];
}AT_MTA_ANQUERY_4G_PARA_STRU;


typedef struct
{
    VOS_UINT8                               enServiceSysMode;                       /* ????????????*/
    VOS_UINT8                               aucReserve[3];
    union
    {
        AT_MTA_ANQUERY_2G_3G_PARA_STRU      st2G3GCellSignInfo;                     /* Rssi, GU??????*/
        AT_MTA_ANQUERY_4G_PARA_STRU         st4GCellSignInfo;                       /* Rssi, LTE??????*/
    }u;
}AT_MTA_ANQUERY_PARA_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ???????? */
    AT_MTA_ANQUERY_PARA_STRU            stAntennaInfo;
}MTA_AT_ANTENNA_INFO_QRY_CNF_STRU;


typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}AT_MTA_CSNR_PARA_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ???????? */
    AT_MTA_CSNR_PARA_STRU              stCsnrPara;
}MTA_AT_CSNR_QRY_CNF_STRU;

/*****************************************************************************
 ??????    : AT_MTA_CSQLVL_PARA_STRU
 ????????  : CSQLVL??????????????????????
             ????RSCP ??????RSCP ????????
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRscp;                                 /* RSCP ???? */
    VOS_UINT16                          usLevel;                                /* RSCP ???????? */
}AT_MTA_CSQLVL_PARA_STRU;


typedef struct
{
    VOS_UINT8                           enRssilv;                         /* CSQLVLEX???????????????????? */
    VOS_UINT8                           enBer;                            /* ????????????????????????????BER????????99*/
}AT_MTA_CSQLVLEXT_PARA_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ???????? */
    AT_MTA_CSQLVL_PARA_STRU             stCsqLvlPara;
    AT_MTA_CSQLVLEXT_PARA_STRU          stCsqLvlExtPara;
    VOS_UINT8                           aucReserved[2];
}MTA_AT_CSQLVL_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????? */
    AT_MTA_FRAT_IGNITION_ENUM_UNIT8     enFratIgnitionState;                    /* IgnitionState */
    VOS_UINT8                           aucReserved[3];
}MTA_AT_FRAT_IGNITION_QRY_CNF_STRU;


typedef struct
{
    AT_MTA_FRAT_IGNITION_ENUM_UNIT8     enFratIgnitionState;                    /* IgnitionState */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_FRAT_IGNITION_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ????????????*/
} MTA_AT_FRAT_IGNITION_SET_CNF_STRU;



typedef struct
{
    AT_MTA_BODY_SAR_STATE_ENUM_UINT16   enState;       /* Body SAR???? */
    VOS_UINT16                          usRsv;         /* ?????? */
    MTA_BODY_SAR_PARA_STRU              stBodySARPara; /* Body SAR???????????? */
}AT_MTA_BODY_SAR_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ???????? */
}MTA_AT_RESULT_CNF_STRU;


typedef struct
{
    VOS_UINT8                           aucReserved[4]; /* ?????? */
}AT_MTA_RESERVE_STRU;


typedef struct
{
    VOS_UINT8                           ucCssiRptFlg;                           /* ??????????+CSSI?????????????? 0:??????;1:???? */
    VOS_UINT8                           ucCssuRptFlg;                           /* ??????????+CSSU?????????????? 0:??????;1:???? */
} AT_MTA_CSSN_RPT_FLG_STRU;


typedef struct
{
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                  /* ??????????????0:????????????????????1:????????????????????2:????RptCfg??????????????bit?????????????? */
    VOS_UINT8                                   aucReserve[3];                  /* ???????? */
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];                   /* 64bit???????????? */
} AT_MTA_CURC_SET_NOTIFY_STRU;


typedef struct
{
    VOS_UINT8                           aucReserve[4];
} AT_MTA_CURC_QRY_REQ_STRU;


typedef struct
{
    AT_MTA_RPT_SET_TYPE_ENUM_UINT32     enReqType;                              /* ???????? */

    union
    {
        VOS_UINT8                       ucModeRptFlg;                           /* mode???????????????? 0:????????1:???? */
        VOS_UINT8                       ucSrvstRptFlg;                          /* service status???????????????? */
        VOS_UINT8                       ucRssiRptFlg;                           /* rssi???????????????? */
        VOS_UINT8                       ucTimeRptFlg;                           /* time???????????????? */
        VOS_UINT8                       ucCtzrRptFlg;                           /* ctzr???????????????? */
        VOS_UINT8                       ucDsFlowRptFlg;                         /* ???????????????????? */
        VOS_UINT8                       ucSimstRptFlg;                          /* sim?????????????????????? */
        VOS_UINT8                       ucCregRptFlg;                           /* cs?????????????????????????? */
        VOS_UINT8                       ucCgregRptFlg;                          /* ps?????????????????????????? */
        VOS_UINT8                       ucCeregRptFlg;                          /* L???????????????????????? */
        VOS_UINT8                       ucCsidRptFlg;                           /* CSID???????????????? */
        VOS_UINT8                       ucClocinfoRptFlg;                       /* CLOCINFO???????????????? */
        VOS_UINT8                       ucMtReattachRptFlg;                     /* MTREATTACH???????????????? */
        VOS_UINT8                       ucCenfsRptFlg;                          /* ^CENFS???????????????? 0:????????1:???? */
        VOS_UINT8                       ucC5gregRptFlg;                         /* NR???????????????????????? */

        VOS_UINT8                       ucLendcRptFlg;

        VOS_UINT8                       ucRrcStatRptFlg;
        VOS_UINT8                       ucHfreqInfoRptFlg;
    }u;

    VOS_UINT8                           aucReserve[3];

 } AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU;


typedef struct
{
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;
} AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucGameMode;
    VOS_UINT8                           aucRsv[3];
} AT_MTA_COMM_GAME_MODE_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ucResult;
} MTA_AT_GAME_MODE_SET_CFN_STRU;


typedef struct
{
    MODEM_ID_ENUM_UINT16                enSourceModemId;
    MODEM_ID_ENUM_UINT16                enDestinationModemId;
    PLATAFORM_RAT_CAPABILITY_STRU       stSourceModemPlatform;
    PLATAFORM_RAT_CAPABILITY_STRU       stDestinationModemPlatform;
}AT_MTA_CDMA_MODEM_CAP_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ucResult;
} MTA_AT_CDMA_MODEM_CAP_SET_CNF_STRU;


typedef struct
{
    MODEM_ID_ENUM_UINT16                enCdmaModemId;       /* cdma??????????modem id */
    VOS_UINT8                           aucRsv[2];
    PLATAFORM_RAT_CAPABILITY_STRU       stModem0Platform;
    PLATAFORM_RAT_CAPABILITY_STRU       stModem1Platform;
}AT_MTA_CDMA_CAP_RESUME_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ucResult;
} MTA_AT_CDMA_CAP_RESUME_SET_CNF_STRU;



typedef struct
{
    VOS_UINT16                          usPidIndex;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulLen; /* ?????????????? */
    VOS_UINT8                           aucDate[AT_CMD_COMM_BOOSTER_BS_MAX_LENGTH];
} AT_MTA_COMM_BOOSTER_SET_REQ_STRU;


typedef struct
{
    VOS_UINT16                          usPidIndex;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulLen; /* ?????????????? */
    VOS_UINT8                           aucDate[AT_CMD_COMM_BOOSTER_BS_MAX_LENGTH];
} AT_MTA_COMM_BOOSTER_QUERY_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucInternalResultFlag;      /* ???????????? */
    VOS_UINT8                           ucExternalResultFlag;      /* ???????????? */
    VOS_UINT8                           aucRsv[2];                 /* ?????? */
    VOS_UINT32                          ulResult;                  /* ???? */
}MTA_AT_COMM_BOOSTER_SET_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucResult;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulLen;  /* ?????????????? */
    VOS_UINT8                           aucDate[MTA_AT_BOOSTER_QRY_CNF_MAX_NUM];
}MTA_AT_COMM_BOOSTER_QUERY_CNF_STRU;



typedef struct
{
    TAF_MTA_NV_CARRIER_OPT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_SET_NVLOAD_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulPidIndex;
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucBoosterIndData[MTA_AT_BOOSTER_IND_MAX_NUM];  /* Booster??????????????????TLV???????????????????? */
} MTA_AT_COMM_BOOSTER_IND_STRU;


typedef struct
{
    VOS_UINT32                           ulReqType;
}AT_MTA_NVLOAD_SET_REQ_STRU;


typedef struct
{
    VOS_UINT16                          usReqType;
    VOS_UINT16                          usTempRange;                 /*????????(????????????????????????????????)??"11111"????????????*/
    VOS_INT16                           sPpmOffset;                  /*??????????*/
    VOS_INT16                           sTimeOffset;                 /*??????????*/

}AT_MTA_SET_SAMPLE_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_SET_SAMPLE_CNF_STRU;




typedef struct
{
    VOS_UINT8                           ucPseudRat;                            /* ?????????? 1.GSM  2.WCDMA  3.LTE */
    VOS_UINT8                           ucPseudBtsQryType;                     /* ???????? 1.??????????????????  2.?????????????????? */
    VOS_UINT8                           aucRsv[2];

}AT_MTA_SET_PSEUDBTS_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32               enResult;                               /* NO_ERROR:??????????:???? */
    VOS_UINT8                               ucPseudBtsIdentType;                    /* ???????? 1.??????????????????  2.?????????????????? */
    VOS_UINT8                               aucRsv[3];

    union
    {
        VOS_UINT32                          ulPseudBtsIdentTimes;                   /* ???????? */
        VOS_UINT8                           ucPseudBtsIdentCap;                     /* ???????? */
    }u;
}MTA_AT_PSEUD_BTS_SET_CNF_STRU;




typedef struct
{
    VOS_UINT16                          usClfsGroupNum;                         /* AT??????CLFS????????????4?????????????????????????????????????????? */
    VOS_UINT16                          usDataLength;                           /* aucClfsData???? */
    VOS_UINT8                           aucClfsData[4];                         /* CLFS???????????? */
}AT_MTA_PARA_INFO_STRU;




typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* 0:??????????1:???????? */
    VOS_UINT8                           ucSeq;                                  /* ?????? */
    VOS_UINT8                           ucType;                                 /* 0:????????GSM?????????????? */
    VOS_UINT8                           aucVersionId[AT_MTA_VERSION_INFO_LEN]; /* ??????????????xx.xx.xxx */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulProbaRate;                            /* ??????????????????????????0~99999??????99999????99.999%???? */
    AT_MTA_PARA_INFO_STRU               stParaInfo;
}AT_MTA_SET_SUBCLFSPARAM_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32   enResult;
}MTA_AT_SUBCLFSPARAM_SET_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32   enResult;
    VOS_UINT8                   aucVersionId[AT_MTA_VERSION_INFO_LEN];          /* ?????? */
    VOS_UINT8                   aucRsv[2];
}MTA_AT_SUBCLFSPARAM_QRY_CNF_STRU;



typedef struct
{
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           aucReserve[3];
} AT_MTA_NCELL_MONITOR_SET_REQ_STRU;


typedef struct
{
    AT_MTA_CLEAR_FREQ_FLG_ENUM_UINT8    enMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU;



typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                          /* ??????????????0:????????????????????1:????????????????????2:????ReportCfg??????????????bit?????????????? */
    VOS_UINT8                                   aucReserve[3];
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];  /* ???????????? */
} MTA_AT_CURC_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;

    union
    {
        VOS_UINT8                       ucTimeRptFlg;                           /* time???????????????? */
        MTA_TAF_CTZR_TYPE_ENUM_UINT32   ucCtzrRptFlg;                           /* ctzr???????????????? */
        AT_MTA_CSSN_RPT_FLG_STRU        stCssnRptFlg;                           /* cssn?????????????????????? */
        VOS_UINT8                       ucCusdRptFlg;                           /* cusd?????????????????????? */
    }u;

} MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU;




typedef struct
{
    VOS_UINT8                           aucImei[NV_ITEM_IMEI_SIZE]; /* IMEI???? */
}MTA_AT_CGSN_QRY_CNF_STRU;

typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[2];
} MTA_AT_NCELL_MONITOR_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_NCELL_MONITOR_IND_STRU;



typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /* ???????????????? */
    VOS_UINT8                           aucReserved1[3];                        /* ?????? */
} AT_MTA_REFCLKFREQ_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulFreq;                                 /* GPS??????????????????????Hz */
    VOS_UINT32                          ulPrecision;                            /* ????GPS????????????????????ppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /* ???????????????? */
    VOS_UINT8                           aucReserved1[2];                        /* ?????? */
} MTA_AT_REFCLKFREQ_QRY_CNF_STRU;



typedef struct
{
    VOS_UINT16                          usChannelNo;                            /* ?????????? */
    VOS_UINT16                          usRficReg;
}AT_MTA_RFICSSIRD_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulRegValue;                             /* ???????????????? */
} MTA_AT_RFICSSIRD_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulFreq;                                 /* GPS??????????????????????Hz */
    VOS_UINT32                          ulPrecision;                            /* ????GPS????????????????????ppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /* ???????????????? */
    VOS_UINT8                           aucReserved1[2];                        /* ?????? */
} MTA_AT_REFCLKFREQ_IND_STRU;



typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????? */
} MTA_AT_HANDLEDECT_SET_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usHandle;                               /* ?????????? */
    VOS_UINT16                          aucReserved1[1];
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????? */
} MTA_AT_HANDLEDECT_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucCause;                                /* PS???????????? */
    VOS_UINT8                           aucReserved1[3];                        /* ?????? */
} MTA_AT_PS_TRANSFER_IND_STRU;


typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* ????????MIPICLK?? */
    VOS_UINT8                           aucReserved1[2];                        /* ?????? */
} MTA_AT_RF_LCD_MIPICLK_IND_STRU;


typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* ????????MIPICLK?? */
    VOS_UINT16                          usResult;
} MTA_AT_RF_LCD_MIPICLK_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulVersion;                              /* ?????????? */
}AT_MTA_ECID_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           aucCellInfoStr[4];                      /* ???????????????????? */
}MTA_AT_ECID_SET_CNF_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                  enPsProtectFlg;
    VOS_UINT8                           aucReserve[3];                          /* ???????????? */
}AT_MTA_RRC_PROTECT_PS_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* ??????AT?????? */
}MTA_AT_RRC_PROTECT_PS_CNF_STRU;


typedef struct
{
    VOS_UINT8                           aucReserve[4];                          /* ???????????? */
}AT_MTA_PHY_INIT_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* ??????AT?????? */
}MTA_AT_PHY_INIT_CNF_STRU;



typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU;


typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulDpdtValue;
} AT_MTA_SET_DPDT_VALUE_REQ_STRU;


typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_QRY_DPDT_VALUE_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDT_VALUE_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulDpdtValue;
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_QRY_DPDT_VALUE_CNF_STRU;


typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    AT_MTA_TRX_TAS_CMD_ENUM_UINT8       enCmd;
    AT_MTA_CMD_SIGNALING_ENUM_UINT8     enMode;
    VOS_UINT8                           ucReserved;
    VOS_UINT32                          ulTrxTasValue;
}AT_MTA_SET_TRX_TAS_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_TRX_TAS_CNF_STRU;


typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    AT_MTA_CMD_SIGNALING_ENUM_UINT8     enMode;
    VOS_UINT8                           aucReserved[2];
}AT_MTA_QRY_TRX_TAS_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulTrxTasValue;
} MTA_AT_QRY_TRX_TAS_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucThreshold;                            /* ??????????????????????????????????:[0,70] */
    VOS_UINT8                           ucFreqNum;                              /* ????????????????????????????????:[0,255] */
    VOS_UINT8                           aucReserved[2];
} AT_MTA_GSM_JAM_DETECT_STRU;


typedef struct
{
    VOS_UINT8                           ucRssiSrhThreshold;                     /* ????RSSI??????????????????????????????????????[0,70]????????????????70???? */
    VOS_UINT8                           ucRssiSrhFreqPercent;                   /* ????RSSI????????????????????????????????????BAND??????????????????????????????????????[0,100] */
    VOS_UINT16                          usPschSrhThreshold;                     /* ????PSCH??????????????????????????????????????????:[0,65535] */
    VOS_UINT8                           ucPschSrhFreqPercent;                   /* ????PSCH????????????????????????????????????BAND????????????????????????????????????:[0,100] */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_WCDMA_JAM_DETECT_STRU;


typedef struct
{
    VOS_INT16                           sRssiThresh;                            /* ????RSSI??????????????????????????????????????[0,70]????????????????70???? */
    VOS_UINT16                          usPssratioThresh;                       /* ????PSS Ratio????????????????????????????????????????:[0,100] */
    VOS_UINT8                           ucRssiPercent;                          /* ????RSSI????????????????????????????????????BAND??????????????????????????????????????[0,100] */
    VOS_UINT8                           ucPssratioPercent;                      /* ????PSS Ratio??????????????????????????????????????????????????????????:[0,100] */
    VOS_UINT8                           aucReserved[2];
} AT_MTA_LTE_JAM_DETECT_STRU;


typedef union
{
    AT_MTA_GSM_JAM_DETECT_STRU          stGsmPara;
    AT_MTA_WCDMA_JAM_DETECT_STRU        stWcdmaPara;
    AT_MTA_LTE_JAM_DETECT_STRU          stLtePara;
}AT_MTA_JAM_DETECT_UNION;


typedef struct
{
    VOS_UINT8                           ucMode;                                 /* ???????????????? */
    VOS_UINT8                           aucReserved[2];
    AT_MTA_CMD_RATMODE_ENUM_UINT8       ucRat;                                  /* ???????? */
    AT_MTA_JAM_DETECT_UNION             unJamPara;                              /* ???????????????? */
}AT_MTA_SET_JAM_DETECT_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_JAM_DETECT_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucGsmJamMode;                           /* GSM???????????????????????? */
    VOS_UINT8                           ucWcdmaJamMode;                         /* WCDMA???????????????????????? */
    VOS_UINT8                           ucLteJamMode;                           /* LTE???????????????????????? */
    VOS_UINT8                           ucReserved;
    AT_MTA_GSM_JAM_DETECT_STRU          stGsmPara;
    AT_MTA_WCDMA_JAM_DETECT_STRU        stWcdmaPara;
    AT_MTA_LTE_JAM_DETECT_STRU          stLtePara;
}MTA_AT_QRY_JAM_DETECT_CNF_STRU;


typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       ucRat;
    VOS_UINT8                           aucReserved[3];
    MTA_AT_JAM_RESULT_ENUM_UINT32       enJamResult;
}MTA_AT_JAM_DETECT_IND_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:??????????????0:???????? */
    AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8  enRatMode;
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;
    VOS_UINT32                          ulLockedFreq;
} AT_MTA_SET_FREQ_LOCK_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FREQ_LOCK_CNF_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                  enableFlag;                             /* PS_TRUE:??????PS_FALSE:?????? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
    VOS_UINT16                          usFreq;                                 /* ?????? */
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;                                 /* GSM???? */
} AT_MTA_SET_GSM_FREQLOCK_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_GSM_FREQLOCK_CNF_STRU;



typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ulResult;
    PS_BOOL_ENUM_UINT8                  enLockFlg;                              /* PS_TRUE: ??????????????,PS_FALSE: ???????????????? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
    VOS_UINT16                          usFreq;                                 /* ?????????? */
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;                                 /* GSM???? */
} MTA_AT_QRY_GSM_FREQLOCK_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_DEL_CELLENTITY_CNF_STRU;

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)

enum AT_FREQLOCK_W_TYPE_ENUM
{
    AT_MTA_WCDMA_FREQLOCK_CMD_FREQ_ONLY         = 8,                            /* ????CWAS???????? */
    AT_MTA_WCDMA_FREQLOCK_CMD_COMBINED          = 9,                            /* ????CWAS????+???????? */
    AT_MTA_WCDMA_FREQLOCK_CMD_BUTT
};
typedef VOS_UINT8 AT_MTA_WCDMA_FREQLOCK_CMD_ENUM_UINT8;


enum AT_MTA_M2M_FREQLOCK_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY     = 1,                            /* ????ONLY???? */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_COMBINED = 2,                            /* ????+??????/????/????????ID */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8;


typedef struct
{
    VOS_UINT16                                  usFreq;                         /* ?????? */
    AT_MTA_GSM_BAND_ENUM_UINT16                 enBand;                         /* GSM???? */
    VOS_UINT32                                  ulReserve;                      /* 8????????-???????? */
} AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU;


typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /* ???????? */
    VOS_UINT8                                   aucReserved[3];                 /* ?????? */
    VOS_UINT16                                  usFreq;                         /* ?????? */
    VOS_UINT16                                  usPsc;                          /* WCDMA?????? */
}AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU;


typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /* ???????? */
    VOS_UINT8                                   aucReserved[3];                 /* ?????? */
    VOS_UINT16                                  usFreq;                         /* ?????? */
    VOS_UINT16                                  usSc;                           /* TD-SCDMA???? */
}AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU;


typedef struct
{
    VOS_UINT32                                  ulFreq;                         /* ?????? */
    VOS_UINT16                                  usPci;                          /* LTE????????ID */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /* ???????? */
    VOS_UINT8                                   ucReserved;                     /* ?????? */
}AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU;


enum AT_FREQLOCK_FLAG_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_MODE_GSM            = 1,                                /* GSM???? */
    AT_MTA_M2M_FREQLOCK_MODE_WCDMA          = 2,                                /* WCDMA???? */
    AT_MTA_M2M_FREQLOCK_MODE_TDSCDMA        = 3,                                /* TD-SCDMA???? */
    AT_MTA_M2M_FREQLOCK_MODE_LTE            = 4,                                /* LTE???? */
    AT_MTA_M2M_FREQLOCK_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_MODE_ENUM_UINT8;


enum AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF       = 0,                                /* ???????? */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ON        = 1,                                /* ???????? */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8;


typedef struct
{
    AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8         enableFlag;                                 /* ???????? */
    AT_MTA_M2M_FREQLOCK_MODE_ENUM_UINT8         ucMode;                                     /* ???????? */
    VOS_UINT8                                   aucReserved[6];                             /* ???? */
    AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU           stGFreqPara;                                /* G?????????????? */
    AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU         stWFreqPara;                                /* W?????????????? */
    AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU       stTDFreqPara;                               /* TD?????????????? */
    AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU           stLFreqPara;                                /* L?????????????? */
} AT_MTA_SET_M2M_FREQLOCK_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ulResult;
} MTA_AT_SET_M2M_FREQLOCK_CNF_STRU;


typedef struct
{
    VOS_UINT8                                   ucFreqState[MTA_FREQLOCK_MAX_MODE];     /* GUTL?????????????? */
    AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU           stGFreqLockInfo;                        /* GSM???????????????? */
    AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU         stWFreqLockInfo;                        /* WCDMA???????????????? */
    AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU       stTFreqLockInfo;                        /* TD-SCDMA???????????????? */
    AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU           stLFreqLockInfo;                        /* LTE???????????????? */
} MTA_AT_QRY_M2M_FREQLOCK_CNF_STRU;
#endif



typedef struct
{
    MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16            enGphyXpassMode;
    VOS_UINT16                                    usResev1;
    MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16          enWphyXpassMode;
    VOS_UINT16                                    usResev2;
} MTA_AT_XPASS_INFO_IND_STRU;

typedef struct
{
    VOS_UINT32      ulCtrlType;
    VOS_UINT32      ulPara1;
    VOS_UINT32      ulPara2;
    VOS_UINT32      ulPara3;
} AT_MTA_SET_FEMCTRL_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FEMCTRL_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucSecType;                              /* ???????????? */
    VOS_UINT8                           ucSecStrFlg;                            /* ???????????????????? */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucSecString[AT_RSA_CIPHERTEXT_LEN];    /* ???????????? */
} AT_MTA_NVWRSECCTRL_SET_REQ_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                          enActFrFlag;                    /* ????FR??????0:??????  1:???? */
    VOS_UINT8                                   aucRsv[3];                      /* ?????? */
}AT_MTA_SET_FR_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enRslt;                         /* FR?????????? */
}MTA_AT_SET_FR_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usYear;
    VOS_UINT8                           ucMonth;
    VOS_UINT8                           ucDay;
    VOS_UINT8                           ucHour;
    VOS_UINT8                           ucMinute;
    VOS_UINT8                           ucSecond;
    VOS_INT8                            cTimeZone;
}MTA_AT_TIME_STRU;



typedef struct
{
    VOS_UINT8                           ucDST;
    VOS_UINT8                           ucIeFlg;
    VOS_INT8                            cLocalTimeZone;
    VOS_UINT8                           ucRsv;
    VOS_UINT8                           aucCurcRptCfg[8];
    VOS_UINT8                           aucUnsolicitedRptCfg[8];
    MTA_AT_TIME_STRU                    stUniversalTimeandLocalTimeZone;
}TAF_AT_COMM_TIME_STRU;


typedef struct
{
    MTA_AT_TIME_INFO_RPT_OPT_ENUM_UINT8 enRptOptType;
    VOS_UINT8                           aucReserve[3];
    TAF_AT_COMM_TIME_STRU               stCommTimeInfo;
}MTA_AT_SIB16_TIME_UPDATE_STRU;


enum MTA_AT_ACCESS_STRATUM_REL_ENUM
{
    MTA_AT_ACCESS_STRATUM_REL8                  = 0,
    MTA_AT_ACCESS_STRATUM_REL9                  = 1,
    MTA_AT_ACCESS_STRATUM_REL10                 = 2,
    MTA_AT_ACCESS_STRATUM_REL11                 = 3,
    MTA_AT_ACCESS_STRATUM_REL12                 = 4,
    MTA_AT_ACCESS_STRATUM_REL13                 = 5,
    MTA_AT_ACCESS_STRATUM_REL14                 = 6,
    MTA_AT_ACCESS_STRATUM_REL_SPARE1            = 7
};
typedef VOS_UINT8 MTA_AT_ACCESS_STRATUM_REL_ENUM_UINT8;


typedef struct
{
    MTA_AT_ACCESS_STRATUM_REL_ENUM_UINT8        enAccessStratumRel; /* ????AT???????????????? */
    VOS_UINT8                                   aucRsv[3];
} MTA_AT_ACCESS_STRATUM_REL_IND_STRU;



typedef struct
{
    VOS_UINT8                           ucValidflag;        /* ??????CC TM1????TRUE??????????????????; ?????????? ??????????FALSE(????????????????????????0). */
    VOS_UINT8                           ucRxAntNum;         /* UE????????????2????4?? */
    VOS_UINT8                           ucTmMode;            /*???????? ?????? ucTmMode=0(????????????1)??????????????????????????*/
    VOS_UINT8                           aucReserved;
    VOS_UINT32                          ulCorrQR1Data0011;  /* ????????6???????????????????????????? */
    VOS_UINT32                          ulCorrQR1Data01IQ;
    VOS_UINT32                          ulCorrQR2Data0011;  /* ??4?????????? */
    VOS_UINT32                          ulCorrQR2Data01IQ;  /* ??4?????????? */
    VOS_UINT32                          ulCorrQR3Data0011;  /* ??4?????????? */
    VOS_UINT32                          ulCorrQR3Data01IQ;  /* ??4?????????? */
    VOS_INT16                           sRsrpR0;            /*???? 0 rsrp?? ???? dB*/
    VOS_INT16                           sRsrpR1;            /*???? 1 rsrp?? ???? dB*/
    VOS_INT16                           sRsrpR2;            /*???? 2 rsrp?? ???? dB???? 4????????*/
    VOS_INT16                           sRsrpR3;            /*???? 3 rsrp?? ???? dB???? 4????????*/
    VOS_INT16                           sRssiR0;            /*???? 0 rssi?? ???? dB*/
    VOS_INT16                           sRssiR1;            /*???? 1 rssi?? ???? dB*/
    VOS_INT16                           sRssiR2;            /*???? 2 rssi?? ???? dB???? 4????????*/
    VOS_INT16                           sRssiR3;            /*???? 3 rssi?? ???? dB???? 4????????*/
    VOS_INT16                           sRsv[8];
} MTA_AT_ECC_STATUS_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulEccEnable;
    VOS_UINT32                          ulRptPeriod;
}AT_MTA_SET_ECC_CFG_REQ_STRU;


typedef MTA_AT_RESULT_CNF_STRU MTA_AT_SET_ECC_CFG_CNF_STRU;

typedef MTA_AT_RESULT_CNF_STRU MTA_AT_LENDC_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucEndcAvaliableFlag;                    /* ????????????????endc????: 0:????????1:???? */
    VOS_UINT8                           ucNrPscellFlag;                         /* ????????ENDC??????????: 0:??ENDC??????1:ENDC???????????? */
    VOS_UINT8                           ucEndcPlmnAvaliableFlag;                /* PLMN LIST????????PLMN????ENDC????, true??????PLMN????ENDC????, false????????PLMN????endc???? */
    VOS_UINT8                           ucEndcEpcRestrictedFlag;                /* ??????????????endc??????true??????????????endc??????false??????????????????endc???? */
} MTA_AT_LENDC_INFO_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enRslt;                                 /* ???? */
    VOS_UINT32                          ulReportFlag;                           /* ????/????^LENDC??????????0:????  1:???? */
    MTA_AT_LENDC_INFO_STRU              stLendcInfo;
} MTA_AT_LENDC_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_LENDC_INFO_STRU              stLendcInfo;
} MTA_AT_LENDC_INFO_IND_STRU;

/*****************************************************************************
 ??????    : MTA_NRRC_FREQLOCK_TYPE_ENUM
 ????????  :
 ASN.1???? :
 ????????  : NRRC????????
*****************************************************************************/
enum MTA_AT_FREQLOCK_TYPE_ENUM
{
    MTA_AT_FREQLOCK_TYPE_LOCK_NONE                  =  0,
    MTA_AT_FREQLOCK_TYPE_LOCK_FREQ                  =  1,
    MTA_AT_FREQLOCK_TYPE_LOCK_CELL                  =  2,
    MTA_AT_FREQLOCK_TYPE_LOCK_BAND                  =  3,

    MTA_AT_FREQLOCK_TYPE_LOCK_BUTT
};
typedef VOS_UINT8 MTA_AT_FREQLOCK_TYPE_ENUM_UINT8;

/*****************************************************************************
 ??????    : MTA_AT_SCS_TYPE_COMM_ENUM
 ????????  :
 ASN.1???? :
 ????????  : NRRC SCS Type COMM
*****************************************************************************/
enum MTA_AT_SCS_TYPE_COMM_ENUM
{
    MTA_AT_SCS_TYPE_COMM_15          = 0x00,
    MTA_AT_SCS_TYPE_COMM_30          = 0x01,
    MTA_AT_SCS_TYPE_COMM_60          = 0x02,
    MTA_AT_SCS_TYPE_COMM_120         = 0x03,
    MTA_AT_SCS_TYPE_COMM_240         = 0x04,

    MTA_AT_SCS_TYPE_COMM_BUTT
};
typedef VOS_UINT8 MTA_AT_SCS_TYPE_COMM_ENUM_UINT8;

typedef MTA_AT_RESULT_CNF_STRU MTA_AT_NRRC_FREQLOCK_SET_CNF_STRU;


typedef struct
{
    MTA_AT_FREQLOCK_TYPE_ENUM_UINT8     enFreqType;
    MTA_AT_SCS_TYPE_COMM_ENUM_UINT8     enScsType;
    VOS_UINT16                          usReserved;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usPhyCellId;
    VOS_UINT32                          ulNrArfcn;
}AT_MTA_SET_NRFREQLOCK_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_FREQLOCK_TYPE_ENUM_UINT8     enFreqType;
    MTA_AT_SCS_TYPE_COMM_ENUM_UINT8     enScsType;
    VOS_UINT16                          usReserved;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usPhyCellId;
    VOS_UINT32                          ulNrArfcn;
} MTA_AT_NRRC_FREQLOCK_QRY_CNF_STRU;



typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enCfg;                                  /* 0:????????1:???? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
} AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU;



typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC, 3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC, 2 or 3 bytes */
} AT_MTA_PLMN_ID_STRU;


typedef struct
{
    VOS_UINT32                          ulMbmsSerId;                            /* Service ID */
    AT_MTA_PLMN_ID_STRU                 stPlmnId;                               /* PLMN ID */
} AT_MTA_MBMS_TMGI_STRU;


typedef struct
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8    enStateSet;                     /* ???????? */
    VOS_UINT8                                   aucReserved[3];                 /* ?????? */
    VOS_UINT32                                  ulAreaId;                       /* Area ID */
    AT_MTA_MBMS_TMGI_STRU                       stTMGI;                         /* TMGI */
} AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU;


typedef struct
{
    AT_MTA_MBMS_CAST_MODE_ENUM_UINT8    enCastMode;                             /* 0:????,1:???? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
} AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          aulUTC[2];                              /* (0..549755813887) */
} MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucBSSILevel;                            /* BSSI????????,0xFF:????BSSI???????????? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
} MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulCellId;                               /* ????ID */
} MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8 enStatus;                       /* ???????? */
    VOS_UINT8                                   aucReserved[3];                 /* ?????? */
} MTA_AT_EMBMS_STATUS_QRY_CNF_STRU;


typedef struct
{
    AT_MTA_CFG_ENUM_UINT8                       enCfg;                          /* 0:????,1:???? */
    VOS_UINT8                                   aucReserved[3];                 /* ?????? */
} AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;


typedef struct
{
    MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8    enEvent;                            /* ???????? */
    VOS_UINT8                               aucReserved[3];                     /* ?????? */
} MTA_AT_MBMS_SERVICE_EVENT_IND_STRU;


typedef struct
{
    AT_MTA_LTE_LOW_POWER_ENUM_UINT8         enLteLowPowerFlg;                   /* 0: Normal;1: Low Power Consumption */
    VOS_UINT8                               aucReserved[3];                     /* ?????? */
} AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU;


typedef struct
{
    VOS_UINT32                          aulFreqList[AT_MTA_INTEREST_FREQ_MAX_NUM];  /* ???????? */
    AT_MTA_MBMS_PRIORITY_ENUM_UINT8     enMbmsPriority;                             /* VOS_FALSE: ????????;VOS_TRUE: MBMS???? */
    VOS_UINT8                           aucReserved[3];                             /* ?????? */
} AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU;


typedef struct
{
    VOS_UINT32                          bitOpSessionId  : 1;
    VOS_UINT32                          bitSpare        : 31;
    VOS_UINT32                          ulAreaId;                               /* Area ID */
    AT_MTA_MBMS_TMGI_STRU               stTMGI;                                 /* TMGI */
    VOS_UINT32                          ulSessionId;                            /* Session ID */
} MTA_AT_MBMS_AVL_SERVICE_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulAvlServiceNum;                                    /* ??????????,0:???????????????? */
    MTA_AT_MBMS_AVL_SERVICE_STRU        astAvlServices[AT_MTA_MBMS_AVL_SERVICE_MAX_NUM];    /* ???????????? */
} MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;


typedef struct
{
    AT_MTA_COEX_BW_TYPE_ENUM_UINT16             enCoexBWType;
    AT_MTA_COEX_CFG_ENUM_UINT16                 enCfg;
    VOS_UINT16                                  usTxBegin;
    VOS_UINT16                                  usTxEnd;
    VOS_INT16                                   sTxPower;
    VOS_UINT16                                  usRxBegin;
    VOS_UINT16                                  usRxEnd;
    VOS_UINT8                                   aucReserved[2];                 /* ?????? */
} AT_MTA_COEX_PARA_STRU;


typedef struct
{
    VOS_UINT16                          usCoexParaNum;
    VOS_UINT16                          usCoexParaSize;
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU;


typedef struct
{
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           aucMeid[AT_MTA_MEID_DATA_LEN];
    VOS_UINT8                           aucRsv[1];
}AT_MTA_MEID_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ????????????*/
    VOS_UINT8                           aucEFRUIMID[MTA_AT_EFRUIMID_OCTET_LEN_EIGHT];
    VOS_UINT8                           aucMeID[MTA_AT_MEID_NV_DATA_LEN_NEW + 1];  /*Data*/
    VOS_UINT8                           aucPEsn[MTA_AT_PESN_NV_DATA_LEN];      /*Data*/
    VOS_UINT32                          ulMeIDReadRst;
    VOS_UINT32                          ulPEsnReadRst;
}MTA_AT_MEID_QRY_CNF_STRU;





typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ????????????*/
    VOS_UINT8                           ucTransMode;                            /* ????????*/
    VOS_UINT8                           aucReserved[3];                         /*??????*/
} MTA_AT_TRANSMODE_QRY_CNF_STRU;


typedef struct
{
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UE????*/
} AT_MTA_SET_UE_CENTER_REQ_STRU;

#if (FEATURE_ON == FEATURE_UE_MODE_NR)

enum AT_MTA_NR_DC_MODE_ENUM
{
    AT_MTA_NR_DC_MODE_NONE           = 0x00,                               /* ???????????? */
    AT_MTA_NR_DC_MODE_ENDC_ONLY      = 0x01,                               /* ??????ENDC */
    AT_MTA_NR_DC_MODE_NEDC_ONLY      = 0x02,                               /* ??????NEDC */
    AT_MTA_NR_DC_MODE_ENDC_NEDC_BOTH = 0x03,                               /* ENDC??NEDC?????? */
    AT_MTA_NR_DC_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_NR_DC_MODE_ENUM_UINT8;

enum AT_MTA_5GC_ACCESS_MODE_ENUM
{
    AT_MTA_5GC_ACCESS_MODE_NOT_ALLOW  = 0x00,                /* ??????????5gc */
    AT_MTA_5GC_ACCESS_MODE_NR_ONLY    = 0x01,                /* ??????NR????5gc */
    AT_MTA_5GC_ACCESS_MODE_LTE_ONLY   = 0x02,                /* ??????LTE????5gc */
    AT_MTA_5GC_ACCESS_MODE_NR_AND_LTE = 0x03,                /* ????LTE??NR??????5gc */
    AT_MTA_5GC_ACCESS_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_5GC_ACCESS_MODE_ENUM_UINT8;


typedef struct
{
    VOS_UINT8                           ucNrSaSupportFlag;          /* 0:??????NR????????SA??????1:????NR????????SA???? */
    AT_MTA_NR_DC_MODE_ENUM_UINT8        enNrDcMode;                 /* NR??DC???????? */
    AT_MTA_5GC_ACCESS_MODE_ENUM_UINT8   en5gcAccessMode;            /* ????????5gc?????? */
    VOS_UINT8                           ucRsv;
} AT_MTA_SET_5G_OPTION_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enRslt;
} MTA_AT_SET_5G_OPTION_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucNrSaSupportFlag;          /* 0:??????NR????????SA??????1:????NR????????SA???? */
    AT_MTA_NR_DC_MODE_ENUM_UINT8        enNrDcMode;                 /* NR??DC???????? */
    AT_MTA_5GC_ACCESS_MODE_ENUM_UINT8   en5gcAccessMode;            /* ????????5gc?????? */
    VOS_UINT8                           ucRsv;
} MTA_AT_QRY_5G_OPTION_CNF_STRU;
#endif


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ????????????*/
} MTA_AT_SET_UE_CENTER_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ????????????*/
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UE????*/
} MTA_AT_QRY_UE_CENTER_CNF_STRU;



typedef struct
{
    VOS_UINT32                          bitOpTa     :1;
    VOS_UINT32                          bitOpSpare  :31;
    VOS_UINT16                          usTa;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulMcc;              /* ?????????? */
    VOS_UINT32                          ulMnc;              /* ?????????? */
    VOS_UINT32                          ulCellID;           /* ????ID */
    VOS_UINT32                          ulArfcn;            /* ?????????? */
    VOS_UINT16                          usLac;              /* ???????? */
    VOS_INT16                           sRssi;              /* Receiving signal strength in dbm */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;             /* GSM????(0-3) */
    VOS_UINT8                           ucBsic;             /* ?????????? */
    VOS_UINT8                           ucRxQuality;        /* IDLE????????PS????????????,????????????????????????????[0,7] ,??????99*/
}MTA_AT_NETMON_GSM_SCELL_INFO_STRU;

 
typedef struct
{
    VOS_UINT32                                  bitOpCellID  : 1;
    VOS_UINT32                                  bitOpLAC     : 1;
    VOS_UINT32                                  bitOpSpare   : 30;
    VOS_UINT32                                  ulMcc;                  /*??????????*/
    VOS_UINT32                                  ulMnc;                  /*??????????*/
    VOS_UINT32                                  ulCellID;               /*????ID*/
    VOS_UINT32                                  ulArfcn;                /*????*/
    VOS_UINT16                                  usLAC;                  /*????????*/
    VOS_UINT8                                   aucReserved[2];
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32           enCellMeasTypeChoice;   /* NETMON????????????:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU    stCellMeasResultsFDD;    /* FDD */
        MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU    stCellMeasResultsTDD;    /* TDD */
    }u;
}MTA_AT_NETMON_UTRAN_SCELL_INFO_STRU;


typedef struct
{
    VOS_UINT32                                  ulMcc;                  /* ?????????? */
    VOS_UINT32                                  ulMnc;                  /* ?????????? */
    VOS_UINT32                                  ulCellIdentityHighBit;  /* Cell Identity??32?? */
    VOS_UINT32                                  ulCellIdentityLowBit;   /* Cell Identity??32?? */
    VOS_UINT32                                  ulPhyCellID;            /* ????????ID */
    VOS_UINT32                                  ulArfcn;                /* ???? */
    VOS_UINT32                                  ulTac;
    VOS_INT16                                   sRSRP;
    VOS_INT16                                   sRSRQ;
    VOS_INT16                                   sSINR;
    MTA_AT_NR_SCS_TYPE_COMM_ENUM_UINT8          enNrScsType;
    VOS_UINT8                                   ucReserved;
}MTA_AT_NETMON_NR_SCELL_INFO_STRU;


typedef union
{
    MTA_AT_NETMON_GSM_SCELL_INFO_STRU       stGsmSCellInfo;    /* GSM???????????? */
    MTA_AT_NETMON_UTRAN_SCELL_INFO_STRU     stUtranSCellInfo;  /* WCDMA???????????? */
    MTA_NETMON_EUTRAN_SCELL_INFO_STRU       stLteSCellInfo;    /* LTE????????????*/
    MTA_AT_NETMON_NR_SCELL_INFO_STRU        stNrSCellInfo;     /* NR???????????? */
}MTA_AT_NETMON_SCELL_INFO_UN;


typedef struct
{
    VOS_UINT32                          bitOpBsic     : 1;
    VOS_UINT32                          bitOpCellID   : 1;
    VOS_UINT32                          bitOpLAC      : 1;
    VOS_UINT32                          bitOpSpare    : 29;
    VOS_UINT32                          ulCellID;       /*????ID*/
    VOS_UINT32                          ulAfrcn;        /*????*/
    VOS_UINT16                          usLAC;          /*????????*/
    VOS_INT16                           sRSSI;          /* ??????RSSI */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;         /* band 0-3 */
    VOS_UINT8                           ucBsic;         /*??????????*/
    VOS_UINT8                           ucReserved;
}MTA_AT_NETMON_GSM_NCELL_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulArfcn;          /*????*/
    VOS_UINT16                          usPSC;            /*??????*/
    VOS_INT16                           sECN0;            /*ECN0*/
    VOS_INT16                           sRSCP;            /*RSCP*/
    VOS_UINT8                           aucReserved[2];
}MTA_AT_NETMON_UTRAN_NCELL_INFO_FDD_STRU;


typedef struct
{
    VOS_UINT32                          ulArfcn;          /*????*/
    VOS_UINT16                          usSC;             /*????*/
    VOS_UINT16                          usSyncID;         /*??????????*/
    VOS_INT16                           sRSCP;            /*RSCP*/
    VOS_UINT8                           aucReserved[2];
}MTA_AT_NETMON_UTRAN_NCELL_INFO_TDD_STRU;


typedef struct
{
    VOS_UINT32                            ulPhyCellID;      /* ????????ID */
    VOS_UINT32                            ulArfcn;          /* ???? */
    VOS_INT16                             sRSRP;            /* RSRP???????????????? */
    VOS_INT16                             sRSRQ;            /* RSRQ???????????????? */
    VOS_INT16                             sSINR;
    VOS_UINT8                             aucReserved[2];
}MTA_AT_NETMON_NR_NCELL_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucGsmNCellCnt;                               /* GSM ???????? */
    VOS_UINT8                                               ucUtranNCellCnt;                             /* WCDMA ???????? */
    VOS_UINT8                                               ucLteNCellCnt;                               /* LTE ???????? */
    VOS_UINT8                                               ucNrNCellCnt;                                /* NR ???????? */
    MTA_AT_NETMON_GSM_NCELL_INFO_STRU                       astGsmNCellInfo[NETMON_MAX_GSM_NCELL_NUM];   /* GSM ????????????*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32                       enCellMeasTypeChoice;                        /* NETMON????????????:FDD,TDD */
    union
    {
        MTA_AT_NETMON_UTRAN_NCELL_INFO_FDD_STRU             astFddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM]; /* FDD???????????? */
        MTA_AT_NETMON_UTRAN_NCELL_INFO_TDD_STRU             astTddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM]; /* TDD???????????? */
    }u;
    MTA_NETMON_LTE_NCELL_INFO_STRU                          astLteNCellInfo[NETMON_MAX_LTE_NCELL_NUM];   /* LTE ???????????? */
    MTA_AT_NETMON_NR_NCELL_INFO_STRU                        astNrNCellInfo[NETMON_MAX_NR_NCELL_NUM];     /* NR ???????????? */
}MTA_AT_NETMON_NCELL_INFO_STRU;



typedef struct
{
    VOS_UINT32                                  arfcn;
    VOS_UINT32                                  phyCellId;
    VOS_INT16                                   rsrp;
    VOS_INT16                                   rsrq;
    VOS_INT16                                   sinr;
    MTA_AT_NETMON_MEAS_RS_TYPE_ENUM_UINT8       measRsType;
    VOS_UINT8                                   rsv;
} MTA_AT_NETMON_NR_CC_INFO_STRU;


typedef struct
{
    VOS_UINT32                                  componentCarrierNum;                        /* ???????? */
    MTA_AT_NETMON_NR_CC_INFO_STRU               componentCarrierInfo[NETMON_MAX_NR_CC_NUM]; /* ???????? */
} MTA_AT_NETMON_NR_SSCELL_INFO_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;               /* ???????????????? */
    MTA_NETMON_CELL_TYPE_ENUM_UINT32            enCellType;             /* 0:??????????????1:??????????2:???????????????? */
    MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32     enRatType;              /* ?????????????????????? */
    union
    {
        MTA_AT_NETMON_NCELL_INFO_STRU           stNCellInfo;            /*????????*/
        MTA_AT_NETMON_SCELL_INFO_UN             unSCellInfo;
        MTA_AT_NETMON_NR_SSCELL_INFO_STRU       secSrvCellInfo;         /* ?????????????? */
    }u;
} MTA_AT_NETMON_CELL_INFO_STRU;




typedef struct
{
    VOS_UINT32                          ulReserveValue;
} AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    AT_MTA_AFC_CLK_STATUS_ENUM_UINT32   enStatus;
    VOS_INT32                           lDeviation;                                 /* ???? */

    /* ???????? */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /* ?????????? */
    VOS_UINT32                          aulCoeffMantissa[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3???? */
    VOS_UINT16                          ausCoeffExponent[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3???? */

    MTA_AT_MODEM_ID_ENUM_UINT8          enModemId;
    MTA_AT_RAT_MODE_ENUM_UINT8          enRatMode;
    VOS_UINT8                           aucReserved[2];
} MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU;



typedef struct
{
    VOS_UINT32                          ulDoSysEvent;
}AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulDoSigMask;
}AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} MTA_AT_EVDO_REVA_RLINK_INFO_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} MTA_AT_EVDO_SIG_EXEVENT_IND_STRU;


typedef struct
{
    AT_MTA_XCPOSR_CFG_ENUM_UNIT8        enXcposrEnableCfg;                            /* GPS?????????????????????????????????????????????????? */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_SET_XCPOSR_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????????? */
    AT_MTA_XCPOSR_CFG_ENUM_UNIT8        enXcposrEnableCfg;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_XCPOSR_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucXcposrRptFlg;                         /* +XCPOSRRPT?????????????????????????????????????????????? */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_SET_XCPOSRRPT_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????????? */
    VOS_UINT8                           ucXcposrRptFlg;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_XCPOSRRPT_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulSensorStat;                              /* Sensor Hub ???? */
}AT_MTA_SET_SENSOR_REQ_STRU;

typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_SENSOR_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucScreenStat;                              /* Screen ???? */
    VOS_UINT8                           aucReserved[3];
}AT_MTA_SET_SCREEN_REQ_STRU;

typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_SCREEN_CNF_STRU;


typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enCfg;                                  /* 0:????,1:???? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
} AT_MTA_SET_RXTESTMODE_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????? */
}MTA_AT_SET_RXTESTMODE_CNF_STRU;

typedef struct
{
    VOS_UINT16                          usCause;
    VOS_UINT16                          usReserved;        /* ?????? */
}MTA_AT_AFC_CLK_UNLOCK_IND_STRU;


typedef struct
{
    VOS_UINT8                           ucGroupID;                             /* ?????? */
    VOS_UINT8                           ucDeviceID;                            /* ?????? */
    VOS_UINT8                           ucCaseID;                              /* ???????????????? */
    VOS_UINT8                           ucMode;                                /* ???????????? */
} MTA_AT_DEVICE_FREQ_STRU;


typedef struct
{
    VOS_UINT8                           ucRptDeviceNum;                                    /* ???????????????????? */
    VOS_UINT8                           aucReserved[3];                                    /* ?????? */
    MTA_AT_DEVICE_FREQ_STRU             astDeviceFreqList[MTA_AT_MAX_BESTFREQ_GROUPNUM];   /* 8?????????????????? */
} MTA_AT_BEST_FREQ_CASE_IND_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????????? */
    VOS_UINT8                           ucActiveDeviceNum;
    VOS_UINT8                           aucReserved[3];
    MTA_AT_DEVICE_FREQ_STRU             astDeviceInfoList[MTA_AT_MAX_BESTFREQ_GROUPNUM];
}MTA_AT_BESTFREQ_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                           ucRatType;                              /*0-GSM 1-WCDMA*/
} AT_MTA_SLAVE_SET_REQ_STRU;

typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT16                          usRfic0DieIdValid;                       /*1-?????? 0-??????*/
    VOS_UINT16                          usRfic1DieIdValid;
    VOS_UINT16                          usRfic2DieIdValid;
    VOS_UINT16                          usRfic3DieIdValid;
    VOS_UINT16                          ausRfic0DieId[MTA_AT_MAX_DIE_ID_LEN];
    VOS_UINT16                          ausRfic1DieId[MTA_AT_MAX_DIE_ID_LEN];
    VOS_UINT16                          ausRfic2DieId[MTA_AT_MAX_DIE_ID_LEN];
    VOS_UINT16                          ausRfic3DieId[MTA_AT_MAX_DIE_ID_LEN];
} MTA_AT_RFIC_DIE_ID_REQ_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usDataValid;
    VOS_UINT16                          usReserved;
    VOS_UINT8                           aucRffeDieId[MTA_AT_MAX_RFFE_DIE_ID_LEN];
} MTA_AT_RffeDieIdValueStru;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;   /* ???????? */
    MTA_AT_RffeDieIdValueStru           astDieIdData[MTA_AT_MAX_RFFE_DIE_ID_COUNT]; /* DieId???? */
} MTA_AT_RffeDieIdReqCnfStru;


typedef struct
{
    VOS_UINT16                          usCmdType;                              /* ???????? */
    VOS_UINT16                          usRatBitmap;                            /* ??????rat????????bitmap */
    VOS_UINT32                          ulPara1;                                /* ????????1 */
    VOS_UINT32                          ulPara2;                                /* ????????2 */
    VOS_UINT32                          ulPara3;                                /* ????????3 */
} AT_MTA_PHY_COM_CFG_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_PHY_COM_CFG_SET_CNF_STRU;


typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enEnable;                               /* 0??????????????1???????????? */
    VOS_UINT8                           aucReserved[3];                         /* ?????? */
}AT_MTA_SET_CRRCONN_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus0;
    VOS_UINT8                           ucStatus1;
    VOS_UINT8                           ucStatus2;
    VOS_UINT8                           ucReserved;                             /* ?????? */
}MTA_AT_CRRCONN_STATUS_IND_STRU;


typedef MTA_AT_RESULT_CNF_STRU MTA_AT_SET_CRRCONN_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_CFG_ENUM_UINT8               enEnable;
    VOS_UINT8                           ucStatus0;
    VOS_UINT8                           ucStatus1;
    VOS_UINT8                           ucStatus2;
} MTA_AT_QRY_CRRCONN_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulEnable;                               /* 0??????????????1???????????? */
    VOS_UINT32                          ulThreshold;                            /* LPDCP???????????? */
}AT_MTA_SET_VTRLQUALRPT_REQ_STRU;


typedef struct
{
    VOS_INT16                           sRsrp;                                  /*RSRP????????*/
    VOS_INT16                           sRsrq;                                  /*RSRQ????????*/
    VOS_INT16                           sRssi;                                  /*RSSI????????*/
    VOS_UINT16                          usBler;                                 /*??????*/
} MTA_AT_RL_QUALITY_INFO_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulCurrBuffTime;                         /*??????????????????*/
    VOS_UINT32                          ulCurrBuffPktNum;                       /*??????????????????*/
    VOS_UINT32                          ulMacUlThrput;                          /*MAC????????,??????????????????????????????????????????:bytes/s*/
    VOS_UINT32                          ulMaxBuffTime;                          /*??????????????????ms*/
}MTA_AT_VIDEO_DIAG_INFO_RPT_STRU;


typedef MTA_AT_RESULT_CNF_STRU MTA_AT_SET_VTRLQUALRPT_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           aucDieSN[MTA_PMU_MAX_DIE_SN_LEN];
} MTA_AT_PMU_DIE_SN_REQ_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulExtendFlag;
    VOS_UINT32                          ulMipiId;
    VOS_UINT32                          ulSlaveId;
    VOS_UINT32                          ulRegAddr;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulByteCnt;
} AT_MTA_MIPI_WREX_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulExtendFlag;
    VOS_UINT32                          ulMipiId;
    VOS_UINT32                          ulSlaveId;
    VOS_UINT32                          ulRegAddr;
    VOS_UINT32                          ulByteCnt;
    VOS_UINT32                          ulSpeedType;
} AT_MTA_MIPI_RDEX_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_MIPI_WREX_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulValue;
} MTA_AT_MIPI_RDEX_CNF_STRU;


typedef struct
{
    AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM_UINT8                 enModemCapUpdateType;   /* MODEM???????????????? */
    VOS_UINT8                                               aucReserved[3];
} AT_MTA_MODEM_CAP_UPDATE_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                               enRslt;                 /* MODEM???????????????? */
} MTA_AT_MODEM_CAP_UPDATE_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucDlCategery;                           /* ????category */
    VOS_UINT8                           ucUlCategery;                           /* ????category */
    VOS_UINT8                           aucReserved[2];                         /* ?????? */
} MTA_AT_LTE_CATEGORY_INFO_IND_STRU;

/*****************************************************************************
  8 UNION????
*****************************************************************************/
/*****************************************************************************
  9 OTHERS????
*****************************************************************************/

/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    AT_MTA_MSG_TYPE_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_MTA_MSG_TYPE_ENUM_UINT32*/
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MTA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_DATA                     stMsgData;
}AtMtaInterface_MSG;


typedef struct
{
    VOS_INT32                           lSec;
    VOS_INT32                           lMin;
    VOS_INT32                           lHour;
    VOS_INT32                           lDay;
    VOS_INT32                           lMonth;
    VOS_INT32                           lYear;
    VOS_INT32                           lZone;
}AT_MTA_MODEM_TIME_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_TIME_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulValue;
}AT_MTA_GNSSNTY_STRU;




typedef struct
{
    VOS_UINT8                           ucDeviceID;      /* ??????????????????ID, 0??????????1-255???????????????? */
    VOS_UINT8                           ucMode;          /* 0??????????????????1???????????????? */
    VOS_UINT8                           aucReserved[2];
}AT_MTA_BESTFREQ_SET_REQ_STRU;


typedef struct
{
    AT_MTA_VMODE_RAT_TYPE_UINT8         enRat;           /* ??????????LTE???? */
    AT_MTA_VMODE_PWMODE_TYPE_UINT8      enMode;          /* 0??????????1???????? */
    VOS_UINT8                           aucRsv[2];
}AT_MTA_VMODE_SET_REQ_STRU;

typedef struct
{
    VOS_UINT8                           aucRsv[4];
}AT_MTA_VMODE_QRY_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_VMODE_PWMODE_TYPE_UINT8      enMode;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_VMODE_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_VMODE_PWMODE_TYPE_UINT8      enMode;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_SET_VMODE_CNF_STRU;



enum MTA_AT_RCM_TAS_TEST_RATMODE_ENUM
{
    MTA_AT_RATMODE_GSM                  = 0,
    MTA_AT_RATMODE_WCDMA                = 1,
    MTA_AT_RATMODE_LTE                  = 2,
    MTA_AT_RATMODE_TDS                  = 3,
    MTA_AT_RATMODE_1X                   = 4,
    MTA_AT_RATMODE_HRPD                 = 5,
    MTA_AT_RATMODE_BUTT
};
typedef VOS_UINT32 MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32;


typedef struct
{
    MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32 enRatMode;                                      /* 1-WCDMA   2-TLE */
    VOS_UINT32                          ulPara0;
    VOS_UINT32                          ulPara1;
    VOS_UINT32                          ulPara2;
    VOS_UINT32                          ulPara3;
} AT_MTA_TAS_TEST_CFG_STRU;


typedef struct
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;                                      /* 1-WCDMA   2-TLE */
} AT_MTA_TAS_TEST_QRY_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_TAS_TEST_CFG_CNF_STRU;


typedef struct
{
    VOS_UINT16                          uhwSrcAntTimeLength;                    /* ??(????)??????????????:ms */
    VOS_UINT16                          uhwDestAntTimeLength;                   /* ??????????????????:ms */
    VOS_INT16                           shwSrcAntTxPowerGain;                   /* ??(????)????????????????????????:0.1dB */
    VOS_INT16                           shwDestAntTxPowerGain;                  /* ????????????????????????????:0.1dB */
}MTA_AT_TX_STATEII_LEVEL_STRU;


typedef struct
{
    VOS_UINT16                          uhwLevelNum;
    VOS_UINT16                          uhwRsv;
    MTA_AT_TX_STATEII_LEVEL_STRU        astLevelItem[MTA_AT_MAX_STATEII_LEVEL_ITEM];
}MTA_AT_TX_STATEII_LEVEL_TABLE_STRU;



typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32               enResult;
    MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32     enRatMode;
    VOS_UINT32                              ulCurrLevel;                        /* ???????????? */
    MTA_AT_TX_STATEII_LEVEL_STRU            stLevelInfo;                        /* ?????????????????? */
    MTA_AT_TX_STATEII_LEVEL_TABLE_STRU      stUsedTable;                        /* ?????? */
}MTA_AT_TAS_TEST_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucPmicId;
    VOS_UINT8                           aucReserved[3];
}AT_MTA_MULTI_PMU_DIE_ID_SET_STRU;


typedef struct
{
    AT_MTA_RS_INFO_TYPE_ENUM_UINT32     enRsInfoType;                           /* 0:????RSRP??1:????RSRQ */
}AT_MTA_RS_INFO_QRY_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulCellId;                               /* ????ID */
    VOS_UINT32                          ulEarfcn;                               /* ???????? */
    VOS_INT32                           lRsrp;                                  /* ??????????????LRRC??100????????AT???????????????? */
}MTA_AT_RSRP_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulCellId;                               /* ????ID */
    VOS_UINT32                          ulEarfcn;                               /* ???????? */
    VOS_INT32                           lRsrq;                                  /* ??????????????LRRC??100????????AT???????????????? */
}MTA_AT_RSRQ_INFO_STRU;


typedef struct
{
    AT_MTA_RS_INFO_TYPE_ENUM_UINT32     enRsInfoType;                           /* 0:????RSRP??1:????RSRQ */
    VOS_UINT32                          ulRsInfoNum;
    union
    {
        MTA_AT_RSRP_INFO_STRU           astRsrpInfo[AT_MAX_RS_INFO_NUM];        /* RSRP???????? */
        MTA_AT_RSRQ_INFO_STRU           astRsrqInfo[AT_MAX_RS_INFO_NUM];        /* RSRQ???????? */
    }u;
}MTA_AT_RS_INFO_RSLT_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_RS_INFO_RSLT_STRU            stRsInfoRslt;
}MTA_AT_RS_INFO_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                             ulErrcCapType;
    VOS_UINT32                             ulPara1;
    VOS_UINT32                             ulPara2;
    VOS_UINT32                             ulPara3;
} AT_MTA_ERRCCAP_CFG_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_ERRCCAP_CFG_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulErrcCapType;
} AT_MTA_ERRCCAP_QRY_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulErrcCapType;
    VOS_UINT32                          ulPara1;
    VOS_UINT32                          ulPara2;
    VOS_UINT32                          ulPara3;
} MTA_AT_ERRCCAP_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_UINT32                                              ulCellId;
    VOS_UINT32                                              ulLac;
    AT_MTA_SYS_MODE_ENUM_UINT32                             enSysmode;
    AT_MTA_PSEUCELL_NOTIFY_TYPE_ENUM_UINT8                  enPseucellNotifyType;   /* 0:????????????????:?????? */
    VOS_UINT8                                               aucReserved[3];
}AT_MTA_PSEUCELL_INFO_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_PSEUCELL_INFO_SET_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_INT16                           sPowerDet;                              /* ??????????????0.1dBm???? */
    VOS_UINT8                           aucReserved1[2];                        /* ?????? */
}MTA_AT_POWER_DET_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usReadType;
    VOS_UINT16                          usMipiId;
    VOS_UINT16                          usSlaveId;
    VOS_UINT16                          usRegAddr;
    VOS_UINT16                          usSpeedType;
    VOS_UINT16                          usReadBitMask;
    VOS_UINT16                          usReserved1;
    VOS_UINT16                          usReserved2;
} AT_MTA_MIPI_READ_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ???????? */
    VOS_UINT32                          ulValue;
}MTA_AT_MIPI_READ_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usWriteType;
    VOS_UINT16                          usMipiId;
    VOS_UINT16                          usSlaveId;
    VOS_UINT16                          usRegAddr;
    VOS_UINT16                          usMipiData;
    VOS_UINT16                          usReserved1;
} AT_MTA_PHY_MIPI_WRITE_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ???????? */
}MTA_AT_PHY_MIPI_WRITE_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulEnableFlag;
} AT_MTA_NO_CARD_MODE_SET_REQ_STRU;

typedef MTA_AT_RESULT_CNF_STRU MTA_AT_NO_CARD_MODE_SET_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulEnableFlag;
} MTA_AT_NO_CARD_MODE_QRY_CNF_STRU;



typedef struct
{
    AT_MTA_CHR_ALARM_RLAT_OP_ENUM_UINT32                    enAlarmOp;
    VOS_UINT32                                              ulAlarmId;
    VOS_UINT32                                              ulAlarmDetail;
}AT_MTA_CHR_ALARM_RLAT_CFG_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                               enResult;
    AT_MTA_CHR_ALARM_RLAT_OP_ENUM_UINT32                    enAlarmOp;
    VOS_UINT32                                              ulAlarmDetail;
}MTA_AT_CHR_ALARM_RLAT_CFG_SET_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usTransactionId;
    VOS_UINT8                           ucMsgBodyType;
    VOS_UINT8                           ucLocSource;
    VOS_UINT8                           ucEndFlag;
    VOS_UINT8                           ucCommonIEValidFlg;
    VOS_UINT8                           ucId;
    VOS_UINT8                           ucLocCalcErr;
    VOS_UINT8                           ucNameLength;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucName[AT_MTA_EPDU_NAME_LENGTH_MAX];
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usEpduLength;
    VOS_UINT8                           aucEpduContent[AT_MTA_EPDU_CONTENT_LENGTH_MAX];
    VOS_UINT8                           aucReserved1[2];
} AT_MTA_EPDU_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_EPDU_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                                  ulFreqBegin;                    /* ????100khz */
    VOS_UINT32                                  ulFreqEnd;                      /* ????100khz */
}AT_MTA_FREQ_RANGE_STRU;


typedef struct
{
    VOS_UINT16                                  usBandInd;                      /* Band:1-255 */
    VOS_UINT8                                   ucReserved;
    VOS_UINT8                                   ucFreqRangeNum;                 /* 0-4,0:??????????????Band???????????????????????? */
    AT_MTA_FREQ_RANGE_STRU                      astFreqRange[AT_MTA_MAX_SUB_BAND_NUM];
}AT_MTA_BAND_INFO_STRU;


typedef struct
{
    VOS_UINT8                                   ucCaA2Flg;                     /* CA A2???????? */
    VOS_UINT8                                   ucCaA4Flg;                     /* CA A4???????? */
    VOS_UINT8                                   ucCaCqiFlg;                    /* CA cqi=0???????? */
    VOS_UINT8                                   aucReserved[3];
    VOS_UINT16                                  usBandNum;                     /* 0-8,0:????????????????CA SCell */
    AT_MTA_BAND_INFO_STRU                       astBandInfo[AT_MTA_MAX_BAND_NUM];
}AT_MTA_CA_INFO_STRU;


typedef struct
{
    VOS_UINT8                                   ucCaActFlag;                    /* ??????????Ca??????0:??????  1:???? */
    VOS_UINT8                                   aucReserved[3];                 /* ?????? */
    AT_MTA_CA_INFO_STRU                         stCaInfo;
}AT_MTA_CA_CFG_SET_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucCellIndex;                            /* ????????, 0: PCell, 1~7: SCell */
    MTA_AT_BAND_WIDTH_ENUM_UINT8        enBandWidth;                            /* SCell???????? */
    VOS_UINT16                          usBandInd;                              /* SCell???? */

    VOS_UINT8                           ucUlConfigured;                         /* CA????????????????0:????????1:?????? */
    VOS_UINT8                           ucDlConfigured;                         /* CA????????????????0:????????1:?????? */
    VOS_UINT8                           ucActived;                              /* SCell????????????0:????????1:???? */
    VOS_UINT8                           ucLaaScellFlg;                          /* ??SCell??????LaaScell, 0:????, 1:?? */

    VOS_UINT32                          ulEarfcn;                               /* SCell???? */
}MTA_AT_CA_CELL_INFO_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ???????? */
    VOS_UINT32                          ulTotalCellNum;                         /* ??????????????Cell?????? */
    MTA_AT_CA_CELL_INFO_STRU            astCellInfo[MTA_AT_CA_MAX_CELL_NUM];    /* ??ulTotalCellNum?????????? */
}MTA_AT_CA_CELL_INFO_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulTotalCellNum;                         /* ??????????????Cell?????? */
    MTA_AT_CA_CELL_INFO_STRU            astCellInfo[MTA_AT_CA_MAX_CELL_NUM];    /* ??ulTotalCellNum?????????? */
}MTA_AT_CA_CELL_INFO_NTF_STRU;


typedef struct
{
    VOS_UINT8                           ucFineTimeType;
    VOS_UINT8                           ucForceFlag;
    VOS_UINT16                          usNum;
    MTA_AT_FINE_TIME_RAT_ENUM_UINT8     enRatMode;                              /* ???????????? */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_FINE_TIME_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_FINE_TIME_SET_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_INT32                           lSinr;                                  /*?????????? */
    VOS_UINT8                           aucUtcTime[MTA_AT_UTC_MAX_LENGTH];      /*(0..549755813887) */
    VOS_UINT8                           aucUtcTimeOffset[MTA_AT_UTC_MAX_LENGTH];/*(0..549755813887) */
    VOS_INT16                           sTa;                                    /*???????????????????? */
    VOS_INT16                           sLeapSecond;                            /*?????????? */
    VOS_UINT8                           ucLeapSecondValid;                      /*???????????????? */
    MTA_AT_FINE_TIME_RAT_ENUM_UINT8     enRat;
    MTA_AT_PROTOCOL_STATE_ENUM_UINT8    enState;                                /*????LRRC???????? */
    VOS_UINT8                           aucReserved[3];
} MTA_AT_SIB_FINE_TIME_IND_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT16                          usSysFn;
    VOS_UINT8                           aucReserved [2];
} MTA_AT_LPP_FINE_TIME_IND_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_CA_CELL_SET_CNF_STRU;


typedef struct
{
   VOS_BOOL                             blEnableType;
} AT_MTA_CA_CELL_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_BOOL                            blEnableType;
} MTA_AT_CA_CELL_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulCmdType;
    VOS_UINT32                          ulPara1;
    VOS_UINT32                          ulPara2;
    VOS_UINT32                          ulPara3;
}AT_MTA_L2_COM_CFG_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_L2_COM_CFG_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulCmdType;
}AT_MTA_L2_COM_CFG_QRY_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulCmdType;
    VOS_UINT32                          ulPara1;
    VOS_UINT32                          ulPara2;
    VOS_UINT32                          ulPara3;
}MTA_AT_L2_COM_CFG_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulAckType;                              /* ACK???? */
    VOS_UINT32                          ulAckValue1;                            /* ACK??1 */
    VOS_UINT32                          ulAckValue2;                            /* ACK??2 */
    VOS_UINT32                          ulAckValue3;                            /* ACK??3 */
}MTA_AT_PHY_COMM_ACK_IND_STRU;


typedef struct
{
   AT_MTA_SMS_DOMAIN_ENUM_UINT8         enSmsDomain;
   VOS_UINT8                            aucReserved[3];
} AT_MTA_SMS_DOMAIN_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SMS_DOMAIN_SET_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_SMS_DOMAIN_ENUM_UINT8        enSmsDomain;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_SMS_DOMAIN_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucEpsNetwork[MTA_AT_EPS_NETWORK_BYTE];
    VOS_UINT8                           ucReserved;
}MTA_AT_EPS_NETWORK_INFO_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_EPS_NETWORK_INFO_STRU        stEpsNetworkInfo;
}MTA_AT_EPS_NETWORK_QRY_CNF_STRU;


typedef struct
{
   VOS_UINT32                            ulLocationPermitFlag;
} AT_MTA_GPSLOCSET_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_GPSLOCSET_SET_CNF_STRU;



typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    TIME_ZONE_TIME_STRU                 stTime;
}MTA_AT_CCLK_QRY_CNF_STRU;



typedef struct
{
    VOS_INT32                          lTempResult;
}MTA_AT_TEMP_PROTECT_IND_STRU;



typedef struct
{
   AT_MTA_NV_REFRESH_REASON_ENUM_UINT8  enReason;
   VOS_UINT8                            aucReserved[3];
} AT_MTA_NV_REFRESH_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_NV_REFRESH_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32           ulPseudBtsType;
}MTA_AT_PSEUD_BTS_IDENT_IND_STRU;


typedef struct
{
    VOS_UINT16                          usNum;                                  /* ?????????????? */
    VOS_UINT8                           aucRsv[2];

}AT_MTA_SET_FORCESYNC_REQ_STRU;


typedef struct
{
    VOS_UINT32                          ulResult;                                 /* ???????? */
}MTA_AT_SET_FORCESYNC_CNF_STRU;

/*****************************************************************************
??????    : AT_MTA_LTEPWRDISS_SET_REQ_STRU
????????  : AT??MTA????LTEPWRDISS??????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucReserved;
    VOS_INT16                           sPara;
}AT_MTA_LTEPWRDISS_SET_REQ_STRU;

/*****************************************************************************
??????    : AT_MTA_LTEPWRDISS_SET_CNF_STRU
????????  : MTA??AT????LTEPWRDISS??????????????????
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}AT_MTA_LTEPWRDISS_SET_CNF_STRU;


typedef struct
{
    AT_MTA_DCXO_SAMPLE_TYPE_ENUM_UINT16  enDcxoSampleType;                      /* DCXO_SAMPLE???????? */
    VOS_UINT8                            aucRsv[2];
}AT_MTA_DCXO_SAMPE_QRY_REQ_STRU;

/*****************************************************************************
 ??????    : UCOM_NV_DCXO_SAMPLE_STRU
 ????????  :
 ASN.1???? :
 ????????  : ????????DCXO????
*****************************************************************************/
typedef struct
{
    VOS_INT32                   swTime      :24;                                /* ??????????2016.4????????1604,????1604?????????????? */
    VOS_INT32                   swMode      :8;                                 /* ????????4bit??modem_id,??4bit????????0:G??1:U??2:L??3:TD??4:1X??5:EVDO */
    VOS_INT32                   swTemp;                                         /* ??????Boston????????0.001?? */
    VOS_INT32                   swPpm;                                          /* ????????????????2^31/10^6 */
}MTA_AT_DCXO_SAMPLE_STRU;

/*****************************************************************************
 ??????    : UCOM_NV_XO_INIT_FREQUENCY_STRU
 ????????  :
 ASN.1???? :
 ????????  :2.2????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_INT32                           swInitFrequency;                        /* ??????????????????????????????????2^31/10^6*/
    VOS_INT32                           swInitTemperature;                      /* ????????????????????????????0.001?? */
}MTA_AT_XO_INIT_FREQUENCY_STRU;


typedef union
{
    MTA_AT_DCXO_SAMPLE_STRU                      astSample[UCOM_NV_DCXO_SAMPLE_H_MAX_NUM]; /*????????????????*/
    MTA_AT_XO_INIT_FREQUENCY_STRU                stDcxoInitPpm;            /*????????????*/
}MTA_AT_DCXO_SECTION_DATA_UNION_STRU;


typedef struct
{
    AT_MTA_DCXO_SAMPLE_TYPE_ENUM_UINT16           enDcxoSampleType;                      /* DCXO_SAMPLE???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_ENUM_UINT16         enResult;
    MTA_AT_DCXO_SECTION_DATA_UNION_STRU           stSctionData;                     /*??????????????????????*/
}MTA_AT_DCXO_SAMPE_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulBandCnt;                                 /* ???? */
    VOS_UINT16                          ausBandInfo[AT_MTA_UECAP_MAX_NR_BAND_NUM]; /* Band???? */
}MTA_NRRC_BAND_INFO_STRU;


typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpare1            :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}AT_WCDMA_PREF_BAND_STRU;


typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare7      :23;

}AT_GSM_PREF_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulBand;
    AT_WCDMA_PREF_BAND_STRU             BitBand;
}AT_WCDMA_BAND_SET_UN;


typedef union
{
    VOS_UINT32                          ulBand;
    AT_GSM_PREF_BAND_STRU               BitBand;
}AT_GSM_BAND_SET_UN;



typedef struct
{
    VOS_UINT32                          ulUeGSptBand;
    VOS_UINT32                          ulUeWSptBand;
    VOS_UINT32                          ulAllUeBand;
    AT_WCDMA_BAND_SET_UN                unWRFSptBand;
    AT_GSM_BAND_SET_UN                  unGRFSptBand;
    MTA_NRRC_BAND_INFO_STRU             stNrBand;
}AT_UE_BAND_CAPA_ST;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_UE_BAND_CAPA_ST                  stBandFeature;
}MTA_AT_SFEATURE_QRY_CNF_STRU;

#if (FEATURE_ON == FEATURE_UE_MODE_NR)

typedef struct
{
    VOS_UINT32                             ulNrrcCfgNetMode;
    VOS_UINT32                             aulPara[AT_MTA_NRRCCAP_PARA_MAX_NUM];
} AT_MTA_NRRCCAP_CFG_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_NRRCCAP_CFG_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulNrrcCfgNetMode;
} AT_MTA_NRRCCAP_QRY_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulNrrcCfgNetMode;
    VOS_UINT32                          aulPara[AT_MTA_NRRCCAP_PARA_MAX_NUM];
} MTA_AT_NRRCCAP_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucReserved;
    VOS_INT16                           sPara;
}AT_MTA_NRPWRCTRL_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
}MTA_AT_NRPWRCTRL_SET_CNF_STRU;

#endif


typedef struct
{
    VOS_UINT16                          usUlMcs[MTA_AT_MAX_CODE_NUMBER];
    VOS_UINT16                          usDlMcs[MTA_AT_MAX_CODE_NUMBER];
}AT_LTE_MCS_INFO_STRU;


typedef struct
{
    MTA_AT_UL_MODE_ENUM_UINT32          enUlMode;
    /* NR??????MCS???????????????????????????????? 3GPP TS38.214 5.1.3.1 6.1.4.1*/
    MTA_AT_INDEX_TABLE_ENUM_UINT8       enUlMcsTable;
    MTA_AT_INDEX_TABLE_ENUM_UINT8       enSulMcsTable;
    MTA_AT_INDEX_TABLE_ENUM_UINT8       enDlMcsTable;
    VOS_UINT8                           usRsv;
    VOS_UINT16                          usUlMcs[MTA_AT_MAX_CODE_NUMBER];
    VOS_UINT16                          usSulMcs[MTA_AT_MAX_CODE_NUMBER];
    VOS_UINT16                          usDlMcs[MTA_AT_MAX_CODE_NUMBER];
}AT_NR_MCS_INFO_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_RESULT_TYPE_ENUM_UINT8       enResultType;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usNrCellNum;
    AT_LTE_MCS_INFO_STRU                stLteMcsInfo;
    AT_NR_MCS_INFO_STRU                 astNrMcsInfo[MTA_AT_MAX_CC_NUMBER];
}MTA_AT_MCS_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulUlFreq;
    VOS_UINT32                          ulUlEarfcn;
    VOS_UINT32                          ulUlBandWidth;
    VOS_UINT32                          ulDlFreq;
    VOS_UINT32                          ulDlEarfcn;
    VOS_UINT32                          ulDlBandWidth;
    VOS_UINT16                          usBand;
    VOS_UINT8                           aucRsv[2];
}AT_LTE_HFREQ_INFO_STRU;


typedef struct
{
    MTA_AT_UL_MODE_ENUM_UINT32          enUlMode;
    VOS_UINT32                          ulUlFreq;
    VOS_UINT32                          ulUlNarfcn;
    VOS_UINT32                          ulUlBandWidth;
    VOS_UINT32                          ulSulFreq;
    VOS_UINT32                          ulSulNarfcn;
    VOS_UINT32                          ulSulBandWidth;
    VOS_UINT32                          ulDlFreq;
    VOS_UINT32                          ulDlNarfcn;
    VOS_UINT32                          ulDlBandWidth;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usSulBand;
}AT_NR_HFREQ_INFO_STRU;

typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_RESULT_TYPE_ENUM_UINT8       enResultType;
    VOS_UINT8                           ucIsreportFlg;
    VOS_UINT16                          usNrCellNum;
    AT_LTE_HFREQ_INFO_STRU              stLteHfreqInfo;
    AT_NR_HFREQ_INFO_STRU               astNrHfreqInfo[MTA_AT_MAX_CC_NUMBER];
}MTA_AT_HFREQINFO_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_RESULT_TYPE_ENUM_UINT8       enResultType;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usNrCellNum;
    AT_LTE_HFREQ_INFO_STRU              stLteHfreqInfo;
    AT_NR_HFREQ_INFO_STRU               astNrHfreqInfo[MTA_AT_MAX_CC_NUMBER];
}MTA_AT_HFREQINFO_IND_STRU;


typedef struct
{
    VOS_INT16                           sGuTxPwr;
    VOS_INT16                           sPuschPwr;
    VOS_INT16                           sPucchPwr;
    VOS_INT16                           sSrsPwr;
    VOS_INT16                           sPrachPwr;
    VOS_UINT8                           aucRsv[2];
}AT_TXPOWER_INFO_STRU;


typedef struct
{
    MTA_AT_UL_MODE_ENUM_UINT32          enUlMode;
    VOS_UINT32                          ulUlFreq;        /* ????????????UL???????? */
    VOS_INT16                           sUlPuschPwr;
    VOS_INT16                           sUlPucchPwr;
    VOS_INT16                           sUlSrsPwr;
    VOS_INT16                           sUlPrachPwr;
    VOS_UINT32                          ulSulFreq;     /* SUL????????????SUL???????? */
    VOS_INT16                           sSulPuschPwr;
    VOS_INT16                           sSulPucchPwr;
    VOS_INT16                           sSulSrsPwr;
    VOS_INT16                           sSulPrachPwr;
}AT_NTXPOWER_INFO_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_TXPOWER_INFO_STRU                stTxpwrInfo;
}MTA_AT_TXPOWER_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT16                          usNrCellNum;
    VOS_UINT8                           aucRsv[2];
    AT_NTXPOWER_INFO_STRU               astNrTxPwrInfo[MTA_AT_MAX_CC_NUMBER];
}MTA_AT_NTXPOWER_QRY_CNF_STRU;


typedef struct
{
    AT_MTA_NSSAI_SET_TYPE_ENUM_UINT32   enSNssaiSetType;
    PS_CONFIGURED_NSSAI_STRU            st5gNssai;
}AT_MTA_5G_NSSAI_SET_REQ_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_5G_NSSAI_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPlmn            :1;
    VOS_UINT32                          bitOpSpare           :31;
    PS_NR_PLMN_ID_STRU                  stPlmn;
    AT_MTA_NSSAI_QRY_TYPE_ENUM_UINT32   enSNssaiQryType;
}AT_MTA_5G_NSSAI_QRY_REQ_STRU;


typedef struct
{
    PS_NR_PLMN_ID_STRU                                  stPlmnId;
    PS_ALLOW_NSSAI_STRU                                 stAllowNssai;
    PS_CONFIGURED_NSSAI_STRU                            stCfgNssai;
} MTA_AT_5G_ALLOWED_AND_CFG_NSSAI_WITH_PLMN_ID_STRU;


typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    MTA_AT_5G_ALLOWED_AND_CFG_NSSAI_WITH_PLMN_ID_STRU       astNssai[MTA_AT_MAX_ALLOWED_AND_CFG_NSSAI_PLMN_NUM];
} MTA_AT_5G_ALLOWED_AND_CFG_NSSAI_QRY_CNF_STRU;


typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                                enResult;
    AT_MTA_NSSAI_QRY_TYPE_ENUM_UINT32                        enSNssaiQryType;
    PS_CONFIGURED_NSSAI_STRU                                 st5gDefCfgNssai;   /* default config nssai */
    PS_CONFIGURED_NSSAI_STRU                                 st5gPreferNssai;   /* prefer nssai */
    PS_REJECTED_NSSAI_INFO_STRU                              st5gRejNssai;      /* reject nssai */
    MTA_AT_5G_ALLOWED_AND_CFG_NSSAI_QRY_CNF_STRU             st5gAllowCfgNssai; /* allow????cfg nssai */
} MTA_AT_5G_NSSAI_QRY_CNF_STRU;

/*****************************************************************************
  10 ????????
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

