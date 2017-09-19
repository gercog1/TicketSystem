#define _CRT_SECURE_NO_WARNINGS
#include "PaymentView.h"
#include "ConsoleFunctions.h"
#include "ChoosePlaceView.h"
#include <ctime>

bool myOptions = false;

string getCurrentMY()
{
	time_t t = time(0); // get time now
	struct tm* now = localtime(&t);

	string month = ((now->tm_mon) < 9 ?
		"0" : "") +
		to_string(now->tm_mon + 1);

	return to_string(now->tm_year - 100) + month;
}

string space(int size)
{
	if (size > 0)
	{
		string space = "";
		for (int i = 0; i < size; ++i)
		{
			space += " ";
		}
		return space;
	}
	else
		return "";
}


void drawAsciiFrame(Printer p, int left, int top, int right, int bot)
{
	for (int i = left; i <= right; ++i)
	{
		setCursor(i, top);
		p.print((unsigned char)220);
	}


	for (int i = left; i <= right; ++i)
	{
		setCursor(i, bot);
		p.print((unsigned char)220);
	}


	for (int i = top + 1; i <= bot; ++i)
	{
		setCursor(left, i);
		p.print((unsigned char)219);
	}

	for (int i = top + 1; i <= bot; ++i)
	{
		setCursor(right, i);
		p.print((unsigned char)219);
	}
}

bool isValidCardNumber(string cardNumber)
{
	istringstream stream(cardNumber);

	string result;

	string num;

	while (stream >> num)
		result += num;

	if (result.length() != 16)
		return false;

	int sum = 0;
	for (int i = 15; i >= 0; i--)
	{
		if (!(result[i] >= '0' && result[i] <= '9'))
			return false;
		if (i % 2 == 1)
		{
			int temp = (result[i] - 48) * 2;
			if (temp > 9)
				sum += temp - 9;
			else
				sum += temp;
		}
		else
		{
			sum += result[i] - 48;
		}
	}

	return sum % 10 == 0;
}

bool isValidPin(string pin)
{
	if (pin.length() != 3)
		return false;
	for (auto el : pin)
	{
		if (!(el >= '0' && el <= '9'))
			return false;
	}

	return true;
}

bool isValidDate(string date)
{
	if (date.length() < 5)
		return false;

	date.erase(2, 1);

	for (auto el : date)
	{
		if (!(el >= '0' && el <= '9'))
			return false;
	}

	if (date[0] > '1' || (date[0] == '1' && date[1] > '2'))
		return false;

	swap(date[0], date[2]);
	swap(date[1], date[3]);

	string currDate = getCurrentMY();



	return date > currDate;
}



void PaymentView::drawCarNumberField()
{
	setCursor(10, 3);
	string toPrint = "Card Number:" + space(4) + cardNumber;
	Printer(Color::Yellow, Color::Blue).print(toPrint);

	Color color = chField == Chosen::CardNumber ? Color::Brown : Color::Grey;
	drawAsciiFrame(Printer(color, Color::Blue), 8, 1,
		49, 4);
}

void PaymentView::drawPinNumber()
{
	setCursor(10, 7);
	string toPrint = "PIN Number:" + space(5) + cardPin;
	Printer(Color::Yellow, Color::Blue).print(toPrint);

	Color color = chField == Chosen::CardPin ? Color::Brown : Color::Grey;
	drawAsciiFrame(Printer(color, Color::Blue), 8, 5,
		49, 8);
}

void PaymentView::drawDateOfExpire()
{
	setCursor(10, 11);
	string toPrint = "Date of Expire:" + space(1) + dateOfExpire;
	Printer(Color::Yellow, Color::Blue).print(toPrint);

	Color color = chField == Chosen::DateOfExpire ? Color::Brown : Color::Grey;
	drawAsciiFrame(Printer(color, Color::Blue), 8, 9,
		49, 12);
}

void PaymentView::drawFinish()
{
	printAtMiddle("FINISH ORDER", 14, Printer(Color::Light_Green, Color::Blue));

	Color color = chField == Chosen::Finish ? Color::Brown : Color::Grey;
	drawAsciiFrame(Printer(color, Color::Blue), 12, 12,
		45, 15);
}

