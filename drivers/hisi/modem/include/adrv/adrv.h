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


#ifndef HISI_AP_DRV_H
#define HISI_AP_DRV_H
#include <linux/module.h>
/*************************************************************************
*
*   ????/????/????/????
*
*************************************************************************/

#define PARTITION_MODEM_IMAGE_NAME       "modem"
#define PARTITION_MODEM_DSP_NAME         "modem_dsp"
#define PARTITION_MODEM_NVDLOAD_NAME     "modemnvm_update"
#define PARTITION_MODEM_NVDLOAD_CUST_NAME "modemnvm_cust"
#define PARTITION_MODEM_NVDEFAULT_NAME   "modemnvm_factory"
#define PARTITION_MODEM_NVBACKUP_NAME    "modemnvm_backup"
#define PARTITION_MODEM_NVSYS_NAME       "modemnvm_system"
#define PARTITION_MODEM_NVIMG_NAME       "modemnvm_img"
#define PARTITION_MODEM_NVPATCH_NAME     "modem_patch_nv"
#define PARTITION_MODEM_LOG_NAME         "modem_om"
#define PARTITION_MODEM_DTB_NAME	 "modem_dtb"
#define PARTITION_PTN_VRL_P_NAME 	 "vrl"
#define PARTITION_PTN_VRL_M_NAME	 "vrl_backup"

#define BSP_RESET_NOTIFY_REPLY_OK 		   0
#define BSP_RESET_NOTIFY_SEND_FAILED      -1
#define BSP_RESET_NOTIFY_TIMEOUT          -2

typedef enum
{
	BSP_START_MODE_CHARGING = 0,
	BSP_START_MODE_NORMAL,
	BSP_START_MODE_UPDATE,
	BSP_START_MODE_BUILT
} BSP_START_MODE_E;

typedef enum {
	BSP_CCORE = 0,
	BSP_HIFI,
	BSP_BBE,
	BSP_CDSP,
	BSP_CCORE_TAS,
	BSP_CCORE_WAS,
	BSP_CCORE_CAS,
	BSP_BUTT
} BSP_CORE_TYPE_E;

/*****************************************************************************
* ?? ?? ??  : flash_find_ptn
*
* ????????  : ??????????????????????
*
* ????????  : str ??????
*
* ????????  : ??
*
* ?? ?? ??  : 0 ???? -1 ????
*
* ????????  : kernel
*
*****************************************************************************/
int flash_find_ptn(const char* str, char* pblkname);

/*****************************************************************************
* ?? ?? ??  : bsp_need_loadmodem
*
* ????????  : ????????????????modem
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : 1 ????????
			  0 ??????????
*
* ????????  : kernel
*
*****************************************************************************/
int bsp_need_loadmodem(void);

/*****************************************************************************
* ?? ?? ??  : bsp_reset_loadimage
*
* ????????  : Modem??HIFI ????????
*
* ????????  : ecoretype ??BSP_CORE_TYPE_E
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int bsp_reset_loadimage (BSP_CORE_TYPE_E ecoretype);

/*
 * Function name:bsp_reset_core_notify.
 * Description:notify the remote processor MODEM is going to reset.
 * Parameters:
 *      @ ecoretype: the core to be notified.
 *      @ cmdtype: to send to remote processor.
 *      @ timeout_ms: max time to wait, ms.
 *      @ retval: the ack's value get from the remote processor.
 *Called in:
 *      @ modem is going to reset. <reset_balong.c>
 *Return value:
 *      @ BSP_RESET_NOTIFY_REPLY_OK-->the remote processor give response in time.
 *      @ BSP_RESET_NOTIFY_SEND_FAILED-->the parameter is wrong or other rproc_sync_send's self error.
 *      @ BSP_RESET_NOTIFY_TIMEOUT-->after wait timeout_ms's time, the remote processor give no response.
*/
int bsp_reset_core_notify(BSP_CORE_TYPE_E ecoretype, unsigned int cmdtype, unsigned int timeout_ms, unsigned int *retval);



/*************************************************************************
*
*   RDR/Coresight
*
*************************************************************************/

#define STR_EXCEPTIONDESC_MAXLEN	48

