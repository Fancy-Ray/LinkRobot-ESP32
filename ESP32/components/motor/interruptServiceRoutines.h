#ifndef _ISR_H_
#define _ISR_H
#include "driver/gpio.h"
#include "encoder.h"
extern int i;
void IRAM_ATTR gpio_isr_handler(void* arg);
void IRAM_ATTR timing_isr_handler(void *arg);
#endif