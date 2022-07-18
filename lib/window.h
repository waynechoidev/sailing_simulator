#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();

    Window(GLint windowWidth, GLint windowHeight, const char *subject);

    int Initialise();

    GLint getBufferWidth() { return _bufferWidth; }
    GLint getBufferHeight() { return _bufferHeight; }
    int getWindowKey(int key) { return glfwGetKey(mainWindow, key); }
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    ~Window() {}

    void terminateWindow();

private:
    GLFWwindow *mainWindow;

    GLint _width, _height;
    GLint _bufferWidth, _bufferHeight;
    const char *_subject;
};