#pragma once

#include"Collision.h"


class GameObject
{
protected:
	Vector2D location;				//座標
	Collision collision;			//コリジョン
	int image;						//画像
	unsigned char z_layer;			//レイヤー
	bool is_mobility;				//可動性
	Vector2D player_location;		//プレイヤー座標
	Vector2D old_player_location;	//生成時プレイヤー座標

public:
	GameObject();
	~GameObject();

public:
	virtual void Initialize();
	virtual void Update(float);
	virtual void Draw(const Vector2D&, bool) const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObject*);	//当たり判定通知処理
	const Vector2D& GetLocation() const;		//座標取得処理
	void SetLocation(const Vector2D);			//座標設定処理
	const Collision& GetCollision() const;		//コリジョン取得処理
	const unsigned char GetZLayer() const;		//レイヤー取得処理
	const bool GetMobility() const;				//可動性取得処理

	void SetPlayerLocation(Vector2D location);	//プレイヤー座標設定処理
	Vector2D Tracking(Vector2D A, Vector2D B);	//AがBを追尾する処理

};