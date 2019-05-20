//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Sphere;
class EffectCreater;
class SoundManager;

class Fire
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	Fire(VECTOR pos,Direction dir);
	~Fire();
	void Update();
	void Draw();
	void DestroyFire();
	Sphere& GetCollisionSphere();
	bool IsActive();
	Fire* GetInstance();
	VECTOR GetPosition();
private:
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	VECTOR position;
	float moveSpeed;
	Sphere* collisionSphere;
	EffectCreater* effectCreater;
	SoundManager* soundManager;
	bool active = true;
	int firingCount;	//発射するまでのカウント
	bool soundPlayed = false;
	int fireCount;
};

