/*
 *
 *    Author: Michael Li (Self - independent developer)
 *    Date: 10/27/2017
 *    Company: Self
 *    Project: Renesas S5D9 Tutorial.
 *
 *    Description:
 *
 *  Develop the C code from scratch for the S5D9 board
 *
 *  Read the current temperature (F) from onboard AMS EN210 sensor (I2C interface).
 *  Display the current temperature (F) on OLED display (I2C interface).
 *  Display the temperature graphically over time on OLED display.
 *
 *
 */


#include "hal_data.h"
#include "i2c.h"


/*
 *
 * I2C read and write subroutines
 *
 */
ssp_err_t g_int_i2c_bus_slave_addr_set( uint16_t const slave)
{
    if (SSP_SUCCESS == g_int_i2c_bus.p_api->slaveAddressSet(g_int_i2c_bus.p_ctrl, slave, I2C_ADDR_MODE_7BIT))
    {
            //g_ioport.p_api->pinWrite(g_leds.p_leds[YEL], ON);
            return(SSP_SUCCESS);
    } else {
            return(SSP_SUCCESS);
    }
}


ssp_err_t g_int_i2c_bus_read(uint8_t * const p_src, uint32_t const bytes, bool const restart)
{
    ssp_err_t err;
    err = g_int_i2c_bus.p_api->read(g_int_i2c_bus.p_ctrl, p_src, bytes, restart);
    return(err);
}

ssp_err_t g_int_i2c_bus_write(uint8_t * const p_src, uint32_t const bytes, bool const restart)
{
    ssp_err_t err;
    err = g_int_i2c_bus.p_api->write(g_int_i2c_bus.p_ctrl, p_src, bytes, restart);
    return(err);
}

/*
 *
 * I2C read and write subroutines
 *
 */
ssp_err_t g_ext_i2c_bus_slave_addr_set( uint16_t const slave)
{
    if (SSP_SUCCESS == g_ext_i2c_bus.p_api->slaveAddressSet(g_ext_i2c_bus.p_ctrl, slave, I2C_ADDR_MODE_7BIT))
    {
            //g_ioport.p_api->pinWrite(g_leds.p_leds[YEL], ON);
            return(SSP_SUCCESS);
    } else {
            return(SSP_SUCCESS);
    }
}


ssp_err_t g_ext_i2c_bus_read(uint8_t * const p_src, uint32_t const bytes, bool const restart)
{
    ssp_err_t err;
    err = g_ext_i2c_bus.p_api->read(g_ext_i2c_bus.p_ctrl, p_src, bytes, restart);
    return(err);
}

ssp_err_t g_ext_i2c_bus_write(uint8_t * const p_src, uint32_t const bytes, bool const restart)
{
    ssp_err_t err;
    err = g_ext_i2c_bus.p_api->write(g_ext_i2c_bus.p_ctrl, p_src, bytes, restart);
    return(err);
}




