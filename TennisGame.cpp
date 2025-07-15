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

	// �Q�[���i�s�Ɋւ���ϐ��A�X�R�A��������ϐ�
	enum { TITLE, PLAY, OVER };
	int scene = TITLE;
	int timer = 0;
	int score = 0; // �X�R�A����
	int highScore = 1000; // �n�C�X�R�A����
	int dx, dy; // �q�b�g�`�F�b�N�p�̕ϐ��錾

	while (1) // ���C�����[�v
	{
		ClearDrawScreen(); // ��ʂ��N���A����
		timer++;

		switch (scene)
		{
		case TITLE: // �^�C�g����ʂ̏���
			SetFontSize(50);
			DrawString(WIDTH / 2 - 50 / 2 * 12 / 2, HEIGHT / 3, "Tennis Game", 0x00ff00);
			if (timer % 60 < 30) { //������_�ŕ\��
				SetFontSize(30);
				DrawString(WIDTH / 2 - 30 / 2 * 21 / 2, HEIGHT * 2 / 3, "Press SPACE to start", 0x00ffff);
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == 1) // �X�y�[�X�L�[��������
			{
				ballX = 40;
				ballY = 80;
				ballVx = 5;
				ballVy = 5;
				racketX = WIDTH / 2;
				racketY = HEIGHT - 50;
				score = 0;
				scene = PLAY;
			}
			break;

		case PLAY: // �Q�[�����v���C���鏈��
			// �{�[���̏���
			ballX = ballX + ballVx;
			if (ballX < ballR && ballVx < 0) ballVx = -ballVx;
			if (ballX > WIDTH - ballR && ballVx > 0) ballVx = -ballVx;
			ballY = ballY + ballVy;
			if (ballY < ballR && ballVy < 0) ballVy = -ballVy;
			// if (ballY > HEIGHT - ballR && ballVy > 0) ballVy = -ballVy;
			if (ballY > HEIGHT) // �{�[�������[�ɒB������
			{
				scene = OVER;
				timer = 0;
				break;
			}
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
			dx = ballX - racketX; // x�������̋���
			dy = ballY - racketY; // y�������̋���
			if (-racketW / 2 - 10 < dx && dx < racketW / 2 + 10 && -20 < dy && dy < 0)
			{
				ballVy = -5 - rand() % 5;
				score = score + 100;
				if (score > highScore) highScore = score; // �n�C�X�R�A�̍X�V
			}
			break;

		case OVER: // �Q�[���I�[�o�[�̏���
			SetFontSize(40);
			DrawString(WIDTH / 2 - 40 / 2 * 9 /2, HEIGHT / 3, "GAME OVER", 0xff0000);
			if (timer > 60 * 5) scene = TITLE;
			break;
		}

		SetFontSize(30); // �X�R�A�ƃn�C�X�R�A�̕����̑傫��
		DrawFormatString(10, 10, 0xffffff, "SCORE %d", score);
		DrawFormatString(WIDTH - 200, 10, 0xffff00, "HI-Sc %d", highScore);
				
		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f������
		WaitTimer(16); // ��莞�ԑ҂�
		if (ProcessMessage() == -1) break; // Windows��������󂯎��G���[���N������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESC�L�[�������ꂽ��I��
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������
	return 0; // �\�t�g�I��
}