/*
 PlutoX API V.1.0
 */


#pragma once

#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    RED = 0,
    GREEN,
    BLUE

} led_e;

typedef enum {
    OFF = 0,
    ON,
    TOGGLE

} led_state_e;


typedef enum {

    ACTIVATE = 0,
    DEACTIVATE

} flightstatus_state_e;




class LED_P {
public:

    void set(led_e LED, led_state_e STATE);

    void flightStatus(flightstatus_state_e STATE);



};


class Graph_P {
public:

    void red(double value, uint8_t precision=4);

    void green(double value, uint8_t precision=4);

    void blue(double value, uint8_t precision=4);

};



class Interval {

private:

uint32_t time;
uint32_t loopTime;



public:


    bool set(uint32_t time, bool repeat); //time is in milliseconds
    void reset(void);


};




class Monitor_P {

public:


void print(const char* msg);

void print(const char* tag, int number);

void print(const char* tag, double number, uint8_t precision);

void println(const char* msg);

void println(const char* tag, int number);

void println(const char* tag, double number, uint8_t precision);


};

uint32_t micros();

uint32_t millis();


extern LED_P LED;
extern Graph_P Graph;
extern Monitor_P Monitor;


#ifdef __cplusplus
}
#endif
