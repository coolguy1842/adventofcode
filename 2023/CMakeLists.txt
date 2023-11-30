cmake_minimum_required(VERSION 3.5.0)
project(adventofcode VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory("include")

include(CTest)
enable_testing()

include_directories(include src/include)
add_executable(adventofcode src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(spdlog REQUIRED)

target_include_directories(adventofcode PRIVATE spdlog::spdlog)
target_link_libraries(adventofcode PRIVATE headers spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

file(COPY input DESTINATION ${CMAKE_BINARY_DIR})