/*??AP ????????????????????????????????AP????*/
typedef enum
{
    CP_S_MODEMDMSS     = 0x70,
    CP_S_MODEMNOC      = 0x71,
    CP_S_MODEMAP       = 0x72,
    CP_S_EXCEPTION     = 0x73,
    CP_S_RESETFAIL     = 0x74,
    CP_S_NORMALRESET   = 0x75,
    CP_S_RILD_EXCEPTION= 0x76,
    CP_S_3RD_EXCEPTION = 0x77,
    CP_S_DRV_EXC       = 0x78,
    CP_S_PAM_EXC       = 0x79,
    CP_S_GUAS_EXC      = 0x7a,
    CP_S_CTTF_EXC      = 0x7b,
    CP_S_CAS_CPROC_EXC = 0x7c,
    CP_S_GUDSP_EXC     = 0x7d,
    CP_S_TLPS_EXC      = 0x7e,
    CP_S_TLDSP_EXC     = 0x7f,
    CP_S_CPHY_EXC      = 0x80,
    CP_S_GUCNAS_EXC    = 0x81,
} EXCH_SOURCE;

struct list_head_rdr {
	struct list_head_rdr *next, *prev;
};
typedef void (*rdr_e_callback)(unsigned int, void*);

/*
 *   struct list_head_rdr   e_list;
 *   u32 modid,			    exception id;
 *		if modid equal 0, will auto generation modid, and return it.
 *   u32 modid_end,		    can register modid region. [modid~modid_end];
		need modid_end >= modid,
 *		if modid_end equal 0, will be register modid only,
		but modid & modid_end cant equal 0 at the same time.
 *   u32 process_priority,	exception process priority
 *   u32 reboot_priority,	exception reboot priority
 *   u64 save_log_mask,		need save log mask
 *   u64 notify_core_mask,	need notify other core mask
 *   u64 reset_core_mask,	need reset other core mask
 *   u64 from_core,		    the core of happen exception
 *   u32 reentrant,		    whether to allow exception reentrant
 *   u32 exce_type,		    the type of exception
 *   char* from_module,		    the module of happen excption
 *   char* desc,		        the desc of happen excption
 *   rdr_e_callback callback,	will be called when excption has processed.
 *   u32 reserve_u32;		reserve u32
 *   void* reserve_p		    reserve void *
 */
struct rdr_exception_info_s {
	struct list_head_rdr e_list;	/*list_head_rdr instead of list_head  to solve the confliction between <linux/types.h>*/
	unsigned int	e_modid;
	unsigned int	e_modid_end;
	unsigned int	e_process_priority;
	unsigned int	e_reboot_priority;
	unsigned long long	e_notify_core_mask;
	unsigned long long	e_reset_core_mask;
	unsigned long long	e_from_core;
	unsigned int	e_reentrant;
	unsigned int    e_exce_type;
	unsigned int    e_exce_subtype;
	unsigned int    e_upload_flag;
	unsigned char	e_from_module[MODULE_NAME_LEN];
	unsigned char	e_desc[STR_EXCEPTIONDESC_MAXLEN];
	unsigned int	e_reserve_u32;
	void*	e_reserve_p;
	rdr_e_callback e_callback;
};

enum UPLOAD_FLAG {
    RDR_UPLOAD_YES = 0xff00fa00,
    RDR_UPLOAD_NO
};
enum REENTRANT {
    RDR_REENTRANT_ALLOW = 0xff00da00,
    RDR_REENTRANT_DISALLOW
};

enum REBOOT_PRI {
    RDR_REBOOT_NOW      = 0x01,
    RDR_REBOOT_WAIT,
    RDR_REBOOT_NO,
    RDR_REBOOT_MAX
};
enum CORE_LIST {
    RDR_AP      = 0x1,
    RDR_CP      = 0x2,
    RDR_HIFI    = 0x8,
    RDR_LPM3    = 0x10,
    RDR_MODEMAP = 0x200,
};
enum PROCESS_PRI {
    RDR_ERR      = 0x01,
    RDR_WARN,
    RDR_OTHER,
    RDR_PPRI_MAX
};


typedef void (*pfn_cb_dump_done)(unsigned int modid, unsigned long long coreid);
typedef void (*pfn_dump)(unsigned int modid, unsigned int etype, unsigned long long coreid, char* logpath, pfn_cb_dump_done fndone);
typedef void (*pfn_reset)(unsigned int modid, unsigned int etype, unsigned long long coreid);

struct rdr_module_ops_pub {
    pfn_dump    ops_dump;
    pfn_reset   ops_reset;
};

struct rdr_register_module_result {
    unsigned long long   log_addr;
    unsigned int         log_len;
    unsigned long long   nve;
};


