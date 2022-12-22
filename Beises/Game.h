#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <chrono>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Tower.h"
#include "UIElements.h"

#include "GameMath.h"

class Application
{
public:

	// constructor and desconstructor

	Application();
	~Application();

	// application functions

	void start();

	void update();

	void draw();

	// init functions

	void initVariables();

	void initPlayer();

	void initBullet();

	void initEnemy();

	void initTower();

	void initUI();

	void initAudio();

	// update functions

	void updateBullet();

	void updatePlayer();

	void updateEnemies();

	void updateTowers();

	void updateCollision();

	void updateUI();

	void updateResizeWindow();

	void updateMenu();

	void updateAudio();


	// draw functions

	void drawMenu();

	void drawButton(Button* button);
	
	void drawSlider(Slider* slider);

	void drawCheckBox(Checkbox* checkBox);

	void drawLabel(Label* label);
		
	// other functions

	void restartGame();

	void getRecordFromFile(int difficulty);

	void setRecordInFile(int difficulty);

	void configureDifficulty(int difficulty);

private:
	
	// Application
	int fps;
	int maxFps;
	bool init;
	sf::Image icon;
	sf::Image cursorGame;
	sf::Image cursorMenu;
	sf::ContextSettings settings;

	sf::Cursor cursor_game;
	sf::Cursor cursor_menu;

	// Window data
	int windowHeight;
	int windowWidth;

	int monitorResolution_x;
	int monitorResolution_y;

	sf::RenderWindow* window;
	sf::Event events;

	// Time data
	sf::Clock clock;
	float multiplier;
	float deltaTime;
	float mDeltaTime;

	// Entities
	Player* player;
	Bullet* bullet;
	Enemy* enemy;
	Tower* tower;

	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	std::vector<Tower> towers;

	// Game logic
	float shootDelayCount;
	float shootDelay;

	float enemySpawnDelayCount;
	float enemySpawnDelay;
	float enemySpawnLimit;
	
	float enemySpeed;

	float count;

	sf::Clock spawnClockTimer;

	bool end;
	bool pause;
	bool startGame;
	bool newBestScore;
	bool soundBestScoreAux;

	//circleSpawnEnemies : randomly spawn enemy at current position of the point circle
	float circleSpawnEnemiesVelocity;
	float circleSpawnEnemiesRadius;
	sf::Vector2f circleSpawnEnemiesPosition;


	//tower variables
	sf::Vector2f towerPosition;

	// towers position variables
	float rot;
	int nTowers;
	double spacing;
	float towerRadius;

	float towerMaxHp;
	float towerHpRectMaxSize;


	size_t smallDistanceTowerEnemyIndex;
	float smallDistanceTowerEnemy;
	float currentDistanceTowerEnemy;

	// player
	int playerScore;
	int bestScore;

	// ui

	sf::Font scoreFont;
	sf::Text scoreText;
	sf::Font endFont;
	sf::Text endText;
	sf::Font gameFont;
	sf::Text pauseText;
	sf::Text fpsText;

	int changeTextDifficulty;


	Button* button1;
	sf::Texture textureBG;
	sf::RectangleShape menuBackground;

	Button* buttonQuit;

	Button* buttonDifficulty;

	Button* buttonMenu;

	Slider* audioSlider;

	Slider* sfxSlider;

	Slider* fpsSlider;

	Checkbox* checkBoxShowFPS;

	Checkbox* checkBoxUnlimited;

	Label* bestRecordLabel;

	// file
	std::ofstream outputFile;
	std::ifstream inputFile;


	float center_x;
	float center_y;

	// audio
	// music

	sf::Music menuMusic;
	sf::Music gameMusic;

	//sfx

	
			 			 
	sf::SoundBuffer soundBuffer_hitEnemy;
	sf::SoundBuffer soundBuffer_newBestScore;
	sf::SoundBuffer soundBuffer_shoot;
	sf::SoundBuffer soundBuffer_DestroyTower;
	sf::SoundBuffer soundBuffer_towerHit;
	sf::SoundBuffer soundBuffer_gameOver;
	sf::SoundBuffer soundBuffer_pause;

	sf::Sound sound_pause;
	sf::Sound sound_gameOver;
	sf::Sound sound_towerHit;
	sf::Sound sound_hitEnemy;
	sf::Sound sound_newBestScore;
	sf::Sound sound_shoot;
	sf::Sound sound_DestroyTower;

	//debug

	int x_;
	int y_;
	int z_;

	Entity* debugRect;

	sf::Vertex* CreateLine(sf::Vector2f a, sf::Vector2f b);

	sf::Vertex* debugLine;

	//background

	sf::RectangleShape gameBackground;
	sf::Texture backgroundTexture;

	sf::RectangleShape menuBackgroundShape;
	sf::Texture menuBackgroundTexture;


};

#endif
