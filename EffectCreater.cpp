//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "EffectCreater.h"

EffectCreater* EffectCreater::effectCreater = NULL;

//-----------------------------------------------------------------------------//
//								インスタンスを渡す
//-----------------------------------------------------------------------------//
EffectCreater * EffectCreater::GetInstance()
{
	return effectCreater;
}

//-----------------------------------------------------------------------------//
//								インスタンスを作る
//-----------------------------------------------------------------------------//
void EffectCreater::CreateInstance()
{
	if (effectCreater == NULL)
	{
		effectCreater = new EffectCreater();
	}
}

void EffectCreater::DeleteInstance()
{
	if (effectCreater != NULL)
	{
		delete(effectCreater);
	}
}

void EffectCreater::EffectLoad()
{
	blockBreakEffect = LoadEffekseerEffect("Effect/BlockBreak.efk");
	fireEffect = LoadEffekseerEffect("Effect/FireEffect.efk");
	crashFireEffect = LoadEffekseerEffect("Effect/CrashFireEffect.efk");
	centerFireEffect = LoadEffekseerEffect("Effect/FireCenter.efk");
	crystalEffect = LoadEffekseerEffect("Effect/CristalEffect_Blue.efk");
	upperAttackEffect = LoadEffekseerEffect("Effect/AttackEffect1.efk");
	rightAttackEffect = LoadEffekseerEffect("Effect/AttackEffect2.efk");
	leftAttackEffect = LoadEffekseerEffect("Effect/AttackEffect3.efk");
	fireBlockBreakEffect = LoadEffekseerEffect("Effect/FireBlockBreakEffect.efk");
	underAttackEffect = LoadEffekseerEffect("Effect/AttackEffect4.efk");
	darkEffect = LoadEffekseerEffect("Effect/DarkEffect.efk");
	swallowEffect = LoadEffekseerEffect("Effect/SwallowEffect.efk");
	playerPowerEffect = LoadEffekseerEffect("Effect/PlayerPowerEffect.efk");
	bombEffect = LoadEffekseerEffect("Effect/BombEffect.efk");
	playerExplosionEffect = LoadEffekseerEffect("Effect/PlayerDie.efk");
	playerBarrierEffect = LoadEffekseerEffect("Effect/PlayerBarrier.efk");
	playerBarrierBreakEffect = LoadEffekseerEffect("Effect/PlayerBarrierBreak.efk");
	crystalBreakEffect = LoadEffekseerEffect("Effect/CrystalBreakEffect.efk");
	ItemEffect = LoadEffekseerEffect("Effect/ItemEffect.efk");
	barrierItemEffect = LoadEffekseerEffect("Effect/BarrierItemEffect.efk");
	bombItemEffect = LoadEffekseerEffect("Effect/BombItem.efk");
}

void EffectCreater::AllStopEffect()
{
}

