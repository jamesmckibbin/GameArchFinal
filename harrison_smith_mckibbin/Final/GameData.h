#pragma once

#include <string>
#include <unordered_map>

using namespace std;
typedef std::string Key;

const float FRAME_RATE = 60.0;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// File Paths
const string DEAN_ASSET_PATH = "..\\..\\shared\\assets\\";
const string ART_ASSET_PATH = "..\\Art\\";
const string SOUND_ASSET_PATH = "..\\Sound\\";
const string DATA_ASSET_PATH = "..\\Data\\";

// Background Images
const string BACKGROUND_FILENAME = "Background.png";
const string START_BACKGROUND_FILENAME = "StartScreen.png";

// Player Animations
const string BANDIT_ANIM_FILENAME = "Bandit.png";
const string WIZARD_ANIM_FILENAME = "Wizard.png";
const string WARRIOR_ANIM_FILENAME = "Warrior.png";

// Attack Animations
const string PROJECTILE_FILENAME = "Projectile.png";
const string WARRIOR_SECOND_ATTACK_FILENAME = "WarriorSpecial.png";

// Enemy Animations
const string ENEMY_FILENAME = "Enemy.png";

// Audio Filenames
const string MAIN_MENU_MUSIC = "menu.wav";
const string LEVEL_MUSIC = "level.wav";

// Voice Clip Filenamse
const string WARRIOR_ATTACK = "WarriorAttack.wav";
const string WARRIOR_HURT = "WarriorHurt.wav";
const string WARRIOR_SPECIAL = "WarriorSpecial.wav";
const string BANDIT_ATTACK = "BanditAttack.wav";
const string BANDIT_HURT = "BanditHurt.wav";
const string BANDIT_SPECIAL = "BanditSpecial.wav";
const string WIZARD_ATTACK = "WizardAttack.wav";
const string WIZARD_HURT = "WizardHurt.wav";
const string WIZARD_SPECIAL = "WizardSpecial.wav";

// Data Filenames
const string SETTINGS_FILENAME = "settings.txt";
const string ENGLISH_LANGUAGE = "language_english.txt";
const string PIRATE_LANGUAGE = "language_pirate.txt";
const string UWU_LANGUAGE = "language_uwu.txt";

class FileData
{
public:
	FileData() {}
	~FileData() {}

	void loadData(const string& filename);
	int getIntData(const Key& key);
	float getFloatData(const Key& key);
	string getStringData(const Key& key);
private:
	std::unordered_map<Key, string> mData;
};
