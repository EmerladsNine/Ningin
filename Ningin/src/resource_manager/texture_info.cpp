#include "texture_info.h"

// ructor
TextureInfo::TextureInfo( std::filesystem::path& imgPath, bool alpha,  std::string& name)
    : img_path(imgPath), alpha(alpha), name(name) {}

// Getters
bool TextureInfo::hasAlpha()  {
    return alpha;
}

 std::filesystem::path& TextureInfo::getImgPath()  {
    return img_path;
}

 std::string& TextureInfo::getName()  {
    return name;
}

// Setters
void TextureInfo::setAlpha(bool alpha) {
    this->alpha = alpha;
}

void TextureInfo::setImgPath( std::filesystem::path& imgPath) {
    this->img_path = imgPath;
}

void TextureInfo::setName( std::string& name) {
    this->name = name;
}
