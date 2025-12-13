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

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.22.0
)
FetchContent_MakeAvailable(httplib)

# -------------------------
# Executable
# -------------------------
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nexus_api_lib
    httplib::httplib
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