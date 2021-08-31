#include"DxLib.h"

#include "DrawCube.h"

//c_DrawCube::c_DrawCube() {
//
//}

 void c_DrawCube::f_create(float x, float y, float z, float w, float h, float d) {
	 //VERTEX3D Cubevertex[8];        //lŠpŒ`‚Ì’¸“_8
	 //WORD Index[36];		//°‚Ìƒ|ƒŠƒSƒ“12‚±‚Ì’¸“_À•W


		//’¸“_À•W‚Ìİ’è
		Cubevertex[0].pos = VGet(x, y, z);
		Cubevertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[0].dif = GetColorU8(255, 0, 0, 255);
		Cubevertex[0].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[0].u = 0.0f;
		Cubevertex[0].v = 0.0f;
		Cubevertex[0].su = 0.0f;
		Cubevertex[0].sv = 0.0f;

		Cubevertex[1].pos = VGet(x + w, y, z);
		Cubevertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[1].dif = GetColorU8(0, 0, 255, 255);
		Cubevertex[1].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[1].u = 0.0f;
		Cubevertex[1].v = 0.0f;
		Cubevertex[1].su = 0.0f;
		Cubevertex[1].sv = 0.0f;

		Cubevertex[2].pos = VGet(x, y + h, z);
		Cubevertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[2].dif = GetColorU8(255, 255, 255, 255);
		Cubevertex[2].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[2].u = 0.0f;
		Cubevertex[2].v = 0.0f;
		Cubevertex[2].su = 0.0f;
		Cubevertex[2].sv = 0.0f;

		Cubevertex[3].pos = VGet(x + w, y + h, z);
		Cubevertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[3].dif = GetColorU8(255, 255, 255, 255);
		Cubevertex[3].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[3].u = 0.0f;
		Cubevertex[3].v = 0.0f;
		Cubevertex[3].su = 0.0f;
		Cubevertex[3].sv = 0.0f;

		Cubevertex[4].pos = VGet(x, y, z + d);
		Cubevertex[4].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[4].dif = GetColorU8(255, 0, 255, 255);
		Cubevertex[4].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[4].u = 0.0f;
		Cubevertex[4].v = 0.0f;
		Cubevertex[4].su = 0.0f;
		Cubevertex[4].sv = 0.0f;

		Cubevertex[5].pos = VGet(x + w, y, z + d);
		Cubevertex[5].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[5].dif = GetColorU8(255, 255, 0, 255);
		Cubevertex[5].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[5].u = 0.0f;
		Cubevertex[5].v = 0.0f;
		Cubevertex[5].su = 0.0f;
		Cubevertex[5].sv = 0.0f;

		Cubevertex[6].pos = VGet(x, y + h, z + d);
		Cubevertex[6].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[6].dif = GetColorU8(255, 255, 255, 255);
		Cubevertex[6].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[6].u = 0.0f;
		Cubevertex[6].v = 0.0f;
		Cubevertex[6].su = 0.0f;
		Cubevertex[6].sv = 0.0f;

		Cubevertex[7].pos = VGet(x + w, y + h, z + d);
		Cubevertex[7].norm = VGet(0.0f, 0.0f, -1.0f);
		Cubevertex[7].dif = GetColorU8(255, 255, 255, 255);
		Cubevertex[7].spc = GetColorU8(0, 0, 0, 0);
		Cubevertex[7].u = 0.0f;
		Cubevertex[7].v = 0.0f;
		Cubevertex[7].su = 0.0f;
		Cubevertex[7].sv = 0.0f;


		

		//
		Index[0] = 0;	Index[1] = 2;	Index[2] = 1;
		Index[3] = 1;	Index[4] = 2;	Index[5] = 3;

		Index[6] = 1;	Index[7] = 5;	Index[8] = 3;
		Index[9] = 5;	Index[10] = 3;	Index[11] = 7;

		Index[12] = 5;	Index[13] = 4;	Index[14] = 7;
		Index[15] = 4;	Index[16] = 7;	Index[17] = 6;

		Index[18] = 4;	Index[19] = 0;	Index[20] = 6;
		Index[21] = 0;	Index[22] = 6;	Index[23] = 2;

		Index[24] = 5;	Index[25] = 4;	Index[26] = 0;
		Index[27] = 5;	Index[28] = 0;	Index[29] = 1;

		Index[30] = 6;	Index[31] = 7;	Index[32] = 2;
		Index[33] = 7;	Index[34] = 2;	Index[35] = 3;


		//Äİ’è
		Index[0] = 0;	Index[1] = 2;	Index[2] = 1;
		Index[3] = 1;	Index[4] = 2;	Index[5] = 3;

		Index[6] = 1;	Index[7] = 3;	Index[8] = 5;
		Index[9] = 3;	Index[10] = 7;	Index[11] = 5;

		Index[12] = 5;	Index[13] = 4;	Index[14] = 7;
		Index[15] = 4;	Index[16] = 7;	Index[17] = 6;

		Index[18] = 4;	Index[19] = 0;	Index[20] = 6;
		Index[21] = 0;	Index[22] = 6;	Index[23] = 2;

		Index[24] = 5;	Index[25] = 4;	Index[26] = 0;
		Index[27] = 0;	Index[28] = 1;	Index[29] = 5;

		Index[30] = 6;	Index[31] = 7;	Index[32] = 2;
		Index[33] = 7;	Index[34] = 3;	Index[35] = 2;


		// ‚P‚Qƒ|ƒŠƒSƒ“‚Ì•`‰æ(°)
		DrawPolygonIndexed3D(Cubevertex, 36, Index, 12, DX_NONE_GRAPH, FALSE);

}