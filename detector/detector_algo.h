//
// Created by Emmanuel Baah on 25.8.2022.
//

#ifndef BOTTLE_DETECTOR_DETECTOR_ALGO_H
#define BOTTLE_DETECTOR_DETECTOR_ALGO_H
#include <string>
#include <map>

template<class T>
class Detector_Algo {
    public:
       static std::map<std::string ,std::string> houghCircles(T& image, T& originalImage, std::string& path);
};


#endif //BOTTLE_DETECTOR_DETECTOR_ALGO_H
