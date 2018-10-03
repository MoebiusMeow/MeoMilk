#include "BaseApplication.hpp"

int MMilk::BaseApplication::Init()
{
	flag_Quit = 0;
	return 0;
}

void MMilk::BaseApplication::Disp()
{
}

void MMilk::BaseApplication::Tick()
{
}

bool MMilk::BaseApplication::IsQuit()
{
	return flag_Quit;
}
