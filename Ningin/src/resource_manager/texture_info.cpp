#include "texture_info.h"

// Constructor
TextureInfo::TextureInfo(const std::filesystem::path& imgPath, bool alpha, const std::string& name)
    : img_path(imgPath), alpha(alpha), name(name) {}

// Getters
bool TextureInfo::hasAlpha() const {
    return alpha;
}

const std::filesystem::path& TextureInfo::getImgPath() const {
    return img_path;
}

const std::string& TextureInfo::getName() const {
    return name;
}

// Setters
void TextureInfo::setAlpha(bool alpha) {
    this->alpha = alpha;
}

void TextureInfo::setImgPath(const std::filesystem::path& imgPath) {
    this->img_path = imgPath;
}

void TextureInfo::setName(const std::string& name) {
    this->name = name;
}
