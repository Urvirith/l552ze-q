#ifndef L552ZE_H_
#define L552ZE_H_

/* Register Base */
/* Reset and Clock Control (RCC) */
#define RCC_BASE                    ((uint32_t)0X40021000)                  /* RCC base address */

/* General Purpose I/O */
#define GPIOA_BASE                  ((uint32_t)0x42020000)                  /* GPIO Port A base address */
#define GPIOB_BASE                  ((uint32_t)0x42020400)                  /* GPIO Port B base address */
#define GPIOC_BASE                  ((uint32_t)0x42020800)                  /* GPIO Port C base address */
#define GPIOD_BASE                  ((uint32_t)0x42020C00)                  /* GPIO Port D base address */
#define GPIOE_BASE                  ((uint32_t)0x42021000)                  /* GPIO Port E base address */
#define GPIOF_BASE                  ((uint32_t)0x42021400)                  /* GPIO Port F base address */
#define GPIOG_BASE                  ((uint32_t)0x42021800)                  /* GPIO Port G base address */
#define GPIOH_BASE                  ((uint32_t)0x42021C00)                  /* GPIO Port H base address */

/* Timers */
#define TIMER1_BASE                 ((uint32_t)0x40012C00)
#define TIMER2_BASE                 ((uint32_t)0x40000000)
#define TIMER3_BASE                 ((uint32_t)0x40000400)
#define TIMER4_BASE                 ((uint32_t)0x40000800)
#define TIMER5_BASE                 ((uint32_t)0x40000C00)
#define TIMER6_BASE                 ((uint32_t)0x40001000)
#define TIMER7_BASE                 ((uint32_t)0x40001400)
#define TIMER8_BASE                 ((uint32_t)0x40013400)
#define TIMER15_BASE                ((uint32_t)0x40014000)
#define TIMER16_BASE                ((uint32_t)0x40014400)
#define TIMER17_BASE                ((uint32_t)0x40014800)

/* USART (Universal Synchronous and Asynchronous Receiver Transmitter) */
#define USART1_BASE                 ((uint32_t)0x40013800)
#define USART2_BASE                 ((uint32_t)0x40004400)     
#define USART3_BASE                 ((uint32_t)0x40004800)
#define USART4_BASE                 ((uint32_t)0x40004C00)     
#define USART5_BASE                 ((uint32_t)0x40005000)

/* Inter-Integrated Circuit (I2C) */
#define I2C1_BASE                   ((uint32_t)0x40005400)
#define I2C2_BASE                   ((uint32_t)0x40005800)
#define I2C3_BASE                   ((uint32_t)0x40005C00)

/* Serial Peripheral Interface */
#define SPI1_BASE                   ((uint32_t)0x40013000)
#define SPI2_BASE                   ((uint32_t)0x40003800)
#define SPI3_BASE                   ((uint32_t)0x40003C00)

/* Serial Peripheral Interface */
#define CAN_BASE                    ((uint32_t)0x4000A400)
      
/* Reset and Clock Control (RCC) */
#define RCC_GPIOA_AHB2EN            BIT_0                                   /* GPIOA Enable is located on AHB2 Board Bit 0 */
#define RCC_GPIOB_AHB2EN            BIT_1                                   /* GPIOB Enable is located on AHB2 Board Bit 1 */
#define RCC_GPIOC_AHB2EN            BIT_2                                   /* GPIOC Enable is located on AHB2 Board Bit 2 */

/* General Purpose I/O */
/* NUCLEO BOARD PIN OUT SPECIFICS - NUCLEO - L552ZE-Q */
#define GPIOC_PIN7                  (uint32_t)7                             /* USER GREEN LED on GPIO C Bus, Pin 7  */
#define LED_GRN_PIN                 GPIOC_PIN7                              /* USER GREEN LED on GPIO C Bus, Pin 7  */
#define LED_GRN                     BIT_7                                   /* USER GREEN LED on GPIO C Bus, Pin 7  */
#define GPIOB_PIN7                  (uint32_t)7                             /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define LED_BLU_PIN                 GPIOB_PIN7                              /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define LED_BLU                     BIT_7                                   /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define GPIOA_PIN9                  (uint32_t)9                             /* USER RED LED on GPIO A Bus, Pin 9    */
#define LED_RED_PIN                 GPIOA_PIN9                              /* USER RED LED on GPIO A Bus, Pin 9    */
#define LED_RED                     BIT_9                                   /* USER RED LED on GPIO A Bus, Pin 9    */

/* Timer */
#define RCC_TIMER2_APB1R1EN         BIT_0

/* USART (Universal Synchronous and Asynchronous Receiver Transmitter) */
#define RCC_USART2_APB1R1EN         BIT_17
#define GPIOA_PIN2                  (uint32_t)2                             /* GPIO Bus D Pin 2 TX    */
#define GPIOA_PIN3                  (uint32_t)3                             /* GPIO Bus D Pin 3 RX    */
#define USART2_TX                   GPIOA_PIN2
#define USART2_RX                   GPIOA_PIN3

/* GPIO SETUP */
#define USART_MODE                  Gpio_Alternate
#define USART_OTYPE                 Gpio_Push_Pull
#define USART_AF                    AF7

/* I2C 1*/
//#define I2C1_RCC_APB1R1_ENABLE:     u32 = common::BIT_21;
//#define PORTB_PIN6:                 u32 = 6;    //D5    SCL
//#define PORTB_PIN7:                 u32 = 7;    //D4    SDA
//#define I2C1_SCL:                   u32 = PORTB_PIN6;
//#define I2C1_SDA:                   u32 = PORTB_PIN7;

/* GPIO SETUP */
//#define CAN_MODE:                   gpio::Mode = gpio::Mode::Alt;
//#define CAN_OTYPE:                  gpio::OType = gpio::OType::PushPull;
//#define CAN_AF:                     gpio::AltFunc = gpio::AltFunc::Af9;
//#define CAN_OSPEED:                 gpio::OSpeed = gpio::OSpeed::High;
//#define CAN_PUPD:                   gpio::Pupd = gpio::Pupd::Pu;

/* SPI 1*/
/* RCC */
//#define SPI1_RCC_APB2R_ENABLE:      u32 = common::BIT_12;

/* SPI 2*/
/* RCC */
// #define SPI2_RCC_APB1R1_ENABLE:  u32 = common::BIT_14; // NOT AVAILABLE 432KC

/* SPI 3*/
/* RCC */
//#define SPI3_RCC_APB1R1_ENABLE:     u32 = common::BIT_15;

#endif /* L552ZE_H_ */
