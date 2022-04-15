file(GLOB MyCSources *.cc)
add_library(libguessfactor ${MyCSources})
add_executable(guess_factor main.cpp)
target_link_libraries(guess_factor libguessfactor)
