file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_library(TilePuzzle STATIC ${SRCS} ${INCS})
