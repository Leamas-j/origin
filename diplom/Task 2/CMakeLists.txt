cmake_minimum_required(VERSION 3.20)
project(racing_simulator)
add_executable(racing_simulator racing_simulator.cpp)
add_subdirectory(DLL)
target_link_libraries(racing_simulator rs)