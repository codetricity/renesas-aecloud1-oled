/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*
 *
 *    Author: Michael Li (Self - independent developer)
 *    Date: 10/27/2017
 *    Company: Self
 *    Project: Renesas S5D9 Tutorial.
 *
 *    Description: This file is based on Adafruit work and modified extensively for Renesas S5D9.
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

#define SSD1306_I2C_ADDRESS   0x3C	// 011110+SA0+RW - 0x3C or 0x3D
// Address for 128x32 is 0x3C
// Address for 128x32 is 0x3D (default) or 0x3C (if SA0 is grounded)

#define SSD1306_128_64


#if defined SSD1306_128_64
  #define SSD1306_LCDWIDTH                  128
  #define SSD1306_LCDHEIGHT                 64
#endif

#define FONTHEIGHT  8
#define FONTWIDTH   8

// added by M. Li since GFX libaray is not used
#define WIDTH SSD1306_LCDWIDTH
#define HEIGHT SSD1306_LCDHEIGHT

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2


// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

void oled_begin(uint8_t switchvcc);
void ssd1306_command(uint8_t c);
void ssd1306_data(uint8_t c);
void oled_display();

void drawADot1(int16_t x, int16_t y, uint8_t bitval);
void drawADot2(int16_t x, int16_t y, uint8_t bitval);
void clearBuffer();

void writedisplaybuffer(uint16_t xpos, uint16_t ypos, char str[], uint8_t len);
void writefontchar(uint16_t xpos, uint16_t ypos, uint8_t choice);
void writefontnum(uint16_t xpos, uint16_t ypos, uint8_t number);
void displayNumber (uint16_t xpos, uint16_t ypos, uint16_t value);

#define HISTHEIGHT    50
#define MINTEMPHISTF  70
#define MAXTEMPHISTF  MINTEMPHISTF + HISTHEIGHT
#define HISTYPOS      60

#define HISTWIDTH     90
#define HISTXPOS      30



void displayHistogram(uint16_t xhist, uint16_t temperatureF);
void drawverticalline(uint16_t x, uint16_t y, uint16_t length);
void drawhorizontalline(uint16_t x, uint16_t y, uint16_t length);


