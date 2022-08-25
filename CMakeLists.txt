cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

project(bottle_detector VERSION 1.0)

#option to use library
option (USE_D "A library to detect bottles in a crate." ON)
message("NO message")
if (USE_D)
    add_subdirectory(detector)
    list(APPEND EXTRA_LIBS detector)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/detector")
    message("nothing here")
endif ()

configure_file(bd_config.h.in bd_config.h)

add_executable(bottle_detector main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

#--------Download all submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    #Update submodules as needed
    option( GIT_SUBMODULE "Check modules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
        endif ()
    endif ()
endif()

#------- Check the glfw submodule
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "CMakeLists.txt file does not exist in submodule directory" )
endif ()

add_subdirectory(external/glfw/)

target_include_directories(${PROJECT_NAME}
        PUBLIC external/glfw/include
        ${EXTRA_INCLUDES}
        )
target_link_directories(${PROJECT_NAME}
        PRIVATE external/glfw/src
        ${EXTRA_LIBS}
        )

target_link_libraries(${PROJECT_NAME} detector_algo glfw)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/bd_config.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${bottle_detector_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${bottle_detector_VERSION_MINOR})
INCLUDE(CPack)