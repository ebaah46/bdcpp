//
// Created by Emmanuel Baah on 25.8.2022.
//

#include "detector_algo.h"
#include <string>
#include <map>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <fmt/format.h>

template<> std::map<std::string ,std::string> Detector_Algo<cv::Mat>::houghCircles(cv::Mat& image, cv::Mat& originalImage, std::string &file) {
    double minDist =30.0;
    int minRadius =10;
    int maxRadius =36;
    double param1 =32;
    double param2 =34;
    int count = 0;

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image,circles,cv::HOUGH_GRADIENT,1.0,minDist,param1,param2,minRadius,maxRadius);
    for (size_t i = 0; i< circles.size();i++){
        cv::Vec3i c = circles[i];
        cv::Point center = cv::Point (c[0],c[1]);
        // Draw circle around the bottle
        cv::circle(originalImage,center,c[2],cv::Scalar(0.0,255.0,255.0),3,cv::LINE_AA);
        // Put text of bottle count in drawn circle
        std::string text = std::to_string(i+1);
        cv::putText(originalImage,text,center,cv::FONT_HERSHEY_COMPLEX,0.4,cv::Scalar(255.0,0.0,255.0),1);
        count++;
    }
    std::string title = fmt::format("{}_{}_bottles.png",file,std::to_string(count));
    std::map<std::string,std::string> response;
    response.insert({"title",title});
    response.insert({"bottles",std::to_string(count)});
    return response;
}
