// Main Call To The The Processor

#include "hal/common.h"
#include "board/L552ZE.h"
#include "hal/rcc.h"
#include "hal/gpio.h"
#include "hal/timer.h"
#include "hal/usart.h"
#include "hal/spi.h"
#include "hal/nvic.h"
#include "routine/axis.h"
#include "main.h"

struct motor_control motorcontoller = {
    .MOTOR1 = {.DIRECTION = Reverse, .STATE = BootUp, .COUNT = 0},
    .MOTOR2 = {.DIRECTION = Reverse, .STATE = BootUp, .COUNT = 0},
    .MOTOR3 = {.DIRECTION = Reverse, .STATE = BootUp, .COUNT = 0},
    .MOTOR4 = {.DIRECTION = Reverse, .STATE = BootUp, .COUNT = 0},
    .STATE = BootUp,
    .COUNT = 0,
    .TOGGLE = 0
};

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
    rcc_write_apb1_enr1(RCC, RCC_USART3_APB1R1EN);
    rcc_write_apb2_enr(RCC, RCC_SPI1_APB2REN);
}

extern void _start() { 
    /* LED Setup */
    gpio_type(GPIOA, LED_RED_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOB, LED_BLU_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOC, LED_GRN_PIN, Gpio_Output, Gpio_Push_Pull, 0);
    /* Timer Setup */
    /* TIMER 2 */
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 1000, 16000, 5000);
    timer_start(TIMER2);
    /* TIMER 3 */
    gpio_type(GPIOE, TIM3_PWM1_PIN, Gpio_Alternate, Gpio_Push_Pull, TIM3_PWM1_AF);
    gpio_type(GPIOE, TIM3_PWM2_PIN, Gpio_Alternate, Gpio_Push_Pull, TIM3_PWM2_AF);
    gpio_type(GPIOE, TIM3_PWM3_PIN, Gpio_Alternate, Gpio_Push_Pull, TIM3_PWM3_AF);
    timer_open(TIMER3, Timer_Ons, Timer_Upcount);
    timer_set_time(TIMER3, 500, 16, 16);
    timer_set_pwm_ccr1(TIMER3, 0);
    timer_set_pwm_ch1(TIMER3);
    timer_set_pwm_ccr2(TIMER3, 0);
    timer_set_pwm_ch2(TIMER3);
    timer_set_pwm_ccr3(TIMER3, 0);
    timer_set_pwm_ch3(TIMER3);
    timer_set_interrupt(TIMER3);
    delay(TIMER3, 500);
    nvic_enable_interrupt(NVIC, TIM3_IRQ);

    /* Usart Setup */
    gpio_type(GPIOD, USART3_TX, USART_MODE, USART_OTYPE, USART_AF);
    gpio_type(GPIOD, USART3_RX, USART_MODE, USART_OTYPE, USART_AF);
    usart_open(USART3, USART_8_Bits, USART_1_StopBit, USART_921600_BAUD, 16000, USART_Oversample_16);

    /* SPI Setup */
    gpio_type(GPIOB, SPI1_MISO, SPI_MODE, SPI_OTYPE, SPI_AF);
    gpio_type(GPIOB, SPI1_MOSI, SPI_MODE, SPI_OTYPE, SPI_AF);
    gpio_type(GPIOB, SPI1_SCK, SPI_MODE, SPI_OTYPE, SPI_AF);
    gpio_type(GPIOA, SPI1_NSS, SPI_MODE, SPI_OTYPE, SPI_AF);
    gpio_type(GPIOA, SPI1_SS, Gpio_Input, Gpio_Push_Pull, 0);
    spi_open(SPI1, SPI_Div_16, SPI_RisingEdgeClockLow, SPI_Msb, SPI_Bits_8);

    /* PIN SETUP */
    gpio_type(GPIOF, DIR_Z_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOF, DIR_Y_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOF, DIR_X_AXIS, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_type(GPIOE, AXIS_ENABLE, Gpio_Output, Gpio_Push_Pull, 0);
    gpio_pupd(GPIOF, DIR_Z_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOF, DIR_Y_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOF, DIR_X_AXIS, Gpio_NoPuPd);
    gpio_pupd(GPIOE, AXIS_ENABLE, Gpio_NoPuPd);
    
    gpio_clr_pin(GPIOE, AXIS_ENABLE_PIN);
    

    uint8_t buf[8] = {0x03, 0x01, 0x02, 0x03 ,0x04, 0x05, 0x06, 0x0D};
    uint8_t spi_obuf[4] = {0x03, 0x06, 0x04, 0x0D};
    uint8_t spi_ibuf[4] = {0x00, 0x00, 0x00, 0x00};

    bool flip = 0;

    motorcontoller.MOTOR1.COUNT = 200;
    motorcontoller.MOTOR1.STATE = PreOperational;
    motorcontoller.MOTOR2.COUNT = 150;
    motorcontoller.MOTOR2.STATE = PreOperational;
    motorcontoller.MOTOR3.COUNT = 100;
    motorcontoller.MOTOR3.STATE = PreOperational;
    motorcontoller.STATE = Stopped;

    uint8_t i = 0;
    uint8_t j = 0;

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

            if (motorcontoller.STATE == Stopped) {
                if (j == 0) {
                    motorcontoller.COUNT = 0;
                    gpio_set_pin(GPIOF, DIR_Z_AXIS_PIN);
                    gpio_set_pin(GPIOF, DIR_Y_AXIS_PIN);
                    gpio_set_pin(GPIOF, DIR_X_AXIS_PIN);
                    timer_set_time(TIMER3, 2000, 16, 16);
                    timer_set_pwm_ccr1(TIMER3, 1000);
                    timer_set_pwm_ccr2(TIMER3, 1000);
                    timer_set_pwm_ccr3(TIMER3, 1000);
                    motorcontoller.STATE = Operational;
                    timer_start(TIMER3);
                    j = 1;
                } else if (j == 1) {
                    gpio_set_pin(GPIOF, DIR_Z_AXIS_PIN);
                    gpio_set_pin(GPIOF, DIR_Y_AXIS_PIN);
                    gpio_clr_pin(GPIOF, DIR_X_AXIS_PIN);
                    motorcontoller.COUNT = 0;
                    timer_set_time(TIMER3, 1800, 16, 16);
                    timer_set_pwm_ccr1(TIMER3, 900);
                    timer_set_pwm_ccr2(TIMER3, 900);
                    timer_set_pwm_ccr3(TIMER3, 900);
                    motorcontoller.STATE = Operational;
                    timer_start(TIMER3);
                    j = 2;
                } else if (j == 2) {
                    gpio_set_pin(GPIOF, DIR_Z_AXIS_PIN);
                    gpio_clr_pin(GPIOF, DIR_Y_AXIS_PIN);
                    gpio_set_pin(GPIOF, DIR_X_AXIS_PIN);
                    motorcontoller.COUNT = 0;
                    timer_set_time(TIMER3, 1600, 16, 16);
                    timer_set_pwm_ccr1(TIMER3, 800);
                    timer_set_pwm_ccr2(TIMER3, 800);
                    timer_set_pwm_ccr3(TIMER3, 800);
                    motorcontoller.STATE = Operational;
                    timer_start(TIMER3);
                    j = 3;
                } else {
                    gpio_clr_pin(GPIOF, DIR_Z_AXIS_PIN);
                    gpio_set_pin(GPIOF, DIR_Y_AXIS_PIN);
                    gpio_set_pin(GPIOF, DIR_X_AXIS_PIN);
                    motorcontoller.COUNT = 0;
                    timer_set_time(TIMER3, 1500, 16, 16);
                    timer_set_pwm_ccr1(TIMER3, 750);
                    timer_set_pwm_ccr2(TIMER3, 750);
                    timer_set_pwm_ccr3(TIMER3, 750);
                    motorcontoller.STATE = Operational;
                    timer_start(TIMER3);
                    j = 0;
                }
            }
           
            buf[1] = i;

            spi_enable(SPI1);
            spi_write(SPI1, spi_obuf, 4);
            spi_disable(SPI1);
            spi_read(SPI1, spi_ibuf, 4);

            spi_obuf[1] = i;

            usart_write(USART3, spi_ibuf, 4);
            usart_write(USART3, buf, 8);

            timer_clr_flag(TIMER2);
            i++;
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}

