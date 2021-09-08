#include "HitCheck.h"


// 衝突判定
// 当たっていればtrueを返し、当たっていなければfalseを返す
// col1:オブジェクト    col2:プレイヤー    rot:プレイヤーのｙ軸の回転値
bool c_HitCheck::f_playerAndObjects(c_Collision col1, c_Collision col2, float rot) {
	VECTOR Cubevertex1[16];        // 四角形の頂点16
	VECTOR Cubevertex2[4];         // 四角形の頂点8
	HITRESULT_LINE result;         // 結果を格納
	float radius = sqrtf(powf(col2.wide / 2, 2.0) + powf(col2.depth / 2, 2.0));    // 剃刀の原点から当たり判定のポリゴンの頂点への距離
	float angle = atan2(float(col2.depth / 2), float(col2.wide / 2)) * DX_PI;       // 剃刀の原点から当たり判定のポリゴンの頂点への角度



	//頂点座標の設定
	Cubevertex1[ 0] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y,              col1.pos.z - (col1.depth / 2));																			//
	Cubevertex1[ 1] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y,              col1.pos.z - (col1.depth / 2));
	Cubevertex1[ 2] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z - (col1.depth / 2));
	Cubevertex1[ 3] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z - (col1.depth / 2));
	Cubevertex1[ 4] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y,              col1.pos.z + (col1.depth / 2));
	Cubevertex1[ 5] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y,              col1.pos.z + (col1.depth / 2));
	Cubevertex1[ 6] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));
	Cubevertex1[ 7] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));
	Cubevertex1[ 8] = VGet(col1.pos.x,                   col1.pos.y,              col1.pos.z - (col1.depth / 2));																			//
	Cubevertex1[ 9] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y,              col1.pos.z);
	Cubevertex1[10] = VGet(col1.pos.x,                   col1.pos.y,              col1.pos.z - (col1.depth / 2));
	Cubevertex1[11] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y,              col1.pos.z);
	Cubevertex1[12] = VGet(col1.pos.x,                   col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));
	Cubevertex1[13] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z);
	Cubevertex1[14] = VGet(col1.pos.x,                   col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));
	Cubevertex1[15] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z);

	
	Cubevertex2[0] = VGet(col2.pos.x + sinf(rot -          angle ) * radius, col2.pos.y, col2.pos.z + cosf(rot -          angle ) * radius);
	Cubevertex2[1] = VGet(col2.pos.x + sinf(rot - (DX_PI - angle)) * radius, col2.pos.y, col2.pos.z + cosf(rot - (DX_PI - angle)) * radius);
	Cubevertex2[2] = VGet(col2.pos.x + sinf(rot + (DX_PI - angle)) * radius, col2.pos.y, col2.pos.z + cosf(rot + (DX_PI - angle)) * radius);
	Cubevertex2[3] = VGet(col2.pos.x + sinf(rot +          angle ) * radius, col2.pos.y, col2.pos.z + cosf(rot +          angle ) * radius);



	result = HitCheck_Line_Triangle(Cubevertex1[0], Cubevertex1[2], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[1], Cubevertex1[3], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[4], Cubevertex1[6], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[5], Cubevertex1[7], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[0], Cubevertex1[2], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[1], Cubevertex1[3], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[4], Cubevertex1[6], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[5], Cubevertex1[7], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[ 8], Cubevertex1[12], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[ 9], Cubevertex1[13], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[10], Cubevertex1[14], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[11], Cubevertex1[15], Cubevertex2[0], Cubevertex2[1], Cubevertex2[2]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[ 8], Cubevertex1[12], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[ 9], Cubevertex1[13], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[10], Cubevertex1[14], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[11], Cubevertex1[15], Cubevertex2[0], Cubevertex2[2], Cubevertex2[3]);
	if (result.HitFlag == true)return true;

	/*
	result = HitCheck_Line_Triangle(Cubevertex1[0], Cubevertex1[2], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[1], Cubevertex1[3], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[4], Cubevertex1[6], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[5], Cubevertex1[7], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[0], Cubevertex1[2], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[1], Cubevertex1[3], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[4], Cubevertex1[6], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[5], Cubevertex1[7], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[ 8], Cubevertex1[12], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[ 9], Cubevertex1[13], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[10], Cubevertex1[14], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[11], Cubevertex1[15], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4]);
	if (result.HitFlag == true)return true;


	result = HitCheck_Line_Triangle(Cubevertex1[ 8], Cubevertex1[12], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[ 9], Cubevertex1[13], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[10], Cubevertex1[14], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	result = HitCheck_Line_Triangle(Cubevertex1[11], Cubevertex1[15], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5]);
	if (result.HitFlag == true)return true;
	*/
	return false;
}