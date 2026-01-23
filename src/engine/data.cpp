#include "data.hpp"
#include "simdjson.h"
#include <string_view>
#include <string>


std::expected<silver::engine::data::GameData, err::Error> silver::engine::data::load_game_data(const std::string_view path) {
    IdTable<Item>       item_table;
    IdTable<Machine>    machine_table;
    StringIdTable       category_stringtable;
    IdTable<Recipe>     recipe_table;

    auto import_items_res = import_items(item_table, path);
    if (!import_items_res)
        return std::unexpected(import_items_res.error());

    auto import_machines_res = import_buildings(machine_table, category_stringtable, path);
    if (!import_machines_res)
        return std::unexpected(import_machines_res.error());

    auto import_recipes_res = import_recipes(recipe_table, item_table, category_stringtable, path);
    if (!import_recipes_res)
        return std::unexpected(import_recipes_res.error());

    return GameData{
        std::move(item_table),
        std::move(machine_table),
        std::move(recipe_table),
        std::move(category_stringtable)
    };
}


std::expected<void, err::Error> silver::engine::data::import_items(IdTable<Item>& table, const std::string_view filepath) {
    simdjson::dom::parser parser;
    simdjson::dom::element doc;

    if (parser.load(std::string(filepath)).get(doc))
        return std::unexpected(err::Error{err::FILE_LOAD_FAILED, "Failed to load JSON"});

    simdjson::dom::object root;
    if (doc.get(root))
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Root is not an object"});

    simdjson::dom::array items;
    if (root["items"].get(items))
        return std::unexpected(err::Error{err::JSON_FIELD_MISSING, "\"items\" field missing"});

    for (auto item : items) {
        simdjson::dom::object obj;
        if (item.get(obj)) continue;

        std::string_view key_name;
        std::string_view name;

        if (obj["key_name"].get(key_name)) continue;
        if (obj["name"].get(name)) continue;

        table.intern(Item{
            std::string(key_name),
            UNASSIGNED_ID,
            std::string(name)
        });
    }

    simdjson::dom::array fluids;
    if (root["fluids"].get(fluids)) {
        return std::unexpected(err::Error{err::JSON_FIELD_MISSING, "\"fluids\" field missing"});
    }

    for (simdjson::dom::element item : fluids) {
        simdjson::dom::object obj;
        if (item.get(obj)) continue;

        std::string_view key_name;
        std::string_view name;

        if (obj["key_name"].get(key_name)) continue;
        if (obj["name"].get(name)) continue;

        table.intern(Item{
            std::string(key_name),
            UNASSIGNED_ID,
            std::string(name)
        });
    }

    return {};
}


std::expected<void, err::Error> silver::engine::data::import_buildings(IdTable<Machine>& table, StringIdTable& category_stringtable, const std::string_view filepath) {
    simdjson::dom::parser parser;
    simdjson::dom::element doc;

    if (parser.load(std::string(filepath)).get(doc))
        return std::unexpected(err::Error{err::FILE_LOAD_FAILED, "Failed to load JSON"});

    simdjson::dom::object root;
    if (doc.get(root))
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Root is not an object"});

    simdjson::dom::array buildings;
    if (root["buildings"].get(buildings))
        return std::unexpected(err::Error{err::JSON_FIELD_MISSING, "\"buildings\" field missing"});

    for (auto b : buildings) {
        simdjson::dom::object obj;
        if (b.get(obj)) continue;

        std::string_view key_name;
        if (obj["key_name"].get(key_name))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Parsing JSON failed at key_name for a machines."
            });

        std::string_view name;
        if (obj["name"].get(name))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse name from " + std::string(key_name)
            });

        std::int64_t sloop_slots_val = 0;
        obj["somersloop_slots"].get(sloop_slots_val);
        auto sloop_slots = static_cast<std::uint32_t>(sloop_slots_val);

        std::string_view category_str;
        if (obj["category"].get(category_str))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse category from " + std::string(key_name)
            });
        auto category = category_stringtable.intern(category_str);

        std::int64_t power_val = 0;
        if (obj["power"].get(power_val)) {
            simdjson::dom::array power_range;
            if (obj["power_range"].get(power_range)) {
                std::cout << "power range" << std::endl;
            }
        }

        table.intern(Machine{
            std::string(key_name),
            UNASSIGNED_ID,
            std::string(name),
            category,
            static_cast<std::uint32_t>(power_val),
            sloop_slots
        });
    }

    simdjson::dom::array miners;
    if (root["miners"].get(miners)) {
        return std::unexpected(err::Error{err::JSON_FIELD_MISSING, "\"miners\" field missing"});
    }

    for (simdjson::dom::element b : miners) {
        simdjson::dom::object obj;
        if (b.get(obj)) continue;

        std::string_view key_name;
        if (obj["key_name"].get(key_name)) {
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Parsing JSON failed at key_name for a miner."
            });
        }

        std::string_view name;
        if (obj["name"].get(name)) {
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse name from " + std::string(key_name)
            });
        }

        std::int64_t sloop_slots_val = 0;
        obj["somersloop_slots"].get(sloop_slots_val);

        std::string_view category_str;
        if (obj["category"].get(category_str)) {
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse category from " + std::string(key_name)
            });
        }
        auto category = category_stringtable.intern(category_str);

        std::int64_t power_val = 0;
        if (obj["power"].get(power_val)) {
            simdjson::dom::array power_range;
            if (obj["power_range"].get(power_range)) {
                std::cout << "power range" << std::endl;
            }
        }

        table.intern(Machine{
            std::string(key_name),
            UNASSIGNED_ID,
            std::string(name),
            category,
            static_cast<std::uint32_t>(power_val),
            static_cast<std::uint32_t>(sloop_slots_val)
        });
    }

    return {};
}


