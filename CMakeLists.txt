cmake_minimum_required(VERSION 3.0.0)
project(breakout VERSION 0.5.0)

find_package(raylib 3.0 QUIET)

# include(CTest)
# enable_testing()

add_executable(breakout main.cpp)

target_link_libraries(breakout raylib)
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
