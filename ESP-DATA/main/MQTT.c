/* Mesh IP Internal Networking Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "esp_log.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "esp_tls.h"

#include "mqtt_client.h"

#include "MQTT.h"


#define NUMBER_OF_TOPIC 1
#define NUMBER_OF_SENSOR 2

static const char *TAG = "mesh_mqtt";
static esp_mqtt_client_handle_t s_client = NULL;
static char **topic_list;
static char **data_list;

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:  {
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            topic_list = malloc(NUMBER_OF_TOPIC*sizeof(char *));
            data_list = malloc(NUMBER_OF_SENSOR*sizeof(char *));

            data_list[0] = "70";
            data_list[1] = "80";
            data_list[2] = "90";

            topic_list[0] = "sensor/nhiet_do";
            topic_list[1] = "sensor/do_am";
            topic_list[2] = "sensor/gass";

            while (1)
            {
                for(int i=0; i<3; i++)
                    mqtt_app_publish(TOPIC, data_list[i]);

                vTaskDelay(5000/portTICK_PERIOD_MS);
            }
        }
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            // ESP_LOGI(TAG, "TOPIC=%.*s", event->topic_len, event->topic);
            // ESP_LOGI(TAG, "DATA=%.*s", event->data_len, event->data);
            break;

        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;

        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%" PRId32 "", base, event_id);
    mqtt_event_handler_cb(event_data);
}

void mqtt_app_publish(char* topic, char *publish_string)
{
    if (s_client) {
        int msg_id = esp_mqtt_client_publish(s_client, topic, publish_string, 0, 1, 0);
        ESP_LOGI(TAG, "sent publish returned msg_id=%d", msg_id);
    }
}

void mqtt_app_subscribe(char* topic)
{
    if (s_client) {
        int msg_id = esp_mqtt_client_subscribe(s_client, topic, 0);
        ESP_LOGI(TAG, "sent subscribe returned msg_id=%d", msg_id);
    }

}

void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = CONFIG_BROKER_URL,
    };

    s_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(s_client, ESP_EVENT_ANY_ID, mqtt_event_handler, s_client);
    esp_mqtt_client_start(s_client);
}