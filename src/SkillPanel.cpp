#include "SkillPanel.h"
#include "Main.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "Inputor.h"
#include "Camera.h"
#include "Dice.h"
#include "Player.h"
#include "XmlParser.h"
#include <iostream>

#define GRIDSIZE 46
#define TITLEHEIGHT 53
#define HOTKEYNUMS	6
#define SKILLGRIDSIZE 30

#define CloseButtonPos				position.x + 460, position.y + 2

#define SkillPhysicalTrainingPos	position.x + 40, position.y + 118
#define SkillDoubleThrowPos			position.x + 40, position.y + 193
#define SkillTripleThrowPos			position.x + 40, position.y + 267
#define SkillLifeForcePos			position.x + 130, position.y + 118
#define SkillIronBodyPos			position.x + 130, position.y + 193
#define SkillLifeRegenerationPos	position.x + 130, position.y + 267
#define SkillMPBoostPos				position.x + 220, position.y + 118
#define SkillCriticalThrowPos		position.x + 220, position.y + 193

#define SkillPointsTextPos			position.x + 5, position.y + height - skillPointsText->getHeight() - 5
#define SkillInfoPos_X				pos.x + 309
#define SkillInfoPos_Y				pos.y + 58
#define SkillHotkeySlot1Pos_X		750
#define SkillHotkeySlot1Pos_Y		Main::Inst()->getRenderHeight() + 7
#define SkillHotkeySlot2Pos_X		782								  
#define SkillHotkeySlot2Pos_Y		Main::Inst()->getRenderHeight() + 7
#define SkillHotkeySlot3Pos_X		814								  
#define SkillHotkeySlot3Pos_Y		Main::Inst()->getRenderHeight() + 7

SkillSlot::SkillSlot(int skillID, Skill* _skill)
{
	if (skillID == NULL)
		active = false;	
	skill = _skill;
	uniqueID = skillID;
	Load();
}

void SkillSlot::refresh()
{
	skill->refresh();
	skillInfoTexts.clear();
	Load();
}

void SkillSlot::Load()
{
	width = height = GRIDSIZE;
	levelNumText = new Textbox(position, to_string(1), segoeui18, COLOR_BLACK, -1);
	mouseAbove = false;

	if (uniqueID == SkillPhysicalTrainingIcon)
		skillIndex = SkillIndexPhysicalTraining;
	else if (uniqueID == SkillDoubleThrowIcon)
		skillIndex = SkillIndexDoubleThrow;
	else if (uniqueID == SkillTripleThrowIcon)
		skillIndex = SkillIndexTripleThrow;
	else if (uniqueID == SkillLifeForceIcon)
		skillIndex = SkillIndexLifeForce;
	else if (uniqueID == SkillIronBodyIcon)
		skillIndex = SkillIndexIronBody;
	else if (uniqueID == SkillLifeRegenerationIcon)
		skillIndex = SkillIndexLifeRegeneration;
	else if (uniqueID == SkillMPBoostIcon)
		skillIndex = SkillIndexMPBoost;
	else if (uniqueID == SkillCriticalThrowIcon)
		skillIndex = SkillIndexCriticalThrow;


	InitSkillInfo();
}

