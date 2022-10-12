#include "encoder.h"
/**
 * @brief initialization interrupt server routine
 * @param phase_A,phase_B:GPIO number.
 * @note
 * @return Always return void.
 */
void isr_init(gpio_num_t phase_A, gpio_num_t phase_B)
{
    //initialize gpio isr
    gpio_set_direction(phase_A, GPIO_MODE_INPUT);
    gpio_set_direction(phase_B, GPIO_MODE_INPUT);
    gpio_set_intr_type(phase_A, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(phase_B, GPIO_INTR_ANYEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(phase_A, gpio_isr_handler, (void *)phase_A);
    gpio_isr_handler_add(phase_B, gpio_isr_handler, (void *)phase_B);
    gpio_intr_enable(phase_A);
    gpio_intr_enable(phase_B);

    //initialize timing isr
    /* Select and initialize basic parameters of the timer */
    timer_config_t config = {
        .divider = 1000,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = true,
    }; // default clock source is APB
    timer_init(TIMER_GROUP_0, TIMER_0, &config);
    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
    timer_isr_callback_add(TIMER_GROUP_0, TIMER_0,timing_isr_handler,NULL,0);
    /* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 8000);
    timer_start(TIMER_GROUP_0, TIMER_0);
}
/**
 * @brief used in isr,process motor encoder's pulse to get raw data
 * @param quarstu:A structure which coquadraturentain level informations from quadrature encoder
 * @note
 * @return Always return void.
 */
void getRawAngle(quadratureSturct *quarstu)
{
    switch (quarstu->Alast + quarstu->Blast)
    {
    case 0:
        switch (quarstu->A + quarstu->B)
        {
        case 0:
            quarstu->rawAngle = quarstu->rawAngle;
            break;
        case 1:
            quarstu->rawAngle = quarstu->rawAngle - 1;
            break;
        case 2:
            quarstu->rawAngle = quarstu->rawAngle + 1;
            break;
        case 3:
            quarstu->rawAngle = quarstu->rawAngle - 2;
            break;
        }
        break;
    case 1:
        switch (quarstu->A + quarstu->B)
        {
        case 1:
            quarstu->rawAngle = quarstu->rawAngle;
            break;
        case 2:
            quarstu->rawAngle = quarstu->rawAngle + 2;
            break;
        case 3:
            quarstu->rawAngle = quarstu->rawAngle - 1;
            break;
        case 0:
            quarstu->rawAngle = quarstu->rawAngle + 1;
            break;
        }
        break;
    case 2:
        switch (quarstu->A + quarstu->B)
        {
        case 0:
            quarstu->rawAngle = quarstu->rawAngle - 1;
            break;
        case 1:
            quarstu->rawAngle = quarstu->rawAngle + 2;
            break;
        case 2:
            quarstu->rawAngle = quarstu->rawAngle;
            break;
        case 3:
            quarstu->rawAngle = quarstu->rawAngle + 1;
            break;
        }
        break;
    case 3:
        switch (quarstu->A + quarstu->B)
        {
        case 0:
            quarstu->rawAngle = quarstu->rawAngle - 2;
            break;
        case 1:
            quarstu->rawAngle = quarstu->rawAngle + 1;
            break;
        case 2:
            quarstu->rawAngle = quarstu->rawAngle - 1;
            break;
        case 3:
            quarstu->rawAngle = quarstu->rawAngle;
            break;
        }
        break;
    }
}

void processRawData(quadratureSturct *quarstu){
    quarstu->angle=(float)((quarstu->rawAngle)*360/1536 + quarstu->numberOfTurns * 360);
}