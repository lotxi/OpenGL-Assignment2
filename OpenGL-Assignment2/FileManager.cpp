#include "FileManager.h"

FileManager::FileManager()
{}

void FileManager::writeRotationalSweep(std::vector<glm::vec3>* positionCurve)
{
	int defaultSweeps = 75;
	std::ofstream output;
	output.open("output.txt");
	if (output.is_open())
	{


		output << 1 << std::endl;
		output << defaultSweeps << std::endl;
		output << positionCurve->size() << std::endl;
		for (int i = 0; i < positionCurve->size(); i++)
		{
			output << positionCurve->at(i).x << " " << positionCurve->at(i).z << " " << positionCurve->at(i).y << std::endl;
		}
	}
	else
	{
		throw "Error writing rotational sweep";
	}
}

void FileManager::writeTranslationalSweep(std::vector<glm::vec3>* profileCurve, std::vector<glm::vec3>* trajectoryCurve)
{
	std::ofstream output;
	output.open("output.txt");
	if (output.is_open()) {

		output << 0 << std::endl;
		output << profileCurve->size() << std::endl;
		for (int i = 0; i < profileCurve->size(); i++)
		{
			// Write profile Curve. Z value is written in place of Y as discussed in assignment specifications
			output << profileCurve->at(i).x << " " << profileCurve->at(i).z << " " << profileCurve->at(i).y << std::endl;
		}
		output << trajectoryCurve->size() << std::endl;
		for (int i = 0; i < trajectoryCurve->size(); i++)
		{
			// Write trajectory curve
			output << trajectoryCurve->at(i).x << " " << trajectoryCurve->at(i).y << " " << trajectoryCurve->at(i).z << std::endl;
		}
	}
	else
	{
		throw "Error writing translational sweep";
	}
}


FileManager::~FileManager()
{

}