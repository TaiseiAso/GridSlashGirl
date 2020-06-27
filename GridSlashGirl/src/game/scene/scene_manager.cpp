#include <algorithm>
#include "scene_manager.h"
#include "DxLib.h"

namespace game::scene
{
	void SceneManager::initScene(SCENE_ID sceneID)
	{
		auto itr = idToScene_.find(sceneID);
		if (itr != idToScene_.end())
		{
			itr->second->initialize();
		}
	}

	void SceneManager::finalScene(SCENE_ID sceneID)
	{
		auto itr = idToScene_.find(sceneID);
		if (itr != idToScene_.end())
		{
			itr->second->finalize();
		}
	}

	void SceneManager::swapScene()
	{
		// ‚±‚±‚Å‚•‰‰×ˆ—‚ª—\‘z‚³‚ê‚é
		finalScene(currentSceneID_);
		currentSceneID_ = nextSceneID_;
		for (const SCENE_ID& createSceneID : createSceneIDVector_)
		{
			createScene(createSceneID);
		}
		for (const SCENE_ID& deleteSceneID : deleteSceneIDVector_)
		{
			deleteScene(deleteSceneID);
		}
		createSceneIDVector_.clear();
		createSceneIDVector_.shrink_to_fit();
		deleteSceneIDVector_.clear();
		deleteSceneIDVector_.shrink_to_fit();
		initScene(currentSceneID_);
	}

	void SceneManager::updateMoveScene()
	{
		if (isMovingScene_)
		{
			if (moveSceneFrame_ == 0)
			{
				isMovingScene_ = false;
				swapScene();
			}
			else if (isFadeOut_)
			{
				++fadeLevel_;
				if (fadeLevel_ == moveSceneFrame_)
				{
					isFadeOut_ = false;
					swapScene();
				}
			}
			else
			{
				--fadeLevel_;
				if (fadeLevel_ == 0)
				{
					isMovingScene_ = false;
				}
			}
		}
	}

	void SceneManager::drawMoveSceneFade() const
	{
		if (isMovingScene_ && fadeLevel_ > 0 && moveSceneFrame_ > 0)
		{
			if ((isFadeOut_ && drawMoveSceneFadeOut_) || (!isFadeOut_ && drawMoveSceneFadeIn_))
			{
				int alpha = 255 * fadeLevel_ / moveSceneFrame_;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::clamp<int>(alpha, 0, 255));
				DrawBox(0, 0, 800, 640, moveSceneFadeColor_, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}

	SceneManager::SceneManager()
		: isMovingScene_(false),
		  nextSceneID_(SCENE_ID::end),
		  isFadeOut_(true),
		  moveSceneFrame_(0),
		  fadeLevel_(0),
		  drawMoveSceneFadeOut_(true),
		  drawMoveSceneFadeIn_(true),
		  moveSceneFadeColor_(GetColor(0, 0, 0)),
		  currentSceneID_(SCENE_ID::end),
		  sceneFactory_(std::make_unique<SceneFactory>())
	{}

	SceneManager::~SceneManager() {}

	bool SceneManager::step()
	{
		updateMoveScene();
		auto itr = idToScene_.find(currentSceneID_);
		if (itr != idToScene_.end())
		{
			if (!isMovingScene_) itr->second->action();
			itr->second->update();
			itr->second->draw();
			drawMoveSceneFade();
			return true;
		}
		else return false;
	}

	bool SceneManager::isMovingScene() const
	{
		return isMovingScene_;
	}

	float SceneManager::getFadeRatio() const
	{
		if (!isMovingScene_ || moveSceneFrame_ <= 0) return 0.f;
		float fadeRatio = (float)fadeLevel_ / moveSceneFrame_;
		return isFadeOut_ ? fadeRatio : -fadeRatio;
	}

	void SceneManager::setMoveSceneFrame(int moveSceneFrame)
	{
		if (!isMovingScene_) moveSceneFrame_ = moveSceneFrame;
	}

	void SceneManager::setDrawMoveSceneFade(bool drawMoveSceneFadeOut, bool drawMoveSceneFadeIn)
	{
		if (!isMovingScene_)
		{
			drawMoveSceneFadeOut_ = drawMoveSceneFadeOut;
			drawMoveSceneFadeIn_ = drawMoveSceneFadeIn;
		}
	}

	void SceneManager::setMoveSceneFadeColor(unsigned int moveSceneFadeColor)
	{
		if (!isMovingScene_) moveSceneFadeColor_ = moveSceneFadeColor;
	}

	void SceneManager::moveScene(SCENE_ID sceneID, const std::vector<SCENE_ID>& createSceneIDVector, const std::vector<SCENE_ID>& deleteSceneIDVector)
	{
		if (moveSceneFrame_ >= 0 && !isMovingScene_)
		{
			isMovingScene_ = true;
			nextSceneID_ = sceneID;
			isFadeOut_ = true;
			fadeLevel_ = 0;
			createSceneIDVector_ = createSceneIDVector;
			deleteSceneIDVector_ = deleteSceneIDVector;
		}
	}

	void SceneManager::createFirstScene(SCENE_ID sceneID)
	{
		createScene(sceneID);
		idToScene_[sceneID]->initialize();
		currentSceneID_ = sceneID;
	}
	
	void SceneManager::createScene(SCENE_ID sceneID)
	{
		auto itr = idToScene_.find(sceneID);
		if (itr == idToScene_.end())
		{
			idToScene_[sceneID] = sceneFactory_->create(sceneID);
		}
	}

	void SceneManager::deleteScene(SCENE_ID sceneID)
	{
		auto itr = idToScene_.find(sceneID);
		if (itr != idToScene_.end())
		{
			idToScene_.erase(itr);
		}
	}
}