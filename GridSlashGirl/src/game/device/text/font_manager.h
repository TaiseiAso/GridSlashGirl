#ifndef font_manager_h
#define font_manager_h

#include <unordered_map>
#include <unordered_set>
#include "utils/singleton.h"

namespace game::text
{
	class FontManager : public Singleton<FontManager>
	{
		friend class Singleton<FontManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		// �������ɓǂݍ��ރt�H���g�̖��O�ƃt�@�C���p�X�̃}�b�v
		std::unordered_map<std::string, std::string> fontResourceNameToPath_;

		// �������ɓǂݍ��񂾃t�H���g�̃t�@�C���p�X�̃Z�b�g
		std::unordered_set<std::string> loadFontResourcePathSet_;

		// �쐬�����t�H���g�̎��ʖ��ƃn���h���̃}�b�v
		std::unordered_map<std::string, int> createFontNameToHandle_;

		FontManager(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~FontManager();

	public:
		// �t�H���g�̖��O�ƃt�@�C���p�X���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadFontResourceNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine = true);

		// �t�H���g�̖��O����t�H���g���\�[�X���������ɓǂݍ��� (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		void loadFontResourceFromNameWithDatabase(const std::string& fontResourceName);
		// �t�H���g�̃t�@�C���p�X����t�H���g���\�[�X���������ɓǂݍ���
		void loadFontResourceFromPath(const std::string& fontResourcePath);

		// �C�ӂ̃T�C�Y, ����, �^�C�v�̃t�H���g���쐬���������ɓǂݍ��� (�n���h����Ԃ�) (���ɍ쐬�ς݂Ȃ炻�̃n���h����Ԃ�)
		void createFont(const std::string& fontResorceName, const std::string& createFontName, int size, int thick, int fontType);

		// �쐬�ς݂̃t�H���g������������j������
		void deleteFont(const std::string& createFontName);
		// �쐬�ς݂̃t�H���g��S�ă���������j������
		void deleteAllFont();

		// �t�H���g�̖��O����t�H���g���\�[�X������������j������ (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		void deleteFontResourceFromNameWithDatabase(const std::string& fontResourceName);
		// �t�H���g�̃t�@�C���p�X����t�H���g���\�[�X������������j������
		void deleteFontResourceFromPath(const std::string& fontResourcePath);
		// �ǂݍ��񂾑S�Ẵt�H���g���\�[�X������������j������
		void deleteAllFontResource();

		// �쐬�ς݂̃t�H���g�̃n���h�����擾����
		int getFontHandle(const std::string& createFontName) const;
	};
}

#endif // !font_manager_h