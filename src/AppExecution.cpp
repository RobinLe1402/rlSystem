#include <rlSystem/AppExecution.hpp>

#include <rlSystem/WindowsUnicodeString.hpp>
#include "include/IncludeWindows.h"

namespace rlSystem
{

	bool RunApp(
		const char8_t *szAppPath,
		const char8_t *szArgs,
		const char8_t *szCurrentDir,
			  bool     bSynchronous,
			  int     *pResult,
			  bool     bHideWindow 
	)
	{
#ifdef _WIN32
		std::u8string sCmd;
		sCmd.reserve(1 + strlen(reinterpret_cast<const char *>(szAppPath)) + 2 +
			strlen(reinterpret_cast<const char *>(szAppPath)));
		sCmd = u8'"';
		sCmd += szAppPath;
		sCmd += u8'"';
		if (szArgs)
		{
			sCmd += u8' ';
			sCmd += szArgs;
		}

		DWORD dwCreationFlags = 0;
		if (bHideWindow)
			dwCreationFlags |= CREATE_NO_WINDOW;

		STARTUPINFOW si{ sizeof(STARTUPINFOW) };
		PROCESS_INFORMATION pi{};
		auto sCmdOS = rlSystem::String::ToOS(sCmd.c_str());
		if (!CreateProcessW(
			NULL,                                            // lpApplicationName
			sCmdOS.data(),                                   // lpCommandLIne
			NULL,                                            // lpProcessAttributes
			NULL,                                            // lpThreadAttributes
			FALSE,                                           // bInheritHandles
			dwCreationFlags,                                 // dwCreationFlags,
			NULL,                                            // lpEnvironment
			szCurrentDir ?                                   // lpCurrentDirectory
				rlSystem::String::ToOS(szCurrentDir).c_str()
				: 0,
			&si,                                             // lpStartupInfo
			&pi                                              // lpProcessInformation
		))
			return false;

		if (bSynchronous)
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			DWORD dwExitCode;
			if (pResult)
			{
				if (GetExitCodeProcess(pi.hProcess, &dwExitCode))
					*pResult = dwExitCode;
				else
					*pResult = 0;
			}
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return true;

#else
#error "Not implemented"
#endif
	}

}