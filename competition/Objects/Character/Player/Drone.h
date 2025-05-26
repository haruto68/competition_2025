#pragma once

#include "../Character.h"
#include"../../Shot/PlayerShot/PlayerShot.h"
#include"PlayerStats.h"
#include <cmath>


class Drone : public Character
{
protected:

private:

public:
	Drone();
	~Drone();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

};