//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Stage;
class InputManager;
class Player;

class BombAttackState : public PlayerState
{
public:
	BombAttackState();
	~BombAttackState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;
private:
	int animationCount;
	bool createdEffect;
};

