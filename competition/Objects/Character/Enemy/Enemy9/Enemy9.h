#pragma once
#include "../EnemyBase.h"

class Enemy9 : public EnemyBase
{
private:
    int target;
    bool turn;
    float birth_count;

public:
    Enemy9();
    ~Enemy9();

    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject*) override;

public:
    void Movement(float);
    void Animation();
};