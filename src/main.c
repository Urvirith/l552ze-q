// WORKING EXAMPLE FOR THE STM32L552ZE-Q NUCLEO
// THIS WILL ACTIVATE AND DEACTIVE THE USER LEDS ON THE BOARD,
// IT ALSO SHOWS HOW TO GET ACCESS TO REGISTERS, AND FORM VOLITILE POINTERS FOR USE LATER
// VOLITILE TELLS THE COMPILER TO NOT OPTIMIZE THE MEMORY LOCATIONS 

#include <stdint.h>

#define PORTA_PIN5          (uint32_t)5                                     /* USER GREEN LED on GPIO A Bus, Pin 5  */
#define LED_GRN             PORTA_PIN5                                      /* USER GREEN LED on GPIO A Bus, Pin 5  */
#define PORTB_PIN7          (uint32_t)7                                     /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define LED_BLU             PORTB_PIN7                                      /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define PORTA_PIN9          (uint32_t)9                                     /* USER RED LED on GPIO 9 Bus, Pin 9    */
#define LED_RED             PORTA_PIN9                                      /* USER RED LED on GPIO 9 Bus, Pin 9    */

/* GPIO Port A REGISTERS */
#define GPIOA_BASE          (uint32_t)0x42020000                            /* GPIO Port B base address */
#define GPIOA_MODER         *((volatile uint32_t *) (GPIOA_BASE  + 0x00))   /* Port B Mode register */
#define GPIOA_OTYPER        *((volatile uint32_t *) (GPIOA_BASE  + 0x04))   /* Port B Output Type Register */
#define GPIOA_BSRR          *((volatile uint32_t *) (GPIOA_BASE  + 0x18))   /* Output Data Set And Reset Register */

/* GPIO Port B REGISTERS */
#define GPIOB_BASE          (uint32_t)0x42020400                            /* GPIO Port B base address */
#define GPIOB_MODER         *((volatile uint32_t *) (GPIOB_BASE  + 0x00))   /* Port B Mode register */
#define GPIOB_OTYPER        *((volatile uint32_t *) (GPIOB_BASE  + 0x04))   /* Port B Output Type Register */
#define GPIOB_BSRR          *((volatile uint32_t *) (GPIOB_BASE  + 0x18))   /* Output Data Set And Reset Register */

#define PORTA_AHBEN         0
#define PORTB_AHBEN         1                                               /* GPIOB Enable is located on AHB2 Board Bit 1 */

/* Reset and Clock Control (RCC) */
#define RCC_BASE            (uint32_t)0x40021400                            /* RCC base address */
#define RCC_CR              *((volatile uint32_t *) (RCC_BASE + 0x00))      /* Clock Control Register */
#define RCC_AHB2ENR         *((volatile uint32_t *) (RCC_BASE + 0x4C))      /* AHB1 Enable Register */

/* User required */                                          
#define MASK_2_BIT         (uint32_t)0x00000003                             /* 2 bit mask, example 0011 = 0x03 */

/* Extern Keyword Allows To Be Call */
extern void _system_init() {
    RCC_AHB2ENR |= (1 << PORTA_AHBEN);
    RCC_AHB2ENR |= (1 << PORTB_AHBEN);
}

extern void _start() { 
    GPIOA_MODER &= (~(MASK_2_BIT << (LED_GRN * 2)));
    GPIOA_MODER |= (1 << (LED_GRN * 2));
    GPIOA_OTYPER &= (~(1 << LED_GRN));
    GPIOB_MODER &= (~(MASK_2_BIT << (LED_BLU * 2)));
    GPIOB_MODER |= (1 << (LED_BLU * 2));
    GPIOB_OTYPER &= (~(1 << LED_BLU));
    GPIOA_MODER &= (~(MASK_2_BIT << (LED_RED * 2)));
    GPIOA_MODER |= (1 << (LED_RED * 2));
    GPIOA_OTYPER &= (~(1 << LED_RED));

    int i = 0;
    while (1) {
        for (i = 0; i < 1200000; ++i) {
            if (i == 300000) {
                GPIOA_BSRR = (1 << LED_GRN);
            } else if (i == 0) {
                GPIOA_BSRR = (1 << (LED_GRN + 16));
            }

            if (i == 600000) {
                GPIOB_BSRR = (1 << LED_BLU);
            } else if (i == 0) {
                GPIOB_BSRR = (1 << (LED_BLU + 16));
            }

            if (i == 900000) {
                GPIOA_BSRR = (1 << LED_RED);
            } else if (i == 0) {
                GPIOA_BSRR = (1 << (LED_RED + 16));
            }
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}
