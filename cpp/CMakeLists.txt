cmake_minimum_required(VERSION 3.14)
project(gillespie_sim CXX)

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

add_executable(gillespie_sim apps/main.cpp src/Species.cpp src/Solver.cpp src/Composition.cpp src/ReactionChannel.cpp src/Participant.cpp)

target_include_directories(gillespie_sim PRIVATE 
    include 
    ${Python3_INCLUDE_DIRS} 
    ${Python3_NumPy_INCLUDE_DIRS}
)

target_link_libraries(gillespie_sim PRIVATE Python3::Python Python3::NumPy)

target_compile_features(gillespie_sim PRIVATE cxx_std_11)