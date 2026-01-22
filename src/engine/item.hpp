#pragma once

#include <cstdint>
#include <string>

namespace silver {
    using ItemId = std::uint32_t;

    struct Item {
        std::string key_name;
        ItemId id;
        std::string name;
    };

}
