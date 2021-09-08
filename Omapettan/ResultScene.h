#pragma once
#include "Dxlib.h"
#include "Scene.h"
#include "Controller.h"

class c_Result : public c_Scene{
public:
	c_Result(float rate);
	~c_Result();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;


	void f_loadImage();

	c_GamePad* c_pad;
private:
	int BG;
	int Beginner;
	int Common;
	int Expert;
	int God;

	float rateData;
};