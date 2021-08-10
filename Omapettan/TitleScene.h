#pragma once

#include "Dxlib.h"
#include "Scene.h"

class c_Title{
public:
	c_Title();
	virtual ~c_Title();
	void f_update();
	void f_output();

private:
	int a;
};