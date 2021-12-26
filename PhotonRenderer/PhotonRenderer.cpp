// PhotonRenderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include <stb\stb_image.h> 
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Cube.h"
#define WIDTH 800
#define HEIGHT 800


// Vertices coordinates
GLfloat m_vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for m_vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.2f, -0.2f,  0.2f,
	-0.2f, -0.2f, -0.2f,
	 0.2f, -0.2f, -0.2f,
	 0.2f, -0.2f,  0.2f,
	-0.2f,  0.2f,  0.2f,
	-0.2f,  0.2f, -0.2f,
	 0.2f,  0.2f, -0.2f,
	 0.2f,  0.2f,  0.2f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	//Initialize GLFW
	glfwInit();

	//Tell glfw which opengl version is used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//using core profile(contains only modern opengl functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the glfw window object
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PhotonRenderer", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Window fail to create" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	//create openGL viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSwapBuffers(window);

	Shader obj_shader("default.vert", "default.frag");

	//-------------------Original------------------
	////Generate vertex array object and binds it
	//VertexArray vao1;
	//vao1.Bind();

	////Generate vertex buffer object and link to m_vertices
	//VertexBuffer vb(m_vertices, sizeof(m_vertices));

	////Generate index buffer object and link to indices
	//IndexBuffer ebo(indices, sizeof(indices));

	//vao1.LinkAttrib(vb, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	//vao1.LinkAttrib(vb, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	//vao1.LinkAttrib(vb, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	//vao1.LinkAttrib(vb, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	//vao1.Unbind();
	//vb.Unbind();
	//ebo.Unbind();

	//glm::vec3 obj_pos = glm::vec3(0.0f,0.0f, 0.0f);
	//glm::mat4 obj_model = glm::mat4(1.0f);
	//obj_model = glm::translate(obj_model, obj_pos);
	//
	//Shader light_shader("light.vert", "light.frag");

	//VertexArray light_vao;
	//light_vao.Bind();

	//VertexBuffer light_vbo(lightVertices, sizeof(lightVertices));
	//IndexBuffer light_ebo(lightIndices, sizeof(lightIndices));

	//light_vao.LinkAttrib(light_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	//light_vao.Unbind();
	//light_vbo.Unbind();
	//light_ebo.Unbind();

	//glm::vec3 light_pos = glm::vec3(0.5f, 0.5f, 0.5f);
	//glm::mat4 light_model = glm::mat4(1.0);
	//glm::vec4 light_color = glm::vec4(1, 1, 1, 1);
	//light_model = glm::translate(light_model, light_pos);

	//light_shader.Activate();
	//light_shader.SetUniformMat4("model", light_model);
	//light_shader.SetUniformVec4("lightColor", light_color);
	//light_shader.SetUniformVec3("Position", light_pos);

	//obj_shader.Activate();
	//obj_shader.SetUniformMat4("model", obj_model);
	//obj_shader.SetUniformVec4("lightColor", light_color);
	//obj_shader.SetUniformVec3("lightPosition", light_pos);

	////Texture
	////define width, height and color channel for the texture, and load the texture
	//int widthImg, heightImg, numofColorChannel;

	//Texture brick_texture("resources/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//obj_shader.SetInt("tex0", 0);
	//brick_texture.Unbind();

	
	//-------------------Original------------------

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
	Cube cube;

	float rotation = 0;
	double previous_time = glfwGetTime();
	float light_r = 1;
	bool start_decreasing = false;
	bool start_increasing = false;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(.2f, .3f, .3f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		camera.HandleInput(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		//-------------------Original------------------
		/*obj_shader.Activate();
		obj_shader.SetUniformVec4("lightColor", light_color);
		obj_shader.SetUniformVec3("camPos", camera.Position());
		
		brick_texture.Bind();
		vao1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		light_shader.Activate();
		camera.SetUniform(light_shader, "camMatrix");
		light_shader.SetUniformVec4("lightColor", light_color);
		light_shader.SetUniformMat4("model", light_model);
		light_vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);*/
		//-------------------Original------------------
		cube.Draw(camera);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//-------------------Original------------------
	/*vao1.Delete();
	vb.Delete();
	ebo.Delete();
	obj_shader.Delete();
	brick_texture.Delete();*/
	//-------------------Original------------------
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
