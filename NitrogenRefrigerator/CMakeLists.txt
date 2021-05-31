cmake_minimum_required(VERSION 3.5)

project(NitrogenRefrigerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS CellContainer/cellcontainer.h CellContainer/jsonStorage.h)
set(SOURCES main.cpp CellContainer/cellcontainer.cpp CellContainer/jsonStorage.cpp)

add_executable(NitrogenRefrigerator ${HEADERS} ${SOURCES})