#ifdef CONFIG_HISI_BB
/*****************************************************************************
* ?? ?? ??  : rdr_register_exception
*
* ????????  : RDR????????????
*
* ????????  : rdr_exception_info_s
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  >0 e_modid_end
*
* ????????  : kernel
*
*****************************************************************************/
unsigned int rdr_register_exception (struct rdr_exception_info_s* e);

/*****************************************************************************
* ?? ?? ??  : rdr_register_module_ops
*
* ????????  : ????????????????
*
* ????????  : coreid  ??????ID
			  ops     ??????????????reset????
*             retinfo ????????????
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int rdr_register_module_ops(unsigned long long coreid, struct rdr_module_ops_pub* ops, struct rdr_register_module_result* retinfo);


/*****************************************************************************
* ?? ?? ??  : rdr_system_error
*
* ????????  : ??????????????????????????????????????????????????
*
* ????????  :
*
* ????????  : ??
*
* ?? ?? ??  : ??
*
* ????????  : kernel
*
*****************************************************************************/
void rdr_system_error(unsigned int modid, unsigned int arg1, unsigned int arg2);
#else
static inline u32 rdr_register_exception(struct rdr_exception_info_s* e){ return 0;}
static inline int rdr_register_module_ops(unsigned long long coreid, struct rdr_module_ops_pub* ops,
				struct rdr_register_module_result* retinfo){ return -1; }
static inline void rdr_system_error(unsigned int modid, unsigned int arg1, unsigned int arg2) {}
#endif

/*****************************************************************************
* ?? ?? ??  : rdr_syserr_process_for_ap
*
* ????????  : ??????????rdr??????????????????????????????????????log??reset??????????????AP??????
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : ??
*
* ????????  : kernel
*
*****************************************************************************/
void rdr_syserr_process_for_ap(unsigned int modid, unsigned long long arg1, unsigned long long arg2);

/*************************************************************************
*
*   eFuse
*
*************************************************************************/

/*****************************************************************************
* ?? ?? ??  : get_efuse_dieid_value
*
* ????????  : ????die id ????
*
* ????????  : u32Length ????????????????????????????4??????
			  timeout   ????????
*
* ????????  : pu8Buffer ????????efuse????
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int get_efuse_dieid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);

/*****************************************************************************
* ?? ?? ??  : get_efuse_chipid_value
*
* ????????  : ????chip id ????
*
* ????????  : u32Length ????????????????????????????4??????
			  timeout   ????????
*
* ????????  : pu8Buffer ????????efuse????
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int get_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);

/*****************************************************************************
* ?? ?? ??  : get_efuse_kce_value
*
* ????????  : ????kce????
*
* ????????  : u32Length ????????????????????????????4??????
			  timeout   ????????
*
* ????????  : pu8Buffer ????????efuse????
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int get_efuse_kce_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);

/*****************************************************************************
* ?? ?? ??  : set_efuse_kce_value
*
* ????????  : ????kce????
*
* ????????  : pu8Buffer ????????efuse????
			  u32Length ????????????????????????????4??????
			  timeout   ????????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int set_efuse_kce_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);

/*
 * FUNC DESCRIPTION: get_efuse_avs_value
 *
 * INPUT PARAMETERS:
 *   unsigned char *buf;     store the avs efuse read value
 *   unsigned int  size;     defined in bytes, and requires a minimum of 1 byte
 *   unsigned int  timeout;  overrun time, usually 1000 ms, 0 means waiting unless
 *                           the func finish your request successfully.
 *
 * OUTPUT PARAMETERS:
 *    buf            is updated
 *
 * RETURN VALUE:
 *    The func returns 0 if it finish your request successfully,
 *    otherwise, it returns less than 0 which means an error has occurred.
 */
int get_efuse_avs_value(unsigned char *buf, unsigned int size, unsigned int timeout);

/*************************************************************************
*
*   USB
*
*************************************************************************/
typedef void (*USB_ENABLE_CB_T)(void);
typedef void (*USB_DISABLE_CB_T)(void);

/*****************************************************************************
* ?? ?? ??  : bsp_acm_open
*
* ????????  : ????????
*
* ????????  : dev_id ????????????id
*
* ????????  : ??
*
* ?? ?? ??  : ??0 ??????handle
			  NULL ????
*
* ????????  : kernel
*
*****************************************************************************/
void *bsp_acm_open(unsigned int dev_id);

