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
    UWB,
    WHYCON,
    VICON

} localisation_type;


class Localisation_P {

public:

    void init(localisation_type localisation);

    int16_t get(axis_e AXIS);

};

extern Localisation_P Localisation;

#ifdef __cplusplus
}
#endif
