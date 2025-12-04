#include "FractalLayer.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>


FractalLayer::FractalLayer(const char* path) :
    m_FragmentShaderPath(path)
{
    m_shader = Renderer::CreateGraphicsShader(
        "App/Data/Fullscreen.vert.glsl", 
        m_FragmentShaderPath 
    );

    m_loc_resolution = glGetUniformLocation(m_shader, "iResolution");
    m_loc_center     = glGetUniformLocation(m_shader, "center");
    m_loc_zoom       = glGetUniformLocation(m_shader, "zoom");
    m_loc_palette    = glGetUniformLocation(m_shader, "palette");
    m_loc_iterations = glGetUniformLocation(m_shader, "u_maxIterations");

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

    m_palette.generateGradient();

    glGenTextures(1, &m_colorTexture);
    glBindTexture(GL_TEXTURE_1D, m_colorTexture);

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexImage1D(
        GL_TEXTURE_1D,
        0,
        GL_RGB8,
        Core::ColorPalette::PALETTE_SIZE,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        m_palette.getColors().data()
    );
}


FractalLayer::~FractalLayer()
{
    glDeleteVertexArrays(1, &m_vertexArray);
    glDeleteBuffers(1, &m_vertexBuffer);

    glDeleteProgram(m_shader);
}


void FractalLayer::onEvent(Core::Event& event)
{
    // std::println("{}", event.ToString());

    Core::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Core::MouseScrolledEvent>([this](Core::MouseScrolledEvent& mouseEvent) {
        return OnMouseScrollEvent(mouseEvent);
    });

    dispatcher.Dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent& keyEvent) {
        // std::cout << keyEvent.ToString() << std::endl;
        return OnKeyPressedEvent(keyEvent);
    });

}


void FractalLayer::onRender()
{
    glUseProgram(m_shader);
    
    glm::vec2 frameBufferSize = Core::Application::Get().GetFrameBufferSize();
    
    glUniform2f(m_loc_resolution, frameBufferSize.x, frameBufferSize.y);

#ifdef _DOUBLE_PRECISION_
    glUniform1d(m_loc_zoom, m_zoom);
    glUniform2d(m_loc_center, m_center.x, m_center.y);
    
#else
    glUniform1f(m_loc_zoom, m_zoom);
    glUniform2f(m_loc_center, m_center.x, m_center.y);

#endif

    glUniform1i(m_loc_iterations, m_iterations);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, m_colorTexture);

    glUniform1i(m_loc_palette, 0);
    
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


void FractalLayer::updatePaletteTexture()
{
    glBindTexture(GL_TEXTURE_1D, m_colorTexture);
    glTexSubImage1D(
        GL_TEXTURE_1D,
        0,
        0,
        Core::ColorPalette::PALETTE_SIZE,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        m_palette.getColors().data()
    );
}



bool FractalLayer::OnMouseScrollEvent(Core::MouseScrolledEvent& event)
{
    glm::vec2 mouse = Core::Application::Get().GetWindow()->GetMousePos();
    glm::vec2 windowSize = Core::Application::Get().GetFrameBufferSize();

    float yOffset = (float)event.GetYOffset();
    double zoomSpeed = 0.1;

    double aspect = (double)windowSize.x / (double)windowSize.y;

    glm::dvec2 uv;
    uv.x =  (mouse.x / windowSize.x) * 2.0 - 1.0;
    uv.y = -(mouse.y / windowSize.y) * 2.0 + 1.0;
    uv.x *= aspect;

    glm::dvec2 mouseWorldBefore = m_center + uv * m_zoom;

    m_zoom *= (1.0 - yOffset * zoomSpeed);
    m_zoom = glm::max(m_zoom, 1e-20);

    glm::dvec2 mouseWorldAfter = m_center + uv * m_zoom;
    m_center += (mouseWorldBefore - mouseWorldAfter);

    return false;
}


bool FractalLayer::OnKeyPressedEvent(Core::KeyPressedEvent& event)
{
    if (event.IsRepeat())
        return false;

    switch (event.GetKeyCode())
    {
        case GLFW_KEY_ESCAPE:
        {
            Core::Application::Get().Stop();
            break;
        }

        case GLFW_KEY_H:
        {
            Core::Application& app = Core::Application::Get();
            
            if (app.GetLayer<ControlLayer>())   // If Layer exists
                app.RemoveLayer<ControlLayer>();
            else
                app.PushLayer<ControlLayer>();

            return true;
        }
    }

    return false;
}