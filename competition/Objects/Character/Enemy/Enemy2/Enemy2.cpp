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

	hp = 2.0;
	
	// 音源取得(0: 敵が破壊時の音 1: 敵が弾を撃った時の音)
	soundseffect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemybreak.mp3");
	soundseffect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemyshot.mp3");
	ChangeVolumeSoundMem(sound_volume[0], soundseffect[0]);
	ChangeVolumeSoundMem(sound_volume[1], soundseffect[1]);
}

void Enemy2::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	float shot_cooldown = 0.5f;

	//時間経過
	shot_timer += delta_seconds;

	if (shot_timer >= shot_cooldown)
	{
		EnemyShot* shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		// shot->SetShotType(eEnemy3);
		// PlaySoundMem(soundseffect1, DX_PLAYTYPE_BACK, TRUE);
		// PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);s
		if (!trans)
			shot->SetShotType(eEnemy2);
		else
			shot->SetShotType(eEnemy3);

		PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);

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
	// DeleteSoundMem(soundseffect1);
	// DeleteSoundMem(soundseffect);
	// DeleteSoundMem(soundseffect[0]);
	// DeleteSoundMem(soundseffect[1]);
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
		PlaySoundMem(soundseffect[0], DX_PLAYTYPE_BACK, TRUE);
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
	if (hp <= 0.0)
	{
		object_manager->CreateGameObject< ExperiencePoints>(this->location);
		object_manager->DestroyGameObject(this);
		PlaySoundMem(soundseffect[0], DX_PLAYTYPE_BACK, TRUE);
		// PlaySoundMem(soundseffect, DX_PLAYTYPE_BACK, TRUE);
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
