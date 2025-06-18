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
	int back_ground_image;				// �w�i�摜
	Vector2D back_ground_location;		// �w�i���W

	// �t�H���g�̓o�^
	// int title_name;
	// int button;
	// int push_button;
	// int help_font;
	// int help_font_title;

	// �{�^���摜		test			0 :	�\���J�[�\�� 1: A�{�^��	2:�@B�{�^��
	std::vector<int> ui_button;
	std::vector<Vector2D> ui_location;
	std::vector<Vector2D> font_location;

	int font[5];
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