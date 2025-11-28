cmake_minimum_required(VERSION 3.16)

# Project name and language
set(PROJECT_NAME Gw2Addon)
project(${PROJECT_NAME} LANGUAGES CXX)

# Use C++ standard 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable from main.cpp
add_executable(${PROJECT_NAME} main.cpp)

# -------------------------
# STATIC LINKING SETTINGS
# -------------------------

# Force static linking of the runtime (MSVC / GCC)
if(MSVC)
    # /MT = static runtime, /MD = dynamic runtime
    foreach(flag_var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_DEBUG
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_DEBUG)
        string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endforeach()
else()
    # For GCC / MinGW: static link libstdc++ and libc++
    target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()

# -------------------------
# Output directory
# -------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
