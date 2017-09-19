#pragma once
#include <string>
#include "Colors.h"
#include <windows.h>

using namespace std;

extern HANDLE  hConsole;

class Printer
{
private:
	Color colorOfText;
	Color colorOfBackground;
public:
	Printer(Color _colorOfText, Color _colorOfBackground);
	void print(string text);
	void print(char ch);
};