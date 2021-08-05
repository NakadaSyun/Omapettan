#include "Stage.h"

#define PI 3.141592653589793

c_Stage::c_Stage(const int Model) {
	sModel = Model;
	// ‚R‚cƒ‚ƒfƒ‹‚ÌÀ•W‚ğ‰Šú‰»
	position = VGet(0.0f, 0.0f, 0.0f);

	MV1SetRotationXYZ(sModel, VGet(0.0f, PI / 2, 0.0f));

	c_colision = new c_Collision(position, 2000.0f, -200.0f, 2000.0f);
}

void c_Stage::f_init() {

	// ‚R‚cƒ‚ƒfƒ‹‚ÌÀ•W‚ğ‰Šú‰»
	position = VGet(0.0f, 0.0f, 0.0f);


}

void c_Stage::f_update() {

	static float Arm_XRotate = 0.0f;

	if (CheckHitKey(KEY_INPUT_A) == 1) {
		Arm_XRotate += 0.01f;
	}

	if (CheckHitKey(KEY_INPUT_D) == 1) {
		Arm_XRotate -= 0.01f;
	}

	MV1SetRotationXYZ(sModel, VGet(Arm_XRotate, PI / 2, 0.0f));
}

void c_Stage::f_output() {

	//°‚Ì¶¬
	MV1DrawModel(sModel);
}