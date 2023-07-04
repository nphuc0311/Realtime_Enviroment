#include <stdio.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "mqtt_client.h"
#include "dht11.h"

#include "MQTT.h"
#include "mesh.h"

void app_main(void)
{
    DHT11_init(GPIO_NUM_23);
    mesh_init();
}


