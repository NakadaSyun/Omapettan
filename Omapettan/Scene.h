#pragma once
#include "Dxlib.h"

class c_Scene {
protected:
	//コンストラクタ
	c_Scene() {}

public:
	//コピー禁止
	c_Scene(const c_Scene&) = delete;
	//コピー禁止
	c_Scene& operator=(const c_Scene&) = delete;

	//仮想関数化したデストラクタ
	virtual ~c_Scene() = default;

	virtual c_Scene* f_update() = 0;
	virtual void f_output() const = 0;
	virtual void f_fadeout() = 0;		//暗転する
	virtual void f_fadein() = 0;		//明るくする

	bool IsNextScene;
};

namespace {
	enum SCENE_STATUS {
		FADE_IN,        // フェードイン
		IDOL,           // 待機
		FADE_OUT,       // フェードアウト
		NEXT_SCENE,		//次のシーンへ
	};
}


//列挙体型の現在のゲームモード
enum GAME_MODE {		
	GAME_TITLE,
	GAME_MAIN,
	GAME_RESULT,
	GAME_OVER,
	GAME_END,
	END = 99
};
