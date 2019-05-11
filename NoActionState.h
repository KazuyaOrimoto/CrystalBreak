#pragma once

class PlayerState;
class Stage;
class InputManager;

class NoActionState : public PlayerState
{
public:
	NoActionState();
	~NoActionState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;
};
