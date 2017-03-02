#include "Renderer.h"
#include "CurveGenerator.h"
#include "../glm/glm.hpp"
#include "FileManager.h"

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void changeView();
void reset();
void selectSweep();

glm::vec2 screenToModel(glm::vec2 point);

enum state { INPUT_PROFILE, INPUT_TRAJECTORY, REVIEW_CURVES, RENDER };
enum sweepType { TRANSLATIONAL, ROTATIONAL };
enum view {PROFILE, TRAJECTORY, SHAPE};
state currentState = INPUT_PROFILE;
sweepType currentSweep;
view currentView = PROFILE;

bool keys[1024];
bool mouse[2];
CurveGenerator* profile=0;
CurveGenerator* trajectory=0;
int WIDTH = WIDTH_DEFAULT;
int HEIGHT = HEIGHT_DEFAULT;


int main()
{
	
	
	currentState = INPUT_PROFILE;
	selectSweep();
	
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
		glfwSwapInterval(1);
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
			if (currentState == INPUT_TRAJECTORY || currentState==INPUT_PROFILE)
			{
				double xPos, yPos;
				glfwGetCursorPos(window, &xPos, &yPos);
				Renderer::getInstance()->AddPoint(glm::vec3(screenToModel(glm::vec2(xPos, yPos)),0));
			}
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
	int src_min_x = 0, src_max_x = WIDTH, src_min_y = HEIGHT, src_max_y = 0, res_min = -1, res_max = 1;
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
				if (currentState==INPUT_PROFILE)
				{
					profile = new CurveGenerator();
					profile->generateCurve(Renderer::getInstance()->getPoints());
					Renderer::getInstance()->NewPoints(profile->getCurve());
					currentState = REVIEW_CURVES;
					if (currentSweep==ROTATIONAL)
					{
						FileManager::writeRotationalSweep(profile->getCurve());
						std::cout << "Translational sweep written to file" << std::endl;
					}
				}
				else if (currentState==INPUT_TRAJECTORY)
				{
					trajectory = new CurveGenerator();
					trajectory->generateCurve(Renderer::getInstance()->getPoints());
					std::cout << "Rendering trajectory curve" << std::endl;
					Renderer::getInstance()->NewPoints(trajectory->getCurve());
					currentState = REVIEW_CURVES;
					// Write translational sweep to file
					std::cout << "Translational sweep written to file" << std::endl;
					FileManager::writeTranslationalSweep(profile->getCurve(),trajectory->getCurve());
					

				}
				else if (currentState==REVIEW_CURVES)
				{
					if (currentSweep==TRANSLATIONAL)
					{
						if (!trajectory)
						{
							std::cout << "Choose points for trajectory curve" << std::endl;
							currentState = INPUT_TRAJECTORY;
							Renderer::getInstance()->ClearPoints();
							Renderer::getInstance()->SetRenderMode(Renderer::RenderMode::POINT);
						}
						else
						{
							// Display shape.
						}
					}
					else
					{
						// Display shape
					}
					
				}
				
				
			}
			else
			{
				std::cerr << "Not enough points to compute Catmull Rom splines: At least 4 points are required" << std::endl;
			}
			break;


		case GLFW_KEY_LEFT:
			std::cout << "Left key pressed" << std::endl;
			if (currentState==REVIEW_CURVES)
			{
				if (trajectory) // If both curves have been defined, allow switching between views
				{
					changeView();
				}
			}
			break;
		case GLFW_KEY_RIGHT:
			std::cout << "Right key pressed" << std::endl;
			if (currentState == REVIEW_CURVES)
			{
				if (trajectory) // If both curves have been defined, allow switching between views
				{
					changeView();
				}
			}
			break;
		case GLFW_KEY_L:
			if (currentState==REVIEW_CURVES)
			Renderer::getInstance()->SetRenderMode(Renderer::RenderMode::LINE);
			break;
		case GLFW_KEY_P:
			if (currentState == REVIEW_CURVES)
			Renderer::getInstance()->SetRenderMode(Renderer::RenderMode::POINT);
			break;
		case GLFW_KEY_BACKSPACE:
			currentState == INPUT_PROFILE;
			reset();
		default:
			break;
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, WIDTH, HEIGHT);
}

void changeView()
{
	if (currentView==PROFILE)
	{
		Renderer::getInstance()->NewPoints(trajectory->getCurve());
		currentView = TRAJECTORY;
	}
	else if (currentView==TRAJECTORY)
	{
		Renderer::getInstance()->NewPoints(profile->getCurve());
		currentView = PROFILE;
	}
}

void reset()
{
	if (profile)
	{
		delete profile;
		profile = nullptr;
	}
	if (trajectory)
	{
		delete trajectory;
		trajectory = nullptr;
	}
	Renderer::getInstance()->ClearPoints();
	currentState = INPUT_PROFILE;
	currentView = PROFILE;
	selectSweep();
}

void selectSweep()
{
	std::string response;
	while (true) {
		std::cout << "Please select a sweep type > [t]ranslational or [r]otational > ";
		std::cin >> response;

		if (response == "T" || response == "t")
		{
			std::cout << "Translational Sweep Selected" << std::endl;
			currentSweep = TRANSLATIONAL;
			break;
		}
		if (response == "R" || response == "r")
		{
			std::cout << "Rotational Sweep Selected: Click ponts for curve then press enter" << std::endl;
			currentSweep = ROTATIONAL;
			break;
		}

		std::cout << "Please enter T or R" << std::endl;
	}
}

