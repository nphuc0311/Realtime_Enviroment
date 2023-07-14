#include <stdio.h>
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_wifi.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "mqtt_client.h"
#include "dht11.h"

#include "mesh.h"
#include "mq2.h"

adc_oneshot_unit_handle_t adc1_handle;
adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
bool do_calibration1_chan0;
adc_cali_handle_t adc1_cali_chan0_handle = NULL;

// struct dht11_reading last_read;

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    /* tcpip initialization */
    ESP_ERROR_CHECK(esp_netif_init());
    /* event initialization */
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    mesh_init();    
    // int temp, humi;
    // float gas;

    // vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
    DHT11_init(GPIO_NUM_22);
    mq2_init();
    // mesh_init();    

    // while (1) {

        
    //     temp = DHT11_read().temperature;
    //     humi = DHT11_read().humidity;
    //     gas = mq2_read().percent;

    //     printf("%d\n", temp);
    //     printf("%d\n", humi);
    //     printf("%.1f\n", gas);
    //     vTaskDelay(1 * 1000 / portTICK_PERIOD_MS);
    // }
}


