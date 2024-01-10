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

    // Enable the MPU-6050 Sensor
    enable_mpu();

    // Setting up the result arrays, time difference and initial conditions
    float acce_angle[2], gyro_angle[2], complementary_angle[2], dt;
    float mpu_offset[2] = {0.0f, 0.0f};

    int16_t acce_raw_value[BUFF_SIZE / 2], gyro_raw_value[BUFF_SIZE / 2];
    uint32_t timer = esp_timer_get_time();

    // Read the MPU raw values
    while (read_mpu_raw(acce_raw_value, gyro_raw_value) == ESP_OK)
    {
        // Calculate the time difference between two samples
        dt = (float)(esp_timer_get_time() - timer) / 1000000;
        timer = esp_timer_get_time();
        
        // Get the angles as per the accelerometer raw values only
        compute_acce_angle(acce_raw_value[0], acce_raw_value[1], acce_raw_value[2], acce_angle);
        // Get the angles computed as per the gyroscope raw values only
        compute_gyro_angle(gyro_raw_value[0], gyro_raw_value[1], gyro_raw_value[2], dt, gyro_angle);
        // Get fused angles due to both the accelerometer and gyroscope
        complementary_filter(acce_raw_value, gyro_raw_value, complementary_angle, mpu_offset);
    }

    ESP_LOGE(TAG, "%s", "Error reading values!");
}
