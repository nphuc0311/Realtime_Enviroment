#include <stdio.h>

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"

#include "esp_log.h"

#include "MQTT.h"
#include "mesh.h"

#include "cJSON.h"

#include "dht11.h"


static const char *TAG = "mqtt connection";

// char temp_value[20];
// char humidity_value[20];
// char status[1];


extern int count;
extern MQTT_Handler_Struct mqtt_h;
extern MQTT_Handler_Struct *mqtt_t;
extern esp_name *name_devices;
extern mesh_config confg;

static char *topic;
static char *data;


void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0)
    {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    mqtt_t = (MQTT_Handler_Struct *)handler_args;
    // ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%ld", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    // esp_mqtt_client_handle_t client = event->client;
    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        mqtt_client_subscribe(mqtt_t, ADD_NODE_TOPIC);
        // xTaskCreate(&pub_data_clk, "DHT_task", 8192, NULL, 5, NULL);
        // mqtt_client_publish(mqtt_t, CONNECT_PUB, "Esp32");
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
    // case MQTT_EVENT_PUBLISHED:
    //     ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        
    //     break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        topic = event->topic;
        data = event->data;
        if (strcmp(topic, ADD_NODE_TOPIC)==0) {
            sprintf(confg.name, "%s", data);
        }
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT)
        {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno", event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
        }
        break;
    default:
        // ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}
bool mqtt_client_publish(MQTT_Handler_Struct *mqtt_t, char *topic, char *publish_string)
{
    if (mqtt_t->client)
    {
        int msg_id = esp_mqtt_client_publish(mqtt_t->client, topic, publish_string, 0, 1, 0);
        ESP_LOGI(TAG, "Sent publish returned msg_id=%d", msg_id);
        return true;
    }
    return false;
}

bool mqtt_client_subscribe(MQTT_Handler_Struct *mqtt_t, char *topic)
{
    if (mqtt_t->client)
    {
        int msg_id = esp_mqtt_client_subscribe(mqtt_t->client, topic, 1);
        // ESP_LOGI(TAG, "Sent publish returned msg_id=%d", msg_id);
        return true;
    }
    return false;
}

void mqtt_init_start(MQTT_Handler_Struct *mqtt_t)
{
    mqtt_t->client = esp_mqtt_client_init(mqtt_t->mqtt_cfg); 
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(mqtt_t->client, ESP_EVENT_ANY_ID, mqtt_event_handler, mqtt_t);
    esp_mqtt_client_start(mqtt_t->client);
}
