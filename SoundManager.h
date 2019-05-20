//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class SoundManager
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	static SoundManager* GetInstance();
	static void CreateInstance();
	static void DeleteInstance();
	void PlayBGM();
	void PlayStoneBreak();
	void PlayTakeCrystal();
	void PlayPlayerAttack();
	void PlayPlayerMove();
	void PlayPlayerLanding();
	void PlayEnemyDie();
	void PlayFire();
	void PlayTerror();
	void PlayLaugh();
	void PlayPlayerExplosion();
	void GameEndSound();
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	SoundManager();
	~SoundManager();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	static SoundManager* soundManager;
	int bgmSoundHandle;
	int stoneBrealSoundHandle;
	int takeCrystalSoundHandle;
	int playerAttackSoundHandle;
	int playerMoveSoundHandle;
	int playerLandingSoundHandle;
	int enemyDirSoundHandle;
	int fireSoundHandle;
	int terrorSoundHandle;
	int laughSoundHandle;
	int playerExplosionSoundHandle;
	int gameEndSoundHandle;
};
