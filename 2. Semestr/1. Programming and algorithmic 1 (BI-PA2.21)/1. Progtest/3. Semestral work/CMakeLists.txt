cmake_minimum_required(VERSION 3.10)
project(papp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra ${CMAKE_CXX_FLAGS}")

include_directories(src/)

# Executable
add_executable(papp src/main.cpp src/CFloat.cpp src/Float.h src/CCoord.h src/CFloatBig.cpp src/CFloatBig.h src/CInteger.cpp src/CInteger.h src/CIntegerBig.cpp src/CIntegerBig.h src/CType.cpp src/CType.h src/CTypeBig.cpp src/CTypeBig.h src/CVariable.cpp src/CVariable.h)

