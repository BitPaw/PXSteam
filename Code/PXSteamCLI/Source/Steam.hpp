#pragma once

#include "PXSteam.h"

namespace PX
{
	class Stream : public PXSteam
	{
		private:
		unsigned int AppID;

		char Name[32];

		public:
		bool Initialize();
		void Shutdown();
	};
}