#include <stdio.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "mqtt_client.h"
#include "rc_wifi.h"
#include "rc_mqtt.h"
#include "rc_motor.h"
void app_main(void)
{
    (void)app_wifi();
    (void)app_mqtt();
    (void)app_motor();
}