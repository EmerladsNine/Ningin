#pragma once

#include <string>
#include <filesystem>

class TextureInfo {
public:
    // ructor
    TextureInfo( std::filesystem::path& imgPath, bool alpha,  std::string& name);

    // Getters
    bool hasAlpha() ;
     std::filesystem::path& getImgPath() ;
     std::string& getName() ;

    // Setters
    void setAlpha(bool alpha);
    void setImgPath( std::filesystem::path& imgPath);
    void setName( std::string& name);

private:
    bool alpha;
    std::filesystem::path img_path;
    std::string name;
};

