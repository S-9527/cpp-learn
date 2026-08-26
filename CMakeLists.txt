cmake_minimum_required(VERSION 3.14)
project(myproject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/myproject.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
