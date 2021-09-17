//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"
#include <stdlib.h>

#define PI 3.141592653589793

extern Sound g_Snd;
static int SoundFlg = 0;

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 760.0f, 4500.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);
	p_OldPosition = p_Position;

	IsAcneHit = false; 
	IsMove = true;

    c_colision = new c_Collision(VGet(sinf(p_Rotation.y) * -DISTANCE_TO_COLLISION_DETECTION + p_Position.x,
		                              p_Position.y,
		                              cosf(p_Rotation.y) * -DISTANCE_TO_COLLISION_DETECTION + p_Position.z),
		                              KAMISORI_SIZE.x, KAMISORI_SIZE.y, KAMISORI_SIZE.z);



	c_cameracon = new c_CameraCon;
	c_pad = new c_GamePad();

	model_Arm = MV1LoadModel("models/arm4.mv1");
	model_KAMISORI = MV1LoadModel("models/KKAMISORI_02.mv1");
	model_Acne = MV1LoadModel("models/dekimono.mv1");

	SoundFlg = 0;		//最初の剃刀の音を鳴らすフラグ
	MV1AttachAnim(p_Model, 1);
	TotalAnimTime = MV1GetAttachAnimTotalTime(p_Model, 0);
	image_PTexture = LoadGraph("images/Ch18_1001_Diffuse.png");
}

c_Player::~c_Player() {
	delete c_cameracon;
	delete c_colision;
	delete c_pad;
}

void c_Player::f_init() {
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);


	MV1SetPosition(model_KAMISORI, VGet(p_Position.x, p_Position.y, p_Position.z));


}

