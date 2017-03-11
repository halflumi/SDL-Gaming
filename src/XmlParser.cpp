#include "XmlParser.h"

XmlParser* XmlParser::INSTANCE = 0;

XmlParser::XmlParser()
{
	fullscreen = false;
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
	XMLError error = xmlFile.LoadFile("ini\\SavedData.xml");
	XMLNode * node = xmlFile.FirstChild();

	XMLElement * element = node->FirstChildElement("fullscreen");
	error = element->QueryBoolText(&fullscreen);
}

void XmlParser::save()
{
	XMLDocument xmlFile;
	XMLNode* node = xmlFile.NewElement("root");
	xmlFile.InsertFirstChild(node);

	XMLElement* element = xmlFile.NewElement("fullscreen");
	element->SetText(fullscreen);
	node->InsertEndChild(element);

	XMLError error = xmlFile.SaveFile("ini\\SavedData.xml");
}