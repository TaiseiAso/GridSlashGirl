#ifndef input_receiver_h
#define input_receiver_h

#include "utils/singleton.h"

namespace game::input
{
	class InputReceiver : public Singleton<InputReceiver>
	{
		friend class Singleton<InputReceiver>; // Singleton でのインスタンス作成は許可

	private:
		int pushKeyFrameArray_[256] = {}; // 全てのキーが押されているフレーム数

		InputReceiver();// 外部でのインスタンス作成は禁止
		~InputReceiver();

	public:
		// キー入力状態を更新する
		void update();
		
		// 指定したキーが押されているフレーム数を取得する
		int getPushKeyFrame(int keyID) const;
		
		// 指定したキーが直近に押されたかを取得する
		bool isPushKeyNow(int keyID) const;

		// 指定したキーが現在押されているかを取得する
		bool isPushingKey(int keyID) const;
	};
}

#endif // !input_receiver_h