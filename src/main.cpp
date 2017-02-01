#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>

// this function is called every time an error is encountered
void error_callback(int error, const char* description){
    std::cout << "Error: " << description << std::endl;
}

int main(void){

    bool running = true;

    // initialize GLFW
    if(glfwInit()){
        // set the error callback function that is called whenever an error occurs
        glfwSetErrorCallback(error_callback);
        // set a minimum required version of openGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // create a window if GLFW was successfully initialized
        // window is in openGL context by default
        GLFWwindow* window = glfwCreateWindow(1280, 720, "game", nullptr, nullptr);
        // make sure a window was successfully created before starting the game
        if(!window){
            glfwTerminate();
            running = false;
        }
        while(running){
            // check if the user exited the window
            if(glfwWindowShouldClose(window)){
                running = false;
            }
            glfwPollEvents();
        }
        // destroy the window once the program finishes
        // window destruction always succeeds, no need to check
        glfwDestroyWindow(window);

        // terminate GLFW
        // also destroys any remaining open windows
        glfwTerminate();
    }

    return 0;

}
