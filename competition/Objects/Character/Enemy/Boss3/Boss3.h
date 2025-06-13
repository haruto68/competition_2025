#pragma once
#include "../EnemyBase.h"

class Boss3 : public EnemyBase
{
private:
    int images[7];

public:
    Boss3();
    ~Boss3();

    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject*) override;

public:
    void Movement(float);
    void Animation();

    int GetBoss3Hp();
    float GetBoss3DeathCount();
    bool GetDeathFlag();
};

