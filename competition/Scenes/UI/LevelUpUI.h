#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class LevelUpUI
{
	bool draw_flag;

	int window;
	int table_01;
	int header;

public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();			//����������
	void Update(bool flag);		//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������
};