#include "graph.hpp"

#include <iostream>
#include <ostream>

silver::engine::graph::Graph::Graph(const data::GameData *game_data) : game_data_(game_data) {
    nodes_.reserve(128);
    edges_.reserve(128);

    nodes_.emplace_back(Node{next_node_id_++, 0, 0.0f});
    edges_.emplace_back(Edge{next_edge_id_++, 0, 0, 0, 0});
}

silver::engine::graph::NodeId silver::engine::graph::Graph::add_node(const RecipeId recipe, const float primary_rate) {
    Node n{next_node_id_++, recipe, primary_rate};

    auto res = game_data_->recipes.get_obj(recipe);
    if (!res) {
#ifndef NDEBUG
        std::cout << "Failed to retrieve recipe while initializing a graph node" << std::endl;
#endif
        return 0;
    }
    const auto* r = res.value();
    n.inputs.reserve(r->ingredients.size());
    n.outputs.reserve(r->products.size());

    nodes_.push_back(n);

    return n.id;
}

void silver::engine::graph::Graph::remove_node(const NodeId id) {
    nodes_.erase(nodes_.begin() + id);
}

silver::engine::graph::EdgeId silver::engine::graph::Graph::add_edge(const NodeId source, const std::uint32_t source_index, const NodeId target, const std::uint32_t target_index) {
    if (!can_connect(source, source_index, target, target_index))
        return 0;

    edges_.emplace_back(Edge{next_edge_id_++, source, source_index, target, target_index});
    return next_edge_id_ - 1;
}

void silver::engine::graph::Graph::remove_edge(const EdgeId id) {
    edges_.erase(edges_.begin() + id);
}

const silver::engine::graph::Node* silver::engine::graph::Graph::get_node(const NodeId id) const {
    return &nodes_.at(id);
}

bool silver::engine::graph::Graph::can_connect(const NodeId source, const std::uint32_t source_index, const NodeId target, const std::uint32_t target_index) const {
    auto source_recipe_res = game_data_->recipes.get_obj(nodes_.at(source).recipe_id);
    if (!source_recipe_res) {
#ifndef NDEBUG
        std::cerr << "Could not find source recipe while attempting to connect nodes: "
                    << source_recipe_res.error().msg << std::endl;
#endif
        return false;
    }

    auto target_recipe_res = game_data_->recipes.get_obj(nodes_.at(target).recipe_id);
    if (!target_recipe_res) {
#ifndef NDEBUG
        std::cerr << "Could not find target recipe while attempting to connect nodes: "
                    << target_recipe_res.error().msg << std::endl;
#endif
        return false;
    }

    const ItemId source_item = source_recipe_res.value()->products.at(source_index).first;
    if (source_item == 0) return false;
    const ItemId target_item = target_recipe_res.value()->ingredients.at(target_index).first;
    if (target_item == 0) return false;

    if (source_item == target_item)
        return true;
    return false;
}
