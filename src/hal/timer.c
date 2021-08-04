#include "common.h"
#include "timer.h"

void timer_open(TIMER_TypeDef *ptr, TIMER_Type ons, TIMER_Direction dir) {
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

void timer_set_interrupt(TIMER_TypeDef *ptr) {
    set_ptr_vol_bit_u32(&ptr->DIER, UPDATE_BIT);
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

/* Set Prescaler, And Auto Reload Register */
/* Prescaler = PSC - 1, due to register being PSC + 1, ARR - 1 due to loading and ticking over to 0 */
void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale) {
    uint32_t value = 0;
    uint32_t psc = 0;

    if (prescale == 0) {
        value = (time * clock_speed) - 1;
    } else {
        value = ((time * clock_speed) / prescale) - 1;
        psc = prescale - 1;
    }

    set_ptr_vol_raw_u32(&ptr->PSC, psc);
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

/* Setup For PWM on CH 1 */
void timer_set_pwm_ccr1(TIMER_TypeDef *ptr, uint32_t cnt) {
    set_ptr_vol_raw_u32(&ptr->CCR1, cnt);
}

/* Setup For PWM on CH 2 */
void timer_set_pwm_ccr2(TIMER_TypeDef *ptr, uint32_t cnt) {
    set_ptr_vol_raw_u32(&ptr->CCR2, cnt);
}

/* Setup For PWM on CH 3 */
void timer_set_pwm_ccr3(TIMER_TypeDef *ptr, uint32_t cnt) {
    set_ptr_vol_raw_u32(&ptr->CCR3, cnt);
}

/* Setup For PWM on CH 4 */
void timer_set_pwm_ccr4(TIMER_TypeDef *ptr, uint32_t cnt) {
    set_ptr_vol_raw_u32(&ptr->CCR4, cnt);
}

/* Default Set Up For PWM */
void timer_set_pwm_ch1(TIMER_TypeDef *ptr) {
    set_ptr_vol_u32(&ptr->CCMR1, CC1S_OFFSET, CCS_MASK, CCS_OUTPUT);
    set_ptr_vol_u32(&ptr->CCMR1, OC1M_OFFSET, OCM_MASK, PWM_MODE1);
    set_ptr_vol_bit_u32(&ptr->CCER, CC1E_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC1P_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC1NP_BIT);
}

/* Default Set Up For PWM */
void timer_set_pwm_ch2(TIMER_TypeDef *ptr) {
    set_ptr_vol_u32(&ptr->CCMR1, CC2S_OFFSET, CCS_MASK, CCS_OUTPUT);
    set_ptr_vol_u32(&ptr->CCMR1, OC2M_OFFSET, OCM_MASK, PWM_MODE1);
    set_ptr_vol_bit_u32(&ptr->CCER, CC2E_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC2P_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC2NP_BIT);
}

/* Default Set Up For PWM */
void timer_set_pwm_ch3(TIMER_TypeDef *ptr) {
    set_ptr_vol_u32(&ptr->CCMR2, CC1S_OFFSET, CCS_MASK, CCS_OUTPUT);
    set_ptr_vol_u32(&ptr->CCMR2, OC1M_OFFSET, OCM_MASK, PWM_MODE1);
    set_ptr_vol_bit_u32(&ptr->CCER, CC3E_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC3P_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC3NP_BIT);
}

/* Default Set Up For PWM */
void timer_set_pwm_ch4(TIMER_TypeDef *ptr) {
    set_ptr_vol_u32(&ptr->CCMR2, CC2S_OFFSET, CCS_MASK, CCS_OUTPUT);
    set_ptr_vol_u32(&ptr->CCMR2, OC2M_OFFSET, OCM_MASK, PWM_MODE1);
    set_ptr_vol_bit_u32(&ptr->CCER, CC4E_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC4P_BIT);
    clr_ptr_vol_bit_u32(&ptr->CCER, CC4NP_BIT);
}