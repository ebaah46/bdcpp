cmake_minimum_required(VERSION 3.23)
project(bottle_detector)

set(CMAKE_CXX_STANDARD 20)

add_executable(bottle_detector main.cpp)

add_subdirectory(detector)

target_include_directories(${PROJECT_NAME} PUBLIC detector)

target_link_directories(${PROJECT_NAME} PRIVATE detector/)

target_link_libraries(${PROJECT_NAME} detector)
#find_package(OpenCv)
#OpenCV