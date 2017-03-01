#include "Renderer.h"

Renderer::Renderer()
{
	std::cout << "Initializing Renderer" << std::endl;
	
	shader = new Shader("shader.vs", "shader.frag");
	clicks.push_back(glm::vec3(0.75, 0.75, 0));

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * clicks.size(), clicks.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
	glBindVertexArray(0); // Unbind VAO
}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Activate shader
	shader->Use();

	// Draw container
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, clicks.size());
	glBindVertexArray(0);
}

void Renderer::AddPoint(const glm::vec2& point)
{
	clicks.push_back(glm::vec3(point, 0));
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * clicks.size(), clicks.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	std::cout << "Point added to VBO" << std::endl;
	glBindVertexArray(0);
}

void Renderer::outputClicks()
{
	for (const auto click: clicks)
	{
		std::cout << click.x << " " << click.y << " " << click.z << std::endl;
	}
}



