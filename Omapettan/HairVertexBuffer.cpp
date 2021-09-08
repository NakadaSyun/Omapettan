#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "LoadSound.h"

extern Sound g_Snd;

c_Hair::c_Hair(const int Model, const int Image) {
	//毛の当たり判定用の座標の初期化
	//毛の当たり判定用のフラグの初期化
	for (int num = 0; num < HAIR_NUM; num++)
	{
		CollisionPosition[num] = VGet(0.0f, 0.0f, 0.0f);
		HitHair[num] = true;
		hairStatus[num] = ROOTED_IS;
		personalRadius[num] = 0.0f;
		hairFlyingRotX[num] = 0.0f;
		hairFlyingRotZ[num] = 0.0f;
		hairFlyingVec[num] = 0.0f;
		playerRotY[num] = 0.0f;
		personalAnimTime[num] = 0.0f;
	}

	acnepersonalpos = new c_Acne();

	// モデルの代入
	modelHandle = Model;

	// 画像の代入
	graphHandle = Image;

	// メモリの割り当て
	f_allocateMemory();

	//毛のアニメーションを設定
	MV1AttachAnim(modelHandle, 0);
	AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle, 0);
	AnimNowTime = 0;

	// モデルの複製
	f_modelDuplication();

	stageXRotation = 0.0f;

	hairSize = VGet(40.0f, 40.0f, 40.0f);

	//f_funcList[ROOTED_IS] = f_moveHair();
	/*(this->*f_hairStatusFuncList[3])(0) =
	{ f_moveHair, f_flyShavedHair, f_MoveHairOffScreen };*/
}

void c_Hair::f_init() {

}


// 出力(描画)
void c_Hair::f_output() {
	// サイズの設定
	MV1SetScale(modelHandle, VGet(0.2f, 0.6f, 0.2f));
	// 頂点バッファで描画
	DrawPolygonIndexed3D_UseVertexBuffer(vertexBufHandle, indexBufHandle, graphHandle, TRUE);
}


// 更新
void c_Hair::f_update() {
	////ボックスコライダーの描画
	//CubeDraw();

	// 毛の移動
	f_hairUpdate();
}


