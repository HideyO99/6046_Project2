#pragma once
#include <pugixml/pugixml.hpp>
#include <map>
#include <iostream>
#include <glm\glm.hpp>
#include <vector>
#include "../MeshObj/cMeshObj.h"


class cXML
{
public:
	cXML();
	~cXML();

	//media section
	struct MyMusic
	{
		std::string fname;
		std::string path[2];

		MyMusic();
	};

	void readXML();

	//graphic section
	bool loadModelFromXML(std::string filename, std::map<std::string, cMeshObj*>& mapInstancetoMeshOBJ, std::vector<cMeshObj*>& pVecInstanceMeshObj);
	bool findPathFromModelName(std::string modelName, std::string& modelPath);
	//graphic section
	std::map<std::string, std::string> mapModelNameAndPath;
	std::map<std::string, std::string> mapInstanceAndModelName;
	glm::vec3 cameraEyeFromXML;
	//media section
	MyMusic my_music[3];
	std::string my_fx_path[7];
};

