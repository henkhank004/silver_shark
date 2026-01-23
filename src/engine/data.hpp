#pragma once

#include <expected>
#include "id_table.hpp"
#include "string_id_table.hpp"
#include "recipe.hpp"

namespace silver::engine::data {

    constexpr std::uint32_t UNASSIGNED_ID = 0;

    struct GameData {
        IdTable<Item> items;
        IdTable<Machine> machines;
        IdTable<Recipe> recipes;
        StringIdTable categories;
    };

    std::expected<GameData, err::Error> load_game_data(std::string_view path);

    std::expected<void, err::Error> import_items(IdTable<Item>& table, std::string_view filepath);
    std::expected<void, err::Error> import_buildings(IdTable<Machine>& table, StringIdTable& category_stringtable, std::string_view filepath);
    std::expected<void, err::Error> import_recipes(IdTable<Recipe>& table, const IdTable<Item>& item_table, StringIdTable& category_stringtable, std::string_view filepath);

}
