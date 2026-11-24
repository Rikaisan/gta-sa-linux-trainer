#pragma once
#include <cstdint>
#include <sys/types.h>

namespace Trainer {
	bool getBytes(pid_t pid, uintptr_t location, uint8_t* buffer, size_t size);
    bool setBytes(pid_t pid, uintptr_t location, uint8_t* value, size_t size);
}