void delay(TIMER_TypeDef * ptr, uint32_t time_us) {
    timer_set_time(ptr, time_us, 16, 16);
    timer_start(ptr);
    timer_clr_flag(ptr);

    while (!timer_get_flag(ptr)) {
        // SPIN HERE FOR DELAY TIMER
    }

    timer_stop(ptr);
    timer_clr_count(ptr);
    timer_clr_flag(ptr);
}

extern void TIM3_IRQHandler() {
    timer_clr_flag(TIMER3); /* CLEAR THE INTERUPT FIRST */
    
    motorcontoller.COUNT++;

    if (motorcontoller.TOGGLE == true) { // TOGGLE LED FOR HEARTBEAT
        gpio_clr_pin(GPIOA, LED_RED);
        motorcontoller.TOGGLE = false;
    } else {
        gpio_set_pin(GPIOA, LED_RED);
        motorcontoller.TOGGLE = true;
    }

    if (motorcontoller.COUNT < motorcontoller.MOTOR1.COUNT) {
        motorcontoller.MOTOR1.STATE = Operational;
    } else {
        timer_set_pwm_ccr1(TIMER3, 0);
        motorcontoller.MOTOR1.STATE = Stopped;
    }

    if (motorcontoller.COUNT < motorcontoller.MOTOR2.COUNT) {
        motorcontoller.MOTOR2.STATE = Operational;
    } else {
        timer_set_pwm_ccr2(TIMER3, 0);
        motorcontoller.MOTOR2.STATE = Stopped;
    }

    if (motorcontoller.COUNT < motorcontoller.MOTOR3.COUNT) {
        motorcontoller.MOTOR3.STATE = Operational;
    } else {
        timer_set_pwm_ccr3(TIMER3, 0);
        motorcontoller.MOTOR3.STATE = Stopped;
    }

    if ((motorcontoller.MOTOR1.STATE == Stopped) && (motorcontoller.MOTOR2.STATE == Stopped) && (motorcontoller.MOTOR3.STATE == Stopped)) {
        motorcontoller.STATE = Stopped;
    }

    if (motorcontoller.STATE == Stopped) {
        gpio_clr_pin(GPIOA, LED_RED);
        motorcontoller.TOGGLE = false;
    } else {
        timer_start(TIMER3);
    }
}