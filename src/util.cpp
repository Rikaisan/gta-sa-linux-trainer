#include "util.hpp"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Trainer {
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
}
