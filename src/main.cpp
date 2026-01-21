#include <iostream>
#include "engine/data.hpp"

#define DATAFILE "/home/daan/CLionProjects/silver_shark/src/data/data.json"

int main() {
    silver::engine::IdTable<silver::Item> item_table;

    auto res_import_items = silver::engine::data::import_items(item_table, DATAFILE);
    if (!res_import_items) {
        std::cerr << "Error importing items: " << res_import_items.error().msg << std::endl;
        return res_import_items.error().code;
    }

    auto res = item_table.get_obj(1);
    if (!res) {
        std::cerr << "Error in get_obj: " << res.error().msg << std::endl;
        return res.error().code;
    }
    const silver::Item* it = res.value();

    std::cout << it->name << " (" << it->key_name << ", " << it->id << ")" << std::endl;

    return 0;
}