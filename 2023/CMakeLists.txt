cmake_minimum_required(VERSION 3.5.0)
project(adventofcode VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set(HEADER_FILES
    src/include/days.hpp
    src/include/days/Day1/Day1.hpp

    include/util/linkedList.hpp
    include/util/stringUtil.hpp
    include/day.hpp
    include/timer.hpp

    include/robin_hood.hpp
)

set(SOURCE_FILES
	src/main.cpp
	${HEADER_FILES}
)

include_directories(include src/include)
add_executable(adventofcode ${SOURCE_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)

FetchContent_MakeAvailable(argparse)


find_package(spdlog REQUIRED)

target_link_libraries(adventofcode PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> argparse)
target_compile_options(adventofcode PRIVATE -ffast-math -O3 -Wall -pipe -march=native)
set_property(TARGET adventofcode PROPERTY CXX_STANDARD 20)


add_custom_target(
    copy-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/input
        ${CMAKE_CURRENT_BINARY_DIR}/input
)

add_dependencies(adventofcode copy-files)