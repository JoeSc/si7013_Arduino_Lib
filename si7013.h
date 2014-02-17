
#ifndef SI7013_H
#define SI7013_H
#include <stdint.h>
#include <Wire.h>
#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif


#define HUMIDITY_MEAS_CMD       0xE5
#define TEMPERATURE_MEAS_CMD    0xE3
#define RH_TEMP_GET_CMD         0xE0

#define TIMEOUT                 100

class SI7013 {
    private:
        uint8_t _address;
        uint8_t _cmd_offset;
        uint8_t send_cmd(uint8_t);
        uint8_t get_data(uint8_t*, uint8_t);
    public:
        SI7013(uint8_t address, uint8_t clock_stretch);
        void begin(void);
        int readTemperature();
        int readHumidity();
        int getTempFromHumidity();
};

#endif
