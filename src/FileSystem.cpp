#include <rlSystem/FileSystem.hpp>

#include <filesystem>
#include <fstream>
#include <iterator>
#include <regex>

#ifdef _WIN32
#include "include/IncludeWindows.h"
#include <rlSystem/WindowsUnicodeString.hpp>

#include <ShlObj_core.h>
#endif

using namespace std::string_literals;
namespace fs = std::filesystem;



namespace rlSystem
{

	namespace str = rlSystem::String;



	namespace File
	{

		bool Exists(const char8_t *szFilePath)
		{
			return fs::is_regular_file(szFilePath);
		}

		bool Delete(const char8_t *szFilePath)
		{
			if (!Exists(szFilePath))
				return false;

			fs::remove_all(szFilePath);

			return !Exists(szFilePath);
		}

		bool Move(const char8_t *szOrigFilePath, const char8_t *szNewFilePath)
		{
			if (!Exists(szOrigFilePath))
				return false;

			try
			{
				fs::rename(szOrigFilePath, szNewFilePath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		bool Copy(const char8_t *szOrigFilePath, const char8_t *szCopyFilePath)
		{
			if (!Exists(szOrigFilePath))
				return false;

			try
			{
				fs::copy(szOrigFilePath, szCopyFilePath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		size_t GetSize(const char8_t *szFilePath)
		{
			std::ifstream file(
#ifdef _WIN32
				str::ToOS(szFilePath).c_str(),
#else
				reinterpret_cast<const char *>(szFilePath),
#endif
				std::ios::ate | std::ios::binary);

			if (file)
				return file.tellg();
			else
				return 0;
		}

		bool IsReadonly(const char8_t *szFilePath)
		{
			if (!Exists(szFilePath))
				return false;

			std::ofstream file(
#ifdef _WIN32
				str::ToOS(szFilePath).c_str(),
#else
				reinterpret_cast<const char *>(szFilePath),
#endif
				std::ios::binary | std::ios::app);

			return !file;
		}

	}

	namespace Directory
	{

		bool Exists(const char8_t *szDirPath) { return fs::is_directory(szDirPath); }

		bool Create(const char8_t *szDirPath, bool bHidden)
		{
			bool bResult = fs::create_directories(szDirPath);

			if (bResult && bHidden)
				bResult = Path::SetHidden(szDirPath);

			return bResult;
		}

		bool Delete(const char8_t *szDirPath)
		{
			if (!Exists(szDirPath))
				return false;

			fs::remove_all(szDirPath);

			return !Exists(szDirPath);
		}

		bool Move(const char8_t *szOrigDirPath, const char8_t *szNewDirPath)
		{
			if (!Exists(szOrigDirPath))
				return false;

			try
			{
				fs::rename(szOrigDirPath, szNewDirPath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		bool Copy(const char8_t *szOrigDirPath, const char8_t *szCopyDirPath)
		{
			if (!Exists(szOrigDirPath))
				return false;

			try
			{
				fs::copy(szOrigDirPath, szCopyDirPath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		std::vector<std::u8string> GetFiles(
			const char8_t *szDirPath,
			const char8_t *szRegexFilename,
				  bool     bRecursive
		)
		{
			const auto dirpath = fs::path(szDirPath);
			std::regex pattern;
			if (szRegexFilename && *szRegexFilename)
				pattern = reinterpret_cast<const char *>(szRegexFilename);
			else
				pattern = ".*";

			std::vector<std::u8string> oResult;



			for (const auto &item : fs::directory_iterator(dirpath))
			{
				if (item.is_directory())
				{
					if (bRecursive)
					{
						auto oResultSubdir =
							GetFiles(item.path().u8string().c_str(), szRegexFilename, true);
						std::move(oResultSubdir.begin(), oResultSubdir.end(),
							std::back_inserter(oResult));
					}
				}
				else
				{
					const auto sFilename = item.path().filename().u8string();

					if (std::regex_match(
						reinterpret_cast<const char *>(sFilename.c_str()), pattern))
						oResult.push_back(fs::absolute(item.path()).u8string());

				}
			}

			return oResult;
		}

		std::vector<std::u8string> GetDirectories(
			const char8_t *szDirPath,
			const char8_t *szRegexDirname,
				  bool     bRecursive
		)
		{
			const auto dirpath = fs::path(szDirPath);
			std::regex pattern;
			if (szRegexDirname && *szRegexDirname)
				pattern = reinterpret_cast<const char *>(szRegexDirname);
			else
				pattern = ".*";

			std::vector<std::u8string> oResult;



			for (const auto &item : fs::directory_iterator(dirpath))
			{
				if (item.is_directory())
				{
					const auto sDirname = item.path().filename().u8string();

					if (std::regex_match(reinterpret_cast<const char *>(sDirname.c_str()), pattern))
						oResult.push_back(fs::absolute(item.path()).u8string());

if (bRecursive)
{
	auto oResultSubdir =
		GetDirectories(item.path().u8string().c_str(), szRegexDirname, true);
	std::move(oResultSubdir.begin(), oResultSubdir.end(),
		std::back_inserter(oResult));
}
				}
			}

			return oResult;
		}

		bool IsReadonly(const char8_t *szDirPath)
		{
			if (!Exists(szDirPath))
				return false;

			const auto sBasePath = Path::IncludeTrailingDelim(szDirPath) + u8"testfile_";

			std::u8string sTestfilePath;
			sTestfilePath.reserve(sBasePath.length() + sizeof(unsigned) * 2);

			srand((unsigned)time(NULL));
			do
			{
				unsigned iRand = (unsigned)rand();

				sTestfilePath = sBasePath;

				constexpr char8_t cHex[] = u8"0123456789ABCDEF";

				for (int i = 0; i < 8; ++i)
				{
					sTestfilePath += cHex[iRand & 0xF];
					iRand >>= 4;
				}
			} while (Path::Exists(sTestfilePath.c_str()));
			
			
#ifdef _WIN32
			std::ofstream file(str::ToOS(sTestfilePath.c_str()).c_str());
#else
			std::ofstream file(reinterpret_cast<const char *>(sTestfilePath.c_str()));
#endif

			bool bResult = !file;
			if (file)
			{
				file.close();
				File::Delete(sTestfilePath.c_str());
			}

			return bResult;
		}

	}

	namespace Path
	{

		std::u8string CurrentDirectory() { return fs::current_path().u8string(); }

		bool CurrentDirectory(const char8_t *szDirPath) noexcept
		{
			try
			{
				fs::current_path(szDirPath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		bool Exists(const char8_t *szPath)
		{
			return fs::exists(szPath);
		}

		bool Delete(const char8_t *szPath)
		{
			if (!Exists(szPath))
				return false;

			fs::remove_all(szPath);

			return !Exists(szPath);
		}

		bool Move(const char8_t *szOrigPath, const char8_t *szNewPath)
		{
			if (!Exists(szOrigPath))
				return false;

			try
			{
				fs::rename(szOrigPath, szNewPath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		bool Copy(const char8_t *szOrigPath, const char8_t *szCopyPath)
		{
			if (!Exists(szOrigPath))
				return false;

			try
			{
				fs::copy(szOrigPath, szCopyPath);
				return true;
			}
			catch (...)
			{
				return false;
			}
		}

		bool IsHidden(const char8_t *szPath)
		{
#ifdef _WIN32 // Windows: file attribute

			const DWORD dwAttribs = GetFileAttributesW(str::ToOS(szPath).c_str());
			if (dwAttribs == INVALID_FILE_ATTRIBUTES)
				return false;

			return dwAttribs & FILE_ATTRIBUTE_HIDDEN;

#elif defined(__linux__) // Linux: filename starts with "."
			return fs::path(szPath).filename().u8string().starts_with(u8'.');
#else
#error "Not implemented"
#endif
		}

		bool SetHidden(const char8_t *szPath, bool bHidden)
		{
#ifdef _WIN32 // Windows: set file attribute
			const auto sPath = str::ToOS(szPath);

			DWORD dwAttribs = GetFileAttributesW(sPath.c_str());
			if (dwAttribs == INVALID_FILE_ATTRIBUTES)
				return false;

			if (bHidden)
				dwAttribs |= FILE_ATTRIBUTE_HIDDEN;
			else
				dwAttribs &= ~FILE_ATTRIBUTE_HIDDEN;

			return SetFileAttributesW(sPath.c_str(), dwAttribs);
#elif defined(__linux__) // Linux: not possible, as file would have to be renamed to start with "."
			return false;
#else
#error "Not implemented"
#endif
		}

		std::u8string Absolute(const char8_t *szPathRelative)
		{
			return fs::absolute(szPathRelative).u8string();
		}

		std::u8string GetParent(const char8_t *szPath)
		{
			std::u8string sPath = szPath;
			while (sPath.ends_with('/')
#ifdef _WIN32
				|| sPath.ends_with('\\')
#endif
				)
				sPath.erase(sPath.length() - 1);

			if (Exists(sPath.c_str()))
				sPath = Absolute(sPath.c_str());

			const auto path = fs::path(sPath);

			if (!path.has_parent_path())
				return {};
			return path.parent_path().u8string(); // todo: test if trailing delimiter or not
		}

		std::u8string GetFileExtension(const char8_t *szFilePath)
		{
			const auto path = fs::path(szFilePath);
			if (!path.has_extension())
				return {};
			return path.extension().u8string();
		}

		std::u8string SetFileExtension(const char8_t *szFilePath, const char8_t *szExt)
		{
			auto path = fs::path(szFilePath);
			if (!path.has_extension())
				return path.u8string() + szExt;
			return path.replace_extension(szExt).u8string();
		}

		std::u8string IncludeTrailingDelim(const char8_t *szPath)
		{
			std::u8string sResult = szPath;
#ifdef _WIN32 // Windows accepts both / and \ as path delimiters.
			if (!sResult.ends_with('/') && !sResult.ends_with('\\'))
#else // everyone else uses / exclusively.
			if (!sResult.ends_with('/'))
#endif
				sResult += Delimiter;

			return sResult;
		}

		std::u8string ExcludeTrailingDelim(const char8_t *szPath)
		{
			std::u8string sResult = szPath;

#ifdef _WIN32 // Windows accepts both / and \ as path delimiters.
			while (sResult.ends_with('/') || sResult.ends_with('\\'))
#else //  everyone else uses / exclusively.
			while (sResult.ends_with('/'))
#endif
			{
				sResult.pop_back();
			}

			return sResult;
		}

		std::u8string GetName(const char8_t *szPath)
		{
			std::u8string sPath = szPath;
			while (sPath.ends_with('/')
#ifdef _WIN32
				|| sPath.ends_with('\\')
#endif
				)
				sPath.erase(sPath.length() - 1);

			const auto path = fs::path(sPath);
			if (!path.has_filename())
			{
				if (path.has_root_path())
					return path.root_path().u8string();
				else
					return {};
			}
			else
				return path.filename().u8string(); // todo: test!
		}

		std::u8string GetCased(const char8_t *szPath)
		{
			if (!Exists(szPath))
				return {};

#ifndef _WIN32 // Windows is the only case-insensitive OS
			return sAbsPath;
#else

			std::u8string sResult;
			sResult.reserve(strlen(reinterpret_cast<const char *>(szPath)));
			const char8_t *sz = szPath;

			// network path: skip "\\"
			if (sz[0] == '\\' && sz[1] == '\\')
			{
				sResult += u8R"PATH(\\)PATH";
				sz      += 2;
			}
			// drive name: uppercase
			else if (sz[1] == ':')
			{
				sResult += toupper(sz[0]);
				sResult += u8":";
				sResult += Delimiter;
				sz      += 3;
			}

			while (*sz)
			{
				// skip additional slashes
				while (*sz == '\\' || *sz == '/')
					++sz;

				if (!sz[0])
					break;

				size_t len = 0;
				while (sz[len])
				{
					if (sz[len] == '\\' || sz[len] == '/')
						break;
					++len;
				}
				auto up_szItemName = std::make_unique<char8_t[]>(len + 1);
				for (size_t i = 0; i < len; ++i)
				{
					up_szItemName[i] = sz[i];
				}
				up_szItemName[len] = 0; // terminating zero

				sz += len;

				if (u8"."s == up_szItemName.get() || u8".."s == up_szItemName.get())
					sResult += up_szItemName.get();
				else
				{
					SHFILEINFOW sfi{};
					if (!SHGetFileInfoW(str::ToOS((sResult + up_szItemName.get()).c_str()).c_str(), 0,
						&sfi, sizeof(sfi), SHGFI_DISPLAYNAME))
						return {};
					sResult += str::FromOS(sfi.szDisplayName);
				}
				

				if (*sz)
					sResult += Delimiter;
			}

			return sResult;

#endif
		}

#ifdef _WIN32
		std::u8string Expand(const char8_t *szPath)
		{
			const auto sPath = str::ToOS(szPath);

			const DWORD dwSize = ExpandEnvironmentStringsW(sPath.c_str(), NULL, 0);
			if (dwSize <= 1)
				return {};

			str::OSString sResult(dwSize - 1, 0);
			ExpandEnvironmentStringsW(sPath.c_str(), sResult.data(), dwSize);

			return str::FromOS(sResult.c_str());
		}
#endif

	}

}