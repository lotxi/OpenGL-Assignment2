#include "CurveGenerator.h"
#include <iostream>

CurveGenerator::CurveGenerator() {
	curve = new std::vector < glm::vec3 > ;
	subdivisionType = DISTANCE;
	ready = false;
}

void CurveGenerator::generateCurve(std::vector<glm::vec3>& points)
{
	std::cout << "Generating curve" << std::endl;
	glm::mat4x3 control;
	std::vector<glm::vec3> results;


	// For each set of 4 consecutive points, create a catmull rom spline
	for (int i = 0; i < points.size() - 3; i++)
	{
		// Populate the control matrix
		control = glm::mat4x3(points.at(i).x, points.at(i).y, points.at(i).z,
			points.at(i + 1).x, points.at(i + 1).y, points.at(i + 1).z,
			points.at(i + 2).x, points.at(i + 2).y, points.at(i + 2).z,
			points.at(i + 3).x, points.at(i + 3).y, points.at(i + 3).z);
		// Add the initial point (i+1) to the results
		curve->push_back(points.at(i + 1));

		if (subdivisionType == DISTANCE){
			subDivide(0.0f, 1.0f, 0.1f, control);
		}
		else if (subdivisionType == CURVATURE){
			glm::vec3 t0 = glm::normalize(points.at(i) - points.at(i + 2));
			glm::vec3 t1 = glm::normalize(points.at(i + 1) - points.at(i + 3));
			subDivide(0.0f, 1.0f, 10.0f, control, t0, t1);
		}


	}
	// Add the final point to the results
	curve->push_back(points.at(points.size() - 2));

	ready = true;
}

void CurveGenerator::setSubdivisionType(SubdivisionType subdivision)
{
	subdivisionType = subdivision;
}

std::vector<glm::vec3>* CurveGenerator::getCurve()
{
	return curve;
}

/**
Subdivide based on curvature
*/
void CurveGenerator::subDivide(const float u0, const float u1, const float maxAngle, const glm::mat4x3& control, glm::vec3 t0, glm::vec3 t1)
{
	float uMid = (u0 + u1) / 2;
	glm::vec3 x0, x1;
	x0 = catmullRom(control, u0);
	x1 = catmullRom(control, u1);
	float angle = abs(glm::degrees(glm::acos(glm::dot(t0, t1))));
	
	if (angle < 0) return;
	if (angle > maxAngle)
	{
		glm::vec3 tMid = glm::normalize(x0 - x1);
		subDivide(u0, uMid, maxAngle, control, t0, tMid);
		subDivide(uMid, u1, maxAngle, control, tMid, t1);
	}
	else {
		curve->push_back(x0);
		curve->push_back(x1);
	}
}

/**
	Subdivide based on distance
*/
void CurveGenerator::subDivide(const float u0, const float u1, const float maxLength, const glm::mat4x3& control)
{
	float uMid = (u0 + u1) / 2;
	glm::vec3 x0, x1;
	x0 = catmullRom(control, u0);
	x1 = catmullRom(control, u1);

	if (glm::distance(x1, x0) > maxLength)
	{
		subDivide(u0, uMid, maxLength, control);
		subDivide(uMid, u1, maxLength, control);
	}
	else {
		std::cout << "Adding points to curve" << std::endl;
		curve->push_back(x0);
		curve->push_back(x1);
	}
}


/**
Generate point on catmull rom spline from control points
*/
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

void CurveGenerator::Clear(){
	ready = false;
	delete curve;
	curve = new std::vector < glm::vec3 >;
}

bool CurveGenerator::isReady(){
	return ready;
}
