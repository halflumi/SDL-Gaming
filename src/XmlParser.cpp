#include "XmlParser.h"
#include <SDL.h>
#include "Main.h"

XmlParser* XmlParser::INSTANCE = 0;

XmlParser::XmlParser()
{

}

bool XmlParser::CheckXMLError(XMLError error)
{
	if (error == XML_SUCCESS)
		return false;
	else
	{
		cout << "XML_ERROR when loading xml file" << endl;
		return true;
	}
	return false;
}

void XmlParser::load()
{
	XMLDocument xmlFile;
	XMLError error;
	XMLNode* node;
	XMLElement * element;

	error = xmlFile.LoadFile("ini\\SavedData.xm");
	if (error != XML_SUCCESS)
	{
		cout << "XML_ERROR loading xml from file." << endl;
		return;
	}
	node = xmlFile.FirstChild();
	if (node == nullptr)
	{
		cout << "XML_ERROR getting first node of the xml." << endl;
		return;
	}
	///window_x
	element = node->FirstChildElement("window_x");
	if (element == nullptr)
		cout << "XML_ERROR getting window_x element from the node." << endl;
	else
		error = element->QueryIntText(&window_x);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing window_x value to the variable." << endl;
	///window_y
	element = node->FirstChildElement("window_y");
	if (element == nullptr)
		cout << "XML_ERROR getting window_y element from the node." << endl;
	else
		error = element->QueryIntText(&window_y);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing window_y value to the variable." << endl;
	///window_w
	element = node->FirstChildElement("window_w");
	if (element == nullptr)
		cout << "XML_ERROR getting window_w element from the node." << endl;
	else
		error = element->QueryIntText(&window_w);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing window_w value to the variable." << endl;
	///window_h
	element = node->FirstChildElement("window_h");
	if (element == nullptr)
		cout << "XML_ERROR getting window_h element from the node." << endl;
	else
		error = element->QueryIntText(&window_h);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing window_h value to the variable." << endl;
	///fullscreen
	element = node->FirstChildElement("fullscreen");
	if(element == nullptr)
		cout << "XML_ERROR getting fullscreen element from the node." << endl;
	else
		error = element->QueryBoolText(&fullscreen);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing fullscreen value to the variable." << endl;
	///volumn_master
	element = node->FirstChildElement("volumn_master");
	if (element == nullptr)
		cout << "XML_ERROR getting volumn_master element from the node." << endl;
	else
		error = element->QueryIntText(&volumn_master);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing volumn_master value to the variable." << endl;
	///volumn_music
	element = node->FirstChildElement("volumn_music");
	if (element == nullptr)
		cout << "XML_ERROR getting volumn_music element from the node." << endl;
	else
		error = element->QueryIntText(&volumn_music);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing volumn_music value to the variable." << endl;
	///volumn_sfx
	element = node->FirstChildElement("volumn_sfx");
	if (element == nullptr)
		cout << "XML_ERROR getting volumn_sfx element from the node." << endl;
	else
		error = element->QueryIntText(&volumn_sfx);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing volumn_sfx value to the variable." << endl;

}

void XmlParser::save()
{
	XMLDocument xmlFile;
	XMLError error;
	XMLNode* node;
	XMLElement* element;
	node = xmlFile.NewElement("root");
	xmlFile.InsertFirstChild(node);
	///window_x & window_y
	SDL_GetWindowPosition(Main::Inst()->getWindow(), &window_x, &window_y);
	element = xmlFile.NewElement("window_x");
	element->SetText(window_x);
	node->InsertEndChild(element); 

	element = xmlFile.NewElement("window_y");
	element->SetText(window_y);
	node->InsertEndChild(element);
	///window_w
	element = xmlFile.NewElement("window_w");
	element->SetText(window_w);
	node->InsertEndChild(element);
	///window_h
	element = xmlFile.NewElement("window_h");
	element->SetText(window_h);
	node->InsertEndChild(element);
	///fullscreen
	element = xmlFile.NewElement("fullscreen");
	element->SetText(fullscreen);
	node->InsertEndChild(element);
	///volumn_master
	element = xmlFile.NewElement("volumn_master");
	element->SetText(volumn_master);
	node->InsertEndChild(element);
	///volumn_music
	element = xmlFile.NewElement("volumn_music");
	element->SetText(volumn_music);
	node->InsertEndChild(element);
	///volumn_sfx
	element = xmlFile.NewElement("volumn_sfx");
	element->SetText(volumn_sfx);
	node->InsertEndChild(element);

	error = xmlFile.SaveFile("ini\\SavedData.xm");
	if (error != XML_SUCCESS)
		cout << "XML_ERROR saving xml to the local file." << endl;
}