#ifndef music_player_h
#define music_player_h

#include <unordered_map>
#include "utils/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
		friend class Singleton<MusicPlayer>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		struct MusicVolumeAndDistance {
			float volume; // ���y�̍Đ�����
			float distance; // �����ƃ��X�i�[�̋��� (0�ȉ��Ȃ狗���𖳎����ĉ��ʌ������Ȃ�)
		};

		struct MusicVolumeFadeData {
			int fadeFrame; // �t�F�[�h�ɂ�����t���[����
			float deltaVolumeFade; // 1�t���[���ŕω����鉹��
			bool stopWhenFadeFinish; // �t�F�[�h�I����ɉ��y���~���邩
		};

		// �������ɓǂݍ��މ��y�̖��O�ƃt�@�C���p�X�̃}�b�v
		std::unordered_map<std::string, std::string> loadMusicNameToPath_;

		// �������ɓǂݍ��񂾉��y�̖��O�ƃn���h���̃}�b�v
		std::unordered_map<std::string, int> loadMusicNameToHandle_;

		// �Đ����Ă��鉹�y�̃n���h����<�Đ�����, ���X�i�[�Ƃ̋���>�̍\���̂̃}�b�v
		std::unordered_map<int, MusicVolumeAndDistance> playMusicHandleToVolumeAndDistance_;

		// �Đ����Ă��鉹�y�̉��ʂ�ω������邽�߂̏��Z�b�g
		std::unordered_map<int, MusicVolumeFadeData> playMusicHandleToVolumeFadeData_;

		// �S�̂̉��ʔ䗦 (-1����1�̊Ԃ̒l)
		float masterVolume_;

		// �����ƃ��X�i�[�̋����ɂ�鉹�ʌ����̌W�� (�傫���قǌ������₷��) (0�ȉ��Ȃ猸�����Ȃ�)
		float volumeAttenuationCoefficient_;

		// �Đ����̉��y�̉��ʂ��X�V����
		void setPlayMusicVolume(int playMusicHandle, float playMusicVolume, float playMusicDistance) const;
		// �Đ����̑S�Ẳ��y�̉��ʂ��X�V����
		void updateAllPlayMusicVolume() const;

		MusicPlayer(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~MusicPlayer();

	public:
		// ���y�̖��O�ƃt�@�C���p�X���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadMusicNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine = true);
		
		// ���y���������ɓǂݍ��� (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		void loadMusic(const std::string& loadMusicName);
		// ���y���������ɓǂݍ���
		void loadMusic(const std::string& loadMusicName, const std::string& loadMusicFilePath);
		
		// ���y������������j������
		void deleteMusic(const std::string& loadMusicName);

		// �������ɓǂݍ��񂾉��y���Đ����� (���Ƃ��琧�䂵�Ȃ����ʉ��p)
		void playSE(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance = 0.f) const;
		// �������ɓǂݍ��񂾉��y���Đ����� (�n���h����Ԃ�) (���s�����-1��Ԃ�)
		int playMusic(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance = 0.f, bool isLoop = true, bool topPositionFlag = true);

		// �Đ����̉��y���~����
		void stopMusic(int* const playMusicHandle);

		// ���ׂẲ��y������������j������
		void deleteAllMusic();

		// �Đ����̉��y�̉��ʂ�ύX����
		void setPlayMusicVolume(int playMusicHandle, float playMusicVolume);
		// �Đ����̉��y�̃��X�i�[�Ƃ̋�����ύX����
		void setPlayMusicDistance(int playMusicHandle, float playMusicDistance);

		// �}�X�^�[���ʂ�ύX���� (-1����1�̊Ԃ̒l)
		void setMasterVolume(float masterVolume);
		// �}�X�^�[���ʂ��擾����
		float getMasterVolume() const;

		// �����ƃ��X�i�[�̋����ɂ�鉹�ʌ����̌W����ύX����
		void setVolumeAttenuationCoefficient(float volumeAttenuationCoefficient);
		// �����ƃ��X�i�[�̋����ɂ�鉹�ʌ����̌W�����擾����
		float getVolumeAttenuationCoefficient() const;

		// �I�����Ă���̂ɒ�~���Ă��Ȃ����y���~����
		void stopFinishedMusic(int* const playMusicHandle);

		// �Đ����̉��y�̉��ʂ̃t�F�[�h���J�n����
		void startFadeMusicVolume(int playMusicHandle, float targetVolume, int fadeFrame, bool stopWhenFadeFinish = false);

		// �Đ����ł��t�F�[�h���̉��y�̉��ʂ��X�V����
		void update();
	};
}

#endif // !music_player_h