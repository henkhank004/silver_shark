#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <expected>
#include "../error/error.hpp"

namespace silver::engine {
    constexpr std::uint32_t INVALID_ID = 0;

    template<typename T>
    concept IdTableEntry = requires(T t) {
        { t.key_name } -> std::convertible_to<std::string>;
        { t.id } -> std::convertible_to<std::uint32_t>;
    };

    template<IdTableEntry T>
    class IdTable {
    public:
        IdTable() {
            // reserve index 0 for invalid entries
            id_to_T_.emplace_back(T{});
        }

        std::uint32_t intern(T entry) {
            const auto it = key_to_id_.find(entry.key_name);
            if (it != key_to_id_.end()) {
                return it->second;
            }

            const auto id = static_cast<std::uint32_t>(id_to_T_.size());

            entry.id = id;
            id_to_T_.emplace_back(std::move(entry));

            key_to_id_.emplace(id_to_T_.back().key_name, id);

            return id;
        }

        std::uint32_t find(std::string_view key_name) const {
            auto it = key_to_id_.find(std::string{key_name});
            return it != key_to_id_.end() ? it->second : INVALID_ID;
        }

        std::expected<const T*, err::Error> get_obj(std::uint32_t id) const {
            if (id == INVALID_ID || id >= id_to_T_.size()) {
                return std::unexpected(err::Error{
                    err::OUT_OF_BOUNDS,
                    "Invalid IdTable id"
                });
            }
            return &id_to_T_[id];
        }

        size_t entry_count() const {
            return id_to_T_.size();
        }

    private:
        std::unordered_map<std::string, std::uint32_t> key_to_id_;
        std::vector<T> id_to_T_;
    };

}
