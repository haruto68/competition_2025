#pragma once
#include "../../Resource/ResourceManager.h"
class Score
{
protected:

private:
	static int stagelevel;		// ��p(�\���̂ł���p�\)
public:
	// int stagelevel = 0;
public:
	Score();
	~Score();

public:
	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������	

	static void SetStageLevel(int level)
	{
		stagelevel = level;
	}

	static int GetStageLevel()
	{
		return stagelevel;
	}
};