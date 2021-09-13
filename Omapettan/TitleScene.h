#pragma once

#include "Dxlib.h"
#include "Scene.h"
#include "Controller.h"

class c_Title : public c_Scene {
public:
	c_Title();
	~c_Title();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;
	virtual void f_fadeout() override;		//�Ó]����
	virtual void f_fadein() override;			//���邭����

	void f_loadImage();

	void f_CheckSound();
	void f_SelectPoint();
	c_GamePad* c_Pad;

private:
	int BG;			//�w�i�摜�p�ϐ�
	int SceneSeq;	//�^�C�g���V�[���̏��	0:�t�F�[�h�C���@1:���͑҂��@2:�t�F�[�h�A�E�g
	int Brightness;
};