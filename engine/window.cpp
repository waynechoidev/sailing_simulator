#include "window.h"

Window::Window()
{
    _width = 800;
    _height = 600;
    _subject = "Test Window";

    for (size_t i = 0; i < 1024; i++)
        keys[i] = 0;
}

Window::Window(GLint windowWidth, GLint windowHeight, const char *subject)
{
    _width = windowWidth;
    _height = windowHeight;
    _subject = subject;

    for (size_t i = 0; i < 1024; i++)
        keys[i] = 0;
}

void Window::initialise()
{
    if (!glfwInit())
        reportErrorAndExit(__FUNCTION__, "glfw initialization");

#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create the window
    mainWindow = glfwCreateWindow(_width, _height, _subject, NULL, NULL);
    if (!mainWindow)
        reportErrorAndExit(__FUNCTION__, "Window initialization");

    // Set the current context
    glfwMakeContextCurrent(mainWindow);

    // Get buffer size information
    glfwGetFramebufferSize(mainWindow, &_bufferWidth, &_bufferHeight);

    // Handle key and mouse input
    createCallback();
    // glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Allow modern extension access
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if (error != GLEW_OK)
        reportErrorAndExit(__FUNCTION__, "glew initialization");

    // Create Viewport
    glViewport(0, 0, _bufferWidth, _bufferHeight);

    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallback()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
}

void Window::handleKeys(GLFWwindow *window, int key, int code, int action, int mode)
{
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
        }
    }
}

void Window::reportErrorAndExit(const std::string &function_name, const std::string &message)
{
    std::cout << "Error: " << function_name << " " << message << std::endl;

    glfwTerminate();
    getchar(); // pause to read error message
    exit(1);
}

void Window::terminateWindow()
{
    glfwTerminate();
    glfwDestroyWindow(mainWindow);
}
