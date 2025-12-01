#include "FractalLayer.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <print>


FractalLayer::FractalLayer()
{
    m_shader = Renderer::CreateGraphicsShader(
        "App/Data/Fullscreen.vert.glsl", 
        "App/Data/Mandelbrot.frag.glsl"
    );

    m_loc_time       = glGetUniformLocation(m_shader, "iTime");
    m_loc_resolution = glGetUniformLocation(m_shader, "iResolution");
    m_loc_center     = glGetUniformLocation(m_shader, "center");
    m_loc_zoom       = glGetUniformLocation(m_shader, "zoom");

    glCreateVertexArrays(1, &m_vertexArray);
    glCreateBuffers(1, &m_vertexBuffer);

    struct Vertex
    {
        glm::vec2 position;
        glm::vec2 texCoord;
    };

    Vertex vertices[] = {
        { {-1.0f, -1.0f }, { 0.0f, 0.0f } },  // Bottom-left
		{ { 3.0f, -1.0f }, { 2.0f, 0.0f } },  // Bottom-right
		{ {-1.0f,  3.0f }, { 0.0f, 2.0f } }   // Top-left
    };

    glNamedBufferData(m_vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(m_vertexArray, 0, m_vertexBuffer, 0, sizeof(Vertex));

    // Enable attributes
	glEnableVertexArrayAttrib(m_vertexArray, 0); // position
	glEnableVertexArrayAttrib(m_vertexArray, 1); // uv

	// Format: location, size, type, normalized, relative offset
	glVertexArrayAttribFormat(m_vertexArray, 0, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, position)));
	glVertexArrayAttribFormat(m_vertexArray, 1, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, texCoord)));

	// Link attribute locations to binding index 0
	glVertexArrayAttribBinding(m_vertexArray, 0, 0);
	glVertexArrayAttribBinding(m_vertexArray, 1, 0);
}


FractalLayer::~FractalLayer()
{
    glDeleteVertexArrays(1, &m_vertexArray);
    glDeleteBuffers(1, &m_vertexBuffer);

    glDeleteProgram(m_shader);
}


void FractalLayer::onEvent(Core::Event& event)
{
    std::println("{}", event.ToString());

    Core::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Core::MouseScrolledEvent>([this](Core::MouseScrolledEvent& mouseEvent) {
        return OnMouseScrollEvent(mouseEvent);
    });
}


void FractalLayer::onRender()
{
    glUseProgram(m_shader);

    glUniform1f(m_loc_time, m_time);
    
    glm::vec2 frameBufferSize = Core::Application::Get().GetFrameBufferSize();
    glUniform2f(m_loc_resolution, frameBufferSize.x, frameBufferSize.y);
    glUniform1f(m_loc_zoom, m_zoom);
    glUniform2f(m_loc_center, m_center.x, m_center.y);
    
    glViewport(0, 0, static_cast<GLsizei>(frameBufferSize.x), static_cast<GLsizei>(frameBufferSize.y));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(m_vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void FractalLayer::onUpdate(float ts)
{
    m_time += ts;
}


bool FractalLayer::OnMouseScrollEvent(Core::MouseScrolledEvent& event)
{
    float yOffset = static_cast<float>(event.GetYOffset());

    float zoomSpeed = 0.1f;
    m_zoom *= (1.0f - yOffset * zoomSpeed);

    m_zoom = glm::max(m_zoom, 1e-12f);

    return false;
}