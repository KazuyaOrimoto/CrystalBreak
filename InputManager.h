//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class InputManager
{
public:
	//-----------------------------------------------------------------------------//
	//							静的パブリック関数
	//-----------------------------------------------------------------------------//
	static InputManager* GetInstance();
	static void CreateInstance();
	static void DeleteInstance();
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	void Update();
	bool PlayerRightMove();
	bool PlayerLeftMove();
	bool PlayerRightAttack();
	bool PlayerLeftAttack();
	bool PlayerUpAttack();
	bool PlayerDownAttack();
	bool PlayerAttackOnly();
	bool PlayerUseBomb();
	bool PushStartButton();
	bool PushAnyKey();
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	InputManager();
	~InputManager();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	static InputManager* inputManager;
	static XINPUT_STATE input;
	static const int rightThumb = 25000;
	static const int leftThumb = -25000;
};

