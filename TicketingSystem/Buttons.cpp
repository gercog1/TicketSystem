#include "Buttons.h"
#include <conio.h>

bool convertToButton(Button& button)
{
	bool isOk = true;
	char key = _getch();
	switch (key)
	{
	case 72:
		button = Button::UP;
		break;
	case 80:
		button = Button::DOWN;
		break;
	case 75:
		button = Button::LEFT;
		break;
	case 77:
		button = Button::RIGHT;
		break;
	case 13:
		button = Button::ENTER;
		break;
	case 27:
		button = Button::ESC;
		break;
	case 8:
		button = Button::BACKSPACE;
		break;
	case 104:
		button = Button::H;
		break;
	case 118:
		button = Button::V;
		break;
	default:
		isOk = false;
	}
	return isOk;
}

bool doesMatch(Button button, Button* possibleButtons, int size)
{
	int isOk = false;
	for (int i = 0; i < size; i++)
	{
		if (possibleButtons[i] == button)
		{
			isOk = true;
		}
	}
	return isOk;
}

Button getButton(Button* possibleButtons, int size)
{
	while (true)
	{
		Button button;
		if (convertToButton(button) && doesMatch(button, possibleButtons, size))
		{
			return button;
		}
	}
}