#include "DxLib.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "TitleScene.h"

c_SceneManager::c_SceneManager() : mScene(new c_Title())
{
}

c_SceneManager::~c_SceneManager() {
	delete mScene;
}

void c_SceneManager::f_update() {
	c_Scene* p = mScene->f_update();
	if (p != mScene) {
		//delete mScene;
		mScene = p;
	}
}

void c_SceneManager::f_output() const {
	mScene->f_output();
}