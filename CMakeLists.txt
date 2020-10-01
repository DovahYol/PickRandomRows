# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.5)

project ("PickRandomRows")

SET( CMAKE_CXX_FLAGS  "-O1 -g -lrt -DNDEBUG -std=c++11 -DHAVE_CXX0X -march=native -fpic -w -fopenmp -ftree-vectorize -ftree-vectorizer-verbose=0" )
# Include sub-projects.
add_subdirectory ("PickRandomRows")
