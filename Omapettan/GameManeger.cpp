#include "DxLib.h"
#include "GameManeger.h"

VECTOR Playerposition;

// ������
void c_GameManeger::f_init()
{
	f_RoadModel();


	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(model_Plane, VGet(0.0f,-100.0f,0.0f));

	MV1SetPosition(model_Sphere, VGet(0.0f, -850.0f, 0.0f));			//����


	c_player = new c_Player(model_impostor);

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera = new c_CameraCon();

	c_dispUI = new c_DispUI();

}

void c_GameManeger::f_RoadModel()
{
	// �R�c���f���̓ǂݍ���
	model_impostor = MV1LoadModel("models/among us.mv1");
	model_Plane = MV1LoadModel("models/Plane.mv1");
	model_Sphere = MV1LoadModel("models/TestSphere.mv1");
	model_Cylinder = MV1LoadModel("models/cylinder.mv1");
}

// �Q�[���X�V
void c_GameManeger::f_update()
{
	c_player->f_update();

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera->f_update();
}

void c_GameManeger::f_output()
{
	//c_Dc->f_create(0, 0, 50, 640, 20, 250);

	//���̐���
	MV1DrawModel(model_Plane);
	//���̂̐���
	//MV1SetScale(model_Sphere, VGet(3.0f, 3.0f, 3.0f));
	//MV1DrawModel(model_Sphere);
	//for (int x = 0; x < 64; x++) {
	//	MV1SetPosition(model_Cylinder, VGet(0.0f + (x * 50), 0.0f, 0.0f));
	//	MV1DrawModel(model_Cylinder);
	//}
									//exe�t�@�C�����Ɛ���ɓ��삵�Ȃ��̂ň�U�R�����g��

	c_player->f_draw();
	c_dispUI->f_draw();
}

