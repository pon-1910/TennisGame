#include "DxLib.h"
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�萔�̒�`
	const int WIDTH = 960, HEIGHT = 640; //�@�E�B���h�E�̕��ƍ����̃s�N�Z��

	SetWindowText("�e�j�X�Q�[��"); // �E�B���h�E�̃^�C�g��
	SetGraphMode(WIDTH, HEIGHT, 32); // �E�B���h�E�̑傫���ƃJ���[�r�b�g�����w��
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ŋN��
	if (DxLib_Init() == -1) return -1; //���C�u�����̏������@�G���[���N������I��
	SetBackgroundColor(0, 0, 0); // �w�i�F�̎w��
	SetDrawScreen(DX_SCREEN_BACK); // �`��ʂ𗠉�ʂɐݒ肷��

	// �{�[���𓮂������߂̕ϐ�
	int ballX = 40;
	int ballY = 80;
	int ballVx = 5;
	int ballVy = 5;
	int ballR = 10;

	// ���P�b�g�𓮂������߂̕ϐ�
	int racketX = WIDTH / 2;
	int racketY = HEIGHT - 50;
	int racketW = 120;
	int racketH = 12;

	while (1) // ���C�����[�v
	{
		ClearDrawScreen(); // ��ʂ��N���A����
		// �{�[���̏���
		ballX = ballX + ballVx;
		if (ballX < ballR && ballVx < 0) ballVx = -ballVx;
		if (ballX > WIDTH - ballR && ballVx > 0) ballVx = -ballVx;
		ballY = ballY + ballVy;
		if (ballY < ballR && ballVy < 0) ballVy = -ballVy;
		if (ballY > HEIGHT - ballR && ballVy > 0) ballVy = -ballVy;
		DrawCircle(ballX, ballY, ballR, 0xff0000, TRUE); // �{�[��

		// ���P�b�g�̏���
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) // ���L�[��������
		{
			racketX = racketX - 10;
			if (racketX < racketW / 2) racketX = racketW / 2;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) // �E�L�[��������
		{
			racketX = racketX + 10;
			if (racketX > WIDTH - racketW / 2) racketX = WIDTH - racketW / 2;
		}
		DrawBox(racketX - racketW / 2, racketY - racketH / 2, racketX + racketW / 2, racketY + racketH / 2, 0x0080ff, TRUE); //���P�b�g

		// �q�b�g�`�F�b�N
		int dx = ballX - racketX; // x�������̋���
		int dy = ballY - racketY; // y�������̋���
		if (-racketW / 2 - 10 < dx && dx < racketW / 2 + 10 && -20 < dy && dy < 0) ballVy = -5 - rand() % 5;
				
		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f������
		WaitTimer(16); // ��莞�ԑ҂�
		if (ProcessMessage() == -1) break; // Windows��������󂯎��G���[���N������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESC�L�[�������ꂽ��I��
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������
	return 0; // �\�t�g�I��
}