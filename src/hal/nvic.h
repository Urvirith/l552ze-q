#ifndef NVIC_H_
#define NVIC_H_

// NVIC DRIVER
// ARM NVIC MODULE
// NVIC Description - is on pg 529
// NVIC Registers (Programming Manual) - is on 178

/* Nested vectored interrupt controller (NVIC) */

typedef struct {
	volatile uint32_t ISER[16];		    /* Interrupt set-enable register */
	volatile uint32_t Reserved0[16];	/* Offset */
	volatile uint32_t ICER[16]; 	    /* Interrupt clear-enable register */
	volatile uint32_t Reserved1[16];    /* Offset */
	volatile uint32_t ISPR[16];		    /* Interrupt set-pending register */
	volatile uint32_t Reserved2[16];	/* Offset */
	volatile uint32_t ICPR[16];		    /* Interrupt clear-pending register */
	volatile uint32_t Reserved3[16];	/* Offset */
	volatile uint32_t IABR[16];		    /* Interrupt active bit register */
	volatile uint32_t Reserved4[16];	/* Offset */
    volatile uint32_t ITNS[16];		    /* Interrupt active bit register */
	volatile uint32_t Reserved5[16];	/* Offset */
	volatile uint8_t IPR[480];		    /* Interrupt Priority Registers */

}NVIC_Type;

#define NVIC_32BIT      (uint32_t)32

