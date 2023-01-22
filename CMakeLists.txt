cmake_minimum_required(VERSION 3.24)
project(relogioPonto)

set(CMAKE_CXX_STANDARD 23)

add_executable(relogioPonto main.cpp)

# (1) Altere no primeiro set o path/reference para seu diretório SFML, em sua máquina.
# (2) Comente os dois set abaixo caso esteja no linux.
set(SFML_DIR C:/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS network audio graphics window system REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif ()