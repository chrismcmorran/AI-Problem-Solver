file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_library(BridgePuzzle STATIC ${SRCS} ${INCS})
