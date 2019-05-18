//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

//クラスの前方宣言
class EnemyBase;
class Player;

class ActionManager
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	ActionManager();
	~ActionManager();
	void InsertEnemyIndexPair(EnemyBase* enemy, IndexPair pair);	//エネミーのポインタと要素位置を挿入する
	void SetPlayerIndexPair(IndexPair pair);						//プレイヤーの位置を変更
	void SetEnemyIndexPair(EnemyBase* enemy, IndexPair pair);		//エネミーの位置の変更
	Action ReturnPlayerAction(Direction playerDirection);		//プレイヤーのやるべきアクションを返す
	Action ReturnEnemyAction(EnemyBase* enemy,Direction enemyDirection);
	void AttackEnemy(IndexPair serchIndex, Player & player);
	void SetCrystalIndexPair(IndexPair indexPair);
	bool CanMovePlayer(IndexPair indexPair);
	void SetMoveEnemyIndexPair(EnemyBase* enemy, IndexPair nextindexPair);
	void EnemyDataClear();
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	bool IsPlayerAttack(IndexPair serchIndex);
	bool IsEnemyAttack(IndexPair serchIndex);
	void DeleteEnemy(EnemyBase* enemy);
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	std::map<EnemyBase*,IndexPair>enemyIndexPairMap;				//エネミーの要素位置のマップ
	std::map<EnemyBase*, IndexPair>nextIndexPairMap;
	std::vector<IndexPair>crystalIndexPair;
	IndexPair playerIndexPair;
	EnemyBase* deleteEnemy;
};

