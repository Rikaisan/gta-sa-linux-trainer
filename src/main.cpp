#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <sys/uio.h>

#include "cheats/player.hpp"
#include "cheats/weapons.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
    auto pidResult = Trainer::getTargetPid();

    if (!pidResult.has_value()) {
        printf("GTA San Andreas not open or not found.\n");
        return 1;
    }

    pid_t gta_sa_pid = pidResult.value();
    
    if (argc <= 1) {
        printf("Usage: trainer <ammo|imoney|money|state> [options]\n");
    } else {
        if (strcmp(argv[1], "state") == 0) {
            Trainer::Player::printState(gta_sa_pid);
        } else if (strcmp(argv[1], "money") == 0) {
            if (argc < 3) {
                printf("Sets the player money\n");
                printf("Usage: money <amount>\n");
                return 2;
            }

            int32_t amount = atoi(argv[2]);
            if(Trainer::Player::setMoney(gta_sa_pid, amount)) {
                printf("Money set!\n");
            } else {
                printf("Couldn't modify money!\n");
                return 3;
            }
        } else if (strcmp(argv[1], "imoney") == 0) {
            if (argc < 3) {
                printf("Sets the player money and skips the rolling animation\n");
                printf("Usage: imoney <amount>\n");
                return 2;
            }

            int32_t amount = atoi(argv[2]);
            if(Trainer::Player::setMoneyInstant(gta_sa_pid, amount)) {
                printf("Money set!\n");
            } else {
                printf("Couldn't modify money!\n");
                return 3;
            }
        } else if (strcmp(argv[1], "ammo") == 0) {
            if (argc < 3) {
                printf("Enables/Disables infinite ammo\n");
                printf("Usage: ammo <on|off>\n");
                return 2;
            }

            if ((strcmp(argv[2], "on") == 0)) {
                Trainer::Weapons::enableInfiniteAmmo(gta_sa_pid);
                printf("Infinite ammo enabled!\n");
            } else if ((strcmp(argv[2], "off") == 0)) {
                Trainer::Weapons::disableInfiniteAmmo(gta_sa_pid);
                printf("Infinite ammo disabled!\n");
            } else {
                printf("Enables/Disables infinite ammo\n");
                printf("Usage: ammo <on|off>\n");
                return 2;
            }
        }
    }
    return 0;
}