#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "LoadSound.h"

extern Sound g_Snd;

c_Hair::c_Hair(const int Model, const int Image) {
	//�т̓����蔻��p�̍��W�̏�����
	//�т̓����蔻��p�̃t���O�̏�����
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
	}

	acnepersonalpos = new c_Acne();

	// ���f���̑��
	modelHandle = Model;

	// �摜�̑��
	graphHandle = Image;

	// �������̊��蓖��
	f_allocateMemory();

	// �т̍��W�Ɗp�x��ݒ�
	f_setPosAndRot();

	// ���f���̕���
	f_modelDuplication();

	stageXRotation = 0.0f;

	hairSize = VGet(40.0f, 40.0f, 40.0f);

	//f_funcList[ROOTED_IS] = f_moveHair();
	/*(this->*f_hairStatusFuncList[3])(0) =
	{ f_moveHair, f_flyShavedHair, f_MoveHairOffScreen };*/
}

void c_Hair::f_init() {

}


// �o��(�`��)
void c_Hair::f_output() {
	// �T�C�Y�̐ݒ�
	MV1SetScale(modelHandle, VGet(0.2f, 0.6f, 0.2f));
	// ���_�o�b�t�@�ŕ`��
	DrawPolygonIndexed3D_UseVertexBuffer(vertexBufHandle, indexBufHandle, graphHandle, TRUE);
}


// �X�V
void c_Hair::f_update() {
	////�{�b�N�X�R���C�_�[�̕`��
	CubeDraw();

	// �т̈ړ�
	f_hairUpdate();
}


// ���f���̕���
void c_Hair::f_modelDuplication() {
	int vnum = 0;
	int pnum = 0;
	VECTOR debug;

	for (int i = 0; i < HAIR_NUM; i++) {

		MV1SetPosition(modelHandle, VGet(sinf(personalRotation[i]) * ARM_RADIUS,
			cosf(personalRotation[i]) * ARM_RADIUS,
			personalPosZ[i]));
		//���f���̍��W�𓖂��蔻��p�̕ϐ��ɃR�s�[
		CollisionPosition[i] = VGet(sinf(personalRotation[i]) * ARM_RADIUS,
			cosf(personalRotation[i]) * ARM_RADIUS,
			personalPosZ[i]);
		c_colision[i] =
			new c_Collision(CollisionPosition[i], hairSize.x, hairSize.y, hairSize.z);
		// Y����]
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, 0.0f, 0.0f));

		// �Q�Ɨp���b�V���̍쐬
		MV1SetupReferenceMesh(modelHandle, -1, TRUE);
		// �Q�Ɨp���b�V���̍X�V
		MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

		// �Q�Ɨp���b�V���̎擾
		RefMesh = MV1GetReferenceMesh(modelHandle, -1, TRUE);
		// ���_�f�[�^���R�s�[
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

		// �C���f�b�N�X�f�[�^���R�s�[
		for (int j = 0; j < RefMesh.PolygonNum; j++)
		{
			index[j * 3 + 0 + pnum] = (WORD)RefMesh.Polygons[j].VIndex[0] + vnum;
			index[j * 3 + 1 + pnum] = (WORD)RefMesh.Polygons[j].VIndex[1] + vnum;
			index[j * 3 + 2 + pnum] = (WORD)RefMesh.Polygons[j].VIndex[2] + vnum;
		}
		vnum += RefMesh.VertexNum;
		pnum += RefMesh.PolygonNum * 3;

	}


	// ���_�f�[�^�ƃC���f�b�N�X�f�[�^���i�[���钸�_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���쐬
	vertexBufHandle = CreateVertexBuffer(vertexNum, DX_VERTEX_TYPE_NORMAL_3D);
	indexBufHandle = CreateIndexBuffer(indexNum, DX_INDEX_TYPE_32BIT);

	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�Ƀf�[�^��]��
	SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	SetIndexBufferData(0, index, indexNum, indexBufHandle);

	//���f���̍��W��Ԃ�
	//return position;

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


void c_Hair::CubeDraw() {
	//�R���W�����̈ʒu�����p�̐��l
	for (int num = 0; num < HAIR_NUM; num++)
	{
		/*Cube.f_create(CollisionPosition[num].x - (200 / 2), CollisionPosition[num].y,
			CollisionPosition[num].z - (200 / 2),200, 600, 200);*/
		Cube.f_create(CollisionPosition[num].x - (hairSize.x / 2), CollisionPosition[num].y,
			CollisionPosition[num].z - (hairSize.z / 2), hairSize.x, hairSize.y, hairSize.z);
	}
}

// �т̈ړ�
void c_Hair::f_moveHair(int num) {

	int vnum = 0;
	int pnum = 0;

	//for (int i = 0; i < HAIR_NUM; i++) {
	MV1SetPosition(modelHandle, VGet(sinf(personalRotation[num] + stageXRotation) * (ARM_RADIUS + personalRadius[num]) + hairFlyingVec[num],
		cosf(personalRotation[num] + stageXRotation) * (ARM_RADIUS + personalRadius[num]),
		personalPosZ[num]));
	//���f���̍��W�𓖂��蔻��p�̕ϐ��ɃR�s�[
	CollisionPosition[num] = VGet(sinf(personalRotation[num] + stageXRotation) * ARM_RADIUS + hairFlyingVec[num],
		cosf(personalRotation[num] + stageXRotation) * ARM_RADIUS,
		personalPosZ[num]);
	c_colision[num] =
		new c_Collision(CollisionPosition[num], hairSize.x, hairSize.y, hairSize.z);
	// Y����]
	MV1SetRotationXYZ(modelHandle, VGet(hairFlyingRotX[num], 0, hairFlyingRotZ[num] - personalRotation[num] - stageXRotation));


	// �Q�Ɨp���b�V���̍X�V
	MV1RefreshReferenceMesh(modelHandle, -1, TRUE);

	vnum = num * RefMesh.VertexNum;

	// ���_�f�[�^���R�s�[
	for (int j = 0; j < RefMesh.VertexNum; j++)
	{
		vertex[j + vnum].pos = RefMesh.Vertexs[j].Position;
	}

	/*vnum += RefMesh.VertexNum;
	pnum += RefMesh.PolygonNum * 3;*/
	//}

	//// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�Ƀf�[�^��]��
	//SetVertexBufferData(0, vertex, vertexNum, vertexBufHandle);
	//SetIndexBufferData(0, index, indexNum, indexBufHandle);

}

