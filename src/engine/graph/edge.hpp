#pragma once

#include <vector>
#include <cstdint>

#include "node.hpp"

namespace silver::engine::graph {
    using EdgeId = std::uint32_t;

    struct Edge {
        EdgeId id;

        NodeId source;
        std::uint32_t source_port_index;

        NodeId target;
        std::uint32_t target_port_index;
    };

}
