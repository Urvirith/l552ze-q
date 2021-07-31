// Main Call To The The Processor

#include "hal/common.h"
#include "board/L552ZE.h"
#include "hal/rcc.h"
#include "hal/gpio.h"
#include "hal/timer.h"
#include "hal/usart.h"
#include "main.h"

volatile bool toggle = 0;
#define NVIC_EN     *((volatile uint32_t *) (NVIC_BASE + 0x04))      /* Clock Control Register */
#define TIM4_NVIC = (uint32_t)47;
#define TIM4_NVIC_OFFSET = 47 - TIM4_NVIC; 

/* Extern Keyword Allows To Be Call */
extern void _system_init() {
    rcc_write_msi_range(RCC, Clk16MHz);
    rcc_write_ahb2_enr(RCC, RCC_GPIOA_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOB_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOC_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOD_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOE_AHB2EN);
    rcc_write_ahb2_enr(RCC, RCC_GPIOF_AHB2EN);
    rcc_write_apb1_enr1(RCC, RCC_TIMER2_APB1R1EN);
    rcc_write_apb1_enr1(RCC, RCC_TIMER3_APB1R1EN);
    rcc_write_apb1_enr1(RCC, RCC_TIMER4_APB1R1EN);
    rcc_write_apb1_enr1(RCC, RCC_USART3_APB1R1EN);
}

extern void _start() { 
    /* LED Setup */
    gpio_type(GPIOA, LED_RED_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOB, LED_BLU_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOC, LED_GRN_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    /* Timer Setup */
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 1000, 16000, 5000);
    timer_open(TIMER3, Timer_Ons, Timer_Upcount);
    timer_set_time(TIMER3, 5, 16, 0);
    timer_open(TIMER4, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER4, 5000, 16000, 5000);
    timer_set_interrupt(TIMER4);
    timer_start(TIMER2);
    timer_start(TIMER4);
    NVIC_EN = (1 << 15);
    /* Usart Setup */
    gpio_type(GPIOD, USART3_TX, USART_MODE, USART_OTYPE, USART_AF);
    gpio_type(GPIOD, USART3_RX, USART_MODE, USART_OTYPE, USART_AF);
    usart_open(USART3, USART_8_Bits, USART_1_StopBit, USART_921600_BAUD, 16000, USART_Oversample_16);
    /* PIN SETUP */
    gpio_type(GPIOF, DIR_Z_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOE, DIR_Y_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOE, DIR_X_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOF, STEP_Z_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOE, STEP_Y_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOF, STEP_X_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOF, AXIS_ENABLE, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_pupd(GPIOF, DIR_Z_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOE, DIR_Y_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOE, DIR_X_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOF, STEP_Z_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOE, STEP_Y_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOF, STEP_X_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOF, AXIS_ENABLE, Gpio_NoPuPd);

    gpio_clr_pin(GPIOF, AXIS_ENABLE_PIN);

    uint8_t buf[8] = {0x03, 0x01, 0x02, 0x03 ,0x04, 0x05, 0x06, 0x0D};
    bool flip = 0;

    uint8_t i = 0;
    while (1) {
        if (timer_get_flag(TIMER2)) {
            if (i == 1) {
                gpio_set_pin(GPIOB, LED_BLU);
            } else if (i == 2) {
                gpio_set_pin(GPIOC, LED_GRN);
            } else if (i > 2) {
                gpio_clr_pin(GPIOB, LED_BLU);
                gpio_clr_pin(GPIOC, LED_GRN);
                i = 0;
            }

            /*
            if (flip == 0) {
                loop(0, GPIOE, DIR_X_AXIS_PIN, GPIOF, STEP_X_AXIS_PIN, 200);
                flip = 1;
            } else {
                loop(1, GPIOE, DIR_X_AXIS_PIN, GPIOF, STEP_X_AXIS_PIN, 200);
                flip = 0;
            }
            */
           
            buf[1] = i;
            usart_write(USART3, buf, 8);

            timer_clr_flag(TIMER2);
            i++;
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}

void loop(bool dir, GPIO_TypeDef * dir_ptr, uint32_t pin_dir, GPIO_TypeDef * pulse_ptr, uint32_t pin_pulse, uint32_t steps) { 
    if (dir == MotorForward) {
        gpio_set_pin(dir_ptr, pin_dir);
    } else {
        gpio_clr_pin(dir_ptr, pin_dir);
    }

    delay(TIMER3, 50);
    //for (volatile int j = 0; j < 200; j++) {};

    for (volatile int i = 0; i < steps; i++) {
        gpio_set_pin(pulse_ptr, pin_pulse);
        //for (volatile int j = 0; j < 1000; j++) {};
        delay(TIMER3, 1000);
        gpio_clr_pin(pulse_ptr, pin_pulse); 
        //for (volatile int j = 0; j < 1000; j++) {};
        delay(TIMER3, 1000);
    }
}

void delay(TIMER_TypeDef * ptr, uint32_t time_us) {
    timer_set_time(ptr, time_us, 16, 0);
    timer_start(ptr);
    timer_clr_flag(ptr);

    while (!timer_get_flag(ptr)) {
        // SPIN HERE FOR DELAY TIMER
    }

    timer_stop(ptr);
    timer_clr_count(ptr);
    timer_clr_flag(ptr);
}

extern void TIM4_IRQHandler() {
    /* CLEAR THE INTERUPT FIRST */
    timer_clr_flag(TIMER4);
    if (toggle == true) {
        gpio_clr_pin(GPIOA, LED_RED);
        toggle = false;
    } else {
        gpio_set_pin(GPIOA, LED_RED);
        toggle = true;
    }
}