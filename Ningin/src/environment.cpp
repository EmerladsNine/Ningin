#include "Environment.h"
#include <Windows.h>

filesystem::path Enironment::GetGameDirectory()
{
    wchar_t buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);

    wstring::size_type pos =  wstring(buffer).find_last_of(L"\\/");
    filesystem::path path(wstring(buffer).substr(0, pos));

    return path;
}
