#pragma once

#include "DxLib.h"

#include "DrawCube.h"
#include "Player.h"
#include "CameraCon.h"
#include "DispUI.h"
#include "Stage.h"
#include "Collision.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "Controller.h"
#include "MainUI.h"
#include "LoadSound.h"

#include <iostream>


extern VECTOR Playerposition;

class c_GameManager
{
public:
	void f_init();				//ƒQ[ƒ€‚Ì‰Šú‰»
	void f_RoadModel();			//ƒ‚ƒfƒ‹‚Ì“Ç‚İ
	void f_RoadImage();         //‰æ‘œ‚Ì“Ç‚İ‚İ
	void f_update();			//ƒtƒŒ[ƒ€‚²‚Æ‚Ìˆ—
	void f_output();			//ƒtƒŒ[ƒ€‚²‚Æ‚Ì•`‰æ

	void f_SkyBoxDraw();			//”wŒi‚Ì•`‰æ

	bool f_HitCheck(c_Collision col1,c_Collision col2);			//Õ“Ë”»’è

	c_DrawCube* c_Dc;
	c_Player* c_player;
	c_CameraCon* c_camera;
	c_DispUI* c_dispUI;
	c_Stage* c_stage;
	c_Hair* c_hair;
	c_Acne* c_acne;
	c_GamePad* c_pad;
	c_MainUI* c_mainUI;

private:
	
	// ƒ‚ƒfƒ‹
	int model_impostor;
	int model_Plane;
	int model_Sphere;
	int model_Cylinder;
	int model_Arm;
	int model_SkyBox;
	int model_Acne;
	int model_Bandage;

	// ‰æ‘œ
	int image_Cylinder;
	int image_Acne;
	int image_Bansoko;
};