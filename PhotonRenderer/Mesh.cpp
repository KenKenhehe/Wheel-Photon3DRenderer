#include "Mesh.h"

namespace Photon {
    Mesh::Mesh(std::vector<Vertex> vertices, 
        std::vector<unsigned int> indices, 
        std::vector<TextureData> textures)
    {
        this->m_vertices = vertices;
        this->m_indices = indices;
        this->m_textures = textures;

        SetupMesh();
    }

    void Mesh::Draw(Shader& shader)
    {
        /*unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name = m_textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            else if (name == "texture_normal")
                number = std::to_string(normalNr++);
            else if (name == "texture_height")
                number = std::to_string(heightNr++);
            shader.SetInt((name + number), i);
        }*/

        m_vao->Bind();
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
        m_vao->Unbind();

        //glActiveTexture(GL_TEXTURE0);
    }

    void Photon::Mesh::SetupMesh()
    {
        m_vao = new VertexArray();
        m_vao->Bind();

        m_vbo = new VertexBuffer((GLfloat*)&m_vertices[0], m_vertices.size() * sizeof(Vertex));
        m_ibo = new IndexBuffer(&m_indices[0], sizeof(GLuint) * m_indices.size());

        m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
        m_vao->LinkAttrib(*m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        m_vao->LinkAttrib(*m_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
        /*m_vao->LinkAttrib(*m_vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        m_vao->LinkAttrib(*m_vbo, 4, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
        m_vao->LinkAttrib(*m_vbo, 5, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, bone_ids));
        m_vao->LinkAttrib(*m_vbo, 6, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, weights));*/

        m_vao->Unbind();
        m_vbo->Unbind();
        m_ibo->Unbind();

        /* glBindVertexArray(VAO);
         glBindBuffer(GL_ARRAY_BUFFER, VBO);

         glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);*/

         // set the vertex attribute pointers
             // vertex Positions
        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //// vertex normals
        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    }
}