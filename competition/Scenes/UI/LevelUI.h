#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class LevelUI
{	
public:
	int level;
private:
	std::vector<int> level_bar;			// ���x�������̉摜
public:
	LevelUI();
	~LevelUI();

public:
	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������

	void SetExperience(int);
};