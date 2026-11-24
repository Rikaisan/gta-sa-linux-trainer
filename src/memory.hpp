#pragma once
#include <cstdio>
#include <cerrno>
#include <sys/uio.h>

#include "util.hpp"

namespace Trainer {
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
}
