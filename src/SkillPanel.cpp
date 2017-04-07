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

#define SkillPhysicalTrainingPos	position.x + 40 , position.y + 73
#define SkillDoubleThrowPos			position.x + 40 , position.y + 148
#define SkillTripleThrowPos			position.x + 40 , position.y + 223
#define SkillLifeForcePos			position.x + 130, position.y + 73
#define SkillIronBodyPos			position.x + 130, position.y + 148
#define SkillLifeRegenerationPos	position.x + 130, position.y + 223
#define SkillMPBoostPos				position.x + 220, position.y + 73
#define SkillCriticalThrowPos		position.x + 40 , position.y + 298
#define SkillSummonAttackPos		position.x + 220, position.y + 148
#define SkillSpeedupPos				position.x + 220, position.y + 223

#define SkillPointsTextPos			position.x + 5, position.y + height - skillPointsText->height - 5
#define SkillInfoPos				pos.x + 309, pos.y + 58
#define SkillHotkeySlot1Pos_X		750
#define SkillHotkeySlot1Pos_Y		Main::Inst()->getRenderHeight() + 7
#define SkillHotkeySlot2Pos_X		782								  
#define SkillHotkeySlot2Pos_Y		Main::Inst()->getRenderHeight() + 7
#define SkillHotkeySlot3Pos_X		814								  
#define SkillHotkeySlot3Pos_Y		Main::Inst()->getRenderHeight() + 7

SkillSlot::SkillSlot(int skillID, Skill* _skill) : skillInfoTexts(-1, TextSkillInfo)
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
	else if (uniqueID == SkillSummonAttackIcon)
		skillIndex = SkillIndexSummonAttack;
	else if (uniqueID == SkillSpeedupIcon)
		skillIndex = SkillIndexSpeedupSkill;

	InitSkillInfo();
}

