#ifndef _UIELEMENTS_H_
#define _UIELEMENTS_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define FRAME_COLOR sf::Color(0, 5, 5, 255)
#define FILL_COLOR sf::Color(0, 31, 31, 255)

#define PROGRESS_COLOR sf::Color(15, 87, 97, 255)
#define CHECK_COLOR PROGRESS_COLOR

#define HANDLE_COLOR sf::Color(110, 205, 215, 255)


class Button
{
public:
	
	Button(sf::RenderWindow* window, float pos_x, float pos_y, float scale, std::string normal, std::string hovered, std::string clicked, std::string label);

	bool isClicked();
	bool isHovered();
	bool hasClicked();
	void update();
	void updatePosition();
	void setAudioVolume(float value);

	sf::Text label;
	sf::Sprite shape;

private:

	sf::SoundBuffer soundBuffer_ui_hover;
	sf::Sound sound_ui_hover;

	sf::SoundBuffer soundBuffer_ui_clicked;
	sf::Sound sound_ui_clicked;

	float soundVolumeBackup;
	float soundVolume;

	bool release;
	bool click;
	bool hover;
	bool has_clicked;
	bool outSideClick;
	int aux;
	bool soundAux;

	float pos_x;
	float pos_y;

	float center_x;
	float center_y;

	sf::Font font;

	sf::Vector2f buttonScale;
		
	sf::Texture texNormal;
	sf::Texture texClicked;
	sf::Texture texHovered;
	
	sf::RenderWindow* window;

};

class Slider
{
public:


	Slider(sf::RenderWindow* window, float position_x, float position_y, float value, float min, float max, std::string label);

	void setPosition(float position_x, float position_y);

	sf::Vector2f getPosition();

	void setProgress(float value);

	float getProgress();

	void updateSlider();
	
	void updatePosition();

	sf::RectangleShape frame;
	sf::RectangleShape fill;
	sf::RectangleShape progress;
	sf::RectangleShape handle;

	sf::Text number;
	sf::Text label;

private:

	sf::Font font;

	sf::RenderWindow* window;
	sf::Vector2f mousePositionOnClick;
	sf::Vector2f moveHandleAmount;
	sf::Vector2f handlePositionOnClick;

	float max;
	float min;

	float progressValue;
	float progressValueRemaped;
	float position_x;
	float position_y;

	float pos_x;
	float pos_y;

	bool click;

	bool clickInsideHandle;

	bool clickOutsideHandle;

	bool firstClick;

	bool clickOnFill;

	bool aux;


	sf::Vector2f size;
	
};

class Checkbox
{
public:
	Checkbox(sf::RenderWindow* window, float pos_x, float pos_y, bool state, std::string label);
	
	void updatePosition();

	void updateCheckBox();

	bool getState();

	void setAudioVolume(float value);

	void setState(bool value);


	sf::RectangleShape frame;
	sf::RectangleShape fill;
	sf::RectangleShape check;
	sf::Text label;

private:

	sf::SoundBuffer soundBuffer_checkbox;
	sf::Sound sound_checkbox;

	sf::Font font;

	bool state;

	bool insideCheckBox;
	
	bool firstClick;

	bool click;

	bool aux;

	bool soundAux;

	bool soundAux2;

	float soundVolumeBackup;

	float soundVolume;

	float pos_x;
	float pos_y;

	sf::RenderWindow* window;

};

class Label
{
public:
	Label(sf::RenderWindow* window, float pos_x, float pos_y, std::string label_1);

	void updatePosition();

	sf::Text labelText;

private:
	float pos_x;
	float pos_y;
	
	sf::Font font;
	sf::RenderWindow* window;


};




#endif


