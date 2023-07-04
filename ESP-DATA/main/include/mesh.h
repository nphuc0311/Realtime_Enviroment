#ifndef MESH_H
#define MESH_H

#define TX_SIZE          (1024)

#define MESH_CHANNEL 11
#define MESH_ROUTER_SSID "An An"
#define MESH_ROUTER_PASSWD "sinhvien"
#define MESH_AP_AUTHMODE 4
#define MESH_AP_PASSWD "phuc123456789"
#define MESH_AP_CONNECTIONS 6
#define MESH_NON_MESH_AP_CONNECTIONS 0
#define MESH_MAX_LAYER 6
#define MESH_IE_CRYPTO_KEY "IE_CRYPTO_ENABLE"

void mesh_init(void);
// void esp_mesh_p2p_tx_main(void *arg);

#endif