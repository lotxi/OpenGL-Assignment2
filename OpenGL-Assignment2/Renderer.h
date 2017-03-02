#pragma once
#include "iostream"
#define GLEW_STATIC
#include "glew/glew.h"	// include GL Extension Wrangler
#include "glfw/glfw3.h"	// include GLFW helper library
#include "../glm/glm.hpp"
#include "Shader.h"
#include <vector>

#define WIDTH_DEFAULT 800
#define HEIGHT_DEFAULT 800

class Renderer
{
public:
	enum RenderMode { POINT, LINE };
	static Renderer* getInstance();

	/**
	 * \brief Render the points in points vector. Called in each iteration of main loop
	 */
	void Render();
	/**
	 * \brief Add a new vec3 to points vector
	 */
	void AddPoint(glm::vec3);
	/**
	 * \brief Clear the points vector and populate it with the provided vec3s
	 */
	void NewPoints(std::vector<glm::vec3>*);

	/**
	 * \brief Remove all vec3s from the points vector
	 */
	void ClearPoints();

	/**
	 * \brief Accessor for points vector
	 * \return the std::vector of vec3s holding the currently displayed points
	 */
	std::vector<glm::vec3> getPoints();

	/**
	 * \brief Set rendering mode to points or lines
	 * \param mode enum RenderMode
	 */
	void SetRenderMode(RenderMode mode);

private:

	/**
	 * \brief Private constructor to ensure single instance
	 */
	Renderer();

	/**
	 * \brief Instance of shader class holding the active shader program
	 */
	Shader* shader;

	/**
	 * \brief The currently displayed points
	 */
	std::vector<glm::vec3> points;

	GLuint m_vao, m_vbo;

	/**
	 * \brief Private instance of renderer for singleton behaviour
	 */
	static Renderer* instance;

	/**
	 * \brief The currently active render mode (points or lines)
	 */
	RenderMode renderMode;
	int WIDTH, HEIGHT;
};

