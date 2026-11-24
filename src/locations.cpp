#include "locations.hpp"

namespace Trainer {
    float_t* HEALTH_LOCATION = (float_t*)0x502af88;
    float_t* ARMOR_LOCATION = (float_t*)0x502af90;
    int32_t* MONEY_LOCATION = (int32_t*)0xb7ce50;

    uint8_t* UNLIMITED_AMMO_TOTAL_LOCATION = (uint8_t*)0x007428e6;
    const uint8_t UNLIMITED_AMMO_TOTAL_SIZE = 3;
    uint8_t UNLIMITED_AMMO_TOTAL_ORIGINAL[UNLIMITED_AMMO_TOTAL_SIZE] = { 0xff, 0x4e, 0xc };

    uint8_t* UNLIMITED_AMMO_MAG_LOCATION = (uint8_t*)0x007428b0;
    const uint8_t UNLIMITED_AMMO_MAG_SIZE = 3;
    uint8_t UNLIMITED_AMMO_MAG_ORIGINAL[UNLIMITED_AMMO_TOTAL_SIZE] = { 0x89, 0x46, 0x8 };
}
