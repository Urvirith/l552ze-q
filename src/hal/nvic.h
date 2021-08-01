#ifndef NVIC_H_
#define NVIC_H_

// NVIC DRIVER
// ARM NVIC MODULE
// NVIC Description - is on pg 529
// NVIC Registers (Programming Manual) - is on 178

/* Nested vectored interrupt controller (NVIC) */

typedef struct {
	volatile uint32_t   ISER[16];		    /* Interrupt Set-Enable register */
	volatile uint32_t   Reserved0[16];	    /* Offset */
	volatile uint32_t   ICER[16]; 	        /* Interrupt Clear-Enable register */
	volatile uint32_t   Reserved1[16];      /* Offset */
	volatile uint32_t   ISPR[16];		    /* Interrupt Set-Pending Registers */
	volatile uint32_t   Reserved2[16];	    /* Offset */
	volatile uint32_t   ICPR[16];		    /* Interrupt Clear-Pending Registers */
	volatile uint32_t   Reserved3[16];	    /* Offset */
	volatile uint32_t   IABR[16];		    /* Interrupt Active Bit Registers */
	volatile uint32_t   Reserved4[16];	    /* Offset */
    volatile uint32_t   ITNS[16];		    /* Interrupt Target Non-Secure Registers */
	volatile uint32_t   Reserved5[16];	    /* Offset */
	volatile uint8_t    IPR[480];		    /* Interrupt Priority Registers */
} NVIC_TypeDef;

#define NVIC_32BIT      (uint32_t)32
#define NVIC_8BIT       (uint32_t)8
#define NVIC_ARRAYSIZE  (uint32_t)16
#define NVIC_IPR_SIZE   (uint32_t)480

void nvic_enable_interrupt(NVIC_TypeDef *ptr, uint32_t irq_num);
void nvic_set_priority(NVIC_TypeDef *ptr, uint32_t irq_num, uint8_t priority, uint8_t sub_priority);

#endif /* NVIC_H_ */