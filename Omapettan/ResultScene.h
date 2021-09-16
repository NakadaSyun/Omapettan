#pragma once
#include "Dxlib.h"
#include "Scene.h"
#include "Controller.h"

namespace {
	//��ї��̍ő哾�_
	float HairScore = 80.0f;
	//�����o���̔{��
	float AcneScore[5] = { 0, 1.1, 1.15, 1.2, 1.25 };
	//�ō��X�R�A
	float HighScore = 100.0f;
}

class c_Result : public c_Scene{
public:
	c_Result(float rate,int life);
	~c_Result();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;
	virtual void f_fadeout() override;		//�Ó]����
	virtual void f_fadein() override;			//���邭����


	void f_loadImage();

	c_GamePad* c_pad;
private:
	int BG;
	int Beginner;
	int Common;
	int Expert;
	int God;

	float rateData;
	float DrawRate;
	int SceneSeq;	//�^�C�g���V�[���̏��	0:�t�F�[�h�C���@1:���͑҂��@2:�t�F�[�h�A�E�g
	int Brightness;

	int PictImage[4];
	int ResType;

	int playerLife;
};