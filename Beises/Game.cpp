#include "Game.h"


// ---------------------------------------- CONSTRUCTOR AND DESTRUCTOR ----------------------------------------


Application::Application()
{
	init = true;

	initVariables();
	initPlayer();
	initBullet();
	initEnemy();
	initTower();
	initUI();
	initAudio();
	

	init = false;

	restartGame();
	// Debug
	debugRect = new Entity(window);
	debugLine = CreateLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 100.0f));
}

Application::~Application()
{
	delete window;
	delete player;
	delete bullet;
	delete tower;
	delete debugLine;
	delete enemy;

	delete button1;
	delete audioSlider;
	delete fpsSlider;
	delete checkBoxShowFPS;
	delete checkBoxUnlimited;
	delete buttonQuit;
	delete bestRecordLabel;
	delete buttonDifficulty;
	delete buttonMenu;
	delete sfxSlider;

	// Debug
	delete debugRect;
}


// ---------------------------------------- APPLICATION FUNCTIONS ----------------------------------------


void Application::start()
{

	debugRect->loadSprite("../assets/texture/debug.png");

	debugRect->shape.setOrigin(debugRect->shape.getGlobalBounds().width / 2.0f,
	debugRect->shape.getGlobalBounds().height / 2.0f);

	// debug end

	// file


	srand(unsigned int(time(NULL)));

	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		mDeltaTime = deltaTime * multiplier;

		while (window->pollEvent(events))
		{
			if (events.type == sf::Event::KeyPressed)
			{
				if (events.key.code == sf::Keyboard::Backspace)
				{
					window->close();
				}
				if (events.key.code == sf::Keyboard::Escape || events.key.code == sf::Keyboard::Space)
				{
					if (startGame && !end)
					{
						if (pause == false)
						{
							window->setMouseCursor(cursor_menu);
							pause = true;
							sound_pause.play();
						}
						else
						{
							window->setMouseCursor(cursor_game);
							sound_pause.play();
							pause = false;
						}
					}
				}
				if (events.key.code == sf::Keyboard::R)
				{
					restartGame();
					window->setMouseCursor(cursor_menu);
					window->setFramerateLimit(60);
				}
			}
			if (events.type == sf::Event::Closed)
			{
				window->close();
			}
			if (events.type == sf::Event::Resized)
			{
				updateResizeWindow();
			}
		}

		if (!startGame)
		{
			// menu

			//menu.button1("../assets/ui/button_1_normal.png");
			

			// update menu
			updateAudio();
			


			bestRecordLabel->labelText.setString(std::string("Best score: ").append(std::to_string(bestScore)));
			bestRecordLabel->updatePosition();

			button1->update();
			

			buttonQuit->update();
			

			if (button1->hasClicked())
			{
				gameMusic.play();
				menuMusic.stop();
				window->setMouseCursor(cursor_game);
				startGame = true;
				window->setFramerateLimit(int(fpsSlider->getProgress()));
				if(checkBoxUnlimited->getState())
				{
					window->setFramerateLimit(0);
				}
			}
			if(buttonQuit->hasClicked())
			{
				window->close();
			}
			if (buttonDifficulty->hasClicked())
			{
				changeTextDifficulty = (changeTextDifficulty + 1) % 3;

				switch (changeTextDifficulty)
				{
				case 0:
					buttonDifficulty->label.setString("easy");
					break;
				case 1:
					buttonDifficulty->label.setString("normal");
					break;
				case 2:
					buttonDifficulty->label.setString("hard");
					break;
				}

				configureDifficulty(changeTextDifficulty);

			}
			buttonDifficulty->update();
			
			

			checkBoxShowFPS->updateCheckBox();
			checkBoxShowFPS->setAudioVolume(sfxSlider->getProgress());


			checkBoxUnlimited->updateCheckBox();
			checkBoxUnlimited->setAudioVolume(sfxSlider->getProgress());

			fpsSlider->updateSlider();

			sfxSlider->updateSlider();

			// draw menu
			
			drawMenu();

		}
		else
		{
			// game
			if (!pause && !end)
			{
				update();
			}

			// fps
			fps = int(1.0f / deltaTime);

			fpsText.setString(std::to_string(fps));

			draw();
		}
	}
}

