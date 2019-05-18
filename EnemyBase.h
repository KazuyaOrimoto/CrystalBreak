//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

//クラスの前方宣言
class ActionManager;
class Score;
class Stage;
class Sphere;
class SoundManager;
class EffectCreater;
class Player;

class EnemyBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	EnemyBase(int sourceModelHandle, VECTOR startPos, ActionManager &actionManager,int addPoint);
	virtual ~EnemyBase();
	virtual void Update(Stage &stage, ActionManager &actionManager) = 0;
	virtual void Draw();
	EnemyBase* Attacked(Player& player);											//攻撃されたときの処理
	IndexPair GetIndexPair();
	Sphere& GetCollisionSphere();
	VECTOR GetPosition();
	bool isActive();
	bool IsAttacking();
	void NextStageCreate();
protected:
	//-----------------------------------------------------------------------------//
	//							プライベート関数(protected)
	//-----------------------------------------------------------------------------//
	void ChangeEnemyIndexPair(ActionManager& actionManager);	//エネミーの要素位置の変更
	virtual void DieEffect() = 0;
	//-----------------------------------------------------------------------------//
	//							プライベート変数(protected)
	//-----------------------------------------------------------------------------//
	bool		needChangeIndex;								//要素位置の変更が必要か
	int			modelHandle;									//エネミーのモデルハンドル
	VECTOR		position;										//エネミーのポジション
	VECTOR		exactlyPosition;								//マップ上でキリがいいポジション
	IndexPair	indexPair;										//エネミーの要素位置
	Score*		score;											//Scoreのインスタンス
	Sphere*		collisionSphere;
	SoundManager* soundManager;
	EffectCreater* effectCreater;
	bool		isAlive = true;									//生きているかのフラグ
	bool attackFlag = false;
	const int addPoint;
};

