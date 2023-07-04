#ifndef MQTT_H
#define MQTT_H

#define TOPIC "sensor/#"

void mqtt_app_start(void);
void mqtt_app_publish(char* topic, char *publish_string);
void mqtt_app_subscribe(char* topic);

#endif
