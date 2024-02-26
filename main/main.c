#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "mpu.h"
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "mpu_example";

void app_main()
{
    while (1)
    {
    // Enable the MPU-6050 Sensor and check for error
      if (enable_mpu() == ESP_OK)
      {
          // Setting up the result arrays, time difference and initial conditions
          int16_t acce_raw_value[BUFF_SIZE / 2], gyro_raw_value[BUFF_SIZE / 2];
          while (read_mpu_raw(acce_raw_value, gyro_raw_value) == ESP_OK)
          {
            ESP_LOGI(TAG, "acce_raw_value = %d %d %d",acce_raw_value[0],acce_raw_value[1],acce_raw_value[2]);
          }
        }
    }

    ESP_LOGE(TAG, "%s", "Error reading values!");
}
