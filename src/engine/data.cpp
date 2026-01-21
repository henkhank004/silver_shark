#include "data.hpp"
#include "simdjson.h"
#include <string_view>
#include <string>

std::expected<void, err::Error> silver::engine::data::import_items(silver::engine::IdTable<Item>& table, const std::string_view filepath) {
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


