#pragma once

#include <filesystem>
#include <string>

using namespace std;

class TextureInfo
{
	public:
		TextureInfo(const filesystem::path& imgPath, bool alpha, string& name);

		bool HasAlpha();
		const filesystem::path& GetImgPath();
		string& GetName();

		void SetAlpha(bool alpha);
		void SetImgPath(const filesystem::path& imgPath);
		void SetName(string& name);

	private:
		filesystem::path _imgPath;
		string _name;
		bool _alpha;
};
