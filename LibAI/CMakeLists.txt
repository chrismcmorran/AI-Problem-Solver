file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_library(LibAI STATIC ${SRCS} ${INCS})