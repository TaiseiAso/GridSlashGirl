#ifndef image_manager_h
#define image_manager_h

#include <unordered_map>
#include "utils/singleton.h"

namespace game::graphic
{
	struct AnimeElapsedData {
		int frame; // ����摜�ɂ�����o�߃t���[����
		int sheet; // �A�j���̕\���摜�ԍ�
	};

	class ImageManager : public Singleton<ImageManager>
	{
		friend class Singleton<ImageManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		struct ImageDivData {
			int allNum; // �摜�̕�������
			int xNum; // �摜�̉��ɑ΂��镪����
			int yNum; // �摜�̏c�ɑ΂��镪����
			int sizeX; // ������̉摜�̉��̃T�C�Y
			int sizeY; // ������̉摜�̏c�̃T�C�Y
		};

		// �������ɓǂݍ��މ摜�̖��O�ƃt�@�C���p�X�̃}�b�v
		std::unordered_map<std::string, std::string> imageNameToPath_;
		// �������ɓǂݍ��ޏW���摜�̖��O�Ɖ摜�̕������@�̍\���̂̃}�b�v
		std::unordered_map<std::string, ImageDivData> groupNameToDivData_;
		// �������ɓǂݍ��ޏW���摜�̖��O�ƕ�����̉摜�̕`��t���[�����̃��X�g�̃}�b�v
		std::unordered_map<std::string, std::vector<int>> groupNameToFrameVector_;
		
		// �������ɓǂݍ��񂾉摜�̖��O�ƃn���h���̃}�b�v
		std::unordered_map<std::string, int> imageNameToHandle_;
		// �������ɓǂݍ��񂾏W���摜�̖��O�ƃn���h���̃��X�g�̃}�b�v
		std::unordered_map<std::string, std::vector<int>> groupNameToHandleVector_;

		ImageManager(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~ImageManager();

	public:
		// �摜(�W���摜���܂�)�̖��O�ƃt�@�C���p�X���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadImageNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine = true);
		// �W���摜�̖��O�Ɖ摜�̕������@���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadGroupNameToDivDataDatabase(const std::string& databaseFilePath, bool passFirstLine = true);
		// �W���摜�̖��O�ƕ�����̉摜�̕`��t���[�������Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadGroupNameToFramesDatabase(const std::string& databaseFilePath, bool passFirstLine = true);

		// �摜���������ɓǂݍ��� (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		void loadImage(const std::string& imageName);
		// �摜���������ɓǂݍ���
		void loadImage(const std::string& imageName, const std::string& imageFilePath); // ��ɗՎ��e�X�g�p
		// �W���摜���������ɓǂݍ��� (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		void loadGroup(const std::string& groupName);
		// �W���摜���������ɓǂݍ���
		void loadGroup(const std::string& groupName, const std::string& imageFilePath, int allNum, int xNum, int yNum, int sizeX, int sizeY);  // ��ɗՎ��e�X�g�p

		// ����������摜��j������
		void deleteImage(const std::string& imageName);
		// ����������W���摜��j������
		void deleteGroup(const std::string& groupName);

		// ���ׂẲ摜������������j������
		void deleteAllImage();
		// ���ׂĂ̏W���摜������������j������
		void deleteAllGroup();
		// ���ׂẲ摜(�W���摜���܂�)������������j������
		void deleteAllImageAndGroup();

		// �摜�̃n���h�����擾 (���s�����-1��Ԃ�)
		int getImageHandle(const std::string& imageName) const;
		// �W���摜�̎w�肵���摜�̃n���h�����擾 (���s�����-1��Ԃ�)
		int getImageHandleInGroup(const std::string& groupName, int id) const;
		// �W���ʐ^���A�j���[�V�����Ƃ��ĕ`�悷�邽�߂ɉ摜�̃n���h�����擾 (���s�����-1��Ԃ�) (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		int getImageHandleInAnime(const std::string& groupName, AnimeElapsedData* const elapsedData) const;
		// �W���ʐ^���A�j���[�V�����Ƃ��ĕ`�悷�邽�߂ɉ摜�̃n���h�����擾 (���s�����-1��Ԃ�)
		int getImageHandleInAnime(const std::string& groupName, AnimeElapsedData* const elapsedData, const std::vector<int>& frameVector) const;
	};
}

#endif // !image_manager_h