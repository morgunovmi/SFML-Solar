cmake_minimum_required(VERSION 3.14)

project(Solar VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -Waligned-new -Wmultistatement-macros -Wrestrict -Wshadow=global -Wsuggest-attribute=malloc -fcheck-new -fsized-deallocation -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fsanitize=address")

add_executable(${PROJECT_NAME} "")
add_subdirectory(src include)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)
find_package(fmt REQUIRED)
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(sciplot REQUIRED)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SFML_LIBS} fmt::fmt xtensor xtensor::optimize sciplot::sciplot)

target_include_directories(${PROJECT_NAME} PRIVATE "include" "dependencies") 
