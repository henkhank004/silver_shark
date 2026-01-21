#include "string_id_table.hpp"

namespace silver::engine {

    StringIdTable::StringIdTable() {
        // reserve index 0 for anything invalid
        id_to_str_.emplace_back("");
    }

    std::uint32_t StringIdTable::intern(std::string_view str) {
        const auto it = str_to_id_.find(std::string(str));
        if (it != str_to_id_.end()) {
            return it->second;
        }

        auto id = static_cast<std::uint32_t>(id_to_str_.size());
        id_to_str_.emplace_back(str);
        str_to_id_.emplace(id_to_str_.back(), id);
        return id;
    }

    std::uint32_t StringIdTable::find(const std::string_view str) const {
        const auto it = str_to_id_.find(std::string(str));
        return (it != str_to_id_.end()) ? it->second : INVALID_ID;
    }

    std::string_view StringIdTable::to_string(const std::uint32_t id) const {
        return id_to_str_[id];
    }

    std::size_t StringIdTable::size() const noexcept {
        return id_to_str_.size() - 1;
    }

}
