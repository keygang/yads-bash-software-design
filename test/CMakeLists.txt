include(${PROJECT_SOURCE_DIR}/thirdparty/googletest.cmake)
include(GoogleTest)

file(GLOB_RECURSE UNIT_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.test.cpp")

add_executable(unit_tests ${UNIT_TESTS} ${CMAKE_CURRENT_SOURCE_DIR}/unit/fixtures/utils.hpp)

target_compile_definitions(unit_tests PRIVATE -DFIXTURES_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/unit/fixtures/")

gtest_add_tests(TARGET unit_tests SOURCES ${UNIT_TESTS} TEST_LIST tests)
set_tests_properties(${tests} PROPERTIES TIMEOUT 1)

target_link_libraries(unit_tests PUBLIC
        bash-lib

        gtest_main
        )

file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/unit/fixtures/files/*")
