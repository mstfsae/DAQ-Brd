#ifndef ADS8668_H
#define ADS8668_H

#include "SPI_Tools.h"
#include "sdkconfig.h"


// Channel Ranges (Selected in MENUCONFIG)
#define CH0_RANGE  CONFIG_CH0_RANGE_VAL
#define CH1_RANGE  CONFIG_CH1_RANGE_VAL
#define CH2_RANGE  CONFIG_CH2_RANGE_VAL
#define CH3_RANGE  CONFIG_CH3_RANGE_VAL
#define CH4_RANGE  CONFIG_CH4_RANGE_VAL
#define CH5_RANGE  CONFIG_CH5_RANGE_VAL
#define CH6_RANGE  CONFIG_CH6_RANGE_VAL
#define CH7_RANGE  CONFIG_CH7_RANGE_VAL

#if CONFIG_SPI2_HOST
#define HOST_ID SPI2_HOST
#elif CONFIG_SPI3_HOST
#define HOST_ID SPI3_HOST
#else
#error "No SPI Host selected. Please select SPI2 or SPI3 in menuconfig."
#endif


typedef struct {
    uint16_t cmd;
    uint8_t data[16];
    uint8_t databytes; //No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} adc_init_cmd_t;



DRAM_ATTR static const adc_init_cmd_t adc_init_cmds[] = { // Copied from Old code
    // Resets all registers to default values Table 6
    {0x8500, {0x8500}, 1},
    // Enter NO_OP State (Idle) Table 6
    {0x0000,{0x0000}, 1},
 // --- Set Channel Ranges --- Figure 112
    // Channel 0
    {0x0005, {0x00 & CH0_RANGE}, 1},
    // Channel 1
    {0x0006, {0x00 & CH1_RANGE}, 1}, 
    // Channel 2
    {0x0007, {0x00 & CH2_RANGE}, 1}, 
    // Channel 3
    {0x0008, {0x00 & CH3_RANGE}, 1}, 
    // Channel 4
    {0x0009, {0x00 & CH4_RANGE}, 1}, 
    // Channel 5
    {0x000A, {0x00 & CH5_RANGE}, 1}, 
    // Channel 6
    {0x000B, {0x00 & CH6_RANGE}, 1}, 
    // Channel 7
    {0x000C, {0x00 & CH7_RANGE}, 1}, 
// ----------------------------
    // Sets Feature Register Settings
    {0x0003, {0x00}, 1}, // Device ID: 0, ALARM Disabled, SDO Format [Conversion Results, SDO Pulled Low] found in Figure: 111
    // Sets AutoScan Channel Sequence
    {0x0001, {0xFF}, 1},
    // Enters AutoScan Channel State
    {0xA000, {0xA0}, 1},
    {0, {0}, 0xff} // END Sequence for ADC Initialization Loop (not actually transmitted)
};


esp_err_t ADC8668_Init(spi_device_handle_t *handle, int cs_pin);

esp_err_t ADC8668_Read(spi_device_handle_t *spi, uint16_t *data);





#endif