/*****************************************************************************
* ?? ?? ??  : bsp_acm_close
*
* ????????  : ????????
*
* ????????  : ????????????handle
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int bsp_acm_close(void *handle);

/*****************************************************************************
* ?? ?? ??  : bsp_acm_write
*
* ????????  : ??????
*
* ????????  : handle ????handle
			  buf  ????????????
			  size ????????????????
*
* ????????  : ??
*
* ?? ?? ??  : >0  ??????????????????
			  <=0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int bsp_acm_write(void *handle, void *buf, unsigned int size);

/*****************************************************************************
* ?? ?? ??  : bsp_acm_read
*
* ????????  : ??????
*
* ????????  : handle ????handle
			  size ????????????????
*
* ????????  : buf  ????????????
*
* ?? ?? ??  : >0  ??????????????????
			  <=0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int bsp_acm_read(void *handle, void *buf, unsigned int size);

/*****************************************************************************
* ?? ?? ??  : bsp_acm_ioctl
*
* ????????  : ??????????????????
*
* ????????  : handle ????handle
			  cmd ??????
			  para ????????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int bsp_acm_ioctl(void *handle, unsigned int cmd, void *para);

/*****************************************************************************
* ?? ?? ??  : BSP_USB_RegUdiEnableCB
*
* ????????  : ????usb????????????
*
* ????????  : pFunc ????????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
unsigned int BSP_USB_RegUdiEnableCB(USB_ENABLE_CB_T pFunc);

/*****************************************************************************
* ?? ?? ??  : BSP_USB_RegUdiDisableCB
*
* ????????  : ????usb????????????
*
* ????????  : pFunc ????????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
unsigned int BSP_USB_RegUdiDisableCB(USB_DISABLE_CB_T pFunc);

/*************************************************************************
*
*   PMU
*
*************************************************************************/


typedef  void   (*PMU_OCP_CALLBACK)( const char * name);
/*****************************************************************************
* ?? ?? ??  : BSP_USB_RegUdiDisableCB
*
* ????????  : ????usb????????????
*
* ????????  : name OCP??????????????????pmu_mntn DTS????
			  pFunc
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
			  <0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int pmu_ocp_event_reg (const char * name, PMU_OCP_CALLBACK pFunc);

enum EDITION_KIND{
    EDITION_USER            = 1,
    EDITION_INTERNAL_BETA   = 2,
    EDITION_OVERSEA_BETA    = 3,
    EDITION_MAX
};
#ifdef CONFIG_HISI_BB
/*
 * func name: bbox_check_edition
 * func args:
 *   void
 * return:
 *   unsigned int:	return edition information
 *				0x01		User
 *				0x02		Internal BETA
 *				0x03		Oversea BETA
 */
unsigned int bbox_check_edition(void);
#else
static inline unsigned int bbox_check_edition(void){return EDITION_USER;}
#endif

/* hisi_pmic_special_ocp_register????????????????  */


#ifdef CONFIG_DRM_DRIVER
int atfd_hisi_service_access_register_smc(unsigned long long main_fun_id, 
                                          unsigned long long buff_addr_phy, 
                                          unsigned long long data_len, 
                                          unsigned long long sub_fun_id);
#else
static inline int atfd_hisi_service_access_register_smc(unsigned long long main_fun_id,
                                          unsigned long long buff_addr_phy,
                                          unsigned long long data_len,
                                          unsigned long long sub_fun_id){return 0;}
#endif

void ipf_get_waking_pkt(void* data, unsigned int len);

/*****************************************************************************
* function     : get_kernel_build_time
* description  : get build date and build time of kernel
* input        : builddate: buffer for get build date
*                dtlen    : length of builddate buffer
*                buildtime: buffer for get build time
*                tmlen    : length of buildtime buffer
* output       : builddate : kernel build date string
*                buildtime : kernel build time string
* ret value  : 0  successfull
*               <0  failed to get date&time
*****************************************************************************/
int get_kernel_build_time(char* builddate, int dtlen, char* buildtime, int tmlen);


/********sim hotplug start************/
/*
status=1 means plug out;
status=0 means plug in;
*/
#define STATUS_PLUG_IN 0
#define STATUS_PLUG_OUT 1

#define MODULE_SD  0
#define MODULE_SIM  1

/*****************************************************************************
* function     : get_sd2jtag_status
* description  : get sd2jtag status
* input        : void
* output       : void
* ret value  : true -- sd2jtag enabled
*                  false -- sd2jtag disabled
*****************************************************************************/
int get_sd2jtag_status(void);

