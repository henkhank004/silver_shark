#pragma once

#include "recipe.hpp"

namespace silver {
    using MachineId = std::uint32_t;

    struct Machine {
        std::string key_name;
        MachineId id;
        std::string name;
        CategoryId category;
        std::uint32_t power;
        std::uint32_t sloop_slots;
    };

}
