cmake_minimum_required(VERSION 3.20)
set(SOURCE_F air.cpp broom.cpp camel.cpp camelfast.cpp centaur.cpp eagle.cpp flyingCarpet.cpp flyingCarpet.cpp myException.cpp roverboots.cpp transport.cpp ground.cpp)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(rs SHARED ${SOURCE_F})