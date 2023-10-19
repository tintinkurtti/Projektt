cmake_minimum_required(VERSION 3.24)
project(Projektt)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projektt main.cpp Game.cpp Game.h Menu.cpp Menu.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(C:/SFML/include)

target_link_libraries(Projektt sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
