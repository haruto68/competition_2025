#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/Character/Player/PlayerStats.h"

#define	LOT_MAX			(5)	//�ő咊�I��

#define	STATS_HP		(0)
#define STATS_DAMAGE	(1)
#define STATS_SPEED		(2)
#define WAPON_3WAY		(3)
#define WAPON_SIZE		(4)

class LevelUpUI
{
public:
	bool old_flag;
	int cursor;
private:
	//�摜
	int window[4];
	int power[5];
	int power_icon[5];

	ePowerUp lot[LOT_MAX];		//�������e���I
	int lot_str[LOT_MAX];		//�������e����
	int lot_icon[LOT_MAX];		//�������e�A�C�R��

	PlayerStats player_stats;	//�v���C���[�X�e�[�^�X

	//�e�m��(���v100%)
	int proba[LOT_MAX] = { 21,21,21,15,21 };
	int bility[LOT_MAX] = { 0,0,0,0,0 };


public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();							//����������
	void Update(bool flag, PlayerStats stats);	//�X�V����
	void Draw() const;							//�`�揈��
	void Finalize();							//�I������
	
	int Probability();							//�m������
	void Lottery(int* nums);					//���I
	ePowerUp GetLottery();						//���I���e�擾
};