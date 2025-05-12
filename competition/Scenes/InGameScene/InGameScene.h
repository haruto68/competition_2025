#pragma once
#include"../SceneBase.h"
#include"../UI/LevelUpUI.h"
#include"../UI/HpUI.h"
#include"../UI/LevelUI.h"

#include"../../Objects/GameObject.h"
#include"../../Objects/Character/Player/Player.h"
#include"../../Objects/Character/Enemy/Enemy1/Enemy1.h"
#include"../../Objects/Character/Enemy/Enemy2/Enemy2.h"
#include"../../Objects/Character/Enemy/Enemy3/Enemy3.h"
#include"../../Objects/Shot/PlayerShot/PlayerShot.h"
#include"../../Objects/Shot/EnemyShot/EnemyShot.h"
#include"../../Objects/Item/ExperiencePoints/ExperiencePoints.h"

struct Planet
{
	float x;
	float y;
	double size;
	double angle;
	int image;
};

class InGameScene : public SceneBase
{
protected:

public:
	std::vector<GameObject*> scene_objects_list;//�I�u�W�F�N�g���X�g
	class GameObjectManager* object_manager;	//�I�u�W�F�N�g�}�l�[�W���[�C���X�^���X
	class Player* player;						//�v���C���[�C���X�^���X
	LevelUpUI* level_up_ui;						//���x���A�b�vUI
	HpUI* hp_ui;								//HPUI
	LevelUI* level_ui;							//���x��UI

	int back_ground_image;						//�w�i�摜
	Vector2D back_ground_location;				//�w�i���W
	int planets_image[4];						//�f���摜
	Planet pla1;								//�f��1
	Planet pla2;								//�f��2

	float spawn_timer;							//�G�����N�[���^�C��
	bool level_up_flg;							//���x���A�b�v�t���O
	bool time_stop;



public:
	InGameScene();	//�R���X�g���N�^
	~InGameScene();	//�f�X�g���N�^

public:
	virtual void Initialize() override;						//����������
	virtual eSceneType Update(const float& delta_second);	//�X�V����
	virtual void Draw() const override;						//�`�揈��
	virtual void Finalize() override;						//�I������

public:
	virtual eSceneType GetNowSceneType() const override;	//���݃V�[���擾����

private:
	void BackGroundManager(const float& delta_second);		//�w�i�Ǘ�����

	void EnemyManager(const float& delta_second);			//�G�����Ǘ�����
	void Spawn();											//�G����
};