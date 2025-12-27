cmake_minimum_required(VERSION 3.16)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
    set(OPENSSL_USE_STATIC_LIBS TRUE)
else()
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
endif()

set(PROJECT_NAME Gw2Addon)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        CACHE STRING "" FORCE
    )
endif()

# OpenSSL
find_package(OpenSSL REQUIRED)

include(FetchContent)

# Nexus API
FetchContent_Declare(
    nexus_api_src
    GIT_REPOSITORY https://github.com/RaidcoreGG/RCGG-lib-nexus-api.git
    GIT_TAG v6.1
)
FetchContent_MakeAvailable(nexus_api_src)

add_library(nexus_api INTERFACE)
target_include_directories(nexus_api INTERFACE
    ${nexus_api_src_SOURCE_DIR}
)

# cpp-httplib
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.28.0
)
FetchContent_MakeAvailable(httplib)

# Change to SHARED library in Release, executable otherwise
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_library(${PROJECT_NAME} SHARED src/main.cpp)
else()
    add_executable(${PROJECT_NAME} src/main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    nexus_api
    httplib::httplib
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)