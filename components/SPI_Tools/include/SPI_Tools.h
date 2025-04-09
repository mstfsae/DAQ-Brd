#ifndef SPI_TOOLS_H
#define SPI_TOOLS_H

#include <stdio.h>
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

spi_bus_config_t buscfg = {
    .miso_io_num = PIN_NUM_MISO,
    .mosi_io_num = PIN_NUM_MOSI,
    .sclk_io_num = PIN_NUM_CLK,
    .quadwp_io_num = -1, // -1 sets as not used
    .quadhd_io_num = -1, // -1 sets as not used
s
};
// Initializes the SPI bus and configures the SPI settings.
void spi_init();

/**
 * @brief Performs an SPI transfer operation.
 * 
 * @param addr The address to which the data will be written.
 * @param data The data byte to be sent.
 * @param CS The chip select pin to use for the operation.
 * @return uint8_t The data byte received during the SPI transfer.
 */
uint8_t spi_Trans(uint16_t addr, uint8_t data, uint8_t CS, spi_device_handle_t handle);     // SPI Transfer writes and reads
esp_err_t spi_add_device(spi_host_device_t HOST, spi_device_interface_config_t *devcfg, spi_device_handle_t *handle);

#endif