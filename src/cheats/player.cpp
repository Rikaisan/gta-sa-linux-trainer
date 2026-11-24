#include "player.hpp"
#include <cmath>

#include "../memory.hpp"

namespace Trainer {
    namespace Player {    
        uintptr_t HEALTH_LOCATION = 0x502af88;
        uintptr_t ARMOR_LOCATION = 0x502af90;
        uintptr_t MONEY_LOCATION = 0xb7ce50;
        uintptr_t MONEY_ANIM_1_LOCATION = 0xb7ce54;
        uintptr_t MONEY_ANIM_2_LOCATION = 0xbaa430;
    
        void printState(pid_t pid) {
            float_t health = Trainer::getValue<float_t>(pid, HEALTH_LOCATION);
            float_t armor = Trainer::getValue<float_t>(pid, ARMOR_LOCATION);
            int32_t money = Trainer::getValue<int32_t>(pid, MONEY_LOCATION);
    
            printf("Player State:\n");
            printf("\tHealth: %f\n", health);
            printf("\tArmor: %f\n", armor);
            printf("\tMoney: %d\n", money);
        }

        bool setMoney(pid_t pid, int32_t value) {
            return modifyValue(pid, MONEY_LOCATION, value);
        }

        bool setMoneyInstant(pid_t pid, int32_t value) {
            bool success = true;
            if(!modifyValue(pid, MONEY_LOCATION, value)) success = false;
            if(!modifyValue(pid, MONEY_ANIM_1_LOCATION, value)) success = false;
            if(!modifyValue(pid, MONEY_ANIM_2_LOCATION, value)) success = false;
            return success;
        }
    }
}
