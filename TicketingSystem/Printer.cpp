#include "Printer.h"
#include <iostream>
#include <windows.h>
using namespace std;
Printer::Printer(Color _colorOfText, Color _colorOfBackground) : colorOfText(_colorOfText), colorOfBackground(_colorOfBackground) {}

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Printer::print(string text)
{
	SetConsoleTextAttribute(hConsole, (int)colorOfText + (int)colorOfBackground * 16);
	cout << text;
}

void Printer::print(char ch)
{
	SetConsoleTextAttribute(hConsole, (int)colorOfText + (int)colorOfBackground * 16);
	cout << ch;
}