// モデルの複製
void c_Hair::f_modelDuplication() {
	int vnum = 0;
	int pnum = 0;
	VECTOR debug;

	for (int i = 0; i < HAIR_NUM; i++) {

		MV1SetPosition(modelHandle, VGet(sinf(personalRotation[i]) * ARM_RADIUS,
			cosf(personalRotation[i]) * ARM_RADIUS,
			personalPosZ[i]));
		//モデルの座標を当たり判定用の変数にコピー
		CollisionPosition[i] = VGet(sinf(personalRotation[i]) * ARM_RADIUS,
			                        cosf(personalRotation[i]) * ARM_RADIUS,
			                        personalPosZ[i]);
		c_colision[i] =
			new c_Collision(CollisionPosition[i], hairSize.x, hairSize.y, hairSize.z);
		// Y軸回転
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, 0.0f, 0.0f));

		// 参照用メッシュの作成
		MV1SetupReferenceMesh(modelHandle, -1, TRUE);
		// 参照用メッシュの更新
		MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

		// 参照用メッシュの取得
		RefMesh = MV1GetReferenceMesh(modelHandle, -1, TRUE);
		// 頂点データをコピー
		for (int j = 0; j < RefMesh.VertexNum; j++)
		{
			vertex[j + vnum].pos = RefMesh.Vertexs[j].Position;
			vertex[j + vnum].norm = RefMesh.Vertexs[j].Normal;
			vertex[j + vnum].dif = RefMesh.Vertexs[j].DiffuseColor;
			vertex[j + vnum].spc = RefMesh.Vertexs[j].SpecularColor;
			vertex[j + vnum].u = RefMesh.Vertexs[j].TexCoord[0].u;
			vertex[j + vnum].v = RefMesh.Vertexs[j].TexCoord[0].v;
			vertex[j + vnum].su = RefMesh.Vertexs[j].TexCoord[1].u;
			vertex[j + vnum].sv = RefMesh.Vertexs[j].TexCoord[1].v;
		}

		// インデックスデータをコピー
		for (int j = 0; j < RefMesh.PolygonNum; j++)
		{
			index[j * 3 + 0 + pnum] = (WORD)RefMesh.Polygons[j].VIndex[0] + vnum;
			index[j * 3 + 1 + pnum] = (WORD)RefMesh.Polygons[j].VIndex[1] + vnum;
			index[j * 3 + 2 + pnum] = (WORD)RefMesh.Polygons[j].VIndex[2] + vnum;
		}
		vnum += RefMesh.VertexNum;
		pnum += RefMesh.PolygonNum * 3;

	}


	// 頂点データとインデックスデータを格納する頂点バッファとインデックスバッファを作成
	vertexBufHandle = CreateVertexBuffer(vertexNum, DX_VERTEX_TYPE_NORMAL_3D);
	indexBufHandle = CreateIndexBuffer(indexNum, DX_INDEX_TYPE_32BIT);

	// 頂点バッファとインデックスバッファにデータを転送
	SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	SetIndexBufferData(0, index, indexNum, indexBufHandle);

	//モデルの座標を返す
	//return position;

	////モデルのコピー
	//int D_ModelHandle[HAIR_NUM];
	//for (int x = 0; x < 8; x++) {
	//	for (int z = 0; z < 8; z++) {
	//		D_ModelHandle[x * 8 + z] = MV1DuplicateModel(modelHandle);
	//		// 画面に映る位置に３Ｄモデルを移動
	//		MV1SetPosition(D_ModelHandle[x * 8 + z], VGet(x * 100.0f, 0.0f, -z * 100.0f));
	//		// Y軸回転
	//		MV1SetRotationXYZ(D_ModelHandle[x * 8 + z], VGet(0.0f, 60.0f * DX_PI_F / 180.0f, 0.0f));
	//		// テクスチャ
	//		MV1SetTextureGraphHandle(D_ModelHandle[x * 8 + z], 0, graphHandle, TRUE);
	//	}
	//}
}


// メモリの割り当て
void c_Hair::f_allocateMemory() {
	// 参照用メッシュの作成
	MV1SetupReferenceMesh(modelHandle, -1, TRUE);
	// 参照用メッシュの取得
	RefMesh = MV1GetReferenceMesh(modelHandle, -1, TRUE);

	// 頂点の数とインデックスの数を取得
	indexNum = RefMesh.PolygonNum * POLY * HAIR_NUM;
	vertexNum = RefMesh.VertexNum * HAIR_NUM;

	// 頂点データとインデックスデータを格納するメモリ領域の確保
	vertex = (VERTEX3D*)malloc(sizeof(VERTEX3D) * vertexNum);
	index = (DWORD*)malloc(sizeof(DWORD) * indexNum);
}


void c_Hair::CubeDraw() {
	//コリジョンの位置調整用の数値
	for (int num = 0; num < HAIR_NUM; num++)
	{
		/*Cube.f_create(CollisionPosition[num].x - (200 / 2), CollisionPosition[num].y,
			CollisionPosition[num].z - (200 / 2),200, 600, 200);*/
		Cube.f_create(CollisionPosition[num].x - (hairSize.x / 2), CollisionPosition[num].y,
			CollisionPosition[num].z - (hairSize.z / 2), hairSize.x, hairSize.y, hairSize.z);
	}
}

