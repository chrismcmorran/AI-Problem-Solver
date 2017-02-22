add_subdirectory(BridgePuzzle)
add_subdirectory(TilePuzzle)
add_executable(Puzzles Puzzles.cpp)
target_link_libraries(Puzzles ${LIBS} BridgePuzzle TilePuzzle)
