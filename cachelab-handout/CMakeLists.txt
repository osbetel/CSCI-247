cmake_minimum_required(VERSION 3.6)
project(cachelab_handout)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cachelab.c
        cachelab.h
        csim.c
        test-trans.c
        tracegen.c
        trans.c)

add_executable(cachelab_handout ${SOURCE_FILES})