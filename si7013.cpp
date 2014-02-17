
#include "si7013.h"

SI7013::SI7013(uint8_t address, uint8_t clock_stretch)
{
    _address = address;
    if (!clock_stretch)
        _cmd_offset = 0x10;
    else
        _cmd_offset = 0;
}

void SI7013::begin(void)
{
}


uint8_t SI7013::send_cmd(uint8_t cmd)
{
   Wire.beginTransmission(_address);
   Wire.write(cmd);
   return Wire.endTransmission(_address);
}
    
uint8_t SI7013::get_data(uint8_t* buf, uint8_t len)
{
    int i;

    for (i = 0; i < TIMEOUT; i++)
    {
        if (Wire.requestFrom(_address, len) >= len)
            break;
        delay(1);  
    }
    if ( i == TIMEOUT )
        return -1;  

    i = 0;
    while(Wire.available() && i < len)
        buf[i++] = (uint8_t)Wire.read();
    
    if (i != len)
        return -1;
    return 0;
}

int SI7013::readTemperature()
{
    uint8_t buf[2];
    int32_t temp;

    if (send_cmd(TEMPERATURE_MEAS_CMD + _cmd_offset))
        return -100000;

    if (get_data(buf, 2))
        return -100000;
    
    temp = ((uint32_t)buf[0] << 8) + buf[1];

    return (temp * 17572 + 65536 / 2) / 65536 - 4685;

}

// Return -1000 humidity if something goes wrong
int SI7013::readHumidity()
{
    uint8_t buf[2];
    uint32_t humid;

    if (send_cmd(HUMIDITY_MEAS_CMD + _cmd_offset))
        return -100000;

    if (get_data(buf, 2))
        return -100000;
    
    humid = ((uint32_t)buf[0] << 8) + buf[1];

    return (humid * 12500 + 65536 / 2) / 65536 - 600;
}

// Return -1000C temperature if something goes wrong
int SI7013::getTempFromHumidity()
{
    uint8_t buf[2];
    int32_t temp;

    if (send_cmd(RH_TEMP_GET_CMD))
        return -100000;

    if (get_data(buf, 2))
        return -100000;
    
    temp = ((uint32_t)buf[0] << 8) + buf[1];

    return (temp * 17572 + 65536 / 2) / 65536 - 4685;
}

