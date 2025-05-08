#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"
#include"../../Utility/InputManager.h"

class LevelUpUI
{
public:
	bool old_flag;
	int cursor;
private:
	//�摜
	int window[3] = {};
	int power[5] = {};
	int power_icon[5] = {};


	int lottery[3] = {};		//�������e���I
	int lottery_icon[3] = {};	//�������e�A�C�R��


public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();			//����������
	void Update(bool flag);		//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������
};