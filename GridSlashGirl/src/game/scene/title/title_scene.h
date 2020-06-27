#ifndef title_scene_h
#define title_scene_h

#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::title
{
	class TitleScene : public BaseScene
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
		TitleScene();
		// �f�X�g���N�^
		~TitleScene();
	};
}

#endif // !title_scene_h