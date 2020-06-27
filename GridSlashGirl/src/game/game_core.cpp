#include "game_core.h"
#include "DxLib.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "device/graphic/image_manager.h"
#include "device/text/font_manager.h"
#include "scene/scene_manager.h"
#include "game_manager.h"

namespace game
{
	GameCore::GameCore()
		: fpsController_(std::make_unique<fps::FPSController>())
	{
		input::InputReceiver::create();
		audio::MusicPlayer::create();
		graphic::ImageManager::create();
		text::FontManager::create();

		audio::MusicPlayer::instance().loadMusicNameToPathDatabase("resource/database/music_name_to_path.csv");
		graphic::ImageManager::instance().loadImageNameToPathDatabase("resource/database/image_name_to_path.csv");
		graphic::ImageManager::instance().loadGroupNameToDivDataDatabase("resource/database/group_name_to_divdata.csv");
		graphic::ImageManager::instance().loadGroupNameToFramesDatabase("resource/database/group_name_to_frames.csv");
		
		text::FontManager::instance().loadFontResourceNameToPathDatabase("resource/database/font_resource_name_to_path.csv");
		//text::FontManager::instance().loadFontResourceFromNameWithDatabase("Voyager Grotesque Bold");

		scene::SceneManager::create();
		scene::SceneManager::instance().createFirstScene(scene::SCENE_ID::test);

		// テスト用
		scene::SceneManager::instance().setMoveSceneFadeColor(GetColor(255, 255, 255));
		scene::SceneManager::instance().setMoveSceneFrame(60);

		GameManager::create();
	}

	GameCore::~GameCore()
	{
		GameManager::destroy();
		scene::SceneManager::destroy();
		text::FontManager::destroy();
		graphic::ImageManager::destroy();
		audio::MusicPlayer::destroy();
		input::InputReceiver::destroy();
	}

	void GameCore::loop()
	{
		while (!ProcessMessage())
		{
			fpsController_->update();
			input::InputReceiver::instance().update();
			audio::MusicPlayer::instance().update();

			ClearDrawScreen();
			
			if (!scene::SceneManager::instance().step()) break;
			fpsController_->draw(); // テスト用
			
			ScreenFlip();
			
			fpsController_->wait();
		}
	}
}