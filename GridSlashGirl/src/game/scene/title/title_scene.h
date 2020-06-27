#ifndef title_scene_h
#define title_scene_h

#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::title
{
	class TitleScene : public BaseScene
	{
	private:
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
		TitleScene();
		// デストラクタ
		~TitleScene();
	};
}

#endif // !title_scene_h