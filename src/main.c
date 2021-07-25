// Main Call To The The Processor

#include "hal/common.h"
#include "board/L552ZE.h"
#include "hal/rcc.h"
#include "hal/gpio.h"
#include "hal/timer.h"
#include "hal/usart.h"
#include "main.h"

/* Extern Keyword Allows To Be Call */
extern void _system_init() {
    rcc_write_msi_range(RCC, Clk16MHz);
    rcc_write_ahb2_enr(RCC, RCC_GPIOA_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOB_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOC_AHB2EN);
    rcc_write_apb1_enr1(RCC, RCC_TIMER2_APB1R1EN);
    rcc_write_apb1_enr1(RCC, RCC_USART2_APB1R1EN);
}

extern void _start() { 
    /* LED Setup */
    gpio_type(GPIOA, LED_RED_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOB, LED_BLU_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOC, LED_GRN_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    /* Timer Setup */
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 1000, 16000, 400);
    timer_start(TIMER2);
    /* Usart Setup */
    gpio_type(GPIOA, USART2_TX, USART_MODE, USART_OTYPE, USART_AF);
    gpio_type(GPIOA, USART2_RX, USART_MODE, USART_OTYPE, USART_AF);
    usart_open(USART2, USART_8_Bits, USART_1_StopBit, USART_921600_BAUD, 16000, USART_Oversample_16);

    uint8_t buf[8] = {0x03, 0x01, 0x02, 0x03 ,0x04, 0x05, 0x06, 0x0D};

    uint8_t i = 0;
    while (1) {
        if (timer_get_flag(TIMER2)) {
            if (i == 1) {
                gpio_set_pin(GPIOA, LED_RED);
            } else if (i == 2) {
                gpio_set_pin(GPIOB, LED_BLU);
            } else if (i == 3) {
                gpio_set_pin(GPIOC, LED_GRN);
            } else if (i > 3) {
                gpio_clr_pin(GPIOA, LED_RED);
                gpio_clr_pin(GPIOB, LED_BLU);
                gpio_clr_pin(GPIOC, LED_GRN);
                i = 0;
            }

            buf[1] = i;
            usart_write(USART2, buf, 8);

            timer_clr_flag(TIMER2);

            i++;
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}
