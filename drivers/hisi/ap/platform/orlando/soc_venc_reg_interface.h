#ifndef __SOC_VENC_REG_INTERFACE_H__
#define __SOC_VENC_REG_INTERFACE_H__ 
typedef union {
    struct {
        unsigned int vcpi_enable_ve_eop : 1 ;
        unsigned int vcpi_enable_vedu_slice_end : 1 ;
        unsigned int vcpi_enable_ve_buffull : 1 ;
        unsigned int vcpi_enable_ve_pbitsover : 1 ;
        unsigned int vcpi_enable_vedu_brkpt : 1 ;
        unsigned int vcpi_enable_vedu_step : 1 ;
        unsigned int vcpi_enable_vedu_timeout : 1 ;
        unsigned int vcpi_enable_cfg_err : 1 ;
        unsigned int Reserved_0 : 24 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_INTMASK;
typedef union {
    struct {
        unsigned int vcpi_clr_ve_eop : 1 ;
        unsigned int vcpi_clr_vedu_slice_end : 1 ;
        unsigned int vcpi_clr_ve_buffull : 1 ;
        unsigned int vcpi_clr_ve_pbitsover : 1 ;
        unsigned int vcpi_clr_vedu_brkpt : 1 ;
        unsigned int vcpi_clr_vedu_step : 1 ;
        unsigned int vcpi_clr_vedu_timeout : 1 ;
        unsigned int vcpi_clr_cfg_err : 1 ;
        unsigned int Reserved_1 : 24 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_INTCLR;
typedef union {
    struct {
        unsigned int vcpi_vstart : 1 ;
        unsigned int Reserved_3 : 15 ;
        unsigned int vcpi_vstep : 1 ;
        unsigned int Reserved_2 : 15 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_START;
typedef union {
    struct {
        unsigned int vcpi_cnt_clr : 1 ;
        unsigned int vctrl_cnt_clr : 1 ;
        unsigned int curld_cnt_clr : 1 ;
        unsigned int pme_cnt_clr : 1 ;
        unsigned int refld_cnt_clr : 1 ;
        unsigned int ime_cnt_clr : 1 ;
        unsigned int pintra_cnt_clr : 1 ;
        unsigned int mrg_cnt_clr : 1 ;
        unsigned int fme_cnt_clr : 1 ;
        unsigned int intra_cnt_clr : 1 ;
        unsigned int pmv_cnt_clr : 1 ;
        unsigned int tqitq_cnt_clr : 1 ;
        unsigned int sel_cnt_clr : 1 ;
        unsigned int dblk_cnt_clr : 1 ;
        unsigned int sao_cnt_clr : 1 ;
        unsigned int pack_cnt_clr : 1 ;
        unsigned int cabac_cnt_clr : 1 ;
        unsigned int pmeld_cnt_clr : 1 ;
        unsigned int pmest_cnt_clr : 1 ;
        unsigned int nbi_cnt_clr : 1 ;
        unsigned int lfldst_cnt_clr : 1 ;
        unsigned int recst_cnt_clr : 1 ;
        unsigned int csst_cnt_clr : 1 ;
        unsigned int qpg_cnt_clr : 1 ;
        unsigned int Reserved_4 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_CNTCLR;
typedef union {
    struct {
        unsigned int vcpi_bp_lcu_x : 9 ;
        unsigned int Reserved_6 : 7 ;
        unsigned int vcpi_bp_lcu_y : 9 ;
        unsigned int Reserved_5 : 5 ;
        unsigned int vcpi_bkp_en : 1 ;
        unsigned int vcpi_dbgmod : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_BP_POS;
typedef union {
    struct {
        unsigned int vcpi_vedsel : 1 ;
        unsigned int vcpi_lcu_time_sel : 1 ;
        unsigned int vcpi_protocol : 2 ;
        unsigned int vcpi_cfg_mode : 1 ;
        unsigned int vcpi_slice_int_en : 1 ;
        unsigned int vcpi_sao_luma : 1 ;
        unsigned int vcpi_sao_chroma : 1 ;
        unsigned int vcpi_rec_cmp_en : 1 ;
        unsigned int vcpi_img_improve_en : 1 ;
        unsigned int vcpi_frame_type : 2 ;
        unsigned int vcpi_entropy_mode : 1 ;
        unsigned int Reserved_10 : 1 ;
        unsigned int vcpi_ref_num : 1 ;
        unsigned int vcpi_pmv_mvstat_en : 1 ;
        unsigned int vcpi_idr_pic : 1 ;
        unsigned int vcpi_pskip_en : 1 ;
        unsigned int vcpi_trans_mode : 2 ;
        unsigned int Reserved_8 : 1 ;
        unsigned int vcpi_sobel_weight_en : 1 ;
        unsigned int Reserved_7 : 4 ;
        unsigned int vcpi_lcu_size : 2 ;
        unsigned int vcpi_time_en : 2 ;
        unsigned int vcpi_ref_cmp_en : 1 ;
        unsigned int vcpi_refc_nload : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_MODE;
typedef union {
    struct {
        unsigned int vcpi_tile_width : 9 ;
        unsigned int Reserved_12 : 7 ;
        unsigned int vcpi_tile_height : 9 ;
        unsigned int Reserved_11 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_TILE_SIZE;
typedef union {
    struct {
        unsigned int vcpi_imgwidth_pix : 13 ;
        unsigned int Reserved_14 : 3 ;
        unsigned int vcpi_imgheight_pix : 13 ;
        unsigned int Reserved_13 : 3 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_PICSIZE_PIX;
typedef union {
    struct {
        unsigned int vcpi_slice_size : 16 ;
        unsigned int vcpi_slcspilt_mod : 1 ;
        unsigned int vcpi_multislc_en : 1 ;
        unsigned int Reserved_15 : 14 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_MULTISLC;
typedef union {
    struct {
        unsigned int vcpi_cr_qp_offset : 5 ;
        unsigned int vcpi_cb_qp_offset : 5 ;
        unsigned int vcpi_frm_qp : 6 ;
        unsigned int Reserved_18 : 1 ;
        unsigned int Reserved_17 : 1 ;
        unsigned int vcpi_intra_det_qp_en : 1 ;
        unsigned int vcpi_rc_cu_madi_en : 1 ;
        unsigned int Reserved_16 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_QPCFG;
typedef union {
    struct {
        unsigned int vcpi_dblk_beta : 4 ;
        unsigned int vcpi_dblk_alpha : 4 ;
        unsigned int vcpi_dblk_filter_flag : 2 ;
        unsigned int Reserved_19 : 22 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_DBLKCFG;
typedef union {
    struct {
        unsigned int vcpi_intra_lowpow_en : 1 ;
        unsigned int vcpi_fme_lowpow_en : 1 ;
        unsigned int vcpi_ime_lowpow_en : 1 ;
        unsigned int vcpi_force_intra_lowpwr_en : 1 ;
        unsigned int vcpi_ddr_cross_idx : 11 ;
        unsigned int Reserved_22 : 1 ;
        unsigned int vcpi_tqitq_gtck_en : 1 ;
        unsigned int vcpi_mrg_gtck_en : 1 ;
        unsigned int vcpi_fme_gtck_en : 1 ;
        unsigned int vcpi_clkgate_en : 2 ;
        unsigned int vcpi_mem_clkgate_en : 1 ;
        unsigned int Reserved_21 : 1 ;
        unsigned int vcpi_ddr_cross_en : 1 ;
        unsigned int Reserved_20 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_LOW_POWER;
typedef union {
    struct {
        unsigned int vcpi_r_outstanding : 7 ;
        unsigned int Reserved_24 : 1 ;
        unsigned int vcpi_w_outstanding : 4 ;
        unsigned int Reserved_23 : 20 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_OUTSTD;
typedef union {
    struct {
        unsigned int vcpi_tmv_wr_rd_avail : 2 ;
        unsigned int Reserved_25 : 30 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_TMV_LOAD;
typedef union {
    struct {
        unsigned int vcpi_cross_slice : 1 ;
        unsigned int vcpi_cross_tile : 1 ;
        unsigned int Reserved_26 : 30 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_CROSS_TILE_SLC;
typedef union {
    struct {
        unsigned int vcpi_ema : 3 ;
        unsigned int vcpi_emaw : 2 ;
        unsigned int vcpi_emaa : 3 ;
        unsigned int vcpi_emab : 3 ;
        unsigned int Reserved_27 : 21 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_MEM_CTRL;
typedef union {
    struct {
        unsigned int vcpi_intra_cu_en : 3 ;
        unsigned int Reserved_31 : 1 ;
        unsigned int vcpi_ipcm_en : 1 ;
        unsigned int vcpi_intra_h264_cutdiag : 1 ;
        unsigned int Reserved_30 : 1 ;
        unsigned int Reserved_29 : 1 ;
        unsigned int vcpi_fme_cu_en : 4 ;
        unsigned int vcpi_mrg_cu_en : 4 ;
        unsigned int Reserved_28 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_INTRA_INTER_CU_EN;
typedef union {
    struct {
        unsigned int vcpi_ref_idc : 2 ;
        unsigned int Reserved_34 : 2 ;
        unsigned int vcpi_cabac_init_idc : 2 ;
        unsigned int Reserved_33 : 6 ;
        unsigned int vcpi_byte_stuffing : 1 ;
        unsigned int Reserved_32 : 19 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_VLC_CONFIG;
typedef union {
    struct {
        unsigned int vcpi_iblk_pre_en : 1 ;
        unsigned int vcpi_pblk_pre_en : 1 ;
        unsigned int vcpi_force_inter : 1 ;
        unsigned int vcpi_pintra_inter_flag_disable : 1 ;
        unsigned int vcpi_ext_edge_en : 1 ;
        unsigned int Reserved_35 : 27 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_PRE_JUDGE_EXT_EN;
typedef union {
    struct {
        unsigned int vcpi_iblk_pre_cost_thr : 16 ;
        unsigned int vcpi_pblk_pre_cost_thr : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_PRE_JUDGE_COST_THR;
typedef union {
    struct {
        unsigned int vcpi_iblk_pre_mv_dif_thr0 : 8 ;
        unsigned int vcpi_iblk_pre_mv_dif_thr1 : 8 ;
        unsigned int vcpi_iblk_pre_mvx_thr : 8 ;
        unsigned int vcpi_iblk_pre_mvy_thr : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_IBLK_PRE_MV_THR;
typedef union {
    struct {
        unsigned int Reserved_37 : 1 ;
        unsigned int vcpi_move_sad_en : 1 ;
        unsigned int Reserved_36 : 14 ;
        unsigned int vcpi_pblk_pre_mvx_thr : 8 ;
        unsigned int vcpi_pblk_pre_mvy_thr : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_PME_PARAM;
typedef union {
    struct {
        unsigned int vcpi_skin_en : 1 ;
        unsigned int vcpi_strong_edge_en : 1 ;
        unsigned int vcpi_still_en : 1 ;
        unsigned int vcpi_skin_close_angle : 1 ;
        unsigned int vcpi_rounding_sobel_en : 1 ;
        unsigned int Reserved_38 : 27 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_PIC_STRONG_EN;
typedef union {
    struct {
        unsigned int Reserved_40 : 1 ;
        unsigned int vcpi_col_from_l0_flag : 1 ;
        unsigned int vcpi_curr_ref_long_flag : 2 ;
        unsigned int vcpi_col_long_flag : 2 ;
        unsigned int Reserved_39 : 26 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REF_FLAG;
typedef union {
    struct {
        unsigned int vcpi_rc_cu_qp_en : 1 ;
        unsigned int vcpi_rc_row_qp_en : 1 ;
        unsigned int vcpi_move_scene_en : 1 ;
        unsigned int Reserved_46 : 1 ;
        unsigned int vcpi_strong_edge_move_en : 1 ;
        unsigned int Reserved_45 : 1 ;
        unsigned int Reserved_44 : 2 ;
        unsigned int vcpi_rc_low_luma_en : 1 ;
        unsigned int vcpi_rc_h264_smooth_mb_en : 1 ;
        unsigned int vcpi_rd_smooth_mb_en : 1 ;
        unsigned int vcpi_rd_min_sad_flag_en : 1 ;
        unsigned int vcpi_wr_min_sad_flag_en : 1 ;
        unsigned int vcpi_high_min_sad_en : 1 ;
        unsigned int vcpi_low_min_sad_en : 1 ;
        unsigned int vcpi_prev_min_sad_en : 1 ;
        unsigned int Reserved_43 : 1 ;
        unsigned int Reserved_42 : 1 ;
        unsigned int vcpi_flat_region_en : 1 ;
        unsigned int Reserved_41 : 13 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_RC_ENABLE;
typedef union {
    struct {
        unsigned int vcpi_insert_i_slc_idx : 8 ;
        unsigned int vcpi_insert_i_slc_en : 1 ;
        unsigned int Reserved_47 : 23 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_I_SLC_INSERT;
typedef union {
    struct {
        unsigned int vcpi_clkdiv_en : 1 ;
        unsigned int Reserved_49 : 15 ;
        unsigned int vcpi_down_freq_en : 1 ;
        unsigned int Reserved_48 : 15 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_CLKDIV_ENABLE;
typedef union {
    struct {
        unsigned int vcpi_nbist_bypass : 1 ;
        unsigned int vcpi_pmest_bypass : 1 ;
        unsigned int vcpi_recyh_bypass : 1 ;
        unsigned int vcpi_recch_bypass : 1 ;
        unsigned int vcpi_recy_bypass : 1 ;
        unsigned int vcpi_recc_bypass : 1 ;
        unsigned int vcpi_pmeinfost_bypass : 1 ;
        unsigned int vcpi_strm_bypass : 1 ;
        unsigned int Reserved_50 : 24 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_WCHN_BYPASS;
typedef union {
    struct {
        unsigned int vcpi_nbild_bypass : 1 ;
        unsigned int vcpi_pmeld_bypass : 1 ;
        unsigned int vcpi_refyh_bypass : 1 ;
        unsigned int vcpi_refch_bypass : 1 ;
        unsigned int vcpi_refy_bypass : 1 ;
        unsigned int vcpi_refc_bypass : 1 ;
        unsigned int vcpi_pmeinfold0_bypass : 1 ;
        unsigned int vcpi_pmeinfold1_bypass : 1 ;
        unsigned int vcpi_srcy_bypass : 1 ;
        unsigned int vcpi_srcu_bypass : 1 ;
        unsigned int vcpi_srcv_bypass : 1 ;
        unsigned int Reserved_51 : 21 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_RCHN_BYPASS;
typedef union {
    struct {
        unsigned int vcpi_sw_l0_width : 7 ;
        unsigned int Reserved_53 : 9 ;
        unsigned int vcpi_sw_l0_height : 6 ;
        unsigned int Reserved_52 : 10 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_SW_L0_SIZE;
typedef union {
    struct {
        unsigned int vcpi_sw_l1_width : 7 ;
        unsigned int Reserved_55 : 9 ;
        unsigned int vcpi_sw_l1_height : 6 ;
        unsigned int Reserved_54 : 10 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_SW_L1_SIZE;
typedef union {
    struct {
        unsigned int vcpi_curld_c_stride : 16 ;
        unsigned int vcpi_curld_y_stride : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_recst_ystride : 16 ;
        unsigned int vcpi_recst_cstride : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REC_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_recst_head_stride : 16 ;
        unsigned int Reserved_56 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REC_HEAD_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_refc_l0_stride : 16 ;
        unsigned int vcpi_refy_l0_stride : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REF_L0_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_refch_l0_stride : 16 ;
        unsigned int vcpi_refyh_l0_stride : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REFH_L0_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_refc_l1_stride : 16 ;
        unsigned int vcpi_refy_l1_stride : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REF_L1_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_refch_l1_stride : 16 ;
        unsigned int vcpi_refyh_l1_stride : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_REFH_L1_STRIDE;
typedef union {
    struct {
        unsigned int vcpi_crop_en : 1 ;
        unsigned int vcpi_scale_en : 1 ;
        unsigned int vcpi_store_mode : 1 ;
        unsigned int vcpi_blk_type : 3 ;
        unsigned int vcpi_str_fmt : 4 ;
        unsigned int Reserved_59 : 4 ;
        unsigned int vcpi_recst_disable : 1 ;
        unsigned int Reserved_58 : 1 ;
        unsigned int vcpi_package_sel : 4 ;
        unsigned int Reserved_57 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_STRFMT;
typedef union {
    struct {
        unsigned int vcpi_xscale : 16 ;
        unsigned int vcpi_yscale : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_SCALE_PARA;
typedef union {
    struct {
        unsigned int vcpi_oriwidth_pix : 13 ;
        unsigned int Reserved_61 : 3 ;
        unsigned int vcpi_oriheight_pix : 13 ;
        unsigned int Reserved_60 : 3 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_ORI_PICSIZE;
typedef union {
    struct {
        unsigned int vcpi_enable_ve_eop_s : 1 ;
        unsigned int vcpi_enable_vedu_slice_end_s : 1 ;
        unsigned int vcpi_enable_ve_buffull_s : 1 ;
        unsigned int vcpi_enable_ve_pbitsover_s : 1 ;
        unsigned int vcpi_enable_vedu_brkpt_s : 1 ;
        unsigned int vcpi_enable_vedu_step_s : 1 ;
        unsigned int vcpi_enable_vedu_timeout_s : 1 ;
        unsigned int vcpi_enable_cfg_err_s : 1 ;
        unsigned int Reserved_62 : 24 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_INTMASK_S;
typedef union {
    struct {
        unsigned int vcpi_clr_ve_eop_s : 1 ;
        unsigned int vcpi_clr_vedu_slice_end_s : 1 ;
        unsigned int vcpi_clr_ve_buffull_s : 1 ;
        unsigned int vcpi_clr_ve_pbitsover_s : 1 ;
        unsigned int vcpi_clr_vedu_brkpt_s : 1 ;
        unsigned int vcpi_clr_vedu_step_s : 1 ;
        unsigned int vcpi_clr_vedu_timeout_s : 1 ;
        unsigned int vcpi_clr_cfg_err_s : 1 ;
        unsigned int Reserved_63 : 24 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCPI_INTCLR_S;
typedef union {
    struct {
        unsigned int curld_narrow_luma_min : 8 ;
        unsigned int curld_narrow_luma_max : 8 ;
        unsigned int curld_narrow_chrm_min : 8 ;
        unsigned int curld_narrow_chrm_max : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_CURLD_NARROW_THR;
typedef union {
    struct {
        unsigned int vcpi_coef_g2y : 15 ;
        unsigned int Reserved_66 : 1 ;
        unsigned int vcpi_coef_r2y : 15 ;
        unsigned int Reserved_65 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER0;
typedef union {
    struct {
        unsigned int vcpi_coef_r2cb : 15 ;
        unsigned int Reserved_68 : 1 ;
        unsigned int vcpi_coef_b2y : 15 ;
        unsigned int Reserved_67 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER1;
typedef union {
    struct {
        unsigned int vcpi_coef_b2cb : 15 ;
        unsigned int Reserved_70 : 1 ;
        unsigned int vcpi_coef_g2cb : 15 ;
        unsigned int Reserved_69 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER2;
typedef union {
    struct {
        unsigned int vcpi_coef_g2cr : 15 ;
        unsigned int Reserved_72 : 1 ;
        unsigned int vcpi_coef_r2cr : 15 ;
        unsigned int Reserved_71 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER3;
typedef union {
    struct {
        unsigned int vcpi_coef_b2cr : 15 ;
        unsigned int Reserved_73 : 17 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER4;
typedef union {
    struct {
        unsigned int vcpi_coef_rgb_rndy : 16 ;
        unsigned int vcpi_coef_rgb_shift : 4 ;
        unsigned int Reserved_74 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER5;
typedef union {
    struct {
        unsigned int vcpi_coef_rgb_rndcr : 16 ;
        unsigned int vcpi_coef_rgb_rndcb : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_ARGBTO444_PARAMETER6;
typedef union {
    struct {
        unsigned int vcpi_coef_hcoef0 : 4 ;
        unsigned int vcpi_coef_hcoef1 : 4 ;
        unsigned int vcpi_coef_hcoef2 : 4 ;
        unsigned int vcpi_coef_hcoef3 : 4 ;
        unsigned int vcpi_coef_hrnd : 4 ;
        unsigned int vcpi_coef_hshift : 3 ;
        unsigned int Reserved_75 : 9 ;
    } bits;
    unsigned int u32;
} U_VEDU_444TO422_PARAMETER;
typedef union {
    struct {
        unsigned int vcpi_coef_vcoef0 : 4 ;
        unsigned int vcpi_coef_vcoef1 : 4 ;
        unsigned int vcpi_coef_vcoef2 : 4 ;
        unsigned int vcpi_coef_vcoef3 : 4 ;
        unsigned int vcpi_coef_vrnd : 4 ;
        unsigned int vcpi_coef_vshift : 3 ;
        unsigned int Reserved_76 : 9 ;
    } bits;
    unsigned int u32;
} U_VEDU_422TO420_PARAMETER;
typedef union {
    struct {
        unsigned int vctrl_region0en : 1 ;
        unsigned int vctrl_region1en : 1 ;
        unsigned int vctrl_region2en : 1 ;
        unsigned int vctrl_region3en : 1 ;
        unsigned int vctrl_region4en : 1 ;
        unsigned int vctrl_region5en : 1 ;
        unsigned int vctrl_region6en : 1 ;
        unsigned int vctrl_region7en : 1 ;
        unsigned int vctrl_absqp0 : 1 ;
        unsigned int vctrl_absqp1 : 1 ;
        unsigned int vctrl_absqp2 : 1 ;
        unsigned int vctrl_absqp3 : 1 ;
        unsigned int vctrl_absqp4 : 1 ;
        unsigned int vctrl_absqp5 : 1 ;
        unsigned int vctrl_absqp6 : 1 ;
        unsigned int vctrl_absqp7 : 1 ;
        unsigned int vctrl_region0keep : 1 ;
        unsigned int vctrl_region1keep : 1 ;
        unsigned int vctrl_region2keep : 1 ;
        unsigned int vctrl_region3keep : 1 ;
        unsigned int vctrl_region4keep : 1 ;
        unsigned int vctrl_region5keep : 1 ;
        unsigned int vctrl_region6keep : 1 ;
        unsigned int vctrl_region7keep : 1 ;
        unsigned int vctrl_roi_en : 1 ;
        unsigned int Reserved_79 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_CFG0;
typedef union {
    struct {
        unsigned int vctrl_roiqp0 : 7 ;
        unsigned int Reserved_83 : 1 ;
        unsigned int vctrl_roiqp1 : 7 ;
        unsigned int Reserved_82 : 1 ;
        unsigned int vctrl_roiqp2 : 7 ;
        unsigned int Reserved_81 : 1 ;
        unsigned int vctrl_roiqp3 : 7 ;
        unsigned int Reserved_80 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_CFG1;
typedef union {
    struct {
        unsigned int vctrl_roiqp4 : 7 ;
        unsigned int Reserved_87 : 1 ;
        unsigned int vctrl_roiqp5 : 7 ;
        unsigned int Reserved_86 : 1 ;
        unsigned int vctrl_roiqp6 : 7 ;
        unsigned int Reserved_85 : 1 ;
        unsigned int vctrl_roiqp7 : 7 ;
        unsigned int Reserved_84 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_CFG2;
typedef union {
    struct {
        unsigned int vctrl_size0_roiwidth : 10 ;
        unsigned int Reserved_89 : 6 ;
        unsigned int vctrl_size0_roiheight : 10 ;
        unsigned int Reserved_88 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_0;
typedef union {
    struct {
        unsigned int vctrl_size1_roiwidth : 10 ;
        unsigned int Reserved_91 : 6 ;
        unsigned int vctrl_size1_roiheight : 10 ;
        unsigned int Reserved_90 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_1;
typedef union {
    struct {
        unsigned int vctrl_size2_roiwidth : 10 ;
        unsigned int Reserved_93 : 6 ;
        unsigned int vctrl_size2_roiheight : 10 ;
        unsigned int Reserved_92 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_2;
typedef union {
    struct {
        unsigned int vctrl_size3_roiwidth : 10 ;
        unsigned int Reserved_95 : 6 ;
        unsigned int vctrl_size3_roiheight : 10 ;
        unsigned int Reserved_94 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_3;
typedef union {
    struct {
        unsigned int vctrl_size4_roiwidth : 10 ;
        unsigned int Reserved_97 : 6 ;
        unsigned int vctrl_size4_roiheight : 10 ;
        unsigned int Reserved_96 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_4;
typedef union {
    struct {
        unsigned int vctrl_size5_roiwidth : 10 ;
        unsigned int Reserved_99 : 6 ;
        unsigned int vctrl_size5_roiheight : 10 ;
        unsigned int Reserved_98 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_5;
typedef union {
    struct {
        unsigned int vctrl_size6_roiwidth : 10 ;
        unsigned int Reserved_101 : 6 ;
        unsigned int vctrl_size6_roiheight : 10 ;
        unsigned int Reserved_100 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_6;
typedef union {
    struct {
        unsigned int vctrl_size7_roiwidth : 10 ;
        unsigned int Reserved_103 : 6 ;
        unsigned int vctrl_size7_roiheight : 10 ;
        unsigned int Reserved_102 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_SIZE_7;
typedef union {
    struct {
        unsigned int vctrl_start0_roistartx : 9 ;
        unsigned int Reserved_105 : 7 ;
        unsigned int vctrl_start0_roistarty : 9 ;
        unsigned int Reserved_104 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_0;
typedef union {
    struct {
        unsigned int vctrl_start1_roistartx : 9 ;
        unsigned int Reserved_107 : 7 ;
        unsigned int vctrl_start1_roistarty : 9 ;
        unsigned int Reserved_106 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_1;
typedef union {
    struct {
        unsigned int vctrl_start2_roistartx : 9 ;
        unsigned int Reserved_109 : 7 ;
        unsigned int vctrl_start2_roistarty : 9 ;
        unsigned int Reserved_108 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_2;
typedef union {
    struct {
        unsigned int vctrl_start3_roistartx : 9 ;
        unsigned int Reserved_111 : 7 ;
        unsigned int vctrl_start3_roistarty : 9 ;
        unsigned int Reserved_110 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_3;
typedef union {
    struct {
        unsigned int vctrl_start4_roistartx : 9 ;
        unsigned int Reserved_113 : 7 ;
        unsigned int vctrl_start4_roistarty : 9 ;
        unsigned int Reserved_112 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_4;
typedef union {
    struct {
        unsigned int vctrl_start5_roistartx : 9 ;
        unsigned int Reserved_115 : 7 ;
        unsigned int vctrl_start5_roistarty : 9 ;
        unsigned int Reserved_114 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_5;
typedef union {
    struct {
        unsigned int vctrl_start6_roistartx : 9 ;
        unsigned int Reserved_117 : 7 ;
        unsigned int vctrl_start6_roistarty : 9 ;
        unsigned int Reserved_116 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_6;
typedef union {
    struct {
        unsigned int vctrl_start7_roistartx : 9 ;
        unsigned int Reserved_119 : 7 ;
        unsigned int vctrl_start7_roistarty : 9 ;
        unsigned int Reserved_118 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_ROI_START_7;
typedef union {
    struct {
        unsigned int vctrl_lcu_target_bit : 20 ;
        unsigned int Reserved_120 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_LCU_TARGET_BIT;
typedef union {
    struct {
        unsigned int vctrl_narrow_tile_width : 4 ;
        unsigned int Reserved_121 : 28 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_NARROW_THRESHOLD;
typedef union {
    struct {
        unsigned int vctrl_lcu_performance_baseline : 16 ;
        unsigned int Reserved_122 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_LCU_BASELINE;
typedef union {
    struct {
        unsigned int vctrl_norm16_coeff_protect_num : 8 ;
        unsigned int Reserved_126 : 8 ;
        unsigned int vctrl_norm16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_125 : 3 ;
        unsigned int vctrl_roundingoffset16x16 : 4 ;
        unsigned int Reserved_124 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_NORM_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingmechanism : 3 ;
        unsigned int vctrl_roundingdegreethresh : 7 ;
        unsigned int vctrl_roundingforcezeroresidthresh : 3 ;
        unsigned int Reserved_129 : 5 ;
        unsigned int vctrl_roundingac16sum : 4 ;
        unsigned int Reserved_128 : 4 ;
        unsigned int vctrl_roundinglowfreqacblk16 : 4 ;
        unsigned int Reserved_127 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_NORM_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_norm_isolate_ac_enable : 1 ;
        unsigned int vctrl_norm_force_zero_cnt : 3 ;
        unsigned int Reserved_131 : 11 ;
        unsigned int vctrl_norm_engsum_16 : 6 ;
        unsigned int vctrl_norm_engcnt_16 : 5 ;
        unsigned int Reserved_130 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_NORM_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_skin16_coeff_protect_num : 8 ;
        unsigned int Reserved_135 : 8 ;
        unsigned int vctrl_skin16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_134 : 3 ;
        unsigned int vctrl_roundingskinoffset16x16 : 4 ;
        unsigned int Reserved_133 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SKIN_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingskinmechanism : 3 ;
        unsigned int vctrl_roundingskindegreethresh : 7 ;
        unsigned int vctrl_roundingskinforcezeroresidthresh : 3 ;
        unsigned int Reserved_138 : 5 ;
        unsigned int vctrl_roundingskinac16sum : 4 ;
        unsigned int Reserved_137 : 4 ;
        unsigned int vctrl_roundingskinlowfreqacblk16 : 4 ;
        unsigned int Reserved_136 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SKIN_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_skin_isolate_ac_enable : 1 ;
        unsigned int vctrl_skin_force_zero_cnt : 3 ;
        unsigned int Reserved_140 : 11 ;
        unsigned int vctrl_skin_engsum_16 : 6 ;
        unsigned int vctrl_skin_engcnt_16 : 5 ;
        unsigned int Reserved_139 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SKIN_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_hedge16_coeff_protect_num : 8 ;
        unsigned int Reserved_144 : 8 ;
        unsigned int vctrl_hedge16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_143 : 3 ;
        unsigned int vctrl_roundingedgeoffset16x16 : 4 ;
        unsigned int Reserved_142 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_HEDGE_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingedgemechanism : 3 ;
        unsigned int vctrl_roundingedgedegreethresh : 7 ;
        unsigned int vctrl_roundingedgeforcezeroresidthresh : 3 ;
        unsigned int Reserved_147 : 5 ;
        unsigned int vctrl_roundingedgeac16sum : 4 ;
        unsigned int Reserved_146 : 4 ;
        unsigned int vctrl_roundingedgelowfreqacblk16 : 4 ;
        unsigned int Reserved_145 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_HEDGE_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_stredge_isolate_ac_enable : 1 ;
        unsigned int vctrl_stredge_force_zero_cnt : 3 ;
        unsigned int Reserved_149 : 11 ;
        unsigned int vctrl_stredge_engsum_16 : 6 ;
        unsigned int vctrl_stredge_engcnt_16 : 5 ;
        unsigned int Reserved_148 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_HEDGE_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_edgemov16_coeff_protect_num : 8 ;
        unsigned int Reserved_153 : 8 ;
        unsigned int vctrl_edgemov16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_152 : 3 ;
        unsigned int vctrl_roundingedgemovoffset16x16 : 4 ;
        unsigned int Reserved_151 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_HEDGEMOV_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingedgemovmechanism : 3 ;
        unsigned int vctrl_roundingedgemovdegreethresh : 7 ;
        unsigned int vctrl_roundingedgemovforcezeroresidthresh : 3 ;
        unsigned int Reserved_156 : 5 ;
        unsigned int vctrl_roundingedgemovac16sum : 4 ;
        unsigned int Reserved_155 : 4 ;
        unsigned int vctrl_roundingedgemovlowfreqacblk16 : 4 ;
        unsigned int Reserved_154 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_HEDGEMOV_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_edgemov_isolate_ac_enable : 1 ;
        unsigned int vctrl_edgemov_force_zero_cnt : 3 ;
        unsigned int Reserved_158 : 11 ;
        unsigned int vctrl_edgemov_engsum_16 : 6 ;
        unsigned int vctrl_edgemov_engcnt_16 : 5 ;
        unsigned int Reserved_157 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_HEDGEMOV_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_static16_coeff_protect_num : 8 ;
        unsigned int Reserved_162 : 8 ;
        unsigned int vctrl_static16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_161 : 3 ;
        unsigned int vctrl_roundingstilloffset16x16 : 4 ;
        unsigned int Reserved_160 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_STATIC_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingstillmechanism : 3 ;
        unsigned int vctrl_roundingstilldegreethresh : 7 ;
        unsigned int vctrl_roundingstillforcezeroresidthresh : 3 ;
        unsigned int Reserved_165 : 5 ;
        unsigned int vctrl_roundingstillac16sum : 4 ;
        unsigned int Reserved_164 : 4 ;
        unsigned int vctrl_roundingstilllowfreqacblk16 : 4 ;
        unsigned int Reserved_163 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_STATIC_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_still_isolate_ac_enable : 1 ;
        unsigned int vctrl_still_force_zero_cnt : 3 ;
        unsigned int Reserved_167 : 11 ;
        unsigned int vctrl_still_engsum_16 : 6 ;
        unsigned int vctrl_still_engcnt_16 : 5 ;
        unsigned int Reserved_166 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_STATIC_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_sobelstr16_coeff_protect_num : 8 ;
        unsigned int Reserved_171 : 8 ;
        unsigned int vctrl_sobelstr16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_170 : 3 ;
        unsigned int vctrl_roundingsobelstroffset16x16 : 4 ;
        unsigned int Reserved_169 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SOBELSTR_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingsobelstrmechanism : 3 ;
        unsigned int vctrl_roundingsobelstrdegreethresh : 7 ;
        unsigned int vctrl_roundingsobelstrforcezeroresidthresh : 3 ;
        unsigned int Reserved_174 : 5 ;
        unsigned int vctrl_roundingsobelstrac16sum : 4 ;
        unsigned int Reserved_173 : 4 ;
        unsigned int vctrl_roundingsobelstrlowfreqacblk16 : 4 ;
        unsigned int Reserved_172 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SOBELSTR_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_sobelstr_isolate_ac_enable : 1 ;
        unsigned int vctrl_sobelstr_force_zero_cnt : 3 ;
        unsigned int Reserved_176 : 11 ;
        unsigned int vctrl_sobelstr_engsum_16 : 6 ;
        unsigned int vctrl_sobelstr_engcnt_16 : 5 ;
        unsigned int Reserved_175 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SOBELSTR_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_sobelweak16_coeff_protect_num : 8 ;
        unsigned int Reserved_180 : 8 ;
        unsigned int vctrl_sobelweak16_tr1_denois_max_num : 5 ;
        unsigned int Reserved_179 : 3 ;
        unsigned int vctrl_roundingsobelweakoffset16x16 : 4 ;
        unsigned int Reserved_178 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SOBELWEAK_TR16X16_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_roundingsobelweakmechanism : 3 ;
        unsigned int vctrl_roundingsobelweakdegreethresh : 7 ;
        unsigned int vctrl_roundingsobelweakforcezeroresidthresh : 3 ;
        unsigned int Reserved_183 : 5 ;
        unsigned int vctrl_roundingsobelweakac16sum : 4 ;
        unsigned int Reserved_182 : 4 ;
        unsigned int vctrl_roundingsobelweaklowfreqacblk16 : 4 ;
        unsigned int Reserved_181 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SOBELWEAK_COEFF_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_sobelwk_isolate_ac_enable : 1 ;
        unsigned int vctrl_sobelwk_force_zero_cnt : 3 ;
        unsigned int Reserved_185 : 11 ;
        unsigned int vctrl_sobelwk_engsum_16 : 6 ;
        unsigned int vctrl_sobelwk_engcnt_16 : 5 ;
        unsigned int Reserved_184 : 6 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SOBELWEAK_ENG_DENOISE;
typedef union {
    struct {
        unsigned int vctrl_norm_intra_cu4_rdcost_offset : 4 ;
        unsigned int vctrl_norm_intra_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_norm_intra_cu16_rdcost_offset : 4 ;
        unsigned int Reserved_187 : 4 ;
        unsigned int vctrl_strmov_intra_cu4_rdcost_offset : 4 ;
        unsigned int vctrl_strmov_intra_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_strmov_intra_cu16_rdcost_offset : 4 ;
        unsigned int Reserved_186 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_INTRA_RDO_FACTOR_0;
typedef union {
    struct {
        unsigned int vctrl_skin_intra_cu4_rdcost_offset : 4 ;
        unsigned int vctrl_skin_intra_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_skin_intra_cu16_rdcost_offset : 4 ;
        unsigned int Reserved_189 : 4 ;
        unsigned int vctrl_sobel_str_intra_cu4_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_str_intra_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_str_intra_cu16_rdcost_offset : 4 ;
        unsigned int Reserved_188 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_INTRA_RDO_FACTOR_1;
typedef union {
    struct {
        unsigned int vctrl_hedge_intra_cu4_rdcost_offset : 4 ;
        unsigned int vctrl_hedge_intra_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_hedge_intra_cu16_rdcost_offset : 4 ;
        unsigned int Reserved_191 : 4 ;
        unsigned int vctrl_sobel_tex_intra_cu4_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_tex_intra_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_tex_intra_cu16_rdcost_offset : 4 ;
        unsigned int Reserved_190 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_INTRA_RDO_FACTOR_2;
typedef union {
    struct {
        unsigned int vctrl_norm_mrg_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_norm_mrg_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_norm_mrg_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_193 : 4 ;
        unsigned int vctrl_strmov_mrg_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_strmov_mrg_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_strmov_mrg_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_192 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_MRG_RDO_FACTOR_0;
typedef union {
    struct {
        unsigned int vctrl_skin_mrg_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_skin_mrg_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_skin_mrg_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_195 : 4 ;
        unsigned int vctrl_sobel_str_mrg_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_str_mrg_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_str_mrg_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_194 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_MRG_RDO_FACTOR_1;
typedef union {
    struct {
        unsigned int vctrl_hedge_mrg_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_hedge_mrg_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_hedge_mrg_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_197 : 4 ;
        unsigned int vctrl_sobel_tex_mrg_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_tex_mrg_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_tex_mrg_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_196 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_MRG_RDO_FACTOR_2;
typedef union {
    struct {
        unsigned int vctrl_norm_fme_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_norm_fme_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_norm_fme_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_199 : 4 ;
        unsigned int vctrl_strmov_fme_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_strmov_fme_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_strmov_fme_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_198 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_FME_RDO_FACTOR_0;
typedef union {
    struct {
        unsigned int vctrl_skin_fme_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_skin_fme_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_skin_fme_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_201 : 4 ;
        unsigned int vctrl_sobel_str_fme_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_str_fme_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_str_fme_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_200 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_FME_RDO_FACTOR_1;
typedef union {
    struct {
        unsigned int vctrl_hedge_fme_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_hedge_fme_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_hedge_fme_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_203 : 4 ;
        unsigned int vctrl_sobel_tex_fme_cu8_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_tex_fme_cu16_rdcost_offset : 4 ;
        unsigned int vctrl_sobel_tex_fme_cu32_rdcost_offset : 4 ;
        unsigned int Reserved_202 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_FME_RDO_FACTOR_2;
typedef union {
    struct {
        unsigned int vctrl_norm_sel_cu8_rd_offset : 4 ;
        unsigned int vctrl_skin_sel_cu8_rd_offset : 4 ;
        unsigned int vctrl_hedge_sel_cu8_rd_offset : 4 ;
        unsigned int vctrl_strmov_sel_cu8_rd_offset : 4 ;
        unsigned int vctrl_sobelstr_sel_cu8_rd_offset : 4 ;
        unsigned int vctrl_sobeltex_sel_cu8_rd_offset : 4 ;
        unsigned int Reserved_204 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SEL_INTRA_RDO_FACTOR;
typedef union {
    struct {
        unsigned int vctrl_skin_inter_cu_rdcost_offset : 12 ;
        unsigned int vctrl_hedge_inter_cu_rdcost_offset : 12 ;
        unsigned int vctrl_skin_layer_rdcost_offset : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_0;
typedef union {
    struct {
        unsigned int vctrl_sobelstr_inter_cu_rdcost_offset : 12 ;
        unsigned int vctrl_sobeltex_inter_cu_rdcost_offset : 12 ;
        unsigned int vctrl_hedge_layer_rdcost_offset : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_1;
typedef union {
    struct {
        unsigned int vctrl_strmov_inter_cu_rdcost_offset : 12 ;
        unsigned int vctrl_norm_inter_cu_rdcost_offset : 12 ;
        unsigned int vctrl_strmov_layer_rdcost_offset : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_2;
typedef union {
    struct {
        unsigned int vctrl_sobelstr_layer_rdcost_offset : 8 ;
        unsigned int vctrl_sobeltex_layer_rdcost_offset : 8 ;
        unsigned int vctrl_norm_layer_rdcost_offset : 8 ;
        unsigned int Reserved_205 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_VCTRL_SEL_LAYER_RDO_FACTOR;
typedef union {
    struct {
        unsigned int Reserved_209 : 14 ;
        unsigned int curld_col2gray_en : 1 ;
        unsigned int curld_clip_en : 1 ;
        unsigned int curld_narrow_en : 1 ;
        unsigned int Reserved_208 : 3 ;
        unsigned int curld_read_interval : 8 ;
        unsigned int curld_lowdly_en : 1 ;
        unsigned int Reserved_207 : 3 ;
    } bits;
    unsigned int u32;
} U_VEDU_CURLD_GCFG;
typedef union {
    struct {
        unsigned int curld_clip_luma_min : 8 ;
        unsigned int curld_clip_luma_max : 8 ;
        unsigned int curld_clip_chrm_min : 8 ;
        unsigned int curld_clip_chrm_max : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_CURLD_CLIP_THR;
typedef union {
    struct {
        unsigned int pme_l0_psw_adapt_en : 1 ;
        unsigned int Reserved_212 : 31 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SW_ADAPT_EN;
typedef union {
    struct {
        unsigned int pme_l0_psw_thr0 : 16 ;
        unsigned int Reserved_213 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SW_THR0;
typedef union {
    struct {
        unsigned int pme_l0_psw_thr1 : 16 ;
        unsigned int Reserved_214 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SW_THR1;
typedef union {
    struct {
        unsigned int pme_l0_psw_thr2 : 16 ;
        unsigned int Reserved_215 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SW_THR2;
typedef union {
    struct {
        unsigned int pme_skipblk_pre_cost_thr : 16 ;
        unsigned int pme_skipblk_pre_en : 1 ;
        unsigned int Reserved_216 : 15 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SKIP_PRE;
typedef union {
    struct {
        unsigned int pme_tr_weightx_0 : 9 ;
        unsigned int pme_tr_weightx_1 : 9 ;
        unsigned int pme_tr_weightx_2 : 9 ;
        unsigned int Reserved_217 : 5 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_TR_WEIGHTX;
typedef union {
    struct {
        unsigned int pme_tr_weighty_0 : 8 ;
        unsigned int pme_tr_weighty_1 : 8 ;
        unsigned int pme_tr_weighty_2 : 8 ;
        unsigned int Reserved_218 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_TR_WEIGHTY;
typedef union {
    struct {
        unsigned int pme_sr_weight_0 : 4 ;
        unsigned int pme_sr_weight_1 : 4 ;
        unsigned int pme_sr_weight_2 : 4 ;
        unsigned int pme_pskip_strongedge_madi_thr : 8 ;
        unsigned int pme_pskip_strongedge_madi_times : 8 ;
        unsigned int Reserved_219 : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SR_WEIGHT;
typedef union {
    struct {
        unsigned int pme_intrablk_det_cost_thr0 : 16 ;
        unsigned int pme_pskip_mvy_consistency_thr : 8 ;
        unsigned int pme_pskip_mvx_consistency_thr : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_INTRABLK_DET;
typedef union {
    struct {
        unsigned int pme_intrablk_det_mv_dif_thr1 : 8 ;
        unsigned int pme_intrablk_det_mv_dif_thr0 : 8 ;
        unsigned int pme_intrablk_det_mvy_thr : 8 ;
        unsigned int pme_intrablk_det_mvx_thr : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_INTRABLK_DET_THR;
typedef union {
    struct {
        unsigned int pme_skin_u_max_thr : 8 ;
        unsigned int pme_skin_u_min_thr : 8 ;
        unsigned int pme_skin_v_max_thr : 8 ;
        unsigned int pme_skin_v_min_thr : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SKIN_THR;
typedef union {
    struct {
        unsigned int pme_intra16_madi_thr : 8 ;
        unsigned int Reserved_221 : 9 ;
        unsigned int pme_inter_first : 1 ;
        unsigned int Reserved_220 : 14 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_INTRA_LOWPOW;
typedef union {
    struct {
        unsigned int pme_iblk_pre_cost_thr_h264 : 16 ;
        unsigned int pme_intrablk_det_cost_thr1 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_IBLK_COST_THR;
typedef union {
    struct {
        unsigned int pme_skin_num : 9 ;
        unsigned int pme_strong_edge_thr : 8 ;
        unsigned int pme_strong_edge_cnt : 5 ;
        unsigned int pme_still_scene_thr : 9 ;
        unsigned int Reserved_222 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_STRONG_EDGE;
typedef union {
    struct {
        unsigned int pme_move_scene_thr : 8 ;
        unsigned int pme_move_sad_thr : 14 ;
        unsigned int Reserved_223 : 10 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_LARGE_MOVE_THR;
typedef union {
    struct {
        unsigned int pme_interdiff_max_min_madi_abs : 8 ;
        unsigned int pme_interdiff_max_min_madi_times : 8 ;
        unsigned int pme_interstrongedge_madi_thr : 8 ;
        unsigned int Reserved_224 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_INTER_STRONG_EDGE;
typedef union {
    struct {
        unsigned int pme_cost_lamda0 : 4 ;
        unsigned int pme_cost_lamda1 : 4 ;
        unsigned int Reserved_227 : 4 ;
        unsigned int pme_new_cost_en : 2 ;
        unsigned int Reserved_226 : 4 ;
        unsigned int pme_mvp3median_en : 1 ;
        unsigned int Reserved_225 : 13 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_NEW_COST;
typedef union {
    struct {
        unsigned int pme_l0_win0_width : 10 ;
        unsigned int Reserved_229 : 6 ;
        unsigned int pme_l0_win0_height : 9 ;
        unsigned int Reserved_228 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_WINDOW_SIZE0_L0;
typedef union {
    struct {
        unsigned int pme_l0_win1_width : 10 ;
        unsigned int Reserved_231 : 6 ;
        unsigned int pme_l0_win1_height : 9 ;
        unsigned int Reserved_230 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_WINDOW_SIZE1_L0;
typedef union {
    struct {
        unsigned int pme_l0_win2_width : 10 ;
        unsigned int Reserved_233 : 6 ;
        unsigned int pme_l0_win2_height : 9 ;
        unsigned int Reserved_232 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_WINDOW_SIZE2_L0;
typedef union {
    struct {
        unsigned int pme_l0_win3_width : 10 ;
        unsigned int Reserved_235 : 6 ;
        unsigned int pme_l0_win3_height : 9 ;
        unsigned int Reserved_234 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_WINDOW_SIZE3_L0;
typedef union {
    struct {
        unsigned int pme_l0_cost_offset : 16 ;
        unsigned int Reserved_236 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_COST_OFFSET;
typedef union {
    struct {
        unsigned int pme_safe_line : 13 ;
        unsigned int pme_safe_line_val : 1 ;
        unsigned int Reserved_237 : 18 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_SAFE_CFG;
typedef union {
    struct {
        unsigned int pme_iblk_refresh_start_num : 18 ;
        unsigned int Reserved_238 : 14 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_IBLK_REFRESH;
typedef union {
    struct {
        unsigned int pme_iblk_refresh_num : 18 ;
        unsigned int Reserved_239 : 14 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_IBLK_REFRESH_NUM;
typedef union {
    struct {
        unsigned int Reserved_241 : 16 ;
        unsigned int pme_madi_dif_thr : 7 ;
        unsigned int pme_cur_madi_dif_thr : 7 ;
        unsigned int Reserved_240 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_QPG_RC_THR0;
typedef union {
    struct {
        unsigned int pme_min_sad_thr_offset : 8 ;
        unsigned int pme_min_sad_thr_gain : 4 ;
        unsigned int pme_smooth_madi_thr : 8 ;
        unsigned int pme_min_sad_thr_offset_cur : 8 ;
        unsigned int pme_min_sad_thr_gain_cur : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_QPG_RC_THR1;
typedef union {
    struct {
        unsigned int pme_low_luma_thr : 8 ;
        unsigned int pme_low_luma_madi_thr : 8 ;
        unsigned int pme_high_luma_thr : 8 ;
        unsigned int Reserved_242 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_LOW_LUMA_THR;
typedef union {
    struct {
        unsigned int pme_pblk_pre_mv_dif_thr1 : 8 ;
        unsigned int pme_pblk_pre_mv_dif_thr0 : 8 ;
        unsigned int pme_pblk_pre_mv_dif_cost_thr : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_PBLK_PRE1;
typedef union {
    struct {
        unsigned int pme_flat_v_thr_high : 8 ;
        unsigned int pme_flat_v_thr_low : 8 ;
        unsigned int pme_flat_u_thr_high : 8 ;
        unsigned int pme_flat_u_thr_low : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_CHROMA_FLAT;
typedef union {
    struct {
        unsigned int pme_flat_pmemv_thr : 8 ;
        unsigned int pme_flat_luma_madi_thr : 8 ;
        unsigned int pme_flat_low_luma_thr : 8 ;
        unsigned int pme_flat_high_luma_thr : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_LUMA_FLAT;
typedef union {
    struct {
        unsigned int pme_flat_pmesad_thr : 14 ;
        unsigned int pme_flat_icount_thr : 9 ;
        unsigned int pme_flat_region_cnt : 5 ;
        unsigned int pme_flat_madi_times : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_PME_MADI_FLAT;
typedef union {
    struct {
        unsigned int qpg_min_qp : 6 ;
        unsigned int Reserved_247 : 2 ;
        unsigned int qpg_max_qp : 6 ;
        unsigned int Reserved_246 : 2 ;
        unsigned int qpg_cu_qp_delta_enable_flag : 1 ;
        unsigned int Reserved_245 : 15 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_MAX_MIN_QP;
typedef union {
    struct {
        unsigned int qpg_qp_delta : 6 ;
        unsigned int qpg_row_target_bits : 25 ;
        unsigned int Reserved_248 : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_ROW_TARGET_BITS;
typedef union {
    struct {
        unsigned int qpg_ave_lcu_bits : 16 ;
        unsigned int Reserved_249 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_AVERAGE_LCU_BITS;
typedef union {
    struct {
        unsigned int qpg_lowluma_min_qp : 6 ;
        unsigned int Reserved_252 : 2 ;
        unsigned int qpg_lowluma_max_qp : 6 ;
        unsigned int Reserved_251 : 2 ;
        unsigned int qpg_lowluma_qp_delta : 4 ;
        unsigned int Reserved_250 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_LOWLUMA;
typedef union {
    struct {
        unsigned int qpg_hedge_min_qp : 6 ;
        unsigned int Reserved_255 : 2 ;
        unsigned int qpg_hedge_max_qp : 6 ;
        unsigned int Reserved_254 : 2 ;
        unsigned int qpg_hedge_qp_delta : 4 ;
        unsigned int Reserved_253 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_HEDGE;
typedef union {
    struct {
        unsigned int qpg_hedge_move_min_qp : 6 ;
        unsigned int Reserved_258 : 2 ;
        unsigned int qpg_hedge_move_max_qp : 6 ;
        unsigned int Reserved_257 : 2 ;
        unsigned int qpg_hedge_move_qp_delta : 4 ;
        unsigned int Reserved_256 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_HEDGE_MOVE;
typedef union {
    struct {
        unsigned int qpg_large_move_min_qp : 6 ;
        unsigned int Reserved_261 : 2 ;
        unsigned int qpg_large_move_max_qp : 6 ;
        unsigned int Reserved_260 : 2 ;
        unsigned int qpg_large_move_qp_delta : 4 ;
        unsigned int Reserved_259 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_LARGE_MOVE;
typedef union {
    struct {
        unsigned int qpg_skin_min_qp : 6 ;
        unsigned int Reserved_264 : 2 ;
        unsigned int qpg_skin_max_qp : 6 ;
        unsigned int Reserved_263 : 2 ;
        unsigned int qpg_skin_qp_delta : 4 ;
        unsigned int Reserved_262 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_SKIN;
typedef union {
    struct {
        unsigned int qpg_intra_det_min_qp : 6 ;
        unsigned int Reserved_267 : 2 ;
        unsigned int qpg_intra_det_max_qp : 6 ;
        unsigned int Reserved_266 : 2 ;
        unsigned int qpg_intra_det_qp_delta : 4 ;
        unsigned int Reserved_265 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_INTRA_DET;
typedef union {
    struct {
        unsigned int qpg_h264_smooth_min_qp : 6 ;
        unsigned int Reserved_270 : 2 ;
        unsigned int qpg_h264_smooth_max_qp : 6 ;
        unsigned int Reserved_269 : 2 ;
        unsigned int qpg_h264_smooth_qp_delta : 4 ;
        unsigned int qpg_h264_smooth_qp_delta1 : 4 ;
        unsigned int Reserved_268 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_H264_SMOOTH;
typedef union {
    struct {
        unsigned int qpg_cu_qp_delta_thresh0 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh1 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh2 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh3 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_CU_QP_DELTA_THRESH_REG0;
typedef union {
    struct {
        unsigned int qpg_cu_qp_delta_thresh4 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh5 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh6 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh7 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_CU_QP_DELTA_THRESH_REG1;
typedef union {
    struct {
        unsigned int qpg_cu_qp_delta_thresh8 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh9 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh10 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh11 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_CU_QP_DELTA_THRESH_REG2;
typedef union {
    struct {
        unsigned int qpg_cu_qp_delta_thresh12 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh13 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh14 : 8 ;
        unsigned int qpg_cu_qp_delta_thresh15 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_CU_QP_DELTA_THRESH_REG3;
typedef union {
    struct {
        unsigned int qpg_qp_delta_level_0 : 2 ;
        unsigned int qpg_qp_delta_level_1 : 2 ;
        unsigned int qpg_qp_delta_level_2 : 2 ;
        unsigned int qpg_qp_delta_level_3 : 2 ;
        unsigned int qpg_qp_delta_level_4 : 2 ;
        unsigned int qpg_qp_delta_level_5 : 2 ;
        unsigned int qpg_qp_delta_level_6 : 2 ;
        unsigned int qpg_qp_delta_level_7 : 2 ;
        unsigned int qpg_qp_delta_level_8 : 2 ;
        unsigned int qpg_qp_delta_level_9 : 2 ;
        unsigned int qpg_qp_delta_level_10 : 2 ;
        unsigned int qpg_qp_delta_level_11 : 2 ;
        unsigned int qpg_qp_delta_level_12 : 2 ;
        unsigned int qpg_qp_delta_level_13 : 2 ;
        unsigned int qpg_qp_delta_level_14 : 2 ;
        unsigned int qpg_qp_delta_level_15 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_DELTA_LEVEL;
typedef union {
    struct {
        unsigned int qpg_qp_madi_switch_thr : 5 ;
        unsigned int Reserved_271 : 27 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_MADI_SWITCH_THR;
typedef union {
    struct {
        unsigned int qpg_cu32_delta_low : 4 ;
        unsigned int qpg_cu32_delta_high : 4 ;
        unsigned int Reserved_272 : 24 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_CU32_DELTA;
typedef union {
    struct {
        unsigned int qpg_lambda00 : 20 ;
        unsigned int Reserved_273 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG00;
typedef union {
    struct {
        unsigned int qpg_lambda01 : 20 ;
        unsigned int Reserved_274 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG01;
typedef union {
    struct {
        unsigned int qpg_lambda02 : 20 ;
        unsigned int Reserved_275 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG02;
typedef union {
    struct {
        unsigned int qpg_lambda03 : 20 ;
        unsigned int Reserved_276 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG03;
typedef union {
    struct {
        unsigned int qpg_lambda04 : 20 ;
        unsigned int Reserved_277 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG04;
typedef union {
    struct {
        unsigned int qpg_lambda05 : 20 ;
        unsigned int Reserved_278 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG05;
typedef union {
    struct {
        unsigned int qpg_lambda06 : 20 ;
        unsigned int Reserved_279 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG06;
typedef union {
    struct {
        unsigned int qpg_lambda07 : 20 ;
        unsigned int Reserved_280 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG07;
typedef union {
    struct {
        unsigned int qpg_lambda08 : 20 ;
        unsigned int Reserved_281 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG08;
typedef union {
    struct {
        unsigned int qpg_lambda09 : 20 ;
        unsigned int Reserved_282 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG09;
typedef union {
    struct {
        unsigned int qpg_lambda10 : 20 ;
        unsigned int Reserved_283 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG10;
typedef union {
    struct {
        unsigned int qpg_lambda11 : 20 ;
        unsigned int Reserved_284 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG11;
typedef union {
    struct {
        unsigned int qpg_lambda12 : 20 ;
        unsigned int Reserved_285 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG12;
typedef union {
    struct {
        unsigned int qpg_lambda13 : 20 ;
        unsigned int Reserved_286 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG13;
typedef union {
    struct {
        unsigned int qpg_lambda14 : 20 ;
        unsigned int Reserved_287 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG14;
typedef union {
    struct {
        unsigned int qpg_lambda15 : 20 ;
        unsigned int Reserved_288 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG15;
typedef union {
    struct {
        unsigned int qpg_lambda16 : 20 ;
        unsigned int Reserved_289 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG16;
typedef union {
    struct {
        unsigned int qpg_lambda17 : 20 ;
        unsigned int Reserved_290 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG17;
typedef union {
    struct {
        unsigned int qpg_lambda18 : 20 ;
        unsigned int Reserved_291 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG18;
typedef union {
    struct {
        unsigned int qpg_lambda19 : 20 ;
        unsigned int Reserved_292 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG19;
typedef union {
    struct {
        unsigned int qpg_lambda20 : 20 ;
        unsigned int Reserved_293 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG20;
typedef union {
    struct {
        unsigned int qpg_lambda21 : 20 ;
        unsigned int Reserved_294 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG21;
typedef union {
    struct {
        unsigned int qpg_lambda22 : 20 ;
        unsigned int Reserved_295 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG22;
typedef union {
    struct {
        unsigned int qpg_lambda23 : 20 ;
        unsigned int Reserved_296 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG23;
typedef union {
    struct {
        unsigned int qpg_lambda24 : 20 ;
        unsigned int Reserved_297 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG24;
typedef union {
    struct {
        unsigned int qpg_lambda25 : 20 ;
        unsigned int Reserved_298 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG25;
typedef union {
    struct {
        unsigned int qpg_lambda26 : 20 ;
        unsigned int Reserved_299 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG26;
typedef union {
    struct {
        unsigned int qpg_lambda27 : 20 ;
        unsigned int Reserved_300 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG27;
typedef union {
    struct {
        unsigned int qpg_lambda28 : 20 ;
        unsigned int Reserved_301 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG28;
typedef union {
    struct {
        unsigned int qpg_lambda29 : 20 ;
        unsigned int Reserved_302 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG29;
typedef union {
    struct {
        unsigned int qpg_lambda30 : 20 ;
        unsigned int Reserved_303 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG30;
typedef union {
    struct {
        unsigned int qpg_lambda31 : 20 ;
        unsigned int Reserved_304 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG31;
typedef union {
    struct {
        unsigned int qpg_lambda32 : 20 ;
        unsigned int Reserved_305 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG32;
typedef union {
    struct {
        unsigned int qpg_lambda33 : 20 ;
        unsigned int Reserved_306 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG33;
typedef union {
    struct {
        unsigned int qpg_lambda34 : 20 ;
        unsigned int Reserved_307 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG34;
typedef union {
    struct {
        unsigned int qpg_lambda35 : 20 ;
        unsigned int Reserved_308 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG35;
typedef union {
    struct {
        unsigned int qpg_lambda36 : 20 ;
        unsigned int Reserved_309 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG36;
typedef union {
    struct {
        unsigned int qpg_lambda37 : 20 ;
        unsigned int Reserved_310 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG37;
typedef union {
    struct {
        unsigned int qpg_lambda38 : 20 ;
        unsigned int Reserved_311 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG38;
typedef union {
    struct {
        unsigned int qpg_lambda39 : 20 ;
        unsigned int Reserved_312 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG39;
typedef union {
    struct {
        unsigned int qpg_lambda40 : 20 ;
        unsigned int Reserved_313 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG40;
typedef union {
    struct {
        unsigned int qpg_lambda41 : 20 ;
        unsigned int Reserved_314 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG41;
typedef union {
    struct {
        unsigned int qpg_lambda42 : 20 ;
        unsigned int Reserved_315 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG42;
typedef union {
    struct {
        unsigned int qpg_lambda43 : 20 ;
        unsigned int Reserved_316 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG43;
typedef union {
    struct {
        unsigned int qpg_lambda44 : 20 ;
        unsigned int Reserved_317 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG44;
typedef union {
    struct {
        unsigned int qpg_lambda45 : 20 ;
        unsigned int Reserved_318 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG45;
typedef union {
    struct {
        unsigned int qpg_lambda46 : 20 ;
        unsigned int Reserved_319 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG46;
typedef union {
    struct {
        unsigned int qpg_lambda47 : 20 ;
        unsigned int Reserved_320 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG47;
typedef union {
    struct {
        unsigned int qpg_lambda48 : 20 ;
        unsigned int Reserved_321 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG48;
typedef union {
    struct {
        unsigned int qpg_lambda49 : 20 ;
        unsigned int Reserved_322 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG49;
typedef union {
    struct {
        unsigned int qpg_lambda50 : 20 ;
        unsigned int Reserved_323 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG50;
typedef union {
    struct {
        unsigned int qpg_lambda51 : 20 ;
        unsigned int Reserved_324 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG51;
typedef union {
    struct {
        unsigned int qpg_lambda52 : 20 ;
        unsigned int Reserved_325 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG52;
typedef union {
    struct {
        unsigned int qpg_lambda53 : 20 ;
        unsigned int Reserved_326 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG53;
typedef union {
    struct {
        unsigned int qpg_lambda54 : 20 ;
        unsigned int Reserved_327 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG54;
typedef union {
    struct {
        unsigned int qpg_lambda55 : 20 ;
        unsigned int Reserved_328 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG55;
typedef union {
    struct {
        unsigned int qpg_lambda56 : 20 ;
        unsigned int Reserved_329 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG56;
typedef union {
    struct {
        unsigned int qpg_lambda57 : 20 ;
        unsigned int Reserved_330 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG57;
typedef union {
    struct {
        unsigned int qpg_lambda58 : 20 ;
        unsigned int Reserved_331 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG58;
typedef union {
    struct {
        unsigned int qpg_lambda59 : 20 ;
        unsigned int Reserved_332 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG59;
typedef union {
    struct {
        unsigned int qpg_lambda60 : 20 ;
        unsigned int Reserved_333 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG60;
typedef union {
    struct {
        unsigned int qpg_lambda61 : 20 ;
        unsigned int Reserved_334 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG61;
typedef union {
    struct {
        unsigned int qpg_lambda62 : 20 ;
        unsigned int Reserved_335 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG62;
typedef union {
    struct {
        unsigned int qpg_lambda63 : 20 ;
        unsigned int Reserved_336 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG63;
typedef union {
    struct {
        unsigned int qpg_lambda64 : 20 ;
        unsigned int Reserved_337 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG64;
typedef union {
    struct {
        unsigned int qpg_lambda65 : 20 ;
        unsigned int Reserved_338 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG65;
typedef union {
    struct {
        unsigned int qpg_lambda66 : 20 ;
        unsigned int Reserved_339 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG66;
typedef union {
    struct {
        unsigned int qpg_lambda67 : 20 ;
        unsigned int Reserved_340 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG67;
typedef union {
    struct {
        unsigned int qpg_lambda68 : 20 ;
        unsigned int Reserved_341 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG68;
typedef union {
    struct {
        unsigned int qpg_lambda69 : 20 ;
        unsigned int Reserved_342 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG69;
typedef union {
    struct {
        unsigned int qpg_lambda70 : 20 ;
        unsigned int Reserved_343 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG70;
typedef union {
    struct {
        unsigned int qpg_lambda71 : 20 ;
        unsigned int Reserved_344 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG71;
typedef union {
    struct {
        unsigned int qpg_lambda72 : 20 ;
        unsigned int Reserved_345 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG72;
typedef union {
    struct {
        unsigned int qpg_lambda73 : 20 ;
        unsigned int Reserved_346 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG73;
typedef union {
    struct {
        unsigned int qpg_lambda74 : 20 ;
        unsigned int Reserved_347 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG74;
typedef union {
    struct {
        unsigned int qpg_lambda75 : 20 ;
        unsigned int Reserved_348 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG75;
typedef union {
    struct {
        unsigned int qpg_lambda76 : 20 ;
        unsigned int Reserved_349 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG76;
typedef union {
    struct {
        unsigned int qpg_lambda77 : 20 ;
        unsigned int Reserved_350 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG77;
typedef union {
    struct {
        unsigned int qpg_lambda78 : 20 ;
        unsigned int Reserved_351 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG78;
typedef union {
    struct {
        unsigned int qpg_lambda79 : 20 ;
        unsigned int Reserved_352 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_LAMBDA_CTRL_REG79;
typedef union {
    struct {
        unsigned int qpg_lambda_qp_offset : 5 ;
        unsigned int Reserved_355 : 3 ;
        unsigned int qpg_rdo_lambda_choose_mode : 2 ;
        unsigned int Reserved_354 : 2 ;
        unsigned int qpg_lambda_inter_stredge_en : 1 ;
        unsigned int Reserved_353 : 19 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_LAMBDA_MODE;
typedef union {
    struct {
        unsigned int qpg_qp_restrain_madi_thr : 6 ;
        unsigned int Reserved_358 : 2 ;
        unsigned int qpg_qp_restrain_en : 1 ;
        unsigned int qpg_qp_restrain_mode : 2 ;
        unsigned int Reserved_357 : 1 ;
        unsigned int qpg_qp_restrain_delta_blk16 : 4 ;
        unsigned int qpg_qp_restrain_delta_blk32 : 4 ;
        unsigned int Reserved_356 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_QP_RESTRAIN;
typedef union {
    struct {
        unsigned int qpg_min_sad_level : 16 ;
        unsigned int qpg_low_min_sad_mode : 2 ;
        unsigned int qpg_high_min_sad_mode : 2 ;
        unsigned int qpg_min_sad_madi_en : 1 ;
        unsigned int qpg_min_sad_qp_restrain_en : 1 ;
        unsigned int Reserved_359 : 10 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_CU_MIN_SAD_REG;
typedef union {
    struct {
        unsigned int qpg_flat_region_min_qp : 6 ;
        unsigned int Reserved_362 : 2 ;
        unsigned int qpg_flat_region_max_qp : 6 ;
        unsigned int Reserved_361 : 2 ;
        unsigned int qpg_flat_region_qp_delta : 4 ;
        unsigned int Reserved_360 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_QPG_FLAT_REGION;
typedef union {
    struct {
        unsigned int Reserved_367 : 1 ;
        unsigned int ime_inter8x8_en : 1 ;
        unsigned int ime_flat_region_force_low3layer : 1 ;
        unsigned int Reserved_366 : 1 ;
        unsigned int ime_high3pre_en : 2 ;
        unsigned int Reserved_365 : 26 ;
    } bits;
    unsigned int u32;
} U_VEDU_IME_INTER_MODE;
typedef union {
    struct {
        unsigned int ime_lambdaoff8 : 16 ;
        unsigned int ime_lambdaoff16 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_IME_RDOCFG;
typedef union {
    struct {
        unsigned int ime_lowpow_fme_thr0 : 6 ;
        unsigned int ime_lowpow_fme_thr1 : 6 ;
        unsigned int Reserved_368 : 20 ;
    } bits;
    unsigned int u32;
} U_VEDU_IME_FME_LPOW_THR;
typedef union {
    struct {
        unsigned int ime_no_intra_ang_cost_thr : 17 ;
        unsigned int Reserved_369 : 14 ;
        unsigned int ime_no_intra_ang_en : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_IME_NO_INTRA_ANG_EN;
typedef union {
    struct {
        unsigned int ime_no_intra_ang_mvy_thr : 10 ;
        unsigned int Reserved_371 : 6 ;
        unsigned int ime_no_intra_ang_mvx_thr : 11 ;
        unsigned int Reserved_370 : 5 ;
    } bits;
    unsigned int u32;
} U_VEDU_IME_NO_INTRA_ANG_MV_THR;
typedef union {
    struct {
        unsigned int mrg_force_zero_en : 1 ;
        unsigned int mrg_force_y_zero_en : 1 ;
        unsigned int mrg_force_u_zero_en : 1 ;
        unsigned int mrg_force_v_zero_en : 1 ;
        unsigned int Reserved_374 : 28 ;
    } bits;
    unsigned int u32;
} U_VEDU_MRG_FORCE_ZERO_EN;
typedef union {
    struct {
        unsigned int Reserved_376 : 4 ;
        unsigned int mrg_force_skip_en : 1 ;
        unsigned int Reserved_375 : 27 ;
    } bits;
    unsigned int u32;
} U_VEDU_MRG_FORCE_SKIP_EN;
typedef union {
    struct {
        unsigned int intra_inter_avail : 1 ;
        unsigned int Reserved_378 : 31 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_INTER_AVAIL;
typedef union {
    struct {
        unsigned int intra_dc_4shift : 4 ;
        unsigned int intra_dc_8shift : 4 ;
        unsigned int intra_dc_16shift : 4 ;
        unsigned int intra_dc_4mode_en : 1 ;
        unsigned int intra_dc_8mode_en : 1 ;
        unsigned int intra_dc_16mode_en : 1 ;
        unsigned int intra_dc_shift_en : 1 ;
        unsigned int Reserved_379 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_DC_SHIFT;
typedef union {
    struct {
        unsigned int intra_bit_weight : 4 ;
        unsigned int Reserved_380 : 28 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_BIT_WEIGHT;
typedef union {
    struct {
        unsigned int intra_dc_4madi : 8 ;
        unsigned int intra_dc_8madi : 8 ;
        unsigned int intra_dc_16madi : 8 ;
        unsigned int Reserved_381 : 8 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_DC_MADI;
typedef union {
    struct {
        unsigned int intra_cu8_rdo_cost_offset : 16 ;
        unsigned int Reserved_382 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_RDO_COST_OFFSET;
typedef union {
    struct {
        unsigned int intra_cu4_mode0_en : 1 ;
        unsigned int intra_cu4_mode1_en : 1 ;
        unsigned int intra_cu4_mode2_en : 1 ;
        unsigned int intra_cu4_mode3_en : 1 ;
        unsigned int intra_cu4_mode4_en : 1 ;
        unsigned int intra_cu4_mode5_en : 1 ;
        unsigned int intra_cu4_mode6_en : 1 ;
        unsigned int intra_cu4_mode7_en : 1 ;
        unsigned int intra_cu4_mode8_en : 1 ;
        unsigned int Reserved_383 : 23 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_CHNL4_ANG_0EN;
typedef union {
    struct {
        unsigned int intra_cu8_mode0_en : 1 ;
        unsigned int intra_cu8_mode1_en : 1 ;
        unsigned int intra_cu8_mode2_en : 1 ;
        unsigned int intra_cu8_mode3_en : 1 ;
        unsigned int intra_cu8_mode4_en : 1 ;
        unsigned int intra_cu8_mode5_en : 1 ;
        unsigned int intra_cu8_mode6_en : 1 ;
        unsigned int intra_cu8_mode7_en : 1 ;
        unsigned int intra_cu8_mode8_en : 1 ;
        unsigned int intra_cu8_mode9_en : 1 ;
        unsigned int intra_cu8_mode10_en : 1 ;
        unsigned int intra_cu8_mode11_en : 1 ;
        unsigned int intra_cu8_mode12_en : 1 ;
        unsigned int intra_cu8_mode13_en : 1 ;
        unsigned int intra_cu8_mode14_en : 1 ;
        unsigned int intra_cu8_mode15_en : 1 ;
        unsigned int intra_cu8_mode16_en : 1 ;
        unsigned int intra_cu8_mode17_en : 1 ;
        unsigned int intra_cu8_mode18_en : 1 ;
        unsigned int intra_cu8_mode19_en : 1 ;
        unsigned int intra_cu8_mode20_en : 1 ;
        unsigned int intra_cu8_mode21_en : 1 ;
        unsigned int intra_cu8_mode22_en : 1 ;
        unsigned int intra_cu8_mode23_en : 1 ;
        unsigned int intra_cu8_mode24_en : 1 ;
        unsigned int intra_cu8_mode25_en : 1 ;
        unsigned int intra_cu8_mode26_en : 1 ;
        unsigned int intra_cu8_mode27_en : 1 ;
        unsigned int intra_cu8_mode28_en : 1 ;
        unsigned int intra_cu8_mode29_en : 1 ;
        unsigned int intra_cu8_mode30_en : 1 ;
        unsigned int intra_cu8_mode31_en : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_CHNL8_ANG_0EN;
typedef union {
    struct {
        unsigned int intra_cu8_mode32_en : 1 ;
        unsigned int intra_cu8_mode33_en : 1 ;
        unsigned int intra_cu8_mode34_en : 1 ;
        unsigned int Reserved_384 : 29 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_CHNL8_ANG_1EN;
typedef union {
    struct {
        unsigned int intra_cu16_mode0_en : 1 ;
        unsigned int intra_cu16_mode1_en : 1 ;
        unsigned int intra_cu16_mode2_en : 1 ;
        unsigned int intra_cu16_mode3_en : 1 ;
        unsigned int intra_cu16_mode4_en : 1 ;
        unsigned int intra_cu16_mode5_en : 1 ;
        unsigned int intra_cu16_mode6_en : 1 ;
        unsigned int intra_cu16_mode7_en : 1 ;
        unsigned int intra_cu16_mode8_en : 1 ;
        unsigned int intra_cu16_mode9_en : 1 ;
        unsigned int intra_cu16_mode10_en : 1 ;
        unsigned int intra_cu16_mode11_en : 1 ;
        unsigned int intra_cu16_mode12_en : 1 ;
        unsigned int intra_cu16_mode13_en : 1 ;
        unsigned int intra_cu16_mode14_en : 1 ;
        unsigned int intra_cu16_mode15_en : 1 ;
        unsigned int intra_cu16_mode16_en : 1 ;
        unsigned int intra_cu16_mode17_en : 1 ;
        unsigned int intra_cu16_mode18_en : 1 ;
        unsigned int intra_cu16_mode19_en : 1 ;
        unsigned int intra_cu16_mode20_en : 1 ;
        unsigned int intra_cu16_mode21_en : 1 ;
        unsigned int intra_cu16_mode22_en : 1 ;
        unsigned int intra_cu16_mode23_en : 1 ;
        unsigned int intra_cu16_mode24_en : 1 ;
        unsigned int intra_cu16_mode25_en : 1 ;
        unsigned int intra_cu16_mode26_en : 1 ;
        unsigned int intra_cu16_mode27_en : 1 ;
        unsigned int intra_cu16_mode28_en : 1 ;
        unsigned int intra_cu16_mode29_en : 1 ;
        unsigned int intra_cu16_mode30_en : 1 ;
        unsigned int intra_cu16_mode31_en : 1 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_CHNL16_ANG_0EN;
typedef union {
    struct {
        unsigned int intra_cu16_mode32_en : 1 ;
        unsigned int intra_cu16_mode33_en : 1 ;
        unsigned int intra_cu16_mode34_en : 1 ;
        unsigned int Reserved_385 : 29 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_CHNL16_ANG_1EN;
typedef union {
    struct {
        unsigned int h264chroma_mode0_en : 1 ;
        unsigned int h264chroma_mode1_en : 1 ;
        unsigned int h264chroma_mode2_en : 1 ;
        unsigned int h264chroma_mode3_en : 1 ;
        unsigned int Reserved_386 : 28 ;
    } bits;
    unsigned int u32;
} U_VEDU_INTRA_CHROMA_ANG_EN;
typedef union {
    struct {
        unsigned int pmv_tmv_en : 1 ;
        unsigned int Reserved_388 : 31 ;
    } bits;
    unsigned int u32;
} U_VEDU_PMV_TMV_EN;
typedef union {
    struct {
        unsigned int tqitq_deadzone_intra_slice : 8 ;
        unsigned int tqitq_deadzone_inter_slice : 8 ;
        unsigned int Reserved_390 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_TQITQ_DEADZONE;
typedef union {
    struct {
        unsigned int sel_intra4_8_abs_offset : 16 ;
        unsigned int sel_intra16_abs_offset : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_INTRA_ABS_OFFSET0;
typedef union {
    struct {
        unsigned int sel_intra32_abs_offset : 16 ;
        unsigned int sel_layer32_abs_offset : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_INTRA_ABS_OFFSET1;
typedef union {
    struct {
        unsigned int sel_inter8_16_abs_offset : 16 ;
        unsigned int sel_inter32_abs_offset : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_INTER_ABS_OFFSET0;
typedef union {
    struct {
        unsigned int sel_offset_strength : 3 ;
        unsigned int Reserved_393 : 29 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_OFFSET_STRENGTH;
typedef union {
    struct {
        unsigned int sel_cu32_dc_ac_th_offset : 2 ;
        unsigned int Reserved_394 : 30 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_CU32_DC_AC_TH_OFFSET;
typedef union {
    struct {
        unsigned int sel_cu32_qp0_th : 6 ;
        unsigned int Reserved_396 : 2 ;
        unsigned int sel_cu32_qp1_th : 6 ;
        unsigned int Reserved_395 : 18 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_CU32_QP_TH;
typedef union {
    struct {
        unsigned int sel_res16_luma_dc_th : 4 ;
        unsigned int sel_res16_chroma_dc_th : 4 ;
        unsigned int sel_res16_luma_ac_th : 4 ;
        unsigned int sel_res16_chroma_ac_th : 4 ;
        unsigned int sel_res32_luma_dc_th : 4 ;
        unsigned int sel_res32_chroma_dc_th : 4 ;
        unsigned int sel_res32_luma_ac_th : 4 ;
        unsigned int sel_res32_chroma_ac_th : 4 ;
    } bits;
    unsigned int u32;
} U_VEDU_SEL_RES_DC_AC_TH;
typedef union {
    struct {
        unsigned int vcpi_wtmax : 10 ;
        unsigned int vcpi_rtmax : 10 ;
        unsigned int Reserved_400 : 12 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_WAIT_TIM_OUT;
typedef union {
    struct {
        unsigned int vcpi_ch00_rrmax : 5 ;
        unsigned int vcpi_ch01_rrmax : 5 ;
        unsigned int vcpi_ch02_rrmax : 5 ;
        unsigned int vcpi_ch03_rrmax : 5 ;
        unsigned int vcpi_ch04_rrmax : 5 ;
        unsigned int vcpi_ch05_rrmax : 5 ;
        unsigned int Reserved_401 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_RCH_RPT_TH0;
typedef union {
    struct {
        unsigned int vcpi_ch06_rrmax : 5 ;
        unsigned int vcpi_ch07_rrmax : 5 ;
        unsigned int vcpi_ch08_rrmax : 5 ;
        unsigned int vcpi_ch09_rrmax : 5 ;
        unsigned int vcpi_ch10_rrmax : 5 ;
        unsigned int vcpi_ch11_rrmax : 5 ;
        unsigned int Reserved_402 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_RCH_RPT_TH1;
typedef union {
    struct {
        unsigned int vcpi_ch12_rrmax : 5 ;
        unsigned int Reserved_403 : 27 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_RCH_RPT_TH2;
typedef union {
    struct {
        unsigned int vcpi_ch00_wrmax : 5 ;
        unsigned int vcpi_ch01_wrmax : 5 ;
        unsigned int vcpi_ch02_wrmax : 5 ;
        unsigned int vcpi_ch03_wrmax : 5 ;
        unsigned int vcpi_ch04_wrmax : 5 ;
        unsigned int vcpi_ch05_wrmax : 5 ;
        unsigned int Reserved_404 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_WCH_RPT_TH0;
typedef union {
    struct {
        unsigned int vcpi_ch06_wrmax : 5 ;
        unsigned int vcpi_ch07_wrmax : 5 ;
        unsigned int vcpi_ch08_wrmax : 5 ;
        unsigned int vcpi_ch09_wrmax : 5 ;
        unsigned int vcpi_ch10_wrmax : 5 ;
        unsigned int vcpi_ch11_wrmax : 5 ;
        unsigned int Reserved_405 : 2 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_WCH_RPT_TH1;
typedef union {
    struct {
        unsigned int vcpi_ch12_wrmax : 5 ;
        unsigned int vcpi_ch13_wrmax : 5 ;
        unsigned int vcpi_ch14_wrmax : 5 ;
        unsigned int Reserved_406 : 17 ;
    } bits;
    unsigned int u32;
} U_VEDU_EMAR_WCH_RPT_TH2;
typedef union {
    struct {
        unsigned int Reserved_410 : 8 ;
        unsigned int cabac_max_num_mergecand : 3 ;
        unsigned int Reserved_409 : 5 ;
        unsigned int cabac_nal_unit_head : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_CABAC_GLB_CFG;
typedef union {
    struct {
        unsigned int cabac_slchdr_size_part1 : 5 ;
        unsigned int Reserved_411 : 11 ;
        unsigned int cabac_slchdr_size_part2 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_CABAC_SLCHDR_SIZE;
typedef union {
    struct {
        unsigned int cabac_slchdr_part1 : 16 ;
        unsigned int Reserved_412 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_CABAC_SLCHDR_PART1;
typedef union {
    struct {
        unsigned int cabac_slchdr_size_part1_i : 5 ;
        unsigned int Reserved_413 : 11 ;
        unsigned int cabac_slchdr_size_part2_i : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_CABAC_SLCHDR_SIZE_I;
typedef union {
    struct {
        unsigned int cabac_slchdr_part1_i : 16 ;
        unsigned int Reserved_414 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_CABAC_SLCHDR_PART1_I;
typedef union {
    struct {
        unsigned int vlc_markingbit : 6 ;
        unsigned int reserved1 : 2 ;
        unsigned int vlc_reorderbit : 6 ;
        unsigned int reserved0 : 2 ;
        unsigned int vlc_parabit : 7 ;
        unsigned int Reserved_416 : 9 ;
    } bits;
    unsigned int u32;
} U_VEDU_VLC_SLCHDRPARA;
typedef union {
    struct {
        unsigned int vlc_svc_en : 1 ;
        unsigned int vlc_svc_strm : 24 ;
        unsigned int Reserved_417 : 7 ;
    } bits;
    unsigned int u32;
} U_VEDU_VLC_SVC;
typedef union {
    struct {
        unsigned int vlc_markingbit_i : 6 ;
        unsigned int reserved1 : 2 ;
        unsigned int vlc_reorderbit_i : 6 ;
        unsigned int reserved0 : 2 ;
        unsigned int vlc_parabit_i : 7 ;
        unsigned int Reserved_418 : 9 ;
    } bits;
    unsigned int u32;
} U_VEDU_VLC_SLCHDRPARA_I;
typedef union {
    struct {
        unsigned int vlcst_ptbits_en : 1 ;
        unsigned int Reserved_420 : 31 ;
    } bits;
    unsigned int u32;
} U_VEDU_VLCST_PTBITS_EN;
typedef union {
    struct {
        unsigned int vlcst_para_set_len : 8 ;
        unsigned int vlcst_para_sprat_en : 1 ;
        unsigned int Reserved_423 : 7 ;
        unsigned int vlcst_para_set_en : 1 ;
        unsigned int Reserved_422 : 15 ;
    } bits;
    unsigned int u32;
} U_VEDU_VLCST_PARAMETER;
typedef union {
    struct {
        unsigned int env_chn_curr_id : 4 ;
        unsigned int env_chn_goptype : 4 ;
        unsigned int env_chn_bfrm_num : 8 ;
        unsigned int Reserved_425 : 16 ;
    } bits;
    unsigned int u32;
} U_VEDU_ENV_CHN;
typedef union {
    struct {
        unsigned int vcpi_int_ve_eop : 1 ;
        unsigned int vcpi_int_vedu_slice_end : 1 ;
        unsigned int vcpi_int_ve_buffull : 1 ;
        unsigned int vcpi_int_ve_pbitsover : 1 ;
        unsigned int vcpi_int_vedu_brkpt : 1 ;
        unsigned int vcpi_int_vedu_step : 1 ;
        unsigned int vcpi_int_vedu_timeout : 1 ;
        unsigned int vcpi_int_cfg_err : 1 ;
        unsigned int Reserved_427 : 24 ;
    } bits;
    unsigned int u32;
} U_FUNC_VCPI_INTSTAT;
typedef union {
    struct {
        unsigned int vcpi_rint_ve_eop : 1 ;
        unsigned int vcpi_rint_vedu_slice_end : 1 ;
        unsigned int vcpi_rint_ve_buffull : 1 ;
        unsigned int vcpi_rint_ve_pbitsover : 1 ;
        unsigned int vcpi_rint_vedu_brkpt : 1 ;
        unsigned int vcpi_rint_vedu_step : 1 ;
        unsigned int vcpi_rint_vedu_timeout : 1 ;
        unsigned int vcpi_rint_cfg_err : 1 ;
        unsigned int Reserved_428 : 24 ;
    } bits;
    unsigned int u32;
} U_FUNC_VCPI_RAWINT;
typedef union {
    struct {
        unsigned int vcpi_int_ve_eop_s : 1 ;
        unsigned int vcpi_int_vedu_slice_end_s : 1 ;
        unsigned int vcpi_int_ve_buffull_s : 1 ;
        unsigned int vcpi_int_ve_pbitsover_s : 1 ;
        unsigned int vcpi_int_vedu_brkpt_s : 1 ;
        unsigned int vcpi_int_vedu_step_s : 1 ;
        unsigned int vcpi_int_vedu_timeout_s : 1 ;
        unsigned int vcpi_int_cfg_err_s : 1 ;
        unsigned int Reserved_429 : 24 ;
    } bits;
    unsigned int u32;
} U_FUNC_VCPI_INTSTAT_S;
typedef union {
    struct {
        unsigned int vcpi_rint_ve_eop_s : 1 ;
        unsigned int vcpi_rint_vedu_slice_end_s : 1 ;
        unsigned int vcpi_rint_ve_buffull_s : 1 ;
        unsigned int vcpi_rint_ve_pbitsover_s : 1 ;
        unsigned int vcpi_rint_vedu_brkpt_s : 1 ;
        unsigned int vcpi_rint_vedu_step_s : 1 ;
        unsigned int vcpi_rint_vedu_timeout_s : 1 ;
        unsigned int vcpi_rint_cfg_err_s : 1 ;
        unsigned int Reserved_430 : 24 ;
    } bits;
    unsigned int u32;
} U_FUNC_VCPI_RAWINT_S;
typedef union {
    struct {
        unsigned int pme_madi_sum : 25 ;
        unsigned int Reserved_438 : 7 ;
    } bits;
    unsigned int u32;
} U_FUNC_PME_MADI_SUM;
typedef union {
    struct {
        unsigned int pme_madp_sum : 25 ;
        unsigned int Reserved_439 : 7 ;
    } bits;
    unsigned int u32;
} U_FUNC_PME_MADP_SUM;
typedef union {
    struct {
        unsigned int pme_madi_num : 17 ;
        unsigned int Reserved_440 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_PME_MADI_NUM;
typedef union {
    struct {
        unsigned int pme_madp_num : 17 ;
        unsigned int Reserved_441 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_PME_MADP_NUM;
typedef union {
    struct {
        unsigned int slc_len0 : 29 ;
        unsigned int Reserved_464 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR00;
typedef union {
    struct {
        unsigned int invalidnum0 : 7 ;
        unsigned int Reserved_466 : 9 ;
        unsigned int slice_type0 : 2 ;
        unsigned int Reserved_465 : 13 ;
        unsigned int islastslc0 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR01;
typedef union {
    struct {
        unsigned int slc_len1 : 29 ;
        unsigned int Reserved_467 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR10;
typedef union {
    struct {
        unsigned int invalidnum1 : 7 ;
        unsigned int Reserved_469 : 9 ;
        unsigned int slice_type1 : 2 ;
        unsigned int Reserved_468 : 13 ;
        unsigned int islastslc1 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR11;
typedef union {
    struct {
        unsigned int slc_len2 : 29 ;
        unsigned int Reserved_470 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR20;
typedef union {
    struct {
        unsigned int invalidnum2 : 7 ;
        unsigned int Reserved_472 : 9 ;
        unsigned int slice_type2 : 2 ;
        unsigned int Reserved_471 : 13 ;
        unsigned int islastslc2 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR21;
typedef union {
    struct {
        unsigned int slc_len3 : 29 ;
        unsigned int Reserved_473 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR30;
typedef union {
    struct {
        unsigned int invalidnum3 : 7 ;
        unsigned int Reserved_475 : 9 ;
        unsigned int slice_type3 : 2 ;
        unsigned int Reserved_474 : 13 ;
        unsigned int islastslc3 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR31;
typedef union {
    struct {
        unsigned int slc_len4 : 29 ;
        unsigned int Reserved_476 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR40;
typedef union {
    struct {
        unsigned int invalidnum4 : 7 ;
        unsigned int Reserved_478 : 9 ;
        unsigned int slice_type4 : 2 ;
        unsigned int Reserved_477 : 13 ;
        unsigned int islastslc4 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR41;
typedef union {
    struct {
        unsigned int slc_len5 : 29 ;
        unsigned int Reserved_479 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR50;
typedef union {
    struct {
        unsigned int invalidnum5 : 7 ;
        unsigned int Reserved_481 : 9 ;
        unsigned int slice_type5 : 2 ;
        unsigned int Reserved_480 : 13 ;
        unsigned int islastslc5 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR51;
typedef union {
    struct {
        unsigned int slc_len6 : 29 ;
        unsigned int Reserved_482 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR60;
typedef union {
    struct {
        unsigned int invalidnum6 : 7 ;
        unsigned int Reserved_484 : 9 ;
        unsigned int slice_type6 : 2 ;
        unsigned int Reserved_483 : 13 ;
        unsigned int islastslc6 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR61;
typedef union {
    struct {
        unsigned int slc_len7 : 29 ;
        unsigned int Reserved_485 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR70;
typedef union {
    struct {
        unsigned int invalidnum7 : 7 ;
        unsigned int Reserved_487 : 9 ;
        unsigned int slice_type7 : 2 ;
        unsigned int Reserved_486 : 13 ;
        unsigned int islastslc7 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR71;
typedef union {
    struct {
        unsigned int slc_len8 : 29 ;
        unsigned int Reserved_488 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR80;
typedef union {
    struct {
        unsigned int invalidnum8 : 7 ;
        unsigned int Reserved_490 : 9 ;
        unsigned int slice_type8 : 2 ;
        unsigned int Reserved_489 : 13 ;
        unsigned int islastslc8 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR81;
typedef union {
    struct {
        unsigned int slc_len9 : 29 ;
        unsigned int Reserved_491 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR90;
typedef union {
    struct {
        unsigned int invalidnum9 : 7 ;
        unsigned int Reserved_493 : 9 ;
        unsigned int slice_type9 : 2 ;
        unsigned int Reserved_492 : 13 ;
        unsigned int islastslc9 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR91;
typedef union {
    struct {
        unsigned int slc_len10 : 29 ;
        unsigned int Reserved_494 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR100;
typedef union {
    struct {
        unsigned int invalidnum10 : 7 ;
        unsigned int Reserved_496 : 9 ;
        unsigned int slice_type10 : 2 ;
        unsigned int Reserved_495 : 13 ;
        unsigned int islastslc10 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR101;
typedef union {
    struct {
        unsigned int slc_len11 : 29 ;
        unsigned int Reserved_497 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR110;
typedef union {
    struct {
        unsigned int invalidnum11 : 7 ;
        unsigned int Reserved_499 : 9 ;
        unsigned int slice_type11 : 2 ;
        unsigned int Reserved_498 : 13 ;
        unsigned int islastslc11 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR111;
typedef union {
    struct {
        unsigned int slc_len12 : 29 ;
        unsigned int Reserved_500 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR120;
typedef union {
    struct {
        unsigned int invalidnum12 : 7 ;
        unsigned int Reserved_502 : 9 ;
        unsigned int slice_type12 : 2 ;
        unsigned int Reserved_501 : 13 ;
        unsigned int islastslc12 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR121;
typedef union {
    struct {
        unsigned int slc_len13 : 29 ;
        unsigned int Reserved_503 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR130;
typedef union {
    struct {
        unsigned int invalidnum13 : 7 ;
        unsigned int Reserved_505 : 9 ;
        unsigned int slice_type13 : 2 ;
        unsigned int Reserved_504 : 13 ;
        unsigned int islastslc13 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR131;
typedef union {
    struct {
        unsigned int slc_len14 : 29 ;
        unsigned int Reserved_506 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR140;
typedef union {
    struct {
        unsigned int invalidnum14 : 7 ;
        unsigned int Reserved_508 : 9 ;
        unsigned int slice_type14 : 2 ;
        unsigned int Reserved_507 : 13 ;
        unsigned int islastslc14 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR141;
typedef union {
    struct {
        unsigned int slc_len15 : 29 ;
        unsigned int Reserved_509 : 3 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR150;
typedef union {
    struct {
        unsigned int invalidnum15 : 7 ;
        unsigned int Reserved_511 : 9 ;
        unsigned int slice_type15 : 2 ;
        unsigned int Reserved_510 : 13 ;
        unsigned int islastslc15 : 1 ;
    } bits;
    unsigned int u32;
} U_FUNC_VLCST_DSRPTR151;
typedef union {
    struct {
        unsigned int opt_8x8_cnt : 19 ;
        unsigned int Reserved_515 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int intra_opt_8x8_cnt : 19 ;
        unsigned int Reserved_516 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTRA_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int intra_normal_opt_8x8_cnt : 19 ;
        unsigned int Reserved_517 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTRA_NORMAL_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int pcm_opt_8x8_cnt : 19 ;
        unsigned int Reserved_518 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTRA_PCM_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int inter_opt_8x8_cnt : 19 ;
        unsigned int Reserved_519 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int fme_opt_8x8_cnt : 19 ;
        unsigned int Reserved_520 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_FME_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int mrg_opt_8x8_cnt : 19 ;
        unsigned int Reserved_521 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_MERGE_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int mrg_skip_opt_8x8_cnt : 19 ;
        unsigned int Reserved_522 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_SKIP_OPT_8X8_CNT;
typedef union {
    struct {
        unsigned int opt_16x16_cnt : 17 ;
        unsigned int Reserved_523 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_OPT_16X16_CNT;
typedef union {
    struct {
        unsigned int intra_opt_16x16_cnt : 17 ;
        unsigned int Reserved_524 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTRA_OPT_16X16_CNT;
typedef union {
    struct {
        unsigned int opt_4x4_cnt : 19 ;
        unsigned int Reserved_525 : 13 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_OPT_4X4_CNT;
typedef union {
    struct {
        unsigned int inter_opt_16x16_cnt : 17 ;
        unsigned int Reserved_527 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_OPT_16X16_CNT;
typedef union {
    struct {
        unsigned int fme_opt_16x16_cnt : 17 ;
        unsigned int Reserved_528 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_FME_OPT_16X16_CNT;
typedef union {
    struct {
        unsigned int mrg_opt_16x16_cnt : 17 ;
        unsigned int Reserved_529 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_MERGE_OPT_16X16_CNT;
typedef union {
    struct {
        unsigned int mrg_skip_opt_16x16_cnt : 17 ;
        unsigned int Reserved_530 : 15 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_SKIP_OPT_16X16_CNT;
typedef union {
    struct {
        unsigned int opt_32x32_cnt : 16 ;
        unsigned int Reserved_531 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_OPT_32X32_CNT;
typedef union {
    struct {
        unsigned int intra_opt_32x32_cnt : 16 ;
        unsigned int Reserved_532 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTRA_OPT_32X32_CNT;
typedef union {
    struct {
        unsigned int inter_opt_32x32_cnt : 16 ;
        unsigned int Reserved_534 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_OPT_32X32_CNT;
typedef union {
    struct {
        unsigned int fme_opt_32x32_cnt : 16 ;
        unsigned int Reserved_535 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_FME_OPT_32X32_CNT;
typedef union {
    struct {
        unsigned int mrg_opt_32x32_cnt : 16 ;
        unsigned int Reserved_536 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_MERGE_OPT_32X32_CNT;
typedef union {
    struct {
        unsigned int mrg_skip_opt_32x32_cnt : 16 ;
        unsigned int Reserved_537 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_SKIP_OPT_32X32_CNT;
typedef union {
    struct {
        unsigned int opt_64x64_cnt : 16 ;
        unsigned int Reserved_538 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_OPT_64X64_CNT;
typedef union {
    struct {
        unsigned int fme_opt_64x64_cnt : 16 ;
        unsigned int Reserved_539 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_FME_OPT_64X64_CNT;
typedef union {
    struct {
        unsigned int mrg_opt_64x64_cnt : 16 ;
        unsigned int Reserved_540 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_MERGE_OPT_64X64_CNT;
typedef union {
    struct {
        unsigned int mrg_skip_opt_64x64_cnt : 16 ;
        unsigned int Reserved_541 : 16 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_INTER_SKIP_OPT_64X64_CNT;
typedef union {
    struct {
        unsigned int total_luma_qp : 26 ;
        unsigned int Reserved_542 : 6 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_TOTAL_LUMA_QP;
typedef union {
    struct {
        unsigned int min_luma_qp : 6 ;
        unsigned int Reserved_544 : 2 ;
        unsigned int max_luma_qp : 6 ;
        unsigned int Reserved_543 : 18 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_MAX_MIN_LUMA_QP;
typedef union {
    struct {
        unsigned int luma_qp0_cnt : 21 ;
        unsigned int Reserved_546 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP0_CNT;
typedef union {
    struct {
        unsigned int luma_qp1_cnt : 21 ;
        unsigned int Reserved_547 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP1_CNT;
typedef union {
    struct {
        unsigned int luma_qp2_cnt : 21 ;
        unsigned int Reserved_548 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP2_CNT;
typedef union {
    struct {
        unsigned int luma_qp3_cnt : 21 ;
        unsigned int Reserved_549 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP3_CNT;
typedef union {
    struct {
        unsigned int luma_qp4_cnt : 21 ;
        unsigned int Reserved_550 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP4_CNT;
typedef union {
    struct {
        unsigned int luma_qp5_cnt : 21 ;
        unsigned int Reserved_551 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP5_CNT;
typedef union {
    struct {
        unsigned int luma_qp6_cnt : 21 ;
        unsigned int Reserved_552 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP6_CNT;
typedef union {
    struct {
        unsigned int luma_qp7_cnt : 21 ;
        unsigned int Reserved_553 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP7_CNT;
typedef union {
    struct {
        unsigned int luma_qp8_cnt : 21 ;
        unsigned int Reserved_554 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP8_CNT;
typedef union {
    struct {
        unsigned int luma_qp9_cnt : 21 ;
        unsigned int Reserved_555 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP9_CNT;
typedef union {
    struct {
        unsigned int luma_qp10_cnt : 21 ;
        unsigned int Reserved_556 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP10_CNT;
typedef union {
    struct {
        unsigned int luma_qp11_cnt : 21 ;
        unsigned int Reserved_557 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP11_CNT;
typedef union {
    struct {
        unsigned int luma_qp12_cnt : 21 ;
        unsigned int Reserved_558 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP12_CNT;
typedef union {
    struct {
        unsigned int luma_qp13_cnt : 21 ;
        unsigned int Reserved_559 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP13_CNT;
typedef union {
    struct {
        unsigned int luma_qp14_cnt : 21 ;
        unsigned int Reserved_560 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP14_CNT;
typedef union {
    struct {
        unsigned int luma_qp15_cnt : 21 ;
        unsigned int Reserved_561 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP15_CNT;
typedef union {
    struct {
        unsigned int luma_qp16_cnt : 21 ;
        unsigned int Reserved_562 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP16_CNT;
typedef union {
    struct {
        unsigned int luma_qp17_cnt : 21 ;
        unsigned int Reserved_563 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP17_CNT;
typedef union {
    struct {
        unsigned int luma_qp18_cnt : 21 ;
        unsigned int Reserved_564 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP18_CNT;
typedef union {
    struct {
        unsigned int luma_qp19_cnt : 21 ;
        unsigned int Reserved_565 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP19_CNT;
typedef union {
    struct {
        unsigned int luma_qp20_cnt : 21 ;
        unsigned int Reserved_566 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP20_CNT;
typedef union {
    struct {
        unsigned int luma_qp21_cnt : 21 ;
        unsigned int Reserved_567 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP21_CNT;
typedef union {
    struct {
        unsigned int luma_qp22_cnt : 21 ;
        unsigned int Reserved_568 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP22_CNT;
typedef union {
    struct {
        unsigned int luma_qp23_cnt : 21 ;
        unsigned int Reserved_569 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP23_CNT;
typedef union {
    struct {
        unsigned int luma_qp24_cnt : 21 ;
        unsigned int Reserved_570 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP24_CNT;
typedef union {
    struct {
        unsigned int luma_qp25_cnt : 21 ;
        unsigned int Reserved_571 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP25_CNT;
typedef union {
    struct {
        unsigned int luma_qp26_cnt : 21 ;
        unsigned int Reserved_572 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP26_CNT;
typedef union {
    struct {
        unsigned int luma_qp27_cnt : 21 ;
        unsigned int Reserved_573 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP27_CNT;
typedef union {
    struct {
        unsigned int luma_qp28_cnt : 21 ;
        unsigned int Reserved_574 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP28_CNT;
typedef union {
    struct {
        unsigned int luma_qp29_cnt : 21 ;
        unsigned int Reserved_575 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP29_CNT;
typedef union {
    struct {
        unsigned int luma_qp30_cnt : 21 ;
        unsigned int Reserved_576 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP30_CNT;
typedef union {
    struct {
        unsigned int luma_qp31_cnt : 21 ;
        unsigned int Reserved_577 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP31_CNT;
typedef union {
    struct {
        unsigned int luma_qp32_cnt : 21 ;
        unsigned int Reserved_578 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP32_CNT;
typedef union {
    struct {
        unsigned int luma_qp33_cnt : 21 ;
        unsigned int Reserved_579 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP33_CNT;
typedef union {
    struct {
        unsigned int luma_qp34_cnt : 21 ;
        unsigned int Reserved_580 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP34_CNT;
typedef union {
    struct {
        unsigned int luma_qp35_cnt : 21 ;
        unsigned int Reserved_581 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP35_CNT;
typedef union {
    struct {
        unsigned int luma_qp36_cnt : 21 ;
        unsigned int Reserved_582 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP36_CNT;
typedef union {
    struct {
        unsigned int luma_qp37_cnt : 21 ;
        unsigned int Reserved_583 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP37_CNT;
typedef union {
    struct {
        unsigned int luma_qp38_cnt : 21 ;
        unsigned int Reserved_584 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP38_CNT;
typedef union {
    struct {
        unsigned int luma_qp39_cnt : 21 ;
        unsigned int Reserved_585 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP39_CNT;
typedef union {
    struct {
        unsigned int luma_qp40_cnt : 21 ;
        unsigned int Reserved_586 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP40_CNT;
typedef union {
    struct {
        unsigned int luma_qp41_cnt : 21 ;
        unsigned int Reserved_587 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP41_CNT;
typedef union {
    struct {
        unsigned int luma_qp42_cnt : 21 ;
        unsigned int Reserved_588 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP42_CNT;
typedef union {
    struct {
        unsigned int luma_qp43_cnt : 21 ;
        unsigned int Reserved_589 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP43_CNT;
typedef union {
    struct {
        unsigned int luma_qp44_cnt : 21 ;
        unsigned int Reserved_590 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP44_CNT;
typedef union {
    struct {
        unsigned int luma_qp45_cnt : 21 ;
        unsigned int Reserved_591 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP45_CNT;
typedef union {
    struct {
        unsigned int luma_qp46_cnt : 21 ;
        unsigned int Reserved_592 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP46_CNT;
typedef union {
    struct {
        unsigned int luma_qp47_cnt : 21 ;
        unsigned int Reserved_593 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP47_CNT;
typedef union {
    struct {
        unsigned int luma_qp48_cnt : 21 ;
        unsigned int Reserved_594 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP48_CNT;
typedef union {
    struct {
        unsigned int luma_qp49_cnt : 21 ;
        unsigned int Reserved_595 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP49_CNT;
typedef union {
    struct {
        unsigned int luma_qp50_cnt : 21 ;
        unsigned int Reserved_596 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP50_CNT;
typedef union {
    struct {
        unsigned int luma_qp51_cnt : 21 ;
        unsigned int Reserved_597 : 11 ;
    } bits;
    unsigned int u32;
} U_FUNC_SEL_LUMA_QP51_CNT;
typedef union {
    struct {
        unsigned int saooff_luma_num : 14 ;
        unsigned int Reserved_601 : 2 ;
        unsigned int saooff_chroma_num : 14 ;
        unsigned int Reserved_600 : 2 ;
    } bits;
    unsigned int u32;
} U_FUNC_SAO_OFF_NUM;
typedef union {
    struct {
        unsigned int sao_lcu_cnt : 18 ;
        unsigned int Reserved_602 : 14 ;
    } bits;
    unsigned int u32;
} U_FUNC_SAO_LCU_CNT;
typedef union {
    struct {
        unsigned int pmv_cnt_lcu_done : 8 ;
        unsigned int pmv_cnt_lcu_start : 8 ;
        unsigned int cnt_frame : 16 ;
    } bits;
    unsigned int u32;
} U_PMV_CNT_FRAME;
typedef union {
    struct {
        unsigned int PMV_TMV_0_ver : 12 ;
        unsigned int reserved_0 : 4 ;
        unsigned int PMV_TMV_0_hor : 13 ;
        unsigned int PMV_TMV_0_vld : 1 ;
        unsigned int reserved_1 : 2 ;
    } bits;
    unsigned int u32;
} U_PMV_TMV_0;
typedef union {
    struct {
        unsigned int PMV_TMV_1_ver : 12 ;
        unsigned int reserved_0 : 4 ;
        unsigned int PMV_TMV_1_hor : 13 ;
        unsigned int PMV_TMV_1_vld : 1 ;
        unsigned int reserved_1 : 2 ;
    } bits;
    unsigned int u32;
} U_PMV_TMV_1;
typedef union {
    struct {
        unsigned int PMV_TMV_2_ver : 12 ;
        unsigned int reserved_0 : 4 ;
        unsigned int PMV_TMV_2_hor : 13 ;
        unsigned int PMV_TMV_2_vld : 1 ;
        unsigned int reserved_1 : 2 ;
    } bits;
    unsigned int u32;
} U_PMV_TMV_2;
typedef union {
    struct {
        unsigned int PMV_TMV_3_ver : 12 ;
        unsigned int reserved_0 : 4 ;
        unsigned int PMV_TMV_3_hor : 13 ;
        unsigned int PMV_TMV_3_vld : 1 ;
        unsigned int reserved_1 : 2 ;
    } bits;
    unsigned int u32;
} U_PMV_TMV_3;
typedef union {
    struct {
        unsigned int PMV_TMV_4_ver : 12 ;
        unsigned int reserved_0 : 4 ;
        unsigned int PMV_TMV_4_hor : 13 ;
        unsigned int PMV_TMV_4_vld : 1 ;
        unsigned int reserved_1 : 2 ;
    } bits;
    unsigned int u32;
} U_PMV_TMV_4;
typedef union {
    struct {
        unsigned int PMV_TMV_5_ver : 12 ;
        unsigned int reserved_0 : 4 ;
        unsigned int PMV_TMV_5_hor : 13 ;
        unsigned int PMV_TMV_5_vld : 1 ;
        unsigned int reserved_1 : 2 ;
    } bits;
    unsigned int u32;
} U_PMV_TMV_5;
typedef union {
    struct {
        unsigned int glb_scr : 1 ;
        unsigned int Reserved_606 : 31 ;
    } bits;
    unsigned int u32;
} U_MMU_PRE_GLB_SCR;
typedef union {
    struct {
        unsigned int dfx_arerr_ar_flag : 1 ;
        unsigned int Reserved_609 : 31 ;
    } bits;
    unsigned int u32;
} U_MMU_PRE_DFX_ARERR_FLAG;
typedef union {
    struct {
        unsigned int dfx_err_ar_id : 5 ;
        unsigned int Reserved_610 : 27 ;
    } bits;
    unsigned int u32;
} U_MMU_PRE_DFX_ARERR_ID;
typedef union {
    struct {
        unsigned int dfx_arerr_aw_flag : 1 ;
        unsigned int Reserved_612 : 31 ;
    } bits;
    unsigned int u32;
} U_MMU_PRE_DFX_AWERR_FLAG;
typedef union {
    struct {
        unsigned int dfx_err_aw_id : 5 ;
        unsigned int Reserved_613 : 27 ;
    } bits;
    unsigned int u32;
} U_MMU_PRE_DFX_AWERR_ID;
typedef union {
    struct {
        unsigned int dfx_ar_r_err : 1 ;
        unsigned int dfx_aw_w_err : 1 ;
        unsigned int dfx_aw_b_err : 1 ;
        unsigned int dfx_arid_err : 1 ;
        unsigned int dfx_rid_err : 1 ;
        unsigned int dfx_awid_err : 1 ;
        unsigned int dfx_wid_err : 1 ;
        unsigned int dfx_bid_err : 1 ;
        unsigned int dfx_arid_tx_err : 1 ;
        unsigned int dfx_rid_rx_err : 1 ;
        unsigned int dfx_awid_tx_err : 1 ;
        unsigned int dfx_bid_rx_err : 1 ;
        unsigned int dfx_arid_len_err : 1 ;
        unsigned int dfx_awid_len : 1 ;
        unsigned int dfx_rresp_err : 1 ;
        unsigned int dfx_bresp_err : 1 ;
        unsigned int dfx_ar_ovr_err : 1 ;
        unsigned int dfx_r_ovr_err : 1 ;
        unsigned int dfx_aw_ovr_err : 1 ;
        unsigned int dfx_w_ovr_err : 1 ;
        unsigned int dfx_b_ovr_err : 1 ;
        unsigned int dfx_ar_outstanding_err : 1 ;
        unsigned int dfx_aw_outstanding_err : 1 ;
        unsigned int dfx_arlen_err : 1 ;
        unsigned int dfx_awlen_err : 1 ;
        unsigned int Reserved_615 : 7 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR;
typedef union {
    struct {
        unsigned int ar_r_cnt : 7 ;
        unsigned int Reserved_617 : 25 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_AR_R_CNT;
typedef union {
    struct {
        unsigned int aw_w_cnt : 6 ;
        unsigned int Reserved_618 : 26 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_AW_W_CNT;
typedef union {
    struct {
        unsigned int aw_b_cnt : 6 ;
        unsigned int Reserved_619 : 26 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_AW_B_CNT;
typedef union {
    struct {
        unsigned int dfx_arid_err : 1 ;
        unsigned int Reserved_622 : 3 ;
        unsigned int dfx_rid_err : 1 ;
        unsigned int Reserved_621 : 27 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_AR_R_ID_ERR;
typedef union {
    struct {
        unsigned int dfx_err_arid : 7 ;
        unsigned int Reserved_623 : 25 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_ARID;
typedef union {
    struct {
        unsigned int dfx_err_rid : 7 ;
        unsigned int Reserved_624 : 25 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_RID;
typedef union {
    struct {
        unsigned int dfx_awid_err : 1 ;
        unsigned int Reserved_628 : 3 ;
        unsigned int dfx_wid_err : 1 ;
        unsigned int Reserved_627 : 3 ;
        unsigned int dfx_bid_err : 1 ;
        unsigned int Reserved_626 : 23 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_AW_W_B_ID_ERR;
typedef union {
    struct {
        unsigned int dfx_err_awid : 6 ;
        unsigned int Reserved_629 : 26 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_AWID;
typedef union {
    struct {
        unsigned int dfx_err_wid : 6 ;
        unsigned int Reserved_630 : 26 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_WID;
typedef union {
    struct {
        unsigned int dfx_err_bid : 6 ;
        unsigned int Reserved_631 : 26 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_BID;
typedef union {
    struct {
        unsigned int dfx_arid0_tx_err : 1 ;
        unsigned int dfx_arid1_tx_err : 1 ;
        unsigned int dfx_arid2_tx_err : 1 ;
        unsigned int dfx_arid3_tx_err : 1 ;
        unsigned int dfx_arid4_tx_err : 1 ;
        unsigned int dfx_arid5_tx_err : 1 ;
        unsigned int dfx_arid6_tx_err : 1 ;
        unsigned int dfx_arid7_tx_err : 1 ;
        unsigned int dfx_arid8_tx_err : 1 ;
        unsigned int dfx_arid9_tx_err : 1 ;
        unsigned int dfx_arid10_tx_err : 1 ;
        unsigned int dfx_arid11_tx_err : 1 ;
        unsigned int dfx_arid12_tx_err : 1 ;
        unsigned int dfx_arid13_tx_err : 1 ;
        unsigned int dfx_arid14_tx_err : 1 ;
        unsigned int dfx_arid15_tx_err : 1 ;
        unsigned int dfx_arid16_tx_err : 1 ;
        unsigned int dfx_arid17_tx_err : 1 ;
        unsigned int dfx_arid18_tx_err : 1 ;
        unsigned int dfx_arid19_tx_err : 1 ;
        unsigned int dfx_arid20_tx_err : 1 ;
        unsigned int dfx_arid21_tx_err : 1 ;
        unsigned int dfx_arid22_tx_err : 1 ;
        unsigned int dfx_arid23_tx_err : 1 ;
        unsigned int dfx_arid24_tx_err : 1 ;
        unsigned int dfx_arid25_tx_err : 1 ;
        unsigned int dfx_arid26_tx_err : 1 ;
        unsigned int dfx_arid27_tx_err : 1 ;
        unsigned int dfx_arid28_tx_err : 1 ;
        unsigned int dfx_arid29_tx_err : 1 ;
        unsigned int dfx_arid30_tx_err : 1 ;
        unsigned int dfx_arid31_tx_err : 1 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_TX_0ERR;
typedef union {
    struct {
        unsigned int dfx_arid32_tx_err : 1 ;
        unsigned int dfx_arid33_tx_err : 1 ;
        unsigned int dfx_arid34_tx_err : 1 ;
        unsigned int dfx_arid35_tx_err : 1 ;
        unsigned int dfx_arid36_tx_err : 1 ;
        unsigned int dfx_arid37_tx_err : 1 ;
        unsigned int dfx_arid38_tx_err : 1 ;
        unsigned int dfx_arid39_tx_err : 1 ;
        unsigned int dfx_arid40_tx_err : 1 ;
        unsigned int dfx_arid41_tx_err : 1 ;
        unsigned int dfx_arid42_tx_err : 1 ;
        unsigned int dfx_arid43_tx_err : 1 ;
        unsigned int dfx_arid44_tx_err : 1 ;
        unsigned int dfx_arid45_tx_err : 1 ;
        unsigned int dfx_arid46_tx_err : 1 ;
        unsigned int dfx_arid47_tx_err : 1 ;
        unsigned int dfx_arid48_tx_err : 1 ;
        unsigned int dfx_arid49_tx_err : 1 ;
        unsigned int dfx_arid50_tx_err : 1 ;
        unsigned int dfx_arid51_tx_err : 1 ;
        unsigned int dfx_arid52_tx_err : 1 ;
        unsigned int dfx_arid53_tx_err : 1 ;
        unsigned int dfx_arid54_tx_err : 1 ;
        unsigned int dfx_arid55_tx_err : 1 ;
        unsigned int dfx_arid56_tx_err : 1 ;
        unsigned int dfx_arid57_tx_err : 1 ;
        unsigned int dfx_arid58_tx_err : 1 ;
        unsigned int dfx_arid59_tx_err : 1 ;
        unsigned int dfx_arid60_tx_err : 1 ;
        unsigned int dfx_arid61_tx_err : 1 ;
        unsigned int dfx_arid62_tx_err : 1 ;
        unsigned int dfx_arid63_tx_err : 1 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_TX_1ERR;
typedef union {
    struct {
        unsigned int dfx_arid64_tx_err : 1 ;
        unsigned int dfx_arid65_tx_err : 1 ;
        unsigned int dfx_arid66_tx_err : 1 ;
        unsigned int dfx_arid67_tx_err : 1 ;
        unsigned int Reserved_632 : 28 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_TX_2ERR;
typedef union {
    struct {
        unsigned int dfx_rid0_rx_err : 1 ;
        unsigned int dfx_rid1_rx_err : 1 ;
        unsigned int dfx_rid2_rx_err : 1 ;
        unsigned int dfx_rid3_rx_err : 1 ;
        unsigned int dfx_rid4_rx_err : 1 ;
        unsigned int dfx_rid5_rx_err : 1 ;
        unsigned int dfx_rid6_rx_err : 1 ;
        unsigned int dfx_rid7_rx_err : 1 ;
        unsigned int dfx_rid8_rx_err : 1 ;
        unsigned int dfx_rid9_rx_err : 1 ;
        unsigned int dfx_rid10_rx_err : 1 ;
        unsigned int dfx_rid11_rx_err : 1 ;
        unsigned int dfx_rid12_rx_err : 1 ;
        unsigned int dfx_rid13_rx_err : 1 ;
        unsigned int dfx_rid14_rx_err : 1 ;
        unsigned int dfx_rid15_rx_err : 1 ;
        unsigned int dfx_rid16_rx_err : 1 ;
        unsigned int dfx_rid17_rx_err : 1 ;
        unsigned int dfx_rid18_rx_err : 1 ;
        unsigned int dfx_rid19_rx_err : 1 ;
        unsigned int dfx_rid20_rx_err : 1 ;
        unsigned int dfx_rid21_rx_err : 1 ;
        unsigned int dfx_rid22_rx_err : 1 ;
        unsigned int dfx_rid23_rx_err : 1 ;
        unsigned int dfx_rid24_rx_err : 1 ;
        unsigned int dfx_rid25_rx_err : 1 ;
        unsigned int dfx_rid26_rx_err : 1 ;
        unsigned int dfx_rid27_rx_err : 1 ;
        unsigned int dfx_rid28_rx_err : 1 ;
        unsigned int dfx_rid29_rx_err : 1 ;
        unsigned int dfx_rid30_rx_err : 1 ;
        unsigned int dfx_rid31_rx_err : 1 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_RID_RX_0ERR;
typedef union {
    struct {
        unsigned int dfx_rid32_rx_err : 1 ;
        unsigned int dfx_rid33_rx_err : 1 ;
        unsigned int dfx_rid34_rx_err : 1 ;
        unsigned int dfx_rid35_rx_err : 1 ;
        unsigned int dfx_rid36_rx_err : 1 ;
        unsigned int dfx_rid37_rx_err : 1 ;
        unsigned int dfx_rid38_rx_err : 1 ;
        unsigned int dfx_rid39_rx_err : 1 ;
        unsigned int dfx_rid40_rx_err : 1 ;
        unsigned int dfx_rid41_rx_err : 1 ;
        unsigned int dfx_rid42_rx_err : 1 ;
        unsigned int dfx_rid43_rx_err : 1 ;
        unsigned int dfx_rid44_rx_err : 1 ;
        unsigned int dfx_rid45_rx_err : 1 ;
        unsigned int dfx_rid46_rx_err : 1 ;
        unsigned int dfx_rid47_rx_err : 1 ;
        unsigned int dfx_rid48_rx_err : 1 ;
        unsigned int dfx_rid49_rx_err : 1 ;
        unsigned int dfx_rid50_rx_err : 1 ;
        unsigned int dfx_rid51_rx_err : 1 ;
        unsigned int dfx_rid52_rx_err : 1 ;
        unsigned int dfx_rid53_rx_err : 1 ;
        unsigned int dfx_rid54_rx_err : 1 ;
        unsigned int dfx_rid55_rx_err : 1 ;
        unsigned int dfx_rid56_rx_err : 1 ;
        unsigned int dfx_rid57_rx_err : 1 ;
        unsigned int dfx_rid58_rx_err : 1 ;
        unsigned int dfx_rid59_rx_err : 1 ;
        unsigned int dfx_rid60_rx_err : 1 ;
        unsigned int dfx_rid61_rx_err : 1 ;
        unsigned int dfx_rid62_rx_err : 1 ;
        unsigned int dfx_rid63_rx_err : 1 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_RID_RX_1ERR;
typedef union {
    struct {
        unsigned int dfx_rid64_rx_err : 1 ;
        unsigned int dfx_rid65_rx_err : 1 ;
        unsigned int dfx_rid66_rx_err : 1 ;
        unsigned int dfx_rid67_rx_err : 1 ;
        unsigned int Reserved_634 : 28 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_RID_RX_2ERR;
typedef union {
    struct {
        unsigned int dfx_awid0_rx_err : 1 ;
        unsigned int dfx_awid1_rx_err : 1 ;
        unsigned int dfx_awid2_rx_err : 1 ;
        unsigned int dfx_awid3_rx_err : 1 ;
        unsigned int dfx_awid4_rx_err : 1 ;
        unsigned int dfx_awid5_rx_err : 1 ;
        unsigned int dfx_awid6_rx_err : 1 ;
        unsigned int dfx_awid7_rx_err : 1 ;
        unsigned int Reserved_636 : 24 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_RX_0ERR;
typedef union {
    struct {
        unsigned int dfx_bid0_rx_err : 1 ;
        unsigned int dfx_bid1_rx_err : 1 ;
        unsigned int dfx_bid2_rx_err : 1 ;
        unsigned int dfx_bid3_rx_err : 1 ;
        unsigned int dfx_bid4_rx_err : 1 ;
        unsigned int dfx_bid5_rx_err : 1 ;
        unsigned int dfx_bid6_rx_err : 1 ;
        unsigned int dfx_bid7_rx_err : 1 ;
        unsigned int Reserved_637 : 24 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_BID_RX_ERR;
typedef union {
    struct {
        unsigned int dfx_arid0_len_err : 1 ;
        unsigned int dfx_arid1_len_err : 1 ;
        unsigned int dfx_arid2_len_err : 1 ;
        unsigned int dfx_arid3_len_err : 1 ;
        unsigned int dfx_arid4_len_err : 1 ;
        unsigned int dfx_arid5_len_err : 1 ;
        unsigned int dfx_arid6_len_err : 1 ;
        unsigned int dfx_arid7_len_err : 1 ;
        unsigned int dfx_arid8_len_err : 1 ;
        unsigned int dfx_arid9_len_err : 1 ;
        unsigned int dfx_arid10_len_err : 1 ;
        unsigned int dfx_arid11_len_err : 1 ;
        unsigned int dfx_arid12_len_err : 1 ;
        unsigned int dfx_arid13_len_err : 1 ;
        unsigned int dfx_arid14_len_err : 1 ;
        unsigned int dfx_arid15_len_err : 1 ;
        unsigned int dfx_arid16_len_err : 1 ;
        unsigned int dfx_arid17_len_err : 1 ;
        unsigned int dfx_arid18_len_err : 1 ;
        unsigned int dfx_arid19_len_err : 1 ;
        unsigned int dfx_arid20_len_err : 1 ;
        unsigned int dfx_arid21_len_err : 1 ;
        unsigned int dfx_arid22_len_err : 1 ;
        unsigned int dfx_arid23_len_err : 1 ;
        unsigned int dfx_arid24_len_err : 1 ;
        unsigned int dfx_arid25_len_err : 1 ;
        unsigned int dfx_arid26_len_err : 1 ;
        unsigned int dfx_arid27_len_err : 1 ;
        unsigned int dfx_arid28_len_err : 1 ;
        unsigned int dfx_arid29_len_err : 1 ;
        unsigned int dfx_arid30_len_err : 1 ;
        unsigned int dfx_arid31_len_err : 1 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_LEN_0ERR;
typedef union {
    struct {
        unsigned int dfx_arid32_len_err : 1 ;
        unsigned int dfx_arid33_len_err : 1 ;
        unsigned int dfx_arid34_len_err : 1 ;
        unsigned int dfx_arid35_len_err : 1 ;
        unsigned int dfx_arid36_len_err : 1 ;
        unsigned int dfx_arid37_len_err : 1 ;
        unsigned int dfx_arid38_len_err : 1 ;
        unsigned int dfx_arid39_len_err : 1 ;
        unsigned int dfx_arid40_len_err : 1 ;
        unsigned int dfx_arid41_len_err : 1 ;
        unsigned int dfx_arid42_len_err : 1 ;
        unsigned int dfx_arid43_len_err : 1 ;
        unsigned int dfx_arid44_len_err : 1 ;
        unsigned int dfx_arid45_len_err : 1 ;
        unsigned int dfx_arid46_len_err : 1 ;
        unsigned int dfx_arid47_len_err : 1 ;
        unsigned int dfx_arid48_len_err : 1 ;
        unsigned int dfx_arid49_len_err : 1 ;
        unsigned int dfx_arid50_len_err : 1 ;
        unsigned int dfx_arid51_len_err : 1 ;
        unsigned int dfx_arid52_len_err : 1 ;
        unsigned int dfx_arid53_len_err : 1 ;
        unsigned int dfx_arid54_len_err : 1 ;
        unsigned int dfx_arid55_len_err : 1 ;
        unsigned int dfx_arid56_len_err : 1 ;
        unsigned int dfx_arid57_len_err : 1 ;
        unsigned int dfx_arid58_len_err : 1 ;
        unsigned int dfx_arid59_len_err : 1 ;
        unsigned int dfx_arid60_len_err : 1 ;
        unsigned int dfx_arid61_len_err : 1 ;
        unsigned int dfx_arid62_len_err : 1 ;
        unsigned int dfx_arid63_len_err : 1 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_LEN_1ERR;
typedef union {
    struct {
        unsigned int dfx_arid64_len_err : 1 ;
        unsigned int dfx_arid65_len_err : 1 ;
        unsigned int dfx_arid66_len_err : 1 ;
        unsigned int dfx_arid67_len_err : 1 ;
        unsigned int Reserved_639 : 28 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ARID_LEN_2ERR;
typedef union {
    struct {
        unsigned int dfx_rresp_err : 1 ;
        unsigned int Reserved_643 : 3 ;
        unsigned int dfx_bresp_err : 1 ;
        unsigned int Reserved_642 : 27 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_RESP_ERR;
typedef union {
    struct {
        unsigned int dfx_err_rresp : 2 ;
        unsigned int dfx_err_bresp : 2 ;
        unsigned int Reserved_644 : 28 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_RESP;
typedef union {
    struct {
        unsigned int dfx_arlen_err : 1 ;
        unsigned int Reserved_646 : 3 ;
        unsigned int dfx_awlen_err : 1 ;
        unsigned int Reserved_645 : 27 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_LEN_ERR;
typedef union {
    struct {
        unsigned int dfx_err_arlen : 4 ;
        unsigned int dfx_err_awlen : 4 ;
        unsigned int Reserved_647 : 24 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_ERR_LEN;
typedef union {
    struct {
        unsigned int dfx_2rid_flag : 4 ;
        unsigned int Reserved_648 : 28 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_2RID_FLAG;
typedef union {
    struct {
        unsigned int dfx_wid_flag : 8 ;
        unsigned int Reserved_649 : 24 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_WID_FLAG;
typedef union {
    struct {
        unsigned int arvalid : 1 ;
        unsigned int arready : 1 ;
        unsigned int rvalid : 1 ;
        unsigned int rready : 1 ;
        unsigned int awvalid : 1 ;
        unsigned int awready : 1 ;
        unsigned int wvalid : 1 ;
        unsigned int wready : 1 ;
        unsigned int bvalid : 1 ;
        unsigned int bready : 1 ;
        unsigned int Reserved_650 : 22 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_AXI_ST;
typedef union {
    struct {
        unsigned int axi_soft_rst_req : 1 ;
        unsigned int Reserved_652 : 31 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_SOFT_RST_REQ;
typedef union {
    struct {
        unsigned int axi_soft_rst_ack : 1 ;
        unsigned int Reserved_653 : 31 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_SOFT_RST_ACK;
typedef union {
    struct {
        unsigned int axi_soft_rst_force_req_ack : 1 ;
        unsigned int Reserved_655 : 31 ;
    } bits;
    unsigned int u32;
} U_AXIDFX_SOFT_RST_FORCE_REQ_ACK;
typedef union {
    struct {
        unsigned int glb_bypass : 1 ;
        unsigned int Reserved_658 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_GLB_BYPASS;
typedef union {
    struct {
        unsigned int debug_mode : 1 ;
        unsigned int axilock_en : 1 ;
        unsigned int Reserved_659 : 30 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_DEBUG_MODE;
typedef union {
    struct {
        unsigned int mem_ctrl_bp_d1w2r : 16 ;
        unsigned int mem_ctrl_d1w2r : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_MEM_CTRL;
typedef union {
    struct {
        unsigned int apb_clk_en : 2 ;
        unsigned int core_clk_en : 2 ;
        unsigned int Reserved_660 : 28 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_CLK_EN;
typedef union {
    struct {
        unsigned int end_req_2 : 24 ;
        unsigned int Reserved_661 : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_END_REQ_2;
typedef union {
    struct {
        unsigned int end_ack_2 : 24 ;
        unsigned int Reserved_662 : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_END_ACK_2;
typedef union {
    struct {
        unsigned int stream_start_2 : 24 ;
        unsigned int Reserved_663 : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_SMRX_START_2;
typedef union {
    struct {
        unsigned int smr_start_sel : 1 ;
        unsigned int end_req_sel : 1 ;
        unsigned int Reserved_664 : 30 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_INPT_SEL;
typedef union {
    struct {
        unsigned int rd_va_err0_msk : 1 ;
        unsigned int rd_va_err1_msk : 1 ;
        unsigned int wr_va_err0_msk : 1 ;
        unsigned int wr_va_err1_msk : 1 ;
        unsigned int wdata_burst_msk : 1 ;
        unsigned int Reserved_666 : 27 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_INTMASK;
typedef union {
    struct {
        unsigned int rd_va_err0_raw : 1 ;
        unsigned int rd_va_err1_raw : 1 ;
        unsigned int wr_va_err0_raw : 1 ;
        unsigned int wr_va_err1_raw : 1 ;
        unsigned int wdata_burst_raw : 1 ;
        unsigned int Reserved_667 : 27 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_INTRAW;
typedef union {
    struct {
        unsigned int rd_va_err0_stat : 1 ;
        unsigned int rd_va_err1_stat : 1 ;
        unsigned int wr_va_err0_stat : 1 ;
        unsigned int wr_va_err1_stat : 1 ;
        unsigned int wdata_burst_stat : 1 ;
        unsigned int Reserved_668 : 27 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_INTSTAT;
typedef union {
    struct {
        unsigned int rd_va_err0_clr : 1 ;
        unsigned int rd_va_err1_clr : 1 ;
        unsigned int wr_va_err0_clr : 1 ;
        unsigned int wr_va_err1_clr : 1 ;
        unsigned int wdata_burst_clr : 1 ;
        unsigned int Reserved_669 : 27 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_INTCLR;
typedef union {
    struct {
        unsigned int rd_sid : 8 ;
        unsigned int rd_addr_msb : 4 ;
        unsigned int Reserved_670 : 20 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_DBG_0;
typedef union {
    struct {
        unsigned int wr_sid : 8 ;
        unsigned int wr_addr_msb : 4 ;
        unsigned int Reserved_671 : 20 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_DBG_2;
typedef union {
    struct {
        unsigned int awid : 8 ;
        unsigned int awlen : 4 ;
        unsigned int awaddr_msb : 4 ;
        unsigned int wid : 8 ;
        unsigned int wdata_len : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_DBG_4;
typedef union {
    struct {
        unsigned int dbg_cfg_addr : 16 ;
        unsigned int dbg_cfg_cs : 1 ;
        unsigned int dbg_cfg_wr : 1 ;
        unsigned int Reserved_673 : 14 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_DBG_PORT_IN_0;
typedef union {
    struct {
        unsigned int bypass : 1 ;
        unsigned int Reserved_676 : 3 ;
        unsigned int upwin : 8 ;
        unsigned int len : 8 ;
        unsigned int Reserved_675 : 12 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_SMRX_0;
typedef union {
    struct {
        unsigned int va_str : 21 ;
        unsigned int Reserved_677 : 11 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_SMRX_1;
typedef union {
    struct {
        unsigned int va_end : 21 ;
        unsigned int Reserved_678 : 11 ;
    } bits;
    unsigned int u32;
} U_SMMU_MSTR_SMRX_2;
typedef union {
    struct {
        unsigned int rd_cmd_max_latency : 16 ;
        unsigned int rd_cmd_avg_latency : 16 ;
    } bits;
    unsigned int u32;
} U_RD_CMD_TRANS_LATENCY;
typedef union {
    struct {
        unsigned int wr_cmd_max_latency : 16 ;
        unsigned int wr_cmd_avg_latency : 16 ;
    } bits;
    unsigned int u32;
} U_WR_CMD_TRANS_LATENCY;
typedef union {
    struct {
        unsigned int glb_bypass : 1 ;
        unsigned int rqos_en : 1 ;
        unsigned int wqos_en : 1 ;
        unsigned int glb_alloc_en : 1 ;
        unsigned int Reserved_682 : 2 ;
        unsigned int rqos : 4 ;
        unsigned int wqos : 4 ;
        unsigned int Reserved_681 : 1 ;
        unsigned int smr_rd_shadow : 1 ;
        unsigned int ptw_pf : 4 ;
        unsigned int ptw_mid : 6 ;
        unsigned int ctx_racfg_ns : 2 ;
        unsigned int ctx_wacfg_ns : 2 ;
        unsigned int Reserved_680 : 2 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCR;
typedef union {
    struct {
        unsigned int mem_ctrl_s : 26 ;
        unsigned int Reserved_683 : 6 ;
    } bits;
    unsigned int u32;
} U_SMMU_MEMCTRL;
typedef union {
    struct {
        unsigned int auto_clk_gt_en : 2 ;
        unsigned int Reserved_684 : 30 ;
    } bits;
    unsigned int u32;
} U_SMMU_LP_CTRL;
typedef union {
    struct {
        unsigned int intns_permis_msk : 1 ;
        unsigned int intns_ext_msk : 1 ;
        unsigned int intns_tlbmiss_msk : 1 ;
        unsigned int intns_ptw_trans_msk : 1 ;
        unsigned int intns_ptw_invalid_msk : 1 ;
        unsigned int intns_ptw_ns_msk : 1 ;
        unsigned int Reserved_685 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTMASK_NS;
typedef union {
    struct {
        unsigned int intns_permis_raw : 1 ;
        unsigned int intns_ext_raw : 1 ;
        unsigned int intns_tlbmiss_raw : 1 ;
        unsigned int intns_ptw_trans_raw : 1 ;
        unsigned int intns_ptw_invalid_raw : 1 ;
        unsigned int intns_ptw_ns_raw : 1 ;
        unsigned int Reserved_686 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTRAW_NS;
typedef union {
    struct {
        unsigned int intns_permis_stat : 1 ;
        unsigned int intns_ext_stat : 1 ;
        unsigned int intns_tlbmiss_stat : 1 ;
        unsigned int intns_ptw_trans_stat : 1 ;
        unsigned int intns_ptw_invalid_stat : 1 ;
        unsigned int intns_ptw_ns_stat : 1 ;
        unsigned int Reserved_687 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTSTAT_NS;
typedef union {
    struct {
        unsigned int intns_permis_clr : 1 ;
        unsigned int intns_ext_clr : 1 ;
        unsigned int intns_tlbmiss_clr : 1 ;
        unsigned int intns_ptw_trans_clr : 1 ;
        unsigned int intns_ptw_invalid_clr : 1 ;
        unsigned int intns_ptw_ns_clr : 1 ;
        unsigned int Reserved_688 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTCLR_NS;
typedef union {
    struct {
        unsigned int smr_bypass : 1 ;
        unsigned int ptw_racfg_ns : 1 ;
        unsigned int smr_ptw_qos : 2 ;
        unsigned int smr_invld_en : 1 ;
        unsigned int tbu_racfg_ns : 2 ;
        unsigned int tbu_wacfg_ns : 2 ;
        unsigned int tbu_alloc_en_ns : 1 ;
        unsigned int tbu_rptl_as_ful_ns : 1 ;
        unsigned int tbu_wptl_as_ful_ns : 1 ;
        unsigned int smr_pa_msb_ns : 16 ;
        unsigned int smr_pa_msb_en_ns : 2 ;
        unsigned int Reserved_689 : 2 ;
    } bits;
    unsigned int u32;
} U_SMMU_SMRX_NS;
typedef union {
    struct {
        unsigned int smr_rld_en2 : 24 ;
        unsigned int Reserved_690 : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_RLD_EN2_NS;
typedef union {
    struct {
        unsigned int glb_alloc_finish : 1 ;
        unsigned int Reserved_691 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_GLB_ALLOC_ST;
typedef union {
    struct {
        unsigned int cb_bypass : 1 ;
        unsigned int Reserved_692 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_CB_SCTRL;
typedef union {
    struct {
        unsigned int cb_ttbcr_des : 1 ;
        unsigned int cb_ttbcr_t0sz : 3 ;
        unsigned int cb_ttbcr_n : 3 ;
        unsigned int Reserved_694 : 9 ;
        unsigned int cb_ttbcr_t1sz : 3 ;
        unsigned int Reserved_693 : 13 ;
    } bits;
    unsigned int u32;
} U_SMMU_CB_TTBCR;
typedef union {
    struct {
        unsigned int cache_all_invalid : 1 ;
        unsigned int cache_all_level : 2 ;
        unsigned int Reserved_695 : 29 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCACHEI_ALL;
typedef union {
    struct {
        unsigned int cache_l1_invalid : 1 ;
        unsigned int cache_l1_security : 2 ;
        unsigned int Reserved_696 : 29 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCACHEI_L1;
typedef union {
    struct {
        unsigned int cache_l2_invalid : 1 ;
        unsigned int cache_l2_strmid : 15 ;
        unsigned int Reserved_697 : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCACHEI_L2;
typedef union {
    struct {
        unsigned int cb_pa_msb : 16 ;
        unsigned int cb_pa_msb_en : 1 ;
        unsigned int Reserved_698 : 15 ;
    } bits;
    unsigned int u32;
} U_SMMU_CB_PA_MSB;
typedef union {
    struct {
        unsigned int cb_ttbr_msb : 16 ;
        unsigned int Reserved_699 : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_CB_TTBR_MSB;
typedef union {
    struct {
        unsigned int err_rd_addr_msb_ns : 16 ;
        unsigned int err_wr_addr_msb_ns : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_ERR_ADDR_MSB_NS;
typedef union {
    struct {
        unsigned int fault_index_id_tcu : 16 ;
        unsigned int fault_strm_id_tcu : 12 ;
        unsigned int fault_addr_tcu_msb : 4 ;
    } bits;
    unsigned int u32;
} U_SMMU_FAULT_ID_TCU;
typedef union {
    struct {
        unsigned int fault_index_id_tbu : 16 ;
        unsigned int fault_strm_id_tbu : 12 ;
        unsigned int fault_addr_tbu_msb : 4 ;
    } bits;
    unsigned int u32;
} U_SMMU_FAULT_ID_TBUX;
typedef union {
    struct {
        unsigned int fault_tlbmiss_err_tbu : 2 ;
        unsigned int fault_permis_err_tbu : 3 ;
        unsigned int fautl_ext_err_tbu : 2 ;
        unsigned int fault_ext_err_id_tbu : 9 ;
        unsigned int Reserved_700 : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_FAULT_INFOX;
typedef union {
    struct {
        unsigned int smr_nscfg : 1 ;
        unsigned int smr_nscfg_en : 1 ;
        unsigned int smr_bypass_s : 1 ;
        unsigned int ptw_mid_sel_s : 1 ;
        unsigned int Reserved_701 : 1 ;
        unsigned int smr_mid_en_s : 1 ;
        unsigned int smr_mid_s : 6 ;
        unsigned int smr_pa_msb_s : 16 ;
        unsigned int smr_pa_msb_en_s : 2 ;
        unsigned int Reserved_702 : 2 ;
    } bits;
    unsigned int u32;
} U_SMMU_SMRX_S;
typedef union {
    struct {
        unsigned int smr_rld_en2_s : 24 ;
        unsigned int Reserved_703 : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_RLD_EN2_S;
typedef union {
    struct {
        unsigned int ints_permis_msk : 1 ;
        unsigned int ints_ext_msk : 1 ;
        unsigned int ints_tlbmiss_msk : 1 ;
        unsigned int ints_ptw_trans_msk : 1 ;
        unsigned int ints_ptw_invalid_msk : 1 ;
        unsigned int ints_ptw_ns_msk : 1 ;
        unsigned int Reserved_704 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTMAS_S;
typedef union {
    struct {
        unsigned int ints_permis_raw : 1 ;
        unsigned int ints_ext_raw : 1 ;
        unsigned int ints_tlbmiss_raw : 1 ;
        unsigned int ints_ptw_trans_raw : 1 ;
        unsigned int ints_ptw_invalid_raw : 1 ;
        unsigned int ints_ptw_ns_raw : 1 ;
        unsigned int Reserved_705 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTRAW_S;
typedef union {
    struct {
        unsigned int ints_permis_stat : 1 ;
        unsigned int ints_ext_stat : 1 ;
        unsigned int ints_tlbmiss_stat : 1 ;
        unsigned int ints_ptw_trans_stat : 1 ;
        unsigned int ints_ptw_invalid_stat : 1 ;
        unsigned int ints_ptw_ns_stat : 1 ;
        unsigned int Reserved_706 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTSTAT_S;
typedef union {
    struct {
        unsigned int ints_permis_clr : 1 ;
        unsigned int ints_ext_clr : 1 ;
        unsigned int ints_tlbmiss_clr : 1 ;
        unsigned int ints_ptw_trans_clr : 1 ;
        unsigned int ints_ptw_invalid_clr : 1 ;
        unsigned int ints_ptw_ns_clr : 1 ;
        unsigned int Reserved_707 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTCLR_S;
typedef union {
    struct {
        unsigned int glb_nscfg : 2 ;
        unsigned int mid_s : 6 ;
        unsigned int glb_bypass_s : 1 ;
        unsigned int mid_en_s : 1 ;
        unsigned int Reserved_709 : 16 ;
        unsigned int ctx_racfg_s : 2 ;
        unsigned int ctx_wacfg_s : 2 ;
        unsigned int Reserved_708 : 2 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCR_S;
typedef union {
    struct {
        unsigned int scb_bypass : 1 ;
        unsigned int Reserved_710 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCB_SCTRL;
typedef union {
    struct {
        unsigned int scb_ttbcr_des : 1 ;
        unsigned int Reserved_711 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCB_TTBCR;
typedef union {
    struct {
        unsigned int scb_pa_msb : 16 ;
        unsigned int scb_pa_msb_en : 1 ;
        unsigned int Reserved_712 : 15 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCB_PA_MSB;
typedef union {
    struct {
        unsigned int scb_ttbr_msb : 16 ;
        unsigned int Reserved_713 : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCB_TTBR_MSB;
typedef union {
    struct {
        unsigned int err_rd_addr_msb_s : 16 ;
        unsigned int err_wr_addr_msb_s : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_ERR_ADDR_MSB_S;
typedef union {
    struct {
        unsigned int Reserved_716 : 1 ;
        unsigned int ptw_racfg_s : 1 ;
        unsigned int Reserved_715 : 3 ;
        unsigned int tbu_racfg_s : 2 ;
        unsigned int tbu_wacfg_s : 2 ;
        unsigned int tbu_alloc_en_s : 1 ;
        unsigned int tbu_rptl_as_ful_s : 1 ;
        unsigned int tbu_wptl_as_ful_s : 1 ;
        unsigned int Reserved_714 : 20 ;
    } bits;
    unsigned int u32;
} U_SMMU_SMRX_S1;
typedef union {
    struct {
        unsigned int smr_protect_en : 1 ;
        unsigned int ptw_racfg_p : 1 ;
        unsigned int smr_bypass_p : 1 ;
        unsigned int Reserved_718 : 2 ;
        unsigned int tbu_racfg_p : 2 ;
        unsigned int tbu_wacfg_p : 2 ;
        unsigned int tbu_alloc_en_p : 1 ;
        unsigned int tbu_rptl_as_ful_p : 1 ;
        unsigned int tbu_wptl_as_ful_p : 1 ;
        unsigned int smr_pa_msb_p : 16 ;
        unsigned int smr_pa_msb_en_p : 2 ;
        unsigned int Reserved_717 : 2 ;
    } bits;
    unsigned int u32;
} U_SMMU_SMRX_P;
typedef union {
    struct {
        unsigned int smr_rld_en2_p : 24 ;
        unsigned int Reserved_719 : 8 ;
    } bits;
    unsigned int u32;
} U_SMMU_RLD_EN2_P;
typedef union {
    struct {
        unsigned int intp_permis_msk : 1 ;
        unsigned int intp_ext_msk : 1 ;
        unsigned int intp_tlbmiss_msk : 1 ;
        unsigned int intp_ptw_trans_msk : 1 ;
        unsigned int intp_ptw_invalid_msk : 1 ;
        unsigned int intp_ptw_ns_msk : 1 ;
        unsigned int Reserved_720 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTMAS_P;
typedef union {
    struct {
        unsigned int intp_permis_raw : 1 ;
        unsigned int intp_ext_raw : 1 ;
        unsigned int intp_tlbmiss_raw : 1 ;
        unsigned int intp_ptw_trans_raw : 1 ;
        unsigned int intp_ptw_invalid_raw : 1 ;
        unsigned int intp_ptw_ns_raw : 1 ;
        unsigned int Reserved_721 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTRAW_P;
typedef union {
    struct {
        unsigned int intp_permis_stat : 1 ;
        unsigned int intp_ext_stat : 1 ;
        unsigned int intp_tlbmiss_stat : 1 ;
        unsigned int intp_ptw_trans_stat : 1 ;
        unsigned int intp_ptw_invalid_stat : 1 ;
        unsigned int intp_ptw_ns_stat : 1 ;
        unsigned int Reserved_722 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTSTAT_P;
typedef union {
    struct {
        unsigned int intp_permis_clr : 1 ;
        unsigned int intp_ext_clr : 1 ;
        unsigned int intp_tlbmiss_clr : 1 ;
        unsigned int intp_ptw_trans_clr : 1 ;
        unsigned int intp_ptw_invalid_clr : 1 ;
        unsigned int intp_ptw_ns_clr : 1 ;
        unsigned int Reserved_723 : 26 ;
    } bits;
    unsigned int u32;
} U_SMMU_INTCLR_P;
typedef union {
    struct {
        unsigned int glb_prot_cfg : 1 ;
        unsigned int Reserved_736 : 7 ;
        unsigned int glb_bypass_p : 1 ;
        unsigned int Reserved_724 : 17 ;
        unsigned int ctx_racfg_p : 2 ;
        unsigned int ctx_wacfg_p : 2 ;
        unsigned int Reserved_735 : 2 ;
    } bits;
    unsigned int u32;
} U_SMMU_SCR_P;
typedef union {
    struct {
        unsigned int pcb_bypass : 1 ;
        unsigned int Reserved_725 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_PCB_SCTRL;
typedef union {
    struct {
        unsigned int pcb_ttbcr_des : 1 ;
        unsigned int Reserved_726 : 31 ;
    } bits;
    unsigned int u32;
} U_SMMU_PCB_TTBCR;
typedef union {
    struct {
        unsigned int pcb_pa_msb : 16 ;
        unsigned int pcb_pa_msb_en : 1 ;
        unsigned int Reserved_727 : 15 ;
    } bits;
    unsigned int u32;
} U_SMMU_PCB_PA_MSB;
typedef union {
    struct {
        unsigned int pcb_ttbr_msb : 16 ;
        unsigned int Reserved_728 : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_PCB_TTBR_MSB;
typedef union {
    struct {
        unsigned int err_rd_addr_msb_p : 16 ;
        unsigned int err_wr_addr_msb_p : 16 ;
    } bits;
    unsigned int u32;
} U_SMMU_ERR_ADDR_MSB_P;
typedef struct {
    volatile U_VEDU_VCPI_INTMASK VEDU_VCPI_INTMASK;
    volatile U_VEDU_VCPI_INTCLR VEDU_VCPI_INTCLR;
    volatile U_VEDU_VCPI_START VEDU_VCPI_START;
    volatile U_VEDU_VCPI_CNTCLR VEDU_VCPI_CNTCLR;
    volatile unsigned int VEDU_VCPI_FRAMENO;
    volatile U_VEDU_VCPI_BP_POS VEDU_VCPI_BP_POS;
    volatile unsigned int VEDU_VCPI_TIMEOUT;
    volatile U_VEDU_VCPI_MODE VEDU_VCPI_MODE;
    volatile U_VEDU_VCPI_TILE_SIZE VEDU_VCPI_TILE_SIZE;
    volatile U_VEDU_VCPI_PICSIZE_PIX VEDU_VCPI_PICSIZE_PIX;
    volatile U_VEDU_VCPI_MULTISLC VEDU_VCPI_MULTISLC;
    volatile U_VEDU_VCPI_QPCFG VEDU_VCPI_QPCFG;
    volatile U_VEDU_VCPI_DBLKCFG VEDU_VCPI_DBLKCFG;
    volatile U_VEDU_VCPI_LOW_POWER VEDU_VCPI_LOW_POWER;
    volatile U_VEDU_VCPI_OUTSTD VEDU_VCPI_OUTSTD;
    volatile U_VEDU_VCPI_TMV_LOAD VEDU_VCPI_TMV_LOAD;
    volatile U_VEDU_VCPI_CROSS_TILE_SLC VEDU_VCPI_CROSS_TILE_SLC;
    volatile U_VEDU_VCPI_MEM_CTRL VEDU_VCPI_MEM_CTRL;
    volatile U_VEDU_VCPI_INTRA_INTER_CU_EN VEDU_VCPI_INTRA_INTER_CU_EN;
    volatile U_VEDU_VCPI_VLC_CONFIG VEDU_VCPI_VLC_CONFIG;
    volatile U_VEDU_VCPI_PRE_JUDGE_EXT_EN VEDU_VCPI_PRE_JUDGE_EXT_EN;
    volatile U_VEDU_VCPI_PRE_JUDGE_COST_THR VEDU_VCPI_PRE_JUDGE_COST_THR;
    volatile U_VEDU_VCPI_IBLK_PRE_MV_THR VEDU_VCPI_IBLK_PRE_MV_THR;
    volatile U_VEDU_VCPI_PME_PARAM VEDU_VCPI_PME_PARAM;
    volatile U_VEDU_VCPI_PIC_STRONG_EN VEDU_VCPI_PIC_STRONG_EN;
    volatile U_VEDU_VCPI_REF_FLAG VEDU_VCPI_REF_FLAG;
    volatile U_VEDU_VCPI_RC_ENABLE VEDU_VCPI_RC_ENABLE;
    volatile U_VEDU_VCPI_I_SLC_INSERT VEDU_VCPI_I_SLC_INSERT;
    volatile U_VEDU_VCPI_CLKDIV_ENABLE VEDU_VCPI_CLKDIV_ENABLE;
    volatile U_VEDU_VCPI_WCHN_BYPASS VEDU_VCPI_WCHN_BYPASS;
    volatile U_VEDU_VCPI_RCHN_BYPASS VEDU_VCPI_RCHN_BYPASS;
    volatile U_VEDU_VCPI_SW_L0_SIZE VEDU_VCPI_SW_L0_SIZE;
    volatile U_VEDU_VCPI_SW_L1_SIZE VEDU_VCPI_SW_L1_SIZE;
    volatile unsigned int VEDU_VCPI_PMEINFO_ST_ADDR;
    volatile unsigned int VEDU_VCPI_PMEINFO_LD0_ADDR;
    volatile unsigned int VEDU_VCPI_PMEINFO_LD1_ADDR;
    volatile unsigned int VEDU_VCPI_TUNLCELL_ADDR;
    volatile unsigned int VEDU_VCPI_SRC_YADDR;
    volatile unsigned int VEDU_VCPI_SRC_CADDR;
    volatile unsigned int VEDU_VCPI_SRC_VADDR;
    volatile unsigned int VEDU_VCPI_YH_ADDR;
    volatile unsigned int VEDU_VCPI_CH_ADDR;
    volatile U_VEDU_VCPI_STRIDE VEDU_VCPI_STRIDE;
    volatile unsigned int VEDU_VCPI_REC_YADDR;
    volatile unsigned int VEDU_VCPI_REC_CADDR;
    volatile U_VEDU_VCPI_REC_STRIDE VEDU_VCPI_REC_STRIDE;
    volatile unsigned int VEDU_VCPI_REC_YH_ADDR;
    volatile unsigned int VEDU_VCPI_REC_CH_ADDR;
    volatile U_VEDU_VCPI_REC_HEAD_STRIDE VEDU_VCPI_REC_HEAD_STRIDE;
    volatile unsigned int VEDU_VCPI_REFY_L0_ADDR;
    volatile unsigned int VEDU_VCPI_REFC_L0_ADDR;
    volatile U_VEDU_VCPI_REF_L0_STRIDE VEDU_VCPI_REF_L0_STRIDE;
    volatile unsigned int VEDU_VCPI_REFYH_L0_ADDR;
    volatile unsigned int VEDU_VCPI_REFCH_L0_ADDR;
    volatile U_VEDU_VCPI_REFH_L0_STRIDE VEDU_VCPI_REFH_L0_STRIDE;
    volatile unsigned int VEDU_VCPI_PMELD_L0_ADDR;
    volatile unsigned int VEDU_VCPI_REFY_L1_ADDR;
    volatile unsigned int VEDU_VCPI_REFC_L1_ADDR;
    volatile U_VEDU_VCPI_REF_L1_STRIDE VEDU_VCPI_REF_L1_STRIDE;
    volatile unsigned int VEDU_VCPI_REFYH_L1_ADDR;
    volatile unsigned int VEDU_VCPI_REFCH_L1_ADDR;
    volatile U_VEDU_VCPI_REFH_L1_STRIDE VEDU_VCPI_REFH_L1_STRIDE;
    volatile unsigned int VEDU_VCPI_PMELD_L1_ADDR;
    volatile unsigned int VEDU_VCPI_PMEST_ADDR;
    volatile unsigned int VEDU_VCPI_NBI_UPST_ADDR;
    volatile unsigned int VEDU_VCPI_NBI_MVST_ADDR;
    volatile unsigned int VEDU_VCPI_NBI_MVLD_ADDR;
    volatile unsigned int VEDU_VCPI_STRMADDR;
    volatile unsigned int VEDU_VCPI_SWPTRADDR;
    volatile unsigned int VEDU_VCPI_SRPTRADDR;
    volatile unsigned int VEDU_VCPI_LLILD_ADDR;
    volatile U_VEDU_VCPI_STRFMT VEDU_VCPI_STRFMT;
    volatile U_VEDU_VCPI_SCALE_PARA VEDU_VCPI_SCALE_PARA;
    volatile U_VEDU_VCPI_ORI_PICSIZE VEDU_VCPI_ORI_PICSIZE;
    volatile unsigned int VEDU_VCPI_MEM_CTRL_T16_S;
    volatile unsigned int VEDU_VCPI_PMEST_STRIDE;
    volatile unsigned int VEDU_VCPI_PMELD_STRIDE;
    volatile U_VEDU_VCPI_INTMASK_S VEDU_VCPI_INTMASK_S;
    volatile U_VEDU_VCPI_INTCLR_S VEDU_VCPI_INTCLR_S;
    volatile unsigned int RESERVED_VEDU_VCPI0;
    volatile U_VEDU_CURLD_NARROW_THR VEDU_CURLD_NARROW_THR;
    volatile U_VEDU_ARGBTO444_PARAMETER0 VEDU_ARGBTO444_PARAMETER0;
    volatile U_VEDU_ARGBTO444_PARAMETER1 VEDU_ARGBTO444_PARAMETER1;
    volatile U_VEDU_ARGBTO444_PARAMETER2 VEDU_ARGBTO444_PARAMETER2;
    volatile U_VEDU_ARGBTO444_PARAMETER3 VEDU_ARGBTO444_PARAMETER3;
    volatile U_VEDU_ARGBTO444_PARAMETER4 VEDU_ARGBTO444_PARAMETER4;
    volatile U_VEDU_ARGBTO444_PARAMETER5 VEDU_ARGBTO444_PARAMETER5;
    volatile U_VEDU_ARGBTO444_PARAMETER6 VEDU_ARGBTO444_PARAMETER6;
    volatile U_VEDU_444TO422_PARAMETER VEDU_444TO422_PARAMETER;
    volatile U_VEDU_422TO420_PARAMETER VEDU_422TO420_PARAMETER;
    volatile unsigned int RESERVED_CURLD1[6] ;
    volatile unsigned int VEDU_VCPI_MEM_CTRL_T16_T ;
    volatile unsigned int VEDU_VCPI_MEM_CTRL_T16_B ;
    volatile unsigned int RESERVED_VEDU_VCPI[30];
    volatile U_VEDU_VCTRL_ROI_CFG0 VEDU_VCTRL_ROI_CFG0;
    volatile U_VEDU_VCTRL_ROI_CFG1 VEDU_VCTRL_ROI_CFG1;
    volatile U_VEDU_VCTRL_ROI_CFG2 VEDU_VCTRL_ROI_CFG2;
    volatile U_VEDU_VCTRL_ROI_SIZE_0 VEDU_VCTRL_ROI_SIZE_0;
    volatile U_VEDU_VCTRL_ROI_SIZE_1 VEDU_VCTRL_ROI_SIZE_1;
    volatile U_VEDU_VCTRL_ROI_SIZE_2 VEDU_VCTRL_ROI_SIZE_2;
    volatile U_VEDU_VCTRL_ROI_SIZE_3 VEDU_VCTRL_ROI_SIZE_3;
    volatile U_VEDU_VCTRL_ROI_SIZE_4 VEDU_VCTRL_ROI_SIZE_4;
    volatile U_VEDU_VCTRL_ROI_SIZE_5 VEDU_VCTRL_ROI_SIZE_5;
    volatile U_VEDU_VCTRL_ROI_SIZE_6 VEDU_VCTRL_ROI_SIZE_6;
    volatile U_VEDU_VCTRL_ROI_SIZE_7 VEDU_VCTRL_ROI_SIZE_7;
    volatile U_VEDU_VCTRL_ROI_START_0 VEDU_VCTRL_ROI_START_0;
    volatile U_VEDU_VCTRL_ROI_START_1 VEDU_VCTRL_ROI_START_1;
    volatile U_VEDU_VCTRL_ROI_START_2 VEDU_VCTRL_ROI_START_2;
    volatile U_VEDU_VCTRL_ROI_START_3 VEDU_VCTRL_ROI_START_3;
    volatile U_VEDU_VCTRL_ROI_START_4 VEDU_VCTRL_ROI_START_4;
    volatile U_VEDU_VCTRL_ROI_START_5 VEDU_VCTRL_ROI_START_5;
    volatile U_VEDU_VCTRL_ROI_START_6 VEDU_VCTRL_ROI_START_6;
    volatile U_VEDU_VCTRL_ROI_START_7 VEDU_VCTRL_ROI_START_7;
    volatile U_VEDU_VCTRL_LCU_TARGET_BIT VEDU_VCTRL_LCU_TARGET_BIT;
    volatile U_VEDU_VCTRL_NARROW_THRESHOLD VEDU_VCTRL_NARROW_THRESHOLD;
    volatile U_VEDU_VCTRL_LCU_BASELINE VEDU_VCTRL_LCU_BASELINE;
    volatile unsigned int RESERVED_VEDU_VCTRL0;
    volatile U_VEDU_VCTRL_NORM_TR16X16_COEFF_DENOISE VEDU_VCTRL_NORM_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_NORM_COEFF_DENOISE VEDU_VCTRL_NORM_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_NORM_ENG_DENOISE VEDU_VCTRL_NORM_ENG_DENOISE;
    volatile unsigned int RESERVED_VEDU_VCTRL1;
    volatile U_VEDU_VCTRL_SKIN_TR16X16_COEFF_DENOISE VEDU_VCTRL_SKIN_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SKIN_COEFF_DENOISE VEDU_VCTRL_SKIN_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SKIN_ENG_DENOISE VEDU_VCTRL_SKIN_ENG_DENOISE;
    volatile unsigned int RESERVED_VEDU_VCTRL2;
    volatile U_VEDU_VCTRL_HEDGE_TR16X16_COEFF_DENOISE VEDU_VCTRL_HEDGE_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGE_COEFF_DENOISE VEDU_VCTRL_HEDGE_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGE_ENG_DENOISE VEDU_VCTRL_HEDGE_ENG_DENOISE;
    volatile unsigned int RESERVED_VEDU_VCTRL3;
    volatile U_VEDU_VCTRL_HEDGEMOV_TR16X16_COEFF_DENOISE VEDU_VCTRL_HEDGEMOV_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGEMOV_COEFF_DENOISE VEDU_VCTRL_HEDGEMOV_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGEMOV_ENG_DENOISE VEDU_VCTRL_HEDGEMOV_ENG_DENOISE;
    volatile unsigned int RESERVED_VEDU_VCTRL4;
    volatile U_VEDU_VCTRL_STATIC_TR16X16_COEFF_DENOISE VEDU_VCTRL_STATIC_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_STATIC_COEFF_DENOISE VEDU_VCTRL_STATIC_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_STATIC_ENG_DENOISE VEDU_VCTRL_STATIC_ENG_DENOISE;
    volatile unsigned int RESERVED_VEDU_VCTRL5;
    volatile U_VEDU_VCTRL_SOBELSTR_TR16X16_COEFF_DENOISE VEDU_VCTRL_SOBELSTR_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELSTR_COEFF_DENOISE VEDU_VCTRL_SOBELSTR_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELSTR_ENG_DENOISE VEDU_VCTRL_SOBELSTR_ENG_DENOISE;
    volatile unsigned int RESERVED_VEDU_VCTRL6;
    volatile U_VEDU_VCTRL_SOBELWEAK_TR16X16_COEFF_DENOISE VEDU_VCTRL_SOBELWEAK_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELWEAK_COEFF_DENOISE VEDU_VCTRL_SOBELWEAK_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELWEAK_ENG_DENOISE VEDU_VCTRL_SOBELWEAK_ENG_DENOISE;
    volatile U_VEDU_VCTRL_INTRA_RDO_FACTOR_0 VEDU_VCTRL_INTRA_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_INTRA_RDO_FACTOR_1 VEDU_VCTRL_INTRA_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_INTRA_RDO_FACTOR_2 VEDU_VCTRL_INTRA_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_MRG_RDO_FACTOR_0 VEDU_VCTRL_MRG_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_MRG_RDO_FACTOR_1 VEDU_VCTRL_MRG_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_MRG_RDO_FACTOR_2 VEDU_VCTRL_MRG_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_FME_RDO_FACTOR_0 VEDU_VCTRL_FME_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_FME_RDO_FACTOR_1 VEDU_VCTRL_FME_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_FME_RDO_FACTOR_2 VEDU_VCTRL_FME_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_SEL_INTRA_RDO_FACTOR VEDU_VCTRL_SEL_INTRA_RDO_FACTOR;
    volatile U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_0 VEDU_VCTRL_SEL_INTER_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_1 VEDU_VCTRL_SEL_INTER_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_2 VEDU_VCTRL_SEL_INTER_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_SEL_LAYER_RDO_FACTOR VEDU_VCTRL_SEL_LAYER_RDO_FACTOR;
    volatile unsigned int RESERVED_VEDU_VCTRL[64];
    volatile U_VEDU_CURLD_GCFG VEDU_CURLD_GCFG;
    volatile U_VEDU_CURLD_CLIP_THR VEDU_CURLD_CLIP_THR;
    volatile unsigned int RESERVED_VEDU_CURLD[62];
    volatile unsigned int RESERVED_VEDU_NBI[64];
    volatile U_VEDU_PME_SW_ADAPT_EN VEDU_PME_SW_ADAPT_EN;
    volatile U_VEDU_PME_SW_THR0 VEDU_PME_SW_THR0;
    volatile U_VEDU_PME_SW_THR1 VEDU_PME_SW_THR1;
    volatile U_VEDU_PME_SW_THR2 VEDU_PME_SW_THR2;
    volatile U_VEDU_PME_SKIP_PRE VEDU_PME_SKIP_PRE;
    volatile U_VEDU_PME_TR_WEIGHTX VEDU_PME_TR_WEIGHTX;
    volatile U_VEDU_PME_TR_WEIGHTY VEDU_PME_TR_WEIGHTY;
    volatile U_VEDU_PME_SR_WEIGHT VEDU_PME_SR_WEIGHT;
    volatile U_VEDU_PME_INTRABLK_DET VEDU_PME_INTRABLK_DET;
    volatile U_VEDU_PME_INTRABLK_DET_THR VEDU_PME_INTRABLK_DET_THR;
    volatile U_VEDU_PME_SKIN_THR VEDU_PME_SKIN_THR;
    volatile U_VEDU_PME_INTRA_LOWPOW VEDU_PME_INTRA_LOWPOW;
    volatile U_VEDU_PME_IBLK_COST_THR VEDU_PME_IBLK_COST_THR;
    volatile U_VEDU_PME_STRONG_EDGE VEDU_PME_STRONG_EDGE;
    volatile U_VEDU_PME_LARGE_MOVE_THR VEDU_PME_LARGE_MOVE_THR;
    volatile U_VEDU_PME_INTER_STRONG_EDGE VEDU_PME_INTER_STRONG_EDGE;
    volatile U_VEDU_PME_NEW_COST VEDU_PME_NEW_COST;
    volatile U_VEDU_PME_WINDOW_SIZE0_L0 VEDU_PME_WINDOW_SIZE0_L0;
    volatile U_VEDU_PME_WINDOW_SIZE1_L0 VEDU_PME_WINDOW_SIZE1_L0;
    volatile U_VEDU_PME_WINDOW_SIZE2_L0 VEDU_PME_WINDOW_SIZE2_L0;
    volatile U_VEDU_PME_WINDOW_SIZE3_L0 VEDU_PME_WINDOW_SIZE3_L0;
    volatile U_VEDU_PME_COST_OFFSET VEDU_PME_COST_OFFSET;
    volatile U_VEDU_PME_SAFE_CFG VEDU_PME_SAFE_CFG;
    volatile U_VEDU_PME_IBLK_REFRESH VEDU_PME_IBLK_REFRESH;
    volatile U_VEDU_PME_IBLK_REFRESH_NUM VEDU_PME_IBLK_REFRESH_NUM;
    volatile U_VEDU_PME_QPG_RC_THR0 VEDU_PME_QPG_RC_THR0;
    volatile U_VEDU_PME_QPG_RC_THR1 VEDU_PME_QPG_RC_THR1;
    volatile U_VEDU_PME_LOW_LUMA_THR VEDU_PME_LOW_LUMA_THR;
    volatile U_VEDU_PME_PBLK_PRE1 VEDU_PME_PBLK_PRE1;
    volatile U_VEDU_PME_CHROMA_FLAT VEDU_PME_CHROMA_FLAT;
    volatile U_VEDU_PME_LUMA_FLAT VEDU_PME_LUMA_FLAT;
    volatile U_VEDU_PME_MADI_FLAT VEDU_PME_MADI_FLAT;
    volatile unsigned int RESERVED_VEDU_PME[96];
    volatile unsigned int RESERVED_VEDU_PMEST[64];
    volatile U_VEDU_QPG_MAX_MIN_QP VEDU_QPG_MAX_MIN_QP;
    volatile U_VEDU_QPG_ROW_TARGET_BITS VEDU_QPG_ROW_TARGET_BITS;
    volatile U_VEDU_QPG_AVERAGE_LCU_BITS VEDU_QPG_AVERAGE_LCU_BITS;
    volatile U_VEDU_QPG_LOWLUMA VEDU_QPG_LOWLUMA;
    volatile U_VEDU_QPG_HEDGE VEDU_QPG_HEDGE;
    volatile U_VEDU_QPG_HEDGE_MOVE VEDU_QPG_HEDGE_MOVE;
    volatile U_VEDU_QPG_LARGE_MOVE VEDU_QPG_LARGE_MOVE;
    volatile U_VEDU_QPG_SKIN VEDU_QPG_SKIN;
    volatile U_VEDU_QPG_INTRA_DET VEDU_QPG_INTRA_DET;
    volatile U_VEDU_QPG_H264_SMOOTH VEDU_QPG_H264_SMOOTH;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG0 VEDU_QPG_CU_QP_DELTA_THRESH_REG0;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG1 VEDU_QPG_CU_QP_DELTA_THRESH_REG1;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG2 VEDU_QPG_CU_QP_DELTA_THRESH_REG2;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG3 VEDU_QPG_CU_QP_DELTA_THRESH_REG3;
    volatile U_VEDU_QPG_DELTA_LEVEL VEDU_QPG_DELTA_LEVEL;
    volatile U_VEDU_QPG_MADI_SWITCH_THR VEDU_QPG_MADI_SWITCH_THR;
    volatile U_VEDU_QPG_CU32_DELTA VEDU_QPG_CU32_DELTA;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG00 VEDU_QPG_QP_LAMBDA_CTRL_REG00;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG01 VEDU_QPG_QP_LAMBDA_CTRL_REG01;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG02 VEDU_QPG_QP_LAMBDA_CTRL_REG02;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG03 VEDU_QPG_QP_LAMBDA_CTRL_REG03;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG04 VEDU_QPG_QP_LAMBDA_CTRL_REG04;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG05 VEDU_QPG_QP_LAMBDA_CTRL_REG05;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG06 VEDU_QPG_QP_LAMBDA_CTRL_REG06;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG07 VEDU_QPG_QP_LAMBDA_CTRL_REG07;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG08 VEDU_QPG_QP_LAMBDA_CTRL_REG08;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG09 VEDU_QPG_QP_LAMBDA_CTRL_REG09;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG10 VEDU_QPG_QP_LAMBDA_CTRL_REG10;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG11 VEDU_QPG_QP_LAMBDA_CTRL_REG11;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG12 VEDU_QPG_QP_LAMBDA_CTRL_REG12;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG13 VEDU_QPG_QP_LAMBDA_CTRL_REG13;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG14 VEDU_QPG_QP_LAMBDA_CTRL_REG14;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG15 VEDU_QPG_QP_LAMBDA_CTRL_REG15;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG16 VEDU_QPG_QP_LAMBDA_CTRL_REG16;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG17 VEDU_QPG_QP_LAMBDA_CTRL_REG17;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG18 VEDU_QPG_QP_LAMBDA_CTRL_REG18;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG19 VEDU_QPG_QP_LAMBDA_CTRL_REG19;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG20 VEDU_QPG_QP_LAMBDA_CTRL_REG20;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG21 VEDU_QPG_QP_LAMBDA_CTRL_REG21;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG22 VEDU_QPG_QP_LAMBDA_CTRL_REG22;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG23 VEDU_QPG_QP_LAMBDA_CTRL_REG23;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG24 VEDU_QPG_QP_LAMBDA_CTRL_REG24;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG25 VEDU_QPG_QP_LAMBDA_CTRL_REG25;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG26 VEDU_QPG_QP_LAMBDA_CTRL_REG26;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG27 VEDU_QPG_QP_LAMBDA_CTRL_REG27;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG28 VEDU_QPG_QP_LAMBDA_CTRL_REG28;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG29 VEDU_QPG_QP_LAMBDA_CTRL_REG29;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG30 VEDU_QPG_QP_LAMBDA_CTRL_REG30;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG31 VEDU_QPG_QP_LAMBDA_CTRL_REG31;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG32 VEDU_QPG_QP_LAMBDA_CTRL_REG32;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG33 VEDU_QPG_QP_LAMBDA_CTRL_REG33;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG34 VEDU_QPG_QP_LAMBDA_CTRL_REG34;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG35 VEDU_QPG_QP_LAMBDA_CTRL_REG35;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG36 VEDU_QPG_QP_LAMBDA_CTRL_REG36;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG37 VEDU_QPG_QP_LAMBDA_CTRL_REG37;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG38 VEDU_QPG_QP_LAMBDA_CTRL_REG38;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG39 VEDU_QPG_QP_LAMBDA_CTRL_REG39;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG40 VEDU_QPG_QP_LAMBDA_CTRL_REG40;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG41 VEDU_QPG_QP_LAMBDA_CTRL_REG41;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG42 VEDU_QPG_QP_LAMBDA_CTRL_REG42;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG43 VEDU_QPG_QP_LAMBDA_CTRL_REG43;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG44 VEDU_QPG_QP_LAMBDA_CTRL_REG44;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG45 VEDU_QPG_QP_LAMBDA_CTRL_REG45;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG46 VEDU_QPG_QP_LAMBDA_CTRL_REG46;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG47 VEDU_QPG_QP_LAMBDA_CTRL_REG47;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG48 VEDU_QPG_QP_LAMBDA_CTRL_REG48;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG49 VEDU_QPG_QP_LAMBDA_CTRL_REG49;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG50 VEDU_QPG_QP_LAMBDA_CTRL_REG50;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG51 VEDU_QPG_QP_LAMBDA_CTRL_REG51;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG52 VEDU_QPG_QP_LAMBDA_CTRL_REG52;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG53 VEDU_QPG_QP_LAMBDA_CTRL_REG53;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG54 VEDU_QPG_QP_LAMBDA_CTRL_REG54;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG55 VEDU_QPG_QP_LAMBDA_CTRL_REG55;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG56 VEDU_QPG_QP_LAMBDA_CTRL_REG56;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG57 VEDU_QPG_QP_LAMBDA_CTRL_REG57;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG58 VEDU_QPG_QP_LAMBDA_CTRL_REG58;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG59 VEDU_QPG_QP_LAMBDA_CTRL_REG59;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG60 VEDU_QPG_QP_LAMBDA_CTRL_REG60;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG61 VEDU_QPG_QP_LAMBDA_CTRL_REG61;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG62 VEDU_QPG_QP_LAMBDA_CTRL_REG62;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG63 VEDU_QPG_QP_LAMBDA_CTRL_REG63;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG64 VEDU_QPG_QP_LAMBDA_CTRL_REG64;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG65 VEDU_QPG_QP_LAMBDA_CTRL_REG65;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG66 VEDU_QPG_QP_LAMBDA_CTRL_REG66;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG67 VEDU_QPG_QP_LAMBDA_CTRL_REG67;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG68 VEDU_QPG_QP_LAMBDA_CTRL_REG68;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG69 VEDU_QPG_QP_LAMBDA_CTRL_REG69;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG70 VEDU_QPG_QP_LAMBDA_CTRL_REG70;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG71 VEDU_QPG_QP_LAMBDA_CTRL_REG71;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG72 VEDU_QPG_QP_LAMBDA_CTRL_REG72;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG73 VEDU_QPG_QP_LAMBDA_CTRL_REG73;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG74 VEDU_QPG_QP_LAMBDA_CTRL_REG74;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG75 VEDU_QPG_QP_LAMBDA_CTRL_REG75;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG76 VEDU_QPG_QP_LAMBDA_CTRL_REG76;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG77 VEDU_QPG_QP_LAMBDA_CTRL_REG77;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG78 VEDU_QPG_QP_LAMBDA_CTRL_REG78;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG79 VEDU_QPG_QP_LAMBDA_CTRL_REG79;
    volatile U_VEDU_QPG_LAMBDA_MODE VEDU_QPG_LAMBDA_MODE;
    volatile U_VEDU_QPG_QP_RESTRAIN VEDU_QPG_QP_RESTRAIN;
    volatile unsigned int VEDU_QPG_CU_MIN_SAD_THRESH_0;
    volatile unsigned int VEDU_QPG_CU_MIN_SAD_THRESH_1;
    volatile U_VEDU_QPG_CU_MIN_SAD_REG VEDU_QPG_CU_MIN_SAD_REG;
    volatile U_VEDU_QPG_FLAT_REGION VEDU_QPG_FLAT_REGION;
    volatile unsigned int RESERVED_VEDU_QPG[89];
    volatile unsigned int RESERVED_VEDU_REFLD[64];
    volatile U_VEDU_IME_INTER_MODE VEDU_IME_INTER_MODE;
    volatile U_VEDU_IME_RDOCFG VEDU_IME_RDOCFG;
    volatile U_VEDU_IME_FME_LPOW_THR VEDU_IME_FME_LPOW_THR;
    volatile U_VEDU_IME_NO_INTRA_ANG_EN VEDU_IME_NO_INTRA_ANG_EN;
    volatile U_VEDU_IME_NO_INTRA_ANG_MV_THR VEDU_IME_NO_INTRA_ANG_MV_THR;
    volatile unsigned int RESERVED_VEDU_IME[59];
    volatile unsigned int RESERVED_VEDU_FME[64];
    volatile U_VEDU_MRG_FORCE_ZERO_EN VEDU_MRG_FORCE_ZERO_EN;
    volatile U_VEDU_MRG_FORCE_SKIP_EN VEDU_MRG_FORCE_SKIP_EN;
    volatile unsigned int RESERVED_VEDU_MRG[62];
    volatile U_VEDU_INTRA_INTER_AVAIL VEDU_INTRA_INTER_AVAIL;
    volatile U_VEDU_INTRA_DC_SHIFT VEDU_INTRA_DC_SHIFT;
    volatile U_VEDU_INTRA_BIT_WEIGHT VEDU_INTRA_BIT_WEIGHT;
    volatile U_VEDU_INTRA_DC_MADI VEDU_INTRA_DC_MADI;
    volatile U_VEDU_INTRA_RDO_COST_OFFSET VEDU_INTRA_RDO_COST_OFFSET;
    volatile U_VEDU_INTRA_CHNL4_ANG_0EN VEDU_INTRA_CHNL4_ANG_0EN;
    volatile U_VEDU_INTRA_CHNL8_ANG_0EN VEDU_INTRA_CHNL8_ANG_0EN;
    volatile U_VEDU_INTRA_CHNL8_ANG_1EN VEDU_INTRA_CHNL8_ANG_1EN;
    volatile U_VEDU_INTRA_CHNL16_ANG_0EN VEDU_INTRA_CHNL16_ANG_0EN;
    volatile U_VEDU_INTRA_CHNL16_ANG_1EN VEDU_INTRA_CHNL16_ANG_1EN;
    volatile U_VEDU_INTRA_CHROMA_ANG_EN VEDU_INTRA_CHROMA_ANG_EN;
    volatile unsigned int RESERVED_VEDU_INTRA[53];
    volatile unsigned int VEDU_PMV_POC_0;
    volatile unsigned int VEDU_PMV_POC_1;
    volatile unsigned int VEDU_PMV_POC_2;
    volatile unsigned int VEDU_PMV_POC_3;
    volatile unsigned int VEDU_PMV_POC_4;
    volatile unsigned int VEDU_PMV_POC_5;
    volatile U_VEDU_PMV_TMV_EN VEDU_PMV_TMV_EN;
    volatile unsigned int RESERVED_VEDU_PMV[57];
    volatile U_VEDU_TQITQ_DEADZONE VEDU_TQITQ_DEADZONE;
    volatile unsigned int RESERVED_VEDU_TQITQ[191];
    volatile U_VEDU_SEL_INTRA_ABS_OFFSET0 VEDU_SEL_INTRA_ABS_OFFSET0;
    volatile U_VEDU_SEL_INTRA_ABS_OFFSET1 VEDU_SEL_INTRA_ABS_OFFSET1;
    volatile U_VEDU_SEL_INTER_ABS_OFFSET0 VEDU_SEL_INTER_ABS_OFFSET0;
    volatile unsigned int RESERVED_VEDU_SEL0;
    volatile U_VEDU_SEL_OFFSET_STRENGTH VEDU_SEL_OFFSET_STRENGTH;
    volatile U_VEDU_SEL_CU32_DC_AC_TH_OFFSET VEDU_SEL_CU32_DC_AC_TH_OFFSET;
    volatile U_VEDU_SEL_CU32_QP_TH VEDU_SEL_CU32_QP_TH;
    volatile U_VEDU_SEL_RES_DC_AC_TH VEDU_SEL_RES_DC_AC_TH;
    volatile unsigned int RESERVED_VEDU_SEL[56];
    volatile unsigned int RESERVED_VEDU_DBLK[64];
    volatile unsigned int RESERVED_VEDU_SAO[64];
    volatile U_VEDU_EMAR_WAIT_TIM_OUT VEDU_EMAR_WAIT_TIM_OUT;
    volatile U_VEDU_EMAR_RCH_RPT_TH0 VEDU_EMAR_RCH_RPT_TH0;
    volatile U_VEDU_EMAR_RCH_RPT_TH1 VEDU_EMAR_RCH_RPT_TH1;
    volatile U_VEDU_EMAR_RCH_RPT_TH2 VEDU_EMAR_RCH_RPT_TH2;
    volatile U_VEDU_EMAR_WCH_RPT_TH0 VEDU_EMAR_WCH_RPT_TH0;
    volatile U_VEDU_EMAR_WCH_RPT_TH1 VEDU_EMAR_WCH_RPT_TH1;
    volatile U_VEDU_EMAR_WCH_RPT_TH2 VEDU_EMAR_WCH_RPT_TH2;
    volatile unsigned int RESERVED_VEDU_EMAR[57];
    volatile unsigned int RESERVED_VEDU_PACK[64];
    volatile U_VEDU_CABAC_GLB_CFG VEDU_CABAC_GLB_CFG;
    volatile U_VEDU_CABAC_SLCHDR_SIZE VEDU_CABAC_SLCHDR_SIZE;
    volatile U_VEDU_CABAC_SLCHDR_PART1 VEDU_CABAC_SLCHDR_PART1;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG1;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG2;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG3;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG4;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG5;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG6;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG7;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG8;
    volatile U_VEDU_CABAC_SLCHDR_SIZE_I VEDU_CABAC_SLCHDR_SIZE_I;
    volatile U_VEDU_CABAC_SLCHDR_PART1_I VEDU_CABAC_SLCHDR_PART1_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG1_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG2_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG3_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG4_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG5_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG6_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG7_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG8_I;
    volatile unsigned int RESERVED_VEDU_CABAC[43];
    volatile unsigned int VEDU_VLC_SLCHDRSTRM0;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM1;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM2;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM3;
    volatile unsigned int VEDU_VLC_REORDERSTRM0;
    volatile unsigned int VEDU_VLC_REORDERSTRM1;
    volatile unsigned int VEDU_VLC_MARKINGSTRM0;
    volatile unsigned int VEDU_VLC_MARKINGSTRM1;
    volatile U_VEDU_VLC_SLCHDRPARA VEDU_VLC_SLCHDRPARA;
    volatile U_VEDU_VLC_SVC VEDU_VLC_SVC;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM0_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM1_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM2_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM3_I;
    volatile unsigned int VEDU_VLC_REORDERSTRM0_I;
    volatile unsigned int VEDU_VLC_REORDERSTRM1_I;
    volatile unsigned int VEDU_VLC_MARKINGSTRM0_I;
    volatile unsigned int VEDU_VLC_MARKINGSTRM1_I;
    volatile U_VEDU_VLC_SLCHDRPARA_I VEDU_VLC_SLCHDRPARA_I;
    volatile unsigned int RESERVED_VEDU_VLC[45];
    volatile U_VEDU_VLCST_PTBITS_EN VEDU_VLCST_PTBITS_EN;
    volatile unsigned int VEDU_VLCST_PTBITS;
    volatile unsigned int RESERVED_VEDU_VLCST0;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN0;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN1;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN2;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN3;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN4;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN5;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN6;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN7;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN8;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN9;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN10;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN11;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN12;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN13;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN14;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN15;
    volatile unsigned int VEDU_VLCST_STRMADDR0;
    volatile unsigned int VEDU_VLCST_STRMADDR1;
    volatile unsigned int VEDU_VLCST_STRMADDR2;
    volatile unsigned int VEDU_VLCST_STRMADDR3;
    volatile unsigned int VEDU_VLCST_STRMADDR4;
    volatile unsigned int VEDU_VLCST_STRMADDR5;
    volatile unsigned int VEDU_VLCST_STRMADDR6;
    volatile unsigned int VEDU_VLCST_STRMADDR7;
    volatile unsigned int VEDU_VLCST_STRMADDR8;
    volatile unsigned int VEDU_VLCST_STRMADDR9;
    volatile unsigned int VEDU_VLCST_STRMADDR10;
    volatile unsigned int VEDU_VLCST_STRMADDR11;
    volatile unsigned int VEDU_VLCST_STRMADDR12;
    volatile unsigned int VEDU_VLCST_STRMADDR13;
    volatile unsigned int VEDU_VLCST_STRMADDR14;
    volatile unsigned int VEDU_VLCST_STRMADDR15;
    volatile unsigned int VEDU_VLCST_PARA_ADDR;
    volatile U_VEDU_VLCST_PARAMETER VEDU_VLCST_PARAMETER;
    volatile unsigned int VEDU_VLCST_PARA_DATA0;
    volatile unsigned int VEDU_VLCST_PARA_DATA1;
    volatile unsigned int VEDU_VLCST_PARA_DATA2;
    volatile unsigned int VEDU_VLCST_PARA_DATA3;
    volatile unsigned int VEDU_VLCST_PARA_DATA4;
    volatile unsigned int VEDU_VLCST_PARA_DATA5;
    volatile unsigned int VEDU_VLCST_PARA_DATA6;
    volatile unsigned int VEDU_VLCST_PARA_DATA7;
    volatile unsigned int VEDU_VLCST_PARA_DATA8;
    volatile unsigned int VEDU_VLCST_PARA_DATA9;
    volatile unsigned int VEDU_VLCST_PARA_DATA10;
    volatile unsigned int VEDU_VLCST_PARA_DATA11;
    volatile unsigned int VEDU_VLCST_PARA_DATA12;
    volatile unsigned int VEDU_VLCST_PARA_DATA13;
    volatile unsigned int VEDU_VLCST_PARA_DATA14;
    volatile unsigned int VEDU_VLCST_PARA_DATA15;
    volatile unsigned int VEDU_VLCST_PARA_DATA16;
    volatile unsigned int VEDU_VLCST_PARA_DATA17;
    volatile unsigned int VEDU_VLCST_PARA_DATA18;
    volatile unsigned int VEDU_VLCST_PARA_DATA19;
    volatile unsigned int VEDU_VLCST_PARA_DATA20;
    volatile unsigned int VEDU_VLCST_PARA_DATA21;
    volatile unsigned int VEDU_VLCST_PARA_DATA22;
    volatile unsigned int VEDU_VLCST_PARA_DATA23;
    volatile unsigned int VEDU_VLCST_PARA_DATA24;
    volatile unsigned int VEDU_VLCST_PARA_DATA25;
    volatile unsigned int VEDU_VLCST_PARA_DATA26;
    volatile unsigned int VEDU_VLCST_PARA_DATA27;
    volatile unsigned int VEDU_VLCST_PARA_DATA28;
    volatile unsigned int VEDU_VLCST_PARA_DATA29;
    volatile unsigned int VEDU_VLCST_PARA_DATA30;
    volatile unsigned int VEDU_VLCST_PARA_DATA31;
    volatile unsigned int VEDU_VLCST_PARA_DATA32;
    volatile unsigned int VEDU_VLCST_PARA_DATA33;
    volatile unsigned int VEDU_VLCST_PARA_DATA34;
    volatile unsigned int VEDU_VLCST_PARA_DATA35;
    volatile unsigned int VEDU_VLCST_PARA_DATA36;
    volatile unsigned int VEDU_VLCST_PARA_DATA37;
    volatile unsigned int VEDU_VLCST_PARA_DATA38;
    volatile unsigned int VEDU_VLCST_PARA_DATA39;
    volatile unsigned int VEDU_VLCST_PARA_DATA40;
    volatile unsigned int VEDU_VLCST_PARA_DATA41;
    volatile unsigned int VEDU_VLCST_PARA_DATA42;
    volatile unsigned int VEDU_VLCST_PARA_DATA43;
    volatile unsigned int VEDU_VLCST_PARA_DATA44;
    volatile unsigned int VEDU_VLCST_PARA_DATA45;
    volatile unsigned int VEDU_VLCST_PARA_DATA46;
    volatile unsigned int VEDU_VLCST_PARA_DATA47;
    volatile unsigned int RESERVED_VEDU_VLCST[43];
    volatile U_VEDU_ENV_CHN VEDU_ENV_CHN;
    volatile unsigned int RESERVED_VEDU_ENV[1151];
    volatile U_FUNC_VCPI_INTSTAT FUNC_VCPI_INTSTAT;
    volatile U_FUNC_VCPI_RAWINT FUNC_VCPI_RAWINT;
    volatile unsigned int FUNC_VCPI_VEDU_TIMER;
    volatile unsigned int FUNC_VCPI_IDLE_TIMER;
    volatile U_FUNC_VCPI_INTSTAT_S FUNC_VCPI_INTSTAT_S;
    volatile U_FUNC_VCPI_RAWINT_S FUNC_VCPI_RAWINT_S;
    volatile unsigned int RESERVED_FUNC_VCPI[10];
    volatile unsigned int RESERVED_FUNC_VCTRL[16];
    volatile unsigned int RESERVED_FUNC_QPGLD[16];
    volatile unsigned int RESERVED_FUNC_CURLD[16];
    volatile unsigned int RESERVED_FUNC_NBI[16];
    volatile unsigned int RESERVED_FUNC_PMELD[16];
    volatile unsigned int RESERVED_FUNC_PMEINFO_LD[16];
    volatile U_FUNC_PME_MADI_SUM FUNC_PME_MADI_SUM;
    volatile U_FUNC_PME_MADP_SUM FUNC_PME_MADP_SUM;
    volatile U_FUNC_PME_MADI_NUM FUNC_PME_MADI_NUM;
    volatile U_FUNC_PME_MADP_NUM FUNC_PME_MADP_NUM;
    volatile unsigned int RESERVED_FUNC_PME[12];
    volatile unsigned int RESERVED_FUNC_PMEST[16];
    volatile unsigned int RESERVED_FUNC_PMEINFO_ST[16];
    volatile unsigned int RESERVED_FUNC0[48];
    volatile unsigned int RESERVED_FUNC_PINTRA[32];
    volatile unsigned int RESERVED_FUNC_FME[16];
    volatile unsigned int RESERVED_FUNC_MRG[16];
    volatile unsigned int RESERVED_FUNC1[16];
    volatile unsigned int RESERVED_FUNC_INTRA[16];
    volatile unsigned int RESERVED_FUNC2[16];
    volatile unsigned int RESERVED_FUNC_PMV[16];
    volatile unsigned int FUNC_PMV[16];
    volatile unsigned int RESERVED_FUNC_TQITQ[16];
    volatile unsigned int RESERVED_FUNC4[16];
    volatile unsigned int RESERVED_FUNC5[32];
    volatile unsigned int RESERVED_FUNC_DBLK[16];
    volatile unsigned int RESERVED_FUNC_SAO[16];
    volatile unsigned int RESERVED_FUNC_RECST[16];
    volatile unsigned int RESERVED_FUNC_PACK[16];
    volatile unsigned int RESERVED_FUNC6[16];
    volatile unsigned int FUNC_CABAC_PIC_STRMSIZE;
    volatile unsigned int FUNC_CABAC_BIT_NUM;
    volatile unsigned int FUNC_CABAC_PIC_HDRBIN_NUM;
    volatile unsigned int FUNC_CABAC_PIC_RESBIN_NUM;
    volatile unsigned int RESERVED_FUNC_CABAC[12];
    volatile unsigned int FUNC_VLC_PIC_BITS;
    volatile unsigned int RESERVED_FUNC_VLC[15];
    volatile unsigned int FUNC_VLCST_SLC_LEN_CNT;
    volatile U_FUNC_VLCST_DSRPTR00 FUNC_VLCST_DSRPTR00;
    volatile U_FUNC_VLCST_DSRPTR01 FUNC_VLCST_DSRPTR01;
    volatile U_FUNC_VLCST_DSRPTR10 FUNC_VLCST_DSRPTR10;
    volatile U_FUNC_VLCST_DSRPTR11 FUNC_VLCST_DSRPTR11;
    volatile U_FUNC_VLCST_DSRPTR20 FUNC_VLCST_DSRPTR20;
    volatile U_FUNC_VLCST_DSRPTR21 FUNC_VLCST_DSRPTR21;
    volatile U_FUNC_VLCST_DSRPTR30 FUNC_VLCST_DSRPTR30;
    volatile U_FUNC_VLCST_DSRPTR31 FUNC_VLCST_DSRPTR31;
    volatile U_FUNC_VLCST_DSRPTR40 FUNC_VLCST_DSRPTR40;
    volatile U_FUNC_VLCST_DSRPTR41 FUNC_VLCST_DSRPTR41;
    volatile U_FUNC_VLCST_DSRPTR50 FUNC_VLCST_DSRPTR50;
    volatile U_FUNC_VLCST_DSRPTR51 FUNC_VLCST_DSRPTR51;
    volatile U_FUNC_VLCST_DSRPTR60 FUNC_VLCST_DSRPTR60;
    volatile U_FUNC_VLCST_DSRPTR61 FUNC_VLCST_DSRPTR61;
    volatile U_FUNC_VLCST_DSRPTR70 FUNC_VLCST_DSRPTR70;
    volatile U_FUNC_VLCST_DSRPTR71 FUNC_VLCST_DSRPTR71;
    volatile U_FUNC_VLCST_DSRPTR80 FUNC_VLCST_DSRPTR80;
    volatile U_FUNC_VLCST_DSRPTR81 FUNC_VLCST_DSRPTR81;
    volatile U_FUNC_VLCST_DSRPTR90 FUNC_VLCST_DSRPTR90;
    volatile U_FUNC_VLCST_DSRPTR91 FUNC_VLCST_DSRPTR91;
    volatile U_FUNC_VLCST_DSRPTR100 FUNC_VLCST_DSRPTR100;
    volatile U_FUNC_VLCST_DSRPTR101 FUNC_VLCST_DSRPTR101;
    volatile U_FUNC_VLCST_DSRPTR110 FUNC_VLCST_DSRPTR110;
    volatile U_FUNC_VLCST_DSRPTR111 FUNC_VLCST_DSRPTR111;
    volatile U_FUNC_VLCST_DSRPTR120 FUNC_VLCST_DSRPTR120;
    volatile U_FUNC_VLCST_DSRPTR121 FUNC_VLCST_DSRPTR121;
    volatile U_FUNC_VLCST_DSRPTR130 FUNC_VLCST_DSRPTR130;
    volatile U_FUNC_VLCST_DSRPTR131 FUNC_VLCST_DSRPTR131;
    volatile U_FUNC_VLCST_DSRPTR140 FUNC_VLCST_DSRPTR140;
    volatile U_FUNC_VLCST_DSRPTR141 FUNC_VLCST_DSRPTR141;
    volatile U_FUNC_VLCST_DSRPTR150 FUNC_VLCST_DSRPTR150;
    volatile U_FUNC_VLCST_DSRPTR151 FUNC_VLCST_DSRPTR151;
    volatile unsigned int RESERVED_FUNC_VLCST[95];
    volatile unsigned int RESERVED_FUNC_EMAR[16];
    volatile unsigned int RESERVED_FUNC7[16];
    volatile U_FUNC_SEL_OPT_8X8_CNT FUNC_SEL_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTRA_OPT_8X8_CNT FUNC_SEL_INTRA_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTRA_NORMAL_OPT_8X8_CNT FUNC_SEL_INTRA_NORMAL_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTRA_PCM_OPT_8X8_CNT FUNC_SEL_INTRA_PCM_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_OPT_8X8_CNT FUNC_SEL_INTER_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_8X8_CNT FUNC_SEL_INTER_FME_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_8X8_CNT FUNC_SEL_INTER_MERGE_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_8X8_CNT FUNC_SEL_INTER_SKIP_OPT_8X8_CNT;
    volatile U_FUNC_SEL_OPT_16X16_CNT FUNC_SEL_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTRA_OPT_16X16_CNT FUNC_SEL_INTRA_OPT_16X16_CNT;
    volatile U_FUNC_SEL_OPT_4X4_CNT FUNC_SEL_OPT_4X4_CNT;
    volatile unsigned int RESERVED_FUNC_SEL0;
    volatile U_FUNC_SEL_INTER_OPT_16X16_CNT FUNC_SEL_INTER_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_16X16_CNT FUNC_SEL_INTER_FME_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_16X16_CNT FUNC_SEL_INTER_MERGE_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_16X16_CNT FUNC_SEL_INTER_SKIP_OPT_16X16_CNT;
    volatile U_FUNC_SEL_OPT_32X32_CNT FUNC_SEL_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTRA_OPT_32X32_CNT FUNC_SEL_INTRA_OPT_32X32_CNT;
    volatile unsigned int RESERVED_FUNC_SEL1;
    volatile U_FUNC_SEL_INTER_OPT_32X32_CNT FUNC_SEL_INTER_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_32X32_CNT FUNC_SEL_INTER_FME_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_32X32_CNT FUNC_SEL_INTER_MERGE_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_32X32_CNT FUNC_SEL_INTER_SKIP_OPT_32X32_CNT;
    volatile U_FUNC_SEL_OPT_64X64_CNT FUNC_SEL_OPT_64X64_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_64X64_CNT FUNC_SEL_INTER_FME_OPT_64X64_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_64X64_CNT FUNC_SEL_INTER_MERGE_OPT_64X64_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_64X64_CNT FUNC_SEL_INTER_SKIP_OPT_64X64_CNT;
    volatile U_FUNC_SEL_TOTAL_LUMA_QP FUNC_SEL_TOTAL_LUMA_QP;
    volatile U_FUNC_SEL_MAX_MIN_LUMA_QP FUNC_SEL_MAX_MIN_LUMA_QP;
    volatile unsigned int RESERVED_FUNC_SEL2[35];
    volatile U_FUNC_SEL_LUMA_QP0_CNT FUNC_SEL_LUMA_QP0_CNT;
    volatile U_FUNC_SEL_LUMA_QP1_CNT FUNC_SEL_LUMA_QP1_CNT;
    volatile U_FUNC_SEL_LUMA_QP2_CNT FUNC_SEL_LUMA_QP2_CNT;
    volatile U_FUNC_SEL_LUMA_QP3_CNT FUNC_SEL_LUMA_QP3_CNT;
    volatile U_FUNC_SEL_LUMA_QP4_CNT FUNC_SEL_LUMA_QP4_CNT;
    volatile U_FUNC_SEL_LUMA_QP5_CNT FUNC_SEL_LUMA_QP5_CNT;
    volatile U_FUNC_SEL_LUMA_QP6_CNT FUNC_SEL_LUMA_QP6_CNT;
    volatile U_FUNC_SEL_LUMA_QP7_CNT FUNC_SEL_LUMA_QP7_CNT;
    volatile U_FUNC_SEL_LUMA_QP8_CNT FUNC_SEL_LUMA_QP8_CNT;
    volatile U_FUNC_SEL_LUMA_QP9_CNT FUNC_SEL_LUMA_QP9_CNT;
    volatile U_FUNC_SEL_LUMA_QP10_CNT FUNC_SEL_LUMA_QP10_CNT;
    volatile U_FUNC_SEL_LUMA_QP11_CNT FUNC_SEL_LUMA_QP11_CNT;
    volatile U_FUNC_SEL_LUMA_QP12_CNT FUNC_SEL_LUMA_QP12_CNT;
    volatile U_FUNC_SEL_LUMA_QP13_CNT FUNC_SEL_LUMA_QP13_CNT;
    volatile U_FUNC_SEL_LUMA_QP14_CNT FUNC_SEL_LUMA_QP14_CNT;
    volatile U_FUNC_SEL_LUMA_QP15_CNT FUNC_SEL_LUMA_QP15_CNT;
    volatile U_FUNC_SEL_LUMA_QP16_CNT FUNC_SEL_LUMA_QP16_CNT;
    volatile U_FUNC_SEL_LUMA_QP17_CNT FUNC_SEL_LUMA_QP17_CNT;
    volatile U_FUNC_SEL_LUMA_QP18_CNT FUNC_SEL_LUMA_QP18_CNT;
    volatile U_FUNC_SEL_LUMA_QP19_CNT FUNC_SEL_LUMA_QP19_CNT;
    volatile U_FUNC_SEL_LUMA_QP20_CNT FUNC_SEL_LUMA_QP20_CNT;
    volatile U_FUNC_SEL_LUMA_QP21_CNT FUNC_SEL_LUMA_QP21_CNT;
    volatile U_FUNC_SEL_LUMA_QP22_CNT FUNC_SEL_LUMA_QP22_CNT;
    volatile U_FUNC_SEL_LUMA_QP23_CNT FUNC_SEL_LUMA_QP23_CNT;
    volatile U_FUNC_SEL_LUMA_QP24_CNT FUNC_SEL_LUMA_QP24_CNT;
    volatile U_FUNC_SEL_LUMA_QP25_CNT FUNC_SEL_LUMA_QP25_CNT;
    volatile U_FUNC_SEL_LUMA_QP26_CNT FUNC_SEL_LUMA_QP26_CNT;
    volatile U_FUNC_SEL_LUMA_QP27_CNT FUNC_SEL_LUMA_QP27_CNT;
    volatile U_FUNC_SEL_LUMA_QP28_CNT FUNC_SEL_LUMA_QP28_CNT;
    volatile U_FUNC_SEL_LUMA_QP29_CNT FUNC_SEL_LUMA_QP29_CNT;
    volatile U_FUNC_SEL_LUMA_QP30_CNT FUNC_SEL_LUMA_QP30_CNT;
    volatile U_FUNC_SEL_LUMA_QP31_CNT FUNC_SEL_LUMA_QP31_CNT;
    volatile U_FUNC_SEL_LUMA_QP32_CNT FUNC_SEL_LUMA_QP32_CNT;
    volatile U_FUNC_SEL_LUMA_QP33_CNT FUNC_SEL_LUMA_QP33_CNT;
    volatile U_FUNC_SEL_LUMA_QP34_CNT FUNC_SEL_LUMA_QP34_CNT;
    volatile U_FUNC_SEL_LUMA_QP35_CNT FUNC_SEL_LUMA_QP35_CNT;
    volatile U_FUNC_SEL_LUMA_QP36_CNT FUNC_SEL_LUMA_QP36_CNT;
    volatile U_FUNC_SEL_LUMA_QP37_CNT FUNC_SEL_LUMA_QP37_CNT;
    volatile U_FUNC_SEL_LUMA_QP38_CNT FUNC_SEL_LUMA_QP38_CNT;
    volatile U_FUNC_SEL_LUMA_QP39_CNT FUNC_SEL_LUMA_QP39_CNT;
    volatile U_FUNC_SEL_LUMA_QP40_CNT FUNC_SEL_LUMA_QP40_CNT;
    volatile U_FUNC_SEL_LUMA_QP41_CNT FUNC_SEL_LUMA_QP41_CNT;
    volatile U_FUNC_SEL_LUMA_QP42_CNT FUNC_SEL_LUMA_QP42_CNT;
    volatile U_FUNC_SEL_LUMA_QP43_CNT FUNC_SEL_LUMA_QP43_CNT;
    volatile U_FUNC_SEL_LUMA_QP44_CNT FUNC_SEL_LUMA_QP44_CNT;
    volatile U_FUNC_SEL_LUMA_QP45_CNT FUNC_SEL_LUMA_QP45_CNT;
    volatile U_FUNC_SEL_LUMA_QP46_CNT FUNC_SEL_LUMA_QP46_CNT;
    volatile U_FUNC_SEL_LUMA_QP47_CNT FUNC_SEL_LUMA_QP47_CNT;
    volatile U_FUNC_SEL_LUMA_QP48_CNT FUNC_SEL_LUMA_QP48_CNT;
    volatile U_FUNC_SEL_LUMA_QP49_CNT FUNC_SEL_LUMA_QP49_CNT;
    volatile U_FUNC_SEL_LUMA_QP50_CNT FUNC_SEL_LUMA_QP50_CNT;
    volatile U_FUNC_SEL_LUMA_QP51_CNT FUNC_SEL_LUMA_QP51_CNT;
    volatile unsigned int RESERVED_FUNC_SEL[140];
    volatile unsigned int RESERVED_FUNC_SAO0[19];
    volatile U_FUNC_SAO_OFF_NUM FUNC_SAO_OFF_NUM;
    volatile U_FUNC_SAO_LCU_CNT FUNC_SAO_LCU_CNT;
    volatile unsigned int RESERVED_FUNC_SAO1[11];
    volatile unsigned int RESERVED_FUNC[48];
    volatile unsigned int RESERVED_FUNC_001[1344];
    volatile U_PMV_CNT_FRAME PMV_CNT_FRAME ;
    volatile U_PMV_TMV_0 PMV_TMV_0 ;
    volatile U_PMV_TMV_1 PMV_TMV_1 ;
    volatile U_PMV_TMV_2 PMV_TMV_2 ;
    volatile U_PMV_TMV_3 PMV_TMV_3 ;
    volatile U_PMV_TMV_4 PMV_TMV_4 ;
    volatile U_PMV_TMV_5 PMV_TMV_5 ;
    volatile unsigned int PMV_RESERVED0 ;
    volatile unsigned int FUNC_PMV_MV0_COUNT ;
    volatile unsigned int FUNC_PMV_MV1_COUNT ;
    volatile unsigned int FUNC_PMV_MV2_COUNT ;
    volatile unsigned int FUNC_PMV_MV3_COUNT ;
    volatile unsigned int FUNC_PMV_MV4_COUNT ;
    volatile unsigned int FUNC_PMV_MV5_COUNT ;
    volatile unsigned int FUNC_PMV_MV6_COUNT ;
    volatile unsigned int FUNC_PMV_MV7_COUNT ;
    volatile unsigned int FUNC_PMV_MV8_COUNT ;
    volatile unsigned int FUNC_PMV_MV9_COUNT ;
    volatile unsigned int FUNC_PMV_MV10_COUNT ;
    volatile unsigned int FUNC_PMV_MV11_COUNT ;
    volatile unsigned int FUNC_PMV_MV12_COUNT ;
    volatile unsigned int FUNC_PMV_MV13_COUNT ;
    volatile unsigned int FUNC_PMV_MV14_COUNT ;
    volatile unsigned int FUNC_PMV_MV15_COUNT ;
    volatile unsigned int FUNC_PMV_MV16_COUNT ;
    volatile unsigned int FUNC_PMV_MV17_COUNT ;
    volatile unsigned int FUNC_PMV_MV18_COUNT ;
    volatile unsigned int FUNC_PMV_MV19_COUNT ;
    volatile unsigned int FUNC_PMV_MV20_COUNT ;
    volatile unsigned int FUNC_PMV_MV21_COUNT ;
    volatile unsigned int FUNC_PMV_MV22_COUNT ;
    volatile unsigned int RESERVED_FUNC_002[2721];
    volatile U_MMU_PRE_GLB_SCR MMU_PRE_GLB_SCR;
    volatile unsigned int MMU_PRE_RESERVED_0[3];
    volatile unsigned int MMU_PRE_NBI_MVST_ADDR_STR;
    volatile unsigned int MMU_PRE_NBI_MVST_ADDR_END;
    volatile unsigned int MMU_PRE_NBI_MVLD_ADDR_STR;
    volatile unsigned int MMU_PRE_NBI_MVLD_ADDR_END;
    volatile unsigned int MMU_PRE_PMEST_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEST_ADDR_END;
    volatile unsigned int MMU_PRE_PMELD_ADDR_STR;
    volatile unsigned int MMU_PRE_PMELD_ADDR_END;
    volatile unsigned int MMU_PRE_PMEINFOST_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEINFOST_ADDR_END;
    volatile unsigned int MMU_PRE_PMEINFOLD0_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEINFOLD0_ADDR_END;
    volatile unsigned int MST_PRE_RESERVED_1[2];
    volatile unsigned int MMU_PRE_PMEINFOLD1_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEINFOLD1_ADDR_END;
    volatile unsigned int MMU_PRE_QPGLD_ADDR_STR;
    volatile unsigned int MMU_PRE_QPGLD_ADDR_END;
    volatile unsigned int MMU_PRE_REC_YH_ADDR_STR;
    volatile unsigned int MMU_PRE_REC_YH_ADDR_END;
    volatile unsigned int MMU_PRE_REC_CH_ADDR_STR;
    volatile unsigned int MMU_PRE_REC_CH_ADDR_END;
    volatile unsigned int MMU_PRE_REC_YADDR_STR;
    volatile unsigned int MMU_PRE_REC_YADDR_END;
    volatile unsigned int MMU_PRE_REC_CADDR_STR;
    volatile unsigned int MMU_PRE_REC_CADDR_END;
    volatile unsigned int MMU_PRE_REF_YH_ADDR_STR;
    volatile unsigned int MMU_PRE_REF_YH_ADDR_END;
    volatile unsigned int MMU_PRE_REF_CH_ADDR_STR;
    volatile unsigned int MMU_PRE_REF_CH_ADDR_END;
    volatile unsigned int MMU_PRE_REF_YADDR_STR;
    volatile unsigned int MMU_PRE_REF_YADDR_END;
    volatile unsigned int MMU_PRE_REF_CADDR_STR;
    volatile unsigned int MMU_PRE_REF_CADDR_END;
    volatile unsigned int MMU_PRE_SRC_YHADDR_STR;
    volatile unsigned int MMU_PRE_SRC_YHADDR_END;
    volatile unsigned int MMU_PRE_SRC_CHADDR_STR;
    volatile unsigned int MMU_PRE_SRC_CHADDR_END;
    volatile unsigned int MMU_PRE_SRC_YADDR_STR;
    volatile unsigned int MMU_PRE_SRC_YADDR_END;
    volatile unsigned int MMU_PRE_SRC_CADDR_STR;
    volatile unsigned int MMU_PRE_SRC_CADDR_END;
    volatile unsigned int MMU_PRE_SRC_VADDR_STR;
    volatile unsigned int MMU_PRE_SRC_VADDR_END;
    volatile unsigned int MMU_PRE_LOWDLY_ADDR_STR;
    volatile unsigned int MMU_PRE_LOWDLY_ADDR_END;
    volatile unsigned int MMU_PRE_PPS_ADDR_STR;
    volatile unsigned int MMU_PRE_PPS_ADDR_END;
    volatile unsigned int MMU_PRE_STRMADDR0_STR;
    volatile unsigned int MMU_PRE_STRMADDR0_END;
    volatile unsigned int MMU_PRE_STRMADDR1_STR;
    volatile unsigned int MMU_PRE_STRMADDR1_END;
    volatile unsigned int MMU_PRE_STRMADDR2_STR;
    volatile unsigned int MMU_PRE_STRMADDR2_END;
    volatile unsigned int MMU_PRE_STRMADDR3_STR;
    volatile unsigned int MMU_PRE_STRMADDR3_END;
    volatile unsigned int MMU_PRE_STRMADDR4_STR;
    volatile unsigned int MMU_PRE_STRMADDR4_END;
    volatile unsigned int MMU_PRE_STRMADDR5_STR;
    volatile unsigned int MMU_PRE_STRMADDR5_END;
    volatile unsigned int MMU_PRE_STRMADDR6_STR;
    volatile unsigned int MMU_PRE_STRMADDR6_END;
    volatile unsigned int MMU_PRE_STRMADDR7_STR;
    volatile unsigned int MMU_PRE_STRMADDR7_END;
    volatile unsigned int MMU_PRE_STRMADDR8_STR;
    volatile unsigned int MMU_PRE_STRMADDR8_END;
    volatile unsigned int MMU_PRE_STRMADDR9_STR;
    volatile unsigned int MMU_PRE_STRMADDR9_END;
    volatile unsigned int MMU_PRE_STRMADDR10_STR;
    volatile unsigned int MMU_PRE_STRMADDR10_END;
    volatile unsigned int MMU_PRE_STRMADDR11_STR;
    volatile unsigned int MMU_PRE_STRMADDR11_END;
    volatile unsigned int MMU_PRE_STRMADDR12_STR;
    volatile unsigned int MMU_PRE_STRMADDR12_END;
    volatile unsigned int MMU_PRE_STRMADDR13_STR;
    volatile unsigned int MMU_PRE_STRMADDR13_END;
    volatile unsigned int MMU_PRE_STRMADDR14_STR;
    volatile unsigned int MMU_PRE_STRMADDR14_END;
    volatile unsigned int MMU_PRE_STRMADDR15_STR;
    volatile unsigned int MMU_PRE_STRMADDR15_END;
    volatile U_MMU_PRE_DFX_ARERR_FLAG MMU_PRE_DFX_ARERR_FLAG;
    volatile U_MMU_PRE_DFX_ARERR_ID MMU_PRE_DFX_ARERR_ID;
    volatile unsigned int MMU_PRE_DFX_ARERR_ADDR;
    volatile unsigned int MST_PRE_RESERVED_2;
    volatile U_MMU_PRE_DFX_AWERR_FLAG MMU_PRE_DFX_AWERR_FLAG;
    volatile U_MMU_PRE_DFX_AWERR_ID MMU_PRE_DFX_AWERR_ID;
    volatile unsigned int MMU_PRE_DFX_AWERR_ADDR;
    volatile unsigned int MMU_PRE_RESERVED_3[933];
    volatile U_AXIDFX_ERR AXIDFX_ERR;
    volatile unsigned int RESERVED_AXIDFX1[3];
    volatile U_AXIDFX_AR_R_CNT AXIDFX_AR_R_CNT;
    volatile U_AXIDFX_AW_W_CNT AXIDFX_AW_W_CNT;
    volatile U_AXIDFX_AW_B_CNT AXIDFX_AW_B_CNT;
    volatile unsigned int RESERVED__AXIDFX2;
    volatile U_AXIDFX_AR_R_ID_ERR AXIDFX_AR_R_ID_ERR;
    volatile U_AXIDFX_ERR_ARID AXIDFX_ERR_ARID;
    volatile U_AXIDFX_ERR_RID AXIDFX_ERR_RID;
    volatile unsigned int RESERVED__AXIDFX3;
    volatile U_AXIDFX_AW_W_B_ID_ERR AXIDFX_AW_W_B_ID_ERR;
    volatile U_AXIDFX_ERR_AWID AXIDFX_ERR_AWID;
    volatile U_AXIDFX_ERR_WID AXIDFX_ERR_WID;
    volatile U_AXIDFX_ERR_BID AXIDFX_ERR_BID;
    volatile U_AXIDFX_ARID_TX_0ERR AXIDFX_ARID_TX_0ERR;
    volatile U_AXIDFX_ARID_TX_1ERR AXIDFX_ARID_TX_1ERR;
    volatile U_AXIDFX_ARID_TX_2ERR AXIDFX_ARID_TX_2ERR;
    volatile unsigned int RESERVED__AXIDFX4;
    volatile U_AXIDFX_RID_RX_0ERR AXIDFX_RID_RX_0ERR;
    volatile U_AXIDFX_RID_RX_1ERR AXIDFX_RID_RX_1ERR;
    volatile U_AXIDFX_RID_RX_2ERR AXIDFX_RID_RX_2ERR;
    volatile unsigned int RESERVED__AXIDFX5;
    volatile U_AXIDFX_ARID_RX_0ERR AXIDFX_ARID_RX_0ERR;
    volatile U_AXIDFX_BID_RX_ERR AXIDFX_BID_RX_ERR;
    volatile unsigned int RESERVED__AXIDFX6[2];
    volatile U_AXIDFX_ARID_LEN_0ERR AXIDFX_ARID_LEN_0ERR;
    volatile U_AXIDFX_ARID_LEN_1ERR AXIDFX_ARID_LEN_1ERR;
    volatile U_AXIDFX_ARID_LEN_2ERR AXIDFX_ARID_LEN_2ERR;
    volatile unsigned int RESERVED__AXIDFX7;
    volatile unsigned int AXIDFX_AWLEN_CNT;
    volatile unsigned int AXIDFX_WLEN_CNT;
    volatile unsigned int RESERVED__AXIDFX8[2];
    volatile U_AXIDFX_RESP_ERR AXIDFX_RESP_ERR;
    volatile U_AXIDFX_ERR_RESP AXIDFX_ERR_RESP;
    volatile U_AXIDFX_LEN_ERR AXIDFX_LEN_ERR;
    volatile U_AXIDFX_ERR_LEN AXIDFX_ERR_LEN;
    volatile unsigned int AXIDFX_0RID_FLAG;
    volatile unsigned int AXIDFX_1RID_FLAG;
    volatile U_AXIDFX_2RID_FLAG AXIDFX_2RID_FLAG;
    volatile U_AXIDFX_WID_FLAG AXIDFX_WID_FLAG;
    volatile U_AXIDFX_AXI_ST AXIDFX_AXI_ST;
    volatile unsigned int RESERVED__AXIDFX9[19];
    volatile U_AXIDFX_SOFT_RST_REQ AXIDFX_SOFT_RST_REQ;
    volatile U_AXIDFX_SOFT_RST_ACK AXIDFX_SOFT_RST_ACK;
    volatile unsigned int RESERVED__AXIDFX11[2];
    volatile U_AXIDFX_SOFT_RST_FORCE_REQ_ACK AXIDFX_SOFT_RST_FORCE_REQ_ACK;
    volatile unsigned int AXIDFX_SOFT_RST_STATE0;
    volatile unsigned int AXIDFX_SOFT_RST_STATE1;
    volatile unsigned int RESERVED__AXIDFX12[57];
    volatile unsigned int RESERVED__AXIDFX12_001[7040];
    volatile U_SMMU_MSTR_GLB_BYPASS SMMU_MSTR_GLB_BYPASS;
    volatile U_SMMU_MSTR_DEBUG_MODE SMMU_MSTR_DEBUG_MODE;
    volatile U_SMMU_MSTR_MEM_CTRL SMMU_MSTR_MEM_CTRL;
    volatile U_SMMU_MSTR_CLK_EN SMMU_MSTR_CLK_EN;
    volatile unsigned int SMMU_MSTR_END_REQ_0;
    volatile unsigned int SMMU_MSTR_END_REQ_1;
    volatile U_SMMU_MSTR_END_REQ_2 SMMU_MSTR_END_REQ_2;
    volatile unsigned int SMMU_MSTR_END_ACK_0;
    volatile unsigned int SMMU_MSTR_END_ACK_1;
    volatile U_SMMU_MSTR_END_ACK_2 SMMU_MSTR_END_ACK_2;
    volatile unsigned int SMMU_MSTR_SMRX_START_0;
    volatile unsigned int SMMU_MSTR_SMRX_START_1;
    volatile U_SMMU_MSTR_SMRX_START_2 SMMU_MSTR_SMRX_START_2;
    volatile U_SMMU_MSTR_INPT_SEL SMMU_MSTR_INPT_SEL;
    volatile unsigned int SMMU_MSTR_RESERVED_0[2];
    volatile U_SMMU_MSTR_INTMASK SMMU_MSTR_INTMASK;
    volatile U_SMMU_MSTR_INTRAW SMMU_MSTR_INTRAW;
    volatile U_SMMU_MSTR_INTSTAT SMMU_MSTR_INTSTAT;
    volatile U_SMMU_MSTR_INTCLR SMMU_MSTR_INTCLR;
    volatile U_SMMU_MSTR_DBG_0 SMMU_MSTR_DBG_0;
    volatile unsigned int SMMU_MSTR_DBG_1;
    volatile U_SMMU_MSTR_DBG_2 SMMU_MSTR_DBG_2;
    volatile unsigned int SMMU_MSTR_DBG_3;
    volatile U_SMMU_MSTR_DBG_4 SMMU_MSTR_DBG_4;
    volatile unsigned int SMMU_MSTR_DBG_5;
    volatile unsigned int SMMU_MSTR_RESERVED_1[2];
    volatile U_SMMU_MSTR_DBG_PORT_IN_0 SMMU_MSTR_DBG_PORT_IN_0;
    volatile unsigned int SMMU_MSTR_DBG_PORT_IN_1;
    volatile unsigned int SMMU_MSTR_DBG_PORT_OUT;
    volatile unsigned int SMMU_MSTR_RESERVED_2[33];
    volatile U_SMMU_MSTR_SMRX_0 SMMU_MSTR_SMRX_0[88];
    volatile U_SMMU_MSTR_SMRX_1 SMMU_MSTR_SMRX_1[88];
    volatile U_SMMU_MSTR_SMRX_2 SMMU_MSTR_SMRX_2[144];
    volatile unsigned int RD_CMD_TOTAL_CNT[88];
    volatile unsigned int RD_CMD_MISS_CNT[88];
    volatile unsigned int RD_DATA_TOTAL_CNT[88];
    volatile unsigned int RD_CMD_CASE_CNT[6];
    volatile U_RD_CMD_TRANS_LATENCY RD_CMD_TRANS_LATENCY[50];
    volatile unsigned int WR_CMD_TOTAL_CNT[88];
    volatile unsigned int WR_CMD_MISS_CNT[88];
    volatile unsigned int WR_DATA_TOTAL_CNT[88];
    volatile unsigned int WR_CMD_CASE_CNT[6];
    volatile U_WR_CMD_TRANS_LATENCY WR_CMD_TRANS_LATENCY[50];
    volatile unsigned int RESERVED_MSTR_RESERVED_4[15360];
    volatile U_SMMU_SCR SMMU_SCR;
    volatile U_SMMU_MEMCTRL SMMU_MEMCTRL;
    volatile U_SMMU_LP_CTRL SMMU_LP_CTRL;
    volatile unsigned int SMMU_COMN_RESERVED_1;
    volatile U_SMMU_INTMASK_NS SMMU_INTMASK_NS;
    volatile U_SMMU_INTRAW_NS SMMU_INTRAW_NS;
    volatile U_SMMU_INTSTAT_NS SMMU_INTSTAT_NS;
    volatile U_SMMU_INTCLR_NS SMMU_INTCLR_NS;
    volatile U_SMMU_SMRX_NS SMMU_SMRX_NS[116];
    volatile unsigned int SMMU_RLD_EN0_NS;
    volatile unsigned int SMMU_RLD_EN1_NS;
    volatile U_SMMU_RLD_EN2_NS SMMU_RLD_EN2_NS;
    volatile U_SMMU_GLB_ALLOC_ST SMMU_GLB_ALLOC_ST;
    volatile U_SMMU_CB_SCTRL SMMU_CB_SCTRL;
    volatile unsigned int SMMU_CB_TTBR0;
    volatile unsigned int SMMU_CB_TTBR1;
    volatile U_SMMU_CB_TTBCR SMMU_CB_TTBCR;
    volatile unsigned int SMMU_COMN_RESERVED_2;
    volatile U_SMMU_SCACHEI_ALL SMMU_SCACHEI_ALL;
    volatile U_SMMU_SCACHEI_L1 SMMU_SCACHEI_L1;
    volatile U_SMMU_SCACHEI_L2 SMMU_SCACHEI_L2;
    volatile U_SMMU_CB_PA_MSB SMMU_CB_PA_MSB;
    volatile U_SMMU_CB_TTBR_MSB SMMU_CB_TTBR_MSB;
    volatile unsigned int SMMU_MAIR_NS;
    volatile unsigned int SMMU_COMN_RESERVED_3[53];
    volatile U_SMMU_ERR_ADDR_MSB_NS SMMU_ERR_ADDR_MSB_NS;
    volatile unsigned int SMMU_ERR_RDADDR_NS;
    volatile unsigned int SMMU_ERR_WRADDR_NS;
    volatile unsigned int SMMU_COMN_RESERVED_4;
    volatile unsigned int SMMU_FAULT_ADDR_TCU;
    volatile U_SMMU_FAULT_ID_TCU SMMU_FAULT_ID_TCU;
    volatile unsigned int SMMU_COMN_RESERVED_5[2];
    volatile unsigned int SMMU_FAULT_ADDR_TBUX;
    volatile U_SMMU_FAULT_ID_TBUX SMMU_FAULT_ID_TBUX;
    volatile U_SMMU_FAULT_INFOX SMMU_FAULT_INFOX[22];
    volatile unsigned int SMMU_COMN_RESERVED_6[96];
    volatile U_SMMU_SMRX_S SMMU_SMRX_S[88];
    volatile unsigned int SMMU_COMN_RESERVED_7[36];
    volatile unsigned int SMMU_RLD_EN0_S;
    volatile unsigned int SMMU_RLD_EN1_S;
    volatile U_SMMU_RLD_EN2_S SMMU_RLD_EN2_S;
    volatile unsigned int SMMU_COMN_RESERVED_8;
    volatile U_SMMU_INTMAS_S SMMU_INTMAS_S;
    volatile U_SMMU_INTRAW_S SMMU_INTRAW_S;
    volatile U_SMMU_INTSTAT_S SMMU_INTSTAT_S;
    volatile U_SMMU_INTCLR_S SMMU_INTCLR_S;
    volatile U_SMMU_SCR_S SMMU_SCR_S;
    volatile U_SMMU_SCB_SCTRL SMMU_SCB_SCTRL;
    volatile unsigned int SMMU_SCB_TTBR;
    volatile U_SMMU_SCB_TTBCR SMMU_SCB_TTBCR;
    volatile unsigned int SMMU_COMN_RESERVED_9;
    volatile U_SMMU_SCB_PA_MSB SMMU_SCB_PA_MSB;
    volatile U_SMMU_SCB_TTBR_MSB SMMU_SCB_TTBR_MSB;
    volatile U_SMMU_ERR_ADDR_MSB_S SMMU_ERR_ADDR_MSB_S;
    volatile unsigned int SMMU_ERR_RDADDR_S;
    volatile unsigned int SMMU_ERR_WRADDR_S;
    volatile unsigned int SMMU_MAIR_S;
    volatile unsigned int SMMU_COMN_RESERVED_10;
    volatile U_SMMU_SMRX_S1 SMMU_SMRX_S1[88];
    volatile unsigned int SMMU_COMN_RESERVED_11[15832];
    volatile U_SMMU_SMRX_P SMMU_SMRX_P[88];
    volatile unsigned int SMMU_COMN_RESERVED_12[36];
    volatile unsigned int SMMU_RLD_EN0_P;
    volatile unsigned int SMMU_RLD_EN1_P;
    volatile U_SMMU_RLD_EN2_P SMMU_RLD_EN2_P;
    volatile unsigned int SMMU_COMN_RESERVED_13;
    volatile U_SMMU_INTMAS_P SMMU_INTMAS_P;
    volatile U_SMMU_INTRAW_P SMMU_INTRAW_P;
    volatile U_SMMU_INTSTAT_P SMMU_INTSTAT_P;
    volatile U_SMMU_INTCLR_P SMMU_INTCLR_P;
    volatile U_SMMU_SCR_P SMMU_SCR_P;
    volatile U_SMMU_PCB_SCTRL SMMU_PCB_SCTRL;
    volatile unsigned int SMMU_PCB_TTBR;
    volatile U_SMMU_PCB_TTBCR SMMU_PCB_TTBCR;
    volatile unsigned int SMMU_COMN_RESERVED_14;
    volatile U_SMMU_PCB_PA_MSB SMMU_PCB_PA_MSB;
    volatile U_SMMU_PCB_TTBR_MSB SMMU_PCB_TTBR_MSB;
    volatile unsigned int SMMU_MAIR_P;
    volatile U_SMMU_ERR_ADDR_MSB_P SMMU_ERR_ADDR_MSB_P;
    volatile unsigned int SMMU_ERR_RDADDR_P;
    volatile unsigned int SMMU_ERR_WRADDR_P;
} S_HEVC_AVC_REGS_TYPE;
typedef struct {
    volatile U_VEDU_VCPI_INTMASK VEDU_VCPI_INTMASK;
    volatile U_VEDU_VCPI_INTCLR VEDU_VCPI_INTCLR;
    volatile U_VEDU_VCPI_START VEDU_VCPI_START;
    volatile U_VEDU_VCPI_CNTCLR VEDU_VCPI_CNTCLR;
    volatile unsigned int VEDU_VCPI_FRAMENO;
    volatile U_VEDU_VCPI_BP_POS VEDU_VCPI_BP_POS;
    volatile unsigned int VEDU_VCPI_TIMEOUT;
    volatile U_VEDU_VCPI_MODE VEDU_VCPI_MODE;
    volatile U_VEDU_VCPI_TILE_SIZE VEDU_VCPI_TILE_SIZE;
    volatile U_VEDU_VCPI_PICSIZE_PIX VEDU_VCPI_PICSIZE_PIX;
    volatile U_VEDU_VCPI_MULTISLC VEDU_VCPI_MULTISLC;
    volatile U_VEDU_VCPI_QPCFG VEDU_VCPI_QPCFG;
    volatile U_VEDU_VCPI_DBLKCFG VEDU_VCPI_DBLKCFG;
    volatile U_VEDU_VCPI_LOW_POWER VEDU_VCPI_LOW_POWER;
    volatile U_VEDU_VCPI_OUTSTD VEDU_VCPI_OUTSTD;
    volatile U_VEDU_VCPI_TMV_LOAD VEDU_VCPI_TMV_LOAD;
    volatile U_VEDU_VCPI_CROSS_TILE_SLC VEDU_VCPI_CROSS_TILE_SLC;
    volatile U_VEDU_VCPI_MEM_CTRL VEDU_VCPI_MEM_CTRL;
    volatile U_VEDU_VCPI_INTRA_INTER_CU_EN VEDU_VCPI_INTRA_INTER_CU_EN;
    volatile U_VEDU_VCPI_VLC_CONFIG VEDU_VCPI_VLC_CONFIG;
    volatile U_VEDU_VCPI_PRE_JUDGE_EXT_EN VEDU_VCPI_PRE_JUDGE_EXT_EN;
    volatile U_VEDU_VCPI_PRE_JUDGE_COST_THR VEDU_VCPI_PRE_JUDGE_COST_THR;
    volatile U_VEDU_VCPI_IBLK_PRE_MV_THR VEDU_VCPI_IBLK_PRE_MV_THR;
    volatile U_VEDU_VCPI_PME_PARAM VEDU_VCPI_PME_PARAM;
    volatile U_VEDU_VCPI_PIC_STRONG_EN VEDU_VCPI_PIC_STRONG_EN;
    volatile U_VEDU_VCPI_REF_FLAG VEDU_VCPI_REF_FLAG;
    volatile U_VEDU_VCPI_RC_ENABLE VEDU_VCPI_RC_ENABLE;
    volatile U_VEDU_VCPI_I_SLC_INSERT VEDU_VCPI_I_SLC_INSERT;
    volatile U_VEDU_VCPI_CLKDIV_ENABLE VEDU_VCPI_CLKDIV_ENABLE;
    volatile U_VEDU_VCPI_WCHN_BYPASS VEDU_VCPI_WCHN_BYPASS;
    volatile U_VEDU_VCPI_RCHN_BYPASS VEDU_VCPI_RCHN_BYPASS;
    volatile U_VEDU_VCPI_SW_L0_SIZE VEDU_VCPI_SW_L0_SIZE;
    volatile U_VEDU_VCPI_SW_L1_SIZE VEDU_VCPI_SW_L1_SIZE;
    volatile unsigned int VEDU_VCPI_PMEINFO_ST_ADDR;
    volatile unsigned int VEDU_VCPI_PMEINFO_LD0_ADDR;
    volatile unsigned int VEDU_VCPI_PMEINFO_LD1_ADDR;
    volatile unsigned int VEDU_VCPI_TUNLCELL_ADDR;
    volatile unsigned int VEDU_VCPI_SRC_YADDR;
    volatile unsigned int VEDU_VCPI_SRC_CADDR;
    volatile unsigned int VEDU_VCPI_SRC_VADDR;
    volatile unsigned int VEDU_VCPI_YH_ADDR;
    volatile unsigned int VEDU_VCPI_CH_ADDR;
    volatile U_VEDU_VCPI_STRIDE VEDU_VCPI_STRIDE;
    volatile unsigned int VEDU_VCPI_REC_YADDR;
    volatile unsigned int VEDU_VCPI_REC_CADDR;
    volatile U_VEDU_VCPI_REC_STRIDE VEDU_VCPI_REC_STRIDE;
    volatile unsigned int VEDU_VCPI_REC_YH_ADDR;
    volatile unsigned int VEDU_VCPI_REC_CH_ADDR;
    volatile U_VEDU_VCPI_REC_HEAD_STRIDE VEDU_VCPI_REC_HEAD_STRIDE;
    volatile unsigned int VEDU_VCPI_REFY_L0_ADDR;
    volatile unsigned int VEDU_VCPI_REFC_L0_ADDR;
    volatile U_VEDU_VCPI_REF_L0_STRIDE VEDU_VCPI_REF_L0_STRIDE;
    volatile unsigned int VEDU_VCPI_REFYH_L0_ADDR;
    volatile unsigned int VEDU_VCPI_REFCH_L0_ADDR;
    volatile U_VEDU_VCPI_REFH_L0_STRIDE VEDU_VCPI_REFH_L0_STRIDE;
    volatile unsigned int VEDU_VCPI_PMELD_L0_ADDR;
    volatile unsigned int VEDU_VCPI_REFY_L1_ADDR;
    volatile unsigned int VEDU_VCPI_REFC_L1_ADDR;
    volatile U_VEDU_VCPI_REF_L1_STRIDE VEDU_VCPI_REF_L1_STRIDE;
    volatile unsigned int VEDU_VCPI_REFYH_L1_ADDR;
    volatile unsigned int VEDU_VCPI_REFCH_L1_ADDR;
    volatile U_VEDU_VCPI_REFH_L1_STRIDE VEDU_VCPI_REFH_L1_STRIDE;
    volatile unsigned int VEDU_VCPI_PMELD_L1_ADDR;
    volatile unsigned int VEDU_VCPI_PMEST_ADDR;
    volatile unsigned int VEDU_VCPI_NBI_UPST_ADDR;
    volatile unsigned int VEDU_VCPI_NBI_MVST_ADDR;
    volatile unsigned int VEDU_VCPI_NBI_MVLD_ADDR;
    volatile unsigned int VEDU_VCPI_STRMADDR;
    volatile unsigned int VEDU_VCPI_SWPTRADDR;
    volatile unsigned int VEDU_VCPI_SRPTRADDR;
    volatile unsigned int VEDU_VCPI_LLILD_ADDR;
    volatile U_VEDU_VCPI_STRFMT VEDU_VCPI_STRFMT;
    volatile U_VEDU_VCPI_SCALE_PARA VEDU_VCPI_SCALE_PARA;
    volatile U_VEDU_VCPI_ORI_PICSIZE VEDU_VCPI_ORI_PICSIZE;
    volatile unsigned int VEDU_VCPI_MEM_CTRL_T16_S;
    volatile unsigned int VEDU_VCPI_PMEST_STRIDE;
    volatile unsigned int VEDU_VCPI_PMELD_STRIDE;
    volatile U_VEDU_VCPI_INTMASK_S VEDU_VCPI_INTMASK_S;
    volatile U_VEDU_VCPI_INTCLR_S VEDU_VCPI_INTCLR_S;
    volatile U_VEDU_CURLD_NARROW_THR VEDU_CURLD_NARROW_THR;
    volatile U_VEDU_ARGBTO444_PARAMETER0 VEDU_ARGBTO444_PARAMETER0;
    volatile U_VEDU_ARGBTO444_PARAMETER1 VEDU_ARGBTO444_PARAMETER1;
    volatile U_VEDU_ARGBTO444_PARAMETER2 VEDU_ARGBTO444_PARAMETER2;
    volatile U_VEDU_ARGBTO444_PARAMETER3 VEDU_ARGBTO444_PARAMETER3;
    volatile U_VEDU_ARGBTO444_PARAMETER4 VEDU_ARGBTO444_PARAMETER4;
    volatile U_VEDU_ARGBTO444_PARAMETER5 VEDU_ARGBTO444_PARAMETER5;
    volatile U_VEDU_ARGBTO444_PARAMETER6 VEDU_ARGBTO444_PARAMETER6;
    volatile U_VEDU_444TO422_PARAMETER VEDU_444TO422_PARAMETER;
    volatile U_VEDU_422TO420_PARAMETER VEDU_422TO420_PARAMETER;
    volatile unsigned int VEDU_VCPI_MEM_CTRL_T16_T;
    volatile unsigned int VEDU_VCPI_MEM_CTRL_T16_B;
    volatile U_VEDU_VCTRL_ROI_CFG0 VEDU_VCTRL_ROI_CFG0;
    volatile U_VEDU_VCTRL_ROI_CFG1 VEDU_VCTRL_ROI_CFG1;
    volatile U_VEDU_VCTRL_ROI_CFG2 VEDU_VCTRL_ROI_CFG2;
    volatile U_VEDU_VCTRL_ROI_SIZE_0 VEDU_VCTRL_ROI_SIZE_0;
    volatile U_VEDU_VCTRL_ROI_SIZE_1 VEDU_VCTRL_ROI_SIZE_1;
    volatile U_VEDU_VCTRL_ROI_SIZE_2 VEDU_VCTRL_ROI_SIZE_2;
    volatile U_VEDU_VCTRL_ROI_SIZE_3 VEDU_VCTRL_ROI_SIZE_3;
    volatile U_VEDU_VCTRL_ROI_SIZE_4 VEDU_VCTRL_ROI_SIZE_4;
    volatile U_VEDU_VCTRL_ROI_SIZE_5 VEDU_VCTRL_ROI_SIZE_5;
    volatile U_VEDU_VCTRL_ROI_SIZE_6 VEDU_VCTRL_ROI_SIZE_6;
    volatile U_VEDU_VCTRL_ROI_SIZE_7 VEDU_VCTRL_ROI_SIZE_7;
    volatile U_VEDU_VCTRL_ROI_START_0 VEDU_VCTRL_ROI_START_0;
    volatile U_VEDU_VCTRL_ROI_START_1 VEDU_VCTRL_ROI_START_1;
    volatile U_VEDU_VCTRL_ROI_START_2 VEDU_VCTRL_ROI_START_2;
    volatile U_VEDU_VCTRL_ROI_START_3 VEDU_VCTRL_ROI_START_3;
    volatile U_VEDU_VCTRL_ROI_START_4 VEDU_VCTRL_ROI_START_4;
    volatile U_VEDU_VCTRL_ROI_START_5 VEDU_VCTRL_ROI_START_5;
    volatile U_VEDU_VCTRL_ROI_START_6 VEDU_VCTRL_ROI_START_6;
    volatile U_VEDU_VCTRL_ROI_START_7 VEDU_VCTRL_ROI_START_7;
    volatile U_VEDU_VCTRL_LCU_TARGET_BIT VEDU_VCTRL_LCU_TARGET_BIT;
    volatile U_VEDU_VCTRL_NARROW_THRESHOLD VEDU_VCTRL_NARROW_THRESHOLD;
    volatile U_VEDU_VCTRL_LCU_BASELINE VEDU_VCTRL_LCU_BASELINE;
    volatile U_VEDU_VCTRL_NORM_TR16X16_COEFF_DENOISE VEDU_VCTRL_NORM_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_NORM_COEFF_DENOISE VEDU_VCTRL_NORM_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_NORM_ENG_DENOISE VEDU_VCTRL_NORM_ENG_DENOISE;
    volatile U_VEDU_VCTRL_SKIN_TR16X16_COEFF_DENOISE VEDU_VCTRL_SKIN_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SKIN_COEFF_DENOISE VEDU_VCTRL_SKIN_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SKIN_ENG_DENOISE VEDU_VCTRL_SKIN_ENG_DENOISE;
    volatile U_VEDU_VCTRL_HEDGE_TR16X16_COEFF_DENOISE VEDU_VCTRL_HEDGE_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGE_COEFF_DENOISE VEDU_VCTRL_HEDGE_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGE_ENG_DENOISE VEDU_VCTRL_HEDGE_ENG_DENOISE;
    volatile U_VEDU_VCTRL_HEDGEMOV_TR16X16_COEFF_DENOISE VEDU_VCTRL_HEDGEMOV_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGEMOV_COEFF_DENOISE VEDU_VCTRL_HEDGEMOV_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_HEDGEMOV_ENG_DENOISE VEDU_VCTRL_HEDGEMOV_ENG_DENOISE;
    volatile U_VEDU_VCTRL_STATIC_TR16X16_COEFF_DENOISE VEDU_VCTRL_STATIC_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_STATIC_COEFF_DENOISE VEDU_VCTRL_STATIC_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_STATIC_ENG_DENOISE VEDU_VCTRL_STATIC_ENG_DENOISE;
    volatile U_VEDU_VCTRL_SOBELSTR_TR16X16_COEFF_DENOISE VEDU_VCTRL_SOBELSTR_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELSTR_COEFF_DENOISE VEDU_VCTRL_SOBELSTR_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELSTR_ENG_DENOISE VEDU_VCTRL_SOBELSTR_ENG_DENOISE;
    volatile U_VEDU_VCTRL_SOBELWEAK_TR16X16_COEFF_DENOISE VEDU_VCTRL_SOBELWEAK_TR16X16_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELWEAK_COEFF_DENOISE VEDU_VCTRL_SOBELWEAK_COEFF_DENOISE;
    volatile U_VEDU_VCTRL_SOBELWEAK_ENG_DENOISE VEDU_VCTRL_SOBELWEAK_ENG_DENOISE;
    volatile U_VEDU_VCTRL_INTRA_RDO_FACTOR_0 VEDU_VCTRL_INTRA_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_INTRA_RDO_FACTOR_1 VEDU_VCTRL_INTRA_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_INTRA_RDO_FACTOR_2 VEDU_VCTRL_INTRA_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_MRG_RDO_FACTOR_0 VEDU_VCTRL_MRG_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_MRG_RDO_FACTOR_1 VEDU_VCTRL_MRG_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_MRG_RDO_FACTOR_2 VEDU_VCTRL_MRG_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_FME_RDO_FACTOR_0 VEDU_VCTRL_FME_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_FME_RDO_FACTOR_1 VEDU_VCTRL_FME_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_FME_RDO_FACTOR_2 VEDU_VCTRL_FME_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_SEL_INTRA_RDO_FACTOR VEDU_VCTRL_SEL_INTRA_RDO_FACTOR;
    volatile U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_0 VEDU_VCTRL_SEL_INTER_RDO_FACTOR_0;
    volatile U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_1 VEDU_VCTRL_SEL_INTER_RDO_FACTOR_1;
    volatile U_VEDU_VCTRL_SEL_INTER_RDO_FACTOR_2 VEDU_VCTRL_SEL_INTER_RDO_FACTOR_2;
    volatile U_VEDU_VCTRL_SEL_LAYER_RDO_FACTOR VEDU_VCTRL_SEL_LAYER_RDO_FACTOR;
    volatile U_VEDU_CURLD_GCFG VEDU_CURLD_GCFG;
    volatile U_VEDU_CURLD_CLIP_THR VEDU_CURLD_CLIP_THR;
    volatile U_VEDU_PME_SW_ADAPT_EN VEDU_PME_SW_ADAPT_EN;
    volatile U_VEDU_PME_SW_THR0 VEDU_PME_SW_THR0;
    volatile U_VEDU_PME_SW_THR1 VEDU_PME_SW_THR1;
    volatile U_VEDU_PME_SW_THR2 VEDU_PME_SW_THR2;
    volatile U_VEDU_PME_SKIP_PRE VEDU_PME_SKIP_PRE;
    volatile U_VEDU_PME_TR_WEIGHTX VEDU_PME_TR_WEIGHTX;
    volatile U_VEDU_PME_TR_WEIGHTY VEDU_PME_TR_WEIGHTY;
    volatile U_VEDU_PME_SR_WEIGHT VEDU_PME_SR_WEIGHT;
    volatile U_VEDU_PME_INTRABLK_DET VEDU_PME_INTRABLK_DET;
    volatile U_VEDU_PME_INTRABLK_DET_THR VEDU_PME_INTRABLK_DET_THR;
    volatile U_VEDU_PME_SKIN_THR VEDU_PME_SKIN_THR;
    volatile U_VEDU_PME_INTRA_LOWPOW VEDU_PME_INTRA_LOWPOW;
    volatile U_VEDU_PME_IBLK_COST_THR VEDU_PME_IBLK_COST_THR;
    volatile U_VEDU_PME_STRONG_EDGE VEDU_PME_STRONG_EDGE;
    volatile U_VEDU_PME_LARGE_MOVE_THR VEDU_PME_LARGE_MOVE_THR;
    volatile U_VEDU_PME_INTER_STRONG_EDGE VEDU_PME_INTER_STRONG_EDGE;
    volatile U_VEDU_PME_NEW_COST VEDU_PME_NEW_COST;
    volatile U_VEDU_PME_WINDOW_SIZE0_L0 VEDU_PME_WINDOW_SIZE0_L0;
    volatile U_VEDU_PME_WINDOW_SIZE1_L0 VEDU_PME_WINDOW_SIZE1_L0;
    volatile U_VEDU_PME_WINDOW_SIZE2_L0 VEDU_PME_WINDOW_SIZE2_L0;
    volatile U_VEDU_PME_WINDOW_SIZE3_L0 VEDU_PME_WINDOW_SIZE3_L0;
    volatile U_VEDU_PME_COST_OFFSET VEDU_PME_COST_OFFSET;
    volatile U_VEDU_PME_SAFE_CFG VEDU_PME_SAFE_CFG;
    volatile U_VEDU_PME_IBLK_REFRESH VEDU_PME_IBLK_REFRESH;
    volatile U_VEDU_PME_IBLK_REFRESH_NUM VEDU_PME_IBLK_REFRESH_NUM;
    volatile U_VEDU_PME_QPG_RC_THR0 VEDU_PME_QPG_RC_THR0;
    volatile U_VEDU_PME_QPG_RC_THR1 VEDU_PME_QPG_RC_THR1;
    volatile U_VEDU_PME_LOW_LUMA_THR VEDU_PME_LOW_LUMA_THR;
    volatile U_VEDU_PME_PBLK_PRE1 VEDU_PME_PBLK_PRE1;
    volatile U_VEDU_PME_CHROMA_FLAT VEDU_PME_CHROMA_FLAT;
    volatile U_VEDU_PME_LUMA_FLAT VEDU_PME_LUMA_FLAT;
    volatile U_VEDU_PME_MADI_FLAT VEDU_PME_MADI_FLAT;
    volatile U_VEDU_QPG_MAX_MIN_QP VEDU_QPG_MAX_MIN_QP;
    volatile U_VEDU_QPG_ROW_TARGET_BITS VEDU_QPG_ROW_TARGET_BITS;
    volatile U_VEDU_QPG_AVERAGE_LCU_BITS VEDU_QPG_AVERAGE_LCU_BITS;
    volatile U_VEDU_QPG_LOWLUMA VEDU_QPG_LOWLUMA;
    volatile U_VEDU_QPG_HEDGE VEDU_QPG_HEDGE;
    volatile U_VEDU_QPG_HEDGE_MOVE VEDU_QPG_HEDGE_MOVE;
    volatile U_VEDU_QPG_LARGE_MOVE VEDU_QPG_LARGE_MOVE;
    volatile U_VEDU_QPG_SKIN VEDU_QPG_SKIN;
    volatile U_VEDU_QPG_INTRA_DET VEDU_QPG_INTRA_DET;
    volatile U_VEDU_QPG_H264_SMOOTH VEDU_QPG_H264_SMOOTH;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG0 VEDU_QPG_CU_QP_DELTA_THRESH_REG0;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG1 VEDU_QPG_CU_QP_DELTA_THRESH_REG1;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG2 VEDU_QPG_CU_QP_DELTA_THRESH_REG2;
    volatile U_VEDU_QPG_CU_QP_DELTA_THRESH_REG3 VEDU_QPG_CU_QP_DELTA_THRESH_REG3;
    volatile U_VEDU_QPG_DELTA_LEVEL VEDU_QPG_DELTA_LEVEL;
    volatile U_VEDU_QPG_MADI_SWITCH_THR VEDU_QPG_MADI_SWITCH_THR;
    volatile U_VEDU_QPG_CU32_DELTA VEDU_QPG_CU32_DELTA;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG00 VEDU_QPG_QP_LAMBDA_CTRL_REG00;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG01 VEDU_QPG_QP_LAMBDA_CTRL_REG01;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG02 VEDU_QPG_QP_LAMBDA_CTRL_REG02;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG03 VEDU_QPG_QP_LAMBDA_CTRL_REG03;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG04 VEDU_QPG_QP_LAMBDA_CTRL_REG04;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG05 VEDU_QPG_QP_LAMBDA_CTRL_REG05;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG06 VEDU_QPG_QP_LAMBDA_CTRL_REG06;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG07 VEDU_QPG_QP_LAMBDA_CTRL_REG07;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG08 VEDU_QPG_QP_LAMBDA_CTRL_REG08;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG09 VEDU_QPG_QP_LAMBDA_CTRL_REG09;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG10 VEDU_QPG_QP_LAMBDA_CTRL_REG10;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG11 VEDU_QPG_QP_LAMBDA_CTRL_REG11;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG12 VEDU_QPG_QP_LAMBDA_CTRL_REG12;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG13 VEDU_QPG_QP_LAMBDA_CTRL_REG13;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG14 VEDU_QPG_QP_LAMBDA_CTRL_REG14;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG15 VEDU_QPG_QP_LAMBDA_CTRL_REG15;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG16 VEDU_QPG_QP_LAMBDA_CTRL_REG16;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG17 VEDU_QPG_QP_LAMBDA_CTRL_REG17;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG18 VEDU_QPG_QP_LAMBDA_CTRL_REG18;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG19 VEDU_QPG_QP_LAMBDA_CTRL_REG19;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG20 VEDU_QPG_QP_LAMBDA_CTRL_REG20;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG21 VEDU_QPG_QP_LAMBDA_CTRL_REG21;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG22 VEDU_QPG_QP_LAMBDA_CTRL_REG22;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG23 VEDU_QPG_QP_LAMBDA_CTRL_REG23;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG24 VEDU_QPG_QP_LAMBDA_CTRL_REG24;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG25 VEDU_QPG_QP_LAMBDA_CTRL_REG25;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG26 VEDU_QPG_QP_LAMBDA_CTRL_REG26;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG27 VEDU_QPG_QP_LAMBDA_CTRL_REG27;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG28 VEDU_QPG_QP_LAMBDA_CTRL_REG28;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG29 VEDU_QPG_QP_LAMBDA_CTRL_REG29;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG30 VEDU_QPG_QP_LAMBDA_CTRL_REG30;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG31 VEDU_QPG_QP_LAMBDA_CTRL_REG31;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG32 VEDU_QPG_QP_LAMBDA_CTRL_REG32;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG33 VEDU_QPG_QP_LAMBDA_CTRL_REG33;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG34 VEDU_QPG_QP_LAMBDA_CTRL_REG34;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG35 VEDU_QPG_QP_LAMBDA_CTRL_REG35;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG36 VEDU_QPG_QP_LAMBDA_CTRL_REG36;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG37 VEDU_QPG_QP_LAMBDA_CTRL_REG37;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG38 VEDU_QPG_QP_LAMBDA_CTRL_REG38;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG39 VEDU_QPG_QP_LAMBDA_CTRL_REG39;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG40 VEDU_QPG_QP_LAMBDA_CTRL_REG40;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG41 VEDU_QPG_QP_LAMBDA_CTRL_REG41;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG42 VEDU_QPG_QP_LAMBDA_CTRL_REG42;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG43 VEDU_QPG_QP_LAMBDA_CTRL_REG43;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG44 VEDU_QPG_QP_LAMBDA_CTRL_REG44;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG45 VEDU_QPG_QP_LAMBDA_CTRL_REG45;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG46 VEDU_QPG_QP_LAMBDA_CTRL_REG46;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG47 VEDU_QPG_QP_LAMBDA_CTRL_REG47;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG48 VEDU_QPG_QP_LAMBDA_CTRL_REG48;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG49 VEDU_QPG_QP_LAMBDA_CTRL_REG49;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG50 VEDU_QPG_QP_LAMBDA_CTRL_REG50;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG51 VEDU_QPG_QP_LAMBDA_CTRL_REG51;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG52 VEDU_QPG_QP_LAMBDA_CTRL_REG52;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG53 VEDU_QPG_QP_LAMBDA_CTRL_REG53;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG54 VEDU_QPG_QP_LAMBDA_CTRL_REG54;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG55 VEDU_QPG_QP_LAMBDA_CTRL_REG55;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG56 VEDU_QPG_QP_LAMBDA_CTRL_REG56;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG57 VEDU_QPG_QP_LAMBDA_CTRL_REG57;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG58 VEDU_QPG_QP_LAMBDA_CTRL_REG58;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG59 VEDU_QPG_QP_LAMBDA_CTRL_REG59;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG60 VEDU_QPG_QP_LAMBDA_CTRL_REG60;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG61 VEDU_QPG_QP_LAMBDA_CTRL_REG61;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG62 VEDU_QPG_QP_LAMBDA_CTRL_REG62;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG63 VEDU_QPG_QP_LAMBDA_CTRL_REG63;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG64 VEDU_QPG_QP_LAMBDA_CTRL_REG64;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG65 VEDU_QPG_QP_LAMBDA_CTRL_REG65;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG66 VEDU_QPG_QP_LAMBDA_CTRL_REG66;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG67 VEDU_QPG_QP_LAMBDA_CTRL_REG67;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG68 VEDU_QPG_QP_LAMBDA_CTRL_REG68;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG69 VEDU_QPG_QP_LAMBDA_CTRL_REG69;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG70 VEDU_QPG_QP_LAMBDA_CTRL_REG70;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG71 VEDU_QPG_QP_LAMBDA_CTRL_REG71;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG72 VEDU_QPG_QP_LAMBDA_CTRL_REG72;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG73 VEDU_QPG_QP_LAMBDA_CTRL_REG73;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG74 VEDU_QPG_QP_LAMBDA_CTRL_REG74;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG75 VEDU_QPG_QP_LAMBDA_CTRL_REG75;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG76 VEDU_QPG_QP_LAMBDA_CTRL_REG76;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG77 VEDU_QPG_QP_LAMBDA_CTRL_REG77;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG78 VEDU_QPG_QP_LAMBDA_CTRL_REG78;
    volatile U_VEDU_QPG_QP_LAMBDA_CTRL_REG79 VEDU_QPG_QP_LAMBDA_CTRL_REG79;
    volatile U_VEDU_QPG_LAMBDA_MODE VEDU_QPG_LAMBDA_MODE;
    volatile U_VEDU_QPG_QP_RESTRAIN VEDU_QPG_QP_RESTRAIN;
    volatile unsigned int VEDU_QPG_CU_MIN_SAD_THRESH_0;
    volatile unsigned int VEDU_QPG_CU_MIN_SAD_THRESH_1;
    volatile U_VEDU_QPG_CU_MIN_SAD_REG VEDU_QPG_CU_MIN_SAD_REG;
    volatile U_VEDU_QPG_FLAT_REGION VEDU_QPG_FLAT_REGION;
    volatile U_VEDU_IME_INTER_MODE VEDU_IME_INTER_MODE;
    volatile U_VEDU_IME_RDOCFG VEDU_IME_RDOCFG;
    volatile U_VEDU_IME_FME_LPOW_THR VEDU_IME_FME_LPOW_THR;
    volatile U_VEDU_IME_NO_INTRA_ANG_EN VEDU_IME_NO_INTRA_ANG_EN;
    volatile U_VEDU_IME_NO_INTRA_ANG_MV_THR VEDU_IME_NO_INTRA_ANG_MV_THR;
    volatile U_VEDU_MRG_FORCE_ZERO_EN VEDU_MRG_FORCE_ZERO_EN;
    volatile U_VEDU_MRG_FORCE_SKIP_EN VEDU_MRG_FORCE_SKIP_EN;
    volatile U_VEDU_INTRA_INTER_AVAIL VEDU_INTRA_INTER_AVAIL;
    volatile U_VEDU_INTRA_DC_SHIFT VEDU_INTRA_DC_SHIFT;
    volatile U_VEDU_INTRA_BIT_WEIGHT VEDU_INTRA_BIT_WEIGHT;
    volatile U_VEDU_INTRA_DC_MADI VEDU_INTRA_DC_MADI;
    volatile U_VEDU_INTRA_RDO_COST_OFFSET VEDU_INTRA_RDO_COST_OFFSET;
    volatile U_VEDU_INTRA_CHNL4_ANG_0EN VEDU_INTRA_CHNL4_ANG_0EN;
    volatile U_VEDU_INTRA_CHNL8_ANG_0EN VEDU_INTRA_CHNL8_ANG_0EN;
    volatile U_VEDU_INTRA_CHNL8_ANG_1EN VEDU_INTRA_CHNL8_ANG_1EN;
    volatile U_VEDU_INTRA_CHNL16_ANG_0EN VEDU_INTRA_CHNL16_ANG_0EN;
    volatile U_VEDU_INTRA_CHNL16_ANG_1EN VEDU_INTRA_CHNL16_ANG_1EN;
    volatile U_VEDU_INTRA_CHROMA_ANG_EN VEDU_INTRA_CHROMA_ANG_EN;
    volatile unsigned int VEDU_PMV_POC_0;
    volatile unsigned int VEDU_PMV_POC_1;
    volatile unsigned int VEDU_PMV_POC_2;
    volatile unsigned int VEDU_PMV_POC_3;
    volatile unsigned int VEDU_PMV_POC_4;
    volatile unsigned int VEDU_PMV_POC_5;
    volatile U_VEDU_PMV_TMV_EN VEDU_PMV_TMV_EN;
    volatile U_VEDU_TQITQ_DEADZONE VEDU_TQITQ_DEADZONE;
    volatile U_VEDU_SEL_INTRA_ABS_OFFSET0 VEDU_SEL_INTRA_ABS_OFFSET0;
    volatile U_VEDU_SEL_INTRA_ABS_OFFSET1 VEDU_SEL_INTRA_ABS_OFFSET1;
    volatile U_VEDU_SEL_INTER_ABS_OFFSET0 VEDU_SEL_INTER_ABS_OFFSET0;
    volatile U_VEDU_SEL_OFFSET_STRENGTH VEDU_SEL_OFFSET_STRENGTH;
    volatile U_VEDU_SEL_CU32_DC_AC_TH_OFFSET VEDU_SEL_CU32_DC_AC_TH_OFFSET;
    volatile U_VEDU_SEL_CU32_QP_TH VEDU_SEL_CU32_QP_TH;
    volatile U_VEDU_SEL_RES_DC_AC_TH VEDU_SEL_RES_DC_AC_TH;
    volatile U_VEDU_EMAR_WAIT_TIM_OUT VEDU_EMAR_WAIT_TIM_OUT;
    volatile U_VEDU_EMAR_RCH_RPT_TH0 VEDU_EMAR_RCH_RPT_TH0;
    volatile U_VEDU_EMAR_RCH_RPT_TH1 VEDU_EMAR_RCH_RPT_TH1;
    volatile U_VEDU_EMAR_RCH_RPT_TH2 VEDU_EMAR_RCH_RPT_TH2;
    volatile U_VEDU_EMAR_WCH_RPT_TH0 VEDU_EMAR_WCH_RPT_TH0;
    volatile U_VEDU_EMAR_WCH_RPT_TH1 VEDU_EMAR_WCH_RPT_TH1;
    volatile U_VEDU_EMAR_WCH_RPT_TH2 VEDU_EMAR_WCH_RPT_TH2;
    volatile U_VEDU_CABAC_GLB_CFG VEDU_CABAC_GLB_CFG;
    volatile U_VEDU_CABAC_SLCHDR_SIZE VEDU_CABAC_SLCHDR_SIZE;
    volatile U_VEDU_CABAC_SLCHDR_PART1 VEDU_CABAC_SLCHDR_PART1;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG1;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG2;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG3;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG4;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG5;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG6;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG7;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG8;
    volatile U_VEDU_CABAC_SLCHDR_SIZE_I VEDU_CABAC_SLCHDR_SIZE_I;
    volatile U_VEDU_CABAC_SLCHDR_PART1_I VEDU_CABAC_SLCHDR_PART1_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG1_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG2_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG3_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG4_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG5_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG6_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG7_I;
    volatile unsigned int VEDU_CABAC_SLCHDR_PART2_SEG8_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM0;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM1;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM2;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM3;
    volatile unsigned int VEDU_VLC_REORDERSTRM0;
    volatile unsigned int VEDU_VLC_REORDERSTRM1;
    volatile unsigned int VEDU_VLC_MARKINGSTRM0;
    volatile unsigned int VEDU_VLC_MARKINGSTRM1;
    volatile U_VEDU_VLC_SLCHDRPARA VEDU_VLC_SLCHDRPARA;
    volatile U_VEDU_VLC_SVC VEDU_VLC_SVC;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM0_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM1_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM2_I;
    volatile unsigned int VEDU_VLC_SLCHDRSTRM3_I;
    volatile unsigned int VEDU_VLC_REORDERSTRM0_I;
    volatile unsigned int VEDU_VLC_REORDERSTRM1_I;
    volatile unsigned int VEDU_VLC_MARKINGSTRM0_I;
    volatile unsigned int VEDU_VLC_MARKINGSTRM1_I;
    volatile U_VEDU_VLC_SLCHDRPARA_I VEDU_VLC_SLCHDRPARA_I;
    volatile U_VEDU_VLCST_PTBITS_EN VEDU_VLCST_PTBITS_EN;
    volatile unsigned int VEDU_VLCST_PTBITS;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN0;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN1;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN2;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN3;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN4;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN5;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN6;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN7;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN8;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN9;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN10;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN11;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN12;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN13;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN14;
    volatile unsigned int VEDU_VLCST_STRMBUFLEN15;
    volatile unsigned int VEDU_VLCST_STRMADDR0;
    volatile unsigned int VEDU_VLCST_STRMADDR1;
    volatile unsigned int VEDU_VLCST_STRMADDR2;
    volatile unsigned int VEDU_VLCST_STRMADDR3;
    volatile unsigned int VEDU_VLCST_STRMADDR4;
    volatile unsigned int VEDU_VLCST_STRMADDR5;
    volatile unsigned int VEDU_VLCST_STRMADDR6;
    volatile unsigned int VEDU_VLCST_STRMADDR7;
    volatile unsigned int VEDU_VLCST_STRMADDR8;
    volatile unsigned int VEDU_VLCST_STRMADDR9;
    volatile unsigned int VEDU_VLCST_STRMADDR10;
    volatile unsigned int VEDU_VLCST_STRMADDR11;
    volatile unsigned int VEDU_VLCST_STRMADDR12;
    volatile unsigned int VEDU_VLCST_STRMADDR13;
    volatile unsigned int VEDU_VLCST_STRMADDR14;
    volatile unsigned int VEDU_VLCST_STRMADDR15;
    volatile unsigned int VEDU_VLCST_PARA_ADDR;
    volatile U_VEDU_VLCST_PARAMETER VEDU_VLCST_PARAMETER;
    volatile unsigned int VEDU_VLCST_PARA_DATA0;
    volatile unsigned int VEDU_VLCST_PARA_DATA1;
    volatile unsigned int VEDU_VLCST_PARA_DATA2;
    volatile unsigned int VEDU_VLCST_PARA_DATA3;
    volatile unsigned int VEDU_VLCST_PARA_DATA4;
    volatile unsigned int VEDU_VLCST_PARA_DATA5;
    volatile unsigned int VEDU_VLCST_PARA_DATA6;
    volatile unsigned int VEDU_VLCST_PARA_DATA7;
    volatile unsigned int VEDU_VLCST_PARA_DATA8;
    volatile unsigned int VEDU_VLCST_PARA_DATA9;
    volatile unsigned int VEDU_VLCST_PARA_DATA10;
    volatile unsigned int VEDU_VLCST_PARA_DATA11;
    volatile unsigned int VEDU_VLCST_PARA_DATA12;
    volatile unsigned int VEDU_VLCST_PARA_DATA13;
    volatile unsigned int VEDU_VLCST_PARA_DATA14;
    volatile unsigned int VEDU_VLCST_PARA_DATA15;
    volatile unsigned int VEDU_VLCST_PARA_DATA16;
    volatile unsigned int VEDU_VLCST_PARA_DATA17;
    volatile unsigned int VEDU_VLCST_PARA_DATA18;
    volatile unsigned int VEDU_VLCST_PARA_DATA19;
    volatile unsigned int VEDU_VLCST_PARA_DATA20;
    volatile unsigned int VEDU_VLCST_PARA_DATA21;
    volatile unsigned int VEDU_VLCST_PARA_DATA22;
    volatile unsigned int VEDU_VLCST_PARA_DATA23;
    volatile unsigned int VEDU_VLCST_PARA_DATA24;
    volatile unsigned int VEDU_VLCST_PARA_DATA25;
    volatile unsigned int VEDU_VLCST_PARA_DATA26;
    volatile unsigned int VEDU_VLCST_PARA_DATA27;
    volatile unsigned int VEDU_VLCST_PARA_DATA28;
    volatile unsigned int VEDU_VLCST_PARA_DATA29;
    volatile unsigned int VEDU_VLCST_PARA_DATA30;
    volatile unsigned int VEDU_VLCST_PARA_DATA31;
    volatile unsigned int VEDU_VLCST_PARA_DATA32;
    volatile unsigned int VEDU_VLCST_PARA_DATA33;
    volatile unsigned int VEDU_VLCST_PARA_DATA34;
    volatile unsigned int VEDU_VLCST_PARA_DATA35;
    volatile unsigned int VEDU_VLCST_PARA_DATA36;
    volatile unsigned int VEDU_VLCST_PARA_DATA37;
    volatile unsigned int VEDU_VLCST_PARA_DATA38;
    volatile unsigned int VEDU_VLCST_PARA_DATA39;
    volatile unsigned int VEDU_VLCST_PARA_DATA40;
    volatile unsigned int VEDU_VLCST_PARA_DATA41;
    volatile unsigned int VEDU_VLCST_PARA_DATA42;
    volatile unsigned int VEDU_VLCST_PARA_DATA43;
    volatile unsigned int VEDU_VLCST_PARA_DATA44;
    volatile unsigned int VEDU_VLCST_PARA_DATA45;
    volatile unsigned int VEDU_VLCST_PARA_DATA46;
    volatile unsigned int VEDU_VLCST_PARA_DATA47;
    volatile U_VEDU_ENV_CHN VEDU_ENV_CHN;
    volatile U_FUNC_VCPI_INTSTAT FUNC_VCPI_INTSTAT;
    volatile U_FUNC_VCPI_RAWINT FUNC_VCPI_RAWINT;
    volatile unsigned int FUNC_VCPI_VEDU_TIMER;
    volatile unsigned int FUNC_VCPI_IDLE_TIMER;
    volatile U_FUNC_VCPI_INTSTAT_S FUNC_VCPI_INTSTAT_S;
    volatile U_FUNC_VCPI_RAWINT_S FUNC_VCPI_RAWINT_S;
    volatile U_FUNC_PME_MADI_SUM FUNC_PME_MADI_SUM;
    volatile U_FUNC_PME_MADP_SUM FUNC_PME_MADP_SUM;
    volatile U_FUNC_PME_MADI_NUM FUNC_PME_MADI_NUM;
    volatile U_FUNC_PME_MADP_NUM FUNC_PME_MADP_NUM;
    volatile unsigned int FUNC_PMV[16];
    volatile unsigned int FUNC_CABAC_PIC_STRMSIZE;
    volatile unsigned int FUNC_CABAC_BIT_NUM;
    volatile unsigned int FUNC_CABAC_PIC_HDRBIN_NUM;
    volatile unsigned int FUNC_CABAC_PIC_RESBIN_NUM;
    volatile unsigned int FUNC_VLC_PIC_BITS;
    volatile unsigned int FUNC_VLCST_SLC_LEN_CNT;
    volatile U_FUNC_VLCST_DSRPTR00 FUNC_VLCST_DSRPTR00;
    volatile U_FUNC_VLCST_DSRPTR01 FUNC_VLCST_DSRPTR01;
    volatile U_FUNC_VLCST_DSRPTR10 FUNC_VLCST_DSRPTR10;
    volatile U_FUNC_VLCST_DSRPTR11 FUNC_VLCST_DSRPTR11;
    volatile U_FUNC_VLCST_DSRPTR20 FUNC_VLCST_DSRPTR20;
    volatile U_FUNC_VLCST_DSRPTR21 FUNC_VLCST_DSRPTR21;
    volatile U_FUNC_VLCST_DSRPTR30 FUNC_VLCST_DSRPTR30;
    volatile U_FUNC_VLCST_DSRPTR31 FUNC_VLCST_DSRPTR31;
    volatile U_FUNC_VLCST_DSRPTR40 FUNC_VLCST_DSRPTR40;
    volatile U_FUNC_VLCST_DSRPTR41 FUNC_VLCST_DSRPTR41;
    volatile U_FUNC_VLCST_DSRPTR50 FUNC_VLCST_DSRPTR50;
    volatile U_FUNC_VLCST_DSRPTR51 FUNC_VLCST_DSRPTR51;
    volatile U_FUNC_VLCST_DSRPTR60 FUNC_VLCST_DSRPTR60;
    volatile U_FUNC_VLCST_DSRPTR61 FUNC_VLCST_DSRPTR61;
    volatile U_FUNC_VLCST_DSRPTR70 FUNC_VLCST_DSRPTR70;
    volatile U_FUNC_VLCST_DSRPTR71 FUNC_VLCST_DSRPTR71;
    volatile U_FUNC_VLCST_DSRPTR80 FUNC_VLCST_DSRPTR80;
    volatile U_FUNC_VLCST_DSRPTR81 FUNC_VLCST_DSRPTR81;
    volatile U_FUNC_VLCST_DSRPTR90 FUNC_VLCST_DSRPTR90;
    volatile U_FUNC_VLCST_DSRPTR91 FUNC_VLCST_DSRPTR91;
    volatile U_FUNC_VLCST_DSRPTR100 FUNC_VLCST_DSRPTR100;
    volatile U_FUNC_VLCST_DSRPTR101 FUNC_VLCST_DSRPTR101;
    volatile U_FUNC_VLCST_DSRPTR110 FUNC_VLCST_DSRPTR110;
    volatile U_FUNC_VLCST_DSRPTR111 FUNC_VLCST_DSRPTR111;
    volatile U_FUNC_VLCST_DSRPTR120 FUNC_VLCST_DSRPTR120;
    volatile U_FUNC_VLCST_DSRPTR121 FUNC_VLCST_DSRPTR121;
    volatile U_FUNC_VLCST_DSRPTR130 FUNC_VLCST_DSRPTR130;
    volatile U_FUNC_VLCST_DSRPTR131 FUNC_VLCST_DSRPTR131;
    volatile U_FUNC_VLCST_DSRPTR140 FUNC_VLCST_DSRPTR140;
    volatile U_FUNC_VLCST_DSRPTR141 FUNC_VLCST_DSRPTR141;
    volatile U_FUNC_VLCST_DSRPTR150 FUNC_VLCST_DSRPTR150;
    volatile U_FUNC_VLCST_DSRPTR151 FUNC_VLCST_DSRPTR151;
    volatile U_FUNC_SEL_OPT_8X8_CNT FUNC_SEL_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTRA_OPT_8X8_CNT FUNC_SEL_INTRA_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTRA_NORMAL_OPT_8X8_CNT FUNC_SEL_INTRA_NORMAL_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTRA_PCM_OPT_8X8_CNT FUNC_SEL_INTRA_PCM_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_OPT_8X8_CNT FUNC_SEL_INTER_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_8X8_CNT FUNC_SEL_INTER_FME_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_8X8_CNT FUNC_SEL_INTER_MERGE_OPT_8X8_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_8X8_CNT FUNC_SEL_INTER_SKIP_OPT_8X8_CNT;
    volatile U_FUNC_SEL_OPT_16X16_CNT FUNC_SEL_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTRA_OPT_16X16_CNT FUNC_SEL_INTRA_OPT_16X16_CNT;
    volatile U_FUNC_SEL_OPT_4X4_CNT FUNC_SEL_OPT_4X4_CNT;
    volatile U_FUNC_SEL_INTER_OPT_16X16_CNT FUNC_SEL_INTER_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_16X16_CNT FUNC_SEL_INTER_FME_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_16X16_CNT FUNC_SEL_INTER_MERGE_OPT_16X16_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_16X16_CNT FUNC_SEL_INTER_SKIP_OPT_16X16_CNT;
    volatile U_FUNC_SEL_OPT_32X32_CNT FUNC_SEL_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTRA_OPT_32X32_CNT FUNC_SEL_INTRA_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_OPT_32X32_CNT FUNC_SEL_INTER_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_32X32_CNT FUNC_SEL_INTER_FME_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_32X32_CNT FUNC_SEL_INTER_MERGE_OPT_32X32_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_32X32_CNT FUNC_SEL_INTER_SKIP_OPT_32X32_CNT;
    volatile U_FUNC_SEL_OPT_64X64_CNT FUNC_SEL_OPT_64X64_CNT;
    volatile U_FUNC_SEL_INTER_FME_OPT_64X64_CNT FUNC_SEL_INTER_FME_OPT_64X64_CNT;
    volatile U_FUNC_SEL_INTER_MERGE_OPT_64X64_CNT FUNC_SEL_INTER_MERGE_OPT_64X64_CNT;
    volatile U_FUNC_SEL_INTER_SKIP_OPT_64X64_CNT FUNC_SEL_INTER_SKIP_OPT_64X64_CNT;
    volatile U_FUNC_SEL_TOTAL_LUMA_QP FUNC_SEL_TOTAL_LUMA_QP;
    volatile U_FUNC_SEL_MAX_MIN_LUMA_QP FUNC_SEL_MAX_MIN_LUMA_QP;
    volatile U_FUNC_SEL_LUMA_QP0_CNT FUNC_SEL_LUMA_QP0_CNT;
    volatile U_FUNC_SEL_LUMA_QP1_CNT FUNC_SEL_LUMA_QP1_CNT;
    volatile U_FUNC_SEL_LUMA_QP2_CNT FUNC_SEL_LUMA_QP2_CNT;
    volatile U_FUNC_SEL_LUMA_QP3_CNT FUNC_SEL_LUMA_QP3_CNT;
    volatile U_FUNC_SEL_LUMA_QP4_CNT FUNC_SEL_LUMA_QP4_CNT;
    volatile U_FUNC_SEL_LUMA_QP5_CNT FUNC_SEL_LUMA_QP5_CNT;
    volatile U_FUNC_SEL_LUMA_QP6_CNT FUNC_SEL_LUMA_QP6_CNT;
    volatile U_FUNC_SEL_LUMA_QP7_CNT FUNC_SEL_LUMA_QP7_CNT;
    volatile U_FUNC_SEL_LUMA_QP8_CNT FUNC_SEL_LUMA_QP8_CNT;
    volatile U_FUNC_SEL_LUMA_QP9_CNT FUNC_SEL_LUMA_QP9_CNT;
    volatile U_FUNC_SEL_LUMA_QP10_CNT FUNC_SEL_LUMA_QP10_CNT;
    volatile U_FUNC_SEL_LUMA_QP11_CNT FUNC_SEL_LUMA_QP11_CNT;
    volatile U_FUNC_SEL_LUMA_QP12_CNT FUNC_SEL_LUMA_QP12_CNT;
    volatile U_FUNC_SEL_LUMA_QP13_CNT FUNC_SEL_LUMA_QP13_CNT;
    volatile U_FUNC_SEL_LUMA_QP14_CNT FUNC_SEL_LUMA_QP14_CNT;
    volatile U_FUNC_SEL_LUMA_QP15_CNT FUNC_SEL_LUMA_QP15_CNT;
    volatile U_FUNC_SEL_LUMA_QP16_CNT FUNC_SEL_LUMA_QP16_CNT;
    volatile U_FUNC_SEL_LUMA_QP17_CNT FUNC_SEL_LUMA_QP17_CNT;
    volatile U_FUNC_SEL_LUMA_QP18_CNT FUNC_SEL_LUMA_QP18_CNT;
    volatile U_FUNC_SEL_LUMA_QP19_CNT FUNC_SEL_LUMA_QP19_CNT;
    volatile U_FUNC_SEL_LUMA_QP20_CNT FUNC_SEL_LUMA_QP20_CNT;
    volatile U_FUNC_SEL_LUMA_QP21_CNT FUNC_SEL_LUMA_QP21_CNT;
    volatile U_FUNC_SEL_LUMA_QP22_CNT FUNC_SEL_LUMA_QP22_CNT;
    volatile U_FUNC_SEL_LUMA_QP23_CNT FUNC_SEL_LUMA_QP23_CNT;
    volatile U_FUNC_SEL_LUMA_QP24_CNT FUNC_SEL_LUMA_QP24_CNT;
    volatile U_FUNC_SEL_LUMA_QP25_CNT FUNC_SEL_LUMA_QP25_CNT;
    volatile U_FUNC_SEL_LUMA_QP26_CNT FUNC_SEL_LUMA_QP26_CNT;
    volatile U_FUNC_SEL_LUMA_QP27_CNT FUNC_SEL_LUMA_QP27_CNT;
    volatile U_FUNC_SEL_LUMA_QP28_CNT FUNC_SEL_LUMA_QP28_CNT;
    volatile U_FUNC_SEL_LUMA_QP29_CNT FUNC_SEL_LUMA_QP29_CNT;
    volatile U_FUNC_SEL_LUMA_QP30_CNT FUNC_SEL_LUMA_QP30_CNT;
    volatile U_FUNC_SEL_LUMA_QP31_CNT FUNC_SEL_LUMA_QP31_CNT;
    volatile U_FUNC_SEL_LUMA_QP32_CNT FUNC_SEL_LUMA_QP32_CNT;
    volatile U_FUNC_SEL_LUMA_QP33_CNT FUNC_SEL_LUMA_QP33_CNT;
    volatile U_FUNC_SEL_LUMA_QP34_CNT FUNC_SEL_LUMA_QP34_CNT;
    volatile U_FUNC_SEL_LUMA_QP35_CNT FUNC_SEL_LUMA_QP35_CNT;
    volatile U_FUNC_SEL_LUMA_QP36_CNT FUNC_SEL_LUMA_QP36_CNT;
    volatile U_FUNC_SEL_LUMA_QP37_CNT FUNC_SEL_LUMA_QP37_CNT;
    volatile U_FUNC_SEL_LUMA_QP38_CNT FUNC_SEL_LUMA_QP38_CNT;
    volatile U_FUNC_SEL_LUMA_QP39_CNT FUNC_SEL_LUMA_QP39_CNT;
    volatile U_FUNC_SEL_LUMA_QP40_CNT FUNC_SEL_LUMA_QP40_CNT;
    volatile U_FUNC_SEL_LUMA_QP41_CNT FUNC_SEL_LUMA_QP41_CNT;
    volatile U_FUNC_SEL_LUMA_QP42_CNT FUNC_SEL_LUMA_QP42_CNT;
    volatile U_FUNC_SEL_LUMA_QP43_CNT FUNC_SEL_LUMA_QP43_CNT;
    volatile U_FUNC_SEL_LUMA_QP44_CNT FUNC_SEL_LUMA_QP44_CNT;
    volatile U_FUNC_SEL_LUMA_QP45_CNT FUNC_SEL_LUMA_QP45_CNT;
    volatile U_FUNC_SEL_LUMA_QP46_CNT FUNC_SEL_LUMA_QP46_CNT;
    volatile U_FUNC_SEL_LUMA_QP47_CNT FUNC_SEL_LUMA_QP47_CNT;
    volatile U_FUNC_SEL_LUMA_QP48_CNT FUNC_SEL_LUMA_QP48_CNT;
    volatile U_FUNC_SEL_LUMA_QP49_CNT FUNC_SEL_LUMA_QP49_CNT;
    volatile U_FUNC_SEL_LUMA_QP50_CNT FUNC_SEL_LUMA_QP50_CNT;
    volatile U_FUNC_SEL_LUMA_QP51_CNT FUNC_SEL_LUMA_QP51_CNT;
    volatile U_FUNC_SAO_OFF_NUM FUNC_SAO_OFF_NUM;
    volatile U_FUNC_SAO_LCU_CNT FUNC_SAO_LCU_CNT;
    volatile U_PMV_CNT_FRAME PMV_CNT_FRAME ;
    volatile U_PMV_TMV_0 PMV_TMV_0 ;
    volatile U_PMV_TMV_1 PMV_TMV_1 ;
    volatile U_PMV_TMV_2 PMV_TMV_2 ;
    volatile U_PMV_TMV_3 PMV_TMV_3 ;
    volatile U_PMV_TMV_4 PMV_TMV_4 ;
    volatile U_PMV_TMV_5 PMV_TMV_5 ;
    volatile unsigned int PMV_RESERVED0 ;
    volatile unsigned int FUNC_PMV_MV0_COUNT ;
    volatile unsigned int FUNC_PMV_MV1_COUNT ;
    volatile unsigned int FUNC_PMV_MV2_COUNT ;
    volatile unsigned int FUNC_PMV_MV3_COUNT ;
    volatile unsigned int FUNC_PMV_MV4_COUNT ;
    volatile unsigned int FUNC_PMV_MV5_COUNT ;
    volatile unsigned int FUNC_PMV_MV6_COUNT ;
    volatile unsigned int FUNC_PMV_MV7_COUNT ;
    volatile unsigned int FUNC_PMV_MV8_COUNT ;
    volatile unsigned int FUNC_PMV_MV9_COUNT ;
    volatile unsigned int FUNC_PMV_MV10_COUNT ;
    volatile unsigned int FUNC_PMV_MV11_COUNT ;
    volatile unsigned int FUNC_PMV_MV12_COUNT ;
    volatile unsigned int FUNC_PMV_MV13_COUNT ;
    volatile unsigned int FUNC_PMV_MV14_COUNT ;
    volatile unsigned int FUNC_PMV_MV15_COUNT ;
    volatile unsigned int FUNC_PMV_MV16_COUNT ;
    volatile unsigned int FUNC_PMV_MV17_COUNT ;
    volatile unsigned int FUNC_PMV_MV18_COUNT ;
    volatile unsigned int FUNC_PMV_MV19_COUNT ;
    volatile unsigned int FUNC_PMV_MV20_COUNT ;
    volatile unsigned int FUNC_PMV_MV21_COUNT ;
    volatile unsigned int FUNC_PMV_MV22_COUNT ;
    volatile U_MMU_PRE_GLB_SCR MMU_PRE_GLB_SCR;
    volatile unsigned int MMU_PRE_NBI_MVST_ADDR_STR;
    volatile unsigned int MMU_PRE_NBI_MVST_ADDR_END;
    volatile unsigned int MMU_PRE_NBI_MVLD_ADDR_STR;
    volatile unsigned int MMU_PRE_NBI_MVLD_ADDR_END;
    volatile unsigned int MMU_PRE_PMEST_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEST_ADDR_END;
    volatile unsigned int MMU_PRE_PMELD_ADDR_STR;
    volatile unsigned int MMU_PRE_PMELD_ADDR_END;
    volatile unsigned int MMU_PRE_PMEINFOST_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEINFOST_ADDR_END;
    volatile unsigned int MMU_PRE_PMEINFOLD0_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEINFOLD0_ADDR_END;
    volatile unsigned int MMU_PRE_PMEINFOLD1_ADDR_STR;
    volatile unsigned int MMU_PRE_PMEINFOLD1_ADDR_END;
    volatile unsigned int MMU_PRE_QPGLD_ADDR_STR;
    volatile unsigned int MMU_PRE_QPGLD_ADDR_END;
    volatile unsigned int MMU_PRE_REC_YH_ADDR_STR;
    volatile unsigned int MMU_PRE_REC_YH_ADDR_END;
    volatile unsigned int MMU_PRE_REC_CH_ADDR_STR;
    volatile unsigned int MMU_PRE_REC_CH_ADDR_END;
    volatile unsigned int MMU_PRE_REC_YADDR_STR;
    volatile unsigned int MMU_PRE_REC_YADDR_END;
    volatile unsigned int MMU_PRE_REC_CADDR_STR;
    volatile unsigned int MMU_PRE_REC_CADDR_END;
    volatile unsigned int MMU_PRE_REF_YH_ADDR_STR;
    volatile unsigned int MMU_PRE_REF_YH_ADDR_END;
    volatile unsigned int MMU_PRE_REF_CH_ADDR_STR;
    volatile unsigned int MMU_PRE_REF_CH_ADDR_END;
    volatile unsigned int MMU_PRE_REF_YADDR_STR;
    volatile unsigned int MMU_PRE_REF_YADDR_END;
    volatile unsigned int MMU_PRE_REF_CADDR_STR;
    volatile unsigned int MMU_PRE_REF_CADDR_END;
    volatile unsigned int MMU_PRE_SRC_YHADDR_STR;
    volatile unsigned int MMU_PRE_SRC_YHADDR_END;
    volatile unsigned int MMU_PRE_SRC_CHADDR_STR;
    volatile unsigned int MMU_PRE_SRC_CHADDR_END;
    volatile unsigned int MMU_PRE_SRC_YADDR_STR;
    volatile unsigned int MMU_PRE_SRC_YADDR_END;
    volatile unsigned int MMU_PRE_SRC_CADDR_STR;
    volatile unsigned int MMU_PRE_SRC_CADDR_END;
    volatile unsigned int MMU_PRE_SRC_VADDR_STR;
    volatile unsigned int MMU_PRE_SRC_VADDR_END;
    volatile unsigned int MMU_PRE_LOWDLY_ADDR_STR;
    volatile unsigned int MMU_PRE_LOWDLY_ADDR_END;
    volatile unsigned int MMU_PRE_PPS_ADDR_STR;
    volatile unsigned int MMU_PRE_PPS_ADDR_END;
    volatile unsigned int MMU_PRE_STRMADDR0_STR;
    volatile unsigned int MMU_PRE_STRMADDR0_END;
    volatile unsigned int MMU_PRE_STRMADDR1_STR;
    volatile unsigned int MMU_PRE_STRMADDR1_END;
    volatile unsigned int MMU_PRE_STRMADDR2_STR;
    volatile unsigned int MMU_PRE_STRMADDR2_END;
    volatile unsigned int MMU_PRE_STRMADDR3_STR;
    volatile unsigned int MMU_PRE_STRMADDR3_END;
    volatile unsigned int MMU_PRE_STRMADDR4_STR;
    volatile unsigned int MMU_PRE_STRMADDR4_END;
    volatile unsigned int MMU_PRE_STRMADDR5_STR;
    volatile unsigned int MMU_PRE_STRMADDR5_END;
    volatile unsigned int MMU_PRE_STRMADDR6_STR;
    volatile unsigned int MMU_PRE_STRMADDR6_END;
    volatile unsigned int MMU_PRE_STRMADDR7_STR;
    volatile unsigned int MMU_PRE_STRMADDR7_END;
    volatile unsigned int MMU_PRE_STRMADDR8_STR;
    volatile unsigned int MMU_PRE_STRMADDR8_END;
    volatile unsigned int MMU_PRE_STRMADDR9_STR;
    volatile unsigned int MMU_PRE_STRMADDR9_END;
    volatile unsigned int MMU_PRE_STRMADDR10_STR;
    volatile unsigned int MMU_PRE_STRMADDR10_END;
    volatile unsigned int MMU_PRE_STRMADDR11_STR;
    volatile unsigned int MMU_PRE_STRMADDR11_END;
    volatile unsigned int MMU_PRE_STRMADDR12_STR;
    volatile unsigned int MMU_PRE_STRMADDR12_END;
    volatile unsigned int MMU_PRE_STRMADDR13_STR;
    volatile unsigned int MMU_PRE_STRMADDR13_END;
    volatile unsigned int MMU_PRE_STRMADDR14_STR;
    volatile unsigned int MMU_PRE_STRMADDR14_END;
    volatile unsigned int MMU_PRE_STRMADDR15_STR;
    volatile unsigned int MMU_PRE_STRMADDR15_END;
    volatile U_MMU_PRE_DFX_ARERR_FLAG MMU_PRE_DFX_ARERR_FLAG;
    volatile U_MMU_PRE_DFX_ARERR_ID MMU_PRE_DFX_ARERR_ID;
    volatile unsigned int MMU_PRE_DFX_ARERR_ADDR;
    volatile U_MMU_PRE_DFX_AWERR_FLAG MMU_PRE_DFX_AWERR_FLAG;
    volatile U_MMU_PRE_DFX_AWERR_ID MMU_PRE_DFX_AWERR_ID;
    volatile unsigned int MMU_PRE_DFX_AWERR_ADDR;
    volatile U_AXIDFX_ERR AXIDFX_ERR;
    volatile U_AXIDFX_AR_R_CNT AXIDFX_AR_R_CNT;
    volatile U_AXIDFX_AW_W_CNT AXIDFX_AW_W_CNT;
    volatile U_AXIDFX_AW_B_CNT AXIDFX_AW_B_CNT;
    volatile U_AXIDFX_AR_R_ID_ERR AXIDFX_AR_R_ID_ERR;
    volatile U_AXIDFX_ERR_ARID AXIDFX_ERR_ARID;
    volatile U_AXIDFX_ERR_RID AXIDFX_ERR_RID;
    volatile U_AXIDFX_AW_W_B_ID_ERR AXIDFX_AW_W_B_ID_ERR;
    volatile U_AXIDFX_ERR_AWID AXIDFX_ERR_AWID;
    volatile U_AXIDFX_ERR_WID AXIDFX_ERR_WID;
    volatile U_AXIDFX_ERR_BID AXIDFX_ERR_BID;
    volatile U_AXIDFX_ARID_TX_0ERR AXIDFX_ARID_TX_0ERR;
    volatile U_AXIDFX_ARID_TX_1ERR AXIDFX_ARID_TX_1ERR;
    volatile U_AXIDFX_ARID_TX_2ERR AXIDFX_ARID_TX_2ERR;
    volatile U_AXIDFX_RID_RX_0ERR AXIDFX_RID_RX_0ERR;
    volatile U_AXIDFX_RID_RX_1ERR AXIDFX_RID_RX_1ERR;
    volatile U_AXIDFX_RID_RX_2ERR AXIDFX_RID_RX_2ERR;
    volatile U_AXIDFX_ARID_RX_0ERR AXIDFX_ARID_RX_0ERR;
    volatile U_AXIDFX_BID_RX_ERR AXIDFX_BID_RX_ERR;
    volatile U_AXIDFX_ARID_LEN_0ERR AXIDFX_ARID_LEN_0ERR;
    volatile U_AXIDFX_ARID_LEN_1ERR AXIDFX_ARID_LEN_1ERR;
    volatile U_AXIDFX_ARID_LEN_2ERR AXIDFX_ARID_LEN_2ERR;
    volatile unsigned int AXIDFX_AWLEN_CNT;
    volatile unsigned int AXIDFX_WLEN_CNT;
    volatile U_AXIDFX_RESP_ERR AXIDFX_RESP_ERR;
    volatile U_AXIDFX_ERR_RESP AXIDFX_ERR_RESP;
    volatile U_AXIDFX_LEN_ERR AXIDFX_LEN_ERR;
    volatile U_AXIDFX_ERR_LEN AXIDFX_ERR_LEN;
    volatile unsigned int AXIDFX_0RID_FLAG;
    volatile unsigned int AXIDFX_1RID_FLAG;
    volatile U_AXIDFX_2RID_FLAG AXIDFX_2RID_FLAG;
    volatile U_AXIDFX_WID_FLAG AXIDFX_WID_FLAG;
    volatile U_AXIDFX_AXI_ST AXIDFX_AXI_ST;
    volatile U_AXIDFX_SOFT_RST_REQ AXIDFX_SOFT_RST_REQ;
    volatile U_AXIDFX_SOFT_RST_ACK AXIDFX_SOFT_RST_ACK;
    volatile U_AXIDFX_SOFT_RST_FORCE_REQ_ACK AXIDFX_SOFT_RST_FORCE_REQ_ACK;
    volatile unsigned int AXIDFX_SOFT_RST_STATE0;
    volatile unsigned int AXIDFX_SOFT_RST_STATE1;
    volatile U_SMMU_MSTR_GLB_BYPASS SMMU_MSTR_GLB_BYPASS;
    volatile U_SMMU_MSTR_DEBUG_MODE SMMU_MSTR_DEBUG_MODE;
    volatile U_SMMU_MSTR_MEM_CTRL SMMU_MSTR_MEM_CTRL;
    volatile U_SMMU_MSTR_CLK_EN SMMU_MSTR_CLK_EN;
    volatile unsigned int SMMU_MSTR_END_REQ_0;
    volatile unsigned int SMMU_MSTR_END_REQ_1;
    volatile U_SMMU_MSTR_END_REQ_2 SMMU_MSTR_END_REQ_2;
    volatile unsigned int SMMU_MSTR_END_ACK_0;
    volatile unsigned int SMMU_MSTR_END_ACK_1;
    volatile U_SMMU_MSTR_END_ACK_2 SMMU_MSTR_END_ACK_2;
    volatile unsigned int SMMU_MSTR_SMRX_START_0;
    volatile unsigned int SMMU_MSTR_SMRX_START_1;
    volatile U_SMMU_MSTR_SMRX_START_2 SMMU_MSTR_SMRX_START_2;
    volatile U_SMMU_MSTR_INPT_SEL SMMU_MSTR_INPT_SEL;
    volatile U_SMMU_MSTR_INTMASK SMMU_MSTR_INTMASK;
    volatile U_SMMU_MSTR_INTRAW SMMU_MSTR_INTRAW;
    volatile U_SMMU_MSTR_INTSTAT SMMU_MSTR_INTSTAT;
    volatile U_SMMU_MSTR_INTCLR SMMU_MSTR_INTCLR;
    volatile U_SMMU_MSTR_DBG_0 SMMU_MSTR_DBG_0;
    volatile unsigned int SMMU_MSTR_DBG_1;
    volatile U_SMMU_MSTR_DBG_2 SMMU_MSTR_DBG_2;
    volatile unsigned int SMMU_MSTR_DBG_3;
    volatile U_SMMU_MSTR_DBG_4 SMMU_MSTR_DBG_4;
    volatile unsigned int SMMU_MSTR_DBG_5;
    volatile U_SMMU_MSTR_DBG_PORT_IN_0 SMMU_MSTR_DBG_PORT_IN_0;
    volatile unsigned int SMMU_MSTR_DBG_PORT_IN_1;
    volatile unsigned int SMMU_MSTR_DBG_PORT_OUT;
    volatile U_SMMU_MSTR_SMRX_0 SMMU_MSTR_SMRX_0[88];
    volatile U_SMMU_MSTR_SMRX_1 SMMU_MSTR_SMRX_1[88];
    volatile U_SMMU_MSTR_SMRX_2 SMMU_MSTR_SMRX_2[144];
    volatile U_SMMU_SCR SMMU_SCR;
    volatile U_SMMU_MEMCTRL SMMU_MEMCTRL;
    volatile U_SMMU_LP_CTRL SMMU_LP_CTRL;
    volatile unsigned int SMMU_COMN_RESERVED_1;
    volatile U_SMMU_INTMASK_NS SMMU_INTMASK_NS;
    volatile U_SMMU_INTRAW_NS SMMU_INTRAW_NS;
    volatile U_SMMU_INTSTAT_NS SMMU_INTSTAT_NS;
    volatile U_SMMU_INTCLR_NS SMMU_INTCLR_NS;
    volatile unsigned int SMMU_RLD_EN0_NS;
    volatile unsigned int SMMU_RLD_EN1_NS;
    volatile U_SMMU_RLD_EN2_NS SMMU_RLD_EN2_NS;
    volatile U_SMMU_GLB_ALLOC_ST SMMU_GLB_ALLOC_ST;
    volatile U_SMMU_CB_SCTRL SMMU_CB_SCTRL;
    volatile unsigned int SMMU_CB_TTBR0;
    volatile unsigned int SMMU_CB_TTBR1;
    volatile U_SMMU_CB_TTBCR SMMU_CB_TTBCR;
    volatile unsigned int SMMU_COMN_RESERVED_2;
    volatile U_SMMU_SCACHEI_ALL SMMU_SCACHEI_ALL;
    volatile U_SMMU_SCACHEI_L1 SMMU_SCACHEI_L1;
    volatile U_SMMU_SCACHEI_L2 SMMU_SCACHEI_L2;
    volatile U_SMMU_CB_PA_MSB SMMU_CB_PA_MSB;
    volatile U_SMMU_CB_TTBR_MSB SMMU_CB_TTBR_MSB;
    volatile unsigned int SMMU_MAIR_NS;
    volatile U_SMMU_ERR_ADDR_MSB_NS SMMU_ERR_ADDR_MSB_NS;
    volatile unsigned int SMMU_ERR_RDADDR_NS;
    volatile unsigned int SMMU_ERR_WRADDR_NS;
    volatile unsigned int SMMU_COMN_RESERVED_4;
    volatile unsigned int SMMU_FAULT_ADDR_TCU;
    volatile U_SMMU_FAULT_ID_TCU SMMU_FAULT_ID_TCU;
    volatile unsigned int SMMU_COMN_RESERVED_5[2];
    volatile unsigned int SMMU_FAULT_ADDR_TBUX;
    volatile U_SMMU_FAULT_ID_TBUX SMMU_FAULT_ID_TBUX;
    volatile unsigned int SMMU_RLD_EN0_S;
    volatile unsigned int SMMU_RLD_EN1_S;
    volatile U_SMMU_RLD_EN2_S SMMU_RLD_EN2_S;
    volatile unsigned int SMMU_COMN_RESERVED_8;
    volatile U_SMMU_INTMAS_S SMMU_INTMAS_S;
    volatile U_SMMU_INTRAW_S SMMU_INTRAW_S;
    volatile U_SMMU_INTSTAT_S SMMU_INTSTAT_S;
    volatile U_SMMU_INTCLR_S SMMU_INTCLR_S;
    volatile U_SMMU_SCR_S SMMU_SCR_S;
    volatile U_SMMU_SCB_SCTRL SMMU_SCB_SCTRL;
    volatile unsigned int SMMU_SCB_TTBR;
    volatile U_SMMU_SCB_TTBCR SMMU_SCB_TTBCR;
    volatile unsigned int SMMU_COMN_RESERVED_9;
    volatile U_SMMU_SCB_PA_MSB SMMU_SCB_PA_MSB;
    volatile U_SMMU_SCB_TTBR_MSB SMMU_SCB_TTBR_MSB;
    volatile U_SMMU_ERR_ADDR_MSB_S SMMU_ERR_ADDR_MSB_S;
    volatile unsigned int SMMU_ERR_RDADDR_S;
    volatile unsigned int SMMU_ERR_WRADDR_S;
    volatile unsigned int SMMU_MAIR_S;
    volatile unsigned int SMMU_COMN_RESERVED_10;
    volatile unsigned int SMMU_RLD_EN0_P;
    volatile unsigned int SMMU_RLD_EN1_P;
    volatile U_SMMU_RLD_EN2_P SMMU_RLD_EN2_P;
    volatile unsigned int SMMU_COMN_RESERVED_13;
    volatile U_SMMU_INTMAS_P SMMU_INTMAS_P;
    volatile U_SMMU_INTRAW_P SMMU_INTRAW_P;
    volatile U_SMMU_INTSTAT_P SMMU_INTSTAT_P;
    volatile U_SMMU_INTCLR_P SMMU_INTCLR_P;
    volatile U_SMMU_SCR_P SMMU_SCR_P;
    volatile U_SMMU_PCB_SCTRL SMMU_PCB_SCTRL;
    volatile unsigned int SMMU_PCB_TTBR;
    volatile U_SMMU_PCB_TTBCR SMMU_PCB_TTBCR;
    volatile unsigned int SMMU_COMN_RESERVED_14;
    volatile U_SMMU_PCB_PA_MSB SMMU_PCB_PA_MSB;
    volatile U_SMMU_PCB_TTBR_MSB SMMU_PCB_TTBR_MSB;
    volatile unsigned int SMMU_MAIR_P;
    volatile U_SMMU_ERR_ADDR_MSB_P SMMU_ERR_ADDR_MSB_P;
    volatile unsigned int SMMU_ERR_RDADDR_P;
    volatile unsigned int SMMU_ERR_WRADDR_P;
} S_HEVC_AVC_REGS_TYPE_CFG;
#endif
