#include "game_core.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetAlwaysRunFlag(TRUE);					// ウィンドウが非アクティブ状態のときも処理を続行する
	SetOutApplicationLogValidFlag(FALSE);	// Log.txtを生成しないように設定
	SetMainWindowText("Grid Slash Girl");	// タイトルを設定
	ChangeWindowMode(TRUE);					// ウィンドウモードに設定
	SetGraphMode(800, 640, 32);				// 画面サイズ指定

	if (DxLib_Init() == -1) return -1;		// DXライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);			// 描画先を裏画面にする

	game::GameCore gameCore;				// ゲームを作成する
	gameCore.loop();						// ゲームのメインループを開始する

	DxLib_End();							// DXライブラリ終了処理
	return 0;
}