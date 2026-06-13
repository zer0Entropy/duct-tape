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

add_library(duct_tape STATIC test/src/duct-tape.cpp
            src/utilities/window.cpp)

target_link_libraries(duct_tape
    PRIVATE
        SFML::Audio
        SFML::Graphics
)

add_executable(duct_tape_test
        test/src/main.cpp
        test/include/utilities/window.hpp
        test/include/result.hpp
        test/include/test.hpp
        test/src/test.cpp
        test/src/utilities/window.cpp)
target_sources(duct_tape_test
    PRIVATE
        test/src/main.cpp
        test/src/duct-tape.cpp
)
target_link_libraries(duct_tape_test
    PRIVATE
        SFML::Audio
        SFML::Graphics
        duct_tape)