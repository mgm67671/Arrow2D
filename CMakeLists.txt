cmake_minimum_required(VERSION 3.15)
project(Arrow2D)

set(CMAKE_CXX_STANDARD 17)

# Add all source files in the src directory
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Arrow2D ${SOURCES})

target_include_directories(Arrow2D PRIVATE src)

# --- Add these lines for SDL3 via vcpkg ---
find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(Arrow2D PRIVATE SDL3::SDL3)