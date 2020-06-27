#include "test_scene.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "../scene_manager.h"
#include "DxLib.h"

namespace game::scene::test
{
	void TestScene::initialize()
	{

	}

	void TestScene::finalize()
	{
		//audio::MusicPlayer::instance().stopMusic("test1");
	}

	void TestScene::action()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_P))
		{
			testMusicHandle1_ = audio::MusicPlayer::instance().playMusic("test_", 255.f);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_S))
		{
			audio::MusicPlayer::instance().stopMusic(&testMusicHandle1_);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Q))
		{
			audio::MusicPlayer::instance().setPlayMusicVolume(testMusicHandle1_, 120);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_W))
		{
			audio::MusicPlayer::instance().setPlayMusicVolume(testMusicHandle1_, 255);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_E))
		{
			audio::MusicPlayer::instance().setMasterVolume(0.5f);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_R))
		{
			audio::MusicPlayer::instance().setMasterVolume(1.f);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_T))
		{
			audio::MusicPlayer::instance().deleteAllMusic();
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Y))
		{
			SceneManager::instance().moveScene(SCENE_ID::title, { SCENE_ID::title }, { SCENE_ID::test });
		}
		else if (input::InputReceiver::instance().isPushingKey(KEY_INPUT_U))
		{
			if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
			audio::MusicPlayer::instance().setPlayMusicDistance(testMusicHandle1_, 200 * std::abs(std::sinf(elapsedFrame_ / 30.f)));
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_I))
		{
			audio::MusicPlayer::instance().startFadeMusicVolume(testMusicHandle1_, 100, 60, true);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_O))
		{
			audio::MusicPlayer::instance().startFadeMusicVolume(testMusicHandle1_, 255, 60);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Z))
		{
			testMusicHandle2_ = audio::MusicPlayer::instance().playMusic("test", 255.f);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_X))
		{
			audio::MusicPlayer::instance().stopMusic(&testMusicHandle2_);
		}
	}

	void TestScene::update()
	{

	}

	void TestScene::draw() const
	{
		DrawCircle(100, 100, 100, GetColor(255, 255, 255), 1, 1);
		DrawBox(200, 200, 230, 230, GetColor(0, 0, 0), TRUE);

		DrawFormatString(
			200, 200, GetColor(255, 255, 255),
			"%d", input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_SPACE)
		);

		int handle;
		handle = graphic::ImageManager::instance().getImageHandle("test");
		DrawGraph(300, 300, handle, TRUE);

		handle = graphic::ImageManager::instance().getImageHandleInGroup("test", 2);
		DrawGraph(300, 000, handle, TRUE);

		handle = graphic::ImageManager::instance().getImageHandleInAnime("test", &testElapsedData_);
		DrawGraph(0, 300, handle, TRUE);

		DrawCircle(
			450 + (int)(SceneManager::instance().getFadeRatio() * 450),
			500, 30, GetColor(255, 255, 255), 1, 1);

		DrawCircle(
			400 + (int)(200 * std::sinf(elapsedFrame_ / 30.f)),
			200, 30, GetColor(0, 255, 255), 1, 1);
	}

	TestScene::TestScene()
		: elapsedFrame_(0),
		  testMusicHandle1_(-1),
		  testMusicHandle2_(-1)
	{
		audio::MusicPlayer::instance().loadMusic("test");
		audio::MusicPlayer::instance().loadMusic("test_");
		graphic::ImageManager::instance().loadImage("test");
		graphic::ImageManager::instance().loadGroup("test");

		testElapsedData_ = { 0, 0 };

		audio::MusicPlayer::instance().setVolumeAttenuationCoefficient(0.002f);
	}

	TestScene::~TestScene()
	{
		audio::MusicPlayer::instance().deleteMusic("test");
		audio::MusicPlayer::instance().deleteMusic("test_");
		graphic::ImageManager::instance().deleteImage("test");
		graphic::ImageManager::instance().deleteGroup("test");
	}
}