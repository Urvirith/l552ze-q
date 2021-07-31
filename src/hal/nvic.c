#include "common.h"
#include "nvic.h"

uint32_t nvic_get_reg(uint32_t irq_num) {
    return (irq_num / NVIC_32BIT);
}

uint32_t nvic_get_bit(uint32_t irq_num) {
    return (irq_num % NVIC_32BIT);
}

uint32_t nvic_get_bit(uint8_t priority, uint8_t sub_priority) {
    return (((priority) << (6)) | (((sub_priority) & (0x3)) << (4)));
}