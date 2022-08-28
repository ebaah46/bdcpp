cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

project(bottle_detector VERSION 1.0)

#option to use library
option (USE_D "A library to detect bottles in a crate." ON)
if (USE_D)
    add_subdirectory(detector)
    list(APPEND EXTRA_INCLUDES detector)
    list(APPEND EXTRA_LIBS detector)
endif ()

configure_file(bd_config.h.in bd_config.h)

add_executable(bottle_detector main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


target_include_directories(${PROJECT_NAME}
        PUBLIC ${EXTRA_INCLUDES}
        PUBLIC ${OpenCV_INCLUDE_DIRS}
        )
target_link_directories(${PROJECT_NAME}
        PUBLIC ${EXTRA_LIBS}
        )

target_link_libraries(${PROJECT_NAME} detector_algo  ${OpenCV_LIBS})


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/bd_config.h" DESTINATION include)

