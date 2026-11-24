#include "weapons.hpp"

#include "../process.hpp"

namespace Trainer {
	namespace Weapons {
        uintptr_t INF_AMMO_TOTAL_LOCATION = 0x007428e6;
        const uint8_t INF_AMMO_TOTAL_SIZE = 3;
        uint8_t INF_AMMO_TOTAL_ORIGINAL[INF_AMMO_TOTAL_SIZE] = { 0xff, 0x4e, 0xc };

        uintptr_t INF_AMMO_MAG_LOCATION = 0x007428b0;
        const uint8_t INF_AMMO_MAG_SIZE = 3;
        uint8_t INF_AMMO_MAG_ORIGINAL[INF_AMMO_TOTAL_SIZE] = { 0x89, 0x46, 0x8 };

        // Not working at the moment (even with sudo), maybe program code is protected (?)
        bool enableInfiniteAmmo(pid_t pid) {
            uint8_t newInstruction[] = { 0x90, 0x90, 0x90 };
            if (!setBytes(pid, INF_AMMO_TOTAL_LOCATION, newInstruction, INF_AMMO_TOTAL_SIZE)) return false;
            if (!setBytes(pid, INF_AMMO_MAG_LOCATION, newInstruction, INF_AMMO_TOTAL_SIZE)) return false;
            return true;
        }

        // Not working at the moment (even with sudo), maybe program code is protected (?)
        bool disableInfiniteAmmo(pid_t pid) {
            if (!setBytes(pid, INF_AMMO_TOTAL_LOCATION, INF_AMMO_TOTAL_ORIGINAL, INF_AMMO_TOTAL_SIZE)) return false;
            if (!setBytes(pid, INF_AMMO_MAG_LOCATION, INF_AMMO_MAG_ORIGINAL, INF_AMMO_TOTAL_SIZE)) return false;
            return true;
        }
    }
}
