#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <math.h>

class c_HitCheck {
public:
	bool f_playerAndObjects(c_Collision col1, c_Collision col2, float rot);
private:
	//HITRESULT_LINE result;
};