cmake_minimum_required (VERSION 3.4)
project (guess_factor)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/extern/cmake)


#OpenMP
find_package(OpenMP REQUIRED)

if(PROFILE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg ")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg ")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg ")
endif()

if(COVERAGE)
include(CodeCoverage)
APPEND_COVERAGE_COMPILER_FLAGS()
endif()

add_subdirectory (src)



IF(not ${NDEBUG})
add_subdirectory(extern/pybind11)
pybind11_add_module(guessfactor src/cc/py_main.cpp)
target_link_libraries(guessfactor PRIVATE libguessfactor)
target_compile_definitions(guessfactor PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
endif()

if(COVERAGE)
SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest --output-on-failure #-j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
            test_loops
	    test_test
        EXCLUDE "/usr/*"
        EXCLUDE "${PROJECT_SOURCE_DIR}/extern/*"
        )
endif()