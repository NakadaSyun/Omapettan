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
};