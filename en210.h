#include "hal_data.h"

//  SHT31 Temperature and Humidity Sensor
#define EN210_I2C_ADDRESS   0x43

#define PART_ID 0x00
#define SYS_CTRL 0x10
#define SYS_STAT 0x11
#define SENS_RUN 0x21
#define H_RUN 0x02
#define T_RUN 0x01
#define SENS_START 0x22
#define H_START 0x02
#define T_START 0x01
#define T_VAL 0x30
#define H_VAL 0x33

typedef union AMS_ENS210_REG30
{
    uint32_t lword;
    uint8_t bytes[4];
    struct {
        uint16_t data;
        uint8_t valid   : 1;
        uint8_t crc     : 7;
        uint8_t         : 8;
    } bit;
} AMS_ENS210_REG30_t;

typedef union AMS_ENS210_REG33
{
    uint32_t lword;
    uint8_t bytes[4];
    struct {
        uint16_t data;
        uint8_t valid   : 1;
        uint8_t crc     : 7;
        uint8_t         : 8;
    } bit;
} AMS_ENS210_REG33_t;




float ConvertToHumidity(uint16_t data);
float ConvertToFahrenheit(uint16_t data);
static float ConvertToCelsius(uint16_t data);
float ConvertToHumidity(uint16_t data);
ssp_err_t readstatus (uint16_t * result);
ssp_err_t en210_get_temp_humd(float * g_temperatureC, float * g_temperatureF, float * g_humidityP);
