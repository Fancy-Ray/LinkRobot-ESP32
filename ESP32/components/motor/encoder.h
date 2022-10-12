#ifndef _ENCODER_H
#define _ENCODER_H
#include <stdio.h>
#include "driver/gpio.h"
#include "driver/timer.h"
#include "interruptServiceRoutines.h"
// #include "test_afl_fuzz_host/esp32_mock.h"
// #include "driver/mcpwm.h"
// #include "driver/uart.h"
// extern int i;
typedef struct  
{
    int A;
    int B;
    int Alast;
    int Blast;
    int rawAngleLast;
    int rawAngle;
    int rawSpeed;
    int numberOfTurns;
    int ifChangeTurn;//use for get raw speed
    int angle;
}quadratureSturct;
void getRawAngle(quadratureSturct *quarstu);
void processRawData(quadratureSturct *quarstu);
void isr_init(gpio_num_t phase_A,gpio_num_t phase_B);
#endif