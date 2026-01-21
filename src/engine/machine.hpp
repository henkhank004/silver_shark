#pragma once

#include "item.hpp"

namespace silver::engine {
    using MachineId = std::uint32_t;

    struct Machine {
        std::string key_name;
        MachineId id;
        std::string name;
        std::uint32_t power;
        std::uint32_t sloop_slots;
    };

} // namespace silver::engine
