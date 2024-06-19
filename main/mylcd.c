#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "hd44780.h"  // Replace with your HD44780 library header

#define I2C_MASTER_SCL_IO           22    /*!< GPIO number for I2C master clock */
#define I2C_MASTER_SDA_IO           21    /*!< GPIO number for I2C master data  */
#define I2C_MASTER_NUM              I2C_NUM_0 /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ          100000 /*!< I2C master clock frequency */
#define HD44780_I2C_ADDR            0x27  /*!< I2C address of HD44780 LCD */

void init_i2c_master() {
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void app_main() {
    init_i2c_master();

    // Initialize HD44780 library
    hd44780_t lcd;
    lcd = hd44780_create_i2c(I2C_MASTER_NUM, HD44780_I2C_ADDR, HD44780_I2C_NIBBLE_MODE, HD44780_I2C_BACKLIGHT_POLARITY_POSITIVE);

    // Initialize LCD
    hd44780_init(&lcd, 16, 2);

    // Display "Hello, World!"
    hd44780_clear_display(&lcd);
    hd44780_printf(&lcd, "Hello, World!");

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
