#include "Player.h"

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// �R�c���f���̍��W��������
	p_Position = VGet(320.0f, 10.0f, 150.0f);

}

void c_Player::f_init() {
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(){
	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(p_Model, p_Position);
}

void c_Player::f_draw() {
	// �R�c���f���̕`��
	MV1DrawModel(p_Model);
}