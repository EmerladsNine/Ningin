#include "TextureInfo.h"

TextureInfo::TextureInfo(std::filesystem::path& imgPath, bool alpha, std::string& name)
	: alpha(alpha), imgPath(imgPath), name(name)
{
}

bool TextureInfo::HasAlpha()
{
	return alpha;
}

std::filesystem::path& TextureInfo::GetImgPath()
{
	return imgPath;
}

std::string& TextureInfo::GetName()
{
	return name;
}

void TextureInfo::SetAlpha(bool alpha)
{
	this->alpha = alpha;
}

void TextureInfo::SetImgPath(std::filesystem::path& imgPath)
{
	this->imgPath = imgPath;
}

void TextureInfo::SetName(std::string& name)
{
	this->name = name;
}
