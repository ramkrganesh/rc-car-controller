#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "rc_data.h"
#include "rc_mqtt.h"
#include "rc_motor.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

static void control_the_car(const rc_ctrl_t* cmd)
{
    float throttle = cmd->throttle;
    float breaking = cmd->breaking;
    steering_position_t steering_pos = cmd->steering_pos;
    float steering_rot = cmd->steering_rot;
    printf("Throttle: %f\n", throttle);
    if((int)breaking > 50u )
    {
        (void)ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0u);
        (void)ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    }
    else
    {
        (void)ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (int)((throttle / 100)*1024)+1);
        (void)ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    }

    if(steering_pos == LEFT)
    {
        gpio_set_level(SUB_MOTOR_IN1, 0u);
        gpio_set_level(SUB_MOTOR_IN2, 1u);
    }
    else if(steering_pos == RIGHT)
    {
        gpio_set_level(SUB_MOTOR_IN1, 1u);
        gpio_set_level(SUB_MOTOR_IN2, 0u);
    }
    else
    {
        gpio_set_level(SUB_MOTOR_IN1, 1u);
        gpio_set_level(SUB_MOTOR_IN2, 1u);        
    }
}

static void init_pwm_channel(void)
{
    ledc_timer_config_t main_motor_timer_cfg = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 20000,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ledc_channel_config_t main_motor_channel_cfg = {
        .gpio_num = MAIN_MOTOR_IN2,
        .speed_mode=  LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0u,
        .hpoint = 0,
        .flags.output_invert = 1u,
    };

    (void)ledc_timer_config(&main_motor_timer_cfg); // initialize the timer
    (void)ledc_channel_config(&main_motor_channel_cfg);
    gpio_set_direction(MAIN_MOTOR_IN1, GPIO_MODE_OUTPUT);
    gpio_set_level(MAIN_MOTOR_IN1, 1u);

    gpio_set_direction(SUB_MOTOR_IN1, GPIO_MODE_OUTPUT);
    gpio_set_level(SUB_MOTOR_IN1, 1u);

    gpio_set_direction(SUB_MOTOR_IN2, GPIO_MODE_OUTPUT);
    gpio_set_level(SUB_MOTOR_IN2, 1u);

}

void app_motor(void)
{
    static bool is_PwmChannelInitialized = 0u;
    if(is_PwmChannelInitialized==0u)
    {
        is_PwmChannelInitialized = 1u;
        init_pwm_channel();
    }


    TickType_t PrevWakeUpTime = xTaskGetTickCount();

    for(;;)
    {
        rc_ctrl_t received_cmd = {0};
        xQueuePeek(xQ_rc_ctrl_data, &received_cmd, 0); // 3rd argument is wait time
        control_the_car(&received_cmd);
        (void)xTaskDelayUntil(&PrevWakeUpTime, pdMS_TO_TICKS(100)); // Execute every 100ms
    }

}
