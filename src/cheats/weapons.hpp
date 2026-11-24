#pragma once
#include <cstdint>
#include <sys/types.h>


namespace Trainer {
	namespace Weapons {
        extern uintptr_t INF_AMMO_TOTAL_LOCATION;
        extern const uint8_t INF_AMMO_TOTAL_SIZE;
        extern uint8_t INF_AMMO_TOTAL_ORIGINAL[];
        extern uintptr_t INF_AMMO_MAG_LOCATION;
        extern const uint8_t INF_AMMO_MAG_SIZE;
        extern uint8_t INF_AMMO_MAG_ORIGINAL[];

        bool enableInfiniteAmmo(pid_t pid);
        bool disableInfiniteAmmo(pid_t pid);
    }
}
