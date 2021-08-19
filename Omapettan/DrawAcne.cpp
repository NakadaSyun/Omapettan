#include "DxLib.h"
#include "DrawAcne.h"

c_Acne::c_Acne(const int Acne_Model,const int Acne_Graph) {
	modelacne = Acne_Model;
	graphacne = Acne_Graph;

	stageRotation = 0.0f;

	MV1SetDifColorScale(modelacne, GetColorF(0.9f, 0.5f, 0.5f, 1.0f));
	MV1SetScale(modelacne, VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(modelacne, VGet(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < ACNE_NUM; i++) {
		acnepersonalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;
		acnepersonalPosZ[i] = GetRand(ARM_LENGTH_ACNE);
		printf("guys!%d\t%f\n",i, acnepersonalPosZ[i]);

		c_collision[i] = new c_Collision(position[i], 150.0f, 150.0f, 100.0f);
	}

	//c_collision = new c_Collision();
}
void c_Acne::f_init() {
	//for (int i = 0; i < ACNE_NUM; i++) {
	//	acnepersonalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;
	//	acnepersonalPosZ[i] = GetRand(ARM_LENGTH_ACNE);
	//	printf("guys!%f\n", acnepersonalPosZ[i]);
	//}
}

void c_Acne::f_update() {
	for (int i = 0; i < ACNE_NUM; i++) {
		position[i] = VGet(cosf(acnepersonalRotation[i] - stageRotation) * ARM_RADIUS_ACNE,
								sinf(acnepersonalRotation[i] - stageRotation) * ARM_RADIUS_ACNE,
									 acnepersonalPosZ[i] + ARM_ADJUST_POS_ACNE);

		c_collision[i]->f_update(position[i]);
	}
}

void c_Acne::f_output() {
	for (int i = 0; i < ACNE_NUM; i++) {
		MV1SetPosition(modelacne, position[i]);
		MV1DrawModel(modelacne);
	}
}