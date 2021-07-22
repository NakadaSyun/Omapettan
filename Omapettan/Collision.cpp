#include "Collision.h"

c_Collision::c_Collision(VECTOR position, float w, float h, float d) {
	pos = position;
	
	wide = w;
	hight = h;
	depth = d;
}

bool c_Collision::f_Hit(c_Collision Col) {



}

void c_Collision::CubeDraw() {
	Cube.f_create(pos.x, pos.y, pos.z, wide, hight, depth);
}