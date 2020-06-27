#ifndef battle_scene_h
#define battle_scene_h

#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::battle
{
	class BattleScene : public BaseScene
	{
	private:
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