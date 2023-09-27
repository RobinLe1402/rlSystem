#ifndef RLSYSTEM_FILESYSTEM
#define RLSYSTEM_FILESYSTEM





#include <string>
#include <vector>



namespace rlSystem
{

	namespace File
	{

		/// <summary>Does a path exist as a file?</summary>
		bool Exists(const char8_t *szFilePath);

		/// <summary>Delete a file.</summary>
		/// <returns>
		/// Was <c>szFilePath</c> deleted?<para/>
		/// Always returns <c>false</c> if <c>szFilePath</c> is not a file.
		/// </return>
		bool Delete(const char8_t *szFilePath);

		/// <summary>Move a file to a different path.</summary>
		/// <param name="szOrigFilePath">The current path of the file.</param>
		/// <param name="szNewFilePath">The new path of the file.</param>
		/// <returns>
		/// Was the file successfully moved?<para/>
		/// Always returns <c>false</c> if <c>szOrigFilePath</c> is not a file.
		/// </returns>
		bool Move(const char8_t *szOrigFilePath, const char8_t *szNewFilePath);

	}

	namespace Directory
	{

		/// <summary>Does a path exist as a directory?</summary>
		bool Exists(const char8_t *szDirPath);

		/// <summary>Create a directory.</summary>
		/// <param name="szDirPath">
		/// The path of the directory to create.<para/>
		/// If parent directories also don't exist, an attempt will be made to create those as well.
		/// </param>
		/// <param name="bHidden">Should the directory be hidden?</param>
		/// <returns>Was the directory successfully created?</returns>
		bool Create(const char8_t *szDirPath, bool bHidden = false);

		/// <summary>Delete a directory.</summary>
		/// <param name="szDirPath">
		/// Path to the directory to delete.<para/>
		/// If the directory contains subdirectories or files, they will also be deleted.
		/// </param>
		/// <returns>
		/// Was <c>szDirPath</c> deleted?<para/>
		/// Always returns <c>false</c> if <c>szDirPath</c> is not a directory.
		/// </returns>
		bool Delete(const char8_t *szDirPath);

		/// <summary>Move a directory to a different path.</summary>
		/// <param name="szOrigDirPath">The current path of the directory.</param>
		/// <param name="szNewDirPath">The new path of the directory.</param>
		/// <returns>
		/// Was the directory successfully moved?<para/>
		/// Always returns <c>false</c> if <c>szOrigPath</c> is not a directory.
		/// </returns>
		bool Move(const char8_t *szOrigDirPath, const char8_t *szNewDirPath);

		/// <summary>Get a list of files in a directory.</summary>
		/// <param name="szDirPath">The path of the directory to search.</param>
		/// <param name="szRegexFilename">
		/// A regular expression that is matched against the filename. Only matching files are
		/// returned.<para/>
		/// If this parameter is <c>nullptr</c> or an empty string, all files will be returned.
		/// </param>
		/// <param name="bRecursive">Should subdirectories also be searched?</param>
		/// <returns>A list of (absolute) paths of matched files.</returns>
		std::vector<std::u8string> GetFiles(
			const char8_t *szDirPath,
			const char8_t *szRegexFilename,
			      bool     bRecursive
		);

		/// <summary>Get a list of subdirectories in a directory.</summary>
		/// <param name="szDirPath">The path of the directory to search.</param>
		/// <param name="szRegexDirname">
		/// A regular expression that is matched against the directory names.
		/// Only matching directories are returned.<para/>
		/// If this parameter is <c>nullptr</c> or an empty string, all directories will be
		/// returned.
		/// </param>
		/// <param name="bRecursive">Should subdirectories also be searched?</param>
		/// <returns>A list of (absolute) paths of matched files.</returns>
		std::vector<std::u8string> GetDirectories(
			const char8_t *szDirPath,
			const char8_t *szRegexDirname,
			      bool     bRecursive
		);

	}

	namespace Path
	{

#ifdef _WIN32
		constexpr char8_t Delimiter = u8'\\';
#else
		constexpr char8_t Delimiter = u8'/';
#endif

		/// <summary>Get the current (working) directory.</summary>
		std::u8string CurrentDirectory();

		/// <summary>Set the current (working) directory.</summary>
		/// <returns>Was the current directory changed?</returns>
		bool CurrentDirectory(const char8_t *szDirPath) noexcept;

		/// <summary>Does a path exist as a directory?</summary>
		bool Exists(const char8_t *szPath);

		/// <summary>Delete a file/directory.</summary>
		/// <param name="szDirPath">Path to delete.</param>
		/// <returns>
		/// Was <c>szPath</c> deleted?<para/>
		/// Always returns <c>false</c> if <c>szDirPath</c> does not exist.
		/// </returns>
		bool Delete(const char8_t *szPath);

		/// <summary>Move a file or directory to a different path.</summary>
		/// <param name="szOrigPath">The current path of the file or directory.</param>
		/// <param name="szNewPath">The new path of the file or directory.</param>
		/// <returns>Was the file/directory successfully moved?</returns>
		bool Move(const char8_t *szOrigPath, const char8_t *szNewPath);

		/// <summary>Is a path hidden?</summary>
		/// <param name="szPath">The path of the file/directory to check.</param>
		bool IsHidden(const char8_t *szPath);

		/// <summary>Hide a path.</summary>
		/// <param name="szPath">The path of the file/directory to hide/show.</param>
		bool SetHidden(const char8_t *szPath, bool bHidden = true);

		/// <summary>Convert a relative path into an absolute one.</summary>
		/// <param name="szPathRelative">A relative path.</param>
		std::u8string Absolute(const char8_t *szPathRelative);

		/// <summary>Extract the parent directory/drive of a path.</summary>
		/// <param name="szPath">The path of a file or directory.</param>
		/// <returns>
		/// <c>szPath</c> with the rightmost item removed.<para/>
		/// If this is not an empty string, it contains a trailing path delimiter.
		/// </returns>
		std::u8string GetParent(const char8_t *szPath);

		/// <summary>
		/// Extract the file extension (everything after and including the last occurence of a
		/// period).
		/// </summary>
		/// <param name="szFilePath">A filepath.</param>
		/// <returns>
		/// If <c>szFilePath</c> doesn't contain a file extension, an empty string is returned.
		/// </returns>
		std::u8string GetFileExtension(const char8_t *szFilePath);

		/// <summary>
		/// Replace the file extension (everything after and including the last occurence of a
		/// period).<para/>
		/// If the given path doesn't contain a file extension, the given extension is appended.
		/// </summary>
		/// <param name="szFilePath">A filepath.</param>
		/// <param name="szExt">
		/// The file extension.
		/// If this parameter is <c>nullptr</c> or an empty string, the file extension is removed.
		/// </param>
		std::u8string SetFileExtension(const char8_t *szFilePath, const char8_t *szExt);

		/// <summary>Extract the name of the file/deepest level directory from a path.</summary>
		/// <param name="szPath">
		/// The path of a file or directory. Trailing slashes are ignored.
		/// </param>
		std::u8string GetName(const char8_t *szPath);

		/// <summary>Get a path with the actual casing set for it.</summary>
		/// <param name="szPath">The path of an existing file or directory.</param>
		/// <returns>
		/// On non-Windows system, this function returns the input without further action.<para/>
		/// On Windows, the return value is <c>szPath</c>, but with the actual casing.
		/// </returns>
		std::u8string GetCased(const char8_t *szPath);

	}

}





#endif // RLSYSTEM_FILESYSTEM