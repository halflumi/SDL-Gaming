#include "TextboxGroup.h"
#include "Main.h"
#include "TextureLoader.h"
#include "Camera.h"

TextboxGroup::TextboxGroup(int _duration, TextboxGroupType _textType)
{
	duration = _duration;
	textType = _textType;
	Load();
}

void TextboxGroup::Load()
{
	switch (textType)
	{
	case TextEquipmentDescription:
		background = true;
 		break;
	case TextSkillInfo:
		background = false;
		break;
	}
}

void TextboxGroup::update()
{
	int lineIndent = 0;
	int i, len = texts.size();

	switch (textType)
	{
	case TextEquipmentDescription:
		texts[0]->setPosition(position.x + 5, position.y);
		for (i = 1; i < len; i++)
		{
			lineIndent += TTF_FontLineSkip(Main::Inst()->getFont(texts[i - 1]->fontID));
			texts[i]->setPosition(position.x + 5, position.y + lineIndent);
		}
		break;
	case TextSkillInfo:
		texts[0]->setPosition(position.x, position.y);
		for (i = 1; i < len; i++)
		{
			lineIndent += TTF_FontLineSkip(Main::Inst()->getFont(texts[i - 1]->fontID));
			texts[i]->setPosition(position.x, position.y + lineIndent);
		}
		break;
	}
}

void TextboxGroup::draw()
{
	if (background)
		if (duration != -1)
			TextureLoader::Inst()->drawFrameEx(ItemInfoBackground, position.x - Camera::Inst()->getPosition().x + Main::Inst()->getRenderWidth() / 2, position.y - Camera::Inst()->getPosition().y + Main::Inst()->getRenderHeight() / 2, 10, 10, width, height, 0, 0, 0, 255);
		else
			TextureLoader::Inst()->drawFrameEx(ItemInfoBackground, position.x, position.y, 10, 10, width, height, 0, 0, 0, 255);

	int i, len = texts.size();
	for (i = 0; i < len; i++)
		texts[i]->draw();
}

void TextboxGroup::newLine(string text, int fontID, SDL_Color color)
{
	Textbox* newtext = new Textbox(position, text, fontID, color, duration);
	if (newtext->width > width)
		width = newtext->width + 10;
	height += TTF_FontLineSkip(Main::Inst()->getFont(fontID)) + 2;
	texts.push_back(newtext);
}

void TextboxGroup::clear()
{
	texts.clear();
	width = height = 0;
}