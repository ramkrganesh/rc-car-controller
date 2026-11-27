#ifndef _RC_MOTOR_H_
#define _RC_MOTOR_H_

#define MAIN_MOTOR_IN1  4u  // will be always HIGH
#define MAIN_MOTOR_IN2  5u  // driven by PWM
#define SUB_MOTOR_IN1   6u
#define SUB_MOTOR_IN2   7u
extern void app_motor(void);
#endif
