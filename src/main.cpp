#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <optional>
#include <stdio.h>
#include <sys/uio.h>

float_t* HEALTH_LOCATION = (float_t*)0x502af88;
float_t* ARMOR_LOCATION = (float_t*)0x502af90;
int32_t* MONEY_LOCATION = (int32_t*)0xb7ce50;

uint8_t* UNLIMITED_AMMO_TOTAL_LOCATION = (uint8_t*)0x007428e6;
const uint8_t UNLIMITED_AMMO_TOTAL_SIZE = 3;
uint8_t UNLIMITED_AMMO_TOTAL_ORIGINAL[UNLIMITED_AMMO_TOTAL_SIZE] = { 0xff, 0x4e, 0xc };
uint8_t* UNLIMITED_AMMO_MAG_LOCATION = (uint8_t*)0x007428b0;
const uint8_t UNLIMITED_AMMO_MAG_SIZE = 3;
uint8_t UNLIMITED_AMMO_MAG_ORIGINAL[UNLIMITED_AMMO_TOTAL_SIZE] = { 0x89, 0x46, 0x8 };

void printErrorMeaning(int err) {
    switch (err) {
        case EFAULT:
            printf("EFAULT: The memory described by (local/remote)_iov is outside the caller's accessible address space.\n");
            break;
        case EINVAL:
            printf("EINVAL: The sum of the iov_len values of either local_iov or remote_iov overflows a ssize_t value.\n");
            break;
        case EPERM:
            printf("EPERM: The caller does not have permission to access the address space of the process pid.\n");
            break;
        case ESRCH:
            printf("ESRCH: No process with ID pid exists.\n");
            break;
        default:
            printf("Unknown error: %d\n", errno);
            break;
    }
}

template <typename T>
T getValue(pid_t pid, T* location) {
    T read_value;
    struct iovec local[1], remote[1];
    local->iov_base = &read_value;
    local->iov_len = sizeof(T);
    remote->iov_base = location;
    remote->iov_len = sizeof(T);
    int nread = process_vm_readv(pid, local, 1, remote, 1, 0);
    if (nread == -1) {
        printf("Error while reading address: %p\n", location);
        printErrorMeaning(errno);
    }
    return read_value;
}

uint8_t* getBytes(pid_t pid, uint8_t* location, size_t size) {
    uint8_t* read_value = (uint8_t*)malloc(size);
    struct iovec local[1], remote[1];
    local->iov_base = read_value;
    local->iov_len = size;
    remote->iov_base = location;
    remote->iov_len = size;
    int nread = process_vm_readv(pid, local, 1, remote, 1, 0);
    if (nread == -1) {
        printf("Error while reading address: %p\n", location);
        printErrorMeaning(errno);
    }
    return read_value;
}

bool setBytes(pid_t pid, uint8_t* location, uint8_t* newValue, size_t size) {
    struct iovec local[1], remote[1];
    local->iov_base = newValue;
    local->iov_len = size;
    remote->iov_base = location;
    remote->iov_len = size;
    int nwrite = process_vm_writev(pid, local, 1, remote, 1, 0);
    if (nwrite == -1) {
        printf("Error while writing address: %p\n", location);
        printErrorMeaning(errno);
        return false;
    }
    return true;
}

template <typename T>
bool modifyValue(pid_t pid, T* location, T newValue) {
    struct iovec local[1], remote[1];
    local->iov_base = &newValue;
    local->iov_len = sizeof(T);
    remote->iov_base = location;
    remote->iov_len = sizeof(T);
    int nwrite = process_vm_writev(pid, local, 1, remote, 1, 0);
    if (nwrite == -1) {
        printf("Error while writing address: %p\n", location);
        printErrorMeaning(errno);
        return false;
    }
    return true;
}

void printState(pid_t pid) {
    float_t health = getValue(pid, HEALTH_LOCATION);
    float_t armor = getValue(pid, ARMOR_LOCATION);
    int32_t money = getValue(pid, MONEY_LOCATION);

    printf("Player State:\n");
    printf("\tHealth: %f\n", health);
    printf("\tArmor: %f\n", armor);
    printf("\tMoney: %d\n", money);
}

std::optional<pid_t> getTargetPid() {
    FILE* fp = popen("pgrep gta[-_]sa.exe", "r");
    if (fp == NULL) {
        perror("popen");
        return {};
    }

    static const size_t PID_BUFFER_SIZE = 16;

    char buffer[PID_BUFFER_SIZE] = {};
    fgets(buffer, PID_BUFFER_SIZE, fp);
    pclose(fp);

    for (size_t i; i < PID_BUFFER_SIZE; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }

    if (strlen(buffer) < 1) {
        return {};
    }

    return atoi(buffer);
}

int main(int argc, char* argv[]) {
    auto pidResult = getTargetPid();

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
            if(modifyValue(gta_sa_pid, MONEY_LOCATION, amount)) {
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
                setBytes(gta_sa_pid, UNLIMITED_AMMO_TOTAL_LOCATION, newInstruction, UNLIMITED_AMMO_TOTAL_SIZE);
                setBytes(gta_sa_pid, UNLIMITED_AMMO_MAG_LOCATION, newInstruction, UNLIMITED_AMMO_TOTAL_SIZE);
                printf("Infinite ammo enabled!\n");
            } else if ((strcmp(argv[2], "off") == 0)) {
                setBytes(gta_sa_pid, UNLIMITED_AMMO_TOTAL_LOCATION, UNLIMITED_AMMO_TOTAL_ORIGINAL, UNLIMITED_AMMO_TOTAL_SIZE);
                setBytes(gta_sa_pid, UNLIMITED_AMMO_MAG_LOCATION, UNLIMITED_AMMO_MAG_ORIGINAL, UNLIMITED_AMMO_TOTAL_SIZE);
                printf("Infinite ammo disabled!\n");
            } else if ((strcmp(argv[2], "inspect") == 0)) {
                uint8_t* totalInstruction = getBytes(gta_sa_pid, UNLIMITED_AMMO_TOTAL_LOCATION, UNLIMITED_AMMO_TOTAL_SIZE);
                uint8_t* magInstruction = getBytes(gta_sa_pid, UNLIMITED_AMMO_MAG_LOCATION, UNLIMITED_AMMO_MAG_SIZE);
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