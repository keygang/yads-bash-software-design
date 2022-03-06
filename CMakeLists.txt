cmake_minimum_required(VERSION 3.10)

option(BASH_TESTING "Enabling testing" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

project(bash)

include(FetchContent)

include_directories(src)
add_subdirectory(src)

if(BASH_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
