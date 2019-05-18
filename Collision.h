//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Sphere;
class Capsule;
class Segment;
class FireList;
class Fire;
class BlockBase;
class Stage;
class Player;
class EnemyList;
class EnemyBase;

class Collision
{
public:
	Collision();
	~Collision();
	void CheckCollisionAll(FireList& fireList, Stage& stage, Player& player,EnemyList& enemy);
private:
	void CollisionCheckFireAndBlock();
	void CollisionCheckAttackEnemyAndPlayer(Player& player);
	void CollisionCheckFireAndPlayer(Player& player);
	bool CheckSphereAndSphere(const Sphere& sphereA, const Sphere& sphereB);		//球と球の当たり判定
	bool CheckSphereAndCapsule(const Sphere& sphere, const Capsule& capsule);		//球とカプセルの当たり判定
	bool CheckCapsuleAndCapsule(const Capsule& capsuleA, const Capsule& capsuleB);	//カプセルとカプセルの当たり判定
	FireVector fireListCopy;
	BlockVector blockListCopy;
	EnemyVector enemyListCopy;
};