void Application::update()
{
	if (playerScore > bestScore)
	{
		//std::cout << "nova melhor pontuacao" << '\n';
		bestScore = playerScore;
		setRecordInFile(changeTextDifficulty);

		newBestScore = true;
	}

	//std::cout << bestScore << '\n';

	player->lookAtMouse();

	updateBullet();

	updateEnemies();

	updateCollision();

	updateTowers();

	updateUI();

	if (towers.size() <= 0 && !newBestScore)
	{
		sound_gameOver.play();
		end = true;
	}
	else if(towers.size() <= 0)
 	{
		sound_newBestScore.play();
		end = true;
	}

	

	// Debug
	debugRect->shape.setPosition(circleSpawnEnemiesPosition);

}

void Application::draw()
{
	window->clear(sf::Color(36, 67, 79, 255));

	// background

	for (size_t i = 0; i < monitorResolution_x / 1920; i++)
	{
		gameBackground.setPosition(gameBackground.getSize().x * i, 0.0f);
		window->draw(gameBackground);

		gameBackground.setPosition(0.0f, gameBackground.getSize().y * i);
		window->draw(gameBackground);
	}
	
	if (checkBoxShowFPS->getState())
	{
		window->draw(fpsText);
	}

	// draw player
	window->draw(player->shape);

	//draw towers
	for (size_t i = 0; i < towers.size(); i++)
	{
		window->draw(towers[i].shape);
		window->draw(towers[i].hpRect);
	}

	// draw bullets
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window->draw(bullets[i].shape);
	}

	// draw enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window->draw(enemies[i].shape);
	}


	// draw ui elements

	window->draw(scoreText);

	if(end)
	{
		if (newBestScore)
		{
			endText.setString(std::string("Game Over!   New best score! ").append(std::to_string(bestScore)));
			endText.setPosition(sf::Vector2f((windowWidth / 2.0f) - endText.getGlobalBounds().width / 2.0f, (windowHeight / 2.0f) - 480.0f));

			//endText.setString("New best score!");
			//newBestScore = false;
		}
		else
		{
			//std::cout << "newBestScore: " << newBestScore << '\n';
			endText.setString("Game Over!");
			endText.setPosition(sf::Vector2f((windowWidth / 2.0f) - endText.getGlobalBounds().width / 2.0f, (windowHeight / 2.0f) - 480.0f));
		}
		


		window->draw(endText);

		buttonMenu->update();
		drawButton(buttonMenu);
		if (buttonMenu->hasClicked())
		{
			restartGame();
			window->setMouseCursor(cursor_menu);
			window->setFramerateLimit(60);
		}
	}
	if (pause && !end)
	{
		window->draw(pauseText);

		buttonMenu->update();
		drawButton(buttonMenu);
		if (buttonMenu->hasClicked())
		{
			restartGame();
			window->setMouseCursor(cursor_menu);
			window->setFramerateLimit(60);
		}
	}

	// debug draw

	//window->draw(debugRect->shape);

	//window->draw(debugLine, 2, sf::Lines);

	window->display();
}


// ---------------------------------------- INIT FUNCTIONS ----------------------------------------


