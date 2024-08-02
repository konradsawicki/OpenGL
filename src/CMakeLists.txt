set(SRC_LIST
main.cpp
Camera.cpp
IndexBuffer.cpp
Renderer.cpp
Shader.cpp
VertexArray.cpp
VertexBuffer.cpp
VertexBufferLayout.cpp
Window.cpp
GraphicsContext.cpp
Application.cpp
Core.cpp
)

add_executable(Tachyon ${SRC_LIST})

target_include_directories(Tachyon PRIVATE
${DEPENDENCIES_DIR}/glad/include
${DEPENDENCIES_DIR}/glfw/include
${DEPENDENCIES_DIR}/glm
)

target_link_libraries(Tachyon PRIVATE
glad
glfw)
