#pragma once

//クラスの前方宣言
class EnemyBase;
class Stage;

class FireFly : public EnemyBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	FireFly(int sourceModelHandle, VECTOR startPos, ActionManager &actionManager);
	~FireFly();
	void Update(Stage &stage, ActionManager &actionManager)override;
private:
	void DieEffect();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	int time = 0;
	
};

