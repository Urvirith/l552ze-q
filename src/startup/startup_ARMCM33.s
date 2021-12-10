/******************************************************************************
 * @file     startup_ARMCM33.S
 * @brief    CMSIS-Core Device Startup File for Cortex-M33 Device
 * @version  V2.3.0
 * @date     26. May 2021
 ******************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

                .syntax  unified
                .arch    armv8-m.main

                #define __INITIAL_SP     __StackTop
                #define __STACK_LIMIT    __StackLimit
                #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
                #define __STACK_SEAL     __StackSeal
                #endif

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Initial Stack Pointer */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    MemManage_Handler                  /* -12 MPU Fault Handler */
                .long    BusFault_Handler                   /* -11 Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long    SecureFault_Handler                /*  -9 Secure Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVCall Handler */
                .long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long    WWDG_IRQHandler                    /*   0  Window Watchdog */
                .long    PDV_PVM_IRQHandler                 /*   1  PVD/PVM1/PVM2/PVM3/PVM4 through EXTI lines 16/35/36/37/38 interrupts */
                .long    RTC_IRQHandler                     /*   2  RTC secure global interrupts (EXTI line 18) */
                .long    RTC_S_IRQHandler                   /*   3  RTC secure global interrupts (EXTI line 18) */
                .long    TAMP_IRQHandler                    /*   4  Tamper global interrupt (EXTI line 19) */
                .long    TAMP_S_IRQHandler                  /*   5  Tamper secure global interrupt (EXTI line 20) */
                .long    FLASH_IRQHandler                   /*   6  Flash memory global interrupt */
                .long    FLASH_S_IRQHandler                 /*   7  Flash memory secure global interrupt */
                .long    GTZC_IRQHandler                    /*   8  TZIC secure global interrupt */
                .long    RCC_IRQHandler                     /*   9  RCC global interrupt */
                .long    RCC_S_IRQHandler                   /*  10  RCC secure global interrupt */
                .long    EXTI0_IRQHandler                   /*  11  EXTI Line0 interrupt */ 
                .long    EXTI1_IRQHandler                   /*  12  EXTI Line1 interrupt */
                .long    EXTI2_IRQHandler                   /*  13  EXTI Line2 interrupt */
                .long    EXTI3_IRQHandler                   /*  14  EXTI Line3 interrupt */
                .long    EXTI4_IRQHandler                   /*  15  EXTI Line4 interrupt */
                .long    EXTI5_IRQHandler                   /*  16  EXTI Line5 interrupt */
                .long    EXTI6_IRQHandler                   /*  17  EXTI Line6 interrupt */
                .long    EXTI7_IRQHandler                   /*  18  EXTI Line7 interrupt */
                .long    EXTI8_IRQHandler                   /*  19  EXTI Line8 interrupt */
                .long    EXTI9_IRQHandler                   /*  20  EXTI Line9 interrupt */
                .long    EXTI10_IRQHandler                  /*  21  EXTI Line10 interrupt */
                .long    EXTI11_IRQHandler                  /*  22  EXTI Line11 interrupt */
                .long    EXTI12_IRQHandler                  /*  23  EXTI Line12 interrupt */
                .long    EXTI13_IRQHandler                  /*  24  EXTI Line13 interrupt */
                .long    EXTI14_IRQHandler                  /*  25  EXTI Line14 interrupt */
                .long    EXTI15_IRQHandler                  /*  26  EXTI Line15 interrupt */
                .long    DMAMUX1_IRQHandler                 /*  27  DMAMUX1 non-secure interrupt */
                .long    DMAMUX1_S_IRQHandler               /*  28  DMAMUX1 secure interrupt */
                .long    DMA1_Channel1_IRQHandler           /*  29  DMA1 Channel 1 interrupt */
                .long    DMA1_Channel2_IRQHandler           /*  30  DMA1 Channel 2 interrupt */
                .long    DMA1_Channel3_IRQHandler           /*  31  DMA1 Channel 3 interrupt */
                .long    DMA1_Channel4_IRQHandler           /*  32  DMA1 Channel 4 interrupt */
                .long    DMA1_Channel5_IRQHandler           /*  33  DMA1 Channel 5 interrupt */
                .long    DMA1_Channel6_IRQHandler           /*  34  DMA1 Channel 6 interrupt */
                .long    DMA1_Channel7_IRQHandler           /*  35  DMA1 Channel 7 interrupt */
                .long    DMA1_Channel8_IRQHandler           /*  36  DMA1 Channel 8 interrupt */
                .long    ADC1_2_IRQHandler                  /*  37  ADC1 & ADC2 interrupt */
                .long    DAC_IRQHandler                     /*  38  DAC1&2 underrun errors interrupt */
                .long    FDCAN1_IT0_IRQHandler              /*  39  FDCAN1 Interrupt 0 interrupt */
                .long    FDCAN1_IT1_IRQHandler              /*  40  FDCAN1 Interrupt 1 interrupt */
                .long    TIM1_BRK_IRQHandler                /*  41  TIM1 Break interrupt */
                .long    TIM1_UP_IRQHandler                 /*  42  TIM1 Update interrupt */
                .long    TIM1_TRG_COM_IRQHandler            /*  43  TIM1 Trigger and Commutation interrupt */
                .long    TIM1_CC_IRQHandler                 /*  44  TIM1 Capture Compare interrupt */
                .long    TIM2_IRQHandler                    /*  45  TIM2 interrupt */
                .long    TIM3_IRQHandler                    /*  46  TIM3 interrupt */
                .long    TIM4_IRQHandler                    /*  47  TIM4 interrupt */
                .long    TIM5_IRQHandler                    /*  48  TIM5 interrupt */
                .long    TIM6_IRQHandler                    /*  49  TIM6 interrupt */
                .long    TIM7_IRQHandler                    /*  50  TIM7 interrupt */
                .long    TIM8_BRK_IRQHandler                /*  51  TIM8 Break interrupt */
                .long    TIM8_UP_IRQHandler                 /*  52  TIM8 Update interrupt */
                .long    TIM8_TRG_COM_IRQHandler            /*  53  TIM8 Trigger and Commutation interrupt */
                .long    TIM8_CC_IRQHandler                 /*  54  TIM8 Capture Compare interrupt */
                .long    I2C1_EV_IRQHandler                 /*  55  I2C1 Event interrupt */
                .long    I2C1_ER_IRQHandler                 /*  56  I2C1 Error interrupt */
                .long    I2C2_EV_IRQHandler                 /*  57  I2C2 Event interrupt */
                .long    I2C2_ER_IRQHandler                 /*  58  I2C2 Error interrupt */
                .long    SPI1_IRQHandler                    /*  59  SPI1 interrupt */
                .long    SPI2_IRQHandler                    /*  60  SPI2 interrupt */
                .long    USART1_IRQHandler                  /*  61  USART1 interrupt */
                .long    USART2_IRQHandler                  /*  62  USART2 interrupt */
                .long    USART3_IRQHandler                  /*  63  USART3 interrupt */
                .long    UART4_IRQHandler                   /*  64  UART4 interrupt */
                .long    UART5_IRQHandler                   /*  65  UART5 interrupt */
                .long    LPUART1_IRQHandler                 /*  66  LP UART1 interrupt */
                .long    LPTIM1_IRQHandler                  /*  67  LP TIM1 interrupt */
                .long    LPTIM2_IRQHandler                  /*  68  LP TIM2 interrupt */
                .long    TIM15_IRQHandler                   /*  69  TIM15 interrupt */
                .long    TIM16_IRQHandler                   /*  70  TIM16 interrupt */
                .long    TIM17_IRQHandler                   /*  71  TIM17 interrupt */
                .long    COMP_IRQHandler                    /*  72  COMP1&2 interrupt */
                .long    USB_FS_IRQHandler                  /*  73  USB FS interrupt */
                .long    CRS_IRQHandler                     /*  74  CRS interrupt */
                .long    FMC_IRQHandler                     /*  75  FMC interrupt */
                .long    OCTOSPI1_IRQHandler                /*  76  OctoSPI1 global interrupt */
                .long    0                                  /*  77  Reserved interrupt */
                .long    SDMMC1_IRQHandler                  /*  78  SDMMC1 interrupt */
                .long    0                                  /*  79  Reserved interrupt */
                .long    DMA2_Channel1_IRQHandler           /*  80  DMA2 Channel 1 interrupt */
                .long    DMA2_Channel2_IRQHandler           /*  81  DMA2 Channel 2 interrupt */
                .long    DMA2_Channel3_IRQHandler           /*  82  DMA2 Channel 3 interrupt */
                .long    DMA2_Channel4_IRQHandler           /*  83  DMA2 Channel 4 interrupt */
                .long    DMA2_Channel5_IRQHandler           /*  84  DMA2 Channel 5 interrupt */
                .long    DMA2_Channel6_IRQHandler           /*  85  DMA2 Channel 6 interrupt */
                .long    DMA2_Channel7_IRQHandler           /*  86  DMA2 Channel 7 interrupt */
                .long    DMA2_Channel8_IRQHandler           /*  87  DMA2 Channel 8 interrupt */
                .long    I2C3_EV_IRQHandler                 /*  88  I2C3 event interrupt */
                .long    I2C3_ER_IRQHandler                 /*  89  I2C3 error interrupt */
                .long    SAI1_IRQHandler                    /*  90  Serial Audio Interface 1 global interrupt */
                .long    SAI2_IRQHandler                    /*  91  Serial Audio Interface 2 global interrupt */
                .long    TSC_IRQHandler                     /*  92  Touch Sense Controller global interrupt */
                .long    0                                  /*  93  Reserved interrupt */
                .long    RNG_IRQHandler                     /*  94  RNG global interrupt */
                .long    FPU_IRQHandler                     /*  95  FPU interrupt */
                .long    HASH_IRQHandler                    /*  96  HASH interrupt */
                .long    0                                  /*  97  Reserved interrupt */
                .long    LPTIM3_IRQHandler                  /*  98  LP TIM3 interrupt */
                .long    SPI3_IRQHandler                    /*  99  SPI3 interrupt */
                .long    I2C4_ER_IRQHandler                 /*  100 I2C4 error interrupt */
                .long    I2C4_EV_IRQHandler                 /*  101 I2C4 event interrupt */
                .long    DFSDM1_FLT0_IRQHandler             /*  102 DFSDM1 Filter 0 global interrupt */
                .long    DFSDM1_FLT1_IRQHandler             /*  103 DFSDM1 Filter 1 global interrupt */
                .long    DFSDM1_FLT2_IRQHandler             /*  104 DFSDM1 Filter 2 global interrupt */
                .long    DFSDM1_FLT3_IRQHandler             /*  105 DFSDM1 Filter 3 global interrupt */
                .long    UCPD1_IRQHandler                   /*  106 UCPD1 interrupt */
                .long    ICACHE_IRQHandler                  /*  107 ICACHE interrupt */
                .long    0                                  /*  108 Reserved interrupt */

                .space   (371 * 4)                          /* Interrupts 109 .. 480 are left out */
