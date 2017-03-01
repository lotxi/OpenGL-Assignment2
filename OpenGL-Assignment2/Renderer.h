#pragma once
#include "iostream"
#define GLEW_STATIC
#define GLEW_STATIC
#include "glew/glew.h"	// include GL Extension Wrangler
#include "glfw/glfw3.h"	// include GLFW helper library
#include "glm/glm.hpp"
#include "Shader.h"
#include <vector>

#define WIDTH_DEFAULT 800
#define HEIGHT_DEFAULT 800

class Renderer
{
public: 
	static Renderer& getInstance();
	void Render();
	void AddPoint(const glm::vec2 & point);
	void outputClicks();

private: 
	Renderer();
	Shader* shader;
	std::vector<glm::vec3> clicks;
	GLuint m_vao, m_vbo;
	glm::vec3 Renderer::screenToModel(glm::vec3 point);
};

