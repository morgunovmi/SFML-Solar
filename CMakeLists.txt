cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -Waligned-new -Wmultistatement-macros -Wrestrict -Wshadow=global -Wsuggest-attribute=malloc -fcheck-new -fsized-deallocation -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})

project(Solar VERSION 1.0)

find_package(OpenGL)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2f11710abc5aa478503a7ff3f9e654bd2078ebab"
    GIT_PROGRESS   TRUE 
    )

FetchContent_Declare(fmt
    GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
    GIT_PROGRESS   TRUE 
    )

FetchContent_Declare(imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui"
    GIT_PROGRESS   TRUE 
    )

FetchContent_MakeAvailable(SFML fmt imgui)

FetchContent_GetProperties(imgui)

set(IMGUI_SFML_DIR ${CMAKE_BINARY_DIR}/_deps/imgui-sfml)

execute_process(
    COMMAND git clone https://github.com/eliasdaler/imgui-sfml ${IMGUI_SFML_DIR} 
    COMMAND cat ${IMGUI_SFML_DIR}/imgconfig-SFML.h >> ${imgui_SOURCE_DIR}/imconfig.h
    COMMAND_ECHO STDOUT
    ) 

file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${IMGUI_SOURCES} ${IMGUI_SFML_DIR}/imgui-SFML.cpp)
add_subdirectory(src include)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

if(WIN32 OR WIN64)
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBS}
        fmt::fmt
        OpenGL::OpenGL
        )
else()
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBS}
        fmt::fmt
        OpenGL::OpenGL
        pthread)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    "include"
    "dependencies"
    ${IMGUI_SFML_DIR} 
    ) 

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    foreach(lib_sfml sfml-graphics sfml-system sfml-window)
        get_target_property(lib_path_sfml ${lib_sfml} LOCATION)
        file(COPY ${lib_path_sfml} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()

    get_target_property(lib_path_imgui ImGui-SFML::ImGui-SFML LOCATION)
    file(COPY ${lib_path_imgui} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
