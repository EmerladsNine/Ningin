#pragma once

#include <filesystem>
#include <freetype/freetype.h>
#include <ft2build.h>
#include <string>
#include <vector>

/**
 * @brief Struct representing information used to create a font,
 * including the FreeType library, font file path, and font name.
 *
 * Fields:
 * - ft_library: The FT_Library instance from FreeType used for font management.
 * - font_path: A std::filesystem::path representing the file path to the font file.
 * - name: A string representing the name of the font.
 */
class FontInfo
{
  public:
    // Constructor
    FontInfo(const FT_Library &ft_library, const std::filesystem::path &font_path, const std::string &name);

    // Static Methods
    static std::vector<FontInfo> generateInfoFromFolder(const std::filesystem::path &path,
                                                        const FT_Library &ft_library);

    // Accessors
    const FT_Library &getFtLibrary() const;
    const std::filesystem::path &getFontPath() const;
    const std::string &getName() const;

  private:
    FT_Library ft_library;
    std::filesystem::path font_path;
    std::string name;
};
