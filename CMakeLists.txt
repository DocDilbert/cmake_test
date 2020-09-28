cmake_minimum_required(VERSION 3.10)

# set the project name
project(cmdtool)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# add the getopt library
add_subdirectory(getopt)

# add the executable
add_executable(cmdtool main.cc)

# Link getopt  ... attention dll is needed
target_link_libraries(cmdtool PUBLIC getopt)

# Add include directory
target_include_directories(cmdtool PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/getopt"
                          ) 
						  
add_custom_command(TARGET cmdtool POST_BUILD       	# Adds a post-build event to cmdtool
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  	# which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:getopt>                       # <--this is in-file
        $<TARGET_FILE_DIR:cmdtool>)                 # <--this is out-file path
		
		