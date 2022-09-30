#include "encoder.h"
/**
 * @brief Reset an gpio to default state (select gpio function, enable pullup and disable input and output).
 *
 * @param gpio_num GPIO number.
 *
 * @note This function also configures the IOMUX for this pin to the GPIO
 *       function, and disconnects any other peripheral output configured via GPIO
 *       Matrix.
 *
 * @return Always return ESP_OK.
 */
// bool digitalRead(){

// }

/**
 * @brief initialization interrupt server routine
 * @param phase_A,phase_A GPIO number.
 * @note
 * @return Always return void.
 */
void isr_init(gpio_num_t phase_A, gpio_num_t phase_B)
{
    gpio_set_direction(phase_A, GPIO_MODE_INPUT);
    gpio_set_direction(phase_B, GPIO_MODE_INPUT);
    gpio_set_intr_type(phase_A, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(phase_B, GPIO_INTR_ANYEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(phase_A, gpio_isr_handler, (void *)phase_A);
    gpio_isr_handler_add(phase_B, gpio_isr_handler, (void *)phase_B);
    gpio_intr_enable(phase_A);
    gpio_intr_enable(phase_B);
}

void motor_rotation(quardratureSturct *quarstu)
{
    switch (quarstu->Alast + quarstu->Blast)
    {
    case 0:
        switch (quarstu->A + quarstu->B)
        {
        case 0:
            quarstu->raw_value = quarstu->raw_value;
            break;
        case 1:
            quarstu->raw_value = quarstu->raw_value - 1;
            break;
        case 2:
            quarstu->raw_value = quarstu->raw_value + 1;
            break;
        case 3:
            quarstu->raw_value = quarstu->raw_value - 2;
            break;
        }
        break;
    case 1:
        switch (quarstu->A + quarstu->B)
        {
        case 1:
            quarstu->raw_value = quarstu->raw_value;
            break;
        case 2:
            quarstu->raw_value = quarstu->raw_value + 2;
            break;
        case 3:
            quarstu->raw_value = quarstu->raw_value - 1;
            break;
        case 0:
            quarstu->raw_value = quarstu->raw_value + 1;
            break;
        }
        break;
    case 2:
        switch (quarstu->A + quarstu->B)
        {
        case 0:
            quarstu->raw_value = quarstu->raw_value - 1;
            break;
        case 1:
            quarstu->raw_value = quarstu->raw_value + 2;
            break;
        case 2:
            quarstu->raw_value = quarstu->raw_value;
            break;
        case 3:
            quarstu->raw_value = quarstu->raw_value + 1;
            break;
        }
        break;
    case 3:
        switch (quarstu->A + quarstu->B)
        {
        case 0:
            quarstu->raw_value = quarstu->raw_value - 2;
            break;
        case 1:
            quarstu->raw_value = quarstu->raw_value + 1;
            break;
        case 2:
            quarstu->raw_value = quarstu->raw_value - 1;
            break;
        case 3:
            quarstu->raw_value = quarstu->raw_value;
            break;
        }
        break;
    }
}