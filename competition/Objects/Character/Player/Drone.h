#pragma once

#include "../Character.h"
#include"../../Shot/PlayerShot/PlayerShot.h"
#include"PlayerStats.h"


class Drone : public Character
{
protected:

private:
	int Color;
	float rotation_angle;
	float shot_timer;
	float SHOT_INTERVAL;
	std::vector<int> drone_image;
	float image_rotation;
	int soundseffect;
	float death_count;
	bool death_flag;
	PlayerStats* player_stats_ptr;



public:

public:
	Drone();
	~Drone();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

public:
	// ドローン用にプレイヤーの現在のステータスのコピーを設定します
	void SetPlayerStats(PlayerStats* player_stats) // 引数をポインタに変更
	{
		this->player_stats_ptr = player_stats;
	}
	void Animation(float);

};