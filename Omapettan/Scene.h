#pragma once
#include "Dxlib.h"

class c_Scene {
protected:
	//�R���X�g���N�^
	c_Scene() {}

public:
	//�R�s�[�֎~
	c_Scene(const c_Scene&) = delete;
	//�R�s�[�֎~
	c_Scene& operator=(const c_Scene&) = delete;

	//���z�֐��������f�X�g���N�^
	virtual ~c_Scene() = default;

	virtual c_Scene* f_update() = 0;
	virtual void f_output() const = 0;

	bool IsNextScene;
};