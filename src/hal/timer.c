#include "common.h"
#include "timer.h"

void timer_open(TIMER_TypeDef *ptr, uint32_t ons, uint32_t dir) {
    clr_ptr_vol_bit_u32(&ptr->CR1, UDIS_BIT);
    clr_ptr_vol_bit_u32(&ptr->CR1, URS_BIT);

    if (ons == Timer_Ons) {
        set_ptr_vol_bit_u32(&ptr->CR1, OPM_BIT);
    } else {
        clr_ptr_vol_bit_u32(&ptr->CR1, OPM_BIT);
    }

    if (dir == Timer_Down) {
        set_ptr_vol_bit_u32(&ptr->CR1, DIR_BIT);
    } else {
        clr_ptr_vol_bit_u32(&ptr->CR1, DIR_BIT);
    }

    set_ptr_vol_u32(&ptr->CR1, CMS_OFFSET, CMS_MASK, 0);
    clr_ptr_vol_bit_u32(&ptr->CR1, ARPE_BIT);
    set_ptr_vol_u32(&ptr->CR1, CKD_OFFSET, CKD_MASK, 0);
    clr_ptr_vol_bit_u32(&ptr->CR1, UIFREMAP_BIT);
}

bool timer_get_flag(TIMER_TypeDef *ptr) {
    return get_ptr_vol_bit_u32(&ptr->SR, UPDATE_BIT);
}

void timer_clr_flag(TIMER_TypeDef *ptr) {
    clr_ptr_vol_bit_u32(&ptr->SR, UPDATE_BIT);
}

uint32_t timer_read_count(TIMER_TypeDef *ptr) {
    return get_ptr_vol_raw_u32(&ptr->CNT);
}

void timer_clr_count(TIMER_TypeDef *ptr) {
    set_ptr_vol_raw_u32(&ptr->CNT, CLEAR_CNT);
}

void timer_start(TIMER_TypeDef *ptr) {
    set_ptr_vol_bit_u32(&ptr->CR1, EN_BIT);
}

void timer_stop(TIMER_TypeDef *ptr) {
    clr_ptr_vol_bit_u32(&ptr->CR1, EN_BIT);
}

void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale) {
    uint32_t value = 0;

    if (prescale == 0) {
        value = time * clock_speed;
    } else {
        value = (time * clock_speed) / prescale;
    }

    set_ptr_vol_raw_u32(&ptr->PSC, prescale);
    set_ptr_vol_raw_u32(&ptr->ARR, value);
}

