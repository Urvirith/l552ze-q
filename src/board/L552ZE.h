#ifndef L552ZE_H_
#define L552ZE_H_

/* Register Base */
/* Reset and Clock Control (RCC) */
#define RCC_BASE:                   ((uint32_t)0X40021000)

/* General Purpose I/O */
#define GPIOA_BASE:                 ((uint32_t)0x42020000) 
#define GPIOB_BASE:                 ((uint32_t)0x42020400)
#define GPIOC_BASE:                 ((uint32_t)0x42020800)
#define GPIOD_BASE:                 ((uint32_t)0x42020C00) 
#define GPIOE_BASE:                 ((uint32_t)0x42021000)
#define GPIOF_BASE:                 ((uint32_t)0x42021400)
#define GPIOG_BASE:                 ((uint32_t)0x42021800)
#define GPIOH_BASE:                 ((uint32_t)0x42021C00)

/* Timers */
#define TIMER1_BASE:                ((uint32_t)0x40012C00)
#define TIMER2_BASE:                ((uint32_t)0x40000000)
#define TIMER3_BASE:                ((uint32_t)0x40000400)
#define TIMER4_BASE:                ((uint32_t)0x40000800)
#define TIMER5_BASE:                ((uint32_t)0x40000C00)
#define TIMER6_BASE:                ((uint32_t)0x40001000)
#define TIMER7_BASE:                ((uint32_t)0x40001400)
#define TIMER8_BASE:                ((uint32_t)0x40013400)
#define TIMER15_BASE:               ((uint32_t)0x40014000)
#define TIMER16_BASE:               ((uint32_t)0x40014400)
#define TIMER17_BASE:               ((uint32_t)0x40014800)

/* USART (Universal Synchronous and Asynchronous Receiver Transmitter) */
#define USART1_BASE:                ((uint32_t)0x40013800)
#define USART2_BASE:                ((uint32_t)0x40004400)     
#define USART3_BASE:                ((uint32_t)0x40004800)
#define USART4_BASE:                ((uint32_t)0x40004C00)     
#define USART5_BASE:                ((uint32_t)0x40005000)

/* Inter-Integrated Circuit (I2C) */
#define I2C1_BASE:                  ((uint32_t)0x40005400)
#define I2C2_BASE:                  ((uint32_t)0x40005800)
#define I2C3_BASE:                  ((uint32_t)0x40005C00)

/* Serial Peripheral Interface */
#define SPI1_BASE:                  ((uint32_t)0x40013000)
#define SPI2_BASE:                  ((uint32_t)0x40003800)
#define SPI3_BASE:                  ((uint32_t)0x40003C00)

/* Serial Peripheral Interface */
#define CAN_BASE:                   ((uint32_t)0x4000A400)
      
/* Reset and Clock Control (RCC) */
#define GPIOA_RCC_AHB2_ENABLE:      u32 = common::BIT_0;
#define GPIOB_RCC_AHB2_ENABLE:      u32 = common::BIT_1;

/* General Purpose I/O */
#define USER_LED:                   u32 = 3;
#define USER_LED_BIT:               u32 = common::BIT_3;

/* GPIO SETUP */
#define USER_LED_MODE:              gpio::Mode = gpio::Mode::Out;
#define USER_LED_OTYPE:             gpio::OType = gpio::OType::PushPull;
#define USER_LED_AF:                gpio::AltFunc = gpio::AltFunc::Af0;

/* Timer */
#define TIMER2_RCC_APB1R1_ENABLE:   u32 = common::BIT_0;

/* USART (Universal Synchronous and Asynchronous Receiver Transmitter) */
#define USART2_RCC_APB1R1_ENABLE:   u32 = common::BIT_17;
#define PORTA_PIN2:                 u32 = 2;    //A7    TX
#define PORTA_PIN3:                 u32 = 3;    //A2    RX
#define USART2_TX:                  u32 = PORTA_PIN2;
#define USART2_RX:                  u32 = PORTA_PIN3;

/* GPIO SETUP */
#define USART_MODE:                 gpio::Mode = gpio::Mode::Alt;
#define USART_OTYPE:                gpio::OType = gpio::OType::PushPull;
#define USART_AF:                   gpio::AltFunc = gpio::AltFunc::Af7;

/* I2C 1*/
#define I2C1_RCC_APB1R1_ENABLE:     u32 = common::BIT_21;
#define PORTB_PIN6:                 u32 = 6;    //D5    SCL
#define PORTB_PIN7:                 u32 = 7;    //D4    SDA
#define I2C1_SCL:                   u32 = PORTB_PIN6;
#define I2C1_SDA:                   u32 = PORTB_PIN7;

/* CAN */
#define CAN_RCC_APB1R1_ENABLE:      u32 = common::BIT_25;
#define PORTA_PIN11:                u32 = 11;   //D10   RX
#define PORTA_PIN12:                u32 = 12;   //D2    TX
#define CAN_RX:                     u32 = PORTA_PIN11;
#define CAN_TX:                     u32 = PORTA_PIN12;

/* GPIO SETUP */
#define CAN_MODE:                   gpio::Mode = gpio::Mode::Alt;
#define CAN_OTYPE:                  gpio::OType = gpio::OType::PushPull;
#define CAN_AF:                     gpio::AltFunc = gpio::AltFunc::Af9;
#define CAN_OSPEED:                 gpio::OSpeed = gpio::OSpeed::High;
#define CAN_PUPD:                   gpio::Pupd = gpio::Pupd::Pu;

/* SPI 1*/
/* RCC */
#define SPI1_RCC_APB2R_ENABLE:      u32 = common::BIT_12;

/* SPI 2*/
/* RCC */
// #define SPI2_RCC_APB1R1_ENABLE:  u32 = common::BIT_14; // NOT AVAILABLE 432KC

/* SPI 3*/
/* RCC */
#define SPI3_RCC_APB1R1_ENABLE:     u32 = common::BIT_15;

#endif /* L552ZE_H_ */
