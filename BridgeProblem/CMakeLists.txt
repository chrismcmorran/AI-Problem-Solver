file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_executable(BridgeProblem ${SRCS} ${INCS})
target_link_libraries(BridgeProblem ${LIBS})
