cmake_minimum_required(VERSION 3.0.0)
project(cmake_practice VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(cmake_practice
    src/main.cpp
    src/shader_loader.h
    src/shader_loader.cpp
)


add_subdirectory(external/glfw EXCLUDE_FROM_ALL)
add_subdirectory(external/glew EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glfw
    PRIVATE libglew_static
    PRIVATE glm
)

add_custom_target(fragment_shader SOURCE shader/fragement.glsl)
add_custom_target(vertex_shader SOURCE shader/vertex.glsl)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
