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

#define MAX_SAMPLES 300
#define MAX_END_SEQ_COUNT 3

static const char *TAG = "MAIN";

void app_main()
{
  int16_t acce_raw_value[BUFF_SIZE / 2], gyro_raw_value[BUFF_SIZE / 2];
  uint32_t count = 0;
  int16_t end_seq[4] = {0,1,0};
  // TODO : make end_seq of different size than the acqual data, this will ensure data
  // aquisition is terminated successfully
  int i = 0;

  while (1)
  {
    if (enable_mpu() == ESP_OK)
    {
      setup_ble();
      while (read_mpu_raw(acce_raw_value, gyro_raw_value) == ESP_OK && count < MAX_SAMPLES)
      {
        if (ble_hid_task(acce_raw_value) != ESP_OK)
          ESP_LOGE(TAG, "%s", "Failed to send acc values !!");

        count++;
      }

      /* We have come out of the while loop, send the end sequence */
      for(i = 0; i < MAX_END_SEQ_COUNT; i++)
      {
        if (ble_hid_task(end_seq) != ESP_OK)
          ESP_LOGE(TAG, "%s", "Failed to send the end sequence !!");
      }

      // TODO : wait until next button press, but code is not written for that
      // so for now just poll and log forever so that the task does not exit

      ///////////////// This will go //////////////////////////
      while (1)
      {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, ". . .");
      }
      /////////////////////////////////////////////////////////

    }
  }
  ESP_LOGE(TAG, "%s", "Error reading values!");
}
