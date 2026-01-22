cmake_minimum_required(VERSION 4.1)
project(silver_shark)

set(CMAKE_CXX_STANDARD 26)

add_executable(silver_shark src/main.cpp
        src/engine/item.hpp
        src/engine/data.hpp
        src/engine/data.cpp
        src/error/error.hpp
        src/engine/id_table.hpp
        src/engine/recipe.hpp
        src/engine/machine.hpp
        src/engine/string_id_table.cpp)

target_include_directories(silver_shark PRIVATE /usr/include)
target_link_libraries(silver_shark PRIVATE simdjson)