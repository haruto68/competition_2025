#pragma once

#include"../Shot.h"

class PlayerShot : public Shot
{
protected:

private:
	float screen_velocity;		// ÉXÉNÉäÅ[Éìà⁄ìÆó 
	int Color;
	int Shotmode;

public:
	PlayerShot();
	~PlayerShot();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

public:
	Vector2D GetScreenVelocity();
	Vector2D GetVelocity();
	void SetVelocity(Vector2D);

	void Movement(float);
	void Animation();
	void ShotModeChange();
};