void SkillSlot::InitSkillInfo()
{
	skillInfoTexts.push_back(new Textbox(position, skill->name, segoeui22, COLOR_BLUE, -1));
	switch (skillIndex)
	{
	case SkillIndexPhysicalTraining:
		skillInfoTexts.push_back(new Textbox(position, "Improves ATT", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "permanently through", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "physical training.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "ATT: " + to_string(skill->minATT) + "~" + to_string(skill->maxATT), segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexDoubleThrow:
		skillInfoTexts.push_back(new Textbox(position, "Throws two darts at", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "high speed.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "mp: " + to_string(skill->manaConsume), segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexTripleThrow:
		skillInfoTexts.push_back(new Textbox(position, "Throws three darts at", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "high speed.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "mp: " + to_string(skill->manaConsume), segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexLifeForce:
		skillInfoTexts.push_back(new Textbox(position, "Strengthen your body", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "further using psychic", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "reinforcement.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "Max HP: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexIronBody:
		skillInfoTexts.push_back(new Textbox(position, "Boosts DEF by a set", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "value.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "DEF: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexLifeRegeneration:
		skillInfoTexts.push_back(new Textbox(position, "Decrease Life Regenerate", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Interval by percentage.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "HP Regen Interval: -" + to_string(skill->minATT) + "%", segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexMPBoost:
		skillInfoTexts.push_back(new Textbox(position, "Increase Max mana", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "permanently through", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "mental training.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "Max MP: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK, -1));
		break;
	case SkillIndexCriticalThrow:
		skillInfoTexts.push_back(new Textbox(position, "Increase Critical Hit", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Chance permanently.", segoeui18, COLOR_GREY, -1));
		skillInfoTexts.push_back(new Textbox(position, "Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK, -1));
		skillInfoTexts.push_back(new Textbox(position, "Crithit Chance: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK, -1));
		break;
	}
}

void SkillSlot::updateSkillInfo(Vector2D pos)
{
	Vector2D infopos(SkillInfoPos_X, SkillInfoPos_Y);
	int lineIndent = TTF_FontLineSkip(Main::Inst()->getFont(segoeui18));
	int i, len = skillInfoTexts.size();
	skillInfoTexts[0]->setPosition(infopos);
	for (i = 1; i < len; i++)
		skillInfoTexts[i]->setPosition(SkillInfoPos_X, SkillInfoPos_Y + i * lineIndent);
}

void SkillSlot::renderSkillInfo()
{
	int i, len = skillInfoTexts.size();
	for (i = 0; i < len; i++)
		skillInfoTexts[i]->draw();
}

void SkillSlot::update()
{
	levelNumText->setPosition(position.x - 2, position.y - 5);
	if(active)
		if (to_string(skill->level) != levelNumText->text)
			levelNumText->changeText(to_string(skill->level));

	if (checkMouseOver())
		mouseAbove = true;
	else
		mouseAbove = false;
}

void SkillSlot::draw()
{
	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	levelNumText->draw();
	if (skill->cooldownTick)
		TextureLoader::Inst()->drawEx2(GameMenuBackground, position.x, position.y, 10, 10, width, height * (float)(skill->cooldownInterval - skill->cooldownTick) / skill->cooldownInterval);
	if (mouseAbove)
		TextureLoader::Inst()->drawFrameEx(InventoryGridMask, position.x, position.y, 10, 10, GRIDSIZE, GRIDSIZE, 0, 0, 0, 255);
}

bool SkillSlot::checkMouseOver()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();

	if (mousepos.x <= position.x + GRIDSIZE && mousepos.x >= position.x && mousepos.y >= position.y && mousepos.y <= position.y + GRIDSIZE)
		return true;
	return false;
}

//--------------------------------------------------------
SkillPanel::SkillPanel() : closeButton(InventoryCloseButton), selectCooldown(true), hotkeySkillIndexes(6, -1)
{
	uniqueID = SkillPanelPic;
	Load();
}

void SkillPanel::Load()
{
	width = 504;
	height = 384;
	position.x = 400;
	position.y = 100;

	selectedSkillIndex = -1;
	///load skills
	skills.push_back(new Skill(SkillPhysicalTraining, 0));
	skills.push_back(new Skill(SkillDoubleThrow, 0));
	skills.push_back(new Skill(SkillTripleThrow, 0));
	skills.push_back(new Skill(SkillLifeForce, 0));
	skills.push_back(new Skill(SkillIronBody, 0));
	skills.push_back(new Skill(SkillLifeRegeneration, 0));
	skills.push_back(new Skill(SkillMPBoost, 0));
	skills.push_back(new Skill(SkillCriticalThrow, 0));
	///register skill buttons
	for (int i = 0; i < TOTALSKILLS; i++)
	{
		skillButtons.push_back(new Button(SkillPanelAddSkillButton));
		skillButtons.push_back(new Button(SkillPanelMinusSkillButton));
	}
	///register skill slots
	skillslots.push_back(new SkillSlot(SkillPhysicalTrainingIcon, skills[SkillIndexPhysicalTraining]));
	skillslots.push_back(new SkillSlot(SkillDoubleThrowIcon, skills[SkillIndexDoubleThrow]));
	skillslots.push_back(new SkillSlot(SkillTripleThrowIcon, skills[SkillIndexTripleThrow]));
	skillslots.push_back(new SkillSlot(SkillLifeForceIcon, skills[SkillIndexLifeForce]));
	skillslots.push_back(new SkillSlot(SkillIronBodyIcon, skills[SkillIndexIronBody]));
	skillslots.push_back(new SkillSlot(SkillLifeRegenerationIcon, skills[SkillIndexLifeRegeneration]));
	skillslots.push_back(new SkillSlot(SkillMPBoostIcon, skills[SkillIndexMPBoost]));
	skillslots.push_back(new SkillSlot(SkillCriticalThrowIcon, skills[SkillIndexCriticalThrow]));
	///load skill points
	skillPoints = 10;
	skillPointsText = new Textbox(position, "sp: 1", arial28_bold, COLOR_BLACK, -1);
}

void SkillPanel::update()
{
	Player* player = Camera::Inst()->getTarget_nonConst();

	closeButton.setPosition(CloseButtonPos);
	closeButton.update();
	if (closeButton.outsideUpdate())
	{
		selectedSkillIndex = -1;
		active = false;
		player->mouseCooldown.start();
	}

	UpdateSkillButtons();
	UpdateSkillSlots();
	skillPointsText->changeText("sp: " + to_string(skillPoints));
}

void SkillPanel::UpdateSkillButtons()
{
	if (selectedSkillIndex == -1)
		return;
	Player* player = Camera::Inst()->getTarget_nonConst();
	
	skillButtons[selectedSkillIndex * 2]->setPosition(skillslots[selectedSkillIndex]->getPosition().x - 14, skillslots[selectedSkillIndex]->getPosition().y + 38);
	skillButtons[selectedSkillIndex * 2 + 1]->setPosition(skillslots[selectedSkillIndex]->getPosition().x + GRIDSIZE + 4, skillslots[selectedSkillIndex]->getPosition().y + 38);
	skillButtons[selectedSkillIndex * 2]->update();
	skillButtons[selectedSkillIndex * 2 + 1]->update();

	if (skillPoints > 0 && (skills[selectedSkillIndex]->preSkillIndex == -1 || skills[skills[selectedSkillIndex]->preSkillIndex]->level > 0))
		if (skillButtons[selectedSkillIndex * 2]->outsideUpdate())
		{
			skills[selectedSkillIndex]->level++;
			skillPoints--;
			skillslots[selectedSkillIndex]->refresh();
		}
	if (skills[selectedSkillIndex]->level > 0 && (skills[selectedSkillIndex]->postSkillIndex == -1 || skills[skills[selectedSkillIndex]->postSkillIndex]->level == 0))
		if (skillButtons[selectedSkillIndex * 2 + 1]->outsideUpdate())
		{
			skills[selectedSkillIndex]->level--;
			skillPoints++;
			skillslots[selectedSkillIndex]->refresh();
		}
}

void SkillPanel::UpdateSkillSlots()
{
	skillslots[SkillIndexPhysicalTraining]->setPosition(SkillPhysicalTrainingPos);
	skillslots[SkillIndexDoubleThrow]->setPosition(SkillDoubleThrowPos);
	skillslots[SkillIndexTripleThrow]->setPosition(SkillTripleThrowPos);
	skillslots[SkillIndexLifeForce]->setPosition(SkillLifeForcePos);
	skillslots[SkillIndexIronBody]->setPosition(SkillIronBodyPos);
	skillslots[SkillIndexLifeRegeneration]->setPosition(SkillLifeRegenerationPos);
	skillslots[SkillIndexMPBoost]->setPosition(SkillMPBoostPos);
	skillslots[SkillIndexCriticalThrow]->setPosition(SkillCriticalThrowPos);
	///select and hotkey assignment
	for (int i = 0; i < TOTALSKILLS; i++)
	{
		if (skillslots[i]->checkMouseOver())
		{
			if (Inputor::Inst()->getMouseButtonState(MOUSE_LEFT) && selectCooldown.getTicks() > CLICKCOOLDOWN)
			{
				selectCooldown.start();
				selectedSkillIndex = i;
			}
			if (skills[i]->level > 0 && !skills[i]->passive)
			{
				if (Inputor::Inst()->isKeyDown(XmlParser::Inst()->key_skillHotkey1))
					hotkeySkillIndexes[hotkey1] = i;
				else if (Inputor::Inst()->isKeyDown(XmlParser::Inst()->key_skillHotkey2))
					hotkeySkillIndexes[hotkey2] = i;
				else if (Inputor::Inst()->isKeyDown(XmlParser::Inst()->key_skillHotkey3))
					hotkeySkillIndexes[hotkey3] = i;
			}
		}
	}
	///fresh skillslots
	for (int i = 0; i < TOTALSKILLS; i++)
		skillslots[i]->update();
	///update chosen
	if (selectedSkillIndex != -1)
		skillslots[selectedSkillIndex]->updateSkillInfo(position);
	skillPointsText->setPosition(SkillPointsTextPos);
}

void SkillPanel::draw()
{
	Player* player = Camera::Inst()->getTarget_nonConst();

	TextureLoader::Inst()->draw(uniqueID, position.x, position.y, width, height);
	closeButton.draw();

	///draw skillslots
	for (int i = 0; i < TOTALSKILLS; i++)
		skillslots[i]->draw();
	///draw chosen elements
	if (selectedSkillIndex != -1)
	{
		skillslots[selectedSkillIndex]->renderSkillInfo();
		skillButtons[selectedSkillIndex * 2]->draw();
		skillButtons[selectedSkillIndex * 2 + 1]->draw();
	}
	skillPointsText->draw();
}

bool SkillPanel::outsideCheckMouseTitle()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.y <= position.y + TITLEHEIGHT)
		return true;
	return false;
}

bool SkillPanel::outsideCheckMouseOver()
{
	Vector2D mousepos = Inputor::Inst()->getMouseRelativePosition();
	if (mousepos.x <= position.x + width && mousepos.x >= position.x && mousepos.y >= position.y && mousepos.y <= position.y + height)
		return true;
	return false;
}

void SkillPanel::outsideUpdateSkills()
{
	for (int i = 0; i < TOTALSKILLS; i++)
		skills[i]->update();
}

void SkillPanel::outsideDrawHotkeys()
{
	if (hotkeySkillIndexes[hotkey1] != -1)
	{
		TextureLoader::Inst()->drawEx2(skillslots[hotkeySkillIndexes[hotkey1]]->getUniqueID(), SkillHotkeySlot1Pos_X, SkillHotkeySlot1Pos_Y, skillslots[hotkeySkillIndexes[hotkey1]]->getWidth(), skillslots[hotkeySkillIndexes[hotkey1]]->getHeight(), SKILLGRIDSIZE, SKILLGRIDSIZE);
		if (skills[hotkeySkillIndexes[hotkey1]]->cooldownTick)
			TextureLoader::Inst()->drawEx2(GameMenuBackground, SkillHotkeySlot1Pos_X, SkillHotkeySlot1Pos_Y, 10, 10, SKILLGRIDSIZE, SKILLGRIDSIZE * (float)(skills[hotkeySkillIndexes[hotkey1]]->cooldownInterval - skills[hotkeySkillIndexes[hotkey1]]->cooldownTick) / skills[hotkeySkillIndexes[hotkey1]]->cooldownInterval);
	}
	if (hotkeySkillIndexes[hotkey2] != -1)
	{
		TextureLoader::Inst()->drawEx2(skillslots[hotkeySkillIndexes[hotkey2]]->getUniqueID(), SkillHotkeySlot2Pos_X, SkillHotkeySlot2Pos_Y, skillslots[hotkeySkillIndexes[hotkey2]]->getWidth(), skillslots[hotkeySkillIndexes[hotkey2]]->getHeight(), SKILLGRIDSIZE, SKILLGRIDSIZE);
		if (skills[hotkeySkillIndexes[hotkey2]]->cooldownTick)
			TextureLoader::Inst()->drawEx2(GameMenuBackground, SkillHotkeySlot2Pos_X, SkillHotkeySlot2Pos_Y, 10, 10, SKILLGRIDSIZE, SKILLGRIDSIZE * (float)(skills[hotkeySkillIndexes[hotkey2]]->cooldownInterval - skills[hotkeySkillIndexes[hotkey2]]->cooldownTick) / skills[hotkeySkillIndexes[hotkey2]]->cooldownInterval);
	}
	if (hotkeySkillIndexes[hotkey3] != -1)
	{
		TextureLoader::Inst()->drawEx2(skillslots[hotkeySkillIndexes[hotkey3]]->getUniqueID(), SkillHotkeySlot3Pos_X, SkillHotkeySlot3Pos_Y, skillslots[hotkeySkillIndexes[hotkey3]]->getWidth(), skillslots[hotkeySkillIndexes[hotkey3]]->getHeight(), SKILLGRIDSIZE, SKILLGRIDSIZE);
		if (skills[hotkeySkillIndexes[hotkey3]]->cooldownTick)
			TextureLoader::Inst()->drawEx2(GameMenuBackground, SkillHotkeySlot3Pos_X, SkillHotkeySlot3Pos_Y, 10, 10, SKILLGRIDSIZE, SKILLGRIDSIZE * (float)(skills[hotkeySkillIndexes[hotkey3]]->cooldownInterval - skills[hotkeySkillIndexes[hotkey3]]->cooldownTick) / skills[hotkeySkillIndexes[hotkey3]]->cooldownInterval);
	}
}