#include "process.hpp"
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/uio.h>

#include "util.hpp"


// Not working at the moment (even with sudo), program code is protected, so will need to attach to the proces with ptrace, probably.
namespace Trainer {    
	bool getBytes(pid_t pid, uintptr_t location, uint8_t* buffer, size_t size) {
        struct iovec local[1], remote[1];
        local->iov_base = buffer;
        local->iov_len = size;
        remote->iov_base = (uint8_t*)location;
        remote->iov_len = size;
        int nread = process_vm_readv(pid, local, 1, remote, 1, 0);
        if (nread == -1) {
            printf("Error while reading address: %p\n", (uint8_t*)location);
            printErrorMeaning(errno);
            return false;
        }
        return true;
    }

    bool setBytes(pid_t pid, uintptr_t location, uint8_t* newValue, size_t size) {
        struct iovec local[1], remote[1];
        local->iov_base = newValue;
        local->iov_len = size;
        remote->iov_base = (uint8_t*)location;
        remote->iov_len = size;
        int nwrite = process_vm_writev(pid, local, 1, remote, 1, 0);
        if (nwrite == -1) {
            printf("Error while writing address: %p\n", (uint8_t*)location);
            printErrorMeaning(errno);
            return false;
        }
        return true;
    }
}
