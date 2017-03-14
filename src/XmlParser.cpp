#include "XmlParser.h"
#include <SDL.h>
#include "Main.h"
#include "World.h"
#include "Camera.h"

XmlParser* XmlParser::INSTANCE = 0;

XmlParser::XmlParser()
{

}

void XmlParser::load()
{
	XMLDocument xmlFile;
	XMLError error;
	XMLNode* node;
	XMLElement * element;

	error = xmlFile.LoadFile(SettingsFile);
	if (error != XML_SUCCESS)
	{
		cout << "XML_ERROR loading settings from file." << endl;
		return;
	}
	node = xmlFile.FirstChild();
	if (node == nullptr)
	{
		cout << "XML_ERROR getting first node of the settings xml." << endl;
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

	error = xmlFile.SaveFile(SettingsFile);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR saving settings to the local file." << endl;
}

void XmlParser::loadCharacter()
{
	XMLDocument xmlFile;
	XMLError error;
	XMLNode* node;
	XMLElement* element;

	error = xmlFile.LoadFile(SavedataFile);
	if (error != XML_SUCCESS)
	{
		cout << "XML_ERROR loading character from file." << endl;
		return;
	}
	node = xmlFile.FirstChild();
	if (node == nullptr)
	{
		cout << "XML_ERROR getting first node of the character xml." << endl;
		return;
	}	
	///mapID
	element = node->FirstChildElement("mapID");
	if (element == nullptr)
		cout << "XML_ERROR getting mapID element from the node." << endl;
	else
		error = element->QueryIntText(&mapID);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing mapID value to the variable." << endl;

	///level
	element = node->FirstChildElement("level");
	if (element == nullptr)
		cout << "XML_ERROR getting level element from the node." << endl;
	else
		error = element->QueryIntText(&level);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing level value to the variable." << endl;
	///xp
	element = node->FirstChildElement("xp");
	if (element == nullptr)
		cout << "XML_ERROR getting xp element from the node." << endl;
	else
		error = element->QueryIntText(&xp);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing xp value to the variable." << endl;
	///life
	element = node->FirstChildElement("life");
	if (element == nullptr)
		cout << "XML_ERROR getting life element from the node." << endl;
	else
		error = element->QueryIntText(&life);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing life value to the variable." << endl;
	///mana
	element = node->FirstChildElement("mana");
	if (element == nullptr)
		cout << "XML_ERROR getting mana element from the node." << endl;
	else
		error = element->QueryIntText(&mana);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing mana value to the variable." << endl;
}

void XmlParser::saveCharacter()
{
	XMLDocument xmlFile;
	XMLError error;
	XMLNode* node;
	XMLElement* element;
	node = xmlFile.NewElement("root");
	xmlFile.InsertFirstChild(node);

	const Player* player = Camera::Inst()->getTarget();
	///mapID
	element = xmlFile.NewElement("mapID");
	element->SetText(World::Inst()->currentMapID);
	node->InsertEndChild(element);
	///level
	element = xmlFile.NewElement("level");
	element->SetText(player->level);
	node->InsertEndChild(element);
	///xp
	element = xmlFile.NewElement("xp");
	element->SetText(player->exp);
	node->InsertEndChild(element);
	///life
	element = xmlFile.NewElement("life");
	element->SetText(player->life);
	node->InsertEndChild(element);
	///mana
	element = xmlFile.NewElement("mana");
	element->SetText(player->mana);
	node->InsertEndChild(element);

	error = xmlFile.SaveFile(SavedataFile);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR saving character to the local file." << endl;
}