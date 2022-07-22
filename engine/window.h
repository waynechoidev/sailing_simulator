#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();

    Window(GLint windowWidth, GLint windowHeight, const char *subject);
    ~Window() {}

    void initialise();

    GLint getBufferWidth() { return _bufferWidth; }
    GLint getBufferHeight() { return _bufferHeight; }
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    bool *getKeys() { return keys; }

    void terminateWindow();

private:
    void reportErrorAndExit(const std::string &function_name, const std::string &message);
    static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    void createCallback();

private:
    GLFWwindow *mainWindow;

    GLint _width, _height;
    GLint _bufferWidth, _bufferHeight;
    const char *_subject;

    bool keys[1024];
};