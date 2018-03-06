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

#define APP_ERROR_TRAP(x)    if (x) {\
                                   g_ioport.p_api->pinWrite(g_leds.p_leds[RED], ON);\
                                   g_ioport.p_api->pinWrite(g_leds.p_leds[YEL], OFF);\
                                   g_ioport.p_api->pinWrite(g_leds.p_leds[GRN], OFF);\
                                    __BKPT();}

#define COUNTS_PER_MILLISECOND (120E6 / 1000)  // The timer period is based on msec

#define GRN (BSP_LED_LED1)
#define YEL (BSP_LED_LED2)
#define RED (BSP_LED_LED3)

#define OFF (IOPORT_LEVEL_LOW)
#define ON (IOPORT_LEVEL_HIGH)
extern bsp_leds_t g_leds;

void delay(timer_size_t delaytimeMS);
