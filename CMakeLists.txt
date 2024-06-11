cmake_minimum_required(VERSION 3.15)

project(
    demarok
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(
    -Wall
    -Wextra
    -Wno-unused-result
)

if (OPTIMIZE)
    add_compile_options(-O2 -DNDEBUG)
else()
    add_compile_options(-Og -ggdb)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()


add_executable(demarok
    src/main.cpp
    src/hider.cpp
    src/base64.cpp
)
install(TARGETS demarok DESTINATION bin)
