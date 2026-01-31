cmake_minimum_required(VERSION 3.14)
project(ssa_sim CXX)

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

add_executable(ssa_sim apps/main.cpp src/Utils.cpp src/Species.cpp src/Solver.cpp src/Composition.cpp src/ReactionChannel.cpp src/Participant.cpp src/Volume.cpp)

target_include_directories(ssa_sim PRIVATE 
    include 
    ${Python3_INCLUDE_DIRS} 
    ${Python3_NumPy_INCLUDE_DIRS}
)

target_link_libraries(ssa_sim PRIVATE Python3::Python Python3::NumPy)

target_compile_features(ssa_sim PRIVATE cxx_std_11)