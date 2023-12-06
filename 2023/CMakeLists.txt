cmake_minimum_required(VERSION 3.5.0)
project(adventofcode VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set(CLI11_PRECOMPILED true)
add_subdirectory(CLI11)

set(HEADER_FILES
    src/include/days.hpp
    src/include/days/Day1/Day1.hpp
    src/include/days/Day2/Day2.hpp
    src/include/days/Day3/Day3.hpp
    src/include/days/Day4/Day4.hpp
    src/include/days/Day5/Day5.hpp

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
include(CPack)

target_link_libraries(adventofcode PRIVATE $<$<BOOL:${MINGW}>:ws2_32> CLI11::CLI11)
target_compile_options(adventofcode PRIVATE -ffast-math -O3 -Wall -pipe -march=native)
set_property(TARGET adventofcode PROPERTY CXX_STANDARD 20)


add_custom_target(
    copy-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/input
        ${CMAKE_CURRENT_BINARY_DIR}/input
)

add_dependencies(adventofcode copy-files)