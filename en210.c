#include "hal_data.h"
#include "hal_entry.h"
#include "i2c.h"
#include "en210.h"

float ConvertToFahrenheit(uint16_t data)
{
    float TinK = (float)data / 64; // Temperature in Kelvin
    float TinC = TinK - 273.15f; // Temperature in Celsius
    float TinF = TinC * 1.8f + 32.0f; // Temperature in Fahrenheit
    return(TinF);
}

static float ConvertToCelsius(uint16_t data)
{
    float TinK = (float)data / 64; // Temperature in Kelvin
    float TinC = (float) (TinK - 273.15); // Temperature in Celsius
    return(TinC);
}

float ConvertToHumidity(uint16_t data)
{
    return((float)data/512.0f);
}

ssp_err_t readstatus (uint16_t * result) {
    uint8_t   cmd[2];
    uint8_t   status_data[3];
    ssp_err_t err;

    cmd[0] = PART_ID;
    err = g_int_i2c_bus_write( cmd, 1, false);
    APP_ERROR_TRAP(err)

    if (err == SSP_SUCCESS) {
    err = g_int_i2c_bus_read(status_data, 3, false);
        APP_ERROR_TRAP(err)
    }

    *result =  ((uint16_t) status_data[1]) << 8;
    *result |= ((uint16_t) status_data[0]);
    return (err);
}

/* AMS ENS210 Thread entry function */
ssp_err_t en210_get_temp_humd(
        float * g_temperatureC,
        float * g_temperatureF,
        float * g_humidityP
        )
{
    ssp_err_t err;
    uint8_t cmd[2];
    AMS_ENS210_REG33_t humidity;
    AMS_ENS210_REG30_t temperature;

    /* TODO: add your own code here */
    cmd[0] = T_VAL;
    err = g_int_i2c_bus_write( cmd, 1, false);
    APP_ERROR_TRAP(err)

    if (err == SSP_SUCCESS) {
        err = g_int_i2c_bus_read(temperature.bytes , 3, false);
        APP_ERROR_TRAP(err)

        if (temperature.bit.valid)
        {
            *g_temperatureC = ConvertToCelsius(temperature.bit.data);
            *g_temperatureF = ConvertToFahrenheit(temperature.bit.data);
        }

        cmd[0] = H_VAL;
        err = g_int_i2c_bus_write( cmd, 1, false);
        APP_ERROR_TRAP(err)

        err = g_int_i2c_bus_read(humidity.bytes , 3, false);
        APP_ERROR_TRAP(err)

        if (humidity.bit.valid)
            *g_humidityP= ConvertToHumidity(humidity.bit.data);
    }
    return (err);
}
