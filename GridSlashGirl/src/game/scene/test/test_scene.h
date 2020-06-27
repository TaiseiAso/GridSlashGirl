#ifndef test_scene_h
#define test_scene_h

#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::test
{
	class TestScene : public BaseScene
	{
	private:
		mutable graphic::AnimeElapsedData testElapsedData_;

		int elapsedFrame_; // �o�߃t���[����

		int testMusicHandle1_;
		int testMusicHandle2_;

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
		TestScene();
		// �f�X�g���N�^
		~TestScene();
	};
}

#endif // !test_scene_h