#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/GameObjectManager.h"

InGameScene::InGameScene() :
	object_manager(),
	player(),
	shot()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像取得
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
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 200));
	shot->SetShotType(eEnemy1);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 400));
	shot->SetShotType(eEnemy2);
	// 仮に生成するときはこの下に
	object_manager->CreateGameObject<Enemy1>(Vector2D(1000, 400));
	object_manager->CreateGameObject<Enemy2>(Vector2D(1000, 400));
	object_manager->CreateGameObject<Enemy3>(Vector2D(1000, 400));
}

eSceneType InGameScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

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
	DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(0, 0, 100), TRUE);

	// オブジェクト描画
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(screen_offset, false);
	}

	DrawFormatString(10, 10, GetColor(255, 255, 255), "インゲームシーン");
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}

//void InGameScene::spawn()
//{
//	/*int ramdom_l = GetRand(2);*/
//	int ramdom_r = GetRand(2);
//	int ramdom_y = GetRand(2);
//
//	// Y座標決定
//	float Y_t = 170.0f + (float)(ramdom_y * 80);
//	float Y_b = 170.0f + (3 * 80);
//
//	int num = rand() % 100 + 1;
//
//	// 右側に敵をスポーンさせる（90%の確率）
//	if (num <= 90)
//	{
//		switch (ramdom_r)
//		{
//		case 0:
//			object_manager->CreateGameObject<Enemy1>(Vector2D(620, Y_b));
//			break;
//		case 1:
//			object_manager->CreateGameObject<Enemy2>(Vector2D(620, Y_t));
//			break;
//		case 2:
//			object_manager->CreateGameObject<Enemy3>(Vector2D(620, Y_t));
//			break;
//		default:
//			break;
//		}
//	}
//
//	//// 左側にもスポーンしたいならこっちも有効にする
//	//if (num <= 75)
//	//{
//	//	switch (ramdom_l)
//	//	{
//	//	case 0:
//	//		object_manager->CreateGameObject<Enemy1>(Vector2D(30, Y_b));
//	//		break;
//	//	case 1:
//	//		object_manager->CreateGameObject<Enemy2>(Vector2D(30, Y_t));
//	//		break;
//	//	case 2:
//	//		object_manager->CreateGameObject<Enemy3>(Vector2D(30, Y_t));
//	//		break;
//	//	default:
//	//		break;
//	//	}
//	//}
//}
