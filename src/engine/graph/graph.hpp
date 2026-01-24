#pragma once
#include <unordered_map>

#include "edge.hpp"
#include "node.hpp"
#include "engine/data.hpp"
#include "engine/recipe.hpp"


namespace silver::engine::graph {

    class Graph {
    public:
        Graph(const data::GameData* game_data);

        NodeId add_node(RecipeId recipe, float primary_rate);
        void remove_node(NodeId id);

        EdgeId add_edge(NodeId source, std::uint32_t source_index, NodeId target, std::uint32_t target_index);
        void remove_edge(EdgeId id);

        const Node* get_node(NodeId id) const;

    private:
        const data::GameData* game_data_;

        NodeId next_node_id_ = 0;
        EdgeId next_edge_id_ = 0;

        std::vector<Node> nodes_;
        std::vector<Edge> edges_;

        bool can_connect(NodeId source, std::uint32_t source_index, NodeId target, std::uint32_t target_index) const;
    };

}
