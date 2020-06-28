#ifndef how_scene_h
#define how_scene_h

#include "DxLib.h"
#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::how
{
	class HowScene : public BaseScene
	{
	private:
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // ���F
		const unsigned int blackColor_ = GetColor(0, 0, 0); // ���F

		int elapsedFrame_; // �o�߃t���[����
		int page_; // ���ݕ\�����̗V�ѕ��̃y�[�W

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
		HowScene();
		// �f�X�g���N�^
		~HowScene();
	};
}

#endif // !how_scene_h