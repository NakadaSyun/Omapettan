#include "MainScene.h"
#include "ResultScene.h"

c_Main::c_Main() {
	//ゲームマネージャー生成
	c_gm = new c_GameManager();

	// ゲームマネジャ初期化
	c_gm->f_init();
	IsNextScene = false;

	//
	//StageClearImage = LoadGraph("images/Result.png");
	StageClearImage = LoadGraph("images/StageClear.png");
	
}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		//return new c_Result();
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		//IsNextScene = true;
	}

	//毛が全部剃られた状態ならResultシーンへ
	if (c_gm->c_hair->f_hairStatusSee()) {
		/*if (StageClearTime <240)
		{
			DrawGraph(0, 0, StageClearImage, true);
			StageClearTime++;
		}
		else
		{
			return new c_Result();
		}*/

		if (StageClearTime < 120)
		{
			StageClearTime++;
		}
		else if (StageClearTime < 240)
		{
			StageClearTime++;
			DrawGraph(0, 0, StageClearImage, true);
		}
		else
		{
			return new c_Result();
		}
	}

	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

