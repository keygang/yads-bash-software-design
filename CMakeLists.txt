cmake_minimum_required(VERSION 3.10)

option(BASH_TESTING "Enabling testing" ON)
option(CODECOVERAGE "Enabling code coverage" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

project(bash)

include(FetchContent)

if(CODECOVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Add required flags (GCC & LLVM/Clang)
    add_library(coverage_config INTERFACE)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )

    target_link_options(coverage_config INTERFACE --coverage)
endif()

include_directories(src)
add_subdirectory(src)

if(BASH_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
