#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <sys/uio.h>

#include "locations.hpp"
#include "process.hpp"
#include "memory.hpp"
#include "util.hpp"

void printState(pid_t pid) {
    float_t health = Trainer::getValue(pid, Trainer::HEALTH_LOCATION);
    float_t armor = Trainer::getValue(pid, Trainer::ARMOR_LOCATION);
    int32_t money = Trainer::getValue(pid, Trainer::MONEY_LOCATION);

    printf("Player State:\n");
    printf("\tHealth: %f\n", health);
    printf("\tArmor: %f\n", armor);
    printf("\tMoney: %d\n", money);
}

int main(int argc, char* argv[]) {
    using namespace Trainer; // Only for constants
    auto pidResult = Trainer::getTargetPid();

    if (!pidResult.has_value()) {
        printf("GTA San Andreas not open or not found.\n");
        return 1;
    }

    pid_t gta_sa_pid = pidResult.value();
    
    if (argc <= 1) {
        printState(gta_sa_pid);
    } else {
        if (strcmp(argv[1], "money") == 0) {
            if (argc < 3) {
                printf("Usage: money <amount>\n");
                return 2;
            }
            int32_t amount = atoi(argv[2]);
            if(Trainer::modifyValue(gta_sa_pid, MONEY_LOCATION, amount)) {
                printf("Money set!\n");
            } else {
                printf("Couldn't modify money!\n");
                return 3;
            }
        }
        if (strcmp(argv[1], "ammo") == 0) { // Not working at the moment (even with sudo), maybe program code is protected (?)
            if (argc < 3) {
                printf("Usage: ammo <on|off|inspect>\n");
                return 2;
            }

            if ((strcmp(argv[2], "on") == 0)) {
                uint8_t newInstruction[] = { 0x90, 0x90, 0x90 };
                Trainer::setBytes(gta_sa_pid, UNLIMITED_AMMO_TOTAL_LOCATION, newInstruction, UNLIMITED_AMMO_TOTAL_SIZE);
                Trainer::setBytes(gta_sa_pid, UNLIMITED_AMMO_MAG_LOCATION, newInstruction, UNLIMITED_AMMO_TOTAL_SIZE);
                printf("Infinite ammo enabled!\n");
            } else if ((strcmp(argv[2], "off") == 0)) {
                Trainer::setBytes(gta_sa_pid, UNLIMITED_AMMO_TOTAL_LOCATION, UNLIMITED_AMMO_TOTAL_ORIGINAL, UNLIMITED_AMMO_TOTAL_SIZE);
                Trainer::setBytes(gta_sa_pid, UNLIMITED_AMMO_MAG_LOCATION, UNLIMITED_AMMO_MAG_ORIGINAL, UNLIMITED_AMMO_TOTAL_SIZE);
                printf("Infinite ammo disabled!\n");
            } else if ((strcmp(argv[2], "inspect") == 0)) {
                uint8_t* totalInstruction = Trainer::getBytes(gta_sa_pid, UNLIMITED_AMMO_TOTAL_LOCATION, UNLIMITED_AMMO_TOTAL_SIZE);
                uint8_t* magInstruction = Trainer::getBytes(gta_sa_pid, UNLIMITED_AMMO_MAG_LOCATION, UNLIMITED_AMMO_MAG_SIZE);
                printf("Total Instruction: %x %x %x\n", totalInstruction[0], totalInstruction[1], totalInstruction[2]);
                printf("Mag Instruction: %x %x %x\n", magInstruction[0], magInstruction[1], magInstruction[2]);
            } else {
                printf("Usage: ammo <on|off|inspect>\n");
                return 2;
            }
        }
    }
    return 0;
}