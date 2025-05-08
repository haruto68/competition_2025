#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class HpUI
{
private:
	int hp_table;
	int hp_bar;

public:
	HpUI();
	~HpUI();

public:
	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������
};