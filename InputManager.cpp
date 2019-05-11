#include "Common.h"
#include "InputManager.h"

InputManager* InputManager::inputManager = NULL;
XINPUT_STATE InputManager::input = {};

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
InputManager::InputManager()
{
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
InputManager::~InputManager()
{
}

//-----------------------------------------------------------------------------//
//								インスタンスを返す
//-----------------------------------------------------------------------------//
InputManager* InputManager::GetInstance()
{
	return inputManager;
}

//-----------------------------------------------------------------------------//
//								インスタンスを生成
//-----------------------------------------------------------------------------//
void InputManager::CreateInstance()
{
	if (inputManager == NULL)
	{
		inputManager = new InputManager();
	}
}

//-----------------------------------------------------------------------------//
//								インスタンスを削除
//-----------------------------------------------------------------------------//
void InputManager::DeleteInstance()
{
	if (inputManager != NULL)
	{
		delete(inputManager);
	}
}

//-----------------------------------------------------------------------------//
//								キーの入力情報更新
//-----------------------------------------------------------------------------//
void InputManager::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
}

//-----------------------------------------------------------------------------//
//						プレイヤーが右に移動するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerRightMove()
{
	if (rightThumb < input.ThumbLX)
	{
		return true;
	}
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが左に移動するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerLeftMove()
{
	if (input.ThumbLX < leftThumb)
	{
		return true;
	}
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが右に攻撃するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerRightAttack()
{
	if (rightThumb < input.ThumbLX || input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])
	{
		if (input.Buttons[XINPUT_BUTTON_A])
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが左に攻撃するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerLeftAttack()
{
	if (input.ThumbLX < leftThumb || input.Buttons[XINPUT_BUTTON_DPAD_LEFT])
	{
		if (input.Buttons[XINPUT_BUTTON_A])
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが上に攻撃するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerUpAttack()
{
	if (rightThumb < input.ThumbLY || input.Buttons[XINPUT_BUTTON_DPAD_UP])
	{
		if (input.Buttons[XINPUT_BUTTON_A])
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが下に攻撃するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerDownAttack()
{
	if (input.ThumbLY < leftThumb || input.Buttons[XINPUT_BUTTON_DPAD_DOWN])
	{
		if (input.Buttons[XINPUT_BUTTON_A])
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが攻撃するかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerAttackOnly()
{
	if (input.Buttons[XINPUT_BUTTON_A])
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが爆弾を使うかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PlayerUseBomb()
{
	if (input.LeftTrigger >= 200 || input.RightTrigger >= 200)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						Startボタンが押されたかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PushStartButton()
{
	if (input.Buttons[XINPUT_BUTTON_START])
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//						何かキーが押されているかどうか
//-----------------------------------------------------------------------------//
bool InputManager::PushAnyKey()
{
	for (int i = 0;i < 16;i++)
	{
		if (input.Buttons[i])
		{
			return false;
		}
	}
	if (input.LeftTrigger)
	{
		return false;
	}
	if (input.RightTrigger)
	{
		return false;
	}
	return true;
}
