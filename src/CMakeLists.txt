# Author: Scott Marshall
# Date: 11/04/2014

set( CMAKE_C_FLAGS "-Wall -g")

file(GLOB SRCS *.cpp *.h)

add_executable( gpsimu ${SRCS} )