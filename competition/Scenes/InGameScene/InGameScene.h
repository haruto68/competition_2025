#pragma once
#include"../SceneBase.h"
#include"../../Objects/GameObject.h"

#include"../../Objects/Character/Player/Player.h"
#include"../../Objects/Character/Enemy/Enemy1/Enemy1.h"
#include"../../Objects/Character/Enemy/Enemy2/Enemy2.h"
#include"../../Objects/Character/Enemy/Enemy3/Enemy3.h"
#include"../../Objects/Shot/PlayerShot/PlayerShot.h"
#include"../../Objects/Shot/EnemyShot/EnemyShot.h"

class InGameScene : public SceneBase
{
protected:

public:
	class GameObjectManager* object_manager;
	class Player* player;
	//class Shot* shot;
	int back_ground_image;
	Vector2D back_ground_location;

	std::vector<GameObject*> scene_objects_list;

public:
	InGameScene();
	~InGameScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	/*void spawn();*/
};