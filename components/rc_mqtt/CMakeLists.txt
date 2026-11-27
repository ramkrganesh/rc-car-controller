idf_component_register(SRCS "rc_mqtt.c"
                    INCLUDE_DIRS "include"
                    REQUIRES nvs_flash esp_event esp_netif mqtt protocol_examples_common)
