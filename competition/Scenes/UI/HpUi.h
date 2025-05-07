#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class HpUI
{
private:

public:
	HpUI();
	~HpUI();

public:
	void Initialize();			//����������
	void Update(bool flag);		//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������
};