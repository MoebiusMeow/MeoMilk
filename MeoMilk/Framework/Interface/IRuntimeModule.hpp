#ifndef F_IRUNTIMEMODULE
#define F_IRUNTIMEMODULE

#include "Interface.hpp"

namespace MMilk
{
	class IRuntimeModule
	{
		public:
			virtual ~IRuntimeModule() { };
			virtual int Init() = 0;
			virtual void Disp() = 0;
			virtual void Tick() = 0;
	};
}

#endif
