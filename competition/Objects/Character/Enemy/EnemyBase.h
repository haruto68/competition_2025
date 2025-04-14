#pragma once

#include"../Character.h"

class EnemyBase : public Character
{
protected:


public:
    virtual void Initialize() override;
    virtual void Update(float) override;
    virtual void Draw(const Vector2D&, bool) const override;
    virtual void Finalize() override;

    virtual void OnHitCollision(GameObject*) override;

public:
    void Movement(float);
    void Animation();
private:

};