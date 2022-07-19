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

void Window::Initialise()
{
    if (!glfwInit())
        reportErrorAndExit(__FUNCTION__, "glfw initialization");

    // Setup GLFW Windows Properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
};

GLfloat Window::getYChange()
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
};

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
            std::cout << "Pressed: " << key << std::endl;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
            std::cout << "Released: " << key << std::endl;
        }
    }
}

void Window::handleMouse(GLFWwindow *window, double xPos, double yPos)
{
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;

    // std::cout << "x: " << theWindow->xChange << ", y: " << theWindow->yChange << std::endl;
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
