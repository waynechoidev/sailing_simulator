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
#include "vane.h"
#include "goal.h"
#include <iostream>
#include <random>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

std::random_device rd;
std::mt19937 gen(rd());
Window mainWindow;
GLuint shader, u_model, u_projection;
Yacht yacht;
Mast mast;
Obstacle obstacle;
Vane vane;
const int NUM_OF_OBSTACLES = 20;
struct AABB
{
    glm::vec2 center;
    glm::vec2 length;
};
Obstacle obstacleList[NUM_OF_OBSTACLES];
AABB obstacleAABBList[NUM_OF_OBSTACLES];
Goal goal;
AABB goalAABB;

glm::vec2 pointList[4] = {
    {-70.f, -50.f},
    {70.f, -50.f},
    {70.f, 50.f},
    {-70.f, 50.f}};
float startDirAngle[4] = {-45.0f, 45.0f, 135.0f, -135.0f};

// World data
glm::vec2 worldWind = {0.0f, 5.0f};
float deltaTime = 0.0f;
float lastTime = 0.0f;

void loop();
void setObstacles();
void setGoal(glm::vec2 center);
void testCollision();
void goalCollision();
void reset();

int main()
{

    mainWindow = Window(800, 600, "Sailing Simulation");
    mainWindow.initialise();

    // Create Meshes
    yacht.createYacht();
    mast.createMast();
    vane.createVane();

    // Set world
    reset();

    shader = loadShaders("shader/shader.vert", "shader/shader.frag");
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!mainWindow.getShouldClose())
    {
        loop();
    }
    glDeleteProgram(shader);
    mainWindow.terminateWindow();
#endif

    return 0;
}

void loop()
{
    testCollision();
    goalCollision();

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

    // Render Goal
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
    goal.renderMesh();

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

    // Render Vane
    glm::mat4 vaneModel(1.0f);
    vaneModel = vaneModel * vane.getModelMatrix(yacht.getCurPos(), worldWind);
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(vaneModel));
    vane.renderMesh();

    glUseProgram(0);

    mainWindow.swapBuffers();
    glfwPollEvents();
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
        AABB aabb;
        glm::vec2 center = {randCenterX(gen), randCenterY(gen)};
        glm::vec2 length = {randLengthX(gen), randLengthY(gen)};
        obstacle.createObstacle(center, length);
        aabb.center = center;
        aabb.length = length;
        obstacleList[i] = obstacle;
        obstacleAABBList[i] = aabb;
    }
}

void setGoal(glm::vec2 center)
{
    glm::vec2 length = {10.0f, 10.0f};
    goal.createGoal(center, length);
    goalAABB.center = center;
    goalAABB.length = length;
}

void testCollision()
{
    for (int i = 0; i < NUM_OF_OBSTACLES; i++)
    {
        if (yacht.testCollision(obstacleAABBList[i].center, obstacleAABBList[i].length))
        {
            std::cout << "crash!!" << std::endl;
            yacht.crash();
            break;
        }
    }
    if (yacht.testCollisionWithWall())
    {
        std::cout << "Do not go that far!!" << std::endl;
        yacht.crash();
    }
}

void goalCollision()
{

    if (yacht.testCollision(goalAABB.center, goalAABB.length))
    {
        std::cout << "Success!!" << std::endl;
        reset();
    }
}

void reset()
{
    std::uniform_int_distribution<int> point(0, 3);
    int start = point(gen);

    std::uniform_int_distribution<int> dir(0, 360);
    float windDir = (float)dir(gen);

    yacht.reset(pointList[start], startDirAngle[start]);

    worldWind = glm::rotate(worldWind, glm::radians(windDir));

    setObstacles();

    int finish;
    switch (start)
    {
    case 0:
        finish = 2;
        break;
    case 1:
        finish = 3;
        break;
    case 2:
        finish = 0;
        break;
    case 3:
        finish = 1;
        break;
    }
    setGoal(pointList[finish]);
}