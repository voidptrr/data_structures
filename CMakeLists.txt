cmake_minimum_required(VERSION 4.1)

# Compiler options
project(data_structures C)

# Options
set(CMAKE_C_COMPILER "clang")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.c)
add_executable(data_structures ${SRC})

# Private headers
target_include_directories(data_structures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Standard and compiler flags
target_compile_features(data_structures PRIVATE c_std_17)
target_compile_options(data_structures PRIVATE -Wall -Wextra -Werror)

# Install phase
install(TARGETS data_structures RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
