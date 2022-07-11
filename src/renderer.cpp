#include "renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_loader.h"

Renderer::Renderer(const std::string &title, const int &width, const int &height,
                   const bool isWhite)
{
    _title = title;
    _width = width;
    _height = height;
    _isWhite = isWhite;

    init(_title, _width, _height, _isWhite);
}

Renderer::~Renderer()
{
    glfwDestroyWindow(_window);
}

void Renderer::init(const std::string &title, const int &width, const int &height, const bool isWhite)
{
    // Initialise GLFW
    if (!glfwInit())
        reportErrorAndExit(__FUNCTION__, "glfw initialization");

    // Set window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Open a window and create its OpenGL context
    _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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
    if (isWhite)
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    else
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Renderer::run()
{
    update();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

void Renderer::reportErrorAndExit(const std::string &function_name, const std::string &message)
{
    std::cout << "Error: " << function_name << " " << message << std::endl;

    glfwTerminate();
    getchar(); // pause to read error message
    exit(1);
}