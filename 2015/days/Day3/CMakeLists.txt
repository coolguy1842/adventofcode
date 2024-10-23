cmake_minimum_required(VERSION 3.5.0)

add_compile_definitions(INPUT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

find_package(CLI11 REQUIRED)
find_package(glm REQUIRED)

include_directories(src)
add_executable(day ../../main.cpp)

target_link_libraries(day PRIVATE $<$<BOOL:${MINGW}>:ws2_32> aoc glm CLI11::CLI11 pthread $<$<BOOL:${MINGW}>:tbb12>)
set_property(TARGET day PROPERTY CXX_STANDARD 23)
