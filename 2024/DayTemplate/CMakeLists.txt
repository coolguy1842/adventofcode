cmake_minimum_required(VERSION 3.5.0)
project(day VERSION 0.1.0 LANGUAGES C CXX)

add_compile_definitions(INPUT_PATH="${PROJECT_SOURCE_DIR}/input.txt")
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB UTIL_SRC
    "../src/*.cpp"
)

find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)

include_directories(../include src)
add_executable(day ${UTIL_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(day PRIVATE spdlog::spdlog CLI11::CLI11 $<$<BOOL:${MINGW}>:ws2_32>)