__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
                ldr      r0, =__StackTop
                msr      psp, r0

                ldr      r0, =__StackLimit
                msr      msplim, r0
                msr      psplim, r0

                #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
                #ldr      r0, =__StackSeal
                #ldr      r1, =0xFEF5EDA5U
                #strd     r1,r1,[r0,#0]
                #endif

                bl       _system_init

                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]                /* source address */
                ldr      r2, [r4, #4]            /* destination address */
                ldr      r3, [r4, #8]            /* word count */
                lsls     r3, r3, #2              /* byte count */

.L_loop0_0:
                subs     r3, #4                  /* decrement byte count */
                ittt     ge
                ldrge    r0, [r1, r3]
                strge    r0, [r2, r3]
                bge      .L_loop0_0

                adds     r4, #12
                b        .L_loop0
.L_loop0_done:

                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]                /* destination address */
                ldr      r2, [r3, #4]            /* word count */
                lsls     r2, r2, #2              /* byte count */
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4                  /* decrement byte count */
                itt      ge
                strge    r0, [r1, r2]
                bge      .L_loop2_0

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:

                bl       _start

                .fnend
                .size    Reset_Handler, . - Reset_Handler


/* The default macro is not used for HardFault_Handler
 * because this results in a poor debug illusion.
 */
                .thumb_func
                .type    HardFault_Handler, %function
                .weak    HardFault_Handler
                .fnstart
HardFault_Handler:
                b        .
                .fnend
                .size    HardFault_Handler, . - HardFault_Handler

                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SecureFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  WWDG_IRQHandler                    /*   0  Window Watchdog */
                Set_Default_Handler  PDV_PVM_IRQHandler                 /*   1  PVD/PVM1/PVM2/PVM3/PVM4 through EXTI lines 16/35/36/37/38 interrupts */
                Set_Default_Handler  RTC_IRQHandler                     /*   2  RTC secure global interrupts (EXTI line 18) */
                Set_Default_Handler  RTC_S_IRQHandler                   /*   3  RTC secure global interrupts (EXTI line 18) */
                Set_Default_Handler  TAMP_IRQHandler                    /*   4  Tamper global interrupt (EXTI line 19) */
                Set_Default_Handler  TAMP_S_IRQHandler                  /*   5  Tamper secure global interrupt (EXTI line 20) */
                Set_Default_Handler  FLASH_IRQHandler                   /*   6  Flash memory global interrupt */
                Set_Default_Handler  FLASH_S_IRQHandler                 /*   7  Flash memory secure global interrupt */
                Set_Default_Handler  GTZC_IRQHandler                    /*   8  TZIC secure global interrupt */
                Set_Default_Handler  RCC_IRQHandler                     /*   9  RCC global interrupt */
                Set_Default_Handler  RCC_S_IRQHandler                   /*  10  RCC secure global interrupt */
                Set_Default_Handler  EXTI0_IRQHandler                   /*  11  EXTI Line0 interrupt */ 
                Set_Default_Handler  EXTI1_IRQHandler                   /*  12  EXTI Line1 interrupt */
                Set_Default_Handler  EXTI2_IRQHandler                   /*  13  EXTI Line2 interrupt */
                Set_Default_Handler  EXTI3_IRQHandler                   /*  14  EXTI Line3 interrupt */
                Set_Default_Handler  EXTI4_IRQHandler                   /*  15  EXTI Line4 interrupt */
                Set_Default_Handler  EXTI5_IRQHandler                   /*  16  EXTI Line5 interrupt */
                Set_Default_Handler  EXTI6_IRQHandler                   /*  17  EXTI Line6 interrupt */
                Set_Default_Handler  EXTI7_IRQHandler                   /*  18  EXTI Line7 interrupt */
                Set_Default_Handler  EXTI8_IRQHandler                   /*  19  EXTI Line8 interrupt */
                Set_Default_Handler  EXTI9_IRQHandler                   /*  20  EXTI Line9 interrupt */
                Set_Default_Handler  EXTI10_IRQHandler                  /*  21  EXTI Line10 interrupt */
                Set_Default_Handler  EXTI11_IRQHandler                  /*  22  EXTI Line11 interrupt */
                Set_Default_Handler  EXTI12_IRQHandler                  /*  23  EXTI Line12 interrupt */
                Set_Default_Handler  EXTI13_IRQHandler                  /*  24  EXTI Line13 interrupt */
                Set_Default_Handler  EXTI14_IRQHandler                  /*  25  EXTI Line14 interrupt */
                Set_Default_Handler  EXTI15_IRQHandler                  /*  26  EXTI Line15 interrupt */
                Set_Default_Handler  DMAMUX1_IRQHandler                 /*  27  DMAMUX1 non-secure interrupt */
                Set_Default_Handler  DMAMUX1_S_IRQHandler               /*  28  DMAMUX1 secure interrupt */
                Set_Default_Handler  DMA1_Channel1_IRQHandler           /*  29  DMA1 Channel 1 interrupt */
                Set_Default_Handler  DMA1_Channel2_IRQHandler           /*  30  DMA1 Channel 2 interrupt */
                Set_Default_Handler  DMA1_Channel3_IRQHandler           /*  31  DMA1 Channel 3 interrupt */
                Set_Default_Handler  DMA1_Channel4_IRQHandler           /*  32  DMA1 Channel 4 interrupt */
                Set_Default_Handler  DMA1_Channel5_IRQHandler           /*  33  DMA1 Channel 5 interrupt */
                Set_Default_Handler  DMA1_Channel6_IRQHandler           /*  34  DMA1 Channel 6 interrupt */
                Set_Default_Handler  DMA1_Channel7_IRQHandler           /*  35  DMA1 Channel 7 interrupt */
                Set_Default_Handler  DMA1_Channel8_IRQHandler           /*  36  DMA1 Channel 8 interrupt */
                Set_Default_Handler  ADC1_2_IRQHandler                  /*  37  ADC1 & ADC2 interrupt */
                Set_Default_Handler  DAC_IRQHandler                     /*  38  DAC1&2 underrun errors interrupt */
                Set_Default_Handler  FDCAN1_IT0_IRQHandler              /*  39  FDCAN1 Interrupt 0 interrupt */
                Set_Default_Handler  FDCAN1_IT1_IRQHandler              /*  40  FDCAN1 Interrupt 1 interrupt */
                Set_Default_Handler  TIM1_BRK_IRQHandler                /*  41  TIM1 Break interrupt */
                Set_Default_Handler  TIM1_UP_IRQHandler                 /*  42  TIM1 Update interrupt */
                Set_Default_Handler  TIM1_TRG_COM_IRQHandler            /*  43  TIM1 Trigger and Commutation interrupt */
                Set_Default_Handler  TIM1_CC_IRQHandler                 /*  44  TIM1 Capture Compare interrupt */
                Set_Default_Handler  TIM2_IRQHandler                    /*  45  TIM2 interrupt */
                Set_Default_Handler  TIM3_IRQHandler                    /*  46  TIM3 interrupt */
                Set_Default_Handler  TIM4_IRQHandler                    /*  47  TIM4 interrupt */
                Set_Default_Handler  TIM5_IRQHandler                    /*  48  TIM5 interrupt */
                Set_Default_Handler  TIM6_IRQHandler                    /*  49  TIM6 interrupt */
                Set_Default_Handler  TIM7_IRQHandler                    /*  50  TIM7 interrupt */
                Set_Default_Handler  TIM8_BRK_IRQHandler                /*  51  TIM8 Break interrupt */
                Set_Default_Handler  TIM8_UP_IRQHandler                 /*  52  TIM8 Update interrupt */
                Set_Default_Handler  TIM8_TRG_COM_IRQHandler            /*  53  TIM8 Trigger and Commutation interrupt */
                Set_Default_Handler  TIM8_CC_IRQHandler                 /*  54  TIM8 Capture Compare interrupt */
                Set_Default_Handler  I2C1_EV_IRQHandler                 /*  55  I2C1 Event interrupt */
                Set_Default_Handler  I2C1_ER_IRQHandler                 /*  56  I2C1 Error interrupt */
                Set_Default_Handler  I2C2_EV_IRQHandler                 /*  57  I2C2 Event interrupt */
                Set_Default_Handler  I2C2_ER_IRQHandler                 /*  58  I2C2 Error interrupt */
                Set_Default_Handler  SPI1_IRQHandler                    /*  59  SPI1 interrupt */
                Set_Default_Handler  SPI2_IRQHandler                    /*  60  SPI2 interrupt */
                Set_Default_Handler  USART1_IRQHandler                  /*  61  USART1 interrupt */
                Set_Default_Handler  USART2_IRQHandler                  /*  62  USART2 interrupt */
                Set_Default_Handler  USART3_IRQHandler                  /*  63  USART3 interrupt */
                Set_Default_Handler  UART4_IRQHandler                   /*  64  UART4 interrupt */
                Set_Default_Handler  UART5_IRQHandler                   /*  65  UART5 interrupt */
                Set_Default_Handler  LPUART1_IRQHandler                 /*  66  LP UART1 interrupt */
                Set_Default_Handler  LPTIM1_IRQHandler                  /*  67  LP TIM1 interrupt */
                Set_Default_Handler  LPTIM2_IRQHandler                  /*  68  LP TIM2 interrupt */
                Set_Default_Handler  TIM15_IRQHandler                   /*  69  TIM15 interrupt */
                Set_Default_Handler  TIM16_IRQHandler                   /*  70  TIM16 interrupt */
                Set_Default_Handler  TIM17_IRQHandler                   /*  71  TIM17 interrupt */
                Set_Default_Handler  COMP_IRQHandler                    /*  72  COMP1&2 interrupt */
                Set_Default_Handler  USB_FS_IRQHandler                  /*  73  USB FS interrupt */
                Set_Default_Handler  CRS_IRQHandler                     /*  74  CRS interrupt */
                Set_Default_Handler  FMC_IRQHandler                     /*  75  FMC interrupt */
                Set_Default_Handler  OCTOSPI1_IRQHandler                /*  76  OctoSPI1 global interrupt */
                Set_Default_Handler  SDMMC1_IRQHandler                  /*  78  SDMMC1 interrupt */
                Set_Default_Handler  DMA2_Channel1_IRQHandler           /*  80  DMA2 Channel 1 interrupt */
                Set_Default_Handler  DMA2_Channel2_IRQHandler           /*  81  DMA2 Channel 2 interrupt */
                Set_Default_Handler  DMA2_Channel3_IRQHandler           /*  82  DMA2 Channel 3 interrupt */
                Set_Default_Handler  DMA2_Channel4_IRQHandler           /*  83  DMA2 Channel 4 interrupt */
                Set_Default_Handler  DMA2_Channel5_IRQHandler           /*  84  DMA2 Channel 5 interrupt */
                Set_Default_Handler  DMA2_Channel6_IRQHandler           /*  85  DMA2 Channel 6 interrupt */
                Set_Default_Handler  DMA2_Channel7_IRQHandler           /*  86  DMA2 Channel 7 interrupt */
                Set_Default_Handler  DMA2_Channel8_IRQHandler           /*  87  DMA2 Channel 8 interrupt */
                Set_Default_Handler  I2C3_EV_IRQHandler                 /*  88  I2C3 event interrupt */
                Set_Default_Handler  I2C3_ER_IRQHandler                 /*  89  I2C3 error interrupt */
                Set_Default_Handler  SAI1_IRQHandler                    /*  90  Serial Audio Interface 1 global interrupt */
                Set_Default_Handler  SAI2_IRQHandler                    /*  91  Serial Audio Interface 2 global interrupt */
                Set_Default_Handler  TSC_IRQHandler                     /*  92  Touch Sense Controller global interrupt */
                Set_Default_Handler  RNG_IRQHandler                     /*  94  RNG global interrupt */
                Set_Default_Handler  FPU_IRQHandler                     /*  95  FPU interrupt */
                Set_Default_Handler  HASH_IRQHandler                    /*  96  HASH interrupt */
                Set_Default_Handler  LPTIM3_IRQHandler                  /*  98  LP TIM3 interrupt */
                Set_Default_Handler  SPI3_IRQHandler                    /*  99  SPI3 interrupt */
                Set_Default_Handler  I2C4_ER_IRQHandler                 /*  100 I2C4 error interrupt */
                Set_Default_Handler  I2C4_EV_IRQHandler                 /*  101 I2C4 event interrupt */
                Set_Default_Handler  DFSDM1_FLT0_IRQHandler             /*  102 DFSDM1 Filter 0 global interrupt */
                Set_Default_Handler  DFSDM1_FLT1_IRQHandler             /*  103 DFSDM1 Filter 1 global interrupt */
                Set_Default_Handler  DFSDM1_FLT2_IRQHandler             /*  104 DFSDM1 Filter 2 global interrupt */
                Set_Default_Handler  DFSDM1_FLT3_IRQHandler             /*  105 DFSDM1 Filter 3 global interrupt */
                Set_Default_Handler  UCPD1_IRQHandler                   /*  106 UCPD1 interrupt */
                Set_Default_Handler  ICACHE_IRQHandler                  /*  107 ICACHE interrupt */

                .end
