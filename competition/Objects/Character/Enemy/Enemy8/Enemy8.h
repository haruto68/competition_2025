#pragma once
#include "../EnemyBase.h"

class Enemy8 : public EnemyBase
{
private:

public:
    Enemy8();
    ~Enemy8();

    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject*) override;

public:
    void Movement(float);
    void Animation();
};