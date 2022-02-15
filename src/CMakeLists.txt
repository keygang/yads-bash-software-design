set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/commands/command.hpp
        ${PROJECT_SOURCE_DIR}/src/commands/command.cpp
        ${PROJECT_SOURCE_DIR}/src/commands/arguments.hpp)

add_library(bash-lib STATIC ${SOURCES})
add_executable(bash ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(bash PUBLIC bash-lib)
