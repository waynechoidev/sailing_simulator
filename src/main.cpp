#include "iostream"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../engine/window.h"
#include "../engine/shader_loader.h"
#include "yacht.h"
#include <iostream>

Window mainWindow;
GLuint shader, u_model, u_projection;
Yacht yacht;

float deltaTime = 0.0f;
float lastTime = 0.0f;
float windSpeed = 2.0f;
int windAngle = 30;

int main()
{
    mainWindow = Window(800, 600, "Sailing Simulation");
    mainWindow.initialise();

    yacht.createYacht();

    shader = loadShaders("shader/vertex.glsl", "shader/fragment.glsl");

    // glm::mat4 projection = glm::perspective(glm::radians(20.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
    glm::mat4 projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);

    while (!mainWindow.getShouldClose())
    {
        float now = glfwGetTime();  // SDL_GetPerformanceCounter();
        deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
        lastTime = now;

        yacht.turnEngine(mainWindow.getKeys()[265]);
        if (mainWindow.getKeys()[263])
            yacht.turnToPort();
        if (mainWindow.getKeys()[262])
            yacht.turnToStarboard();

        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        u_model = glGetUniformLocation(shader, "model");
        u_projection = glGetUniformLocation(shader, "projection");

        glm::mat4 model = yacht.getModelMatrix(deltaTime);

        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

        yacht.renderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
        glfwPollEvents();
    };

    glDeleteProgram(shader);
    mainWindow.terminateWindow();

    return 0;
}
