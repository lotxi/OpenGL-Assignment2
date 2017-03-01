#include "Renderer.h"
#include "CurveGenerator.h"
#include "../glm/glm.hpp"

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
glm::vec2 screenToModel(glm::vec2 point);

//enum state { INPUT_PROFILE, INPUT_TRAJECTORY, RENDER };
//enum sweepType { TRANSLATIONAL, ROTATIONAL };
//state currentState = INPUT_PROFILE;
//sweepType currentSweep;

bool keys[1024];
bool mouse[2];
CurveGenerator* profile;
CurveGenerator* trajectory;


int main()
{
	// Initialize OpenGL Window
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH_DEFAULT, HEIGHT_DEFAULT, "Assignment 2", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		std::cout << "Failed to create GLFW Window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -2;
	}

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Setup OpenGL options
	//glEnable(GL_DEPTH_TEST);
	glPointSize(6);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	while (!glfwWindowShouldClose(window))
	 {
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		Renderer::getInstance()->Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	 }

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_1)
	{
		if (action == GLFW_PRESS)
		{
			mouse[0] = true;
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			std::cout << "Adding point to curve 1 - x: " << xPos << ", y: " << yPos << std::endl;
			Renderer::getInstance()->AddPoint(glm::vec3(screenToModel(glm::vec2(xPos, yPos)),0));
		}
		else if (action == GLFW_RELEASE)
		{
			mouse[0] = false;
		}

	}

	if (button == GLFW_MOUSE_BUTTON_2)
	{
		



		if (action == GLFW_PRESS)
		{
			Renderer::getInstance()->outputClicks();
	//		mouse[1] = true;
	//		/*std::cout << "Clicks 1:" << std::endl;
	//		for (auto const& click : mouseClicks1)
	//		{
	//			std::cout << "X: " << click.x << "Y: " << click.y << std::endl;
	//		}
	//		std::cout << "Clicks 2:" << std::endl;
	//		for (auto const& click : mouseClicks2)
	//		{
	//			std::cout << "X: " << click.x << "Y: " << click.y << std::endl;
	//		}*/

		}
	//	else if (action == GLFW_RELEASE)
	//	{
	//		mouse[1] = false;
	//	}

	}

}

glm::vec2 screenToModel(const glm::vec2 point)
{
	int src_min_x = 0, src_max_x = 800, src_min_y = 800, src_max_y = 0, res_min = -1, res_max = 1;
	GLfloat x, y;
	std::cout << "X:" << point.x << " , Y:" << point.y << std::endl;
	x = (point.x - src_min_x) / (src_max_x - src_min_x) * (res_max - res_min) + res_min;
	y = (point.y - src_min_y) / (src_max_y - src_min_y) * (res_max - res_min) + res_min;
	std::cout << "X':" << std::endl << x << " , Y':" << y << std::endl;
	return glm::vec2(x, y);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ENTER:
			if (Renderer::getInstance()->getPoints().size() >= 4)
			{
				profile = new CurveGenerator();
				profile->generateCurve(Renderer::getInstance()->getPoints());
				Renderer::getInstance()->NewPoints(profile->getCurve());
			}
			else
			{
				std::cerr << "Not enough points to compute Catmull Rom splines: At least 4 points are required" << std::endl;
			}



		default:
			break;
		}
	}
}