enum nvic_irq {
    WWDG_IRQ,                   /*  0       Window Watchdog */
    PDV_PVM_IRQ,                /*  1       PVD/PVM1/PVM2/PVM3/PVM4 through EXTI lines 16/35/36/37/38 interrupts */
    RTC_IRQ,                    /*  2       RTC secure global interrupts (EXTI line 18) */
    RTC_S_IRQ,                  /*  3       RTC secure global interrupts (EXTI line 18) */
    TAMP_IRQ,                   /*  4       Tamper global interrupt (EXTI line 19) */
    TAMP_S_IRQ,                 /*  5       Tamper secure global interrupt (EXTI line 20) */
    FLASH_IRQ,                  /*  6       Flash memory global interrupt */
    FLASH_S_IRQ,                /*  7       Flash memory secure global interrupt */
    GTZC_IRQ,                   /*  8       TZIC secure global interrupt */
    RCC_IRQ,                    /*  9       RCC global interrupt */
    RCC_S_IRQ,                  /*  10      RCC secure global interrupt */
    EXTI0_IRQ,                  /*  11      EXTI Line0 interrupt */ 
    EXTI1_IRQ,                  /*  12      EXTI Line1 interrupt */
    EXTI2_IRQ,                  /*  13      EXTI Line2 interrupt */
    EXTI3_IRQ,                  /*  14      EXTI Line3 interrupt */
    EXTI4_IRQ,                  /*  15      EXTI Line4 interrupt */
    EXTI5_IRQ,                  /*  16      EXTI Line5 interrupt */
    EXTI6_IRQ,                  /*  17      EXTI Line6 interrupt */
    EXTI7_IRQ,                  /*  18      EXTI Line7 interrupt */
    EXTI8_IRQ,                  /*  19      EXTI Line8 interrupt */
    EXTI9_IRQ,                  /*  20      EXTI Line9 interrupt */
    EXTI10_IRQ,                 /*  21      EXTI Line10 interrupt */
    EXTI11_IRQ,                 /*  22      EXTI Line11 interrupt */
    EXTI12_IRQ,                 /*  23      EXTI Line12 interrupt */
    EXTI13_IRQ,                 /*  24      EXTI Line13 interrupt */
    EXTI14_IRQ,                 /*  25      EXTI Line14 interrupt */
    EXTI15_IRQ,                 /*  26      EXTI Line15 interrupt */
    DMAMUX1_IRQ,                /*  27      DMAMUX1 non-secure interrupt */
    DMAMUX1_S_IRQ,              /*  28      DMAMUX1 secure interrupt */
    DMA1_Channel1_IRQ,          /*  29      DMA1 Channel 1 interrupt */
    DMA1_Channel2_IRQ,          /*  30      DMA1 Channel 2 interrupt */
    DMA1_Channel3_IRQ,          /*  31      DMA1 Channel 3 interrupt */
    DMA1_Channel4_IRQ,          /*  32      DMA1 Channel 4 interrupt */
    DMA1_Channel5_IRQ,          /*  33      DMA1 Channel 5 interrupt */
    DMA1_Channel6_IRQ,          /*  34      DMA1 Channel 6 interrupt */
    DMA1_Channel7_IRQ,          /*  35      DMA1 Channel 7 interrupt */
    DMA1_Channel8_IRQ,          /*  36      DMA1 Channel 8 interrupt */
    ADC1_2_IRQ,                 /*  37      ADC1 & ADC2 interrupt */
    DAC_IRQ,                    /*  38      DAC1&2 underrun errors interrupt */
    FDCAN1_IT0_IRQ,             /*  39      FDCAN1 Interrupt 0 interrupt */
    FDCAN1_IT1_IRQ,             /*  40      FDCAN1 Interrupt 1 interrupt */
    TIM1_BRK_IRQ,               /*  41      TIM1 Break interrupt */
    TIM1_UP_IRQ,                /*  42      TIM1 Update interrupt */
    TIM1_TRG_COM_IRQ,           /*  43      TIM1 Trigger and Commutation interrupt */
    TIM1_CC_IRQ,                /*  44      TIM1 Capture Compare interrupt */
    TIM2_IRQ,                   /*  45      TIM2 interrupt */
    TIM3_IRQ,                   /*  46      TIM3 interrupt */
    TIM4_IRQ,                   /*  47      TIM4 interrupt */
    TIM5_IRQ,                   /*  48      TIM5 interrupt */
    TIM6_IRQ,                   /*  49      TIM6 interrupt */
    TIM7_IRQ,                   /*  50      TIM7 interrupt */
    TIM8_BRK_IRQ,               /*  51      TIM8 Break interrupt */
    TIM8_UP_IRQ,                /*  52      TIM8 Update interrupt */
    TIM8_TRG_COM_IRQ,           /*  53      TIM8 Trigger and Commutation interrupt */
    TIM8_CC_IRQ,                /*  54      TIM8 Capture Compare interrupt */
    I2C1_EV_IRQ,                /*  55      I2C1 Event interrupt */
    I2C1_ER_IRQ,                /*  56      I2C1 Error interrupt */
    I2C2_EV_IRQ,                /*  57      I2C2 Event interrupt */
    I2C2_ER_IRQ,                /*  58      I2C2 Error interrupt */
    SPI1_IRQ,                   /*  59      SPI1 interrupt */
    SPI2_IRQ,                   /*  60      SPI2 interrupt */
    USART1_IRQ,                 /*  61      USART1 interrupt */
    USART2_IRQ,                 /*  62      USART2 interrupt */
    USART3_IRQ,                 /*  63      USART3 interrupt */
    UART4_IRQ,                  /*  64      UART4 interrupt */
    UART5_IRQ,                  /*  65      UART5 interrupt */
    LPUART1_IRQ,                /*  66      LP UART1 interrupt */
    LPTIM1_IRQ,                 /*  67      LP TIM1 interrupt */
    LPTIM2_IRQ,                 /*  68      LP TIM2 interrupt */
    TIM15_IRQ,                  /*  69      TIM15 interrupt */
    TIM16_IRQ,                  /*  70      TIM16 interrupt */
    TIM17_IRQ,                  /*  71      TIM17 interrupt */
    COMP_IRQ,                   /*  72      COMP1&2 interrupt */
    USB_FS_IRQ,                 /*  73      USB FS interrupt */
    CRS_IRQ,                    /*  74      CRS interrupt */
    FMC_IRQ,                    /*  75      FMC interrupt */
    OCTOSPI1_IRQ,               /*  76      OctoSPI1 global interrupt */
    SDMMC1_IRQ = 78,            /*  78      SDMMC1 interrupt */
    DMA2_Channel1_IRQ,          /*  80      DMA2 Channel 1 interrupt */
    DMA2_Channel2_IRQ,          /*  81      DMA2 Channel 2 interrupt */
    DMA2_Channel3_IRQ,          /*  82      DMA2 Channel 3 interrupt */
    DMA2_Channel4_IRQ,          /*  83      DMA2 Channel 4 interrupt */
    DMA2_Channel5_IRQ,          /*  84      DMA2 Channel 5 interrupt */
    DMA2_Channel6_IRQ,          /*  85      DMA2 Channel 6 interrupt */
    DMA2_Channel7_IRQ,          /*  86      DMA2 Channel 7 interrupt */
    DMA2_Channel8_IRQ,          /*  87      DMA2 Channel 8 interrupt */
    I2C3_EV_IRQ,                /*  88      I2C3 event interrupt */
    I2C3_ER_IRQ,                /*  89      I2C3 error interrupt */
    SAI1_IRQ,                   /*  90      Serial Audio Interface 1 global interrupt */
    SAI2_IRQ,                   /*  91      Serial Audio Interface 2 global interrupt */
    TSC_IRQ,                    /*  92      Touch Sense Controller global interrupt */
    RNG_IRQ = 94,               /*  94      RNG global interrupt */
    FPU_IRQ,                    /*  95      FPU interrupt */
    HASH_IRQ,                   /*  96      HASH interrupt */
    LPTIM3_IRQ = 98,            /*  98      LP TIM3 interrupt */
    SPI3_IRQ,                   /*  99      SPI3 interrupt */
    I2C4_ER_IRQ,                /*  100     I2C4 error interrupt */
    I2C4_EV_IRQ,                /*  101     I2C4 event interrupt */
    DFSDM1_FLT0_IRQ,            /*  102     DFSDM1 Filter 0 global interrupt */
    DFSDM1_FLT1_IRQ,            /*  103     DFSDM1 Filter 1 global interrupt */
    DFSDM1_FLT2_IRQ,            /*  104     DFSDM1 Filter 2 global interrupt */
    DFSDM1_FLT3_IRQ,            /*  105     DFSDM1 Filter 3 global interrupt */
    UCPD1_IRQ,                  /*  106     UCPD1 interrupt */
    ICACHE_IRQ,                 /*  107     ICACHE interrupt */
};


#endif /* NVIC_H_ */