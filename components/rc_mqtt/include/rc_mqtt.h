#ifndef _RC_MQTT_
#define _RC_MQTT_

extern volatile QueueHandle_t xQ_rc_ctrl_data;
extern void app_mqtt(void);
#endif