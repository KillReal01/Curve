cmake_minimum_required(VERSION 3.5)

project(project)
set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/src
)

add_executable(prog main.cpp)
#target_link_libraries(prog gtest gmock pthread)