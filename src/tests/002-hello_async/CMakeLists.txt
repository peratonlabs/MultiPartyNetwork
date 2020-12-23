cmake_minimum_required(VERSION 3.0.0)
project(player VERSION 0.1.0)

include(CTest)
enable_testing()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.71.0 COMPONENTS thread chrono date_time) 

include_directories(${Boost_INCLUDE_DIRS}) 

SET (SRCS ../../mp_network.h
../../mp_network.cpp
player.cpp
)

add_executable(player ${SRCS})

target_link_libraries(player pthread ${Boost_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
