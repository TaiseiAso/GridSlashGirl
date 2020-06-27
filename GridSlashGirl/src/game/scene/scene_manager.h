#ifndef scene_manager_h
#define scene_manager_h

#include <memory>
#include <unordered_map>
#include "utils/singleton.h"
#include "scene_factory.h"

namespace game::scene
{
	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>; // Singleton でのインスタンス作成は許可

	private:
		bool isMovingScene_; // シーンを移動中かどうか
		SCENE_ID nextSceneID_; // 移動先のシーンID
		bool isFadeOut_; // フェードアウトかフェードインインかの判別
		int moveSceneFrame_; // シーン移動に要するフレーム数
		int fadeLevel_; // フェードのかかり具合 (最大はmoveSceneFrame)
		bool drawMoveSceneFadeOut_; // フェードアウトを描画するかどうか
		bool drawMoveSceneFadeIn_; // フェードインを描画するかどうか
		unsigned int moveSceneFadeColor_; // シーン移動時のフェード色
		std::vector<SCENE_ID> createSceneIDVector_; // シーン移動時に作成するシーンIDのリスト
		std::vector<SCENE_ID> deleteSceneIDVector_; // シーン移動時に破棄するシーンIDのリスト

		// シーンIDと作成したシーンのマップ
		std::unordered_map<SCENE_ID, std::unique_ptr<BaseScene>> idToScene_;
		// 現在のシーンID
		SCENE_ID currentSceneID_;

		// シーンファクトリ
		std::unique_ptr<SceneFactory> sceneFactory_;

		// シーンを初期化する
		void initScene(SCENE_ID sceneID);
		// シーンを終了する
		void finalScene(SCENE_ID sceneID);

		// 現在のシーンを交換する
		void swapScene();
		// シーン移動を更新する
		void updateMoveScene();

		// シーン移動のフェードイン/アウトを描画する
		void drawMoveSceneFade() const;

		SceneManager(); // 外部でのインスタンス作成は禁止
		~SceneManager();

	public:
		// ステップごとの処理 (終了時falseを返す)
		// 一箇所のみからの呼び出しを許可する
		bool step();

		// 現在シーン移動中かどうかを取得
		bool isMovingScene() const;
		/*
			シーン移動状況を取得する (-1.0~1.0の間の値)
			-1.0~0.0: フェードイン中
			0.0: シーン移動中ではない (もしくは即時シーン移動の瞬間)
			0.0~1.0: フェードアウト中
		*/
		float getFadeRatio() const;

		// シーン移動に要するフレーム数を設定する
		void setMoveSceneFrame(int moveSceneFrame);
		// フェードアウト/インを描画するかどうかを設定する
		void setDrawMoveSceneFade(bool drawMoveSceneFadeOut, bool drawMoveSceneFadeIn);
		// シーン移動時のフェード色を設定する
		void setMoveSceneFadeColor(unsigned int moveSceneFadeColor);

		// シーン移動を開始する
		void moveScene(SCENE_ID sceneID, const std::vector<SCENE_ID>& createSceneIDVector = {}, const std::vector<SCENE_ID>& deleteSceneIDVector = {});

		// 最初のシーンを作成する
		void createFirstScene(SCENE_ID sceneID);
		// シーンを作成する
		void createScene(SCENE_ID sceneID);

		// シーンを破棄する
		void deleteScene(SCENE_ID sceneID);
	};
}

#endif // !scene_manager_h