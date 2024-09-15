#include "Environment.h"
#include <Windows.h>
#include <filesystem>
#include <string>

std::filesystem::path Environment::GetGameDirectory()
{
    wchar_t buffer[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, buffer, MAX_PATH);

    std::wstring::size_type pos =  std::wstring(buffer).find_last_of(L"\\/");
    std::filesystem::path path(std::wstring(buffer).substr(0, pos));

    return path;
}
