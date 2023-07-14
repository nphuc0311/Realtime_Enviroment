#ifndef _WIFI_H_
#define _WIFI_H_

typedef struct {
    char ssid[33];
    char password[65];
} wf_cfg;

void wifi_init();

#endif