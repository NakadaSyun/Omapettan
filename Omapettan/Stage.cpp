#include "Stage.h"

c_Stage::c_Stage(const int Model) {
	sModel = Model;
	// ‚R‚cƒ‚ƒfƒ‹‚ÌÀ•W‚ğ‰Šú‰»
	position = VGet(0.0f, 0.0f, 0.0f);

	c_colision = new c_Collision(position, 2000.0f, -200.0f, 2000.0f);
}

void c_Stage::f_init() {

	// ‚R‚cƒ‚ƒfƒ‹‚ÌÀ•W‚ğ‰Šú‰»
	position = VGet(0.0f, 0.0f, 0.0f);


}

void c_Stage::f_update() {

}

void c_Stage::f_output() {

	//°‚Ì¶¬
	MV1DrawModel(sModel);
}