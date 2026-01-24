cmake_minimum_required(VERSION 3.26)

project(silver_shark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(simdjson REQUIRED)

add_executable(silver_shark
        src/main.cpp
        src/engine/data.cpp
        src/engine/string_id_table.cpp
        src/engine/graph/graph.cpp
        src/ui/main_window.hpp
        src/ui/main_window.cpp
        src/engine/graph/node.hpp
        src/engine/graph/graph.hpp
        src/ui/graph/machine_node_item.cpp
        src/ui/graph/machine_node_item.hpp
        src/ui/graph/port_direction.hpp
        src/ui/graph/port_item.cpp
        src/ui/graph/port_item.hpp
        src/ui/graph_view.cpp
        src/ui/graph_view.hpp
        src/ui/float_input_widget.cpp
        src/ui/float_input_widget.hpp
        src/engine/graph/edge.hpp
)

target_include_directories(silver_shark
        PRIVATE
        src
)

target_link_libraries(silver_shark
        PRIVATE
        Qt6::Widgets
        simdjson::simdjson
)
