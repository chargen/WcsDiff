#include "stdafx.h"
#include "find_files.h"

using namespace std;

map<wstring, wstring> find_files(const wchar_t * pattern)
{
	map<wstring, wstring> ret;
	wchar_t path[MAX_PATH] = {};
	wcscpy_s(path, pattern);
	WIN32_FIND_DATA fd;
	HANDLE find = ::FindFirstFile(pattern, &fd);
	if (find != INVALID_HANDLE_VALUE) {
		do {
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				PathRemoveFileSpec(path);
				PathCombine(path, path, fd.cFileName);
				wstring name = fd.cFileName;
				for (auto& c : name) c = towlower(c);
				ret[name] = path;
			}
		} while (::FindNextFile(find, &fd));
		::FindClose(find);
	}
	return ret;
}

std::map<std::wstring, std::map<std::wstring, std::wstring>> find_files_ex(const std::wstring& pattern)
{
	//TODO: support recursive
	std::map<std::wstring, std::map<std::wstring, std::wstring>> ret;
	auto files = find_files(pattern.c_str());
	if (!files.empty()) ret[wstring()] = move(files);
	return ret;
}
