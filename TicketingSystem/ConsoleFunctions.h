#pragma once

#include <string>
#include <windows.h>
#include "Printer.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27
#define KEY_WHITESPACE 32

using namespace std;

extern HANDLE hConOut;
extern int consoleWidth;
extern int consoleHeight;

extern int width;
extern int height;

extern int fontHeight;
extern int fontWidth;

extern COORD cursor;

extern HWND handle;
extern HDC dc;

extern HPEN penGreen;
extern HBRUSH brushGreen;

using namespace std;

void setConsoleSize(int width, int height);
void setCursor(int x, int y);
void printAtCenterOfLine(int line, string text, Printer p);
void setConsoleToLucidaConsole();
void setCursorVisability(bool showFlag);
void wait();
void printAtMiddle(string text, int y, Printer p, int beginning = 0);
string inputData(int sz, int x, int y, string input = "");
void setConsoleVisability(bool visible);
void setConsole(int w, int h);