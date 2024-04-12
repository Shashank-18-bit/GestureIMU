set(srcs "i2cdev.c" "mpu.c")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "."
                    REQUIRES driver efuse esp_common esp_event esp_timer
                                esp_rom freertos heap log soc spiffs)
