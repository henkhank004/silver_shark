#include "data.hpp"
#include "simdjson.h"
#include <string_view>
#include <string>

std::expected<void, err::Error> silver::engine::data::import_items(IdTable<Item>& table, const std::string_view filepath) {
    simdjson::ondemand::parser parser;

    auto json = simdjson::padded_string::load(std::string(filepath));
    if (json.error()) {
        return std::unexpected(err::Error{err::FILE_LOAD_FAILED, "Failed to load JSON"});
    }

    auto doc = parser.iterate(json.value());
    if (doc.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to parse JSON"});
    }

    auto root_res = doc.get_object();
    if (root_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Root is not an object"});
    }
    auto root = root_res.value();

    auto items_val_res = root["items"];
    if (items_val_res.error()) {
        return std::unexpected(err::Error{err::ITEM_FIELD_MISSING, "\"items\" field missing"});
    }
    auto items_val = items_val_res.value();

    if (items_val.type() != simdjson::ondemand::json_type::array) {
        return std::unexpected(err::Error{err::INCORRECT_TYPE, "\"items\" is not an array"});
    }

    auto items_res = items_val.get_array();
    if (items_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to get items array"});
    }
    auto items = items_res.value();

    for (auto item : items) {
        auto key_name = item["key_name"].get_string();
        if (key_name.error()) continue;
        auto name = item["name"].get_string();
        if (name.error()) continue;
        table.intern(Item{
            static_cast<std::string>(key_name.value()),
            UNASSIGNED_ID,
            static_cast<std::string>(name.value())
            });
    }

    auto fluids_val_res = root["fluids"];
    if (fluids_val_res.error()) {
        return std::unexpected(err::Error{err::ITEM_FIELD_MISSING, "\"fluids\" field missing"});
    }
    auto fluids_val = fluids_val_res.value();

    if (fluids_val.type() != simdjson::ondemand::json_type::array) {
        return std::unexpected(err::Error{err::INCORRECT_TYPE, "\"fluids\" is not an array"});
    }

    auto fluids_res = fluids_val.get_array();
    if (items_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to get fluid array"});
    }
    auto fluids = fluids_res.value();

    for (auto item : fluids) {
        auto key_name = item["key_name"].get_string();
        if (key_name.error()) continue;
        auto name = item["name"].get_string();
        if (name.error()) continue;
        table.intern(Item{
            static_cast<std::string>(key_name.value()),
            UNASSIGNED_ID,
            static_cast<std::string>(name.value())
            });
    }

    return {};
}