// 毛の移動
void c_Hair::f_moveHair(int num) {

	int vnum = 0;
	int pnum = 0;


	//アニメーションの更新
	f_Animupdate(num);
	MV1SetPosition(modelHandle, VGet(sinf(personalRotation[num] + stageXRotation) * (ARM_RADIUS + personalRadius[num]) + hairFlyingVec[num],
		cosf(personalRotation[num] + stageXRotation) * (ARM_RADIUS + personalRadius[num]),
		personalPosZ[num]));
	//モデルの座標を当たり判定用の変数にコピー
	CollisionPosition[num] = VGet(sinf(personalRotation[num] + stageXRotation) * ARM_RADIUS + hairFlyingVec[num],
		                          cosf(personalRotation[num] + stageXRotation) * ARM_RADIUS,
		                          personalPosZ[num]);

	delete c_colision[num];
	c_colision[num] =
		new c_Collision(CollisionPosition[num], hairSize.x, hairSize.y, hairSize.z);
	
	// Y軸回転
	MV1SetRotationXYZ(modelHandle, VGet(hairFlyingRotX[num], 0, hairFlyingRotZ[num] - personalRotation[num] - stageXRotation));


	// 参照用メッシュの更新
	MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

	vnum = num * RefMesh.VertexNum;

	// 頂点データをコピー
	for (int j = 0; j < RefMesh.VertexNum; j++)
	{
		vertex[j + vnum].pos = RefMesh.Vertexs[j].Position;
	}

	/*vnum += RefMesh.VertexNum;
	pnum += RefMesh.PolygonNum * 3;*/

	//// 頂点バッファとインデックスバッファにデータを転送
	//SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	//SetIndexBufferData(0, index, indexNum, indexBufHandle);

}

