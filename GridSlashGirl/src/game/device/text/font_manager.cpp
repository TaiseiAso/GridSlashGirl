#include <fstream>
#include <sstream>
#include "font_manager.h"
#include "utils/string_util.h"
#include "DxLib.h"

namespace game::text
{
	FontManager::FontManager() {}
	FontManager::~FontManager() {
		deleteAllFont();
		deleteAllFontResource();
	}

	void FontManager::loadFontResourceNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine)
	{
		fontResourceNameToPath_.clear();

		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (passFirstLine) std::getline(ifs, line); // ˆês–Ú‚Í”ò‚Î‚·
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = util::split(line, ',');
			if (strVec.size() >= 2) fontResourceNameToPath_[strVec[0]] = strVec[1];
		}
	}

	void FontManager::loadFontResourceFromNameWithDatabase(const std::string& fontResourceName)
	{
		auto itrRes = fontResourceNameToPath_.find(fontResourceName);
		if (itrRes != fontResourceNameToPath_.end())
		{
			loadFontResourceFromPath(itrRes->second);
		}
	}

	void FontManager::loadFontResourceFromPath(const std::string& fontResourcePath)
	{
		auto itrRes = loadFontResourcePathSet_.find(fontResourcePath);
		if (itrRes == loadFontResourcePathSet_.end())
		{
			if (AddFontResourceEx(fontResourcePath.c_str(), FR_PRIVATE, NULL) > 0)
			{
				loadFontResourcePathSet_.insert(fontResourcePath);
			}
		}
	}

	void FontManager::createFont(const std::string& fontResorceName, const std::string& createFontName, int size, int thick, int fontType)
	{
		auto itr = createFontNameToHandle_.find(createFontName);
		if (itr == createFontNameToHandle_.end())
		{
			int fontHandle = CreateFontToHandle(fontResorceName.c_str(), size, thick, fontType);
			if (fontHandle != -1)
			{
				createFontNameToHandle_[createFontName] = fontHandle;
			}
		}
	}

	void FontManager::deleteFont(const std::string& createFontName)
	{
		auto itr = createFontNameToHandle_.find(createFontName);
		if (itr != createFontNameToHandle_.end())
		{
			DeleteFontToHandle(itr->second);
			createFontNameToHandle_.erase(itr);
		}
	}

	void FontManager::deleteAllFont()
	{
		InitFontToHandle();
		createFontNameToHandle_.clear();
	}

	void FontManager::deleteFontResourceFromNameWithDatabase(const std::string& fontResourceName)
	{
		auto itrRes = fontResourceNameToPath_.find(fontResourceName);
		if (itrRes != fontResourceNameToPath_.end())
		{
			deleteFontResourceFromPath(itrRes->second);
		}
	}

	void FontManager::deleteFontResourceFromPath(const std::string& fontResourcePath)
	{
		auto itrRes = loadFontResourcePathSet_.find(fontResourcePath);
		if (itrRes != loadFontResourcePathSet_.end())
		{
			RemoveFontResourceEx(fontResourcePath.c_str(), FR_PRIVATE, NULL);
			loadFontResourcePathSet_.erase(itrRes);
		}
	}
	
	void FontManager::deleteAllFontResource()
	{
		for (const std::string& loadFontResourcePath : loadFontResourcePathSet_)
		{
			RemoveFontResourceEx(loadFontResourcePath.c_str(), FR_PRIVATE, NULL);
		}
		loadFontResourcePathSet_.clear();
	}

	int FontManager::getFontHandle(const std::string& createFontName) const
	{
		auto itr = createFontNameToHandle_.find(createFontName);
		if (itr != createFontNameToHandle_.end())
		{
			return itr->second;
		}
		return -1;
	}
}