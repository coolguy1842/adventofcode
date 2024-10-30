cmake_minimum_required(VERSION 3.5.0)
project(aoc VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB UTIL_SRC
    "src/*.cpp"
    "src/**/*.cpp"
)

list(REMOVE_ITEM UTIL_SRC src/main.cpp)

add_subdirectory(thirdparty/scnlib)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(aoc SHARED ${UTIL_SRC})
target_include_directories(aoc PUBLIC include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(FetchContent)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -pipe -g3 -O0 -DDEBUG -static")
set(CMAKE_C_FLAGS_DEBUG_INIT "-Wall -pipe -g3 -O0 -DDEBUG -static")
# set(CMAKE_CXX_FLAGS_RELEASE_INIT "-ffast-math -O3 -Wall -pipe -march=native -static")
# set(CMAKE_C_FLAGS_RELEASE_INIT "-ffast-math -O3 -Wall -pipe -march=native -static")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-ffast-math -O3 -g3 -Wall -pipe -march=native -static")
set(CMAKE_C_FLAGS_RELEASE_INIT "-ffast-math -O3 -g3 -Wall -pipe -march=native -static")

target_link_libraries(aoc PUBLIC scn::scn spdlog::spdlog nlohmann_json::nlohmann_json)
target_link_libraries(aoc PRIVATE $<$<BOOL:${MINGW}>:ws2_32> pthread $<$<BOOL:${MINGW}>:tbb12>)
set_property(TARGET aoc PROPERTY CXX_STANDARD 23)

set(DAYS_PATH ${PROJECT_SOURCE_DIR}/days)
file(GLOB DAYS_LIST
    "days/*/"
)

if(${DAYS_PATH}/Day${DAY} IN_LIST DAYS_LIST)
    add_subdirectory(${DAYS_PATH}/Day${DAY})
else()
    message(WARNING "No day specified, using most recent")

    list(LENGTH DAYS_LIST length)
    if(length GREATER 0)
        list(GET DAYS_LIST -1 last_item)
        add_subdirectory(${last_item})
    else()
        message(FATAL_ERROR "Day not found")
    endif()
endif()