#include "Point.h"
namespace Photon {
    Point::Point(glm::vec3 position) :
        Entity(position)
    {
        if (Init())
            LoadDefaultShader();
    }

    Point::Point(glm::vec2 position) :
        Entity(glm::vec3(position.x, position.y, 0))
    {
        if (Init())
            LoadDefaultShader();
    }

    void Point::Draw(FPSCamera* cam)
    {
        if (!m_init_success)
        {
            std::cout << "(Point) ERROR: unable to draw due to unsuccessful initialization" << std::endl;
            return;
        }

        glPointSize(2);
        m_shader->Activate();
        m_vao->Bind();
        glm::vec4 color = glm::vec4(1, 1, 1, 1);
        m_shader->SetUniformVec4("color", color);

        glDrawArrays(GL_POINTS, 0, 1);
    }

    bool Point::Init()
    {
        if (!Entity::Init())
            return false;

        float position_final_x = map(m_position.x, 0, 800, -1, 1);
        float position_final_y = map(m_position.y, 0, 800, -1, 1);

        m_position.x = position_final_x;
        m_position.y = position_final_y;

        m_vertex_data_list = {
            m_position.x, m_position.y, m_position.z
        };

        m_vertices_ptr = m_vertex_data_list.data();

        m_vao = new VertexArray();
        m_vao->Bind();

        m_vbo = new VertexBuffer(m_vertices_ptr, sizeof(GLfloat) * m_vertex_data_list.size());

        m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

        m_vao->Unbind();
        m_vbo->Unbind();

        return true;
    }

    void Point::LoadDefaultShader()
    {
        m_shader = new Shader("basicTransform.vert", "basicTransform.frag");
        m_shader->Activate();
        glm::vec4 color = glm::vec4(1, 1, 1, 1);
        m_shader->SetUniformVec4("color", color);
    }
}