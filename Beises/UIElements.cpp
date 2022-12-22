#include "UIElements.h"

Button::Button(sf::RenderWindow* window, float pos_x, float pos_y, float scale, std::string normal, std::string hovered, std::string clicked, std::string label)
{
	font.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf");

	this->label.setFont(font);
	this->label.setString(label);

	this->pos_x = pos_x;
	this->pos_y = pos_y;

	this->soundVolume = 100.0f;
	this->soundVolumeBackup = 100.0f;

	center_x = (window->getSize().x / 2.0f - float(shape.getGlobalBounds().width));
	center_y = (window->getSize().y / 2.0f - float(shape.getGlobalBounds().height));

	buttonScale = sf::Vector2f(scale, scale);

	aux = 0;

	soundAux = true;
	outSideClick = false;
	has_clicked = false;
	release = true;
	click = false;
	hover = false;
	this->window = window;

	texNormal.loadFromFile(normal);
	texHovered.loadFromFile(hovered);
	texClicked.loadFromFile(clicked);

	shape.setTexture(this->texNormal);

	this->shape.setScale(buttonScale);

	soundBuffer_ui_hover.loadFromFile("../assets/sfx/select_002.ogg");
	sound_ui_hover.setBuffer(soundBuffer_ui_hover);

	soundBuffer_ui_clicked.loadFromFile("../assets/sfx/select_006.ogg");
	sound_ui_clicked.setBuffer(soundBuffer_ui_clicked);

	updatePosition();
}

bool Button::isClicked()
{
	return click;
}
	
bool Button::isHovered()
{
	return hover;
}

void Button::setAudioVolume(float value)
{
	this->soundVolume = value;
}

