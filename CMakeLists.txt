cmake_minimum_required(VERSION 3.5)
project(RadixMP)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(HEADER_FILE include/radixmp.h)
set(SOURCE_FILE src/radixmp.c)

set(EXAMPLE_FILE_32BITS example/32bitsVersion.c)
set(EXAMPLE_FILE_64BITS example/64bitsVersion.c)

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

    add_library(radixmp STATIC ${HEADER_FILE} ${SOURCE_FILE})

    add_executable(example32Bits ${EXAMPLE_FILE_32BITS} ${HEADER_FILE} ${SOURCE_FILE})
    add_executable(example64Bits ${EXAMPLE_FILE_64BITS} ${HEADER_FILE} ${SOURCE_FILE})
endif ()