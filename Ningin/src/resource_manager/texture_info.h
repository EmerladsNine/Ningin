#pragma once

#include <string>
#include <filesystem>

class TextureInfo {
public:
    // Constructor
    TextureInfo(const std::filesystem::path& imgPath, bool alpha, const std::string& name);

    // Getters
    bool hasAlpha() const;
    const std::filesystem::path& getImgPath() const;
    const std::string& getName() const;

    // Setters
    void setAlpha(bool alpha);
    void setImgPath(const std::filesystem::path& imgPath);
    void setName(const std::string& name);

private:
    bool alpha;
    std::filesystem::path img_path;
    std::string name;
};

