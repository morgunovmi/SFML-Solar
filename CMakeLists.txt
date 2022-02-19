cmake_minimum_required(VERSION 3.14)

project(Solar VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE debug)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -Waligned-new -Wmultistatement-macros -Wrestrict -Wshadow=global -Wsuggest-attribute=malloc -fcheck-new -fsized-deallocation -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

add_executable(${PROJECT_NAME} "/home/johnson/git/imgui/imgui_demo.cpp")
add_subdirectory(src include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)
find_package(fmt REQUIRED)
find_package(ImGui-SFML REQUIRED)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

target_include_directories(${PROJECT_NAME} PRIVATE "include" "dependencies") 

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    foreach(lib_sfml sfml-graphics sfml-system sfml-window)
        get_target_property(lib_path_sfml ${lib_sfml} LOCATION)
        file(COPY ${lib_path_sfml} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endforeach()

    get_target_property(lib_path_imgui ImGui-SFML::ImGui-SFML LOCATION)
    file(COPY ${lib_path_imgui} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
