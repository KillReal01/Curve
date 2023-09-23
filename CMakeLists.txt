cmake_minimum_required(VERSION 3.5)

project(main)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib_src
    ${CMAKE_SOURCE_DIR}/build
)


# library

add_library(curve SHARED
    lib_src/curve.cpp
)

# executable

file(GLOB SOURCE_FILES
    "main.cpp"
    "lib_src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE curve)

if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

endif()