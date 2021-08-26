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

void c_Collision::CubeDraw() {
	Cube.f_create(pos.x - (wide / 2), pos.y, pos.z - (depth / 2), wide , hight, depth);
}