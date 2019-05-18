//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class PlayerState;
class Stage;
class InputManager;

class RightMoveState : public PlayerState
{
public:
	RightMoveState();
	~RightMoveState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	void Animation();
	int animationCount;
};