void c_Player::f_update(bool Isfall) {
	if (!IsMove) return;
	c_pad->f_update();

	if (SoundFlg == 0) {
		PlaySoundMem(g_Snd.KAMISORI_Hold, DX_PLAYTYPE_BACK);
		SoundFlg++;
	}

	AnimSet();


	// キャラに新しい座標をセット
	MV1SetPosition(p_Model, p_Position);
	// キャラに新しい回転値をセット
	MV1SetRotationXYZ(p_Model, p_Rotation);

	//剃刀のモデルに座標、回転値、コリジョンの設定
	MV1SetRotationXYZ(model_KAMISORI, VGet(p_Rotation.x, p_Rotation.y + PI, p_Rotation.z));

	static float cameraAdd_X = 0.0;
	static float cameraAdd_Z = 0.0;

	// カメラの位置と回転値をセット、カメラの位置は原点
	//SetCameraPositionAndTarget_UpVecY(VGet(0.0, sinf(cameraAdd_X++),cosf(0.0)), Playerposition);


	/**************************************
	*プレイヤーの移動処理
	**************************************/

	float MoveX = 0, MoveZ = 0;//プレイヤーの移動量
	Arm_XRotate = 0.0f;


	static float Rota_Vec = 0;		//Rotate_Vectol：：キャラが入力されたキーに対して向くべき方向
	static int int_angle = 0;			//Rotate_Vectolをラジアン角度に直したint型整数
	static float rad = PI / 180;		//ラジアンでの1°  rad * 180 =　PI
	static int Rota_Dif = 0;			//Rotate_Difference：：現在の回転値と向きたい方向の　時計廻り角度の差分格納変数
	static int NowRota = 0;				//Now_Rotate：：現在の向いているラジアン角度

	bool MoveKeyFlag = false;	//移動キーが一つでも押されているかのフラグ
	if (c_pad->LeftStick != 0) MoveKeyFlag = true;		//スティックがどこかに傾いていたらtrue


	/*****	コントローラーの入力	*****/
	if (c_pad->LeftStick == UP||
		c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == LEFTUP ) {
		if (c_pad->IsButton2 == TRUE) MoveZ = p_Speed * p_SpeedMagnification;
		else {
			MoveZ = p_Speed;
		}
	}

	if (c_pad->LeftStick == LEFTUP ||
		c_pad->LeftStick == LEFT ||
		c_pad->LeftStick == LEFTDOWN) {
		if (c_pad->IsButton2 == TRUE) MoveX = -p_Speed * p_SpeedMagnification;
		else {
			MoveX = -p_Speed;
		}
	}
	if (c_pad->LeftStick == DOWN ||
		c_pad->LeftStick == RIGHTDOWN ||
		c_pad->LeftStick == LEFTDOWN) {
		if (c_pad->IsButton2 == TRUE) MoveZ = -p_Speed * p_SpeedMagnification;
		else {
			MoveZ = -p_Speed;
		}
	}
	if (c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == RIGHT ||
		c_pad->LeftStick == RIGHTDOWN) {
		if (c_pad->IsButton2 == TRUE) MoveX = p_Speed * p_SpeedMagnification;
		else {
			MoveX = p_Speed;
		}
	}

	Rota_Vec = atan2(-MoveX, -MoveZ);			//プレイヤーの向く方向
	if (Rota_Vec < 0) {								//プレイヤーの向くべき方向が-3.14など反時計廻りに回るときに-の値になった時
		Rota_Vec = PI + (PI + Rota_Vec);			//2PIで一周換算した値にする
	}

	int_angle = Rota_Vec / rad;						//向くべき方向をラジアン角度に変換

	if (p_Rotation.y < 0) {							//プレイヤーの向いている方向が-3.14など反時計廻りに回るときに-の値になった時
		p_Rotation.y = PI + (PI + p_Rotation.y);	//2PIで一周換算した値にする
	}

	NowRota = abs(p_Rotation.y) / rad;				//現在の向いているラジアン角度

	if (int_angle == 0 && NowRota > 180) {
		int_angle = 360;
	}
	if (int_angle > 180 && NowRota == 0) {
		NowRota = 360;
	}	
	Rota_Dif = int_angle - NowRota;			//向きたい角度　ー　現在の角度 の差分
	Rota_Dif = abs(Rota_Dif);				//上記の値の差分の絶対値

	Rota_Dif = Rota_Dif % 360;				//差分が360°以上行かないようにする

	if (MoveKeyFlag == TRUE) {				//移動キーが押されている時
		if ((CheckSoundMem(g_Snd.Player_footStep) == 0) && (c_pad->IsButton2 == FALSE)){
			PlaySoundMem(g_Snd.Player_footStep, DX_PLAYTYPE_BACK);
		}
		if ((CheckSoundMem(g_Snd.Player_footStep_DS) == 0) && (c_pad->IsButton2 == TRUE)){
			PlaySoundMem(g_Snd.Player_footStep_DS, DX_PLAYTYPE_BACK);
		}
		
		//現在の角度から向きたい方向に向く処理
		if (int_angle > NowRota) {			//現在の角度と、向きべき角度を比べる
			if (Rota_Dif <= 180) {			//差分を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y += rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
			if (Rota_Dif > 180) {			//現在の角度と、向くべき角度を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y -= rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
		}
		if (int_angle < NowRota) {			//現在の角度と、向きべき角度を比べる
			if (Rota_Dif <= 180) {			//差分を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y -= rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
			if (Rota_Dif > 180) {			//差分を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y += rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
		}
	}

	//現在の角度が初期位置と同じなった時、値が超過しないように値を初期値にする
	if (NowRota == 360 && Rota_Dif == 0 && int_angle == 360) {		
		p_Rotation.y = 0.0f;
	}

	//かみそりの位置、角度をプレイヤーとの位置と角度に準拠させる
	MV1SetPosition(model_KAMISORI, VGet(
		sinf(p_Rotation.y) * +100 + p_Position.x,
		p_Position.y,
		cosf(p_Rotation.y) * +100 + p_Position.z
	));

	p_Position = VAdd(p_Position, VGet(0, 0, MoveZ));	//プレイヤーの座標加減算処理


	if (p_Position.z > 8000) {						//キャラが腕ステージ内での移動制限//腕の手首より上には行けない
		p_Position.z = 8000;
	}
	if (p_Position.z < 4500) {						//キャラが腕ステージ内での移動制限//肘手前より下には行けない
		p_Position.z = 4500;
	}

	c_colision->f_update(VGet(sinf(p_Rotation.y) * +DISTANCE_TO_COLLISION_DETECTION + p_Position.x,
		                      p_Position.y,
		                      cosf(p_Rotation.y) * +DISTANCE_TO_COLLISION_DETECTION + p_Position.z));

	if (IsAcneHit) {			//吹き出物と衝突していたら一フレーム前の座標に戻す
		p_Position = VGet(p_OldPosition.x,
						p_Position.y,
						cosf(p_Rotation.y) * 100 + p_OldPosition.z);
	}
	else {
		p_OldPosition = p_Position;
	}
	IsAcneHit = false;
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {

	static int Skin1 = MV1GetMaterialDifMapTexture(p_Model, 0);
	//マテリアルで使用されているテクスチャの番号を取得
	static int Skin2 = MV1GetMaterialDifMapTexture(p_Model, 2);

	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(p_Model, Skin1, image_PTexture, FALSE);
	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(p_Model, Skin2, image_PTexture, FALSE);

	// ３Ｄモデルの描画
	MV1DrawModel(p_Model);

	MV1DrawModel(model_KAMISORI);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

float c_Player::f_GetPlayerRotationY() {
	return p_Rotation.y;
}

bool c_Player::f_PlayerDebug(bool DebugFlg,bool speedFlg) {
	/*if (DebugFlg)
	{
		p_SpeedMagnification = 5;
		return true;
	}
	else {
		p_SpeedMagnification = 2;
		return false;
	}*/
	if (!speedFlg)
	{
		p_SpeedMagnification = 5;
		return true;
	}
	else {
		p_SpeedMagnification = 2;
		return false;
	}
}

void c_Player::AnimSet() {

	static float NowAnimTime = 0.0f;
	if (c_pad->LeftStick != NONE && IsMove) {
		if (c_pad->IsButton2 == TRUE) NowAnimTime += 1.0f * p_SpeedMagnification;
		else  NowAnimTime += 1.0f;
	}
	if (NowAnimTime > TotalAnimTime) {
		NowAnimTime = 0.0f;
	}
	MV1SetAttachAnimTime(p_Model, 0, NowAnimTime);
}