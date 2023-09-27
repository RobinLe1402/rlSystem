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

}





#endif // RLSYSTEM_APPEXECUTION