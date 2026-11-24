#include "player.hpp"

#include "../memory.hpp"

namespace Trainer {
    namespace Player {    
        float_t* HEALTH_LOCATION = (float_t*)0x502af88;
        float_t* ARMOR_LOCATION = (float_t*)0x502af90;
        int32_t* MONEY_LOCATION = (int32_t*)0xb7ce50;
        int32_t* MONEY_ANIM_1_LOCATION = (int32_t*)0xb7ce54;
        int32_t* MONEY_ANIM_2_LOCATION = (int32_t*)0xbaa430;
    
        void printState(pid_t pid) {
            float_t health = Trainer::getValue(pid, HEALTH_LOCATION);
            float_t armor = Trainer::getValue(pid, ARMOR_LOCATION);
            int32_t money = Trainer::getValue(pid, MONEY_LOCATION);
    
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
