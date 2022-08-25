add_library(detector_algo detector_algo.cpp detector_algo.h)

install(TARGETS detector_algo DESTINATION lib)
install(FILES detector_algo.h DESTINATION include)