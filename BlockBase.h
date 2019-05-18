//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Sphere;
class EffectCreater;
class SoundManager;
class Player;

class BlockBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	BlockBase(int sourceModelHandle, VECTOR startPos);
	virtual ~BlockBase();
	virtual void Update() = 0;
	virtual void Attacked(Player & player) = 0;
	virtual void Draw();
	bool IsActive();
	BlockName GetBlockName();
	IndexPair GetIndexPair();
	VECTOR GetPosition();
	Sphere& GetCollisionSphere();
	virtual void OnBlock(Player& player) = 0;
	void NextStageCreate();
	bool needDrawModel(VECTOR position);
protected:
	//-----------------------------------------------------------------------------//
	//							プライベート変数(protected)
	//-----------------------------------------------------------------------------//
	int modelHandle;
	VECTOR pos;
	BlockName blockName;
	IndexPair indexPair;
	bool active;
	Sphere* collisionSphere;
	EffectCreater* effect;
	SoundManager* soundManager;
};
