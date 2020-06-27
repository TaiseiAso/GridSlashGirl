#include "input_receiver.h"
#include "DxLib.h"

namespace game::input
{
	InputReceiver::InputReceiver() {}
	InputReceiver::~InputReceiver() {}

	void InputReceiver::update()
	{
		char tmpKey[256]; // 現在のキーの入力状態を格納する
		GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
		for (int i = 0; i < 256; i++) {
			if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
				pushKeyFrameArray_[i]++; // 加算
			}
			else { // 押されていなければ
				pushKeyFrameArray_[i] = 0; // 0にする
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