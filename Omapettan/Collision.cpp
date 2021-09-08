#include "Collision.h"

c_Collision::c_Collision(VECTOR position, float w, float h, float d) {
	pos = position;
	
	wide = w;
	hight = h;
	depth = d;
}


bool c_Collision::f_Hit() {

	if (HitCheck_Triangle_Triangle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f))) {
		return true;
	}


	return false;
}

void c_Collision::f_update(VECTOR position) {
	pos = position;

	//CubeDraw();
}

void c_Collision::f_CubeDraw() {

	Cube.f_create(pos.x - (wide / 2), pos.y, pos.z - (depth / 2), wide , hight, depth);
}

void c_Collision::f_PolyDraw(float rot) {
	float radius = sqrtf(powf(wide / 2, 2.0) + powf(depth / 2, 2.0));    // �䓁�̌��_���瓖���蔻��̃|���S���̒��_�ւ̋���
	float angle = atan2(float(depth / 2), float(wide / 2)) * DX_PI;       // �䓁�̌��_���瓖���蔻��̃|���S���̒��_�ւ̊p�x
	VECTOR Cubevertex2_ver2[4];                                          // �l�p�`�̒��_8


	Cubevertex2_ver2[0] = VGet(pos.x + sinf(rot - angle) * radius, pos.y, pos.z + cosf(rot - angle) * radius);
	Cubevertex2_ver2[1] = VGet(pos.x + sinf(rot - (DX_PI - angle)) * radius, pos.y, pos.z + cosf(rot - (DX_PI - angle)) * radius);
	Cubevertex2_ver2[2] = VGet(pos.x + sinf(rot + (DX_PI - angle)) * radius, pos.y, pos.z + cosf(rot + (DX_PI - angle)) * radius);
	Cubevertex2_ver2[3] = VGet(pos.x + sinf(rot + angle) * radius, pos.y, pos.z + cosf(rot + angle) * radius);


	DrawTriangle3D(Cubevertex2_ver2[0], Cubevertex2_ver2[1], Cubevertex2_ver2[2], GetColor(255, 0, 0), true);
	DrawTriangle3D(Cubevertex2_ver2[0], Cubevertex2_ver2[2], Cubevertex2_ver2[3], GetColor(0, 0, 255), true);

}