void Application::initVariables()
{
	//debug
	x_ = 0;
	y_ = 0;
	z_ = 0;

	

	// vector
	enemies.reserve(size_t(1000));
	bullets.reserve(size_t(500));

	// FPS control
	maxFps = 10000;
	fps = 0;
	multiplier = 62.50f;
	deltaTime = 0.0f;
	mDeltaTime = multiplier * deltaTime;

	// Window size
	windowWidth = 1920;
	windowHeight = 1080;

	monitorResolution_x = sf::VideoMode::getDesktopMode().width;
	monitorResolution_y = sf::VideoMode::getDesktopMode().height;

	// anti-aliasing
	settings.antialiasingLevel = 16;

	// Window
	this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Beises", sf::Style::Fullscreen, settings);
	window->setFramerateLimit(fps);
	icon.loadFromFile("../assets/texture/beises_icon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	cursorGame.loadFromFile("../assets/texture/beises_cursor_game.png");
	cursorMenu.loadFromFile("../assets/texture/beises_cursor_menu.png");

	cursor_menu.loadFromPixels(cursorMenu.getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(0, 0));
	cursor_game.loadFromPixels(cursorGame.getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(16, 16));

	window->setMouseCursor(cursor_menu);
		
	// Game logic
	shootDelay = 8.0f;
	shootDelayCount = 0.0f;

	enemySpawnDelayCount = 0.0f;
	enemySpawnDelay = 15.0f;
	enemySpawnLimit = 1000;
	enemySpeed = 0.0f;

	count = 0.0f;

	end = false;
	pause = false;
	startGame = false;
	newBestScore = false;
	soundBestScoreAux = false;

	circleSpawnEnemiesVelocity = 15.0f;
	circleSpawnEnemiesRadius = 1100.0f;
	circleSpawnEnemiesPosition = sf::Vector2f(0.0f, 0.0f);

	towerPosition = sf::Vector2f(0.0f, 0.0f);
	rot = 0.0f;
	nTowers = 1;
	spacing = PI * 2.0f / nTowers;
	towerRadius = 130.0f;

	towerMaxHp = 10;
	towerHpRectMaxSize = 50.0f;
	
	smallDistanceTowerEnemy = 0.0f;
	currentDistanceTowerEnemy = 0.0f;
	smallDistanceTowerEnemyIndex = 0;


	playerScore = 0;
	bestScore = 0;

	// file
	//getRecordFromFile(0);

	// background
	
	backgroundTexture.loadFromFile("../assets/texture/bg5.png");

	gameBackground.setPosition(sf::Vector2f(0.0f, 0.0f));
	gameBackground.setTexture(&backgroundTexture);
	gameBackground.setSize(sf::Vector2f(1920, 1080));


	menuBackgroundTexture.loadFromFile("../assets/texture/menu_bg.png");

	menuBackgroundShape.setPosition(sf::Vector2f((windowWidth / 2.0f) - 250.0f, (windowHeight / 2.0f) - 500.0f));
	menuBackgroundShape.setTexture(&menuBackgroundTexture);
	menuBackgroundShape.setSize(sf::Vector2f(500.0f, 900.0f));

	changeTextDifficulty = 0;
	configureDifficulty(changeTextDifficulty);
}

void Application::initPlayer()
{
	player = new Player(window);

	//player->shape.setFillColor(sf::Color::Blue);
	//player->shape.setSize(sf::Vector2f(100.0f, 100.0f));
		
	player->loadSprite("../assets/texture/arrow.png");

	player->shape.setOrigin(player->shape.getGlobalBounds().width / 2.0f,
							player->shape.getGlobalBounds().height / 2.0f);
	
	player->shape.setPosition(float(windowWidth / 2), float(windowHeight / 2));

	//std::cout << player->shape.getOrigin().x << ' '<< player->shape.getOrigin().y;
	
	player->shape.setScale(sf::Vector2f(7.0f, 7.0f));
}

void Application::initBullet()
{
	bullet = new Bullet(window);

	//bullet->shape.setFillColor(sf::Color::Red);
	//bullet->shape.setSize(sf::Vector2f(15.0f, 15.0f));

	bullet->loadSprite("../assets/texture/arrow.png");

	bullet->setSpeed(15.0f);

	bullet->shape.setOrigin(bullet->shape.getGlobalBounds().width / 2.0f,
							bullet->shape.getGlobalBounds().height / 2.0f);

	//bullet->shape.setPosition(player->shape.getPosition().x, player->shape.getPosition().y);
	bullet->shape.setPosition(float(windowWidth / 2), float(windowHeight / 2));
}

void Application::initTower()
{

	if (init == true)
	{
		tower = new Tower(window);
		tower->loadSprite("../assets/texture/tower_test.png");
		tower->shape.setOrigin(tower->shape.getGlobalBounds().width / 2.0f, tower->shape.getGlobalBounds().height / 2.0f);
		tower->shape.setScale(5.0f, 5.0f);
	}

	tower->setHp(int(towerMaxHp));

	for (size_t i = 1; i <= nTowers; i++)
	{
		towerPosition.x = float(sin(spacing * i) * towerRadius) + float(windowWidth / 2.0f);
		towerPosition.y = float(cos(spacing * i) * towerRadius) + float(windowHeight / 2.0f);
	
		// std::cout << towerPosition.x << '/' << towerPosition.y << '\n';
		tower->hpRect.setSize(sf::Vector2f(towerHpRectMaxSize, 2.0f));
		tower->shape.setPosition(towerPosition);
		tower->hpRect.setPosition(tower->shape.getPosition().x - tower->shape.getGlobalBounds().width / 2.0f, tower->shape.getPosition().y - tower->shape.getGlobalBounds().height + 20);
		towers.push_back(*tower);
	}
}

void Application::initEnemy()
{
	if (init == true)
	{
		enemy = new Enemy(window);
		enemy->loadSprite("../assets/texture/enemy_3.png");

		enemy->shape.setOrigin(enemy->shape.getGlobalBounds().width / 2.0f,
			enemy->shape.getGlobalBounds().height / 2.0f);

	}
	//enemy->setSpeed(enemySpeed);

	enemy->shape.setPosition(100.0f, 100.0f);
	enemy->shape.setScale(sf::Vector2f(4.5, 4.5f));
}

void Application::initUI()
{

	if (!scoreFont.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf"))
	{
		std::cerr << "Error: failed to load font\n";
	}
	else
	{
		scoreText.setCharacterSize(25);
		scoreText.move(2.0f, 2.0f);
		scoreText.setFont(scoreFont);
		scoreText.setString("Score 0");

	}
	
	if (!endFont.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf"))
	{
		std::cerr << "Error: failed to load font\n";
	}
	else
	{
		endText.setFont(endFont);
		endText.setString("Game Over!");
		endText.setPosition(sf::Vector2f((windowWidth / 2.0f) - endText.getGlobalBounds().width / 2.0f, (windowHeight / 2.0f) - 480.0f));
	}

	if (!gameFont.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf"))
	{
		std::cerr << "Error: failed to load font\n";
	}
	else
	{
		pauseText.setFont(endFont);
		fpsText.setFont(endFont);
		fpsText.setCharacterSize(23);
		fpsText.setPosition(sf::Vector2f(windowWidth - 200.0f, 0.0f));

		pauseText.setString("Pause");
		pauseText.setCharacterSize(40);
		pauseText.setPosition(sf::Vector2f((windowWidth / 2.0f) - pauseText.getGlobalBounds().width / 2.0f, (windowHeight / 2.0f) - 480.0f));
		

	}
	
	changeTextDifficulty = 0;

	// menu

	// menu elements

	//start button
	button1 = new Button(window, 0.0f, -150.0f, 4.0f, "../assets/ui/button_1_normal.png", "../assets/ui/button_1_hovered.png", "../assets/ui/button_1_clicked.png", "Start");

	buttonQuit = new Button(window, 0.0f, -50.0f, 4.0f, "../assets/ui/button_1_normal.png", "../assets/ui/button_1_hovered.png", "../assets/ui/button_1_clicked.png", "Quit");
	
	buttonDifficulty = new Button(window, 0.0f, -250.0f, 4.0f, "../assets/ui/button_1_normal.png", "../assets/ui/button_1_hovered.png", "../assets/ui/button_1_clicked.png", "Easy");

	buttonMenu = new Button(window, 0.0f, -350.0f, 4.0f, "../assets/ui/button_1_normal.png", "../assets/ui/button_1_hovered.png", "../assets/ui/button_1_clicked.png", "Menu");

	audioSlider = new Slider(window, -150.0f, 150.0f, 70.0f, 0.0f, 100.0f, "Audio");

	fpsSlider = new Slider(window, -150.0f, 250.0f, 120.0f, 15.0f, 500.0f, "FPS");

	sfxSlider = new Slider(window, -150.0f, 350.0f, 40.0f, 0.0f, 100.0f, "SFX");

	checkBoxShowFPS = new Checkbox(window, -150.0f, 50.0f, false, "Show FPS");

	checkBoxUnlimited = new Checkbox(window, -150.0f, 0.0f, true, "Unlimited FPS");

	bestRecordLabel = new Label(window, 0.0f, -400.0f, "");

	window->setFramerateLimit(int(fpsSlider->getProgress()));

	// text



	updateMenu();

}

void Application::initAudio()
{
	menuMusic.openFromFile("../assets/music/The-Grand-Affair-Coupe.wav");
	menuMusic.setLoop(true);

	gameMusic.openFromFile("../assets/music/Kevin-MacLeod-Itty-Bitty-8-Bit.wav");
	gameMusic.setLoop(true);

	menuMusic.play();

	// sfx
	soundBuffer_shoot.loadFromFile("../assets/sfx/laserSmall_004.ogg");
	soundBuffer_hitEnemy.loadFromFile("../assets/sfx/mixkit-game-ball-tap-2073.wav");
	soundBuffer_DestroyTower.loadFromFile("../assets/sfx/minimize_001.ogg");
	soundBuffer_towerHit.loadFromFile("../assets/sfx/bong_001.ogg");
	soundBuffer_gameOver.loadFromFile("../assets/sfx/mixkit-funny-game-over-2878.wav");
	soundBuffer_pause.loadFromFile("../assets/sfx/switch_002.ogg");
	soundBuffer_newBestScore.loadFromFile("../assets/sfx/mixkit-video-game-treasure-2066.wav");


	sound_newBestScore.setBuffer(soundBuffer_newBestScore);
	sound_pause.setBuffer(soundBuffer_pause);
	sound_gameOver.setBuffer(soundBuffer_gameOver);
	sound_towerHit.setBuffer(soundBuffer_towerHit);
	sound_DestroyTower.setBuffer(soundBuffer_DestroyTower);
	sound_shoot.setBuffer(soundBuffer_shoot);
	sound_hitEnemy.setBuffer(soundBuffer_hitEnemy);
	

}


// FILE FUNCTIONS

void Application::setRecordInFile(int difficulty)
{
	int score[3]{ 0 };
	int bestScoreBackup = bestScore;

	for (size_t i = 0; i < 3; i++)
	{
		if (difficulty != i)
		{
			getRecordFromFile(int(i));
			score[i] = bestScore;
		}
		else
		{
			score[i] = bestScoreBackup;
		}
	}

	outputFile.open("../info/record.txt");

	for (size_t i = 0; i < 3; i++)
	{
		outputFile << score[i] << " ";
	}

	bestScore = bestScoreBackup;
	outputFile.close();
}

void Application::getRecordFromFile(int difficulty)
{
	difficulty++;
	// load file
	inputFile.open("../info/record.txt");

	for (size_t i = 1; i <= difficulty; i++)
	{
		inputFile >> bestScore;
	}
		
	inputFile.close();
}


// ---------------------------------------- UPDATE FUNCTIONS ----------------------------------------

void Application::updateAudio()
{
	audioSlider->updateSlider();

	button1->setAudioVolume(sfxSlider->getProgress());
	buttonQuit->setAudioVolume(sfxSlider->getProgress());
	buttonDifficulty->setAudioVolume(sfxSlider->getProgress());
	buttonMenu->setAudioVolume(sfxSlider->getProgress());

	
	gameMusic.setVolume(audioSlider->getProgress());
	menuMusic.setVolume(audioSlider->getProgress());


	sound_newBestScore.setVolume(sfxSlider->getProgress());
	sound_pause.setVolume(sfxSlider->getProgress());
	sound_gameOver.setVolume(sfxSlider->getProgress());
	sound_towerHit.setVolume(sfxSlider->getProgress());
	sound_DestroyTower.setVolume(sfxSlider->getProgress());
	sound_shoot.setVolume(sfxSlider->getProgress());
	sound_hitEnemy.setVolume(sfxSlider->getProgress());


}

void Application::updateEnemies()
{
	// counter
	if (count < 100000.0f)
	{
		count = (count + mDeltaTime);
	}
	else
	{
		count = 0.0f;
	}
	
	// initial position
	circleSpawnEnemiesPosition = sf::Vector2f(sin(count / circleSpawnEnemiesVelocity) * circleSpawnEnemiesRadius + float(windowWidth / 2.0f),
		                                     cos(count / circleSpawnEnemiesVelocity) * circleSpawnEnemiesRadius + float(windowHeight / 2.0f));

	// temporario
	//circleSpawnEnemiesPosition = sf::Vector2f(800, 900.0f);

	// spawn timer
	if (enemySpawnDelayCount < enemySpawnDelay)
	{
		enemySpawnDelayCount += mDeltaTime;
	}

	if (spawnClockTimer.getElapsedTime().asMilliseconds() > 100 + rand() % int(enemySpawnDelay/mDeltaTime))
	{

			spawnClockTimer.restart();
			enemySpawnDelayCount = 0;
			enemy->shape.setPosition(circleSpawnEnemiesPosition);
			//enemy->shape.setPosition(0.0f, 400.0f);

			// calcule the distance between enemy and towers and get the small distance tower
			smallDistanceTowerEnemyIndex = 0;

			if (towers.size() > 0)
			{
				smallDistanceTowerEnemy = float(DistanceBetweenTwoPoints(enemy->shape.getPosition(), towers[0].shape.getPosition()));
			}

			for (size_t i = 1; i < towers.size(); i++)
			{
				currentDistanceTowerEnemy = float(DistanceBetweenTwoPoints(enemy->shape.getPosition(), towers[i].shape.getPosition()));

				//std::cout << "atual.:" << currentDistanceTowerEnemy << " ";
				//std::cout << "menor distancia.: " << smallDistanceTowerEnemy << '\n';

				if (currentDistanceTowerEnemy < smallDistanceTowerEnemy)
				{
					smallDistanceTowerEnemyIndex = i;
					smallDistanceTowerEnemy = currentDistanceTowerEnemy;
				}
			}

			if (towers.size() > 0)
			{
				enemy->direction.x = (enemy->shape.getPosition().x - towers[smallDistanceTowerEnemyIndex].shape.getPosition().x) * -1.0f;
				enemy->direction.y = (enemy->shape.getPosition().y - towers[smallDistanceTowerEnemyIndex].shape.getPosition().y) * -1.0f;
			}

			enemy->direction = NormalizeVector(enemy->direction);
			enemy->lookAtPoint();

			//std::cout << "menor distancia: " << smallDistanceTowerEnemy << '\n';

			//debugLine = CreateLine(enemy->shape.getPosition(), towers[smallDistanceTowerEnemyIndex].shape.getPosition());

			//std::cout << enemy->direction.x << "  " << enemy->direction.y << '\n';

			enemies.push_back(*enemy);
			//std::cout << "enemies " << enemies.size() << '/' << enemySpawnLimit << '\n';
		
	}

	//check if entered the window
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if( (enemies[i].shape.getPosition().x - enemies[i].shape.getGlobalBounds().width / 2.0f) > 0 &&
			(enemies[i].shape.getPosition().x + enemies[i].shape.getGlobalBounds().width / 2.0f) < windowWidth &&
			(enemies[i].shape.getPosition().y - enemies[i].shape.getGlobalBounds().height / 2.0f) > 0 &&
			(enemies[i].shape.getPosition().y + enemies[i].shape.getGlobalBounds().height / 2.0f) < windowHeight)
		{
			enemies[i].setKill(true);
		}
		else
		{
			if (enemies[i].getKill() == true)
			{
				enemies.erase(enemies.begin() + i);
				//std::cout << "morto ";
				//std::cout << "enemies " << enemies.size() << '/' << enemySpawnLimit << '\n';
				break;
			}
		}
	}

	// move
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].shape.move(enemies[i].direction.x * mDeltaTime * enemySpeed, enemies[i].direction.y * mDeltaTime * enemySpeed);
		//enemies[i].shape.move(1 * mDeltaTime, 1 * mDeltaTime);
	}
}

void Application::updateBullet()
{
	if (shootDelayCount < shootDelay)
	{
		shootDelayCount += mDeltaTime;
	}

	// Add new bullet to vector
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootDelayCount >= shootDelay)
	{
		shootDelayCount = 0;

		bullet->direction = NormalizeVector(player->getDirection());

		bullet->shape.setRotation(player->shape.getRotation());
		sound_shoot.play();
		bullets.push_back(*bullet);
	}

	//update bullet position and check collision and check if is out of window and delete
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].shape.move(bullets[i].direction.x * mDeltaTime * bullets[i].getSpeed(),
			-bullets[i].direction.y * mDeltaTime * bullets[i].getSpeed());

		if (bullets[i].shape.getPosition().x - bullets[i].shape.getGlobalBounds().width / 2.0f > windowWidth)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (bullets[i].shape.getPosition().x + bullets[i].shape.getGlobalBounds().width / 2.0f < 0.0f)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (bullets[i].shape.getPosition().y + bullets[i].shape.getGlobalBounds().height / 2.0f < 0.0f)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (bullets[i].shape.getPosition().y - bullets[i].shape.getGlobalBounds().height / 2.0f > windowHeight)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
	}
}

