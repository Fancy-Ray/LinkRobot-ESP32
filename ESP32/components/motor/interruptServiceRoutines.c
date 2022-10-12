#include "interruptServiceRoutines.h"
extern quadratureSturct motor0;
void IRAM_ATTR gpio_isr_handler(void *arg)
{
    motor0.Alast = motor0.A;
    if (gpio_get_level(23) == 0)
        motor0.A = 0;
    else
        motor0.A = 2;
    motor0.Blast = motor0.B;
    if (gpio_get_level(22) == 0)
        motor0.B = 0;
    else
        motor0.B = 1;
    getRawAngle(&motor0);
    if (motor0.rawAngle > 1536){
        motor0.rawAngle = 1;
        motor0.numberOfTurns++;
        motor0.ifChangeTurn=1;
        }
    if (motor0.rawAngle < 0){
        motor0.rawAngle = 1536;
        motor0.numberOfTurns--;
        motor0.ifChangeTurn=-1;
        }
}
/**
 * @brief used in isr,use M-method to get raw speed data
 * @param 
 * @note
 * @return Always return void.
 */
void IRAM_ATTR timing_isr_handler(void *arg){
    motor0.rawSpeed=motor0.rawAngle+motor0.ifChangeTurn*1536-motor0.rawAngleLast;
    motor0.rawAngleLast=motor0.rawAngle;
    motor0.ifChangeTurn=0;
    // processRawData(&motor0);
    motor0.angle=((motor0.rawAngle) + motor0.numberOfTurns * 1536);
    timer_set_alarm(TIMER_GROUP_0, TIMER_0,TIMER_ALARM_EN);
}