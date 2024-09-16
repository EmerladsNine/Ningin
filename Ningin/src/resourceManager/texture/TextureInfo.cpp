#include "TextureInfo.h"

TextureInfo::TextureInfo(const filesystem::path imgPath, bool alpha, string name)
	: _alpha(alpha), _imgPath(imgPath), _name(name) {}

bool TextureInfo::HasAlpha()
{
	return _alpha;
}

const filesystem::path& TextureInfo::GetImgPath()
{
	return _imgPath;
}

string& TextureInfo::GetName()
{
	return _name;
}

void TextureInfo::SetAlpha(bool alpha)
{
	this->_alpha = alpha;
}

void TextureInfo::SetImgPath(const filesystem::path& imgPath)
{
	this->_imgPath = imgPath;
}

void TextureInfo::SetName(string& name)
{
	this->_name = name;
}
