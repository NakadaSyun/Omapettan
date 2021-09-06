#include "DxLib.h"
#include "DrawAcne.h"


#define PI 3.141592653589793

c_Acne::c_Acne(const int Acne_Model,const int Acne_Graph, const int Bandage_Model) {
	modelacne = Acne_Model;
	graphacne = Acne_Graph;
	modelBandage = Bandage_Model;

	stageRotation = 0.0f;

	MV1SetDifColorScale(modelacne, GetColorF(0.9f, 0.5f, 0.5f, 1.0f));
	MV1SetScale(modelacne, VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(modelacne, VGet(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < ACNE_NUM; i++) {
		acnepersonalPosZ[i] = 0.0f;
		acnepersonalPosZ[i] = ARM_ADJUST_POS_ACNE + (ACNE_PERSONAL_AREA * i) + ((i + 1) * ACNE_DISTANCE) + GetRand(ACNE_PERSONAL_AREA);
		if ((acnepersonalPosZ[i] > START_PLAYER_DISTANCE) && (acnepersonalPosZ[i] < PLAYER_POSITION)) acnepersonalPosZ[i] = acnepersonalPosZ[i] - 300;
		if ((acnepersonalPosZ[i] < END_PLAYER_DISTANCE) && (acnepersonalPosZ[i] > PLAYER_POSITION)) acnepersonalPosZ[i] = acnepersonalPosZ[i] + 300;

		acnepersonalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;

		//printf("\n%d\t%f", i, acnepersonalPosZ[i]);

		status[i] = 0;

		c_collision[i] = new c_Collision(position[i], 120.0f, 120.0f, 80.0f);
	}

	//c_collision = new c_Collision();
}

c_Acne::c_Acne(){

}
void c_Acne::f_init() {
	//for (int i = 0; i < ACNE_NUM; i++) {
	//	acnepersonalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;
	//	acnepersonalPosZ[i] = GetRand(ARM_LENGTH_ACNE);
		//printf("guys!%f\n", acnepersonalPosZ[i]);
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

		if (status[i] == 0) {
			MV1SetPosition(modelacne, position[i]);
			MV1SetRotationXYZ(modelacne, VGet(0.0f, 0.0f, acnepersonalRotation[i] - stageRotation - PI/2));
			MV1DrawModel(modelacne);
		}
		else {
			MV1SetPosition(modelBandage, position[i]);
			MV1SetRotationXYZ(modelBandage, VGet(0.0f, 0.0f, acnepersonalRotation[i] - stageRotation - PI / 2));
			MV1DrawModel(modelBandage);
		}
	}
}


bool c_Acne::AcneStatus() {
	for (int i = 0; i < ACNE_NUM; i++) {
		if (status[i] == 0) return false;
	}

	return true;		//‚·‚×‚ÄØ‚ç‚ê‚Ä‚¢‚½‚çtrue‚ð•Ô‚·
}