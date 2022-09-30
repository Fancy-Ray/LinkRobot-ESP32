#include "interruptServiceRoutines.h"
extern quardratureSturct motor0;
void IRAM_ATTR gpio_isr_handler(void* arg)
{
motor0.Alast=motor0.A;
if(gpio_get_level(23)==0)
motor0.A=0;
else
motor0.A=2;
motor0.Blast=motor0.B;
if(gpio_get_level(22)==0)
motor0.B=0;
else
motor0.B=1;
motor_rotation(&motor0);
}