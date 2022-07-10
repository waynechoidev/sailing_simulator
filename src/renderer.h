#pragma once
#include <iostream>

class GLFWwindow;

class Renderer
{
public:
    void run();

protected:
    void init();
    void reportErrorAndExit(const std::string &function_name, const std::string &message);
    GLFWwindow *_window;
};