void Application::updateCollision()
{

	for (size_t i = 0; i < towers.size(); i++)
	{
		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (enemies[j].shape.getGlobalBounds().intersects(towers[i].shape.getGlobalBounds()))
			{
				sound_towerHit.play();
				enemies.erase(enemies.begin() + j);
				towers[i].setHp(towers[i].getHp() - 1);
				break;
			}
		}
	}

	for (size_t j = 0; j < enemies.size(); j++)
	{
		if (enemies[j].shape.getGlobalBounds().intersects(player->shape.getGlobalBounds()))
		{
			enemies.erase(enemies.begin() + j);
			break;
		}
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
			{
				sound_hitEnemy.play();
				bullets.erase(bullets.begin() + i);
				enemies.erase(enemies.begin() + j);
				playerScore++;
				break;
			}
		}
	}
}

void Application::updateTowers()
{

	for (size_t t = 0; t < towers.size(); t++)
	{
		if (towers[t].getHp() <= 0)
		{
			sound_DestroyTower.play();
			towers.erase(towers.begin() + t);
			break;
		}

	}



	// update health bar
	for (size_t i = 0; i < towers.size(); i++)
	{
		towers[i].hpRect.setSize(sf::Vector2f((towers[i].getHp() * towerHpRectMaxSize / towerMaxHp), 2.0f));

		towers[i].hpRect.setFillColor(sf::Color(sf::Uint8((((towerMaxHp - towers[i].getHp()) / towerMaxHp * 255.0f))),
			(sf::Uint8(towers[i].getHp() / towerMaxHp * 255.0f)),
			0,
			255));
	}

	
}

