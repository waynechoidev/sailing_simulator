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
#include "mast.h"
#include "obstacle.h"
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
Window mainWindow;
GLuint shader, u_model, u_projection;
Yacht yacht;
Mast mast;
Obstacle obstacle;
const int NUM_OF_OBSTACLES = 20;
struct obstacleAABB
{
    glm::vec2 center;
    glm::vec2 length;
};
Obstacle obstacleList[NUM_OF_OBSTACLES];
obstacleAABB obstacleAABBList[NUM_OF_OBSTACLES];
glm::vec2 startPointList[4] = {
    {-70.f, -50.f},
    {70.f, -50.f},
    {70.f, 50.f},
    {-70.f, 50.f}};

// World data
glm::vec2 worldWind = {0.0f, 5.0f};
float deltaTime = 0.0f;
float lastTime = 0.0f;

void setObstacles();
void testCollision();
void reset();

int main()
{

    mainWindow = Window(800, 600, "Sailing Simulation");
    mainWindow.initialise();

    // Create Meshes
    yacht.createYacht();
    mast.createMast();

    // Set world
    reset();

    shader = loadShaders("shader/vertex.glsl", "shader/fragment.glsl");

    while (!mainWindow.getShouldClose())
    {
        testCollision();

        if (mainWindow.getKeys()[32])
        {
            reset();
        } // space to reset (backdoor)

        float now = glfwGetTime();  // SDL_GetPerformanceCounter();
        deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
        lastTime = now;

        yacht.turnEngine(mainWindow.getKeys()[265]);
        if (mainWindow.getKeys()[263])
            yacht.turnToPort();
        if (mainWindow.getKeys()[262])
            yacht.turnToStarboard();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);
        u_model = glGetUniformLocation(shader, "model");
        u_projection = glGetUniformLocation(shader, "projection");

        glm::mat4 projection = glm::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1.0f, 1.0f);
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model(1.0f);

        // Render obstacles
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        for (int i = 0; i < NUM_OF_OBSTACLES; i++)
        {
            obstacleList[i].renderMesh();
        }

        // Render Yacht
        model = yacht.getModelMatrix(deltaTime, worldWind);
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        yacht.renderMesh();

        // Render Mast
        model = model * mast.getModelMatrix(yacht.getMastAngle(worldWind));
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        mast.renderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
        glfwPollEvents();
    };

    glDeleteProgram(shader);
    mainWindow.terminateWindow();

    return 0;
}

void setObstacles()
{
    std::uniform_int_distribution<int> randCenterX(-65, 65);
    std::uniform_int_distribution<int> randCenterY(-45, 45);
    std::uniform_int_distribution<int> randLengthX(2, 10);
    std::uniform_int_distribution<int> randLengthY(2, 10);

    for (int i = 0; i < NUM_OF_OBSTACLES; i++)
    {
        Obstacle obstacle;
        obstacleAABB aabb;
        glm::vec2 center = {randCenterX(gen), randCenterY(gen)};
        glm::vec2 length = {randLengthX(gen), randLengthY(gen)};
        obstacle.createObstacle(center, length);
        aabb.center = center;
        aabb.length = length;
        obstacleList[i] = obstacle;
        obstacleAABBList[i] = aabb;
    }
}

void testCollision()
{
    for (int i = 0; i < NUM_OF_OBSTACLES; i++)
    {
        if (yacht.testCollision(obstacleAABBList[i].center, obstacleAABBList[i].length))
        {
            std::cout << "crash!!" << std::endl;
            reset();
            continue;
        }
    }
}

void reset()
{
    std::uniform_int_distribution<int> point(0, 3);
    int start = point(gen);

    std::uniform_int_distribution<int> dir(0, 360);
    float windDir = (float)dir(gen);
    yacht.reset(startPointList[start]);
    worldWind = glm::rotate(worldWind, glm::radians(windDir));

    setObstacles();
}