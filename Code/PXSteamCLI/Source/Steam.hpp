#pragma once

#include "../../PXSteam/Source/PXSteam.h"

namespace PX
{
	public ref class Stream
	{
		private:
		bool _isInitialized;
		PXSteam* _pxSteam;

		public:
		Stream();
		~Stream();

		// propertys
		property bool IsInitialized
		{
			bool get()
			{
				return _isInitialized;
			}
			private:
			void set(bool value)
			{
				_isInitialized = value;
			}
			public:
		}

		property System::String^ ProfileName
		{
			System::String^ get();
		}

		bool Initialize();
		void Shutdown();
	};
}