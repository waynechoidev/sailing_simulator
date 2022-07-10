#include "renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_loader.h"

void Renderer::run()
{
    init();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("shader/vertex.glsl", "shader/fragment.glsl");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    do
    {

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(_window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(_window) == 0);

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

void Renderer::init()
{
    // Initialise GLFW
    if (!glfwInit())
        reportErrorAndExit(__FUNCTION__, "glfw initialization");

    // Set window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Open a window and create its OpenGL context
    _window = glfwCreateWindow(1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if (!_window)
        reportErrorAndExit(__FUNCTION__, "Window initialization");
    glfwMakeContextCurrent(_window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
        reportErrorAndExit(__FUNCTION__, "glew initialization");

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void Renderer::reportErrorAndExit(const std::string &function_name, const std::string &message)
{
    std::cout << "Error: " << function_name << " " << message << std::endl;

    glfwTerminate();
    getchar(); // pause to read error message
    exit(1);
}