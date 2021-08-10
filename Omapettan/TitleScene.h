#pragma once

#include "Dxlib.h"
#include "Scene.h"

class c_Title : public c_Scene {
public:
	c_Title();
	~c_Title();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;


	void f_loadImage();

private:
	int BG;
};