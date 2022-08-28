#include <bd_config.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#ifdef USE_D
    #include <detector_algo.h>
#endif
int main(int argc, char*argv[]) {
/*    #ifdef USE_D
        std::cout<<argv[0] <<"Version "<<bottle_detector_VERSION_MAJOR<<"."<<bottle_detector_VERSION_MINOR<<std::endl;
    #endif
    */
    std::string pathToFile,fileName;
    if(argc > 1){
        pathToFile = argv[1];
    }
    else{
        fprintf(stderr, "No image provided.");
        exit(2);
    }
    // strip filename from path
    auto pos = pathToFile.find_last_of("/");
    if (pos != std::string::npos){
        fileName = pathToFile.substr(pos+1);
    }
    // remove extension from filename
    auto ext = fileName.find_last_of(".");
    if(ext != std::string::npos){
        fileName = fileName.substr(0,ext);
    }
    // read image to container
    cv::Mat src, grayScale,imgProcess;
    src = cv::imread(pathToFile);
    // convert image to grayscale
    cv::cvtColor(src,grayScale,cv::COLOR_BGR2GRAY);
    /*
     * Apply filters
     * first apply 2 median filters with different kernel sizes
     * then apply a bilateral filter
     */
    cv::medianBlur(grayScale,grayScale,5);
    cv::medianBlur(grayScale,grayScale,7);
    cv::bilateralFilter( grayScale,imgProcess,9,114.0,114.0);
    // apply hough transform to detect the circles in the filtered image
    auto response  = Detector_Algo<cv::Mat>::houghCircles(grayScale,src,fileName);
    bool result = false;
    try
    {
        //    write the resulting image to disk
        result = cv::imwrite(response["title"],src);
    }
    catch (const cv::Exception& ex)
    {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
    if (result)
        printf("Saved PNG file with alpha data.\n");
    else
        printf("ERROR: Can't save PNG file.\n");
    return 0;
}
