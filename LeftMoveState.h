#pragma once

class PlayerState;
class Stage;
class InputManager;

class LeftMoveState : public PlayerState
{
public:
	LeftMoveState();
	~LeftMoveState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	VECTOR previewPlayerPosition;
	bool needSavePreviw;

	void Animation();
	int animationCount;
};
