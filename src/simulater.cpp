#include "simulater.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_loader.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Simulater::update()
{
    const float toRadians = 3.14159265f / 180.0f;

    bool direction = true;
    float triOffset = 0.0f;
    float triMaxOffset = 0.7f;
    float triIncreasement = 0.001f;
    int currentAngle = 0;

    GLuint VAO, vertexBuffer, colorBuffer, IBO, shader, u_model;

    // Create and compile our GLSL program from the shaders
    shader = LoadShaders("shader/vertex.glsl", "shader/fragment.glsl");

    static const GLfloat vertices[] = {
        -1.0f,
        -1.0f,
        0.0f,

        1.0f,
        -1.0f,
        0.0f,

        0.0f,
        1.0f,
        0.0f,
    };
    static const GLfloat colors[] = {
        1.0f,
        0.0f,
        0.0f,

        0.0f,
        1.0f,
        0.0f,

        0.0f,
        0.0f,
        1.0f,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    do
    {
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

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader
        glUseProgram(shader);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, triOffset, 0.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(triOffset, triOffset, triOffset));

        // move forward
        u_model = glGetUniformLocation(shader, "model");
        if (u_model != -1)
            glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        // Swap buffers
        glfwSwapBuffers(_window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(_window) == 0);

    // Cleanup VBO
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shader);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
