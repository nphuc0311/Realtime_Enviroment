#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"

#include "mqtt_client.h"
#include "MQTT.h"
#include "mesh.h"
#include "wifi.h"

// MQTT
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

// Wifi
wf_cfg wifi;
esp_netif_t *netif_sta = NULL;

// Mesh
mesh_config confg;

// Sensor
esp_name *name_devices;
int count = 2;

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    name_devices = (esp_name*)malloc(NUMBER_OF_DEVICES * sizeof(esp_name));
    sprintf(confg.name, "%s", "DEFAULT");
    sprintf(confg.ssid, "%s", MESH_ROUTER_SSID);
    sprintf(confg.password, "%s", MESH_ROUTER_PASSWD);

    sprintf(name_devices[0].name, "%s", "/NODE_01/DATA/SENSOR");
    sprintf(name_devices[0].addr, "%s", "40:22:d8:4f:5e:78");

    sprintf(name_devices[1].name, "%s", "/NODE_02/DATA/SENSOR");
    sprintf(name_devices[1].addr, "%s", "e0:5a:1b:a1:93:58");

    wifi_init();
    mesh_init();
//     mqtt_init_start(&mqtt_h);
}


