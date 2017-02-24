file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_executable(FocusGame ${SRCS} ${INCS})
target_link_libraries(FocusGame ${LIBS})
