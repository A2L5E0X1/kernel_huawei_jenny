#ifndef __NPU_DDR_MAP_H__
#define __NPU_DDR_MAP_H__ 
#include <global_ddr_map.h>
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define NPU_NONSEC_RESERVED_DDR_BASE_ADDR (HISI_RESERVED_NPU_NORMAL_PHYMEM_BASE)
#define NPU_NONSEC_RESERVED_MEMORY_SIZE 0xC00000
#define NPU_SEC_RESERVED_DDR_BASE_ADDR (HISI_RESERVED_NPU_SEC_PHYMEM_BASE)
#define NPU_SEC_RESERVED_DDR_SIZE 0xA00000
enum tag_reserved_memory_idx {
    NPU_AICPU_FW_IDX = 0,
    NPU_TSCPU_FW_IDX = 1,
    NPU_SQCQ_MEM_IDX = 2,
    NPU_TASKPOOL_MEM_IDX = 3,
    NPU_LOG_MEM_IDX = 4,
    NPU_PROF_MEM_IDX = 5,
    NPU_BBOX_MEM_IDX = 6,
    NPU_DUMP_MEM_IDX = 7,
    NPU_CHIP_CFG_IDX = 8,
    NPU_MAX_RESMEM_IDX = 9,
};
enum tag_npu_nonsec_reserved_ddr {
    NPU_NS_AICPU_FW_SIZE = 0x300000,
    NPU_NS_TSCPU_FW_SIZE = 0x400000,
    NPU_NS_SQCQ_SIZE = 0x180000,
    NPU_NS_TASKPOOL_SIZE = 0x100000,
    NPU_NS_LOG_SIZE = 0x80000,
    NPU_NS_PROF_SIZE = 0x100000,
    NPU_NS_BBOX_SIZE = 0x40000,
    NPU_NS_DUMP_SIZE = 0xC0000,
    NPU_NS_CHIP_CFG_SIZE = 0x0,
};
enum tag_npu_unsec_fw_ddr {
    NPU_NS_AICPU_EL1_SIZE = 0xFE000,
    NPU_NS_AICPU_CONFIG_SIZE = 0x2000,
    NPU_NS_AICPU_RESERVED_SIZE = 0x200000,
    NPU_NS_TSCPU_EL1_SIZE = 0x3FF000,
    NPU_NS_TSCPU_CONFIG_SIZE = 0x1000,
    NPU_NS_TSCPU_RESERVED_SIZE = 0x500000,
};
#define NPU_NS_AICPU_FW_BASE_ADDR (NPU_NONSEC_RESERVED_DDR_BASE_ADDR)
#define NPU_NS_TSCPU_FW_BASE_ADDR (NPU_NS_AICPU_FW_BASE_ADDR + NPU_NS_AICPU_FW_SIZE)
#define NPU_NS_SQCQ_BUF_BASE_ADDR (NPU_NS_TSCPU_FW_BASE_ADDR + NPU_NS_TSCPU_FW_SIZE)
#define NPU_NS_TASKPOOL_BASE_ADDR (NPU_NS_SQCQ_BUF_BASE_ADDR + NPU_NS_SQCQ_SIZE)
#define NPU_NS_LOG_BASE_ADDR (NPU_NS_TASKPOOL_BASE_ADDR + NPU_NS_TASKPOOL_SIZE)
#define NPU_NS_PROFILE_BASE_ADDR (NPU_NS_LOG_BASE_ADDR + NPU_NS_LOG_SIZE)
#define NPU_NS_BBOX_BASE_ADDR (NPU_NS_PROFILE_BASE_ADDR + NPU_NS_PROF_SIZE)
#define NPU_NS_DATADUMP_BASE_ADDR (NPU_NS_BBOX_BASE_ADDR + NPU_NS_BBOX_SIZE)
#define NPU_NS_CHIP_CFG_BASE_ADDR (NPU_NS_DATADUMP_BASE_ADDR + NPU_NS_DUMP_SIZE)
enum tag_npu_sec_fw_ddr {
    NPU_S_AICPU_EL3_SIZE = 0x20000,
    NPU_S_AICPU_EL1_SIZE = 0xE0000,
    NPU_S_AICPU_RESERVED_SIZE = 0x200000,
    NPU_S_TSCPU_EL3_SIZE = 0x1000,
    NPU_S_TSCPU_EL1_SIZE = 0x2FF000,
    NPU_S_TSCPU_RESERVED_SIZE = 0x400000,
};
enum tag_npu_sec_reserved_ddr {
    NPU_S_CALC_SQ_AERA_SIZE = 0x40000,
    NPU_S_CALC_CQ_AERA_SIZE = 0x4000,
    NPU_S_TASKPOOL_SIZE = 0x100000,
    NPU_S_L2CTRL_CMA_SIZE = 0x200000,
    NPU_S_TS_LOG_SIZE = 0x80000,
    NPU_S_SMMU_QUEUE_SIZE = 0xe000,
    NPU_S_CHIP_CFG_SIZE = 0x0,
};
#define NPU_S_AICPU_FW_EL3_ADDR (NPU_SEC_RESERVED_DDR_BASE_ADDR)
#define NPU_S_AICPU_FW_EL1_ADDR (NPU_S_AICPU_FW_EL3_ADDR + NPU_S_AICPU_EL3_SIZE)
#define NPU_S_TSCPU_FW_EL3_ADDR (NPU_S_AICPU_FW_EL1_ADDR + NPU_S_AICPU_EL1_SIZE + NPU_S_AICPU_RESERVED_SIZE)
#define NPU_S_TSCPU_FW_EL1_ADDR (NPU_S_TSCPU_FW_EL3_ADDR + NPU_S_TSCPU_EL3_SIZE)
#define NPU_S_CALC_SQ_AERA_ADDR (NPU_S_TSCPU_FW_EL1_ADDR + NPU_S_TSCPU_EL1_SIZE)
#define NPU_S_CALC_CQ_AERA_ADDR (NPU_S_CALC_SQ_AERA_ADDR + NPU_S_CALC_SQ_AERA_SIZE)
#define NPU_S_TASKPOOL_ADDR (NPU_S_CALC_CQ_AERA_ADDR + NPU_S_CALC_CQ_AERA_SIZE)
#define NPU_S_L2CTRL_CMA_ADDR (NPU_S_TASKPOOL_ADDR + NPU_S_TASKPOOL_SIZE)
#define NPU_S_TS_LOG_ADDR (NPU_S_L2CTRL_CMA_ADDR + NPU_S_L2CTRL_CMA_SIZE)
#define NPU_S_SMMU_QUEUE_ADDR (NPU_S_TS_LOG_ADDR + NPU_S_TS_LOG_SIZE)
#define NPU_S_CHIP_CFG_ADDR (NPU_S_SMMU_QUEUE_ADDR + NPU_S_SMMU_QUEUE_SIZE)
#define NPU_S_AICPU_FW_BASE_ADDR (NPU_SEC_RESERVED_DDR_BASE_ADDR)
#define NPU_S_NPU_CONFIG_BASE_ADDR (NPU_SEC_RESERVED_DDR_BASE_ADDR)
#define NPU_S_HWTS_SQCQ_BASE_ADDR (NPU_S_NPU_CONFIG_BASE_ADDR + NPU_S_NPU_CONFIG_SIZE)
#define NPU_S_SMMU_QUEUE_BASE_ADDR (NPU_S_HWTS_SQCQ_BASE_ADDR + NPU_S_HWTS_SQCQ_SIZE)
#define NPU_S_NPU_CHIP_CFG_BASE_ADDR (NPU_S_SMMU_QUEUE_BASE_ADDR + NPU_S_SMMU_QUEUE_SIZE)
#ifdef NPU_LITE_SECURE
    #define NPU_TASK_POOL_RESMEM_ADDR NPU_S_TASKPOOL_ADDR
    #define NPU_LOG_RESMEM_ADDR NPU_S_TS_LOG_ADDR
#else
    #define NPU_TASK_POOL_RESMEM_ADDR NPU_NS_TASKPOOL_BASE_ADDR
    #define NPU_LOG_RESMEM_ADDR NPU_NS_LOG_BASE_ADDR
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif
