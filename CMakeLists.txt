########################################################
#
#  This is a CMake configuration file.
#  To use it you need CMake which can be
#  downloaded from here:
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 3.0 )


project( querytester CXX)

add_subdirectory(gumbo)
add_subdirectory(query)
add_subdirectory(querytest)

