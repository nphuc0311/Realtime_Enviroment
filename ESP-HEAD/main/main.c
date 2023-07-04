#include <stdio.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "mqtt_client.h"

#include "MQTT.h"
#include "mesh.h"

esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address = {
            .uri = MQTT_ADDRESS,
            .port = MQTT_PORT
        },
        .credentials = {
            .username = "eXUeRHMZWmaE7CqW9nj2Peio1iKtDrNFdyHS3jGNtGgq6wa6KjYpn5CdbcuCs87v",
            .client_id = "phuc",
            .authentication.password = ""
        },
        .session = {
            .keepalive = KEEPALIVE,
            .last_will.topic = DISCONNECT_PUB,
            .last_will.msg = "Esp32",
            .last_will.msg_len = strlen("Esp32"),
            .last_will.qos = 1,
            .last_will.retain = 0
        }
    };


MQTT_Handler_Struct mqtt_h =
{
    .mqtt_cfg = &mqtt_cfg,
};

MQTT_Handler_Struct *mqtt_t;
esp_name *name_devices;
int count = 0;

void app_main(void)
{
    // name_devices = (esp_name*)malloc(10 * sizeof(esp_name));
    mesh_init();
    mqtt_init_start(&mqtt_h);
}


