#pragma once

using namespace Effekseer;

class EffectCreater
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	static EffectCreater* GetInstance();
	static void CreateInstance();
	static void DeleteInstance();
	void EffectLoad();
	void AllStopEffect();

	void CreateBreakBlockEffect(VECTOR Position);
	void CreateFireEffect(VECTOR Position);
	void CreateCrashFireEffect(VECTOR Position);
	void CreateCrystalEffect(VECTOR Position);
	void CreateTakeCrystalEffect(VECTOR Position);
	void CreateUpperAttackEffect(VECTOR Position);
	void CreateRightAttackEffect(VECTOR Position);
	void CreateLeftAttackEffect(VECTOR Position);
	void CreateFireBlockBreakEffect(VECTOR Position);
	void CreateUnderAttackEffect(VECTOR Position);
	void CreateDrakEffect(VECTOR Position);
	void CreateSwallowEffect(VECTOR Position);
	void CreatePlayerPowerEffect(VECTOR Position, int createEffectNum);
	void CreateBombEffect(VECTOR position);
	void CreatePlayerExplosionEffect(VECTOR position);
	void CreatePlayerBarrierEffect(VECTOR position);
	void PlayerBarrierEffectSetPosition(VECTOR position);
	void PlayerBarrierEffectEnd(VECTOR position);
	int PlayItemEffect(VECTOR position);
	void StopEffect(int playingHandle);
	int CreateBarrierItemEffect(VECTOR position);
	int CreateBombItemEffect(VECTOR position);
	void SetScale(VECTOR scale);

private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	EffectCreater();
	~EffectCreater();
	void InitEffectHandle();

	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	static EffectCreater* effectCreater;
	int playingEffectHandle;
	int blockBreakEffect;
	int fireBlockBreakEffect;
	int fireEffect;
	int crashFireEffect;
	int centerFireEffect;
	int crystalEffect;
	int crystalBreakEffect;
	int upperAttackEffect;
	int rightAttackEffect;
	int leftAttackEffect;
	int underAttackEffect;
	int darkEffect;
	int swallowEffect;
	int playerPowerEffect;
	int bombEffect;
	int playerExplosionEffect;
	int playerBarrierEffect;
	int playerBarrierBreakEffect;
	int ItemEffect;
	int ItemEffectPlayingHandle;
	int barrierItemEffect;
	int bombItemEffect;

	int playerBarrierEffectPlayingHandle;
	const int ad;
	std::vector<int> playingList;
};

