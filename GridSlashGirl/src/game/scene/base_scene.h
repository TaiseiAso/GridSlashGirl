#ifndef base_scene_h
#define base_scene_h

#include <memory>

namespace game::scene
{
	class BaseScene
	{
	private:
		// コピーコンストラクタを禁止する
		BaseScene(const BaseScene&) = delete;
		BaseScene(BaseScene&&) = delete;

		// コピー代入演算子を禁止する
		BaseScene& operator=(const BaseScene&) = delete;
		BaseScene& operator=(BaseScene&&) = delete;

	protected:
		// 画像ハンドル取得用一時変数
		mutable int imagehandle_;

	public:
		// コンストラクタ (派生クラスのコンストラクタ: 変数の初期化や音楽のメモリ読み込みなど)
		BaseScene();
		// デストラクタ (派生クラスのデストラクタ: 音楽のメモリ破棄など)
		virtual ~BaseScene();

		// シーンの初期化処理 (変数の初期化や音楽の再生など)
		virtual void initialize() = 0;
		// シーンの終了処理 (音楽の停止など)
		virtual void finalize() = 0;

		// 入力による変化
		virtual void action() = 0;
		// ステップごとに進む処理
		virtual void update() = 0;
		// 状態の描画
		virtual void draw() const = 0;
	};
}

#endif // ! base_scene_h