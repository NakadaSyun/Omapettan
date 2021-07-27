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

void c_Collision::f_update() {


	CubeDraw();
}

void c_Collision::CubeDraw() {
	Cube.f_create(pos.x, pos.y, pos.z, wide + (wide / 2), hight, depth);
}