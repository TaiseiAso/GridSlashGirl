#ifndef battle_scene_h
#define battle_scene_h

#include "DxLib.h"
#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::battle
{
	class BattleScene : public BaseScene
	{
	private:
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // 白色
		const unsigned int blackColor_ = GetColor(0, 0, 0); // 黒色
		const unsigned int redColor_ = GetColor(200, 60, 80);  // 赤色
		const unsigned int blueColor_ = GetColor(60, 80, 200); // 青色
		const unsigned int greenColor_ = GetColor(80, 200, 60); // 緑色

		int elapsedFrame_; // 経過フレーム数

		// シーンの初期化処理
		void initialize() override;
		// シーンの終了処理
		void finalize() override;

		// 入力による変化
		void action() override;
		// ステップごとに進む処理
		void update() override;
		// 状態の描画
		void draw() const override;

	public:
		// コンストラクタ
		BattleScene();
		// デストラクタ
		~BattleScene();
	};
}

#endif // !battle_scene_h