cmake_minimum_required (VERSION 3.4)
project (guess_factor)


add_subdirectory (src)


add_subdirectory(extern/pybind11)
pybind11_add_module(guessfactor src/py_main.cpp)
target_link_libraries(guessfactor PRIVATE libguessfactor)
target_compile_definitions(guessfactor PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})