#ifndef scene_factory_h
#define scene_factory_h

#include "test/test_scene.h"
#include "battle/battle_scene.h"
#include "title/title_scene.h"

namespace game::scene
{
	enum class SCENE_ID {
		test,
		title,
		battle,
		end
	};

	class SceneFactory
	{
	public:
		std::unique_ptr<BaseScene> create(SCENE_ID sceneID);
	};
}

#endif // !scene_factory_h