void Button::update()
{
	has_clicked = false;
	click = false;
	hover = false;
	
	if (soundVolume != soundVolumeBackup)
	{
		sound_ui_clicked.setVolume(soundVolume);
		sound_ui_hover.setVolume(soundVolume);
	}
	soundVolumeBackup = soundVolume;
	

	if (!this->shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
	{
		this->shape.setTexture(texNormal);

		soundAux = true;

		label.setPosition(pos_x + float(window->getSize().x / 2.0f) - label.getGlobalBounds().width / 2.0f, float(center_y) + 15.0f + pos_y);

		outSideClick = true;
		aux = 0;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		outSideClick = false;
		label.setPosition(pos_x + float(window->getSize().x / 2.0f) - label.getGlobalBounds().width / 2.0f, float(center_y) + 15.0f + pos_y);
	}

	if (!outSideClick)
	{
		if (this->shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->shape.setTexture(texClicked);

			label.setPosition(pos_x + float(window->getSize().x / 2.0f) - (label.getGlobalBounds().width + 15.0f) / 2.0f, (float(center_y) + 17.0f + pos_y));

			this->shape.setScale(buttonScale.x + 0.05f, buttonScale.y + 0.05f);

			release = false;
			click = true;

		}
		else if (this->shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
		{
			this->shape.setTexture(texHovered);
			if (soundAux == true)
			{
				sound_ui_hover.play();
				soundAux = false;
			}
			this->shape.setScale(buttonScale.x + 0.1f, buttonScale.y + 0.1f);
			hover = true;
		}
		else
		{
			this->shape.setTexture(texNormal);
		}



		//foi clicado
		if (click == false)
		{
			release = true;
		}
		if (!release)
		{
			aux = 1;
		}
		if (release && aux == 1)
		{
			//std::cout << "has clicked ";
			has_clicked = true;
			release = true;
			aux = 0;

			if (this->shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && has_clicked)
			{
				has_clicked = true;
				//play clicked
				sound_ui_clicked.play();
			}
			else
			{
				has_clicked = false;
			}
		}
	}

}

bool Button::hasClicked()
{
	return has_clicked;
}

void Button::updatePosition()
{
	center_x = window->getSize().x / 2.0f - float(shape.getGlobalBounds().width - shape.getGlobalBounds().width / 2.0f);
	center_y = window->getSize().y / 2.0f - float(shape.getGlobalBounds().height);

	shape.setPosition(float(center_x) + pos_x, float(center_y) + pos_y);

	//label.setPosition(float(window->getSize().x / 2.0f) - label.getGlobalBounds().width / 2.0f, float(center_y) + 13.0f); // 13.0f -> adjust


}


// SLIDER





Slider::Slider(sf::RenderWindow* window, float pos_x, float pos_y, float value, float min, float max, std::string label)
{

	font.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf");

	this->label.setFont(font);
	this->label.setString(label);
	this->number.setFont(font);
	this->number.setString(std::to_string(int(value)));
	this->number.setCharacterSize(21);

	click = false;
	clickInsideHandle = false;
	clickOutsideHandle = false;
	firstClick = false;
	aux = false;

	this->window = window;

	this->pos_x = pos_x;
	this->pos_y = pos_y;

	this->size.x = 300.0f;
	this->size.y = 30.0f;

	this->min = min;
	this->max = max - min;

	if (min > max)
	{
		max = min;
	}

	if (value <= max || value >= max)
	{
		this->progressValue = value;
	}
	else
	{
		this->progressValue = max;
	}

	this->progressValue = value;

	this->progressValueRemaped = (((progressValue - min) * (size.x - 15.0f)) / max);

	//std::cout << '\n' << "aaa " <<this->progressValueRemaped << '\n';

	frame.setFillColor(FRAME_COLOR);
	frame.setSize(size);
	//frame.setPosition(position_x, position_y);

	fill.setFillColor(FILL_COLOR);
	fill.setSize(sf::Vector2f(size.x - 6.0f, size.y - 6.0f));
	//fill.setPosition(position_x + 3.0f, position_y + 3.0f);

	progress.setFillColor(PROGRESS_COLOR);
	progress.setSize(sf::Vector2f(progressValueRemaped, size.y - 6.0f));
	//progress.setPosition(position_x + 3.0f, position_y + 3.0f);

	handle.setFillColor(HANDLE_COLOR);
	handle.setSize(sf::Vector2f(15.0f, size.y + 10.0f));
	//handle.setPosition(progressValue + position_x, position_y - 5.0f);

	updatePosition();

}

void Slider::setPosition(float position_x, float position_y)
{
	this->position_x = position_x;
	this->position_y = position_y;
}

sf::Vector2f Slider::getPosition()
{
	return sf::Vector2f(position_x, position_y);
}

void Slider::setProgress(float value)
{
	this->progressValue = value;
}

float Slider::getProgress()
{
	return this->progressValue;
}


void Slider::updateSlider()
{
	clickOnFill = false;
	

	if (firstClick == false)
	{

		if (fill.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
		{
			clickOnFill = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && handle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
		{
			clickInsideHandle = true;
			aux = true;
		}
		else
		{
			clickInsideHandle = false;
		}
		firstClick = true;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		firstClick = false;
	}

	if (clickInsideHandle == true || clickOnFill == true)
	{
		if (click == false)
		{
			mousePositionOnClick = sf::Vector2f(sf::Mouse::getPosition(*window));
			handlePositionOnClick = handle.getPosition();
			moveHandleAmount.x = 0.0f;
			moveHandleAmount.y = 0.0f;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			click = true;
		}
		else
		{
			click = false;
			clickInsideHandle = false;
		}

		moveHandleAmount.x = sf::Mouse::getPosition(*window).x - mousePositionOnClick.x;

		//std::cout << "move " << moveHandleAmount.x << " " << moveHandleAmount.y << '\n';

		if (handle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && click)
		{
			clickInsideHandle = true;
		}

		//click inside handle
		if (clickInsideHandle)
		{

			handle.setPosition(sf::Vector2f(handlePositionOnClick.x + moveHandleAmount.x, handlePositionOnClick.y + moveHandleAmount.y));
			if (handle.getPosition().x <= frame.getPosition().x)
			{
				handle.setPosition(frame.getPosition().x, position_y - 5.0f);
			}
			if (handle.getPosition().x >= frame.getPosition().x + size.x - handle.getGlobalBounds().width)
			{
				handle.setPosition(frame.getPosition().x + size.x - handle.getGlobalBounds().width, position_y - 5.0f);
			}
			progress.setSize(sf::Vector2f(handle.getPosition().x - fill.getPosition().x, fill.getSize().y));

			// progress

			//ponto inicial do frame ate a posicao do handle 

			setProgress(handle.getPosition().x - frame.getPosition().x);

			//std::cout << "progress " << progressValue << '\n';
			//std::cout << "max value " << size.x - handle.getGlobalBounds().width << '\n';

			progressValue = (progressValue * max / (size.x - handle.getGlobalBounds().width)) + min;
			number.setString(std::to_string(int(progressValue)));
			number.setPosition(position_x + ((frame.getGlobalBounds().width / 2.0f) - number.getGlobalBounds().width / 2.0f), position_y);

		}

		//click inside fill
		if (clickOnFill && click)
		{
			handle.setPosition(sf::Vector2f(mousePositionOnClick.x - handle.getGlobalBounds().width / 2.0f, position_y - 5.0f));

			if (handle.getPosition().x <= frame.getPosition().x)
			{
				handle.setPosition(frame.getPosition().x, position_y - 5.0f);
			}
			if (handle.getPosition().x >= frame.getPosition().x + size.x - handle.getGlobalBounds().width)
			{
				handle.setPosition(frame.getPosition().x + size.x - handle.getGlobalBounds().width, position_y - 5.0f);
			}

			progress.setSize(sf::Vector2f(handle.getPosition().x - fill.getPosition().x, fill.getSize().y));

			setProgress(handle.getPosition().x - frame.getPosition().x);

			progressValue = (progressValue * max / (size.x - handle.getGlobalBounds().width)) + min;
			number.setString(std::to_string(int(progressValue)));
			number.setPosition(position_x + ((frame.getGlobalBounds().width / 2.0f) - number.getGlobalBounds().width / 2.0f), position_y);


			clickInsideHandle = true;
			click = false;
			clickOnFill = false;
		}

		progressValueRemaped = (((progressValue-min) * (size.x - 15.0f)) / max);

		

		//std::cout << "progress " << progressValueRemaped << " " << progressValue << '\n';
	}
}

void Slider::updatePosition()
{
	
	position_x = (window->getSize().x / 2.0f) + pos_x;
	position_y = (window->getSize().y / 2.0f) + pos_y;

	frame.setPosition(position_x, position_y);
	fill.setPosition(position_x + 3.0f, position_y + 3.0f);
	progress.setPosition(position_x + 3.0f, position_y + 3.0f);
	handle.setPosition((progressValueRemaped) + position_x, position_y - 5.0f);
	
	label.setPosition(position_x + ((frame.getGlobalBounds().width / 2.0f) - label.getGlobalBounds().width / 2.0f), position_y - 40.0f);

	number.setPosition(position_x + ((frame.getGlobalBounds().width / 2.0f) - number.getGlobalBounds().width / 2.0f), position_y);
}


// CHECKBOX


Checkbox::Checkbox(sf::RenderWindow* window, float pos_x, float pos_y, bool state, std::string label)
{
	font.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf");

	this->label.setFont(font);
	this->label.setString(label);

	this->soundVolume = 100.0f;
	this->soundVolumeBackup = 100.0f;

	bool soundAux = false;
	bool soundAux2 = false;

	this->state = state;
	this->window = window;

	this->insideCheckBox = false;
	this->firstClick = true;
	this->click = false;

	this->pos_x = pos_x;
	this->pos_y = pos_y;

	float size_x = 40.0f;
	float size_y = 40.0f;

	frame.setFillColor(FRAME_COLOR);
	frame.setSize(sf::Vector2f(size_x, size_y));

	fill.setFillColor(FILL_COLOR);
	fill.setSize(sf::Vector2f(size_x - 4.0f, size_y - 4.0f));

	check.setFillColor(CHECK_COLOR);
	check.setSize(sf::Vector2f(size_x - 20.0f, size_y - 20.0f));

	if (state)
	{
		check.setFillColor(CHECK_COLOR);
	}
	else
	{
		check.setFillColor(FILL_COLOR);
	}

	soundBuffer_checkbox.loadFromFile("../assets/sfx/toggle_002.ogg");
	sound_checkbox.setBuffer(soundBuffer_checkbox);

	updatePosition();
}

void Checkbox::updatePosition()
{
	frame.setPosition(sf::Vector2f(window->getSize().x / 2.0f + pos_x, window->getSize().y / 2.0f + pos_y));
	fill.setPosition(sf::Vector2f(frame.getPosition().x + 2.0f, frame.getPosition().y + 2.0f));
	check.setPosition(sf::Vector2f(frame.getPosition().x + 10.0f, frame.getPosition().y + 10.0f));

	label.setPosition(window->getSize().x / 2.0f + ((label.getGlobalBounds().width / 2.0f) + (pos_x + (frame.getGlobalBounds().width + 10.0f)) - label.getGlobalBounds().width / 2.0f), window->getSize().y / 2.0f + pos_y);
}

void Checkbox::setAudioVolume(float value)
{
	this->soundVolume = value;
}

void Checkbox::updateCheckBox()
{

	if (soundVolume != soundVolumeBackup)
	{
		sound_checkbox.setVolume(soundVolume);
	}
	soundVolumeBackup = soundVolume;


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		firstClick = false;
		soundAux = true;
	}
	else
	{
		firstClick = true;
		soundAux2 = true;
	}

	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && frame.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && aux)
	{
		
		if (soundAux == true && soundAux2 == true)
		{
			sound_checkbox.play();
			soundAux = false;
			soundAux2 = false;
		}

		if (state)
		{
			state = false;
		}
		else
		{
			state = true;
		}
	}

	if (firstClick == false)
	{
		aux = false;
		
	}
	else
	{
		aux = true;
	}

	if (state)
	{
		check.setFillColor(CHECK_COLOR);
	}
	else
	{
		check.setFillColor(FILL_COLOR);
	}
}

bool Checkbox::getState()
{
	return state;
}

void Checkbox::setState(bool value)
{
	this->state = value;
}

// LABEL ------------------------------

Label::Label(sf::RenderWindow* window, float pos_x, float pos_y, std::string label_1)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;

	font.loadFromFile("../assets/font/RACE1_Brannt_Plus_NCV.ttf");

	this->window = window;

	this->labelText.setFont(font);

	this->labelText.setString(label_1);

	updatePosition();
}

void Label::updatePosition()
{
	labelText.setPosition(sf::Vector2f((window->getSize().x / 2.0f + pos_x) - labelText.getGlobalBounds().width / 2.0f, window->getSize().y / 2.0f + pos_y));
}