#include "input_receiver.h"
#include "DxLib.h"

namespace game::input
{
	InputReceiver::InputReceiver() {}
	InputReceiver::~InputReceiver() {}

	void InputReceiver::update()
	{
		char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
		GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
		for (int i = 0; i < 256; i++) {
			if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
				pushKeyFrameArray_[i]++; // ���Z
			}
			else { // ������Ă��Ȃ����
				pushKeyFrameArray_[i] = 0; // 0�ɂ���
			}
		}
	}

	int InputReceiver::getPushKeyFrame(int keyID) const
	{
		return pushKeyFrameArray_[keyID];
	}

	bool InputReceiver::isPushKeyNow(int keyID) const
	{
		return pushKeyFrameArray_[keyID] == 1;
	}

	bool InputReceiver::isPushingKey(int keyID) const
	{
		return pushKeyFrameArray_[keyID] > 0;
	}
}