// 毛の座標と角度を設定
void c_Hair::f_setPosAndRot() {

	// シード値設定
	//SRand(GetDateTime(&date));
	//float debug = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;

	for (int i = 0; i < HAIR_NUM; i++) {
		// 各毛の角度を設定
		personalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;
		//personalRotation[i] = debug;

		// 各毛のZ座標を設定
		personalPosZ[i] = GetRand(ARM_LENGTH) + ARM_ADJUST_POS;
	}
	for(int i = 0; i < HAIR_NUM; i++){
		if((acnepersonalpos->acnepersonalPosZ[0] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[0] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
			|| (acnepersonalpos->acnepersonalPosZ[1] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[1] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
			|| (acnepersonalpos->acnepersonalPosZ[2] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[2] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
			|| (acnepersonalpos->acnepersonalPosZ[3] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[3] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
			&& (CheckingOverlapsWithPlayer(personalRotation[i],personalPosZ[i]) == false)){
			for (int j = 1; j > 0;) {
				personalPosZ[i] = GetRand(ARM_LENGTH) + ARM_ADJUST_POS;
				if ((acnepersonalpos->acnepersonalPosZ[0] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[0] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
					|| (acnepersonalpos->acnepersonalPosZ[1] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[1] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
					|| (acnepersonalpos->acnepersonalPosZ[2] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[2] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
					|| (acnepersonalpos->acnepersonalPosZ[3] + HAIR_ADJUST_POS_ACNE < personalPosZ[i]) && (acnepersonalpos->acnepersonalPosZ[3] - HAIR_ADJUST_POS_ACNE > personalPosZ[i])
					&& (CheckingOverlapsWithPlayer(personalRotation[i], personalPosZ[i]) == false)) break;
			}
			personalAnimTime[i] = 148.0f - (148.0f * (personalPosZ[i] / 7000.0f));
		}
	}
}

// 毛を画面外へ移動
void c_Hair::f_MoveHairOffScreen(int num) {
	// 毛を画面に映らない位置へ移動
	personalPosZ[num] = -5000.0f;

	(this->*f_hairStatusFuncList[ROOTED_IS])(num);

	hairStatus[num] = DO_NOT_ANYTHING;
}

// 毛の状態を変化(根付いている→剃られた)
void c_Hair::f_hairCut(int num) {
	if (hairStatus[num] == ROOTED_IS) {
		hairStatus[num] = SHAVED;
		HitHair[num] = false;
		PlaySoundMem(g_Snd.HIGESORI_SE, DX_PLAYTYPE_BACK);
		//printf("num=%d status=%d\n", num,hairStatus[num]);
	}
}

// 剃られた毛を飛ばす
void c_Hair::f_flyShavedHair(int num) {
	// 毛の回転
	hairFlyingRotX[num] -= cosf(playerRotY[num]) / 20;
	hairFlyingRotZ[num] += sinf(playerRotY[num]) / 20;

	// 毛をプレイヤーの後ろ方向へ飛ばす
	personalRadius[num] += 9;
	hairFlyingVec[num] -= sinf(playerRotY[num]) * 20;
	personalPosZ[num] -= cosf(playerRotY[num]) * 20;

	(this->*f_hairStatusFuncList[ROOTED_IS])(num);

	if (personalRadius[num] >= 2000) {
		hairStatus[num] = OFF_SCREEN;
		numflg = true;
	}
}

// 何もしない
void c_Hair::f_doNotAnything(int num) {
	return;
}

// 毛の更新
void c_Hair::f_hairUpdate() {

	for (int i = 0/*, vnum = 0, pnum = 0*/; i < HAIR_NUM; i++) {
		(this->*f_hairStatusFuncList[hairStatus[i]])(i);
	}

	// 頂点バッファとインデックスバッファにデータを転送
	SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	SetIndexBufferData(0, index, indexNum, indexBufHandle);

	//
	if (numflg)
	{
		num = 0;
		for (int i = 0; i < HAIR_NUM; i++)
		{
			if (hairStatus[i] == OFF_SCREEN) {
				num++;
			}
		}
		//printf("%d\n",num);
		numflg = false;
	}

}

//毛の状態を見る
bool c_Hair::f_hairStatusSee() {
	//毛の状態を見て剃られてない毛があったらfalseを返す
	for (int i = 0; i < HAIR_NUM; i++)
	{
		if (hairStatus[i] == ROOTED_IS)
		{
			//printf("%d", hairStatus[0]);
			return false;
		}
	}

	//printf("gomi");
	//全部剃られてたらtrueを返す
	return true;
}

// プレイヤーのY軸の回転値を取得
void c_Hair::f_getRotationY(int num, float rot) {
	if (hairStatus[num] == ROOTED_IS) {
		playerRotY[num] = rot;
		playerRotY[num] -= DX_PI_F;
	}
}

void c_Hair::f_GetAcnePosZ(c_Acne* c_acne) {
	acnepersonalpos = c_acne;
	// 毛の座標と角度を設定
	f_setPosAndRot();
}

// プレイヤーとの重複の確認
bool c_Hair::CheckingOverlapsWithPlayer(float rot, float posZ) {
	// プレイヤーと重なっている部分があればtrue
	if (4100 < posZ && posZ < 4900)
		if (rot < DX_PI / 180 * 20 || DX_PI / 180 * 340 < rot)
			return true;

	// 重なっていなければfalse
	return false;
}

void c_Hair::f_Animupdate(int i) {
	personalAnimTime[i] += 1.0f * 2.0f;

	// アニメーション再生時間がアニメーションの総時間を越えていたらループさせる
	if (personalAnimTime[i] >= AnimTotalTime * (3.0f / 4.0f) * 2)
	{
		// 新しいアニメーション再生時間は、アニメーション再生時間からアニメーション総時間を引いたもの
		personalAnimTime[i] = 0;
	}

	float NowAnimTime = personalAnimTime[i];
	if (personalAnimTime[i] > AnimTotalTime* (3.0f / 4.0f)) {
		NowAnimTime = (AnimTotalTime * (3.0f / 4.0f)) - (personalAnimTime[i] - (AnimTotalTime * (3.0f / 4.0f)));
	}

	//if (i == 0)printf("Now = %f\tpersonal = %f\n", NowAnimTime, personalAnimTime[i]);
	MV1SetAttachAnimTime(modelHandle, 0, NowAnimTime);
}

void c_Hair::f_DebugHair(bool DebugFlg,bool HairShaved) {
	if (DebugFlg)
	{
		float debug = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;
		if (!HairShaved) {
			for (int i = 0; i < HAIR_NUM; i++)
			{
				if (hairStatus[i] == ROOTED_IS) {
					// 各毛の角度を設定
					personalRotation[i] = debug;

					// 各毛のZ座標を設定
					personalPosZ[i] = GetRand(ARM_LENGTH) + ARM_ADJUST_POS;
				}
			}
		}

		//毛を全て消す
		if (HairShaved)
		{
			for (int num = 0; num < HAIR_NUM; num++)
			{
				if (hairStatus[num] == ROOTED_IS) {
					hairStatus[num] = SHAVED;
				}
			}
		}
	}
}