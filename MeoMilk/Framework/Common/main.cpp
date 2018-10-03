#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "IApplication.hpp"

using namespace std;
using namespace MMilk;

namespace MMilk
{
	extern IApplication* g_pApp;
}

int main(int argc,char** argv)
{
	int err;
	if((err=g_pApp->Init())!=0)
	{
		cerr << "Init failed!" << endl;
		return err;
	}
	while(!g_pApp->IsQuit())
	{
		g_pApp->Tick();
	}
	g_pApp->Disp();
	cerr << "Exit normally." << endl;
	return 0;
}
