#pragma once

class Stage;
class InputManager;
class Player;

class LeftAttackState : public PlayerState
{
public:
	LeftAttackState();
	~LeftAttackState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	int animationCount;
};

