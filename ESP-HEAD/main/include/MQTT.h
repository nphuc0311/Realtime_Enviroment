#ifndef MAIN_MQTT_APP_H_
#define MAIN_MQTT_APP_H_
#include "mqtt_client.h"

// #define WIFI_SSID      "1111"
// #define WIFI_PASS      "01245678"

#define MAX_LENGTH_TOPIC 30
#define MAX_LENGTH_DATA 10

#define TOPIC_ADD               "New_Devices/Name"
#define TOPIC_DELETE            "Delete_Devices/Name"
#define DISCONNECT_PUB          "Status/Disconnected"

#define KEEPALIVE 50


/**
 * Mqtt config
 */
#define MQTT_ADDRESS 		"mqtt://mqtt.flespi.io"
// #define MQTT_ADDRESS 		"192.168.137.154"
#define MQTT_PORT 		1883

#define SEND_CYCLE 1000

typedef struct MQTT_Handler_Struct{   
    esp_mqtt_client_handle_t client;
    esp_mqtt_client_config_t* mqtt_cfg;    
} MQTT_Handler_Struct;

void log_error_if_nonzero(const char *, int );
void mqtt_event_handler(void *, esp_event_base_t , int32_t , void *);
bool mqtt_client_publish(MQTT_Handler_Struct*, char* , char *);
bool mqtt_client_subscribe(MQTT_Handler_Struct*, char*);
void mqtt_init_start(MQTT_Handler_Struct* );
void mqtt_stop_deinit(MQTT_Handler_Struct *);
#endif /* MAIN_MQTT_APP_H_ */













