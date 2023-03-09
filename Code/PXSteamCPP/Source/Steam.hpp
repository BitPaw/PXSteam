#pragma once

namespace PX
{
	class Steam
	{
		private:
		unsigned int AppID;

		char Name[32];

		public:
		bool Initialize();
		void Shutdown();
	};
}