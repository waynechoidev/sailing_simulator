#include "iostream"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lib/window.h"
#include "lib/shader_loader.h"
#include "lib/mesh.h"

Window mainWindow;
GLuint shader, u_model, u_projection;
Mesh *obj1, *obj2;
std::vector<Mesh *> meshList;
const float toRadians = 3.14159265f / 180.0f;

void CreateObjects();

int main()
{
    bool direction = true;
    float triOffset = 0.0f;
    float triMaxOffset = 0.7f;
    float triIncreasement = 0.001f;
    int currentAngle = 0;

    mainWindow = Window(800, 600, "New Window");
    mainWindow.Initialise();

    shader = LoadShaders("shader/vertex.glsl", "shader/fragment.glsl");
    CreateObjects();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

    while (!mainWindow.getShouldClose())
    {
        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        if (direction)
            triOffset += triIncreasement;
        else
            triOffset -= triIncreasement;
        if (std::abs(triOffset) >= triMaxOffset)
        {
            direction = !direction;
        }
        if (currentAngle >= 360)
            currentAngle = 0;
        else
            currentAngle++;

        u_model = glGetUniformLocation(shader, "model");
        u_projection = glGetUniformLocation(shader, "projection");

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        // model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
        glfwPollEvents();
    };

    glDeleteProgram(shader);
    delete obj1;
    delete obj2;
    mainWindow.terminateWindow();

    return 0;
}

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

    obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}
