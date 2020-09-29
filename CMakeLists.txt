cmake_minimum_required(VERSION 3.10)

# set the project name
project(cmdtool)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# add the getopt library
add_subdirectory(getopt)

# add the executable
add_executable(cmdtool WIN32
	main.cc
    mainwindow.cpp
	mainwindow.ui
	resources.qrc
)

# Link getopt  ... attention dll is needed
target_link_libraries(cmdtool PUBLIC getopt )
target_link_libraries(cmdtool PUBLIC Qt5::Widgets)

# Add include directory
target_include_directories(cmdtool PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/getopt"
                          ) 

# Copy getopt dll to build folder						  
add_custom_command(TARGET cmdtool POST_BUILD       	# Adds a post-build event to cmdtool
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  	# which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:getopt>                       # <--this is in-file
        $<TARGET_FILE_DIR:cmdtool>)                 # <--this is out-file path

# Copy qt widgets dll to build folder
add_custom_command(
    TARGET cmdtool POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE_DIR:cmdtool>
)

# Copy qt core dll to build folder
add_custom_command(
    TARGET cmdtool POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE_DIR:cmdtool>
)

# Copy qt gui dll to build folder
add_custom_command(
    TARGET cmdtool POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:cmdtool>
)

# create platforms folder needed by qt
add_custom_command(
    TARGET cmdtool POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:cmdtool>/platforms"
)

# copy windows integration plugin to platforms folder
add_custom_command(
    TARGET cmdtool POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin>
        "$<TARGET_FILE_DIR:cmdtool>/platforms"
)

# ------------------------------
# For debugging purposes
# ------------------------------
#
# add_custom_command(
#    TARGET cmdtool POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#       COMMAND ${CMAKE_COMMAND} -E make_directory 
#       $<TARGET_FILE_DIR:cmdtool>\test
#)