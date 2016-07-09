# Minimum CMake version required
cmake_minimum_required(VERSION 2.8)

# Name of project
project(FRC_FP)

# Set the default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# Include header files
include_directories(include)

# Include source files
set(SOURCE
	src/frc_fp.c)

# Specify library
add_library(frc_fp STATIC ${SOURCE})

# Add source files for testing
set(TEST_SOURCE
	test/tests.c
	test/unity.c)

# Add executable for testing
add_executable(test ${TEST_SOURCE})

# Link library for testing
target_link_libraries(test frc_fp)
