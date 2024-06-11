#ifndef RLSYSTEM_APPEXECUTION
#define RLSYSTEM_APPEXECUTION





namespace rlSystem
{

	/// <summary>Run an application.</summary>
	/// <param name="szAppPath">The path of the executable.</param>
	/// <param name="szArgs">
	/// The arguments for the application.<para/>
	/// If this value is <c>nullptr</c>, no arguments are passed to the application.
	/// </param>
	/// <param name="szCurrentDir">
	/// The working directory for the application.<para/>
	/// If this value is <c>nullptr</c>, the working directory of the current application is used.
	/// </param>
	/// <param name="bSynchronous">Should the app be executed synchronously?</param>
	/// <param name="pResult">
	/// If <c>bSynchronous</c> is set to <c>true</c> and this value is not <c>nullptr</c>, the
	/// pointed-to variable will receive the exit code of the called application.
	/// </param>
	/// <param name="bHideWindow">Should the application window be hidden?</param>
	/// <returns>Could the application be executed?</returns>
	bool RunApp(
		const char8_t *szAppPath,
		const char8_t *szArgs       = nullptr,
		const char8_t *szCurrentDir = nullptr,
		      bool     bSynchronous = false,
		      int     *pResult      = nullptr,
		      bool     bHideWindow  = false
	);

	/// <summary>Run a console application synchronously.</summary>
	/// <param name="szAppPath">The path of the executable.</param>
	/// <param name="szArgs">
	/// The arguments for the application.<para/>
	/// If this value is <c>nullptr</c>, no arguments are passed to the application.
	/// </param>
	/// <param name="szCurrentDir">
	/// The working directory for the application.<para/>
	/// If this value is <c>nullptr</c>, the working directory of the current application is used.
	/// </param>
	/// <param name="bSynchronous">Should the app be executed synchronously?</param>
	/// <param name="pResult">
	/// If <c>bSynchronous</c> is set to <c>true</c> and this value is not <c>nullptr</c>, the
	/// pointed-to variable will receive the exit code of the called application.
	/// </param>
	/// <param name="szStdOutFile">
	/// Redirection of <c>stdout</c> output:<para/>
	/// If this value is <c>nullptr</c>, the output is not redirected.<para/>
	/// If this value is an empty string, the output is discarded.<para/>
	/// Otherwise, the given value must be a filepath for an output text file. If a file already
	/// exists at the given path, it will be cleared before any writing is done.
	/// </param>
	/// <param name="szStdErrFile">
	/// Redirection of <c>stderr</c> output, see <c>szStdOutFile</c>.
	/// </param>
	/// <returns></returns>
	bool RunConsoleApp(
		const char8_t *szAppPath,
		const char8_t *szArgs       = nullptr,
		const char8_t *szCurrentDir = nullptr,
		      int     *pResult      = nullptr,
		const char8_t *szStdOutFile = nullptr,
		const char8_t *szStdErrFile = nullptr
	);

}





#endif // RLSYSTEM_APPEXECUTION