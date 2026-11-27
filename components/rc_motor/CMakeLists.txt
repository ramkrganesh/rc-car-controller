idf_component_register(SRCS "rc_motor.c"
                    INCLUDE_DIRS "include"
                    REQUIRES rc_mqtt esp_driver_ledc esp_driver_gpio)
