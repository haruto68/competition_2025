#pragma once
#include "../EnemyBase.h"
#include "../Enemy10/Enemy10.h"
#include "../Enemy11/Enemy11.h"

class Boss3 : public EnemyBase
{
private:
    int images[7];
    float atack_interval;

    float shot_timer_2;	    //時間経過2
    float shot_cooldown_2;	//クールタイム2
    float shot_timer_3;	    //時間経過3
    float shot_cooldown_3;	//クールタイム3

    int shot_wave;
    int shot_wave_y;

    float wave_change_count;

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

