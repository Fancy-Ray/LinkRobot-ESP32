#include "main.h"
int i=0;
quardratureSturct motor0;

// static void IRAM_ATTR gpio_isr_handler(void* arg)
// {
//     // printf("1111111");
//     // i=100;
// }

// static void IRAM_ATTR gpio_isr_handler_A(void* arg)
// {
//     // printf("1111111");
//      i=100;
// }
// static void IRAM_ATTR gpio_isr_handler_B(void* arg)
// {
//     // printf("1111111");
//      i=0;
// }

void app_main(void)
{
motor0.raw_value=10;
isr_init(GPIO_NUM_23,GPIO_NUM_22);
// a();

//中断
    // gpio_set_direction(4, GPIO_MODE_INPUT);
    // gpio_config_t io_conf = {};                             //零初始化结构体
    // io_conf.intr_type = GPIO_INTR_ANYEDGE;                  //禁用中断
    // io_conf.mode = GPIO_MODE_INPUT;                        //设置为输出模式
    // io_conf.pin_bit_mask = 4;             //要设置的引脚的位掩码,e.g.GPIO18/19
    // io_conf.pull_down_en = 0;                               //禁用下拉模式
    // io_conf.pull_up_en = 1;                                 //禁用上拉模式
    // gpio_config(&io_conf);   
    // gpio_set_intr_type(4,GPIO_INTR_ANYEDGE);
    // gpio_install_isr_service(0);
    // gpio_isr_handler_add(4,gpio_isr_handler,(void*) 4);
    // gpio_intr_enable(4);

 //PWM
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 2);
    mcpwm_config_t pwm_config={
        .frequency=1000,
        .cmpr_a=50,
        .duty_mode=MCPWM_DUTY_MODE_0,
        .counter_mode=MCPWM_UP_COUNTER,
    };
    mcpwm_init(MCPWM_UNIT_0,MCPWM_TIMER_0,&pwm_config);
    mcpwm_start(MCPWM_UNIT_0,MCPWM_TIMER_0);

//UART
    // //配置结构体
    // uart_config_t uart_config = {
    //     .baud_rate = 115200,
    //     .data_bits = UART_DATA_8_BITS,
    //     .parity    = UART_PARITY_DISABLE,   //校验
    //     .stop_bits = UART_STOP_BITS_1,      //停止位
    //     .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,   //硬件流
    //     .source_clk = UART_SCLK_APB,             //时钟
    // };
    // //安装使能
    //   // 端口号 接收缓存 发送缓存 队列大小 队列指针 分配中断标记
    // uart_driver_install(UART_NUM_0, 2*1024, 0, 0, NULL, 0);
    // //对串口结构体配置
    // uart_param_config(UART_NUM_0, &uart_config);
    
//时钟
    /* Select and initialize basic parameters of the timer */
    // timer_config_t config = {
    //     .divider = 16,
    //     .counter_dir = TIMER_COUNT_UP,
    //     .counter_en = TIMER_PAUSE,
    //     .alarm_en = TIMER_ALARM_DIS,
    //     .auto_reload = false,
    // }; // default clock source is APB
    // timer_init(TIMER_GROUP_0, TIMER_0, &config);
    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    // timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
    // /* Configure the alarm value and the interrupt on alarm. */
    // timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 3 * TIMER_BASE_CLK / 16);
    // timer_start(TIMER_GROUP_0, TIMER_0);
    while (1)
    {
        // printf("12");
        // static bool j=0;
        // if(j==0){
        //     i=i+1;
        //     if(i==100)
        //         j=1;
        // }
        // else{
        //     i=i-1;
        //     if(i==0)
        //         j=0;
        // }
        // vTaskDelay(10);
        // printf("%d\n",i);
        usleep(10000);
        printf("%d\n",motor0.raw_value);
        // printf("%d:%d:%d:%d\n",motor0.Alast,motor0.Blast,motor0.A,motor0.B);
        // gpio_set_level(2,0);
        // usleep(100000);
        // gpio_set_level(2,1);
        mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_GEN_A,i);
        // uint64_t task_counter_value;
        // timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &task_counter_value);
        // printf("Counter: %d\r\n",(uint32_t)(task_counter_value));
        
    }
}