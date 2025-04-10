#include <stdio.h>
#include "SPI_Tools.h"

void spi_init(spi_host_device_t HOST)
{
    esp_err_t ret; 
    // Initialize Bus
    ret = spi_bus_initialize(HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

    return;
}
esp_err_t spi_add_device(spi_host_device_t HOST, spi_device_interface_config_t *devcfg, spi_device_handle_t *handle)
{
    // Attach a device to the SPI bus
    esp_err_t ret = spi_bus_add_device(HOST, devcfg, handle);
    ESP_ERROR_CHECK(ret);
    return ret;
}

esp_err_t spi_Trans(uint8_t CS, spi_device_handle_t handle, spi_transaction_t trans_desc )     // Function to write data at given address
{
    esp_err_t ret;

    gpio_set_level(CS, 0);                                      // Lower the CS' line to select the slave
    //printf("Writing '0x%x' data at 0x%x\n", data, addr); // For Debugging
    ret = spi_device_polling_transmit(handle, &trans_desc);                // spi_device_polling_transmit starts to transmit entire 'trans_desc' structure.
    if (ret != ESP_OK) {
        printf("SPI write operation failed with error: %d\n", ret);       // Log the error if transmission fails
    }
    
    // ERROR LOGGING TO SET UP LATER IF NEEDED
    // if (ret != ESP_OK) 
    // {
    //     ESP_LOGE(SPI_TAG, "SPI write operation failed\n");
    // }
    
    vTaskDelay(1 / portTICK_PERIOD_MS);                                 // Once data is transferred, we provide the delay and then set the CS'
    gpio_set_level(CS, 1);                                      // After CS' is high, the slave sill get unselected
    printf("Writing operation completed\n\n");

    
    return ret; // Return the received data
}