#ifndef game_manager_h
#define game_manager_h

#include "utils/singleton.h"
#include "DxLib.h"

namespace game
{
	class GameManager : public Singleton<GameManager>
	{
		friend class Singleton<GameManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		GameManager(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~GameManager();
	};
}

#endif // !game_manager_h