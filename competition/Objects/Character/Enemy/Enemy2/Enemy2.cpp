#include "Enemy2.h"

Enemy2::Enemy2()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(20, 20);							//当たり判定の大きさ
	collision.object_type = eObjectType::eEnemy;					//オブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//ぶつかるオブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//ぶつかるオブジェクトのタイプ
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

}

Enemy2::~Enemy2()
{
}

void Enemy2::Initialize()
{
	//　仮敵2のサイズ(大きさ)
	collision.box_size = Vector2D(20.0f, 20.0f);
	//box_size = Vector2D(20.0f, 20.0f);
	// 仮テキの速さ
	speed = 200.0f;

	//画像読み込み
	LoadGraph("Resouce/Images/enemy/cannon.png");
}

void Enemy2::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy2::Draw(const Vector2D&, bool) const
{

	DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);

	//// 仮(白い四角を描画する)
	//Vector2D t1 = location - (collision.box_size / 2.0f);
	//Vector2D br = location + (collision.box_size / 2.0f);
	//// 青色の四角を描画
	//DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(0, 255, 255), TRUE);
	//SetFontSize(15);
	//DrawString(location.x,location.y, "2", GetColor(0, 0, 0), TRUE);
}

void Enemy2::Finalize()
{
}

void Enemy2::OnHitCollision(GameObject* hit_object)
{
}

void Enemy2::Movement(float delta_seconds)
{

	location += velocity * speed * delta_seconds;
}

void Enemy2::Animation()
{
}
