#pragma once
#include <optional>
#include <sys/types.h>

namespace Trainer {
	void printErrorMeaning(int err);
    std::optional<pid_t> getTargetPid();
}
