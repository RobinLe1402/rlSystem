#ifndef RLSYSTEM_WINDOWSUNICODESTRING
#define RLSYSTEM_WINDOWSUNICODESTRING

#ifdef _WIN32





#include <memory>
#include <string>



namespace rlSystem
{

	namespace String
	{

		using OSChar   = wchar_t;
		using OSString = std::wstring;

		OSString ToOS(const char8_t *szUTF8) noexcept;

		std::u8string FromOS(const OSChar *szOS) noexcept;

	}

}





#endif // _WIN32

#endif // RLSYSTEM_WINDOWSUNICODESTRING