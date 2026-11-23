#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <sys/uio.h>

float_t* HEALTH_LOCATION = (float_t*)0x502af88;
float_t* ARMOR_LOCATION = (float_t*)0x502af90;
int32_t* MONEY_LOCATION = (int32_t*)0xb7ce50;

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

int main(int argc, char* argv[]) {
    pid_t gta_sa_pid = 64551;
    
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
    }
    return 0;
}