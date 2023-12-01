cmake_minimum_required(VERSION 3.5.0)
project(adventofcode VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
# include(cotire)


set(HEADER_FILES
	thirdparty/robin_hood.hpp
    thirdparty/argparse/argparse.hpp

    src/include/days.hpp
    src/include/days/Day1/Day1.hpp

    include/util/linkedList.hpp
    include/util/stringUtil.hpp
    include/day.hpp
    include/timer.hpp
)


set(SOURCE_FILES
	src/main.cpp
	${HEADER_FILES}
)

include_directories(include src/include thirdparty)
add_executable(adventofcode ${SOURCE_FILES})
target_precompile_headers(adventofcode PRIVATE ${HEADER_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(spdlog REQUIRED)
target_link_libraries(adventofcode PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)


target_compile_options(adventofcode PRIVATE -ffast-math -O3 -Wall -pipe)
set_property(TARGET adventofcode PROPERTY CXX_STANDARD 20)

file(COPY input DESTINATION ${CMAKE_BINARY_DIR})