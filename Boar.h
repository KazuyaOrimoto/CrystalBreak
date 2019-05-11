#pragma once

//クラスの前方宣言
class EnemyBase;
class Stage;

class Boar : public EnemyBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	Boar(int sourceModelHandle, VECTOR startPos, ActionManager &actionManager);
	~Boar();
	void Update(Stage &stage, ActionManager &actionManager)override;
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	void Move(Stage &stage,ActionManager& action);								//移動全般を管理する関数
	void RightMove();										//右移動用の関数
	void LeftMove();										//左移動用の関数
	void MoveEnd();											//1マス分移動し終えたときに呼ばれる関数
	void ActionDecision(ActionManager& actionManager);		//アクションを決めるタイミングで呼ぶ
	void DecisionMoveDirection(Stage &stage, ActionManager& action);				//移動方向を決める
	void Fall();											//落下処理
	void DieEffect();
	void DoRightAttack();
	void DoLeftAttack();
	void ChangeDirection();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	bool		isRightMoving		= false;				//右移動中のフラグ
	bool		isLeftMoving		= false;				//左移動中のフラグ
	bool		isFalling			= false;				//落下中
	bool		needChangeIndex		= false;				//プレイヤーの要素位置を変えるかどうかの判定用
	bool		actionFlag			= false;				//アクションを起こすときのフラグ
	bool		needChangeDirection = false;				//向きを変える必要があるか
	Direction	moveDirection		= RIGHT;				//移動方向
	VECTOR rotation;
	enum Action action;										//エネミーのアクション
	bool rightAttackFlag;
	bool leftAttackFlag;
	int animationCount;
};
