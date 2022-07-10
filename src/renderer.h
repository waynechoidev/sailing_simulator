#pragma once
#include <iostream>

class GLFWwindow;

class Renderer
{
public:
    Renderer();
    Renderer(const std::string &title, const int &width, const int &height,
             const bool isWhite = true);

    ~Renderer(){};

    void run();

protected:
    void init(const std::string &title, const int &width, const int &height,
              const bool isWhite);
    void reportErrorAndExit(const std::string &function_name, const std::string &message);
    GLFWwindow *_window;
    std::string _title = "unnamed";
    int _width = 800;
    int _height = 600;
    bool _isWhite = true;
};