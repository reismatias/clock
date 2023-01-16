cmake_minimum_required(VERSION 3.24)
project(relogioPonto)

set(CMAKE_CXX_STANDARD 23)

add_executable(relogioPonto main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

# (1) Altere esta parte para seu diretório SFML, em sua máquina.
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

# (2) Altere esta parte para seu diretório SFML, em sua máquina.
include_directories(C:/SFML/include)

target_link_libraries(relogioPonto sfml-system sfml-window sfml-graphics sfml-audio sfml-network)