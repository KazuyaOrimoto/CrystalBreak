#pragma once

class Stage;
class InputManager;
class Player;

class UpAttackState : public PlayerState 
{
public:
	UpAttackState();
	~UpAttackState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	int animationCount;
};

