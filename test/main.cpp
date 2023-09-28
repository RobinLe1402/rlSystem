#include <rlSystem/AppExecution.hpp>
#include <rlSystem/FileSystem.hpp>

int main(int argc, char* argv[])
{

#ifdef _WIN32

	constexpr char8_t szTestPathWithEnvVars[] = u8R"PATH(%AppData%\%UndefinedEnvVar%\ASDF)PATH";
	printf("Trying to expand string \"%s\"...\n",
		reinterpret_cast<const char *>(szTestPathWithEnvVars));
	printf("  Result: \"%s\"\n\n",
		reinterpret_cast<const char *>(rlSystem::Path::Expand(szTestPathWithEnvVars).c_str()));

#endif

	printf("Current directory: \"%s\"\n\n",
		reinterpret_cast<const char *>(rlSystem::Path::CurrentDirectory().c_str()));

	constexpr char8_t szTestDir[] = u8"testdir";

	printf("Trying to create \"%s\"\n", reinterpret_cast<const char *>(szTestDir));
	if (!rlSystem::Directory::Create(szTestDir))
	{
		printf("  FAIL.\n\n");
		return 1;
	}
	else
		printf("  SUCCESS.\n\n");

	printf("Trying to switch to then new directory...\n");
	if (!rlSystem::Path::CurrentDirectory(szTestDir))
	{
		printf("  FAIL.\n\n");
		return 1;
	}
	else
		printf("  SUCCESS.\n\n");

	constexpr char8_t szTestDir2[] = u8"testdir2";

	printf("Trying to create \"%s\"\n", reinterpret_cast<const char *>(szTestDir2));
	if (!rlSystem::Directory::Create(szTestDir2))
	{
		printf("  FAIL.\n\n");
		return 1;
	}
	else
		printf("  SUCCESS.\n\n");


	printf("Trying to switch to the parent path...\n");
	if (!rlSystem::Path::CurrentDirectory(rlSystem::Path::GetParent(u8".").c_str()))
	{
		printf("  FAIL.\n\n");
		return 1;
	}
	else
		printf("  SUCCESS.\n\n");

	printf("Current directory: \"%s\"\n\n",
		reinterpret_cast<const char *>(rlSystem::Path::CurrentDirectory().c_str()));

	const auto sNewDir = rlSystem::Path::GetName(szTestDir);
	printf("Trying to delete \"%s\"...\n",
		reinterpret_cast<const char *>(sNewDir.c_str()));
	if (!rlSystem::Directory::Delete(sNewDir.c_str()))
	{
		printf("  FAIL.\n\n");
		return 1;
	}
	else
		printf("  SUCCESS.\n\n");



	printf("\n");
	constexpr char8_t szFilename[] = u8R"PATH(C:\autoexec.bat)PATH";
	printf("The extension of \"%s\" is \"%s\".\n\n",
		reinterpret_cast<const char *>(szFilename),
		reinterpret_cast<const char *>(rlSystem::Path::GetFileExtension(szFilename).c_str()));


	printf("Attempting to call CMD synchronously...\n");
	rlSystem::RunApp(u8"cmd.exe", u8"/C \"echo This is the output of a call to CMD.\"",
		0, true, 0, false);


	return 0;
}
