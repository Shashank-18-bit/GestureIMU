#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "mpu.h"
#include "sdkconfig.h"
#include "esp_hid_gap.h"
#include "esp_hid_device.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN";

void app_main()
{
    int16_t acce_raw_value[BUFF_SIZE / 2], gyro_raw_value[BUFF_SIZE / 2];
    while (1)
    {
      // Enable the MPU-6050 Sensor and check for error
      if (enable_mpu() == ESP_OK)
      {
          // Setting up the result arrays, time difference and initial conditions
          setup_ble(); // Setup BLE
          while (read_mpu_raw(acce_raw_value, gyro_raw_value) == ESP_OK)
          {
            if (ble_hid_task(acce_raw_value) != ESP_OK)
              ESP_LOGE(TAG, "%s", "Failed to send acc values !!");
          }
      }
    }
    ESP_LOGE(TAG, "%s", "Error reading values!");
}
