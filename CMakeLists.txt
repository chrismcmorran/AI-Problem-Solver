cmake_minimum_required(VERSION 2.6) 
project(4106-a1)

set(LIBS LibAI BridgeProblem TileProblem)
add_subdirectory(LibAI)
add_subdirectory(BridgeProblem)
add_subdirectory(TileProblem)
add_subdirectory(A1)
