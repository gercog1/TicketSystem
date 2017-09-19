#include "ConsoleFunctions.h"
#include "Printer.h"
#include <windows.h>
#include <string>
#include <conio.h>
#include <iostream>

using namespace std;

HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
int consoleWidth;
int consoleHeight;

int width;
int height;

int fontHeight = 24;
int fontWidth = 14;

COORD cursor;

HWND handle = GetConsoleWindow();
HDC dc = GetDC(handle);

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;

	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConsole, c);
}

void printAtCenterOfLine(int line, string text, Printer p)
{
	int textSize = text.size();
	int x_pos = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2;
	setCursor(x_pos, line);
	p.print(text);
}

void setConsoleToLucidaConsole()
{
	COORD dwFontSize;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return;

	dwFontSize.X = 10;
	dwFontSize.Y = 16;
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	info.dwFontSize = dwFontSize;
	SetCurrentConsoleFontEx(output, false, &info);
}


const HBRUSH& getBrush(int r, int g, int b)
{
	return CreateSolidBrush(RGB(30, 240, 30));
}

const HPEN& getPen(int r, int g, int b)
{
	return CreatePen(PS_SOLID, 1, RGB(r, g, b));
}


void setCursor(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(hConsole, cursor);
}

void setCursorVisability(bool showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void wait()
{
	while (_getch() != 13);
}

void printAtMiddle(string text, int y, Printer p, int beginning)
{
	int x = beginning + (width - beginning * fontWidth) / (fontWidth * 2) - text.size() / 2;
	setCursor(x, y);
	p.print(text);
}

void printRect(int x1, int y1, int x2, int y2, Printer p)
{
	for (int i = y1; i <= y2; ++i)
	{
		setCursor(x1, i);
		for (int j = 0; j < x2 - x1; ++j)
		{
			p.print(" ");
		}
	}
}

void setConsoleVisability(bool visible)
{
	AllocConsole();
	ShowWindow(handle, visible);
}


string inputData(int sz, int x, int y, string input)
{
	setCursor(x + input.length(), y);
	string inputedData = input;
	char ch = 0;

	int spCounter = input.length();

	while (ch != 13)
	{
		ch = _getch();
		//in case user wants to delete smth
		if (ch == 8 && spCounter > 0)
		{
			spCounter--;
			inputedData.pop_back();
			setCursor(x + spCounter, y);
			cout << " ";
			setCursor(x + spCounter, y);
		}
		else if (spCounter != sz &&
			inputedData.size() >= 1 && inputedData[inputedData.size() - 1] &&
			(ch == 72 || ch == 75 || ch == 77 || ch == 80)
			)
		{
			spCounter -= 1;
			inputedData.pop_back();

			setCursor(x + spCounter, y);
			cout << "  ";
			setCursor(x + spCounter, y);
		}
		else if (ch != 8 && ch != 13 && spCounter != sz)
		{
			inputedData += ch;
			cout << ch;
			spCounter++;
		}
	}
	return inputedData;
}


void scrollOff(int w, int h)
{
	string cols = to_string(w);
	string lines = to_string(h);
	string str = "mode con cols=" + cols + " lines=" + lines;
	const char* sch = str.c_str();
	system(sch);
}

void setConsole(int w, int h)
{
	width = w * fontWidth;
	height = h * fontHeight;

	setCursorVisability(false);
	scrollOff(w, h);

	//set font settings
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = fontWidth;
		cfi.dwFontSize.Y = fontHeight;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		wcscpy_s(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	}


	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = w - 1;
	r.Bottom = h - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	//disallows manual console resizing
	HMENU hm;
	hm = GetSystemMenu(handle, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(handle);


	Sleep(100);
}
