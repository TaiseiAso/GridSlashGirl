#ifndef game_core_h
#define game_core_h

#include <memory>
#include "device/fps/fps_controller.h"

namespace game
{
	// �Q�[���̍ŏ�K�w�N���X
	class GameCore
	{
	private:
		// FPS�𒲐�����R���g���[��
		std::unique_ptr<fps::FPSController> fpsController_;

		// �R�s�[�R���X�g���N�^���֎~����
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;

		// �R�s�[������Z�q���֎~����
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;

	public:
		// �R���X�g���N�^
		GameCore();
		// �f�X�g���N�^
		~GameCore();

		// �Q�[���̃��C�����[�v
		void loop();
	};
}

#endif // !game_core_h
