cmake_minimum_required(VERSION 3.17)
project(FinalProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(FinalProject
        main.cpp
                             test_runner.h
        database.cpp         database.h
        date.cpp             date.h
        node.cpp             node.h
        condition_parser.cpp condition_parser.h
        token.cpp            token.h tests.h)
