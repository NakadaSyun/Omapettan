//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"

#define PI 3.141592653589793

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 760.0f, 4500.0f);
	p_Rotation = VGet(0.0f, PI, 0.0f);

	c_colision = new c_Collision(p_Position, 100.0f, 200.0f, 100.0f);

	c_cameracon = new c_CameraCon;

	model_Arm = MV1LoadModel("models/arm2.mv1");
}

void c_Player::f_init() {
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(bool Isfall) {

	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(p_Model, p_Position);
	// �R�c���f���ɐV������]�l���Z�b�g
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameracon���Ă�Œl���X�V

	StartPos = p_Position;
	EndPos = VGet(p_Position.x , p_Position.y + 250.0f,p_Position.z);

	MV1SetPosition(model_Arm, VGet(0.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(model_Arm,VGet(0.0f,PI/2,0.0f));
	MV1SetupCollInfo(model_Arm, -1, 8, 8, 8);		//���f���S�̂̃t���[���ɃR���W����������

	DrawLine3D(StartPos, EndPos, GetColor(255, 0, 0));		//�L�����̓����蔻��̐���

	MV1_COLL_RESULT_POLY HitPoly = MV1CollCheck_Line(model_Arm,-1, StartPos, EndPos);

	VECTOR Pos0= HitPoly.Position[0],
		   Pos1 = HitPoly.Position[1],
		   Pos2 = HitPoly.Position[2];
	int LineColor = GetColor(255,0,0);

	DrawLine3D(Pos0, Pos1, LineColor);
	DrawLine3D(Pos1, Pos2, LineColor);
	DrawLine3D(Pos2, Pos0, LineColor);

	//���[���h���m�F
	DrawLine3D(p_Position, VGet(p_Position.x + 200, p_Position.y, p_Position.z), GetColor(255,0,0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y + 200, p_Position.z), GetColor(0, 255, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y, p_Position.z + 200), GetColor(0, 0, 255));

	//p_Rotation = HitPoly.Normal;		//�@���̃L�����̌����ɑ��

	if (HitPoly.HitFlag == 1) {
		p_Rotation = VGet(HitPoly.Normal.x, p_Rotation.y, HitPoly.Normal.z); 		//�@���̃L�����̌����ɑ��
	}

	DrawFormatString(0, 200, GetColor(255, 255, 255), "Pos0.x:%f��", HitPoly.Position[0].x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Pos0.y:%f��", HitPoly.Position[0].y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Pos0.z:%f��", HitPoly.Position[0].z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));		//�|���S���̖@���`��

	float MoveX = 0,MoveZ = 0;//�v���C���[�̈ړ���
	Arm_XRotate = 0.0f;

	if (CheckHitKey(KEY_INPUT_W) == 1) {
	    MoveZ = p_Speed;
	    p_Rotation.y = PI;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
	    p_Rotation.y = PI/2;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
	    MoveZ = -p_Speed;
	    p_Rotation.y = 0;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
	    p_Rotation.y = -PI / 2;
	}


	//if (MoveZ != 0 && MoveX != 0 ) {
	//    p_Rotation.y = atan2(-MoveX,-MoveZ);
	//}

	p_Position = VAdd(p_Position,VGet(MoveX,0,MoveZ));
	if (p_Position.z > 8000) {
		p_Position.z = 8000;
	}
	if (p_Position.z < 1000) {
		p_Position.z = 1000;
	}



	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		p_Position.y += 10;
	}

	DrawFormatString(0, 100, 0xffffff, "p_Position.x %f", p_Position.x);
	DrawFormatString(0, 120, 0xffffff, "p_Position.z %f", p_Position.z);
	DrawFormatString(0, 140, 0xffffff, "p_Rotation.y %f", p_Rotation.y);

	if (HitPoly.HitFlag == 0)f_fall();		//�d��
	c_colision->f_update(p_Position);
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {
	c_colision->CubeDraw();
	// �R�c���f���̕`��
	MV1DrawModel(p_Model);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

