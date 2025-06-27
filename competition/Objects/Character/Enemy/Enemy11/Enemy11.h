#pragma once
#include "../EnemyBase.h"
class Enemy11 : public EnemyBase
{
private:
    Vector2D old_velocity;
    Vector2D target;

public:
    Enemy11();
    ~Enemy11();

    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject*) override;

public:
    void Movement(float);
    void Animation();

};

