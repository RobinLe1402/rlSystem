#ifdef _WIN32

#include <rlSystem/WindowsUnicodeString.hpp>

#include <locale>

namespace
{
	class UTF8LocaleSetter final
	{
	private: // methods

		UTF8LocaleSetter()
		{
			std::locale::global(std::locale("en_US.UTF-8"));
		}


	private: // static variables

		static UTF8LocaleSetter s_oInstance;

	};
}

#include "include/IncludeWindows.h"

namespace rlSystem
{

	namespace String
	{

		OSString ToOS(const char8_t *szUTF8) noexcept
		{
			const int sizeOrig = (int)strlen(reinterpret_cast<const char *>(szUTF8)) + 1;

			const auto len = MultiByteToWideChar(
				CP_UTF8,                                // CodePage
				MB_PRECOMPOSED,                         // dwFlags
				reinterpret_cast<const char *>(szUTF8), // lpMultiByteStr
				sizeOrig,                               // cbMultiByte
				nullptr,                                // lpWideCharStr
				0                                       // cchWideChar
			);

			if (len <= 1)
				return OSString{};



			OSString sResult((size_t)len - 1, 0);

			MultiByteToWideChar(
				CP_UTF8,                                // CodePage
				MB_PRECOMPOSED,                         // dwFlags
				reinterpret_cast<const char *>(szUTF8), // lpMultiByteStr
				sizeOrig,                               // cbMultiByte
				sResult.data(),                         // lpWideCharStr
				(int)sResult.length() + 1               // cchWideChar
			);

			return sResult;
		}

		std::u8string FromOS(const OSChar *szOS) noexcept
		{
			const int sizeOrig = (int)wcslen(szOS) + 1;

			const auto len = WideCharToMultiByte(
				CP_UTF8,  // CodePage
				0,        // dwFlags
				szOS,     // lpWideCharStr
				sizeOrig, // cchWideChar
				nullptr,  // lpMultiByteStr
				0,        // cbMultiByte
				NULL,     // lpDefaultChar
				NULL      // lpUsedDefaultChar
			);

			if (len <= 1)
				return std::u8string{};



			std::u8string sResult((size_t)len - 1, 0);

			WideCharToMultiByte(
				CP_UTF8,                                  // CodePage
				0,                                        // dwFlags
				szOS,                                     // lpWideCharStr
				sizeOrig,                                 // cchWideChar
				reinterpret_cast<char *>(sResult.data()), // lpMultiByteStr
				(int)sResult.length() + 1,                // cbMultiByte
				NULL,                                     // lpDefaultChar
				NULL                                      // lpUsedDefaultChar
			);

			return sResult;
		}

	}

}

#endif // _WIN32