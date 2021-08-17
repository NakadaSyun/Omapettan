#include "DxLib.h"
#include "DrawAcne.h"

c_Acne::c_Acne(const int Acne_Model,const int Acne_Graph) {
	modelacne = Acne_Model;
	graphacne = Acne_Graph;

	stageRotation = 0.0f;

	MV1SetDifColorScale(modelacne, GetColorF(0.9f, 0.5f, 0.5f, 1.0f));
	MV1SetTextureGraphHandle(modelacne,100,graphacne,FALSE);
	MV1SetScale(modelacne, VGet(1.0f, 1.0f, 1.0f));
	MV1SetPosition(modelacne, VGet(0.0f, 760.0f, 4500.0f));
	MV1SetRotationXYZ(modelacne, VGet(0.0f, 0.0f, 0.0f));
}
void c_Acne::f_init() {

}

void c_Acne::f_output() {
	MV1DrawModel(modelacne);
}
void c_Acne::f_update() {
	MV1SetPosition(modelacne, VGet(cosf(0.0f - stageRotation) * 750,
								   sinf(0.0f - stageRotation) * 750,
		                                4000.0f  + 750));
}