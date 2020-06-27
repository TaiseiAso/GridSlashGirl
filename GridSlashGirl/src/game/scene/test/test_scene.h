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

		int elapsedFrame_; // 経過フレーム数

		int testMusicHandle1_;
		int testMusicHandle2_;

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
		TestScene();
		// デストラクタ
		~TestScene();
	};
}

#endif // !test_scene_h