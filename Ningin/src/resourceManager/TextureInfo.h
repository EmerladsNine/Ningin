#pragma once

#include <filesystem>
#include <string>

class TextureInfo
{
	public:
		TextureInfo(std::filesystem::path& imgPath, bool alpha, std::string& name);

		bool HasAlpha();
		std::filesystem::path& GetImgPath();
		std::string& GetName();

		void SetAlpha(bool alpha);
		void SetImgPath(std::filesystem::path& imgPath);
		void SetName(std::string& name);

	private:
		std::filesystem::path imgPath;
		std::string name;
		bool alpha;
};
