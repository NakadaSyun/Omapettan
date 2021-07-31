#include "Stage.h"

c_Stage::c_Stage(const int Model) {
	sModel = Model;
	// �R�c���f���̍��W��������
	position = VGet(0.0f, 0.0f, 0.0f);

	c_colision = new c_Collision(position, 2000.0f, -200.0f, 2000.0f);
}

void c_Stage::f_init() {

	// �R�c���f���̍��W��������
	position = VGet(0.0f, 0.0f, 0.0f);


}

void c_Stage::f_update() {

}

void c_Stage::f_output() {

	//�r�g��\��
	MV1SetScale(sModel, VGet(4.0f, 4.0f, 4.0f));

	//���̐���
	MV1DrawModel(sModel);
}