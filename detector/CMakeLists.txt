add_library(detector_algo detector_algo.cpp detector_algo.h)

find_package(OpenCV REQUIRED)

find_package(Boost REQUIRED)

find_package(fmt REQUIRED)
target_include_directories(detector_algo PRIVATE ${Boost_INCLUDE_DIRS} ${fmt_INCLUDE_DIRS})
target_link_libraries(detector_algo ${OpenCV_LIBS} ${Boost_LIBS} fmt::fmt)

#message( FATAL_ERROR "${BOOST_}")
install(TARGETS detector_algo DESTINATION lib)
install(FILES detector_algo.h DESTINATION include)