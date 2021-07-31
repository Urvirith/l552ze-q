#ifndef MAIN_H_
#define MAIN_H_

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define TIMER2              ((TIMER_TypeDef *) TIMER2_BASE)
#define TIMER3              ((TIMER_TypeDef *) TIMER3_BASE)
#define TIMER4              ((TIMER_TypeDef *) TIMER4_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)

enum motor_dir {MotorReverse, MotorForward};

void loop(bool dir, GPIO_TypeDef * dir_ptr, uint32_t pin_dir, GPIO_TypeDef * pulse_ptr, uint32_t pin_pulse, uint32_t steps);
void delay(TIMER_TypeDef * ptr, uint32_t time_us);

#endif /* MAIN_H_ */