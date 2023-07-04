#ifndef MESH_H
#define MESH_H

#define MESH_CHANNEL 11
#define MESH_ROUTER_SSID "Zer0Max"
#define MESH_ROUTER_PASSWD "t1vodich"
#define MESH_AP_AUTHMODE 4
#define MESH_AP_PASSWD "phuc123456789"
#define MESH_AP_CONNECTIONS 6
#define MESH_NON_MESH_AP_CONNECTIONS 0
#define MESH_MAX_LAYER 6
#define MESH_IE_CRYPTO_KEY "IE_CRYPTO_ENABLE"
#define RX_SIZE          (1024)

typedef struct {
    char addr[18];
    char name[50];
} esp_name;

void mesh_init(void);
// void esp_mesh_p2p_rx_main(void *arg);

#endif