std::expected<void, err::Error> silver::engine::data::import_machines(IdTable<Machine>& table, const std::string_view filepath) {
    simdjson::ondemand::parser parser;

    auto json = simdjson::padded_string::load(std::string(filepath));
    if (json.error()) {
        return std::unexpected(err::Error{err::FILE_LOAD_FAILED, "Failed to load JSON"});
    }

    auto doc = parser.iterate(json.value());
    if (doc.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to parse JSON"});
    }

    auto root_res = doc.get_object();
    if (root_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Root is not an object"});
    }
    auto root = root_res.value();

    auto buildings_val_res = root["buildings"];
    if (buildings_val_res.error()) {
        return std::unexpected(err::Error{err::ITEM_FIELD_MISSING, "\"buildings\" field missing"});
    }
    auto buildings_val = buildings_val_res.value();

    if (buildings_val.type() != simdjson::ondemand::json_type::array) {
        return std::unexpected(err::Error{err::INCORRECT_TYPE, "\"buildings\" is not an array"});
    }

    auto buildings_res = buildings_val.get_array();
    if (buildings_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to get buildings array"});
    }
    auto buildings = buildings_res.value();

    for (auto b : buildings) {
        auto key_name = b["key_name"].get_string();
        if (key_name.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED, "Parsing JSON failed at key_name for a machines."
            });

        auto name = b["name"].get_string();
        if (name.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse name from " + std::string(key_name.value())
            });

        auto sloop_slots_res = b["somersloop_slots"].get_int64();
        std::uint32_t sloop_slots = 0;
        if (!sloop_slots_res.error())
            sloop_slots = static_cast<std::int32_t>(sloop_slots_res.value());

        auto category = b["category"].get_string();
        if (category.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse category from " + std::string(key_name.value())
            });

        auto power_res = b["power"].get_int64();
        if (power_res.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse power from " + std::string(key_name.value())
            });

        std::uint32_t power = 0;
        if (power_res.error()) {
            auto power_range = b["power_range"].get_array();
            if (power_range.error())
                std::cout << "power range" << std::endl;
        } else
            power = static_cast<std::uint32_t>(power_res.value());

        table.intern(Machine{
                static_cast<std::string>(key_name.value()),
                UNASSIGNED_ID,
                static_cast<std::string>(name.value()),
                static_cast<std::string>(category.value()),
                power,
                sloop_slots
            });
    }

    auto miners_val_res = root["miners"];
    if (miners_val_res.error()) {
        return std::unexpected(err::Error{err::ITEM_FIELD_MISSING, "\"miners\" field missing"});
    }
    auto miners_val = miners_val_res.value();

    if (miners_val.type() != simdjson::ondemand::json_type::array) {
        return std::unexpected(err::Error{err::INCORRECT_TYPE, "\"miners\" is not an array"});
    }

    auto miners_res = miners_val.get_array();
    if (miners_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to get miners array"});
    }
    auto miners = miners_res.value();

    for (auto b : miners) {
        auto key_name = b["key_name"].get_string();
        if (key_name.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED, "Parsing JSON failed at key_name for a miner."
            });

        auto name = b["name"].get_string();
        if (name.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse name from " + std::string(key_name.value())
            });

        auto sloop_slots_res = b["somersloop_slots"].get_int64();
        std::uint32_t sloop_slots = 0;
        if (!sloop_slots_res.error())
            sloop_slots = static_cast<std::int32_t>(sloop_slots_res.value());

        auto category = b["category"].get_string();
        if (category.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse category from" + std::string(key_name.value())
            });

        auto power_res = b["power"].get_int64();
        if (power_res.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse power from " + std::string(key_name.value())
            });

        std::uint32_t power = 0;
        if (power_res.error()) {
            auto power_range = b["power_range"].get_array();
            if (power_range.error())
                std::cout << "power range" << std::endl;
        } else
            power = static_cast<std::uint32_t>(power_res.value());

        table.intern(Machine{
                static_cast<std::string>(key_name.value()),
                UNASSIGNED_ID,
                static_cast<std::string>(name.value()),
                static_cast<std::string>(category.value()),
                power,
                sloop_slots,
            });
    }


    return {};
}

std::expected<void, err::Error> silver::engine::data::import_recipes(IdTable<Recipe>& table, const IdTable<Machine>& machine_table, const std::string_view filepath) {
    simdjson::ondemand::parser parser;

    auto json = simdjson::padded_string::load(std::string(filepath));
    if (json.error()) {
        return std::unexpected(err::Error{err::FILE_LOAD_FAILED, "Failed to load JSON"});
    }

    auto doc = parser.iterate(json.value());
    if (doc.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to parse JSON"});
    }

    auto root_res = doc.get_object();
    if (root_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Root is not an object"});
    }
    auto root = root_res.value();

    auto recipes_val_res = root["recipes"];
    if (recipes_val_res.error()) {
        return std::unexpected(err::Error{err::ITEM_FIELD_MISSING, "\"recipes\" field missing"});
    }
    auto recipes_val = recipes_val_res.value();

    if (recipes_val.type() != simdjson::ondemand::json_type::array) {
        return std::unexpected(err::Error{err::INCORRECT_TYPE, "\"recipes\" is not an array"});
    }

    auto recipes_res = recipes_val.get_array();
    if (recipes_res.error()) {
        return std::unexpected(err::Error{err::JSON_PARSE_FAILED, "Failed to get recipes array"});
    }
    auto recipes = recipes_res.value();

    for (auto r : recipes) {
        auto key_name = r["key_name"].get_string();
        if (key_name.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED, "Parsing JSON failed at key_name for a machines."
            });

        auto name = r["name"].get_string();
        if (name.error())
            return std::unexpected(err::Error{
                err::JSON_PARSE_FAILED,
                "Could not parse name from " + std::string(key_name.value())
            });

        table.intern(Recipe{
                static_cast<std::string>(key_name.value()),
                UNASSIGNED_ID,
                static_cast<std::string>(name.value()),
            });
    }

    return {};
}

