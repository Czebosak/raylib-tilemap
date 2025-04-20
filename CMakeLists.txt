cmake_minimum_required(VERSION "3.19.2")

option(PRODUCTION_BUILD "Build in production mode" OFF)

project(RaylibTilemap)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_subdirectory("external/raylib")

add_executable(RaylibTilemap "${MY_SOURCES}")

if(PRODUCTION_BUILD)
target_compile_definitions(RaylibTilemap PRIVATE ASSETS_PATH="assets/")
target_compile_definitions(RaylibTilemap PRIVATE PROJECT_PATH="./")
else()
target_compile_definitions(RaylibTilemap PRIVATE PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")
target_compile_definitions(RaylibTilemap PRIVATE ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
endif()

target_include_directories(RaylibTilemap PRIVATE "src")
target_include_directories(RaylibTilemap PRIVATE "external/boost")

target_link_libraries(RaylibTilemap raylib)

if (UNIX)
    target_link_libraries(RaylibTilemap m pthread dl rt X11)
endif()

if(PRODUCTION_BUILD)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
endif()
