file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_library(BridgeProblem STATIC ${SRCS} ${INCS})
