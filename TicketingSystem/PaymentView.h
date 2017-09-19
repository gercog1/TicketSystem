#pragma once
#include "Buttons.h"
#include "Printer.h"
#include <conio.h>
#include <windows.h>
#include "Views.h"
#include "DataHandler.h"

extern bool myOptions;

enum class Chosen
{
	CardNumber,
	CardPin,
	DateOfExpire,
	Finish,
	Back
};

class PaymentView: public View
{
private:
	Chosen chField;

	string cardNumber;
	string cardPin;
	string dateOfExpire;

	Button* possibleButtons = new Button[3]{
		Button::UP,
		Button::DOWN,
		Button::ENTER
	};


	void drawCarNumberField();

	void drawPinNumber();

	void drawDateOfExpire();

	void drawFinish();

	void drawBack();

	void drawFrame(
		const HPEN& pen,
		const HBRUSH& brush,
		int left, int top,
		int right, int bot,
		int frWidth
	);


	void processCardNum();

	void processPin();

	void processDateOfExpire();

	View* processFinish();

	View* processBack();


	View* processEnter();

public:
	PaymentView();

	void draw();

	View* handle();

};