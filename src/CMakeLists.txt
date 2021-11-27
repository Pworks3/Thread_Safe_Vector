cmake_minimum_required(VERSION 3.5)
project(Thread_Safe_Vector CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testThreadSafeVector catch.hpp testThreadSafeVector.cpp threadSafeVector.tpp threadSafeVector.hpp)
