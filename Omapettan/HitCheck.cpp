#include "HitCheck.h"


// �Փ˔���
// �������Ă����true��Ԃ��A�������Ă��Ȃ����false��Ԃ�
bool c_HitCheck::f_playerAndObjects(c_Collision col1, c_Collision col2) {
	VECTOR Cubevertex1[8];        //�l�p�`�̒��_8
	VECTOR Cubevertex2[8];        //�l�p�`�̒��_8
	HITRESULT_LINE result;        // ���ʂ��i�[


	//���_���W�̐ݒ�
	Cubevertex1[0] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y, col1.pos.z - (col1.depth / 2));																			//
	Cubevertex1[1] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y, col1.pos.z - (col1.depth / 2));
	Cubevertex1[2] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z - (col1.depth / 2));
	Cubevertex1[3] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z - (col1.depth / 2));
	Cubevertex1[4] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y, col1.pos.z + (col1.depth / 2));
	Cubevertex1[5] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y, col1.pos.z + (col1.depth / 2));
	Cubevertex1[6] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));
	Cubevertex1[7] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));

	Cubevertex2[0] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y, col2.pos.z - (col2.depth / 2));
	Cubevertex2[1] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y, col2.pos.z - (col2.depth / 2));
	Cubevertex2[2] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z - (col2.depth / 2));
	Cubevertex2[3] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z - (col2.depth / 2));
	Cubevertex2[4] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y, col2.pos.z + (col2.depth / 2));
	Cubevertex2[5] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y, col2.pos.z + (col2.depth / 2));
	Cubevertex2[6] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z + (col2.depth / 2));
	Cubevertex2[7] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z + (col2.depth / 2));
	

	result = HitCheck_Line_Triangle(Cubevertex1[0], Cubevertex1[2], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[1], Cubevertex1[3], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[4], Cubevertex1[6], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[5], Cubevertex1[7], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[0], Cubevertex1[2], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[1], Cubevertex1[3], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[4], Cubevertex1[6], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[5], Cubevertex1[7], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	/*if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[1], Cubevertex1[2], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return true;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[4], Cubevertex1[6], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return true;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[4], Cubevertex1[5], Cubevertex1[7], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return true;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[1], Cubevertex1[5], Cubevertex1[3], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return true;
	}


	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[1], Cubevertex1[2], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return true;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[4], Cubevertex1[6], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return true;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[4], Cubevertex1[5], Cubevertex1[7], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return true;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[1], Cubevertex1[5], Cubevertex1[3], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return true;
	}*/
	return false;
}