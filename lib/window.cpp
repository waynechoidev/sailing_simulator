#include "window.h"
#include "iostream"

Window::Window()
{
    _width = 800;
    _height = 600;
    _subject = "Test Window";
}

Window::Window(GLint windowWidth, GLint windowHeight, const char *subject)
{
    _width = windowWidth;
    _height = windowHeight;
    _subject = subject;
}

int Window::Initialise()
{
    if (!glfwInit())
    {
        std::cout << "Error Initialising GLFW" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW Windows Properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    mainWindow = glfwCreateWindow(_width, _height, _subject, NULL, NULL);
    if (!mainWindow)
    {
        printf("Error creating GLFW window!");
        glfwTerminate();
        return 1;
    }

    // Set the current context
    glfwMakeContextCurrent(mainWindow);

    // Get buffer size information
    glfwGetFramebufferSize(mainWindow, &_bufferWidth, &_bufferHeight);

    // Allow modern extension access
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Create Viewport
    glViewport(0, 0, _bufferWidth, _bufferHeight);

    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // // Enable depth test
    // glEnable(GL_DEPTH_TEST);
    // // Accept fragment if it closer to the camera than the former one
    // glDepthFunc(GL_LESS);

    // // Cull triangles which normal is not towards the camera
    // glEnable(GL_CULL_FACE);

    return 0;
}

void Window::terminateWindow()
{
    glfwTerminate();
    glfwDestroyWindow(mainWindow);
}
