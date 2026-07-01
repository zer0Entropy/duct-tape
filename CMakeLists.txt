cmake_minimum_required(VERSION 4.0)
project(duct_tape)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(SFML json)

add_library(duct_tape
            STATIC
                include/common/init.hpp
                include/common/shutdown.hpp
                include/common/test.hpp
                include/core/engine-test.hpp
                include/core/event.hpp
                include/core/game.hpp
                include/core/input.hpp
                include/core/player.hpp
                include/utilities/window-test.hpp
                include/world/level.hpp
                include/world/creature.hpp
                include/world/tile.hpp
                include/world/world.hpp
                src/common/test.cpp
                src/core/engine.cpp
                src/core/engine-test.cpp
                src/core/input.cpp
                src/utilities/window.cpp
                src/utilities/window-test.cpp
)

target_link_libraries(duct_tape
    PRIVATE
        SFML::Audio
        SFML::Graphics
)

add_executable(dt_test src/main.cpp)

target_link_libraries(dt_test
    PRIVATE
        SFML::Audio
        SFML::Graphics
        duct_tape
)