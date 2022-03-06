set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/commands/command.hpp
        ${PROJECT_SOURCE_DIR}/src/commands/command.cpp
        ${PROJECT_SOURCE_DIR}/src/commands/arguments.hpp
        ${PROJECT_SOURCE_DIR}/src/commands/arguments.cpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parser.hpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parser.cpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parse_command_and_arguments.hpp
        ${PROJECT_SOURCE_DIR}/src/parsing/parse_command_and_arguments.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/utils.hpp
        ${PROJECT_SOURCE_DIR}/src/utils/utils.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/filesystem.hpp
        ${PROJECT_SOURCE_DIR}/src/bash/bash.hpp
        ${PROJECT_SOURCE_DIR}/src/bash/bash.cpp
        ${PROJECT_SOURCE_DIR}/src/bash/variables.hpp)

add_library(bash-lib STATIC ${SOURCES})

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS_EQUAL 8.0)
    set(CXX_FILESYSTEM_LIBRARIES "stdc++fs")
    target_link_libraries(bash-lib PUBLIC ${CXX_FILESYSTEM_LIBRARIES})
endif()

add_executable(bash ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(bash PUBLIC bash-lib)
