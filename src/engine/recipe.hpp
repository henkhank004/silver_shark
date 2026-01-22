#pragma once

#include "item.hpp"
#include "machine.hpp"
#include <vector>

namespace silver {
    using RecipeId = std::uint32_t;
    using CategoryId = std::uint32_t;
    using RecipeCategory = std::string;

    struct Recipe {
        std::string key_name;
        RecipeId id;
        std::string name;
        CategoryId category;
        float time;
        std::vector<std::pair<ItemId, float>> ingredients;
        std::vector<std::pair<ItemId, float>> products;
    };

}
