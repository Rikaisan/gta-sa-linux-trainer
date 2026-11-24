#pragma once
#include <cstdint>
#include <sys/types.h>

namespace Trainer {
	uint8_t* getBytes(pid_t pid, uint8_t* location, size_t size);
    bool setBytes(pid_t pid, uint8_t* location, uint8_t* newValue, size_t size);
}
