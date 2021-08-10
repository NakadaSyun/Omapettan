
#pragma once
#include "DxLib.h"
#include "Scene.h"

class c_SceneManager {
public:
	c_SceneManager();
	~c_SceneManager();
private:
	c_Scene* mScene;

public:
	void f_update();
	void f_output() const;
};
