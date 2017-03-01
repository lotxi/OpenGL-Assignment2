#include "CurveGenerator.h"
#include <iostream>
#include <cmath>

CurveGenerator::CurveGenerator() {
	curve = new std::vector<glm::vec3>;
}

void CurveGenerator::generateCurve(std::vector<glm::vec3>& points)
{
	
	glm::mat4x3 control;
	std::vector<glm::vec3> results;
	float maxLength = 0.1;

	// For each set of 4 consecutive points, create a catmull rom spline
	for (int i = 0; i<points.size() - 3; i++)
	{
		// Populate the control matrix
		control = glm::mat4x3(points.at(i).x, points.at(i).y, points.at(i).z,
		points.at(i + 1).x, points.at(i + 1).y, points.at(i + 1).z,
		points.at(i + 2).x, points.at(i + 2).y, points.at(i + 2).z,
		points.at(i + 3).x, points.at(i + 3).y, points.at(i + 3).z);
		// Add the initial point (i+1) to the results
		curve->push_back(points.at(i + 1));
		std::cout << "Subdividing 0.0, 1.0" << std::endl;
		subDivide(0.0, 1.0, maxLength, control);
	}

		// Add the final point to the results
		curve->push_back(points.at(points.size() - 2));

		std::cout << "Outputting curve" << std::endl;
		for (auto const& point : results)
		{
			std::cout << "X:" << point.x << ", Y:" << point.y << ", Z:" << point.z << std::endl;
		}
}

std::vector<glm::vec3>* CurveGenerator::getCurve()
{
	return curve;
}


void CurveGenerator::subDivide(const float u0, const float u1, const float maxLength, const glm::mat4x3& control)
{
	float uMid = (u0 + u1) / 2;
	glm::vec3 x0, x1;
	x0 = catmullRom(control, u0);
	std::cout << "X0=" << x0.x << " " << x0.y << " " << x0.z << std::endl;
	x1 = catmullRom(control, u1);
	std::cout << "X1=" << x1.x << " " << x1.y << " " << x1.z << std::endl;
	std::cout << "DISTANCE: "<< glm::distance(x1, x0) << std::endl;
	std::cout << (glm::distance(x1, x0) > maxLength) << std::endl;
	if (glm::distance(x1, x0) > maxLength) 
	{
		std::cout << "Subdividing..." << u0 << " " << uMid << std::endl;
		subDivide(u0, uMid, maxLength, control);
		std::cout << "Subdividing..." << uMid << " " << u1 << std::endl;
		subDivide(uMid, u1, maxLength, control);
	}
	else {
		curve->push_back(x0);
		curve->push_back(x1);
	}
	

}


glm::vec3 CurveGenerator::catmullRom(const glm::mat4x3 & control, float u)
{
	float s = 0.5;
	glm::vec4 parameter = glm::vec4(glm::pow(u, 3), glm::pow(u, 2), u, 1);
	glm::mat4 basis = glm::mat4(-s, 2 - s, s - 2, s,
		2 * s, s - 3, 3 - 2 * s, -s,
		-s, 0, s, 0,
		0, 1, 0, 0);
	glm::vec3 result = control*basis*parameter;
	return result;
}
