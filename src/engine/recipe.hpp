#pragma once

#include "item.hpp"
#include "machine.hpp"

namespace silver {
    using RecipeId = std::uint32_t;
    using RecipeCategory = std::string;
    using CategoryId = std::uint32_t;

    struct Recipe {
        std::string key_name;
        RecipeId id;
        std::string name;
        CategoryId category;
        std::uint32_t time;
        std::vector<std::pair<ItemId, std::uint32_t>> ingredients;
        std::vector<std::pair<ItemId, std::uint32_t>> products;
    };

}
