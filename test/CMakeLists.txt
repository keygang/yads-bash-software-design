file(GLOB_RECURSE UNIT_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.test.cpp")

add_executable(unit_tests ${UNIT_TESTS})

include(${PROJECT_SOURCE_DIR}/thirdparty/googletest.cmake)
include(GoogleTest)

target_link_libraries(unit_tests
        bash-lib

        gtest_main
        )