#include <stdio.h>
#include "ADS8668.h"

esp_err_t ADC8668_Init(spi_device_handle_t *handle, int cs_pin)
{
    esp_err_t ret = ESP_OK;
    uint8_t cmd = 0; // Iterator for initialization commands

    // Add ADC to SPIbus
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 15000000, //15MHz
        .mode = 0, // CPOL, CPHA configuration
        .spics_io_num = cs_pin /** @todo Check if this is needed or if the driver controls the CS*/ // Chip Select Pin 
    };

    ret = spi_add_device(HOST_ID, &devcfg, handle); /** @todo check my pointers cause im sped*/

    // Initialize ADC8668 with desired settings
    while(adc_init_cmds[cmd].cmd != 0xFF && ret == ESP_OK) /** @todo This loop feels sketchy, could get stuck*/
    {
        spi_transaction_t trans_desc = {
            .length = 16, // 
            .tx_buffer = &adc_init_cmds[cmd].cmd, 
            .rx_buffer = NULL // Don't expect a response when accessing command register
        };

        ret = spi_Trans(cs_pin, handle, trans_desc); /** @todo Add retry loop & timeout*/

        cmd++;
    }

    return ret;
}

esp_err_t ADC8668_Read(spi_device_handle_t *handle, int cs_pin, uint16_t *data)
{
    esp_err_t ret = ESP_OK;
    uint32_t buffer;

    spi_transaction_t trans_desc = {
            .length = 32, // 
            .tx_buffer = 0x0000, // Send 0x0000 to read the data register
            .rx_buffer = buffer,
        };

    ret = spi_Trans(cs_pin, handle, trans_desc); /** @todo Add retry loop & timeout*/

    if (ret == ESP_OK)
    {
        // Process the received data
        *data = (buffer >> 16) & 0xFFFF; // Extract the 16-bit data from the received buffer
    }
    
    return ret;
}
