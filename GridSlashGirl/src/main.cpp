#include "game_core.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetAlwaysRunFlag(TRUE);					// �E�B���h�E����A�N�e�B�u��Ԃ̂Ƃ��������𑱍s����
	SetOutApplicationLogValidFlag(FALSE);	// Log.txt�𐶐����Ȃ��悤�ɐݒ�
	SetMainWindowText("Grid Slash Girl");	// �^�C�g����ݒ�
	ChangeWindowMode(TRUE);					// �E�B���h�E���[�h�ɐݒ�
	SetGraphMode(800, 640, 32);				// ��ʃT�C�Y�w��

	if (DxLib_Init() == -1) return -1;		// DX���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);			// �`���𗠉�ʂɂ���

	game::GameCore gameCore;				// �Q�[�����쐬����
	gameCore.loop();						// �Q�[���̃��C�����[�v���J�n����

	DxLib_End();							// DX���C�u�����I������
	return 0;
}