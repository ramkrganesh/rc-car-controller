#ifndef _RC_DATA_H
#define _RC_DATA_H

typedef enum {
    CENTER = 0,
    LEFT,
    RIGHT
}steering_position_t;

typedef struct {
    float throttle;
    float breaking;
    steering_position_t steering_pos;
    float steering_rot;
    bool btn_triangle;
    bool btn_circle;
    bool btn_x;
    bool btn_square;
    bool r_paddleshifter;
    bool l_paddleshifter;
}rc_ctrl_t;

#endif