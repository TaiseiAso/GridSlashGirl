#ifndef game_core_h
#define game_core_h

#include <memory>
#include "device/fps/fps_controller.h"

namespace game
{
	// ゲームの最上階層クラス
	class GameCore
	{
	private:
		// FPSを調整するコントローラ
		std::unique_ptr<fps::FPSController> fpsController_;

		// コピーコンストラクタを禁止する
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;

		// コピー代入演算子を禁止する
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;

	public:
		// コンストラクタ
		GameCore();
		// デストラクタ
		~GameCore();

		// ゲームのメインループ
		void loop();
	};
}

#endif // !game_core_h
