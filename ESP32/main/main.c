#include "main.h"
int set=0;
float out;
float a,b;
float p=0.2;
float p2=0.2;
quadratureSturct motor0;

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
    wifi_init();

    motor0.rawAngleLast=0;
    motor0.rawAngle=0;
    motor0.rawSpeed=0;
    motor0.numberOfTurns=0;
    motor0.angle=0;
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
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 2);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_INPUT_OUTPUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, 15);
    mcpwm_config_t pwm_config={
        .frequency=10,
        .cmpr_a=0,
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
         vTaskDelay(10);
        // printf("%d\n",i);
        // printf("%d\n",gpio_get_level(2));
        // printf("%d:%d:%d:%d\n",motor0.Alast,motor0.Blast,motor0.A,motor0.B);
        printf("%d:%d:%d\n",motor0.rawSpeed,motor0.rawAngle,motor0.angle);
        printf("%f\n",out);



        // gpio_set_level(2,0);
        // usleep(1000000);
        // gpio_set_level(2,1);
        // usleep(1000000);
        
        set=0;
        out=(float)((float)(set-motor0.angle)*p-motor0.rawSpeed)*p2;
        if(out<0)a=0;
        else a=out;
        if(out>0)b=0;
        else b=-out;
        mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_GEN_A,a);//PWM
        mcpwm_set_duty(MCPWM_UNIT_0,MCPWM_TIMER_0,MCPWM_GEN_B,b);//PWM

        uint64_t task_counter_value;
        timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &task_counter_value);
        printf("Counter: %d\r\n",(uint32_t)(task_counter_value));
        // if((uint32_t)(task_counter_value)>50000000&&(uint32_t)(task_counter_value)<60000000){
        //     // timer_pause(TIMER_GROUP_0, TIMER_0);
        // gpio_set_level(2,0);
        // usleep(100000);
        // gpio_set_level(2,1);
        // usleep(100000);
        // timer_set_alarm(TIMER_GROUP_0, TIMER_0,TIMER_ALARM_EN);
        // }
        
    }
}