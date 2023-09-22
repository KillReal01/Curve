cmake_minimum_required(VERSION 3.5)

project(project)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

file(GLOB SOURCE_FILES
    "main.cpp"
    "src/*.cpp"
)

add_executable(prog ${SOURCE_FILES})
if(OpenMP_CXX_FOUND)
    target_link_libraries(prog PRIVATE OpenMP::OpenMP_CXX)
endif()