/*****************************************************************************
* function     : get_card1_type
* description  : get card1 type
* input        : void
* output       : void
* ret value  : STATUS_SIM, STATUS_SD, STATUS_NO_CARD, STATUS_SD2JTAG
*****************************************************************************/
u8 get_card1_type(void);

/*****************************************************************************
* function     : sd_sim_detect_run
* description  : run sd sim detect action
* input        : dw_mci_host      mci_host
                    status                in or out
                    current_module  sim or sd
                    need_sleep        true or false
* output       : void
* ret value  : STATUS_PLUG_IN, STATUS_PLUG_OUT
*****************************************************************************/
int sd_sim_detect_run(void *dw_mci_host, int status, int current_module, int need_sleep);

/*****************************************************************************
* function     : hisi_pmic_reg_read
* description  : read pmic register
* input        : addr      pmic register addr
* output       : void
* ret value  : value of addr
*****************************************************************************/
unsigned int hisi_pmic_reg_read(int addr);

/*****************************************************************************
* function     : hisi_pmic_reg_write
* description  : pmic reg write
* input        : addr      pmic register addr
                    val        value to write
* ret value  : void
*****************************************************************************/
void hisi_pmic_reg_write(int addr, int val);

/********sim hotplug end************/

/********kirin pcie start************/
enum kirin_pcie_trigger {
	KIRIN_PCIE_TRIGGER_CALLBACK,
	KIRIN_PCIE_TRIGGER_COMPLETION,
};

enum kirin_pcie_event {
	KIRIN_PCIE_EVENT_MIN_INVALID = 0x0,		/*min invalid value*/
	KIRIN_PCIE_EVENT_LINKUP = 0x1,		/* linkup event  */
	KIRIN_PCIE_EVENT_LINKDOWN = 0x2,		/* linkdown event */
	KIRIN_PCIE_EVENT_WAKE = 0x4,	/* wake event*/
	KIRIN_PCIE_EVENT_L1SS = 0x8,	/* l1ss event*/
	KIRIN_PCIE_EVENT_CPL_TIMEOUT = 0x10,	/* completion timeout event */
	KIRIN_PCIE_EVENT_MAX_INVALID = 0x1F,	/* max invalid value*/
};

struct kirin_pcie_notify {
	enum kirin_pcie_event event;
	void *user;
	void *data;
	u32 options;
};

struct kirin_pcie_register_event {
	u32 events;
	void *user;
	enum kirin_pcie_trigger mode;
	void (*callback)(struct kirin_pcie_notify *notify);
	struct kirin_pcie_notify notify;
	struct completion *completion;
	u32 options;
};

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_register_event
*
* ????????  : EP register hook fun for link event notification
*
* ????????  : reg register_event
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_register_event(struct kirin_pcie_register_event *reg);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_deregister_event
*
* ????????  : EP deregister hook fun for link event notification
*
* ????????  : reg register_event
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_deregister_event(struct kirin_pcie_register_event *reg);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_pm_control
*
* ????????  : ep????rc????????
*
* ????????  : power_ops 0---PowerOff normally
*                       1---Poweron normally
*                       2---PowerOFF without PME
*                       3---Poweron without LINK
*             rc_idx ep??????rc??????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_pm_control(int power_ops, u32 rc_idx);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_ep_off
*
* ????????  : ????ep????????????????
*
* ????????  : rc_idx ep??????rc??????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ??????
*             1  ??????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_ep_off(u32 rc_idx);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_lp_ctrl
*
* ????????  : ??????????????????
*
* ????????  : rc_idx ep??????rc??????
*             enable 0---????
*                    1---????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_lp_ctrl(u32 rc_idx, u32 enable);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_enumerate
*
* ????????  : pcie????????
*
* ????????  : rc_idx ep??????rc??????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_enumerate(u32 rc_idx);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_remove_ep
*
* ????????  : pcie????ep????????
*
* ????????  : rc_idx ep??????rc??????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_remove_ep(u32 rc_idx);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_rescan_ep
*
* ????????  : pcie????ep????????
*
* ????????  : rc_idx ep??????rc??????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_rescan_ep(u32 rc_idx);

