#pragma once
#include <iostream>

class GLFWwindow;

class Renderer
{
public:
    Renderer(const std::string &title, const int &width, const int &height,
             const bool isWhite = true);

    ~Renderer();

    virtual void update() = 0;
    // pure virtual method to implement template method pattern

    void run();

protected:
    void init(const std::string &title, const int &width, const int &height,
              const bool isWhite);
    void reportErrorAndExit(const std::string &function_name, const std::string &message);
    GLFWwindow *_window;
    std::string _title;
    int _width;
    int _height;
    bool _isWhite;
};