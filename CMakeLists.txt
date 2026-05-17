cmake_minimum_required(VERSION 3.20)
project(CRCgenerator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Default to Release build for maximum performance
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# Enable Link Time Optimization (LTO)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# Add aggressive optimization flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -mtune=native -funroll-loops -fomit-frame-pointer -ffast-math")
elseif(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /Ob2 /Oi /Ot /Oy /GL")
endif()

include_directories(include)
add_executable(crc_app
    main.c
)
