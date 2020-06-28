#include "battle_scene.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "device/text/font_manager.h"
#include "../scene_manager.h"

namespace game::scene::battle
{
	void BattleScene::initialize()
	{
		elapsedFrame_ = 0;
	}

	void BattleScene::finalize()
	{

	}

	void BattleScene::action()
	{
		
	}

	void BattleScene::update()
	{
		if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
	}

	void BattleScene::draw() const
	{
		DrawBox(0, 0, 800, 200, whiteColor_, TRUE);
	}

	BattleScene::BattleScene()
		: elapsedFrame_(0)
	{

	}

	BattleScene::~BattleScene()
	{
		
	}
}