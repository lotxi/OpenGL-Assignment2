#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../glm/glm.hpp"
#include <sstream>
#include <istream>
#include <vector>
#include "../glew/glew.h"	// include GL Extension Wrangler
#include <iterator>

class FileManager
{
public:
	static void writeRotationalSweep(std::vector<glm::vec3>* positionCurve);
	static void writeTranslationalSweep(std::vector<glm::vec3>* profileCurve, std::vector<glm::vec3>* trajectoryCurve);

private:
	FileManager();;
	~FileManager();
};