#ifndef TIMER_H_
#define TIMER_H_

// TIMER DRIVER
// ARM TIMER MODULE - FREE RUNNING COUNTERS -32kHz or 25MHz
// Timer Description - is on pg 1181

/* Timers */

/* Register Base */
/* Defined In The Board Specific Folder */

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR1;              // Control Register 1
    volatile uint32_t CR2;              // Control Register 2
    volatile uint32_t SMCR;             // Slave Mode Control Register
    volatile uint32_t DIER;             // DMA/ Interrupt Enable Register
    volatile uint32_t SR;               // Status Register
    volatile uint32_t EGR;              // Event Generation Register
    volatile uint32_t CCMR1;            // Capture/Compare Mode Register 1
    volatile uint32_t CCMR2;            // Capture/Compare Mode Register 2
    volatile uint32_t CCER;             // Capture/Compare Enable Register
    volatile uint32_t CNT;              // Counter Register
    volatile uint32_t PSC;              // Prescaler Register
    volatile uint32_t ARR;              // Auto Reload Register
    volatile uint32_t RCR;              // Repetition Counter Register
    volatile uint32_t CCR1;             // Capture/Compare Register 1
    volatile uint32_t CCR2;             // Capture/Compare Register 2
    volatile uint32_t CCR3;             // Capture/Compare Register 3
    volatile uint32_t CCR4;             // Capture/Compare Register 4
    volatile uint32_t BDTR;             // Break and Dead-Time Register
    volatile uint32_t DCR;              // DMA Control Register
    volatile uint32_t DMAR;             // DMA Address Register
    volatile uint32_t OR1;              // Option Register 1
} TIMER_TypeDef;

/* Register Masks */
/* CR1 */
#define CMS_MASK            MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */
#define CKD_MASK            MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */

/* CCMR */
#define CCS_MASK            MASK_2_BIT
#define OCM_MASK            MASK_3_BIT

/* Register Bits */
/* CR1 */
#define EN_BIT              BIT_0           /* 0 = Disabled, 1 = Enabled */
#define UDIS_BIT            BIT_1           /* Update event, 0 = EN, 1 = DISABLED */
#define URS_BIT             BIT_2           /* 0 = All events enables, 1 = Only OF or UF Events */
#define OPM_BIT             BIT_3           /* 0 = Continous, 1 = ONS (clears en bit) */
#define DIR_BIT             BIT_4           /* 0 = Upcounter, 1 = Downcounter (ONLY ACTIVE IF CMS = 00) */
#define ARPE_BIT            BIT_7           /* 0 ARR = Not Buffered, 1 = Buffered */
#define UIFREMAP_BIT        BIT_11          /* Output, 0 = Pulse, 1 = Toggle */

/* SR, DIER, EGR */
#define UPDATE_BIT          BIT_0

/* CCMR */
#define OC1FE_BIT           BIT_2           /* Output Compare 1 Fast Enable */
#define OC1PE_BIT           BIT_3           /* Output Compare 1 Preload Enable */
#define OC1CE_BIT           BIT_7           /* Output Compare 1 Clear Enable */
#define OC2FE_BIT           BIT_10          /* Output Compare 2 Fast Enable */
#define OC2PE_BIT           BIT_11          /* Output Compare 2 Preload Enable */
#define OC2CE_BIT           BIT_15          /* Output Compare 2 Clear Enable */
#define OC1M_BIT            BIT_16          /* Output Compare 1 Mode */
#define OC2M_BIT            BIT_24          /* Output Compare 2 Mode */

