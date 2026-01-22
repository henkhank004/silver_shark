#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include "id_table.hpp"

namespace silver::engine {

class StringIdTable {
public:
    StringIdTable();

    std::uint32_t intern(std::string_view str);
    std::uint32_t find(std::string_view str) const;

    std::string_view to_string(std::uint32_t id) const;

    size_t size() const noexcept;

private:
    std::unordered_map<std::string, std::uint32_t> str_to_id_;
    std::vector<std::string> id_to_str_;
};

} // namespace silver::engine
