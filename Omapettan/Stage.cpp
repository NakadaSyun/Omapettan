#include "Stage.h"

c_Stage::c_Stage(const int Model) {
	sModel = Model;
	// ÇRÇcÉÇÉfÉãÇÃç¿ïWÇèâä˙âª
	position = VGet(0.0f, 0.0f, 0.0f);

	c_colision = new c_Collision(position, 2000.0f, -200.0f, 2000.0f);
}

void c_Stage::f_init() {

	// ÇRÇcÉÇÉfÉãÇÃç¿ïWÇèâä˙âª
	position = VGet(0.0f, 0.0f, 0.0f);


}

void c_Stage::f_update() {

}

void c_Stage::f_output() {

	c_colision->CubeDraw();
	//è∞ÇÃê∂ê¨
	MV1DrawModel(sModel);
}