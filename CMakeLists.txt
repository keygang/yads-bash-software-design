cmake_minimum_required(VERSION 3.10)

option(BASH_TESTING "Enabling testing" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(CXX_FILESYSTEM_LIBRARIES "stdc++fs")

project(bash)

include(FetchContent)

add_subdirectory(src)

if(BASH_TESTING)
    message(Testing)
    enable_testing()
    add_subdirectory(test)
endif()
