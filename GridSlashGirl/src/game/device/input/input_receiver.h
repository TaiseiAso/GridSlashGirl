#ifndef input_receiver_h
#define input_receiver_h

#include "utils/singleton.h"

namespace game::input
{
	class InputReceiver : public Singleton<InputReceiver>
	{
		friend class Singleton<InputReceiver>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		int pushKeyFrameArray_[256] = {}; // �S�ẴL�[��������Ă���t���[����

		InputReceiver();// �O���ł̃C���X�^���X�쐬�͋֎~
		~InputReceiver();

	public:
		// �L�[���͏�Ԃ��X�V����
		void update();
		
		// �w�肵���L�[��������Ă���t���[�������擾����
		int getPushKeyFrame(int keyID) const;
		
		// �w�肵���L�[�����߂ɉ����ꂽ�����擾����
		bool isPushKeyNow(int keyID) const;

		// �w�肵���L�[�����݉�����Ă��邩���擾����
		bool isPushingKey(int keyID) const;
	};
}

#endif // !input_receiver_h