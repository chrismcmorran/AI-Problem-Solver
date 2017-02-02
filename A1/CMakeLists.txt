file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_executable(A1 ${SRCS} ${INCS})
target_link_libraries(A1 ${LIBS})
