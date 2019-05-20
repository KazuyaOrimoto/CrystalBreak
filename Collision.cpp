//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "Collision.h"
#include "Capsule.h"
#include "Sphere.h"
#include "Stage.h"
#include "FireList.h"
#include "Fire.h"
#include "BlockBase.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EnemyList.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::CheckCollisionAll(FireList& fireList, Stage& stage, Player& player, EnemyList& enemy)
{
	fireListCopy = fireList.GetFireList();
	blockListCopy = stage.GetBlockList();
	enemyListCopy = enemy.GetEnemyList();
	CollisionCheckFireAndBlock();
	CollisionCheckAttackEnemyAndPlayer(player);
	CollisionCheckFireAndPlayer(player);
}

void Collision::CollisionCheckFireAndBlock()
{
	for (auto itr1 : fireListCopy)
	{
		for (auto itr2 : blockListCopy)
		{
			if (CheckSphereAndSphere(itr1->GetCollisionSphere(), itr2->GetCollisionSphere()))
			{
				if (itr2->GetBlockName() != FIRE_CUBE)
				{
					itr1->DestroyFire();
					break;
				}
			}
		}
	}
}

void Collision::CollisionCheckAttackEnemyAndPlayer(Player& player)
{
	bool playerAttacked = false;
	for (auto itr : enemyListCopy)
	{
		if (itr->IsAttacking())
		{
			playerAttacked = CheckSphereAndSphere(itr->GetCollisionSphere(), player.GetCollisionSphere());
			if (playerAttacked)
			{
				player.Attacked();
				break;
			}
		}
	}
}

void Collision::CollisionCheckFireAndPlayer(Player& player)
{
	bool playerAttacked = false;
	for (auto itr : fireListCopy)
	{
		playerAttacked = CheckSphereAndSphere(itr->GetCollisionSphere(), player.GetCollisionSphere());
		if (playerAttacked)
		{
			player.Attacked();
			break;
		}
	}
}

bool Collision::CheckSphereAndSphere(const Sphere& sphereA, const Sphere& sphereB)
{
	VECTOR sub = VSub(sphereA.centerPos, sphereB.centerPos);
	float distance = VSize(sub);
	float radiusSum = sphereA.radius + sphereB.radius;
	if (distance < radiusSum)
	{
		return true;
	}
	return false;
}

bool Collision::CheckSphereAndCapsule(const Sphere& sphere, const Capsule& capsule)
{
	float distance = Segment_Point_MinLength(capsule.segment.startPos, capsule.segment.endPos, sphere.centerPos);
	float radiusSum = sphere.radius + capsule.radius;
	float radiusSumSquare = radiusSum * radiusSum;
	if (distance < radiusSumSquare)
	{
		return true;
	}
	return false;
}

bool Collision::CheckCapsuleAndCapsule(const Capsule& capsuleA, const Capsule& capsuleB)
{
	float distance = Segment_Segment_MinLength(capsuleA.segment.startPos, capsuleA.segment.endPos, capsuleB.segment.startPos, capsuleB.segment.endPos);
	float radiusSum = capsuleA.radius + capsuleB.radius;
	float radiusSumSquare = radiusSum * radiusSum;
	if (distance < radiusSumSquare)
	{
		return true;
	}
	return false;
}
