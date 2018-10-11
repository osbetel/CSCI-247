cmake_minimum_required(VERSION 3.6)
project(perflab_handout)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        clock.c
        clock.h
        config.h
        defs.h
        driver.c
        fcyc.c
        fcyc.h
        kernels.c)

add_executable(perflab_handout ${SOURCE_FILES})