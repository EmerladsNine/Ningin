#include "environment.h"
#include <Windows.h>

std::filesystem::path Enironment::GetGameDirectory()
{
    wchar_t buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos =  std::wstring(buffer).find_last_of(L"\\/");
    std::filesystem::path path(std::wstring(buffer).substr(0, pos));
    return path;
}
