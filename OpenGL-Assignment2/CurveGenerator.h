#pragma once
#include <vector>
#include "../glm/glm.hpp"


class CurveGenerator
{
public:
	CurveGenerator();
	void generateCurve(std::vector<glm::vec3>&);
	std::vector<glm::vec3> * getCurve();
private:
	void subDivide(const float u0, const float u1, const float maxLength, const glm::mat4x3 & control, glm::vec3 t0, glm::vec3 t1);
	glm::mat4x3 basis;
	glm::vec3 CurveGenerator::catmullRom(const glm::mat4x3 & control, float u);
	std::vector<glm::vec3>* curve;
};