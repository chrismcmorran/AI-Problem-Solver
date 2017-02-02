file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_library(TileProblem STATIC ${SRCS} ${INCS})
