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

/*
    PWM mode
    Pulse width modulation mode permits to generate a signal with a frequency determined by
    the value of the TIMx_ARR register and a duty cycle determined by the value of the
    TIMx_CCRx register.
    The PWM mode can be selected independently on each channel (one PWM per OCx
    output) by writing 110 (PWM mode 1) or ‘111 (PWM mode 2) in the OCxM bits in the
    TIMx_CCMRx register. The corresponding preload register must be enabled by setting the
    OCxPE bit in the TIMx_CCMRx register, and eventually the auto-reload preload register (in
    upcounting or center-aligned modes) by setting the ARPE bit in the TIMx_CR1 register.
    As the preload registers are transferred to the shadow registers only when an update event
    occurs, before starting the counter, all registers must be initialized by setting the UG bit in
    the TIMx_EGR register.
    OCx polarity is software programmable using the CCxP bit in the TIMx_CCER register. It
    can be programmed as active high or active low. OCx output is enabled by the CCxE bit in
    the TIMx_CCER register. Refer to the TIMx_CCERx register description for more details.
    In PWM mode (1 or 2), TIMx_CNT and TIMx_CCRx are always compared to determine
    whether TIMx_CCRx ≤ TIMx_CNT or TIMx_CNT ≤ TIMx_CCRx (depending on the direction
    of the counter). However, to comply with the OCREF_CLR functionality (OCREF can be
    cleared by an external event through the ETR signal until the next PWM period), the
    OCREF signal is asserted only:
        • When the result of the comparison or
        • When the output compare mode (OCxM bits in TIMx_CCMRx register) switches from
          the “frozen” configuration (no comparison, OCxM=‘000) to one of the PWM modes
          (OCxM=‘110 or ‘111).
    This forces the PWM by software while the timer is running.
*/