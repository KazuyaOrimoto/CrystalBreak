//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Stage;
class InputManager;
class Player;
class SoundManager;
class EffectCreater;
class ActionManager;

class PlayerState
{
public:
	PlayerState();
	~PlayerState();

	virtual PlayerState* Update(Player& player,Stage& stage,InputManager& inputManager, ActionManager& actionManager) = 0;
	static PlayerState* InitPlayerState();

	VECTOR GetMoveAmount();
	VECTOR GetRotation();
	VECTOR GetScaleAmount();
	VECTOR GetAnimationPosition();
	Direction GetDirecion();

	void SetRotation(VECTOR rotation);
	void passPreviewDirection(Direction dir);

protected:

	SoundManager* soundManager;
	EffectCreater* effectCreater;

	void ResetAmount();

	VECTOR playerMoveAmount;
	VECTOR playerRotation;
	VECTOR playerScaleAmount;
	VECTOR playerAnimationPosition;

	Direction previewDirection;
};
