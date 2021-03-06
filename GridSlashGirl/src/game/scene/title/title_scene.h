#ifndef title_scene_h
#define title_scene_h

#include "DxLib.h"
#include "scene/base_scene.h"
#include "device/graphic/image_manager.h"

namespace game::scene::title
{
	class TitleScene : public BaseScene
	{
	private:
		enum class Mode
		{
			title, // タイトル画面
			select // セレクト画面
		};

		const unsigned int whiteColor_ = GetColor(255, 255, 255); // 白色
		const unsigned int blackColor_ = GetColor(0, 0, 0); // 黒色
		const unsigned int redColor_ = GetColor(200, 60, 80);  // 赤色
		
		int elapsedFrame_; // 経過フレーム数
		Mode mode_; // 現在の画面モード
		int select_; // セレクト画面のカーソル位置

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