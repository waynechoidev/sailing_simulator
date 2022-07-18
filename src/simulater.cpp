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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("shader/vertex.glsl", "shader/fragment.glsl");

    static const GLfloat g_vertex_buffer_data[] = {
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
    static const GLfloat g_color_buffer_data[] = {
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

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    const float toRadians = 3.14159265f / 180.0f;

    bool direction = true;
    float triOffset = 0.0f;
    float triMaxOffset = 0.7f;
    float triIncreasement = 0.001f;
    int currentAngle = 0;
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
        glUseProgram(programID);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, triOffset, 0.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(triOffset, triOffset, triOffset));

        // move forward
        GLint u_model = glGetUniformLocation(programID, "model");
        if (u_model != -1)
            glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,        // attribute. No particular reason for 1, but must match the layout in the shader.
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3 * 12); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers(_window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(_window) == 0);

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
