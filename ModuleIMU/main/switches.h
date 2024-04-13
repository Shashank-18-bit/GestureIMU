#ifndef SWITCHES_H
#define SWITCHES_H

#include <stdlib.h>
// #include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_err.h"
#include "switch_pindefs.h"

esp_err_t enable_switches();
int read_switch(int switch_id);

#endif
