cmake_minimum_required(VERSION 3.5.0)
project(adventofcode VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(include src/include)
add_executable(adventofcode src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