void SkillSlot::InitSkillInfo()
{
	skillInfoTexts.newLine(skill->name, segoeui22, COLOR_BLUE);
	switch (skillIndex)
	{
	case SkillIndexPhysicalTraining:
		skillInfoTexts.newLine("Improves ATT", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("permanently through", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("physical training.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("ATT: " + to_string(skill->percentATT) + "%", segoeui18, COLOR_BLACK);
		break;
	case SkillIndexDoubleThrow:
		skillInfoTexts.newLine("Throws two darts at", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("high speed.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("requires:", segoeui18, COLOR_RED);
		skillInfoTexts.newLine("[Physical Traning] Lv1", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("mp: " + to_string(skill->manaConsume), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("cd: " + to_string(skill->cooldownInterval / 60) + "s", segoeui18, COLOR_BLACK);
		break;
	case SkillIndexTripleThrow:
		skillInfoTexts.newLine("Throws three darts at", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("high speed.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("requires:", segoeui18, COLOR_RED);
		skillInfoTexts.newLine("[Double Throw] Lv2", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("mp: " + to_string(skill->manaConsume), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("cd: " + to_string(skill->cooldownInterval / 60) + "s", segoeui18, COLOR_BLACK);
		break;
	case SkillIndexLifeForce:
		skillInfoTexts.newLine("Strengthen your body", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("further using psychic", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("reinforcement.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("Max HP: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK);
		break;
	case SkillIndexIronBody:
		skillInfoTexts.newLine("Boosts DEF by a set", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("value.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("requires:", segoeui18, COLOR_RED);
		skillInfoTexts.newLine("[Life Force] Lv1", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("DEF: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK);
		break;
	case SkillIndexLifeRegeneration:
		skillInfoTexts.newLine("Decrease Life Regen", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Interval by percentage.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("requires:", segoeui18, COLOR_RED);
		skillInfoTexts.newLine("[Iron Body] Lv1", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("HP Regen Interval: -" + to_string(skill->minATT) + "%", segoeui18, COLOR_BLACK);
		break;
	case SkillIndexMPBoost:
		skillInfoTexts.newLine("Increase Max mana", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("permanently through", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("mental training.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("Max MP: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK);
		break;
	case SkillIndexCriticalThrow:
		skillInfoTexts.newLine("Increase Critical Hit", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Chance permanently.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("Crithit Chance: +" + to_string(skill->minATT), segoeui18, COLOR_BLACK);
		break;
	case SkillIndexSummonAttack:
		skillInfoTexts.newLine("Summon a soul to blast", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("the ground for you.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("requires:", segoeui18, COLOR_RED);
		skillInfoTexts.newLine("sp " + to_string(skill->sp), segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("[MP Boost] Lv1", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("mp: " + to_string(skill->manaConsume), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("cd: " + to_string(skill->cooldownInterval / 60) + "s", segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("ATT: " + to_string(skill->minATT) + "~" + to_string(skill->maxATT), segoeui18, COLOR_BLACK);
		break;
	case SkillIndexSpeedupSkill:
		skillInfoTexts.newLine("Use mogic to lighten", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("the step.", segoeui18, COLOR_GREY);
		skillInfoTexts.newLine("Lv. " + to_string(skill->level), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("mp: " + to_string(skill->manaConsume), segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("cd: " + to_string(skill->cooldownInterval / 60) + "s", segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("mov speed: +" + to_string(skill->minATT) + "%", segoeui18, COLOR_BLACK);
		skillInfoTexts.newLine("duration: " + to_string(skill->maxATT / 60) + "s", segoeui18, COLOR_BLACK);
		break;
	}
}

void SkillSlot::updateSkillInfo(Vector2D pos)
{
	skillInfoTexts.setPosition(SkillInfoPos);
	skillInfoTexts.update();
}

void SkillSlot::renderSkillInfo()
{
	skillInfoTexts.draw();
}

void SkillSlot::update()
{
	levelNumText->setPosition(position.x - 2, position.y - 5);
	if(active)
		if (to_string(skill->level) != levelNumText->text)
			levelNumText->changeText(to_string(skill->level));

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
	{
		mouseAbove = true;
		return true;
	}
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
	skills.push_back(new Skill(SkillSummonAttack, 0));
	skills.push_back(new Skill(SkillSpeedup, 0));
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
	skillslots.push_back(new SkillSlot(SkillSummonAttackIcon, skills[SkillIndexSummonAttack]));
	skillslots.push_back(new SkillSlot(SkillSpeedupIcon, skills[SkillIndexSpeedupSkill]));
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
	Skill* theskill = skills[selectedSkillIndex];
	
	skillButtons[selectedSkillIndex * 2]->setPosition(skillslots[selectedSkillIndex]->position.x - 14, skillslots[selectedSkillIndex]->position.y + 38);
	skillButtons[selectedSkillIndex * 2 + 1]->setPosition(skillslots[selectedSkillIndex]->position.x + GRIDSIZE + 4, skillslots[selectedSkillIndex]->position.y + 38);
	skillButtons[selectedSkillIndex * 2]->update();
	skillButtons[selectedSkillIndex * 2 + 1]->update();

	if (skillButtons[selectedSkillIndex * 2]->outsideUpdate()) // plus button being clicked
		if (skillPoints >= theskill->sp) // sufficient sp
			if (theskill->preSkillIndex == -1 || skills[theskill->preSkillIndex]->level >= theskill->preSkillLevel) // qualified prerequisite
				if(theskill->level < theskill->maxLevel) // not top yet
				{
					theskill->level++;
					skillPoints -= theskill->sp;
					skillslots[selectedSkillIndex]->refresh();
				}
	if (skillButtons[selectedSkillIndex * 2 + 1]->outsideUpdate()) // minus button being clicked
		if (theskill->level > 0) // sufficient level
			if (theskill->postSkillIndex == -1 || skills[theskill->postSkillIndex]->level == 0 || theskill->level > skills[theskill->postSkillIndex]->preSkillLevel) // qualified necessary conditions
			{
				theskill->level--;
				skillPoints += theskill->sp;
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
	skillslots[SkillIndexSummonAttack]->setPosition(SkillSummonAttackPos);
	skillslots[SkillIndexSpeedupSkill]->setPosition(SkillSpeedupPos);
	///fresh skillslots
	for (int i = 0; i < TOTALSKILLS; i++)
		skillslots[i]->update();
	///select skillslots and hotkey assignment
	for (int i = 0; i < TOTALSKILLS; i++)
	{
		if (skillslots[i]->checkMouseOver()) // give gray shadow feedback
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
	///update chosen skillslot
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
		TextureLoader::Inst()->drawEx2(skillslots[hotkeySkillIndexes[hotkey1]]->getUniqueID(), SkillHotkeySlot1Pos_X, SkillHotkeySlot1Pos_Y, skillslots[hotkeySkillIndexes[hotkey1]]->width, skillslots[hotkeySkillIndexes[hotkey1]]->height, SKILLGRIDSIZE, SKILLGRIDSIZE);
		if (skills[hotkeySkillIndexes[hotkey1]]->cooldownTick)
			TextureLoader::Inst()->drawEx2(GameMenuBackground, SkillHotkeySlot1Pos_X, SkillHotkeySlot1Pos_Y, 10, 10, SKILLGRIDSIZE, SKILLGRIDSIZE * (float)(skills[hotkeySkillIndexes[hotkey1]]->cooldownInterval - skills[hotkeySkillIndexes[hotkey1]]->cooldownTick) / skills[hotkeySkillIndexes[hotkey1]]->cooldownInterval);
	}
	if (hotkeySkillIndexes[hotkey2] != -1)
	{
		TextureLoader::Inst()->drawEx2(skillslots[hotkeySkillIndexes[hotkey2]]->getUniqueID(), SkillHotkeySlot2Pos_X, SkillHotkeySlot2Pos_Y, skillslots[hotkeySkillIndexes[hotkey2]]->width, skillslots[hotkeySkillIndexes[hotkey2]]->height, SKILLGRIDSIZE, SKILLGRIDSIZE);
		if (skills[hotkeySkillIndexes[hotkey2]]->cooldownTick)
			TextureLoader::Inst()->drawEx2(GameMenuBackground, SkillHotkeySlot2Pos_X, SkillHotkeySlot2Pos_Y, 10, 10, SKILLGRIDSIZE, SKILLGRIDSIZE * (float)(skills[hotkeySkillIndexes[hotkey2]]->cooldownInterval - skills[hotkeySkillIndexes[hotkey2]]->cooldownTick) / skills[hotkeySkillIndexes[hotkey2]]->cooldownInterval);
	}
	if (hotkeySkillIndexes[hotkey3] != -1)
	{
		TextureLoader::Inst()->drawEx2(skillslots[hotkeySkillIndexes[hotkey3]]->getUniqueID(), SkillHotkeySlot3Pos_X, SkillHotkeySlot3Pos_Y, skillslots[hotkeySkillIndexes[hotkey3]]->width, skillslots[hotkeySkillIndexes[hotkey3]]->height, SKILLGRIDSIZE, SKILLGRIDSIZE);
		if (skills[hotkeySkillIndexes[hotkey3]]->cooldownTick)
			TextureLoader::Inst()->drawEx2(GameMenuBackground, SkillHotkeySlot3Pos_X, SkillHotkeySlot3Pos_Y, 10, 10, SKILLGRIDSIZE, SKILLGRIDSIZE * (float)(skills[hotkeySkillIndexes[hotkey3]]->cooldownInterval - skills[hotkeySkillIndexes[hotkey3]]->cooldownTick) / skills[hotkeySkillIndexes[hotkey3]]->cooldownInterval);
	}
}