#include"DxLib.h"
#include"GameObject.h"
#include"GameObjectManager.h"

#include"Item/ExperiencePoints/ExperiencePoints.h"

GameObject::GameObject() :
	location(0.0f),
	death_location(0.0f),
	speed(0),
	image(NULL),
	transparency(255),
	z_layer(0),
	is_mobility(false),
	player_location(0.0f),
	player_stats(),
	object_manager(nullptr),
	explosions(),
	death_timer(0),
	anim_num(0),
	explosion_flag(false)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	explosions[0] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion1.png")[0];
	explosions[1] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion2.png")[0];
	explosions[2] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion3.png")[0];
	explosions[3] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion4.png")[0];
	explosions[4] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion5.png")[0];
	explosions[5] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion6.png")[0];
	explosions[6] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion7.png")[0];
	explosions[7] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion8.png")[0];
	explosions[8] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion9.png")[0];
	explosions[9] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion10.png")[0];
	explosions[10] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion11.png")[0];
	explosions[11] = 0;
}

GameObject::~GameObject()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void GameObject::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void GameObject::Update(float delta_second)
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void GameObject::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if(!explosion_flag)
	{
		// オフセット値を基に画像の描画を行う
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, image, TRUE, flip_flag);
	}
}

/// <summary>
/// 終了時処理
/// </summary>
void GameObject::Finalize()
{

}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{

}

//座標取得処理
const Vector2D& GameObject::GetLocation() const
{
	return location;
}

//座標設定処理
void GameObject::SetLocation(const Vector2D location)
{
	this->location = location;
}

//コリジョン取得処理
const Collision& GameObject::GetCollision() const
{
	return collision;
}

//レイヤー取得処理
const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

//可動性取得処理
const bool GameObject::GetMobility() const
{
	return is_mobility;
}

//死亡座標設定処理
void GameObject::SetDeathLocation()
{
	this->death_location = location;
}

//死亡座標固定処理
void GameObject::KeepDeathLocation()
{
	this->explosion_flag = true;
	collision.is_blocking = false;
	location = this->death_location;
}

//プレイヤー座標設定処理
void GameObject::SetPlayerLocation(Vector2D location)
{
	if (player_location.x == 0.0f && player_location.y == 0.0f)
	{
		old_player_location = location;
	}
	player_location = location;
}

//プレイヤーステータス設定処理
void GameObject::SetPlayerStats(PlayerStats stats)
{
	player_stats = stats;
}


//AがBを追尾する処理
Vector2D GameObject::Tracking(Vector2D A, Vector2D B)
{
	Vector2D velocity;	//加速度
	float distance;		//距離

	velocity.x = A.x - B.x;
	velocity.y = A.y - B.y;

	distance = sqrt(pow(velocity.x, 2.0) + pow(velocity.y, 2.0));

	velocity.x /= distance;
	velocity.y /= distance;

	velocity *= -1;

	return velocity;

}

//オブジェクトマネージャー設定処理
const GameObjectManager* GameObject::CheckInstance() const
{
	return object_manager;
}
void GameObject::SetInstance(GameObjectManager* instance)
{
	object_manager = instance;
}

void GameObject::Explosion(float delta_second)
{
	death_timer += delta_second;

	if (death_timer >= 0.08f)
	{
		death_timer = 0.0f;

		if (anim_num < 10)
		{
			anim_num += 1;
		}
		else
		{
			object_manager->CreateGameObject<ExperiencePoints>(location);
			object_manager->DestroyGameObject(this);
		}
	}
}

bool GameObject::GetExplosionFlag()
{
	return this->explosion_flag;
}

void GameObject::DrawExplosion() const
{
	DrawRotaGraphF(location.x, location.y, 0.5, 0.0, explosions[anim_num], TRUE, false);
}