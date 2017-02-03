#define GLFW_DLL
#include <glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

// this function is called every time an error is encountered
void error_callback(int error, const char* description){
    std::cout << "Error: " << description << std::endl;
}

int main(void){

    bool running = true;

    // TODO: doge

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
        if (!window) {
            glfwTerminate();
            running = false;
        } else {
            // set the context so that GLEW can initialize correctly
            glfwMakeContextCurrent(window);
        }

        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;
        // initialize GLEW to handle openGL functions and extensions
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            std::cout << glewGetErrorString(err) << std::endl;
        }

        // Source code for the vertex shader
        std::string shaderStuff = "#version 330 core\nlayout (location = 0) in vec3 position;\n"
        "void main()\n{\ngl_Position = vec4(position.x, position.y, position.z, 1.0);\n}\0";
        const GLchar* vertexShaderSource = shaderStuff.c_str();

        // Source code for the fragment shader
        // set the color to blue with full opacity
        std::string shaderStuff2 = "#version 330 core\nout vec4 color;\nvoid main()\n"
        "{\ncolor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n}\n\0";
        const GLchar* fragmentShaderSource = shaderStuff2.c_str();

        // compile the vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // Check for compile time errors
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // compile the fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // Check for compile time errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Link shaders to a shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // Check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // delete shaders after they have been linked to the program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        // Set up vertex data for the triangle to render
        GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f, // Left
             1.0f, -1.0f, 0.0f, // Right
             0.0f,  1.0f, 0.0f  // Top
        };
        // set up the Vertex buffer object and vertex array object
        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Bind the Vertex Array Object
        glBindVertexArray(VAO);

        // Bind and set vertex buffer(s)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // the vertex attribute pointer tells opengl how to interpret the vertex data it recieves
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO
        glBindVertexArray(0);


        while(running){
            // check if the user exited the window
            if(glfwWindowShouldClose(window)){
                running = false;
            }
            glfwPollEvents();
            // Clear the colorbuffer
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw the triangle with the shader program
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            // Swap the screen buffers
            glfwSwapBuffers(window);
        }
        // destroy the window once the program finishes
        // window destruction always succeeds, no need to check
        glfwDestroyWindow(window);

        // terminate GLFW
        // also destroys any remaining open windows
        // dealocate any remaining resources
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
    }

    return 0;

}
