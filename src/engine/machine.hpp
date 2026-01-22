#pragma once
#include "recipe.hpp"

namespace silver {
    struct Machine {
        std::string key_name;
        std::uint32_t id;
        std::string name;
        std::uint32_t category;
        std::uint32_t power;
        std::uint32_t sloop_slots;
    };

}
