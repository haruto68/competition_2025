#include "Enemy2.h"

Enemy2::Enemy2()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(30, 30);							//当たり判定の大きさ
	collision.object_type = eObjectType::eEnemy;					//オブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//ぶつかるオブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//ぶつかるオブジェクトのタイプ
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;
	
	//画像読み込み
	image = rm->GetImages("Resource/Images/enemy/cannon.png")[0];

	exp_num = 1;
}

Enemy2::~Enemy2()
{
}

void Enemy2::Initialize()
{
	//　仮敵2のサイズ(大きさ)
	collision.box_size = Vector2D(20.0f, 20.0f);
	//box_size = Vector2D(20.0fs, 20.0f);
	// 仮テキの速さ
	speed = 200.0f;

	hp = 2.0f;

}

void Enemy2::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	float shot_cooldown = 0.5f;

	//時間経過
	shot_timer += delta_seconds;

	if (shot_timer >= shot_cooldown && !explosion_flag)
	{
		EnemyShot* shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		if (!trans)
			shot->SetShotType(eEnemy2);
		else
			shot->SetShotType(eEnemy3);

		//タイマーリセット
		shot_timer = 0.0f;
	}
}

void Enemy2::Draw(const Vector2D&, bool) const
{
	
	if (image != -1)
	{
		float angle;
		if (trans == false)
		{
			angle = 0.0f;
		}
		else
		{
			angle = 3.14 / 1.0f;
		}
		DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	}
}

void Enemy2::Finalize()
{
}

void Enemy2::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
		break;
	case eEnemy:
		break;
	case ePlayerShot:
		hp -= player_stats.attack_power / 2;
		//PlaySoundMem(soundseffect[0], DX_PLAYTYPE_BACK, TRUE);
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Enemy2::Movement(float delta_seconds)
{
	//左に動かす
	velocity.x = -1.0f;
	
	location += velocity * speed * delta_seconds;
}

void Enemy2::Animation()
{
}

void Enemy2::SetTrans()
{
	trans = true;
}
