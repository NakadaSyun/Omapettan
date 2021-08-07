#include "HairVertexBuffer.h"

c_Hair::c_Hair(const int Model, const int Image) {
	//毛の当たり判定用の座標の初期化
	//毛の当たり判定用のフラグの初期化
	for (int num = 0; num < HAIR_NUM; num++)
	{
		CollisionPosition[num] = VGet(0.0f, 0.0f, 0.0f);
		HitHair[num] = true;
	}

	// モデルの代入
	modelHandle = Model;

	// 画像の代入
	graphHandle = Image;

	// メモリの割り当て
	f_allocateMemory();

	// 髪の座標と角度を設定
	f_setPosAndRot();

	// モデルの複製
	f_modelDuplication();

	stageXRotation = 0.0f;

	hairSize = VGet(200.0f, 600.0f, 200.0f);
}


void c_Hair::f_init() {

}


// 出力(描画)
void c_Hair::f_output() {
	//// 頂点バッファで描画
	DrawPolygonIndexed3D_UseVertexBuffer(vertexBufHandle, indexBufHandle, graphHandle, TRUE);
}


// 更新
void c_Hair::f_update() {
	//ボックスコライダーの描画
	CubeDraw();

	// 髪の移動
	f_moveHair();
}


// モデルの複製
void c_Hair::f_modelDuplication() {
	int vnum = 0;	
	int pnum = 0;
	VECTOR debug;
	
	for (int j = 0; j < HAIR_NUM; j++) {

		MV1SetPosition(modelHandle, VGet(cosf(personalRotation[j]) * ARM_RADIUS,
			                             sinf(personalRotation[j]) * ARM_RADIUS,
			                             personalPosZ[j] + ARM_ADJUST_POS));
		//モデルの座標を当たり判定用の変数にコピー
		CollisionPosition[j] = VGet(cosf(personalRotation[j]) * ARM_RADIUS,
			                             sinf(personalRotation[j]) * ARM_RADIUS,
			                             personalPosZ[j] + ARM_ADJUST_POS
			                             /*4500.0f*/);
		c_colision[j] =
			new c_Collision(CollisionPosition[j], hairSize.x, hairSize.y, hairSize.z);
		// Y軸回転
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, 60.0f * DX_PI_F / 180.0f, 0.0f));

		// 参照用メッシュの作成
		MV1SetupReferenceMesh(modelHandle, -1, TRUE);
		// 参照用メッシュの更新
		MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

		// 参照用メッシュの取得
		RefMesh = MV1GetReferenceMesh(modelHandle, -1, TRUE);
		// 頂点データをコピー
		for (i = 0; i < RefMesh.VertexNum; i++)
		{
			vertex[i + vnum].pos = RefMesh.Vertexs[i].Position;
			vertex[i + vnum].norm = RefMesh.Vertexs[i].Normal;
			vertex[i + vnum].dif = RefMesh.Vertexs[i].DiffuseColor;
			vertex[i + vnum].spc = RefMesh.Vertexs[i].SpecularColor;
			vertex[i + vnum].u = RefMesh.Vertexs[i].TexCoord[0].u;
			vertex[i + vnum].v = RefMesh.Vertexs[i].TexCoord[0].v;
			vertex[i + vnum].su = RefMesh.Vertexs[i].TexCoord[1].u;
			vertex[i + vnum].sv = RefMesh.Vertexs[i].TexCoord[1].v;
		}

		// インデックスデータをコピー
		for (i = 0; i < RefMesh.PolygonNum; i++)
		{
			index[i * 3 + 0 + pnum] = (WORD)RefMesh.Polygons[i].VIndex[0] + vnum;
			index[i * 3 + 1 + pnum] = (WORD)RefMesh.Polygons[i].VIndex[1] + vnum;
			index[i * 3 + 2 + pnum] = (WORD)RefMesh.Polygons[i].VIndex[2] + vnum;
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
		Cube.f_create(CollisionPosition[num].x - (200 / 2), CollisionPosition[num].y,
			CollisionPosition[num].z - (200 / 2),200, 600, 200);
	}	
}

// 髪の移動
void c_Hair::f_moveHair() {

	int vnum = 0;
	int pnum = 0;

	for (int j = 0; j < HAIR_NUM; j++) {
		MV1SetPosition(modelHandle, VGet(cosf(personalRotation[j] - stageXRotation) * ARM_RADIUS,
				                              sinf(personalRotation[j] - stageXRotation) * ARM_RADIUS,
				                              personalPosZ[j] + ARM_ADJUST_POS));
		//モデルの座標を当たり判定用の変数にコピー
		CollisionPosition[j] = VGet(cosf(personalRotation[j] - stageXRotation) * ARM_RADIUS,
			                        sinf(personalRotation[j] - stageXRotation) * ARM_RADIUS,
			                        personalPosZ[j] + ARM_ADJUST_POS
			                        /*4500.0f*/);
		c_colision[j] =
			new c_Collision(CollisionPosition[j], hairSize.x, hairSize.y, hairSize.z);
		// Y軸回転
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, personalRotation[j] + stageXRotation, 0.0f));
		
		// 参照用メッシュの更新
		MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

		// 頂点データをコピー
		for (i = 0; i < RefMesh.VertexNum; i++)
		{
			vertex[i + vnum].pos = RefMesh.Vertexs[i].Position;
		}

		vnum += RefMesh.VertexNum;
		pnum += RefMesh.PolygonNum * 3;
	}

	// 頂点バッファとインデックスバッファにデータを転送
	SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	SetIndexBufferData(0, index, indexNum, indexBufHandle);

}

// 髪の座標と角度を設定
void c_Hair::f_setPosAndRot() {

	// シード値設定
	//SRand(GetDateTime(&date));

	for (int i = 0; i < HAIR_NUM; i++) {
		// 各髪の角度を設定
		personalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;

		// 各髪のZ座標を設定
		personalPosZ[i] = GetRand(ARM_LENGTH);
	}
}

// 髪を画面外へ移動
void c_Hair::f_MoveHairOffScreen(int num) {

	personalPosZ[num] = -1000;

	//int vnum = num * RefMesh.VertexNum;

	//MV1SetPosition(modelHandle, VGet(0, 0, 0));
	////モデルの座標を当たり判定用の変数にコピー
	//CollisionPosition[num] = VGet(0, 0, 0);
	//c_colision[num] = 
	//	new c_Collision(CollisionPosition[num], hairSize.x, hairSize.y, hairSize.z);
	//// Y軸回転
	//MV1SetRotationXYZ(modelHandle, VGet(0.0f, personalRotation[num] + stageXRotation, 0.0f));

	//// 参照用メッシュの更新
	//MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

	//// 頂点データをコピー
	//for (i = 0; i < RefMesh.VertexNum; i++)
	//{
	//	vertex[i + vnum].pos = RefMesh.Vertexs[i].Position;
	//}

	//// 頂点バッファとインデックスバッファにデータを転送
	//SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	//SetIndexBufferData(0, index, indexNum, indexBufHandle);
}