/*****************************************************************************
* ?? ?? ??  : pcie_ep_link_ltssm_notify
*
* ????????  : ????ep????link????????
*
* ????????  : rc_id ep??????rc??????
*             link_status ep????link????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int pcie_ep_link_ltssm_notify(u32 rc_id, u32 link_status);

/*****************************************************************************
* ?? ?? ??  : kirin_pcie_power_notifiy_register
*
* ????????  : ????pcie??????????????ep????
*
* ????????  : rc_id ep??????rc??????
*             poweron ep????????????
*             poweroff ep????????????
*             data ep????????????
*
* ????????  : ??
*
* ?? ?? ??  : 0  ????????
*             ??0 ????????
*
* ????????  : kernel
*
*****************************************************************************/
int kirin_pcie_power_notifiy_register(u32 rc_id, int (*poweron)(void* data),
				int (*poweroff)(void* data), void* data);

/********kirin pcie end************/

/*****************************************************************************
* ?? ?? ??  : get_cmd_product_id
*
* ????????  : ??kernel??cmdline??????product id
*
* ????????  : ??
*
* ????????  : ??
*
* ?? ?? ??  : 32bit????????????0xFFFFFFFF  ????????
*             0xFFFFFFFF ????????
*
* ????????  : kernel
*
*****************************************************************************/
unsigned int get_cmd_product_id(void);

/******************* modem temp start *************/
struct mdm_adc_s {
    unsigned int channel;
    unsigned int mode;
};
extern int hisi_mdm_adc_get_value_register(int (*func)(struct mdm_adc_s *mdm_adc_para));
/******************* modem temp end ****************/


/******************* hisi cpufreq req start *************/
struct cpufreq_req {
	struct notifier_block nb;
	int cpu;
	unsigned int freq;
};

#ifdef CONFIG_HISI_CPUFREQ_DT
/*****************************************************************************
 Description: initlize struct cpufreq, register cpufreq call chain
	      notifier block
 Input:       req: a struct cpufreq_req instance
              cpu: the cpu for which we request frequency
 Return:      zero for SUCCESS, non-zero for FAIL
*****************************************************************************/
extern int hisi_cpufreq_init_req(struct cpufreq_req *req, int cpu);

/*****************************************************************************
 Description: update request frequency and trigger a cpufreq scaling
 Input:       req: a struct cpufreq_req instance
              cpu: new request frequency
 Return:      NA
*****************************************************************************/
extern void hisi_cpufreq_update_req(struct cpufreq_req *req,
				    unsigned int freq);
#else
static inline int hisi_cpufreq_init_req(struct cpufreq_req *req, int cpu)
{
	return 0;
}

static inline void hisi_cpufreq_update_req(struct cpufreq_req *req,
					   unsigned int freq)
{
}
#endif
/******************* hisi cpufreq req end *************/

/******************* hisi core ctl req start *************/
#ifdef CONFIG_HISI_CORE_CTRL
/*****************************************************************************
 Description: disable big cluster isolation for a while
 Input:       timeout: the duration we expect for disabling big
		       cluster isolation
 Return:      NA
*****************************************************************************/
extern void core_ctl_set_boost(unsigned int timeout);
#else
static inline void core_ctl_set_boost(unsigned int timeout) {}
#endif
/******************* hisi core ctl req end *************/

/******************* A+B modem connect with hub by ap ctrl *************/
struct hw_ap_cp_route_t {
	unsigned int channel_id;
	int (*icc_open)(unsigned int channel_id, void *read_cb);
	int (*icc_read)(unsigned int channel_id, unsigned char *pdata, int size);
	int (*icc_write)(unsigned int channel_id, unsigned char *pdata, int size);
};
#ifdef CONFIG_INPUTHUB_20
void connect_pcie_icc_sensorhub_route(struct hw_ap_cp_route_t *ap_cp_route);
#else
static inline void connect_pcie_icc_sensorhub_route
	(struct hw_ap_cp_route_t *ap_cp_route)
{
}
#endif
/******************* A+B modem connect with hub by ap ctrl *************/

/* hifi reset notify modem */
enum DRV_RESET_CALLCBFUN_MOMENT {
	DRV_RESET_CALLCBFUN_RESET_BEFORE,
	DRV_RESET_CALLCBFUN_RESET_AFTER,
	DRV_RESET_CALLCBFUN_RESETING,
	DRV_RESET_CALLCBFUN_MOEMENT_INVALID
};
typedef int (*hifi_reset_cbfunc)(enum DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);

#ifdef CONFIG_HISI_HIFI_BB
int hifireset_regcbfunc(const char *pname, hifi_reset_cbfunc pcbfun, int userdata, int priolevel);
#else
static inline int hifireset_regcbfunc(const char *pname, hifi_reset_cbfunc pcbfun, int userdata, int priolevel)
{
	return 0;
}
#endif

#endif /* HISI_AP_DRV_H */


