//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Stage;
class InputManager;
class Player;


class DownAttackState : public PlayerState
{
public:
	DownAttackState();
	~DownAttackState();

	PlayerState* Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager) override;

private:
	int animationCount;
};

