/*
 PlutoX API V.1.0
 */


#pragma once

#include <stdint.h>
#include "Comman.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum {

    PRESSURE,
    TEMPERATURE

}baro_state_e;


class Accelerometer_P {
public:

    //unit: cm/sec2

    int16_t get(axis_e AXIS);
    int32_t getNetAcc(void);

};

class Gyroscope_P {
public:

    //unit: decidegree/sec

    int16_t get(axis_e AXIS);

};

class Magnetometer_P {
public:

    //unit: microTesla

    int16_t get(axis_e AXIS);

};

class Barometer_P {
public:

    //unit: 100*millibar for Pressure
    //unit" 100*degreeCelsius Temperature

    int32_t get(baro_state_e STATE);

};

extern Accelerometer_P Acceleration;
extern Gyroscope_P Gyroscope;
extern Magnetometer_P Magnetometer;
extern Barometer_P Barometer;

#ifdef __cplusplus
}
#endif
