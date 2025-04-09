#ifndef SPI_TOOLS_H
#define SPI_TOOLS_H

#include <stdio.h>
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "sdkconfig.h"

#define MISO_PIN_NUM CONFIG_MISO_PIN_NUM
#define MOSI_PIN_NUM CONFIG_MOSI_PIN_NUM
#define CLK_PIN_NUM CONFIG_CLK_PIN_NUM

spi_bus_config_t buscfg = {
    .miso_io_num = MISO_PIN_NUM,
    .mosi_io_num = MOSI_PIN_NUM,
    .sclk_io_num = CLK_PIN_NUM,
    .quadwp_io_num = -1, // -1 sets as not used
    .quadhd_io_num = -1, // -1 sets as not used
};
// Initializes the SPI bus and configures the SPI settings.
/**
 * @brief Initializes the SPI module.
 */
void spi_init();

/**
 * @brief Performs an SPI transfer by writing and reading data.
 *
 * This function transfers data over SPI by writing the specified data to the given address and reading the response.
 *
 * @param addr The address to write the data to.
 * @param data The data to be written.
 * @param CS The chip select pin to use.
 * @param handle The SPI device handle.
 * @param trans_desc The SPI transaction descriptor.
 * @return The received data from the SPI transfer.
 */
uint8_t spi_Trans(uint16_t addr, uint8_t data, uint8_t CS, spi_device_handle_t handle, spi_transaction_t trans_desc);
uint8_t spi_Trans(uint16_t addr, uint8_t data, uint8_t CS, spi_device_handle_t handle, spi_transaction_t trans_desc);     // SPI Transfer writes and reads
/**
 * @brief Adds a SPI device to the specified host.
 *
 * This function adds a SPI device to the specified host with the given device configuration.
 *
 * @param HOST The SPI host device to which the device will be added.
 * @param devcfg Pointer to the device configuration structure.
 * @param handle Pointer to store the SPI device handle.
 * @return ESP_OK if the device was successfully added, or an error code if an error occurred.
 */
esp_err_t spi_add_device(spi_host_device_t HOST, spi_device_interface_config_t *devcfg, spi_device_handle_t *handle);

#endif