#include "scene_factory.h"

namespace game::scene
{
	std::unique_ptr<BaseScene> SceneFactory::create(SCENE_ID sceneID)
	{
		std::unique_ptr<BaseScene> createdScene;
		switch (sceneID)
		{
		case SCENE_ID::test:
			createdScene = std::make_unique<test::TestScene>();
			break;
		case SCENE_ID::title:
			createdScene = std::make_unique<title::TitleScene>();
			break;
		case SCENE_ID::battle:
			createdScene = std::make_unique<battle::BattleScene>();
			break;
		default:
			createdScene = nullptr;
			break;
		}
		return createdScene;
	}
}