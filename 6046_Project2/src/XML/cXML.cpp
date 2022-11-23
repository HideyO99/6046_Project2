#include "cXML.h"


cXML::cXML()
{
	this->mapModelNameAndPath.clear();
}

cXML::~cXML()
{
}

void cXML::readXML()
{
	pugi::xml_document music_xml;
	pugi::xml_parse_result result = music_xml.load_file("sound_list.xml");
	if (!result)
	{
		std::cout << "Unable to load XML file" << std::endl;
		return;
	}
	std::cout << "Loaded XML" << std::endl;
	//pugi::xml_object_range<pugi::xml_node_iterator> music = music_xml.child("music").children();
	//if (music.empty())
	//{
	//	std::cout << "There are no entries" << std::endl;
	//	return;
	//}

	//pugi::xml_node_iterator music_i;
	//int i = 0;
	//int j = 0;
	//for (music_i = music.begin(); music_i != music.end(); ++music_i)
	//{
	//	pugi::xml_node fname = *music_i;
	//	pugi::xml_node_iterator musicit;
	//	//std::string s = fname.child_value();
	//	my_music[i].fname = fname.child_value();
	//	my_music[i].fname.erase(std::remove(my_music[i].fname.begin(), my_music[i].fname.end(), '\n'), my_music[i].fname.cend());	//remove \n
	//	my_music[i].fname.erase(std::remove(my_music[i].fname.begin(), my_music[i].fname.end(), '\t'), my_music[i].fname.cend());	//remove \t
	//	for (musicit = fname.children().begin(); musicit != fname.children().end(); ++musicit)
	//	{
	//		pugi::xml_node pathNode = *musicit;

	//		if (!pathNode.children().empty())
	//		{
	//			my_music[i].path[j] = pathNode.child_value();
	//			j++;
	//		}
	//	}
	//	i++;
	//	j = 0;
	//}
	int i = 0;
	int j = 0;

	pugi::xml_object_range<pugi::xml_node_iterator> fx = music_xml.child("fx").children();
	if (fx.empty())
	{
		std::cout << "There are no entries" << std::endl;
		return;
	}

	pugi::xml_node_iterator fx_i;
	i = j = 0;

	for (fx_i = fx.begin(); fx_i != fx.end(); fx_i++)
	{
		pugi::xml_node fx_path = *fx_i;
		pugi::xml_node_iterator fx_it;
		for (fx_it = fx_path.children().begin(); fx_it != fx_path.children().end(); fx_it++)
		{
			pugi::xml_node pathNode = *fx_it;
			if (!pathNode.children().empty())
			{
				my_fx_path[i] = pathNode.child_value();
				i++;
			}
		}
	}
	//music_xml.~xml_document();
}

bool cXML::loadModelFromXML(std::string filename, std::map<std::string, cMeshObj*>& mapInstancetoMeshOBJ, std::vector<cMeshObj*>& pVecInstanceMeshObj)
{
	pugi::xml_document modelList_xml;
	pugi::xml_parse_result result = modelList_xml.load_file(filename.c_str());
	if (!result)
	{
		std::cout << "Unable to load XML file" << std::endl;
		return false;
	}
	std::cout << "Loading Model from XML" << std::endl;
	pugi::xml_object_range<pugi::xml_node_iterator> modelList = modelList_xml.child("PLYMODEL").children();
	if (modelList.empty())
	{
		std::cout << "There are no entries" << std::endl;
		return false;
	}
	pugi::xml_node_iterator i_modelList;
	for (i_modelList = modelList.begin(); i_modelList != modelList.end(); i_modelList++)
	{
		pugi::xml_node modelNode = *i_modelList;
		pugi::xml_node_iterator i_node_lv2;
		std::string instance;

		if (modelNode.child_value() == "")
		{
			continue;
		}

		std::string modelName = modelNode.attribute("name").as_string();
		std::string path = modelNode.child_value();
		path.erase(std::remove(path.begin(), path.end(), '\n'), path.cend());
		path.erase(std::remove(path.begin(), path.end(), '\t'), path.cend());
		mapModelNameAndPath.emplace(modelName, path);

		for (i_node_lv2 = modelNode.children().begin(); i_node_lv2 != modelNode.children().end(); i_node_lv2++)
		{
			pugi::xml_node node_lv3 = *i_node_lv2;
			instance = node_lv3.child_value();
			if (instance == "")
			{
				continue;
			}
			cMeshObj* pModedelInsance = new cMeshObj();
			instance.erase(std::remove(instance.begin(), instance.end(), '\n'), instance.cend());
			instance.erase(std::remove(instance.begin(), instance.end(), '\t'), instance.cend());
			pModedelInsance->meshName = modelName;
			pModedelInsance->instanceName = instance;
			pModedelInsance->position.x = std::stof(node_lv3.child("posX").child_value());
			pModedelInsance->position.y = std::stof(node_lv3.child("posY").child_value());
			pModedelInsance->position.z = std::stof(node_lv3.child("posZ").child_value());
			pModedelInsance->rotation.x = std::stof(node_lv3.child("rotateX").child_value());
			pModedelInsance->rotation.y = std::stof(node_lv3.child("rotateY").child_value());
			pModedelInsance->rotation.z = std::stof(node_lv3.child("rotateZ").child_value());
			mapInstancetoMeshOBJ.emplace(instance, pModedelInsance);
			pVecInstanceMeshObj.push_back(pModedelInsance);
			mapInstanceAndModelName.emplace(instance, modelName);
		}
	}

	pugi::xml_object_range<pugi::xml_node_iterator> loadCameraEye = modelList_xml.child("EYE_LOCATION").children();
	if (loadCameraEye.empty())
	{
		std::cout << "There are no entries" << std::endl;
		return false;
	}
	pugi::xml_node_iterator i_loadCameraEye;
	std::vector<std::string> tempXYZ;
	for (i_loadCameraEye = loadCameraEye.begin(); i_loadCameraEye != loadCameraEye.end(); i_loadCameraEye++)
	{
		pugi::xml_node CameraEye = *i_loadCameraEye;
		std::string check = CameraEye.child_value();
		tempXYZ.push_back(CameraEye.child_value());
	}
	
	cameraEyeFromXML.x = std::stof(tempXYZ[0]);
	cameraEyeFromXML.y = std::stof(tempXYZ[1]);
	cameraEyeFromXML.z = std::stof(tempXYZ[2]);
	
	return true;
}

bool cXML::findPathFromModelName(std::string modelName, std::string& modelPath)
{
	std::map<std::string, std::string>::iterator i_model = mapModelNameAndPath.find(modelName);
	if (i_model == mapModelNameAndPath.end())
	{
		return false;
	}
	modelPath = i_model->second;

	return true;
}

cXML::MyMusic::MyMusic()
{
	path[0] = "";
	path[1] = "";
}
