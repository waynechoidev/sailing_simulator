cmake_minimum_required(VERSION 3.1)
project(sailing_simulator)

add_executable(sailing_simulator
    src/main.cpp
    src/yacht.h
    src/yacht.cpp
    src/mast.h
    src/mast.cpp
    src/obstacle.h
    src/obstacle.cpp
    src/vane.h
    src/vane.cpp
    src/goal.h
    src/goal.cpp
    engine/shader_loader.h
    engine/shader_loader.cpp
    engine/window.h
    engine/window.cpp
    engine/mesh.h
    engine/mesh.cpp
    engine/texture.h
    engine/texture.cpp
    engine/model.h
    engine/model.cpp
    engine/camera.h
    engine/camera.cpp
)

if (EMSCRIPTEN)
  target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_GLFW=3")
  target_link_libraries(${PROJECT_NAME} PUBLIC "-s USE_WEBGL2=1")
  target_link_libraries(${PROJECT_NAME} PUBLIC "-s WASM=1")

  # Allow the directories /shader and /data to be fetched by the web browser.
  set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS
    "--preload-file ${CMAKE_CURRENT_BINARY_DIR}/shader/@/shader/")
  
else() # Not Web

  # glfw
  add_subdirectory(external/glfw EXCLUDE_FROM_ALL)
  target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

  # glew
  add_definitions(-DGLEW_STATIC)
  add_subdirectory(external/glew EXCLUDE_FROM_ALL)
  target_link_libraries(${PROJECT_NAME} PRIVATE libglew_static)

endif()

# glm
add_subdirectory(external/glm EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

# assimp
add_subdirectory(external/assimp EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)

# stb
include_directories(external/stb)

# add shader
foreach(file "shader/shader.frag" "shader/shader.vert")
    configure_file(${file} ${file})
  endforeach(file)

add_custom_command(
   TARGET ${PROJECT_NAME} PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_SOURCE_DIR}/textures
           ${CMAKE_CURRENT_BINARY_DIR}/textures)

add_custom_command(
   TARGET ${PROJECT_NAME} PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_SOURCE_DIR}/models
           ${CMAKE_CURRENT_BINARY_DIR}/models)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
)