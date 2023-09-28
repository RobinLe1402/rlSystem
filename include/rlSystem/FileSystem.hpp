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
		/// Always returns <c>false</c> if <c>szFilePath</c> does not exist as a file.
		/// </return>
		bool Delete(const char8_t *szFilePath);

		/// <summary>Move a file to a different path.</summary>
		/// <param name="szOrigFilePath">The current path of the file.</param>
		/// <param name="szNewFilePath">The new path of the file.</param>
		/// <returns>
		/// Was the file successfully moved?<para/>
		/// Always returns <c>false</c> if <c>szOrigFilePath</c> does not exist as file.
		/// </returns>
		bool Move(const char8_t *szOrigFilePath, const char8_t *szNewFilePath);

		/// <summary>Copy a file.</summary>
		/// <param name="szOrigFilePath">The path of the original file.</param>
		/// <param name="szCopyFilePath">The path of the copied file.</param>
		/// <returns>
		/// Was the file successfully copied?<para/>
		/// Always returns <c>false</c> if <c>szOrigFilePath</c> does not exist as a file.
		/// </returns>
		bool Copy(const char8_t *szOrigFilePath, const char8_t *szCopyFilePath);

		/// <summary>Get the total size of a file, in bytes.</summary>
		/// <param name="szFilePath">The path of the file to get the filesize of.</param>
		/// <returns>
		/// If the function succeeds, it returns the size of the file, in bytes.<para/>
		/// If the function fails, it returns zero.
		/// </returns>
		size_t GetSize(const char8_t *szFilePath);

		/// <summary>Is a file readonly?</summary>
		/// <param name="szFilePath">The path to a file.</param>
		/// <returns>
		/// If <c>szFilePath</c> does not exist as a file, the return value is always <c>false</c>.
		/// </returns>
		bool IsReadonly(const char8_t *szFilePath);

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
		/// <param name="bHidden">Should the (deepest level) directory be hidden?</param>
		/// <returns>Was the directory successfully created?</returns>
		bool Create(const char8_t *szDirPath, bool bHidden = false);

		/// <summary>Delete a directory.</summary>
		/// <param name="szDirPath">
		/// Path to the directory to delete.<para/>
		/// If the directory contains subdirectories or files, they will also be deleted.
		/// </param>
		/// <returns>
		/// Was <c>szDirPath</c> deleted?<para/>
		/// Always returns <c>false</c> if <c>szDirPath</c> does not exist as directory.
		/// </returns>
		bool Delete(const char8_t *szDirPath);

		/// <summary>Move a directory to a different path.</summary>
		/// <param name="szOrigDirPath">The current path of the directory.</param>
		/// <param name="szNewDirPath">The new path of the directory.</param>
		/// <returns>
		/// Was the directory successfully moved?<para/>
		/// Always returns <c>false</c> if <c>szOrigPath</c> does not exist as directory.
		/// </returns>
		bool Move(const char8_t *szOrigDirPath, const char8_t *szNewDirPath);

		/// <summary>Copy a directory.</summary>
		/// <param name="szOrigDirPath">The path of the original directory.</param>
		/// <param name="szCopyDirPath">The path of the copied directory.</param>
		/// <returns>
		/// Was the directory successfully copied?<para/>
		/// Always returns <c>false</c> if <c>szOrigDirPath</c> is does not exist as a directory.
		/// </returns>
		bool Copy(const char8_t *szOrigDirPath, const char8_t *szCopyDirPath);

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

		/// <summary>Is a directory readonly?</summary>
		/// <param name="szDirPath">The path to a directory.</param>
		/// <returns>
		/// If <c>szDirPath</c> does not exist as a directory, the return value is always
		/// <c>false</c>.<para/>
		/// This function tests for writability by creating an empty test file. Please note that
		/// it's possible you have permission to create files in this directory, but lack permission
		/// to delete them, in which case this test file won't be deleted.
		/// </returns>
		bool IsReadonly(const char8_t *szDirPath);

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

		/// <summary>Copy a file or directory.</summary>
		/// <param name="szOrigPath">The path of the original file or directory.</param>
		/// <param name="szCopyPath">The path of the copied file or directory.</param>
		/// <returns>
		/// Was the file or directory successfully copied?<para/>
		/// Always returns <c>false</c> if <c>szOrigPath</c> does not exist as a file or directory.
		/// </returns>
		bool Copy(const char8_t *szOrigPath, const char8_t *szCopyPath);

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
		/// If <c>szFilePath</c> does not contain a file extension, an empty string is returned.
		/// </returns>
		std::u8string GetFileExtension(const char8_t *szFilePath);

		/// <summary>
		/// Replace the file extension (everything after and including the last occurence of a
		/// period).<para/>
		/// If the given path does not contain a file extension, the given extension is appended.
		/// </summary>
		/// <param name="szFilePath">A filepath.</param>
		/// <param name="szExt">
		/// The file extension.
		/// If this parameter is <c>nullptr</c> or an empty string, the file extension is removed.
		/// </param>
		std::u8string SetFileExtension(const char8_t *szFilePath, const char8_t *szExt);

		/// <summary>
		/// Make sure a string ends with a path delimiter ("/" or, under Windows, "\").
		/// </summary>
		/// <param name="szPath">A string that may or may not end on a path delimiter.</param>
		/// <returns><c>szPath</c>, but it's guaranteed to end with a path delimiter.</returns>
		std::u8string IncludeTrailingDelim(const char8_t *szPath);

		/// <summary>
		/// Remove all path delimiters ("/" or, under Windows, "\") at the end of a string.
		/// </summary>
		/// <param name="szPath">A string that may or may not end on a path delimiter.</param>
		/// <returns><c>szPath</c>, but it's guaranteed to not end with a path delimiter.</returns>
		std::u8string ExcludeTrailingDelim(const char8_t *szPath);

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

#ifdef _WIN32
		/// <summary>
		/// Expand the environment variables in a string.<para/>
		/// Note that the other functions that access the file system don't resolve environment
		/// variables. So if you want to use a path with environment variables, use this function to
		/// resolve them first.
		/// </summary>
		/// <param name="szPath">A string with or without environment variables.</param>
		/// <returns>
		/// If the function fails, it returns an empty string.
		/// </returns>
		std::u8string Expand(const char8_t *szPath);
#endif

	}

}





#endif // RLSYSTEM_FILESYSTEM