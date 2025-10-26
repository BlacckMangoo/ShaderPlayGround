#pragma once
#include <cstdint>

[[nodiscard]] inline int GenerateId() noexcept {
    static int id = 0;
    return id++;
}
