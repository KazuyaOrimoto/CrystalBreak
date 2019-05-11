#pragma once

//クラスの前方宣言
class EnemyBase;
class ActionManager;
class Stage;

class EnemyList
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	EnemyList(ActionManager &actionManager,Stage & stage);
	~EnemyList();
	void Update(Stage &stage,ActionManager &actionManager);
	void Draw();
	EnemyVector GetEnemyList();
	void NextStageCreate(Stage& stage, ActionManager& actionManager);
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	void CreateEnemy(ActionManager &actionManager);
	bool needDrawModel(VECTOR position);
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	EnemyVector enemyList;
	int fireFlyModelHandle;
	int boarModelHandle;
	int map[BLOCK_NUM_Y][BLOCK_NUM_X];
};

