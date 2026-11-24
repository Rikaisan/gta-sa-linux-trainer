#include "process.hpp"
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/uio.h>

#include "util.hpp"

namespace Trainer {
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
}
