#include "DxLib.h"
#include "Gamebase.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	GameBase gameBase;


	//�f�o�b�N�R���\�[���̕\��
	//AllocConsole();
	/*FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	printf("�f�o�b�N�R���\�[��\n");*/

	//�Q�[���̊��ݒ�
	if (gameBase.f_init() == false) {
		return -1;
	}

	//�Q�[�����[�v
	gameBase.f_loop();

	//�Q�[���I������
	gameBase.f_exit();

	// �\�t�g�̏I��
	return 0;
}