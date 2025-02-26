cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (cpp_callbacks_cmake)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

# This project will output an executable file
add_executable(${PROJECT_NAME} 
	callbackmanager.cpp
	callback_function_template_args.cpp )

# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
