#ifndef battle_scene_h
#define battle_scene_h

#include "DxLib.h"
#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::battle
{
	class BattleScene : public BaseScene
	{
	private:
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // ���F
		const unsigned int blackColor_ = GetColor(0, 0, 0); // ���F
		const unsigned int redColor_ = GetColor(200, 60, 80);  // �ԐF
		const unsigned int blueColor_ = GetColor(60, 80, 200); // �F
		const unsigned int greenColor_ = GetColor(80, 200, 60); // �ΐF

		int elapsedFrame_; // �o�߃t���[����

		// �V�[���̏���������
		void initialize() override;
		// �V�[���̏I������
		void finalize() override;

		// ���͂ɂ��ω�
		void action() override;
		// �X�e�b�v���Ƃɐi�ޏ���
		void update() override;
		// ��Ԃ̕`��
		void draw() const override;

	public:
		// �R���X�g���N�^
		BattleScene();
		// �f�X�g���N�^
		~BattleScene();
	};
}

#endif // !battle_scene_h