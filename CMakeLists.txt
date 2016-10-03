# Minimum CMake version required
cmake_minimum_required(VERSION 3.1)

# Name of project
project(FRC_FP)

SET(CMAKE_BUILD_TYPE "Debug")

# Set the default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# Set warning flags
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

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
set_property(TARGET frc_fp PROPERTY C_STANDARD 99)
target_link_libraries(frc_fp m)


# Add source files for testing
set(TEST_SOURCE
	test/tests.c
	test/unity.c
	test/test_normalization.c
	test/test_transformation.c
	test/test_compression.c)

# Add executable for testing
add_executable(run_test_suite ${TEST_SOURCE})
set_property(TARGET run_test_suite PROPERTY C_STANDARD 99)

set(C_STANDARD_REQUIRED ON)
# Link library for testing
target_link_libraries(run_test_suite frc_fp)
