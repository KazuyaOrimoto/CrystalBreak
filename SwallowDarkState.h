#pragma once

class PlayerState;
class Stage;
class InputManager;

class SwallowDarkState : public PlayerState
{
public:
	SwallowDarkState(VECTOR position);
	~SwallowDarkState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;
private:
	int swallowCount;
	VECTOR swallowPosition;
	const int RANDOM_LIMIT = 10;					//ランダムな値の上限
	const int RANDOM_LOWEST = 10;					//ランダムな値の最低値
	const float DECREASE_SIZE_NUM = -0.1f ;			//吸い込まれてるときに変わるサイズ
	const float FACTOR_NUM = 0.2f;					//吸い込まれるときの移動する大きさの係数
	const int  SWALLOW_END_COUNT= 100;				//吸い込みが終わるまでのカウント数
};

