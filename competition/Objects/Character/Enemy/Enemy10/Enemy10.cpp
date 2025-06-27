#include "Enemy10.h"

Enemy10::Enemy10()
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
	image = rm->GetImages("Resource/Images/enemy/ship9.png")[0];

	exp_num = 5;
}

Enemy10::~Enemy10()
{
}

void Enemy10::Initialize()
{

	speed = 20.0f;

	//画像読み込み
	image = LoadGraph("Resource/Images/enemy/ship4.png");

	hp = 10.0;

	point.clear();
	point.push_back(Vector2D(600, location.y));
	
	if (location.y < 380)//中心より上
	{
		point.push_back(Vector2D(800, location.y + 150));
		point.push_back(Vector2D(-100, location.y + 150));
	}
	else//中心より下
	{
		point.push_back(Vector2D(800, location.y - 150));
		point.push_back(Vector2D(-100, location.y - 150));
	}

	timar = 0.0f;
	spawn_index = 0;
}

void Enemy10::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy10::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);
	}
}

void Enemy10::Finalize()
{
}

void Enemy10::OnHitCollision(GameObject* hit_object)
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

void Enemy10::Movement(float delta_seconds)
{
	if (move_point >= point.size())
		return;

	Vector2D target = point[move_point];
	Vector2D to_target = target - location;

	// 目標との距離が5以下なら次のポイントへ
	if (to_target.Length() < 5.0f)
	{
		move_point++;
		return;
	}

	// 方向の正規化（目的地への方向）
	Vector2D desired_velocity = to_target.Normalize() * speed;

	// 今のvelocityとdesired_velocityを補間して滑らかにする（慣性っぽく）
	float smooth_factor = 10.0f; // 数値を上げると応答が速くなる（滑らかさ減）
	velocity = Lerp(velocity, desired_velocity, smooth_factor * delta_seconds);

	// 移動
	location += velocity * speed * delta_seconds;
}


void Enemy10::Animation()
{
}

void Enemy10::setClone()
{
	is_first_Enemy = false;
}

Vector2D Enemy10::Lerp(const Vector2D& a, const Vector2D& b, float t)
{
	return a * (1.0f - t) + b * t;
}


