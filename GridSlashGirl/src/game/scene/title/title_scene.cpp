#include "title_scene.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "device/text/font_manager.h"
#include "../scene_manager.h"

namespace game::scene::title
{
	void TitleScene::initialize()
	{
		elapsedFrame_ = 0;
		mode_ = Mode::title;
		select_ = 0;
	}

	void TitleScene::finalize()
	{

	}

	void TitleScene::action()
	{
		switch (mode_)
		{
		case Mode::title: // �^�C�g�����
			if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_SPACE))
			{
				mode_ = Mode::select; // �Z���N�g��ʂ֐i��
			}
			break;
		case Mode::select: // �Z���N�g���
			if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_UP))
			{
				--select_;
				if (select_ < 0) select_ = 3;
			}
			if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_DOWN))
			{
				++select_;
				if (select_ > 3) select_ = 0;
			}
			if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_SPACE))
			{
				switch (select_)
				{
				case 0: // �Q�[���X�^�[�g
					SceneManager::instance().moveScene(SCENE_ID::battle, { SCENE_ID::battle }, { SCENE_ID::title });
					break;
				case 1: // �V�ѕ�
					SceneManager::instance().moveScene(SCENE_ID::how, { SCENE_ID::how }, { SCENE_ID::title });
					break;
				case 2: // �^�C�g����ʂ֖߂�
					mode_ = Mode::title;
					select_ = 0;
					break;
				case 3: // �Q�[�����I������
					SceneManager::instance().setMoveSceneFrame(0);
					SceneManager::instance().moveScene(SCENE_ID::end);
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	void TitleScene::update()
	{
		if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
	}

	void TitleScene::draw() const
	{
		DrawBox(0, 0, 800, 640, whiteColor_, TRUE);
		int fontHandle = text::FontManager::instance().getFontHandle("test");
		switch (mode_)
		{
		case Mode::title: // �^�C�g�����
			DrawStringToHandle(230, 400, "PLEASE PUSH SPACE KEY", blackColor_, fontHandle);
			break;
		case Mode::select: // �Z���N�g���
			DrawStringToHandle(230, 360, "GAME START", select_ == 0 ? redColor_ : blackColor_, fontHandle);
			DrawStringToHandle(230, 410, "HOW TO PLAY", select_ == 1 ? redColor_ : blackColor_, fontHandle);
			DrawStringToHandle(230, 460, "BACK", select_ == 2 ? redColor_ : blackColor_, fontHandle);
			DrawStringToHandle(230, 510, "EXIT", select_ == 3 ? redColor_ : blackColor_, fontHandle);
			break;
		}
	}

	TitleScene::TitleScene()
		: elapsedFrame_(0),
		  mode_(Mode::title),
		  select_(0)
	{
		text::FontManager::instance().createFont("Voyager Grotesque Bold", "test", 32, 6, DX_FONTTYPE_ANTIALIASING);
	}

	TitleScene::~TitleScene()
	{
		text::FontManager::instance().deleteFont("test");
	}
}