std::expected<void, err::Error> silver::engine::data::import_recipes(IdTable<Recipe>& table, const IdTable<Item>& item_table, StringIdTable& category_stringtable, const std::string_view filepath) {
    simdjson::dom::parser parser;
    simdjson::dom::element doc;

    if (parser.load(std::string(filepath)).get(doc))
        return std::unexpected(err::Error{err::FILE_LOAD_FAILED, "Failed to load JSON"});

    simdjson::dom::object root;
    if (doc.get(root))
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Root is not an object"});

    simdjson::dom::array recipes;
    if (root["recipes"].get(recipes))
        return std::unexpected(err::Error{err::JSON_FIELD_MISSING, "\"recipes\" field missing"});

    for (auto r : recipes) {
        simdjson::dom::object obj;
        if (r.get(obj)) continue;

        std::string_view key_name;
        if (obj["key_name"].get(key_name))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Parsing JSON failed at key_name for a recipe"
            });

        std::string_view name;
        if (obj["name"].get(name))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse name from " + std::string(key_name)
            });

        std::string_view category_str;
        if (obj["category"].get(category_str))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse category from " + std::string(key_name)
            });
        auto category = category_stringtable.intern(category_str);

        double time_val = 0.0;
        if (obj["time"].get(time_val))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse time from " + std::string(key_name)
            });

        simdjson::dom::array ingredients_arr;
        if (obj["ingredients"].get(ingredients_arr))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse ingredients from " + std::string(key_name)
            });

        std::vector<std::pair<std::uint32_t, float>> ingredients;

        for (simdjson::dom::element e : ingredients_arr) {
            simdjson::dom::array entry;
            if (e.get(entry))
                return std::unexpected(err::Error{
                    err::JSON_PARSE_FAILED,
                    "Could not parse ingredients from " + std::string(key_name) + " failed at entry (1) reading"
                });

            std::string_view item_key;
            double item_count;

            if (entry.at(0).get(item_key) || entry.at(1).get(item_count))
                return std::unexpected(err::Error{
                    err::JSON_PARSE_FAILED,
                    "Could not parse ingredients from " + std::string(key_name) + " failed at entry (2) reading"
                });

            ingredients.emplace_back(
                item_table.find(item_key),
                static_cast<float>(item_count)
            );
        }

        simdjson::dom::array products_arr;
        if (obj["products"].get(products_arr))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse products from " + std::string(key_name) + " failed at products array reading"
            });

        std::vector<std::pair<std::uint32_t, float>> products;

        for (simdjson::dom::element e : products_arr) {
            simdjson::dom::array entry;
            if (e.get(entry))
                return std::unexpected(err::Error{
                    err::JSON_PARSE_FAILED,
                    "Could not parse products from " + std::string(key_name) + " failed at key reading"
                });

            std::string_view item_key;
            double item_count;

            if (entry.at(0).get(item_key) || entry.at(1).get(item_count))
                return std::unexpected(err::Error{
                    err::JSON_PARSE_FAILED,
                    "Could not parse products from " + std::string(key_name) + " failed at key or count reading"
                });

            products.emplace_back(
                item_table.find(item_key),
                static_cast<float>(item_count)
            );
        }

        table.intern(Recipe{
            std::string(key_name),
            UNASSIGNED_ID,
            std::string(name),
            category,
            static_cast<float>(time_val),
            ingredients,
            products
        });
    }

    simdjson::dom::array resources;
    if (root["resources"].get(resources))
        return std::unexpected(err::Error{err::JSON_FIELD_MISSING, "\"resources\" field missing"});

    for (auto r : resources) {
        simdjson::dom::object obj;
        if (r.get(obj)) continue;

        std::string_view key_name;
        if (obj["key_name"].get(key_name))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Parsing JSON failed at key_name for a resource"
            });

        std::string_view category_str;
        if (obj["category"].get(category_str))
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse category from " + std::string(key_name)
            });
        auto category = category_stringtable.intern(category_str);
        std::vector<std::pair<std::uint32_t, float>> products;
        products.emplace_back(std::pair{item_table.find(key_name), 1.0f});

        auto item = item_table.get_obj(key_name);
        std::string name;
        if (!item)
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Item \"" + std::string(key_name) + "\"does not exist"
            });
        else
            name = item.value()->name;

        table.intern(Recipe{
            std::string(key_name),
            UNASSIGNED_ID,
            name,
            category,
            0.0f,
            std::vector<std::pair<std::uint32_t, float>>{},
            products
        });
    }

    return {};
}