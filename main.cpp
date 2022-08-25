#include <iostream>
#include <GLFW/glfw3.h>
#include <bd_config.h>
#ifdef USE_D
    #include <detector_algo.h>
#endif
int main(int argc, char*argv[]) {
    std::cout << "Hello, Squad!" << std::endl;
    #ifdef USE_D
        detector::Detector_Algo::doNothing();
        std::cout<<argv[0] <<"Version "<<bottle_detector_VERSION_MAJOR<<"."<<bottle_detector_VERSION_MINOR<<std::endl;
    #endif
    GLFWwindow * window;
    if(!glfwInit()){
        fprintf(stderr,"Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(400,400,"Detector",NULL,NULL);
    if(!window){
        fprintf(stderr,"Failed to open GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    while(!glfwWindowShouldClose(window)){

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    // Exit program
    exit( EXIT_SUCCESS );
    return 0;
}
