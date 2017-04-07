#include "XmlParser.h"
#include <SDL.h>
#include "Main.h"
#include "World.h"
#include "Camera.h"

XmlParser* XmlParser::INSTANCE = 0;

XmlParser::XmlParser() : inventory(INVENTORYSIZE * 2, NULL)
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
	///key_movingUp
	element = node->FirstChildElement("key_movingUp");
	if (element == nullptr)
		cout << "XML_ERROR getting key_movingUp element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_movingUp);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_movingUp value to the variable." << endl;
	///key_movingDown
	element = node->FirstChildElement("key_movingDown");
	if (element == nullptr)
		cout << "XML_ERROR getting key_movingDown element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_movingDown);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_movingDown value to the variable." << endl;
	///key_movingLeft
	element = node->FirstChildElement("key_movingLeft");
	if (element == nullptr)
		cout << "XML_ERROR getting key_movingLeft element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_movingLeft);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_movingLeft value to the variable." << endl;
	///key_movingRight
	element = node->FirstChildElement("key_movingRight");
	if (element == nullptr)
		cout << "XML_ERROR getting key_movingRight element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_movingRight);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_movingRight value to the variable." << endl;
	///key_openCharacter
	element = node->FirstChildElement("key_openCharacter");
	if (element == nullptr)
		cout << "XML_ERROR getting key_openCharacter element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_openCharacter);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_openCharacter value to the variable." << endl;
	///key_openSkill
	element = node->FirstChildElement("key_openSkill");
	if (element == nullptr)
		cout << "XML_ERROR getting key_openSkill element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_openSkill);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_openSkill value to the variable." << endl;
	///key_openInventory
	element = node->FirstChildElement("key_openInventory");
	if (element == nullptr)
		cout << "XML_ERROR getting key_openInventory element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_openInventory);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_openInventory value to the variable." << endl;
	///key_skillHotkey1
	element = node->FirstChildElement("key_skillHotkey1");
	if (element == nullptr)
		cout << "XML_ERROR getting key_skillHotkey1 element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_skillHotkey1);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_skillHotkey1 value to the variable." << endl;
	///key_skillHotkey2
	element = node->FirstChildElement("key_skillHotkey2");
	if (element == nullptr)
		cout << "XML_ERROR getting key_skillHotkey2 element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_skillHotkey2);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_skillHotkey2 value to the variable." << endl;
	///key_skillHotkey3
	element = node->FirstChildElement("key_skillHotkey3");
	if (element == nullptr)
		cout << "XML_ERROR getting key_skillHotkey3 element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_skillHotkey3);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_skillHotkey3 value to the variable." << endl;
	///key_skillHotkey4
	element = node->FirstChildElement("key_skillHotkey4");
	if (element == nullptr)
		cout << "XML_ERROR getting key_skillHotkey4 element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_skillHotkey4);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_skillHotkey4 value to the variable." << endl;
	///key_skillHotkey5
	element = node->FirstChildElement("key_skillHotkey5");
	if (element == nullptr)
		cout << "XML_ERROR getting key_skillHotkey5 element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_skillHotkey5);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_skillHotkey5 value to the variable." << endl;
	///key_skillHotkey6
	element = node->FirstChildElement("key_skillHotkey6");
	if (element == nullptr)
		cout << "XML_ERROR getting key_skillHotkey6 element from the node." << endl;
	else
		error = element->QueryIntText((SDL_Keycode*)&key_skillHotkey6);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing key_skillHotkey6 value to the variable." << endl;
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
	///key_movingUp
	element = xmlFile.NewElement("key_movingUp");
	element->SetText(key_movingUp);
	node->InsertEndChild(element);
	///key_movingDown
	element = xmlFile.NewElement("key_movingDown");
	element->SetText(key_movingDown);
	node->InsertEndChild(element);
	///key_movingLeft
	element = xmlFile.NewElement("key_movingLeft");
	element->SetText(key_movingLeft);
	node->InsertEndChild(element);
	///key_movingRight
	element = xmlFile.NewElement("key_movingRight");
	element->SetText(key_movingRight);
	node->InsertEndChild(element);
	///key_openCharacter
	element = xmlFile.NewElement("key_openCharacter");
	element->SetText(key_openCharacter);
	node->InsertEndChild(element);
	///key_openSkill
	element = xmlFile.NewElement("key_openSkill");
	element->SetText(key_openSkill);
	node->InsertEndChild(element);
	///key_openInventory
	element = xmlFile.NewElement("key_openInventory");
	element->SetText(key_openInventory);
	node->InsertEndChild(element);
	///key_skillHotkey1
	element = xmlFile.NewElement("key_skillHotkey1");
	element->SetText(key_skillHotkey1);
	node->InsertEndChild(element);
	///key_skillHotkey2
	element = xmlFile.NewElement("key_skillHotkey2");
	element->SetText(key_skillHotkey2);
	node->InsertEndChild(element);
	///key_skillHotkey3
	element = xmlFile.NewElement("key_skillHotkey3");
	element->SetText(key_skillHotkey3);
	node->InsertEndChild(element);
	///key_skillHotkey4
	element = xmlFile.NewElement("key_skillHotkey4");
	element->SetText(key_skillHotkey4);
	node->InsertEndChild(element);
	///key_skillHotkey5
	element = xmlFile.NewElement("key_skillHotkey5");
	element->SetText(key_skillHotkey5);
	node->InsertEndChild(element);
	///key_skillHotkey6
	element = xmlFile.NewElement("key_skillHotkey6");
	element->SetText(key_skillHotkey6);
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
	XMLElement* listElement;
	int i;

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
	///inventory
	element = node->FirstChildElement("inventory");
	if (element == nullptr)
		cout << "XML_ERROR getting inventory element from the node." << endl;
	listElement = element->FirstChildElement("item");
	cout << inventory.size() << endl;
	for (i = 0; i < INVENTORYSIZE * 2; i++)
	{
		int temp;
		error = listElement->QueryIntText(&temp);
		if (error != XML_SUCCESS)
			cout << "XML_ERROR passing inventory item value to the variable." << endl;
		inventory[i] = temp;
		listElement = listElement->NextSiblingElement("item");
	}
	///gold
	element = node->FirstChildElement("gold");
	if (element == nullptr)
		cout << "XML_ERROR getting gold element from the node." << endl;
	else
		error = element->QueryIntText(&gold);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR passing gold value to the variable." << endl;
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
	element->SetText(mapID);
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
	///inventory
	element = xmlFile.NewElement("inventory");
	for (const auto & item : Camera::Inst()->getTarget_nonConst()->inventory->items)
	{
		XMLElement* listElement;
		if (item->active)
		{
			listElement = xmlFile.NewElement("item");
			listElement->SetText(item->getUniqueID());
			element->InsertEndChild(listElement);
			listElement = xmlFile.NewElement("item");
			listElement->SetText(item->stack);
			element->InsertEndChild(listElement);
		}
		else
		{
		listElement = xmlFile.NewElement("item");
		listElement->SetText(NULL);
		element->InsertEndChild(listElement);
		listElement = xmlFile.NewElement("item");
		listElement->SetText(0);
		element->InsertEndChild(listElement);
		}
	}
	node->InsertEndChild(element);
	///gold
	element = xmlFile.NewElement("gold");
	element->SetText(player->gold);
	node->InsertEndChild(element);

	error = xmlFile.SaveFile(SavedataFile);
	if (error != XML_SUCCESS)
		cout << "XML_ERROR saving character to the local file." << endl;
}