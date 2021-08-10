#include "DxLib.h"
#include "SceneManager.h"


/**********************************/
enum class SceneType
{
	Title,
	Main,
	Result,
};
/**********************************/

c_sceneManager::c_sceneManager() {
	c_title = new c_Title();
	c_main = new c_Main();
	c_result = new c_Result();

	selectScene = (int)SceneType::Main;
}

void c_sceneManager::f_update() {

	switch (selectScene)
	{
	case (int)SceneType::Title:
		c_title->f_update();
		break;

	case (int)SceneType::Main:
		c_main->f_update();
		break;

	case (int)SceneType::Result:
		c_result->f_update();
		break;

	default:
		break;
	}
}

void c_sceneManager::f_output(){
	switch (selectScene)
	{
	case (int)SceneType::Title:
		c_title->f_output();
		break;

	case (int)SceneType::Main:
		c_main->f_output();
		break;

	case (int)SceneType::Result:
		c_result->f_output();
		break;

	default:
		break;
	}
}

void c_sceneManager::f_NextScene() {

}