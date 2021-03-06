#ifndef __ROCKCHIP_PSCI_H
#define __ROCKCHIP_PSCI_H

#define SEC_REG_RD (0x0)
#define SEC_REG_WR (0x1)

/*
 * trust firmware verison
 */
#define RKTF_VER_MAJOR(ver)		(((ver) >> 16) & 0xffff)
#define RKTF_VER_MINOR(ver)		((ver) & 0xffff)

/*
 * pcsi smc funciton id
 */
#define PSCI_SIP_RKTF_VER		(0x82000001)
#define PSCI_SIP_ACCESS_REG		(0x82000002)
#define PSCI_SIP_ACCESS_REG64		(0xc2000002)
#define PSCI_SIP_SUSPEND_WR_CTRBITS	(0x82000003)
#define PSCI_SIP_PENDING_CPUS		(0x82000004)
#define PSCI_SIP_UARTDBG_CFG		(0x82000005)
#define PSCI_SIP_UARTDBG_CFG64		(0xc2000005)
#define PSCI_SIP_EL3FIQ_CFG		(0x82000006)
#define PSCI_SIP_SMEM_CONFIG		(0x82000007)
#define PSCI_SIP_DRAM_FREQ_CONFIG	(0x82000008)

/*
 * pcsi smc funciton err code
 */
#define PSCI_SMC_FUNC_UNK		0xffffffff

/*
 * define PSCI_SIP_UARTDBG_CFG call type
 */
#define UARTDBG_CFG_INIT		0xf0
#define UARTDBG_CFG_OSHDL_TO_OS		0xf1
#define UARTDBG_CFG_OSHDL_CPUSW		0xf3
#define UARTDBG_CFG_OSHDL_DEBUG_ENABLE	0xf4
#define UARTDBG_CFG_OSHDL_DEBUG_DISABLE	0xf5
#define UARTDBG_CFG_SET_SHARE_MEM	0xf6

/*
 * rockchip psci function call interface
 */

#if defined(CONFIG_ARM_PSCI) || defined(CONFIG_ARM64)
u32 rockchip_psci_smc_read(u32 function_id, u32 arg0, u32 arg1, u32 arg2,
			   u32 *val);
u32 rockchip_psci_smc_write(u32 function_id, u32 arg0, u32 arg1, u32 arg2);

u32 rockchip_psci_smc_get_tf_ver(void);
u32 rockchip_secure_reg_read(u32 addr_phy);
u32 rockchip_secure_reg_write(u32 addr_phy, u32 val);

#ifdef CONFIG_ARM64
u32 rockchip_psci_smc_write64(u64 function_id, u64 arg0, u64 arg1, u64 arg2);
u32 rockchip_psci_smc_read64(u64 function_id, u64 arg0, u64 arg1, u64 arg2,
			     u64 *val);
u64 rockchip_secure_reg_read64(u64 addr_phy);
u32 rockchip_secure_reg_write64(u64 addr_phy, u64 val);

void psci_fiq_debugger_uart_irq_tf_cb(u64 sp_el1, u64 offset);
#endif

u32 psci_fiq_debugger_switch_cpu(u32 cpu);
void psci_fiq_debugger_uart_irq_tf_init(u32 irq_id, void *callback);
void psci_fiq_debugger_enable_debug(bool val);

u32 psci_set_memory_secure(bool val);
#else
static inline u32 rockchip_psci_smc_read(u32 function_id, u32 arg0, u32 arg1,
					 u32 arg2, u32 *val)
{
	return 0;
}
static inline u32 rockchip_psci_smc_write(u32 function_id, u32 arg0,
					  u32 arg1, u32 arg2)
{
	return 0;
}

static inline u32 rockchip_psci_smc_get_tf_ver(void) { return 0; }
static inline u32 rockchip_secure_reg_read(u32 addr_phy) { return 0; }
static inline u32 rockchip_secure_reg_write(u32 addr_phy, u32 val) { return 0; }

static inline u32 psci_fiq_debugger_switch_cpu(u32 cpu) { return 0; }
static inline void
psci_fiq_debugger_uart_irq_tf_init(u32 irq_id, void *callback) { }
static inline void psci_fiq_debugger_enable_debug(bool val) { }

static inline u32 psci_set_memory_secure(bool val)
{
	return 0;
}
#endif

#ifdef CONFIG_ARM_PSCI
struct sm_nsec_ctx {
	u32 usr_sp;
	u32 usr_lr;
	u32 irq_spsr;
	u32 irq_sp;
	u32 irq_lr;
	u32 svc_spsr;
	u32 svc_sp;
	u32 svc_lr;
	u32 abt_spsr;
	u32 abt_sp;
	u32 abt_lr;
	u32 und_spsr;
	u32 und_sp;
	u32 und_lr;
	u32 mon_lr;
	u32 mon_spsr;
	u32 r4;
	u32 r5;
	u32 r6;
	u32 r7;
	u32 r8;
	u32 r9;
	u32 r10;
	u32 r11;
	u32 r12;
	u32 r0;
	u32 r1;
	u32 r2;
	u32 r3;
};

int is_psci_enable(void);
#endif

#endif /* __ROCKCHIP_PSCI_H */
