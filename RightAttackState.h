//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Stage;
class InputManager;
class Player;

class RightAttackState : public PlayerState
{
public:
	RightAttackState();
	~RightAttackState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	int animationCount;
};

