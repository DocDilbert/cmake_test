cmake_minimum_required(VERSION 3.10)

# set the project name
project(cmdtool)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# add the getopt library
add_subdirectory(getopt)
add_compile_definitions(STATIC_GETOPT)
# add the executable
add_executable(cmdtool main.cc)

target_link_libraries(cmdtool PUBLIC getopt)
target_include_directories(cmdtool PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/getopt"
                          ) 