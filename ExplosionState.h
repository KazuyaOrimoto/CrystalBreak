//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class PlayerState;
class Stage;
class InputManager;

class ExplosionState : public PlayerState
{
public:
	ExplosionState();
	~ExplosionState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	int effectCteateCount;
	const float DECREASE_SIZE_NUM = -1.0f;
	const int  EFFECT_START_COUNT = 20;
};

