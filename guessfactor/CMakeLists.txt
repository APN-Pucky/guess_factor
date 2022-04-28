cmake_minimum_required (VERSION 3.4)
project (lib_guess_factor)

file(GLOB MyCSources *.cc)
add_library(libguessfactor ${MyCSources})

if(OpenMP_CXX_FOUND)
  set( TARGET_LINK_LIBS ${TARGET_LINK_LIBS}  OpenMP::OpenMP_CXX )
endif()
target_link_libraries(libguessfactor ${TARGET_LINK_LIBS})