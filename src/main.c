// Main Call To The The Processor

#include "hal/common.h"
#include "board/L552ZE.h"
#include "hal/rcc.h"
#include "hal/gpio.h"
#include "main.h"

/* Extern Keyword Allows To Be Call */
extern void _system_init() {
    rcc_write_ahb2_enr(RCC, RCC_PORTA_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_PORTB_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_PORTC_AHB2EN);
}

extern void _start() { 
    gpio_type(GPIOA, LED_RED_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOB, LED_BLU_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOC, LED_GRN_PIN, Gpio_Output, Gpio_Push_Pull, 0);

    int i = 0;
    while (1) {
        for (i = 0; i < 1200000; i++) {
            if (i == 300000) {
                gpio_set_pin(GPIOA, LED_RED);
            } else if (i == 600000) {
                gpio_set_pin(GPIOB, LED_BLU);
            } else if (i == 900000) {
                gpio_set_pin(GPIOC, LED_GRN);
            } else if (i == 0) {
                gpio_clr_pin(GPIOA, LED_RED);
                gpio_clr_pin(GPIOB, LED_BLU);
                gpio_clr_pin(GPIOC, LED_GRN);
            }
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}
