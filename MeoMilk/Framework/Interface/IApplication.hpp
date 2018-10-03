#ifndef F_IAPPLICATION_H
#define F_IAPPLICATION_H

#include "Interface.hpp"
#include "IRuntimeModule.hpp"

namespace MMilk
{
	class IApplication : public IRuntimeModule
	{
		public:
			virtual int Init() = 0;
			virtual void Disp() = 0;
			virtual void Tick() = 0;
			virtual bool IsQuit() = 0;
	};
}

#endif