/* CCER */
#define CC1E_BIT            BIT_0           /* Capture/Compare Output Enable */
#define CC1P_BIT            BIT_1           /* Capture/Compare Output Polarity */
#define CC1NP_BIT           BIT_3           /* Capture/Compare Output Polarity */
#define CC2E_BIT            BIT_4           /* Capture/Compare Output Enable */
#define CC2P_BIT            BIT_5           /* Capture/Compare Output Polarity */
#define CC2NP_BIT           BIT_7           /* Capture/Compare Output Polarity */
#define CC3E_BIT            BIT_8           /* Capture/Compare Output Enable */
#define CC3P_BIT            BIT_9           /* Capture/Compare Output Polarity */
#define CC3NP_BIT           BIT_11          /* Capture/Compare Output Polarity */
#define CC4E_BIT            BIT_12          /* Capture/Compare Output Enable */
#define CC4P_BIT            BIT_13          /* Capture/Compare Output Polarity */
#define CC4NP_BIT           BIT_15          /* Capture/Compare Output Polarity */


/* Register Offsets */
/* CR1 */
#define CMS_OFFSET          5               /* 00 = Edge Aligned     01 = Center Aligned Down     10 = Center Aligned Up     11 - Center Aligned Up */
#define CKD_OFFSET          8               /* 00 = Tdts = Tclk_int  01 = Tdts = 2*Tclk_int       10 = Tdts = 4*Tclk_int     11 - Reserved */
/* CCMR */
#define CC1S_OFFSET         0               /* Capture Compare 1 Mode 00: CC2 channel is configured as output 01: CC1 channel is configured as input, IC1 is mapped on TI1 10: CC1 channel is configured as input, IC1 is mapped on TI1 11: CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if an internal trigger input is selected through the TS bit (TIMx_SMCR register) */
#define OC1M_OFFSET         4               /* Output Compare 1 Mode 0110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 0111: PWM mode 1 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive. */
#define CC2S_OFFSET         8               /* Capture Compare 2 Mode 00: CC2 channel is configured as output 01: CC2 channel is configured as input, IC2 is mapped on TI2 10: CC2 channel is configured as input, IC2 is mapped on TI1 11: CC2 channel is configured as input, IC2 is mapped on TRC. This mode is working only if an internal trigger input is selected through the TS bit (TIMx_SMCR register) */
#define OC2M_OFFSET         12              /* Output Compare 2 Mode 0110: PWM mode 1 - In upcounting, channel 2 is active as long as TIMx_CNT<TIMx_CCR2 0111: PWM mode 2 - In upcounting, channel 2 is inactive as long as TIMx_CNT<TIMx_CCR2 else active. In downcounting, channel 2 is active as long as TIMx_CNT>TIMx_CCR2 else inactive. */

/* CNT */
#define CLEAR_CNT           (uint32_t)0

/* PWM */
#define PWM_MODE1           (uint32_t)6
#define PWM_MODE2           (uint32_t)7
#define CCS_OUTPUT          (uint32_t)0

/* Enumerations */
// 0 = Continous, 1 = ONS (clears en bit)
typedef enum timer_type {
    Timer_Cont, 
    Timer_Ons
} TIMER_Type;

// 0 = Upcounter, 1 = Downcounter
typedef enum timer_direction {
    Timer_Upcount,
    Timer_Down
} TIMER_Direction;

/* Public Functions */
void timer_open(TIMER_TypeDef *ptr, TIMER_Type ons, TIMER_Direction dir);
bool timer_get_flag(TIMER_TypeDef *ptr);
void timer_clr_flag(TIMER_TypeDef *ptr);
void timer_set_interrupt(TIMER_TypeDef *ptr);
uint32_t timer_read_count(TIMER_TypeDef *ptr);
void timer_clr_count(TIMER_TypeDef *ptr);
void timer_start(TIMER_TypeDef *ptr);
void timer_stop(TIMER_TypeDef *ptr);
void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale);
void timer_set_pwm_ccr1(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ccr2(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ccr3(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ccr4(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ch1(TIMER_TypeDef *ptr);
void timer_set_pwm_ch2(TIMER_TypeDef *ptr);
void timer_set_pwm_ch3(TIMER_TypeDef *ptr);
void timer_set_pwm_ch4(TIMER_TypeDef *ptr);

#endif /* TIMER_H_ */