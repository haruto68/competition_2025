#pragma once
#include"../SceneBase.h"
#include"../UI/Score.h"
#include"../RankingScene/RankingScene.h"

#define MAX_STAGE		(4)			// �Q�[���̍ő�X�e�[�W��

class ResultScene : public SceneBase
{
protected:
	enum class selectedbutton 
	{
		Title,
		End
	};

	selectedbutton m_selectedbutton;
public:
	ResultScene();
	~ResultScene();

public:
	int menu_num;
	bool is_button;
	int back_ground_sound;
	int sounds_effect[2];
	int back_ground_image;
	Vector2D back_ground_location;		// �w�i���W
	int power_icon[6];					// ����	�A�C�R��
	int window;							// �g
	// ���U���g�V�[������̃X�R�A�̏�������ϐ�
	int level;
	int stagelevel;
	int power;
	int speed;
	int cool_time;
	int hit_range;
	bool three_way;
	bool drone;
	//int hp;

	bool is_drone;				// �h���[�����擾����Ă�����
	bool is_max;				// ����ɍs������
	bool is_check;				
	int color;					// �F�ύX
	bool is_cir;
	bool is_flash;				// �_�ł�����
	float flash_timer;

	int circle;				// (�J�[�\��)�~�̍��W

	Vector2D button_location;			// �{�^���̍��W

	Score* score;
	RankingScene* ranking;

	// std::vector<int> font_name;					// �t�H���g�ݒ�
	int font[5];								// �t�H���g�̐ݒ�

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

public:
	void CheckData();				// �v���C���[�̏�񂪃}�C�i�X�ɂȂ��Ă��Ȃ����m�F���鏈��

	 void Cursor();				// �J�[�\���̏���
};