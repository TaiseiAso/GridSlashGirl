#ifndef font_manager_h
#define font_manager_h

#include <unordered_map>
#include <unordered_set>
#include "utils/singleton.h"

namespace game::text
{
	class FontManager : public Singleton<FontManager>
	{
		friend class Singleton<FontManager>; // Singleton でのインスタンス作成は許可

	private:
		// メモリに読み込むフォントの名前とファイルパスのマップ
		std::unordered_map<std::string, std::string> fontResourceNameToPath_;

		// メモリに読み込んだフォントのファイルパスのセット
		std::unordered_set<std::string> loadFontResourcePathSet_;

		// 作成したフォントの識別名とハンドルのマップ
		std::unordered_map<std::string, int> createFontNameToHandle_;

		FontManager(); // 外部でのインスタンス作成は禁止
		~FontManager();

	public:
		// フォントの名前とファイルパスが対応付けられたデータベースを読み込む
		void loadFontResourceNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine = true);

		// フォントの名前からフォントリソースをメモリに読み込む (データベースの読み込みが前提)
		void loadFontResourceFromNameWithDatabase(const std::string& fontResourceName);
		// フォントのファイルパスからフォントリソースをメモリに読み込む
		void loadFontResourceFromPath(const std::string& fontResourcePath);

		// 任意のサイズ, 太さ, タイプのフォントを作成しメモリに読み込む (ハンドルを返す) (既に作成済みならそのハンドルを返す)
		void createFont(const std::string& fontResorceName, const std::string& createFontName, int size, int thick, int fontType);

		// 作成済みのフォントをメモリから破棄する
		void deleteFont(const std::string& createFontName);
		// 作成済みのフォントを全てメモリから破棄する
		void deleteAllFont();

		// フォントの名前からフォントリソースをメモリから破棄する (データベースの読み込みが前提)
		void deleteFontResourceFromNameWithDatabase(const std::string& fontResourceName);
		// フォントのファイルパスからフォントリソースをメモリから破棄する
		void deleteFontResourceFromPath(const std::string& fontResourcePath);
		// 読み込んだ全てのフォントリソースをメモリから破棄する
		void deleteAllFontResource();

		// 作成済みのフォントのハンドルを取得する
		int getFontHandle(const std::string& createFontName) const;
	};
}

#endif // !font_manager_h