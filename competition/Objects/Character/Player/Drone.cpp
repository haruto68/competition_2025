#include "Drone.h"
#include"../../../Utility/InputManager.h"
#include "UserTemplate.h"

Drone::Drone() : 
	rotation_angle(0.0f),
	shot_timer(0.3f),
	SHOT_INTERVAL(0.5f),
	image_rotation(0.0f),
	death_count(255),
	death_flag(false)
{

}

Drone::~Drone()
{

}

void Drone::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(15, 15);
	collision.object_type = eObjectType::eBlockDrone;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eEnemyShot);
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;
	// 音源取得
	soundseffect = rm->GetSounds("Resource/Sounds/SoundsEffect/Player/Drone_dead.mp3");

	drone_image = rm->GetImages("Resource/Images/player/Drone.png", 1, 1, 1, 16, 16);

	image = drone_image[0];
}

void Drone::Update(float delta_seconds)
{
	if (shot_timer > 0.0f)
	{
		shot_timer -= delta_seconds;
	}

	//InputManager* input = InputManager::GetInstance();
	//if ((InputManager::GetInstance()->GetButton(13) || CheckHitKey(KEY_INPUT_B)) && shot_timer <= 0.0f)
	if (shot_timer <= 0.0f)	//自動で撃つ場合
	{
		PlayerShot* shot = object_manager->CreateGameObject<PlayerShot>(this->location);

		shot_timer = SHOT_INTERVAL;
		player_stats.shot_speed = SHOT_INTERVAL;
	}

	Animation(delta_seconds);
	if (death_flag == true)
	{
		
		if (player_stats.drone_hp <= 0.0f)
		{
			
			death_count -= (delta_seconds * 1.0f);
			transparency -= 1;
		}
		if (death_count <= 0.0)
		{
			death_flag = false;
		}
	}

}

void Drone::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
	DrawRotaGraphF(location.x, location.y, 2.0, image_rotation, image, TRUE, this->flip_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//__super::Draw(0.0f, this->flip_flag);
	//DrawCircle(location.x, location.y, 12, GetColor(243, 136, 19), true);
}

void Drone::Finalize()
{

}

void Drone::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
		break;
	case eEnemy:
		death_flag = true;
		if (player_stats_ptr)
		{
			player_stats_ptr->drone_hp--;
		}
		PlaySoundMem(soundseffect, DX_PLAYTYPE_BACK, TRUE);
		break;
	case ePlayerShot:
		break;
	case eEnemyShot:
		death_flag = true;
		if (player_stats_ptr)
		{
			player_stats_ptr->drone_hp--;
		}
		PlaySoundMem(soundseffect, DX_PLAYTYPE_BACK, TRUE);
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Drone::Animation(float delta_seconds)
{
	image_rotation = (image_rotation + delta_seconds);
	if (image_rotation >= 360.0f)
	{
		image_rotation = 0;
	}
}
