#ifndef game_manager_h
#define game_manager_h

#include "utils/singleton.h"
#include "DxLib.h"

namespace game
{
	class GameManager : public Singleton<GameManager>
	{
		friend class Singleton<GameManager>; // Singleton でのインスタンス作成は許可

	private:
		GameManager(); // 外部でのインスタンス作成は禁止
		~GameManager();
	};
}

#endif // !game_manager_h