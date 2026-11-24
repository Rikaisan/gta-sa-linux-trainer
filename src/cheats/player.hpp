#pragma once
#include <cstdint>
#include <sys/types.h>

namespace Trainer {
    namespace Player {    
        extern uintptr_t HEALTH_LOCATION;
        extern uintptr_t ARMOR_LOCATION;
        extern uintptr_t MONEY_LOCATION;
        extern uintptr_t MONEY_ANIM_1_LOCATION;
        extern uintptr_t MONEY_ANIM_2_LOCATION;
    
        void printState(pid_t pid);
        bool setMoney(pid_t pid, int32_t value);
        bool setMoneyInstant(pid_t pid, int32_t value);
    }
}
