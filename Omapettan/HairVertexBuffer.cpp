#include "HairVertexBuffer.h"



c_Hair::c_Hair(const int Model, const int Image) {
	// ���f���̑��
	modelHandle = Model;

	// �摜�̑��
	graphHandle = Image;

	// �������̊��蓖��
	f_allocateMemory();
	
	// ���f���̕���
	f_modelDuplication();
}


void c_Hair::f_init() {

}


// �o��(�`��)
void c_Hair::f_output() {
	//// ���_�o�b�t�@�`��̎��Ԍv��
	//Time1 = GetNowHiPerformanceCount();
	//// ���_�o�b�t�@�ŕ`��
	DrawPolygonIndexed3D_UseVertexBuffer(vertexBufHandle, indexBufHandle, graphHandle, TRUE);
	//Time1 = GetNowHiPerformanceCount() - Time1;

	//// �|���������Ԃ�`��
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "���_�o�b�t�@�@:%4d micro sec", Time1);
}


// �X�V
void c_Hair::f_update() {

}


// ���f���̕���
void c_Hair::f_modelDuplication() {
	int vnum = 0;
	int pnum = 0;
	for (int x = 0; x < 8; x++) {
		for (int z = 0; z < 8; z++) {
			// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
			MV1SetPosition(modelHandle, VGet(x * 100.0f, 0.0f, -z * 100.0f));
			// Y����]
			MV1SetRotationXYZ(modelHandle, VGet(0.0f, 60.0f * DX_PI_F / 180.0f, 0.0f));

			//// �Q�Ɨp���b�V���̍쐬
			MV1SetupReferenceMesh(modelHandle, -1, TRUE);
			// �Q�Ɨp���b�V���̍X�V
			MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

			// �Q�Ɨp���b�V���̎擾
			RefMesh = MV1GetReferenceMesh(modelHandle, -1, TRUE);
			// ���_�f�[�^���R�s�[
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

			// �C���f�b�N�X�f�[�^���R�s�[
			for (i = 0; i < RefMesh.PolygonNum; i++)
			{
				index[i * 3 + 0 + pnum] = (WORD)RefMesh.Polygons[i].VIndex[0] + vnum;
				index[i * 3 + 1 + pnum] = (WORD)RefMesh.Polygons[i].VIndex[1] + vnum;
				index[i * 3 + 2 + pnum] = (WORD)RefMesh.Polygons[i].VIndex[2] + vnum;
			}
			vnum += RefMesh.VertexNum;
			pnum += RefMesh.PolygonNum * 3;
		}
	}
	

	// ���_�f�[�^�ƃC���f�b�N�X�f�[�^���i�[���钸�_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���쐬
	vertexBufHandle = CreateVertexBuffer(vertexNum, DX_VERTEX_TYPE_NORMAL_3D);
	indexBufHandle = CreateIndexBuffer(indexNum, DX_INDEX_TYPE_32BIT);

	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�Ƀf�[�^��]��
	SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	SetIndexBufferData(0, index, indexNum, indexBufHandle);

	////���f���̃R�s�[
	//int D_ModelHandle[HAIR_NUM];
	//for (int x = 0; x < 8; x++) {
	//	for (int z = 0; z < 8; z++) {
	//		D_ModelHandle[x * 8 + z] = MV1DuplicateModel(modelHandle);
	//		// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	//		MV1SetPosition(D_ModelHandle[x * 8 + z], VGet(x * 100.0f, 0.0f, -z * 100.0f));
	//		// Y����]
	//		MV1SetRotationXYZ(D_ModelHandle[x * 8 + z], VGet(0.0f, 60.0f * DX_PI_F / 180.0f, 0.0f));
	//		// �e�N�X�`��
	//		MV1SetTextureGraphHandle(D_ModelHandle[x * 8 + z], 0, graphHandle, TRUE);
	//	}
	//}
}


// �������̊��蓖��
void c_Hair::f_allocateMemory() {
	// �Q�Ɨp���b�V���̍쐬
	MV1SetupReferenceMesh(modelHandle, -1, TRUE);
	// �Q�Ɨp���b�V���̎擾
	RefMesh = MV1GetReferenceMesh(modelHandle, -1, TRUE);

	// ���_�̐��ƃC���f�b�N�X�̐����擾
	indexNum = RefMesh.PolygonNum * POLY * HAIR_NUM;
	vertexNum = RefMesh.VertexNum * HAIR_NUM;

	// ���_�f�[�^�ƃC���f�b�N�X�f�[�^���i�[���郁�����̈�̊m��
	vertex = (VERTEX3D*)malloc(sizeof(VERTEX3D) * vertexNum);
	index = (DWORD*)malloc(sizeof(DWORD) * indexNum);
}