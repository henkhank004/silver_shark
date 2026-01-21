#pragma once

#include <expected>
#include "string_id_table.hpp"
#include "id_table.hpp"
#include "recipe.hpp"

namespace silver::engine::data {

    constexpr std::uint32_t UNASSIGNED_ID = 0;

    std::expected<void, err::Error> import_items(IdTable<Item>& table, std::string_view filepath);
    std::expected<void, err::Error> import_recipes(IdTable<Recipe>& table, std::string_view filepath);

}
