#pragma once
#include <cmath>
#include <sys/types.h>

namespace Trainer {
    namespace Player {    
        extern float_t* HEALTH_LOCATION;
        extern float_t* ARMOR_LOCATION;
        extern int32_t* MONEY_LOCATION;
        extern int32_t* MONEY_ANIM_1_LOCATION;
        extern int32_t* MONEY_ANIM_2_LOCATION;
    
        void printState(pid_t pid);
        bool setMoney(pid_t pid, int32_t value);
        bool setMoneyInstant(pid_t pid, int32_t value);
    }
}
