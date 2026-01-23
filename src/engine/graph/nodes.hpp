#pragma once

#include <vector>
#include <cstdint>

namespace silver::engine::graph {
    using NodeId = uint32_t;

    struct Port {
        std::uint32_t item_id;
        float items_per_minute;
    };

    struct Node {
        NodeId id;
        std::uint32_t recipe_id;

        std::vector<Port> inputs;
        std::vector<Port> outputs;
    };

}