void Application::updateUI()
{
	scoreText.setString(std::string("Score \n").append(std::to_string(playerScore)));
}

void Application::updateResizeWindow()
{
	// update the view to the new size of the window
	sf::FloatRect visibleArea(0, 0, float(events.size.width), float(events.size.height));
	window->setView(sf::View(visibleArea));

	// update window size variables
	windowWidth = window->getSize().x;
	windowHeight = window->getSize().y;

	fpsText.setPosition(sf::Vector2f(windowWidth - 200.0f, 0.0f));

	//Update entity positions
	player->shape.setPosition(float(windowWidth / 2), float(windowHeight / 2));
	bullet->shape.setPosition(float(windowWidth / 2), float(windowHeight / 2));

	// update towers position
	for (size_t i = 1; i <= towers.size(); i++)
	{
		towerPosition.x = float(sin(spacing * i + rot) * towerRadius) + float(windowWidth / 2.0f);
		towerPosition.y = float(cos(spacing * i + rot) * towerRadius) + float(windowHeight / 2.0f);

		//std::cout << towerPosition.x << '/' << towerPosition.y << '\n'; 
		towers[i - 1].shape.setPosition(towerPosition);
		towers[i - 1].hpRect.setPosition(towers[i - 1].shape.getPosition().x - towers[i - 1].shape.getGlobalBounds().width / 2.0f, towers[i - 1].shape.getPosition().y - towers[i - 1].shape.getGlobalBounds().height);

	}

	endText.setPosition(sf::Vector2f((windowWidth / 2.0f) - endText.getGlobalBounds().width / 2.0f, (windowHeight / 2.0f) - 420.0f));
	pauseText.setPosition(sf::Vector2f((windowWidth / 2.0f) - pauseText.getGlobalBounds().width / 2.0f, (windowHeight / 2.0f) - 420.0f));

	updateMenu();


	//gameBackground.setSize(sf::Vector2f(windowWidth, windowHeight));

	// enemies

	for (size_t k = 0; k < enemies.size(); k++)
	{

		if (towers.size() > 0)
		{
			smallDistanceTowerEnemy = float(DistanceBetweenTwoPoints(enemies[k].shape.getPosition(), towers[0].shape.getPosition()));
		}

		for (size_t i = 1; i < towers.size(); i++)
		{
			currentDistanceTowerEnemy = float(DistanceBetweenTwoPoints(enemies[k].shape.getPosition(), towers[i].shape.getPosition()));

			//std::cout << "atual.:" << currentDistanceTowerEnemy << " ";
			//std::cout << "menor distancia.: " << smallDistanceTowerEnemy << '\n';

			if (currentDistanceTowerEnemy < smallDistanceTowerEnemy)
			{
				smallDistanceTowerEnemyIndex = i;
				smallDistanceTowerEnemy = currentDistanceTowerEnemy;
			}
		}

		if (towers.size() > 0)
		{
			enemies[k].direction.x = (enemies[k].shape.getPosition().x - towers[smallDistanceTowerEnemyIndex].shape.getPosition().x) * -1.0f;
			enemies[k].direction.y = (enemies[k].shape.getPosition().y - towers[smallDistanceTowerEnemyIndex].shape.getPosition().y) * -1.0f;
		}

		enemies[k].direction = NormalizeVector(enemies[k].direction);
		enemies[k].lookAtPoint();

	}

}

