#pragma once
#include "Dxlib.h"

class c_Scene {
protected:
	//�R���X�g���N�^
	c_Scene() {}

public:
	//�R�s�[�֎~
	c_Scene(const c_Scene&) = delete;
	//�R�s�[�֎~
	c_Scene& operator=(const c_Scene&) = delete;

	//���z�֐��������f�X�g���N�^
	virtual ~c_Scene() = default;

	virtual c_Scene* f_update() = 0;
	virtual void f_output() const = 0;
	virtual void f_fadeout() = 0;		//�Ó]����
	virtual void f_fadein() = 0;		//���邭����

	bool IsNextScene;
};

namespace {
	enum SCENE_STATUS {
		FADE_IN,        // �t�F�[�h�C��
		IDOL,           // �ҋ@
		FADE_OUT,       // �t�F�[�h�A�E�g
		NEXT_SCENE,		//���̃V�[����
	};
}


//�񋓑̌^�̌��݂̃Q�[�����[�h
enum GAME_MODE {		
	GAME_TITLE,
	GAME_MAIN,
	GAME_RESULT,
	GAME_OVER,
	GAME_END,
	END = 99
};
