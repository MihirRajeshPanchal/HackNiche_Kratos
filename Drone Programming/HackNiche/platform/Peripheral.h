/*
 PlutoX API V.1.0
 */


#pragma once

#include <stdint.h>

#include "Specifiers.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum{
    INPUT,
    INPUT_PU,
    INPUT_PD,
    OUTPUT,
} GPIO_Mode_e;


typedef enum{
    STATE_LOW,
    STATE_HIGH,
    STATE_TOGGLE
} GPIO_State_e;



class GPIO_P {
public:

    void init(unibus_e pin_number, GPIO_Mode_e mode);

    bool read(unibus_e pin_number);

    void write(unibus_e pin_number,GPIO_State_e STATE);


};


class ADC_P {
public:

    void init(unibus_e pin_number);


    uint16_t read(unibus_e pin_number);
};



typedef enum{
    UART2,
    UART3
}UART_Port_e;


typedef enum{
    BAUD_RATE_4800,
    BAUD_RATE_9600,
    BAUD_RATE_14400,
    BAUD_RATE_19200,
    BAUD_RATE_38400,
    BAUD_RATE_57600,
    BAUD_RATE_115200,
    BAUD_RATE_128000,
    BAUD_RATE_256000
}UART_Baud_Rate_e;


class UART_P {
public:


    void init(UART_Port_e PORT, UART_Baud_Rate_e BAUD);


    uint8_t read8(UART_Port_e PORT);

    uint16_t read16(UART_Port_e PORT);

    uint32_t read32(UART_Port_e PORT);


    void write(UART_Port_e PORT, uint8_t data);

    void write(UART_Port_e PORT, const char *str);

    void write(UART_Port_e PORT, uint8_t* data, uint16_t length);

    bool rxBytesWaiting(UART_Port_e PORT);

    bool txBytesFree(UART_Port_e PORT);

};



class I2C_P {
public:


    uint8_t* read(uint8_t device_add, uint8_t reg, uint32_t length);


    bool write(uint8_t device_add, uint8_t reg, uint32_t length, uint8_t* data);

};


class PWM_P {

public:

    void init(unibus_e pin_number, uint16_t pwmRate);

    void write(unibus_e pin_number, uint16_t pwmValue);

};





extern GPIO_P GPIO;
extern ADC_P ADC;
extern UART_P UART;
extern I2C_P I2C;
extern PWM_P PWM;


#ifdef __cplusplus
}
#endif

