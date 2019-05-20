//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class PlayerState;
class Stage;
class InputManager;

class FallState : public PlayerState
{
public:
	FallState();
	~FallState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	float fallSpeed = 4.0f;
};

