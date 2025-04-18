#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/GameObjectManager.h"

InGameScene::InGameScene() :
	object_manager(),
	player(),
	back_ground_image(0),
	back_ground_location(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像取得
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_space02.png")[0];

	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	screen_offset.x = -0.05f;
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	//GameObjectManagerインスタンス取得
	object_manager = new GameObjectManager();

	//プライヤー生成
	player = object_manager->CreateGameObject<Player>(Vector2D(160, 360));

	// Test用生成
	Shot* shot;
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 200));
	shot->SetShotType(eEnemy1);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 400));
	shot->SetShotType(eEnemy2);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 600));
	shot->SetShotType(eEnemy3);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 300));
	shot->SetShotType(eEnemy3);
	// 仮に生成するときはこの下に
	EnemyBase* enemy;
	enemy = object_manager->CreateGameObject<Enemy1>(Vector2D(1000, 400));
	object_manager->CreateGameObject<Enemy2>(Vector2D(1000, 400));
	enemy->SetObjectList(object_manager);
	object_manager->CreateGameObject<Enemy3>(Vector2D(1000, 400));
}

eSceneType InGameScene::Update(const float& delta_second)
{
	//screen_offset -= 0.1f;
	back_ground_location.x -= 0.05f;
	if (back_ground_location.x <= -(D_WIN_MAX_X / 2))
	{
		back_ground_location.x = D_WIN_MAX_X / 2;
	}

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//PlayerにGameObjectManagerインスタンスを渡す
	player->SetObjectList(object_manager);

	// 生成するオブジェクトの確認
	object_manager->CheckCreateObject();
	// 破棄するオブジェクトの確認
	object_manager->CheckDestroyObject();
	// 現在のオブジェクトリストを取得
	scene_objects_list = object_manager->GetObjectList();

	// リスト内のオブジェクトを更新する
	for (GameObject* obj : scene_objects_list)
	{
		obj->Update(delta_second);
		obj->SetPlayerLocation(player->GetLocation());
		if(obj->GetCollision().object_type != eObjectType::ePlayer)
		{
			obj->SetLocation(Vector2D(obj->GetLocation().x + screen_offset.x, obj->GetLocation().y));
		}
	}

	// 画面外へでたオブジェクトを破壊する
	for (GameObject* obj : scene_objects_list)
	{
		if (obj->GetLocation().x <= -50 || obj->GetLocation().x >= D_WIN_MAX_X + 50 ||
			obj->GetLocation().y <= -50 || obj->GetLocation().y >= D_WIN_MAX_Y + 50)
		{
			object_manager->DestroyGameObject(obj);
		}
	}

	//インゲームシーンへ遷移
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eResult;
	}

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// 背景描画	
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);
	DrawRotaGraphF(back_ground_location.x + D_WIN_MAX_X, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	int c = 0;
	// オブジェクト描画
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(screen_offset, false);
		c++;
	}

	SetFontSize(40);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d",c);
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}