#include "Renderer.h"
#include "../glm/gtc/matrix_transform.inl"
#include "../glm/gtc/type_ptr.hpp"
Renderer *Renderer::instance = 0;

Renderer::Renderer()
{
	std::cout << "Initializing Renderer" << std::endl;
	
	shader = new Shader("shader.vs", "shader.frag");
	std::cout << "Shader initialized" << std::endl;

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
	glBindVertexArray(0); // Unbind VAO
	renderMode = POINT;
	WIDTH = WIDTH_DEFAULT;
	HEIGHT = HEIGHT_DEFAULT;
}

Renderer* Renderer::getInstance()
{
	if (!instance)
	{
		instance = new Renderer;
	}
	return instance;
}


void Renderer::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Activate shader
	shader->Use();
	
	// Draw container
	glBindVertexArray(m_vao);
	glDrawArrays(renderMode==POINT?GL_POINTS:GL_LINE_STRIP, 0, points.size());
	glBindVertexArray(0);
}

void Renderer::AddPoint(glm::vec3 point)
{
	points.push_back(point);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::NewPoints(std::vector<glm::vec3>* newPoints)
{
	ClearPoints();
	for (auto i = 0; i < newPoints->size(); i++)
	{
		points.push_back(newPoints->at(i));
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::ClearPoints()
{
	std::cout << "Points cleared" << std::endl;
	points.clear();
	Renderer::getInstance()->SetRenderMode(POINT);
}

std::vector<glm::vec3> Renderer::getPoints()
{
	return points;
}

void Renderer::SetRenderMode(RenderMode mode)
{
	if (mode==POINT)
	{
		renderMode = POINT;
	}
	else if (mode == LINE)
	{
		renderMode = LINE;
	}
	
}



