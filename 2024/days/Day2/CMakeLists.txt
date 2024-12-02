cmake_minimum_required(VERSION 3.10.0)

find_package(CLI11 REQUIRED)

include_directories(include)
add_executable(day ${CMAKE_SOURCE_DIR}/main.cpp src/Day.cpp)

target_link_libraries(day PRIVATE $<$<BOOL:${MINGW}>:ws2_32> aoc CLI11::CLI11 pthread $<$<BOOL:${MINGW}>:tbb12>)
set_property(TARGET day PROPERTY CXX_STANDARD 23)
