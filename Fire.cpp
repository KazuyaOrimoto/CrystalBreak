//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "Fire.h"
#include "Sphere.h"
#include "EffectCreater.h"
#include "SoundManager.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
Fire::Fire(VECTOR pos, Direction dir)
{
	position = pos;
	if (dir == RIGHT)
	{
		moveSpeed = FIRE_MOVE_SPEED;
	}
	else if (dir == LEFT)
	{
		moveSpeed = -FIRE_MOVE_SPEED;
	}
	collisionSphere = new Sphere();
	collisionSphere->radius = FIRE_MAGNIFICATION_RATE;
	active = true;
	effectCreater = EffectCreater::GetInstance();
	soundManager = SoundManager::GetInstance();
	firingCount = 0;
	fireCount = 0;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
Fire::~Fire()
{
	delete(collisionSphere);
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void Fire::Update()
{
	if (firingCount > FIRING_COUNT_TIME)
	{
		//サウンドを鳴らし終わっていないなら
		if (!soundPlayed)
		{
			soundManager->PlayFire(); 
			soundPlayed = true;
		}
		position.x += moveSpeed;
		collisionSphere->centerPos = position;
	}
	else
	{
		firingCount++;
		collisionSphere->centerPos = position;
	}
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void Fire::Draw()
{
	fireCount++;
	if (fireCount > 1)
	{
		effectCreater->CreateFireEffect(position);
		fireCount = 0;
	}
	if (active == false)
	{
		effectCreater->CreateCrashFireEffect(position);
	}
}

void Fire::DestroyFire()
{
	active = false;
}

Sphere& Fire::GetCollisionSphere()
{
	return *collisionSphere;
}

bool Fire::IsActive()
{
	return active;
}

Fire * Fire::GetInstance()
{
	return this;
}

VECTOR Fire::GetPosition()
{
	return position;
}
