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
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // 白色
		const unsigned int blackColor_ = GetColor(0, 0, 0); // 黒色

		int elapsedFrame_; // 経過フレーム数
		int page_; // 現在表示中の遊び方のページ

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
		HowScene();
		// デストラクタ
		~HowScene();
	};
}

#endif // !how_scene_h