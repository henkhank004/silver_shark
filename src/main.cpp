#include <iostream>
#include "engine/data.hpp"

#define DATAFILE "/home/daan/CLionProjects/silver_shark/src/data/data.json"

int main() {
    silver::engine::IdTable<silver::Item>       item_table;
    silver::engine::IdTable<silver::Machine>    machine_table;
    silver::engine::StringIdTable               category_stringtable;
    silver::engine::IdTable<silver::Recipe>     recipe_table;

    {
        auto res_import_items = silver::engine::data::import_items(item_table, DATAFILE);
        if (!res_import_items) {
            std::cerr << "Error importing items: " << res_import_items.error().msg << std::endl;
            return res_import_items.error().code;
        }
    }

    {
        auto res_import_machines = silver::engine::data::import_buildings(machine_table, category_stringtable, DATAFILE);
        if (!res_import_machines) {
            std::cerr << "Error importing buildings: " << res_import_machines.error().msg << std::endl;
            return res_import_machines.error().code;
        }
    }

    {
        auto res_import_recipes = silver::engine::data::import_recipes(recipe_table, item_table, category_stringtable, DATAFILE);
        if (!res_import_recipes) {
            std::cerr << "Error importing recipes: " << res_import_recipes.error().msg << std::endl;
            return res_import_recipes.error().code;
        }
    }

    return 0;
}