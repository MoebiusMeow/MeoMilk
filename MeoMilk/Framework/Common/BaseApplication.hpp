#ifndef F_BASEAPPLICATION_H
#define F_BASEAPPLICATION_H

#include "IApplication.hpp"

namespace MMilk
{
	class BaseApplication : public IApplication
	{
		public:
			virtual int Init();
			virtual void Disp();
			virtual void Tick();
			virtual bool IsQuit();
		protected:
			bool flag_Quit;
	};
}

#endif
