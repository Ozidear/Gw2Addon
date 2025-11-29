cmake_minimum_required(VERSION 3.16)

# Project name and language
set(PROJECT_NAME Gw2Addon)
project(${PROJECT_NAME} LANGUAGES CXX)

# Use C++ standard 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FetchContent for dependencies
include(FetchContent)

FetchContent_Declare(
    nexus_api
    GIT_REPOSITORY https://github.com/RaidcoreGG/RCGG-lib-nexus-api.git
    GIT_TAG v6.1
)
FetchContent_MakeAvailable(nexus_api)

add_library(nexus_api_lib INTERFACE)
target_include_directories(nexus_api_lib INTERFACE
    ${nexus_api_SOURCE_DIR}
)

# Create executable
add_executable(${PROJECT_NAME} main.cpp)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE
    nexus_api_lib
)

# -------------------------
# STATIC / DYNAMIC LINKING
# -------------------------
# Release  = static runtime
# Debug    = dynamic runtime (recommended)

if(MSVC)
    # MSVC: /MT for Release, /MD for Debug
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    # GCC / MinGW
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-static-libgcc -static-libstdc++>
    )
endif()

# -------------------------
# Output directory
# -------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)