void EffectCreater::InitEffectHandle()
{

}

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
EffectCreater::EffectCreater()
	:ad(0)
{
	playingEffectHandle = 0;
	blockBreakEffect = 0;
	fireBlockBreakEffect = 0;
	fireEffect = 0;
	crashFireEffect = 0;
	centerFireEffect = 0;
	crystalEffect = 0;
	crystalBreakEffect = 0;
	upperAttackEffect = 0;
	rightAttackEffect = 0;
	leftAttackEffect = 0;
	underAttackEffect = 0;
	darkEffect = 0;
	swallowEffect = 0;
	playerPowerEffect = 0;
	bombEffect = 0;
	playerExplosionEffect = 0;
	playerBarrierEffect = 0;
	playerBarrierBreakEffect = 0;
	ItemEffect = 0;
	ItemEffectPlayingHandle = 0;
	barrierItemEffect = 0;
	bombItemEffect = 0;
	playerBarrierEffectPlayingHandle = 0;

	//DirectX11のバージョンを指定
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(20000) == -1)
	{
		DxLib_End();
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	//EffekseerSyncronizDxlib();
	EffectLoad();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
EffectCreater::~EffectCreater()
{
	DeleteEffekseerEffect(blockBreakEffect);
	DeleteEffekseerEffect(fireEffect);
	DeleteEffekseerEffect(crashFireEffect);
	DeleteEffekseerEffect(centerFireEffect);
	DeleteEffekseerEffect(crystalEffect);
	DeleteEffekseerEffect(upperAttackEffect);
	DeleteEffekseerEffect(rightAttackEffect);
	DeleteEffekseerEffect(leftAttackEffect);
	DeleteEffekseerEffect(fireBlockBreakEffect);
	DeleteEffekseerEffect(underAttackEffect);
	DeleteEffekseerEffect(darkEffect);
	DeleteEffekseerEffect(swallowEffect);
	DeleteEffekseerEffect(playerPowerEffect);
	DeleteEffekseerEffect(bombEffect);
	DeleteEffekseerEffect(playerExplosionEffect);
	DeleteEffekseerEffect(playerBarrierEffect);
	DeleteEffekseerEffect(playerBarrierBreakEffect);
	DeleteEffekseerEffect(crystalBreakEffect);
	DeleteEffekseerEffect(ItemEffect);
	DeleteEffekseerEffect(barrierItemEffect);
	DeleteEffekseerEffect(bombItemEffect);
}

//-----------------------------------------------------------------------------//
//							ブロック破壊時のエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateBreakBlockEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(blockBreakEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//							火の玉のエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateFireEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(fireEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//						火の玉が壊れるときのエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateCrashFireEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(crashFireEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//							クリスタルのエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateCrystalEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(crystalEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//						クリスタルを取った時のエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateTakeCrystalEffect(VECTOR Position)
{

	playingEffectHandle = PlayEffekseer3DEffect(crystalBreakEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//					プレイヤーが上に攻撃するときのエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateUpperAttackEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(upperAttackEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//					プレイヤーが右に攻撃するときのエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateRightAttackEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(rightAttackEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

//-----------------------------------------------------------------------------//
//					プレイヤーが左に攻撃するときのエフェクト
//-----------------------------------------------------------------------------//
void EffectCreater::CreateLeftAttackEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(leftAttackEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

void EffectCreater::CreateFireBlockBreakEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(fireBlockBreakEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

void EffectCreater::CreateUnderAttackEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(underAttackEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

void EffectCreater::CreateDrakEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(darkEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, Position.z);
}

void EffectCreater::CreateSwallowEffect(VECTOR Position)
{
	playingEffectHandle = PlayEffekseer3DEffect(swallowEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y, 0);
}

void EffectCreater::CreatePlayerPowerEffect(VECTOR Position, int createEffectNum)
{
	for (int i = 0; i < createEffectNum; i++)
	{
		playingEffectHandle = PlayEffekseer3DEffect(playerPowerEffect);
		SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x - ad, Position.y - 4, 0);
	}
}

void EffectCreater::CreateBombEffect(VECTOR position)
{
	playingEffectHandle = PlayEffekseer3DEffect(bombEffect);
	playingList.push_back(playingEffectHandle);

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x - ad, position.y, -10);
}

void EffectCreater::CreatePlayerExplosionEffect(VECTOR position)
{
	playingEffectHandle = PlayEffekseer3DEffect(playerExplosionEffect);
	playingList.push_back(playingEffectHandle);

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x - ad, position.y, -10);
}

void EffectCreater::CreatePlayerBarrierEffect(VECTOR position)
{
	playerBarrierEffectPlayingHandle = PlayEffekseer3DEffect(playerBarrierEffect);
	playingList.push_back(playingEffectHandle);

	SetPosPlayingEffekseer3DEffect(playerBarrierEffectPlayingHandle, position.x - ad, position.y - 3, -10);
}

void EffectCreater::PlayerBarrierEffectSetPosition(VECTOR position)
{
	if (SetPosPlayingEffekseer3DEffect(playerBarrierEffectPlayingHandle, position.x - ad, position.y - 3, -10))
	{
		CreatePlayerBarrierEffect(position);
		SetPosPlayingEffekseer3DEffect(playerBarrierEffectPlayingHandle, position.x - ad, position.y - 3, -10);
	}
}

void EffectCreater::PlayerBarrierEffectEnd(VECTOR position)
{
	StopEffekseer3DEffect(playerBarrierEffectPlayingHandle);
	playingEffectHandle = PlayEffekseer3DEffect(playerBarrierBreakEffect);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x - ad, position.y - 3, -10);
}

int EffectCreater::PlayItemEffect(VECTOR position)
{
	ItemEffectPlayingHandle = PlayEffekseer3DEffect(ItemEffect);
	playingList.push_back(playingEffectHandle);

	SetPosPlayingEffekseer3DEffect(ItemEffectPlayingHandle, position.x - ad, position.y - 3, -10);
	return ItemEffectPlayingHandle;
}

void EffectCreater::StopEffect(int playingHandle)
{
	StopEffekseer3DEffect(playingHandle);
}

int EffectCreater::CreateBarrierItemEffect(VECTOR position)
{
	ItemEffectPlayingHandle = PlayEffekseer3DEffect(barrierItemEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(ItemEffectPlayingHandle, position.x - ad, position.y, 0);
	return ItemEffectPlayingHandle;
}

int EffectCreater::CreateBombItemEffect(VECTOR position)
{
	ItemEffectPlayingHandle = PlayEffekseer3DEffect(bombItemEffect);
	playingList.push_back(playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(ItemEffectPlayingHandle, position.x - ad, position.y, 0);
	return ItemEffectPlayingHandle;
}

void EffectCreater::SetScale(VECTOR scale)
{
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

