file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_executable(TileProblem ${SRCS} ${INCS})
target_link_libraries(TileProblem ${LIBS})
