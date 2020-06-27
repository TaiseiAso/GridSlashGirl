#ifndef base_scene_h
#define base_scene_h

#include <memory>

namespace game::scene
{
	class BaseScene
	{
	private:
		// �R�s�[�R���X�g���N�^���֎~����
		BaseScene(const BaseScene&) = delete;
		BaseScene(BaseScene&&) = delete;

		// �R�s�[������Z�q���֎~����
		BaseScene& operator=(const BaseScene&) = delete;
		BaseScene& operator=(BaseScene&&) = delete;

	protected:
		// �摜�n���h���擾�p�ꎞ�ϐ�
		mutable int imagehandle_;

	public:
		// �R���X�g���N�^ (�h���N���X�̃R���X�g���N�^: �ϐ��̏������≹�y�̃������ǂݍ��݂Ȃ�)
		BaseScene();
		// �f�X�g���N�^ (�h���N���X�̃f�X�g���N�^: ���y�̃������j���Ȃ�)
		virtual ~BaseScene();

		// �V�[���̏��������� (�ϐ��̏������≹�y�̍Đ��Ȃ�)
		virtual void initialize() = 0;
		// �V�[���̏I������ (���y�̒�~�Ȃ�)
		virtual void finalize() = 0;

		// ���͂ɂ��ω�
		virtual void action() = 0;
		// �X�e�b�v���Ƃɐi�ޏ���
		virtual void update() = 0;
		// ��Ԃ̕`��
		virtual void draw() const = 0;
	};
}

#endif // ! base_scene_h