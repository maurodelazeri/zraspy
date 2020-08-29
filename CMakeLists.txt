cmake_minimum_required(VERSION 3.16)
project(libgpiodtests)

set(CMAKE_CXX_STANDARD 17)

find_library(GPIOD_LIBRARY NAMES libgpiod.so)
if(NOT GPIOD_LIBRARY)
    message(FATAL_ERROR "gpiod library not found. Install https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/")
endif()

find_package(Threads REQUIRED)

set(LIBS
        ${GPIOD_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
        )

add_executable(libgpiodtests main.cpp)

target_link_libraries (libgpiodtests  ${LIBS})
