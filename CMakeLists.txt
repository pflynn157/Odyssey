cmake_minimum_required(VERSION 3.0.0)
project(odyssey)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS
	Core
	Widgets
	Gui
)

add_compile_options(-std=c++14)
include_directories("${CMAKE_BINARY_DIR}/src" src)

add_subdirectory(src)
add_subdirectory(terminal)
