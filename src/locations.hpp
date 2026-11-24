#pragma once
#include <cmath>
#include <cstdint>

namespace Trainer {
	extern float_t* HEALTH_LOCATION;
    extern float_t* ARMOR_LOCATION;
    extern int32_t* MONEY_LOCATION;

    extern uint8_t* UNLIMITED_AMMO_TOTAL_LOCATION;
    extern const uint8_t UNLIMITED_AMMO_TOTAL_SIZE;
    extern uint8_t UNLIMITED_AMMO_TOTAL_ORIGINAL[];
    extern uint8_t* UNLIMITED_AMMO_MAG_LOCATION;
    extern const uint8_t UNLIMITED_AMMO_MAG_SIZE;
    extern uint8_t UNLIMITED_AMMO_MAG_ORIGINAL[];
}