void Application::updateMenu()
{
	button1->update();

	button1->updatePosition();

	buttonQuit->update();

	buttonQuit->updatePosition();

	buttonDifficulty->update();

	buttonDifficulty->updatePosition();

	buttonMenu->update();

	buttonMenu->updatePosition();

	audioSlider->updatePosition();

	checkBoxShowFPS->updatePosition();

	checkBoxUnlimited->updatePosition();

	fpsSlider->updatePosition();

	sfxSlider->updatePosition();

	bestRecordLabel->updatePosition();

	menuBackgroundShape.setPosition(sf::Vector2f((windowWidth / 2.0f) - 250.0f, (windowHeight / 2.0f) - 450.0f));

	// background
	//menuBackground.setSize(sf::Vector2f(float(windowWidth), float(windowHeight)));

}


// DRAW FUNCTIONS


void Application::drawMenu()
{

	//bg color
	window->clear(sf::Color(5, 47, 60, 255));

	window->draw(menuBackgroundShape);

	window->draw(button1->shape);

	drawButton(button1);

	drawButton(buttonQuit);

	drawButton(buttonDifficulty);

	drawSlider(audioSlider);
	
	drawCheckBox(checkBoxShowFPS);

	drawCheckBox(checkBoxUnlimited);

	drawSlider(fpsSlider);

	drawSlider(sfxSlider);

	drawLabel(bestRecordLabel);

	window->display();
}

