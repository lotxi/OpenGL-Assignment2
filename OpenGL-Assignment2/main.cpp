#include "Renderer.h"

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//enum state { INPUT_PROFILE, INPUT_TRAJECTORY, RENDER };
//enum sweepType { TRANSLATIONAL, ROTATIONAL };
//state currentState = INPUT_PROFILE;
//sweepType currentSweep;

bool keys[1024];
bool mouse[2];


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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	Renderer& renderer = Renderer::getInstance();


	while (!glfwWindowShouldClose(window))
	 {
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		renderer.Render();

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
			Renderer::getInstance().AddPoint(glm::vec2(xPos, yPos));
		}
		else if (action == GLFW_RELEASE)
		{
			mouse[0] = false;
		}

	}

	//if (button == GLFW_MOUSE_BUTTON_2)
	//{
	//	if (action == GLFW_PRESS)
	//	{
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

	//	}
	//	else if (action == GLFW_RELEASE)
	//	{
	//		mouse[1] = false;
	//	}

	//}

}