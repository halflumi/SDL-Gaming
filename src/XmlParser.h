#pragma once
#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class XmlParser
{
private:
	XmlParser();
	~XmlParser() {}
	XmlParser(const XmlParser&);
	static XmlParser* INSTANCE;

	bool CheckXMLError(XMLError error);
public:
	bool fullscreen;

	static XmlParser* Inst()
	{
		if (INSTANCE == 0)
		{
			INSTANCE = new XmlParser();
			return INSTANCE;
		}

		return INSTANCE;
	}

	void load();
	void save();
};