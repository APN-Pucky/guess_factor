cmake_minimum_required (VERSION 3.4)
project (lib_guess_factor)

include_directories(h)
file(GLOB MyCSources cc/*.cc)
add_library(libguessfactor ${MyCSources})

add_executable(guess_factor main.cpp)
target_link_libraries(guess_factor libguessfactor)