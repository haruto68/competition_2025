#pragma once

#include "../Character.h"
#include"../../Shot/PlayerShot/PlayerShot.h"
#include"PlayerStats.h"


class Drone : public Character
{
protected:

private:
	int Color;
	struct PlayerStats player_stats_copy;

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
	// �h���[���p�Ƀv���C���[�̌��݂̃X�e�[�^�X�̃R�s�[��ݒ肵�܂�
	void SetPlayerStatsCopy(const PlayerStats player_stats)
	{
		this->player_stats_copy = player_stats;
	}
	// �v���C���[�ɂ���ČĂяo����A�h���[���ɒe�𔭎˂����܂�
	void Shoot();
};