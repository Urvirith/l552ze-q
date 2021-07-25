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
    volatile uint32_t CR1;      // Control Register 1
    volatile uint32_t CR2;      // Control Register 2
    volatile uint32_t SMCR;     // Slave Mode Control Register
    volatile uint32_t DIER;     // DMA/ Interrupt Enable Register
    volatile uint32_t SR;       // Status Register
    volatile uint32_t EGR;      // Event Generation Register
    volatile uint32_t CCMR1;    // Capture/Compare Mode Register 1
    volatile uint32_t CCMR2;    // Capture/Compare Mode Register 2
    volatile uint32_t CCER;     // Capture/Compare Enable Register
    volatile uint32_t CNT;      // Counter Register
    volatile uint32_t PSC;      // Prescaler Register
    volatile uint32_t ARR;      // Auto Reload Register
    volatile uint32_t RCR;      // Repetition Counter Register
    volatile uint32_t CCR1;     // Capture/Compare Register 1
    volatile uint32_t CCR2;     // Capture/Compare Register 2
    volatile uint32_t CCR3;     // Capture/Compare Register 3
    volatile uint32_t CCR4;     // Capture/Compare Register 4
    volatile uint32_t BDTR;     // Break and Dead-Time Register
    volatile uint32_t DCR;      // DMA Control Register
    volatile uint32_t DMAR;     // DMA Address Register
    volatile uint32_t OR1;      // Option Register 1
} TIMER_TypeDef;

/* Register Masks */
/* CR1 */
#define CMS_MASK            MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */
#define CKD_MASK            MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */

/* Register Bits */
/* CR1 */
#define EN_BIT              BIT_0           /* 0 = Disabled, 1 = Enabled */
#define UDIS_BIT            BIT_1           /* Update event, 0 = EN, 1 = DISABLED */
#define URS_BIT             BIT_2           /* 0 = All events enables, 1 = Only OF or UF Events */
#define OPM_BIT             BIT_3           /* 0 = Continous, 1 = ONS (clears en bit) */
#define DIR_BIT             BIT_4           /* 0 = Upcounter, 1 = Downcounter (ONLY ACTIVE IF CMS = 00) */
#define ARPE_BIT            BIT_7           /* 0 ARR = Not Buffered, 1 = Buffered */
#define UIFREMAP_BIT        BIT_11          /* Output, 0 = Pulse, 1 = Toggle */

/* SR */
#define UPDATE_BIT          BIT_0


/* Register Offsets */
/* CR1 */
#define CMS_OFFSET          5               /* 00 = Edge Aligned     01 = Center Aligned Down     10 = Center Aligned Up     11 - Center Aligned Up */
#define CKD_OFFSET          8               /* 00 = Tdts = Tclk_int  01 = Tdts = 2*Tclk_int       10 = Tdts = 4*Tclk_int     11 - Reserved */
/* CNT */
#define CLEAR_CNT           (uint32_t)0  

/* Enumerations */
// 0 = Continous, 1 = ONS (clears en bit)
enum timer_type {Timer_Cont, Timer_Ons};
// 0 = Upcounter, 1 = Downcounter
enum timer_direction {Timer_Upcount, Timer_Down};

/* Public Functions */
void timer_open(TIMER_TypeDef *ptr, uint32_t ons, uint32_t dir);
bool timer_get_flag(TIMER_TypeDef *ptr);
void timer_clr_flag(TIMER_TypeDef *ptr);
uint32_t timer_read_count(TIMER_TypeDef *ptr);
void timer_clr_count(TIMER_TypeDef *ptr);
void timer_start(TIMER_TypeDef *ptr);
void timer_stop(TIMER_TypeDef *ptr);
void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale);

#endif /* TIMER_H_ */