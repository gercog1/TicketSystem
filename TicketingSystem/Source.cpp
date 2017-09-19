#include <iostream>
#include "Views.h"
#include "ChoosePlaceView.h"
#include "ConsoleFunctions.h"
#include "PaymentView.h"

int main()
{

	setCursorVisability(false);
	setConsoleToLucidaConsole();
	setConsoleSize(80, 30);

	View* view = new StartView();
	
	while (view != NULL)
	{
		View* newView;

		view->clear();
		view->draw();
		newView = view->handle();

		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}
	return 0;
}
