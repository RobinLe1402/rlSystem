#include <rlSystem/AppExecution.hpp>

#include <rlSystem/WindowsUnicodeString.hpp>
#include "include/IncludeWindows.h"

namespace rlSystem
{

	namespace
	{

		bool RunApp_AllOptions(
		const char8_t *szAppPath,
		const char8_t *szArgs,
		const char8_t *szCurrentDir,
			  bool     bSynchronous,
			  int     *pResult,
			  bool     bHideWindow,
		const char8_t *szStdOutFile,
		const char8_t *szStdErrFile
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

			SECURITY_ATTRIBUTES sa{ sizeof(sa) };
			sa.bInheritHandle = TRUE;

			STARTUPINFOW si{};
			si.cb = sizeof(STARTUPINFOW);
			si.dwFlags = STARTF_USESTDHANDLES;

			HANDLE hStdOut = INVALID_HANDLE_VALUE;
			HANDLE hStdErr = INVALID_HANDLE_VALUE;

			if (szStdOutFile)
			{
				if (!*szStdOutFile)
					hStdOut = NULL;
				else
				{
					hStdOut = CreateFileW(
					rlSystem::String::ToOS(szStdOutFile).c_str(),
					GENERIC_WRITE,
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					&sa,
					CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL
				);
				if (hStdOut == INVALID_HANDLE_VALUE)
					return false;
				}

				si.hStdOutput = hStdOut;
			}
			else
				si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

			if (szStdErrFile)
			{
				if (szStdOutFile && std::u8string_view(szStdOutFile) == std::u8string_view(szStdErrFile))
				{
					si.hStdError = si.hStdOutput;
				}
				else if (!*szStdErrFile)
					hStdErr = NULL;
				else
				{
					hStdErr = CreateFileW(
						rlSystem::String::ToOS(szStdErrFile).c_str(),
						GENERIC_WRITE,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						&sa,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL
					);
					if (hStdErr == INVALID_HANDLE_VALUE)
					{
						if (hStdOut && hStdOut != INVALID_HANDLE_VALUE)
							CloseHandle(hStdOut);
						return false;
					}
				}
				si.hStdError = hStdErr;
			}
			else
				si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

			PROCESS_INFORMATION pi{};
			auto sCmdOS = rlSystem::String::ToOS(sCmd.c_str());
			if (!CreateProcessW(
				NULL,                                            // lpApplicationName
				sCmdOS.data(),                                   // lpCommandLine
				NULL,                                            // lpProcessAttributes
				NULL,                                            // lpThreadAttributes
				TRUE,                                            // bInheritHandles
				dwCreationFlags,                                 // dwCreationFlags,
				NULL,                                            // lpEnvironment
				szCurrentDir ?                                   // lpCurrentDirectory
				rlSystem::String::ToOS(szCurrentDir).c_str()
				: 0,
				&si,                                             // lpStartupInfo
				&pi                                              // lpProcessInformation
			))
			{
				if (hStdOut && hStdOut != INVALID_HANDLE_VALUE)
					CloseHandle(hStdOut);
				if (hStdErr && hStdErr != INVALID_HANDLE_VALUE && hStdErr != hStdOut)
					CloseHandle(hStdErr);
				return false;
			}

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

			if (hStdOut && hStdOut != INVALID_HANDLE_VALUE)
				CloseHandle(hStdOut);
			if (hStdOut && hStdErr && hStdErr != INVALID_HANDLE_VALUE && hStdErr != hStdOut)
				CloseHandle(hStdErr);

			return true;

#else
#error "Not implemented"
#endif
		}

	}

	bool RunApp(
		const char8_t *szAppPath,
		const char8_t *szArgs,
		const char8_t *szCurrentDir,
			  bool     bSynchronous,
			  int     *pResult,
			  bool     bHideWindow
	)
	{
		return RunApp_AllOptions(szAppPath, szArgs, szCurrentDir, bSynchronous, pResult,
			bHideWindow, nullptr, nullptr);
	}

	bool RunConsoleApp(
		const char8_t *szAppPath,
		const char8_t *szArgs,
		const char8_t *szCurrentDir,
			  int     *pResult,
		const char8_t *szStdOutFile,
		const char8_t *szStdErrFile
	)
	{
		return RunApp_AllOptions(szAppPath, szArgs, szCurrentDir, true, pResult, false,
			szStdOutFile, szStdErrFile);
	}

}
