cmake_minimum_required(VERSION 3.14)

project(Solar VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_executable(${PROJECT_NAME} "")
add_subdirectory(src include)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SFML_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE "include") 
