#include "how_scene.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "device/text/font_manager.h"
#include "../scene_manager.h"
#include <string>

namespace game::scene::how
{
	void HowScene::initialize()
	{
		elapsedFrame_ = 0;
		page_ = 0;
	}

	void HowScene::finalize()
	{

	}

	void HowScene::action()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Q))
		{
			SceneManager::instance().moveScene(SCENE_ID::title, { SCENE_ID::title }, { SCENE_ID::how });
		}
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_LEFT))
		{
			if (--page_ < 0) page_ = 0;
		}
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_RIGHT))
		{
			if (++page_ > 5) page_ = 5;
		}
	}

	void HowScene::update()
	{
		if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
	}

	void HowScene::draw() const
	{
		DrawBox(50, 50, 750, 590, whiteColor_, TRUE);
		int fontHandle = text::FontManager::instance().getFontHandle("test_how");
		DrawStringToHandle(100, 100, std::to_string(page_+1).c_str(), blackColor_, fontHandle);
		if (page_ > 0) DrawBox(10, 295, 40, 345, whiteColor_, TRUE);
		if (page_ < 5) DrawBox(760, 295, 790, 345, whiteColor_, TRUE);
	}

	HowScene::HowScene()
		: elapsedFrame_(0),
		  page_(0)
	{
		text::FontManager::instance().createFont("Voyager Grotesque Bold", "test_how", 32, 6, DX_FONTTYPE_ANTIALIASING);
	}

	HowScene::~HowScene()
	{
		text::FontManager::instance().deleteFont("test_how");
	}
}