cmake_minimum_required(VERSION 3.0)
project(purpo VERSION 0.0.1)

#if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
#    CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
#    message(STATUS "Using ${CMAKE_CXX_COMPILER_ID} at: ${CMAKE_CXX_COMPILER}")
#else() # like "GNU"
#    message(FATAL_ERROR "Using ${CMAKE_CXX_COMPILER_ID} as CXX compiler. "
#        "Please use Clang or AppleClang by setting \"CMAKE_CXX_COMPILER\". "
#        )
#endif()

find_package(LLVM REQUIRED) # TODO: What are the qualified versions?
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
link_directories("${LLVM_LIBRARY_DIRS}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -fno-strict-aliasing")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

    if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -Wl,-s"
            )
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,-dead_strip -Wl,-S, -Wl,-x"
            )
    endif()
endif()

file(GLOB_RECURSE PURPO_SRC lib/*.cpp)
include_directories("include")

add_library(purpo_dynamic SHARED ${PURPO_SRC})
add_library(purpo_static STATIC ${PURPO_SRC})
set_target_properties(purpo_dynamic PROPERTIES OUTPUT_NAME "purpo")
set_target_properties(purpo_static PROPERTIES OUTPUT_NAME "purpo")

file(GLOB_RECURSE PURC_SRC tools/purc/*.cpp)
add_executable(purc ${PURC_SRC})
target_link_libraries(purc purpo_static -lLLVM)

set(PURPO_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/purpo/${PROJECT_VERSION}")
set(PURPO_INSTALL_BINDIR "${PURPO_INSTALL_DIR}/bin")
set(PURPO_INSTALL_LIBDIR "${PURPO_INSTALL_DIR}/lib")

install(TARGETS purpo_dynamic LIBRARY DESTINATION ${PURPO_INSTALL_LIBDIR})
install(TARGETS purpo_static ARCHIVE DESTINATION ${PURPO_INSTALL_LIBDIR})
install(TARGETS purc RUNTIME DESTINATION ${PURPO_INSTALL_BINDIR})
install(DIRECTORY "include" DESTINATION ${PURPO_INSTALL_DIR})

#### build runtime library in LLVM-IR mode ####
file(GLOB_RECURSE PURPO_RTL_SRC lib/runtime/*.cpp) # RTL for runtime library

add_custom_target(runtime
    COMMAND clang++ -c -emit-llvm -std=c++11 -Wall -Werror -O3
    -fno-strict-aliasing -fno-exceptions -fno-rtti
    -I${CMAKE_SOURCE_DIR}/include ${PURPO_RTL_SRC}

    COMMAND ${LLVM_INSTALL_PREFIX}/bin/llvm-ar r libpurrt.a *.bc
    COMMAND rm *.bc
    )

#### about tests ####
enable_testing()
set(TEST_EXE_PATH test)

set(SCAN_TEST_DIR ${CMAKE_SOURCE_DIR}/test/ScanTest)
add_executable(ScanTest ${SCAN_TEST_DIR}/ScanTest.cpp)
target_link_libraries(ScanTest purpo_static)
set_target_properties(ScanTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_EXE_PATH}
    )

add_test(NAME ScanTest1
    COMMAND $<TARGET_FILE:ScanTest> ${SCAN_TEST_DIR}/input/correct1.pur
    ${SCAN_TEST_DIR}/output/correct1.txt ${SCAN_TEST_DIR}/key/correct1.txt
    )
set_tests_properties(ScanTest1 PROPERTIES PASS_REGULAR_EXPRESSION "Success!")

set(PARSE_TEST_DIR ${CMAKE_SOURCE_DIR}/test/ParseTest)
add_executable(ParseTest ${PARSE_TEST_DIR}/ParseTest.cpp)
target_link_libraries(ParseTest purpo_static)
set_target_properties(ParseTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_EXE_PATH}
    )

add_test(NAME ParseTest1
    COMMAND $<TARGET_FILE:ParseTest> ${PARSE_TEST_DIR}/input/correct1.pur
    ${PARSE_TEST_DIR}/output/correct1.txt ${PARSE_TEST_DIR}/key/correct1.txt
    )
set_tests_properties(ParseTest1 PROPERTIES PASS_REGULAR_EXPRESSION "Success!")