void PaymentView::drawBack()
{
	printAtMiddle("BACK", 17, Printer(Color::Red, Color::Blue));

	Color color = chField == Chosen::Back ? Color::Brown : Color::Grey;
	drawAsciiFrame(Printer(color, Color::Blue), 15, 15,
		42, 18);
}

void PaymentView::drawFrame(
	const HPEN& pen,
	const HBRUSH& brush,
	int left, int top,
	int right, int bot,
	int frWidth
)
{
	SelectObject(dc, pen);
	SelectObject(dc, brush);

	Rectangle(dc, left, top, right, top + frWidth);
	Rectangle(dc, left, bot - frWidth, right, bot);

	Rectangle(dc, left, top + frWidth, left + frWidth, bot - frWidth);
	Rectangle(dc, right - frWidth, top + frWidth, right, bot - frWidth);
}


void PaymentView::processCardNum()
{
	setCursorVisability(true);
	cardNumber = inputData(16, 26, 3, cardNumber);
	setCursorVisability(false);


	clear();
	draw();
}

void PaymentView::processPin()
{
	setCursorVisability(true);
	cardPin = inputData(3, 26, 7, cardPin);
	setCursorVisability(false);


	clear();
	draw();
}

void PaymentView::processDateOfExpire()
{
	setCursorVisability(true);
	dateOfExpire = inputData(5, 26, 11, dateOfExpire);
	setCursorVisability(false);

	clear();
	draw();
}

View* PaymentView::processFinish()
{
	string output = "Invalid data: ";
	bool valid = true;

	if (!isValidCardNumber(cardNumber))
	{
		valid = false;
		cardNumber = "";
		output += "CardNumber, ";
	}
	if (!isValidPin(cardPin))
	{
		valid = false;
		cardPin = "";
		output += "CardPin, ";
	}
	if (!isValidDate(dateOfExpire))
	{
		valid = false;
		dateOfExpire = "";
		output += "DateOfExpire, ";
	}

	output.erase(output.size() - 2, 2);

	if (!valid)
	{
		clear();
		draw();

		printAtMiddle(output, 0, Printer(Color::Light_Red, Color::Blue));

		return this;
	}
	DataHandler::saveData();

	return nullptr;
}

View* PaymentView::processBack()
{
	CustomerOrder::setPlaces({});


	myOptions = false;

	setConsoleVisability(false);

	setCursorVisability(false);
	setConsoleToLucidaConsole();
	setConsoleSize(80, 30);

	setConsoleVisability(true);

	return new CarView();
}


View* PaymentView::processEnter()
{
	View* view = this;
	switch (chField)
	{
	case Chosen::CardNumber:
		processCardNum();
		break;
	case Chosen::CardPin:
		processPin();
		break;
	case Chosen::DateOfExpire:
		processDateOfExpire();
		break;
	case Chosen::Finish:
		view = processFinish();
		break;
	case Chosen::Back:
		view = processBack();
		break;
	}

	return view;
}

PaymentView::PaymentView() :
	chField(Chosen::CardNumber)
{
}

void PaymentView::draw()
{
	if (!myOptions)
	{
		myOptions = true;

		setConsoleVisability(false);

		setConsole(57, 20);

		setConsoleVisability(true);
	}

	drawCarNumberField();
	drawPinNumber();
	drawDateOfExpire();
	drawFinish();
	drawBack();
}


View* PaymentView::handle()
{
	View* view = this;

	while (view == this)
	{
		int sp = static_cast<int>(chField);

		Button but = getButton(possibleButtons, 3);

		switch (but)
		{
		case Button::UP:
			sp--;
			break;
		case Button::DOWN:
			sp++;
			break;
		case Button::ENTER:
			view = processEnter();
			break;
		}

		if (sp >= 0 && sp < 5)
		{
			chField = static_cast<Chosen>(sp);
		}

		draw();
	}

	return view;
}