// �т̍��W�Ɗp�x��ݒ�
void c_Hair::f_setPosAndRot() {

	// �V�[�h�l�ݒ�
	//SRand(GetDateTime(&date));
	//float debug = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;

	for (int i = 0; i < HAIR_NUM; i++) {
		// �e�т̊p�x��ݒ�
		personalRotation[i] = GetRand(int(2 * float(DX_PI) * 100)) * 0.01f;
		//personalRotation[i] = debug;

		// �e�т�Z���W��ݒ�
		personalPosZ[i] = GetRand(ARM_LENGTH) + ARM_ADJUST_POS;
	}
	acnepersonalpos->acnepersonalPosZ[0];
	for (int j = 0; j < ACNE_NUM; j++) {
		for (int i = 0; i < HAIR_NUM; i++) {
			if ((acnepersonalpos->acnepersonalPosZ[j] + 200 < personalPosZ[i]) || (acnepersonalpos->acnepersonalPosZ[j] - 200> personalPosZ[i])) {
				for (personalPosZ[i]; personalPosZ[i] > 0;) {
					personalPosZ[i] = GetRand(ARM_LENGTH) + ARM_ADJUST_POS;
					if ((acnepersonalpos->acnepersonalPosZ[j] + 200 < personalPosZ[i]) || (acnepersonalpos->acnepersonalPosZ[j] - 200 > personalPosZ[i]))
						if (CheckingOverlapsWithPlayer(personalRotation[i], personalPosZ[i]) == false)break;
				}
			}
			printf("\n%d\t%f", i, personalPosZ[i]);
		}
	}
}

// �т���ʊO�ֈړ�
void c_Hair::f_MoveHairOffScreen(int num) {
	// �т���ʂɉf��Ȃ��ʒu�ֈړ�
	personalPosZ[num] = -5000.0f;

	(this->*f_hairStatusFuncList[ROOTED_IS])(num);

	hairStatus[num] = DO_NOT_ANYTHING;
}

// �т̏�Ԃ�ω�(���t���Ă��遨���ꂽ)
void c_Hair::f_hairCut(int num) {
	if (hairStatus[num] == ROOTED_IS) {
		hairStatus[num] = SHAVED;
		HitHair[num] = false;
		PlaySoundMem(g_Snd.HIGESORI_SE, DX_PLAYTYPE_BACK);
		//printf("num=%d status=%d\n", num,hairStatus[num]);
	}
}

// ���ꂽ�т��΂�
void c_Hair::f_flyShavedHair(int num) {
	// �т̉�]
	hairFlyingRotX[num] -= cosf(playerRotY[num]) / 20;
	hairFlyingRotZ[num] += sinf(playerRotY[num]) / 20;

	// �т��v���C���[�̌������֔�΂�
	personalRadius[num] += 9;
	hairFlyingVec[num] -= sinf(playerRotY[num]) * 20;
	personalPosZ[num] -= cosf(playerRotY[num]) * 20;

	(this->*f_hairStatusFuncList[ROOTED_IS])(num);

	if (personalRadius[num] >= 2000) {
		hairStatus[num] = OFF_SCREEN;
		numflg = true;
	}
}

// �������Ȃ�
void c_Hair::f_doNotAnything(int num) {
	return;
}

// �т̍X�V
void c_Hair::f_hairUpdate() {

	for (int i = 0/*, vnum = 0, pnum = 0*/; i < HAIR_NUM; i++) {
		(this->*f_hairStatusFuncList[hairStatus[i]])(i);
	}

	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�Ƀf�[�^��]��
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

//�т̏�Ԃ�����
bool c_Hair::f_hairStatusSee() {
	//�т̏�Ԃ����Ē���ĂȂ��т���������false��Ԃ�
	for (int i = 0; i < HAIR_NUM; i++)
	{
		if (hairStatus[i] == ROOTED_IS)
		{
			//printf("%d", hairStatus[0]);
			return false;
		}
	}

	//printf("gomi");
	//�S������Ă���true��Ԃ�
	return true;
}

// �v���C���[��Y���̉�]�l���擾
void c_Hair::f_getRotationY(int num, float rot) {
	if (hairStatus[num] == ROOTED_IS) {
		playerRotY[num] = rot;
		playerRotY[num] -= DX_PI_F;
	}
}

void c_Hair::f_GetAcnePosZ(c_Acne* c_acne) {
	acnepersonalpos = c_acne;
}

// �v���C���[�Ƃ̏d���̊m�F
bool c_Hair::CheckingOverlapsWithPlayer(float rot, float posZ) {
	// �v���C���[�Əd�Ȃ��Ă��镔���������true
	if (4100 < posZ && posZ < 4900)
		if (rot < DX_PI / 180 * 20 || DX_PI / 180 * 340 < rot)
			return true;

	// �d�Ȃ��Ă��Ȃ����false
	return false;
}