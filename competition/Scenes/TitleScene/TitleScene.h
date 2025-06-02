#pragma once
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
protected:

private:
	int menu_num;			// ���j���[�J�[�\���ԍ�
	bool help;				// �w���v���J����Ă邩�ǂ���?
	bool is_button;			// �{�^��������ł��邩�ǂ���?
	int back_ground_sound;	// BGM
	int sounds_effect[2];	// ���ʉ�
	//int button_sound0;		// �I����
	//int button_sound1;		// ���艹

public:
	TitleScene();
	~TitleScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};