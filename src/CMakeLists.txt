set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/commands/command.hpp
        ${PROJECT_SOURCE_DIR}/src/commands/command.cpp
        ${PROJECT_SOURCE_DIR}/src/commands/arguments.hpp
        ${PROJECT_SOURCE_DIR}/src/commands/arguments.cpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parser.hpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parser.cpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parse_command_and_arguments.hpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parse_command_and_arguments.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/utils.hpp)

add_library(bash-lib STATIC ${SOURCES})
target_link_libraries(bash-lib PUBLIC ${CXX_FILESYSTEM_LIBRARIES})
add_executable(bash ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(bash PUBLIC bash-lib)