void Application::drawSlider(Slider* slider)
{
	window->draw(slider->frame);
	window->draw(slider->fill);
	window->draw(slider->progress);
	window->draw(slider->handle);
	window->draw(slider->label);
	window->draw(slider->number);
}

void Application::drawCheckBox(Checkbox* checkBox)
{
	window->draw(checkBox->frame);
	window->draw(checkBox->fill);
	window->draw(checkBox->check);
	window->draw(checkBox->label);
}

void Application::drawLabel(Label* label)
{
	window->draw(label->labelText);
}

// OTHER FUNCTIONS


void Application::restartGame()
{

	// remove all enemies
	// remove all towers
	// remove all bullets
	newBestScore = false;
	soundBestScoreAux = false;

	gameMusic.stop();
	menuMusic.play();

	enemies.clear();
	towers.clear();
	bullets.clear();

	// place towers

	tower->setHp(int(towerMaxHp));

	for (size_t i = 1; i <= nTowers; i++)
	{
		towerPosition.x = float(sin(spacing * i) * towerRadius) + float(windowWidth / 2.0f);
		towerPosition.y = float(cos(spacing * i) * towerRadius) + float(windowHeight / 2.0f);

		// std::cout << towerPosition.x << '/' << towerPosition.y << '\n';
		tower->hpRect.setSize(sf::Vector2f(towerHpRectMaxSize, 2.0f));
		tower->shape.setPosition(towerPosition);
		tower->hpRect.setPosition(tower->shape.getPosition().x - tower->shape.getGlobalBounds().width / 2.0f, tower->shape.getPosition().y - tower->shape.getGlobalBounds().height);
		towers.push_back(*tower);
	}

	playerScore = 0;

	pause = false;
	end = false;
	startGame = false;
}

void Application::drawButton(Button* button)
{
	window->draw(button->shape);
	window->draw(button->label);
}

void Application::configureDifficulty(int difficulty)
{
	switch (difficulty)
	{
	case 0:
		towerMaxHp = 4;
		nTowers = 6;
		enemySpeed = 2.0f;
		enemySpawnDelay = 1000.0f;
		break;
	case 1:
		towerMaxHp = 4;
		nTowers = 4;
		enemySpeed = 3.0f;
		enemySpawnDelay = 800.0f;
		break;
	case 2:
		towerMaxHp = 5;
		nTowers = 3;
		enemySpeed = 5.0f;
		enemySpawnDelay = 500.0f;
		break;
	}
	towers.clear();
	enemies.clear();

	spacing = PI * 2.0f / nTowers;

	initEnemy();
	initTower();

	getRecordFromFile(difficulty);
	
}

// DEBUG/UTILITY

sf::Vertex* Application::CreateLine(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vertex* line = new sf::Vertex[2];
	line[0] = sf::Vertex(a);
	line[1] = sf::Vertex(b);


	return line;
}

