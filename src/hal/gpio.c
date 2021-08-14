#include "common.h"
#include "gpio.h"

bool gpio_get_pin(GPIO_TypeDef *ptr, uint32_t value){
    return get_ptr_vol_bit_u32(&ptr->IDR, value);
}

void gpio_set_pin(GPIO_TypeDef *ptr, uint32_t value){
    set_ptr_vol_bit_u32(&ptr->ODR, value);
}

void gpio_clr_pin(GPIO_TypeDef *ptr, uint32_t value){
    clr_ptr_vol_bit_u32(&ptr->ODR, value);
}

void gpio_set_lock(GPIO_TypeDef *ptr, uint32_t value){
    set_ptr_vol_bit_u32(&ptr->LCKR, value);
}

void gpio_clr_lock(GPIO_TypeDef *ptr, uint32_t value){
    clr_ptr_vol_bit_u32(&ptr->LCKR, value);
}

void gpio_type(GPIO_TypeDef *ptr, uint32_t bit, GPIO_Mode mode, GPIO_OType otype, GPIO_AltFunction alt_func) {
    set_ptr_vol_u32(&ptr->MODER, bit * MODER_OFFSET, MODER_MASK, mode);
    switch (otype) {
        case Gpio_Open_Drain:
            set_ptr_vol_bit_u32(&ptr->OTYPER, (1 << bit));
            break;
        case Gpio_Push_Pull:
            clr_ptr_vol_bit_u32(&ptr->OTYPER, (1 << bit));
            break;
    }

    if (mode == Gpio_Alternate) {
        if (bit <= 7) {
            set_ptr_vol_u32(&ptr->AFRL, bit * AF_OFFSET, AF_MASK, alt_func);
        } else {
            set_ptr_vol_u32(&ptr->AFRH, (bit - 8) * AF_OFFSET, AF_MASK, alt_func);
        }
    }
}

void gpio_speed(GPIO_TypeDef *ptr, uint32_t bit, uint32_t speed) {
    set_ptr_vol_u32(&ptr->OSPEEDR, bit * OSPEED_OFFSET, OSPEED_MASK, speed);
}

void gpio_pupd(GPIO_TypeDef *ptr, uint32_t bit, uint32_t pupd) {
    set_ptr_vol_u32(&ptr->PUPDR, bit * PUPD_OFFSET, PUPD_MASK, pupd);
}