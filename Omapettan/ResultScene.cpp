#include "DxLib.h"
#include "ResultScene.h"
#include "TitleScene.h"


c_Result::c_Result() {

}

c_Result::~c_Result() {

}

c_Scene* c_Result::f_update() {
	if (false) {
		return new c_Title();
	}

	return this;
}

void c_Result::f_output() const {

}