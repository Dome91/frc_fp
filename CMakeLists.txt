# Minimum CMake version required
cmake_minimum_required(VERSION 2.8)

# Name of project
project(FRC_FP)

# Set the default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

#SET(GCC_COVERAGE_COMPILE_FLAGS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c")

# Include header files
include_directories(include)

# Include source files
set(SOURCE
	src/frc_fp.c
	src/compression.c
	src/encoding.c
	src/normalization.c
	src/transformation.c
	src/common.c)

# Specify library
add_library(frc_fp STATIC ${SOURCE})
target_link_libraries(frc_fp m)

# Add source files for testing
set(TEST_SOURCE
	test/tests.c
	test/unity.c
	test/test_normalization.c
	test/test_transformation.c
	test/test_compression.c)

# Add executable for testing
add_executable(test ${TEST_SOURCE})

# Link library for testing
target_link_libraries(test frc_fp)
