cmake_minimum_required(VERSION 3.16)

# Project name and language
set(PROJECT_NAME Gw2Addon)
project(${PROJECT_NAME} LANGUAGES CXX)

# Use C++ standard 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable
add_executable(${PROJECT_NAME} main.cpp)

# -------------------------
# STATIC / DYNAMIC LINKING
# -------------------------
# Release  = static runtime
# Debug    = dynamic runtime (recommended)

if(MSVC)
    # MSVC: /MT for Release, /MD for Debug
    # CMake 3.15+ has a built-in variable for this:
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    # GCC / MinGW
    # Static link *only for Release*
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