cmake_minimum_required(VERSION 3.0.0)
project(cmake_practice VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(cmake_practice
    main.cpp
    src/shader_loader.h
    src/shader_loader.cpp
    src/renderer.h
    src/renderer.cpp
)


add_subdirectory(external/glfw EXCLUDE_FROM_ALL)
add_subdirectory(external/glew EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glfw
    PRIVATE libglew_static
    PRIVATE glm
)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
                ${CMAKE_SOURCE_DIR}/shader
                ${CMAKE_CURRENT_BINARY_DIR}/shader)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
