//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "SoundManager.h"

SoundManager* SoundManager::soundManager = NULL;

//-----------------------------------------------------------------------------//
//								インスタンスを渡す
//-----------------------------------------------------------------------------//
SoundManager * SoundManager::GetInstance()
{
	return soundManager;
}

//-----------------------------------------------------------------------------//
//								インスタンスを作る
//-----------------------------------------------------------------------------//
void SoundManager::CreateInstance()
{
	if (soundManager == NULL)
	{
		soundManager = new SoundManager();
	}
}

void SoundManager::DeleteInstance()
{
	if (soundManager != NULL)
	{
		delete(soundManager);
	}
}

void SoundManager::PlayBGM()
{
	//BGMが再生中じゃないなら
	if (!CheckSoundMem(bgmSoundHandle))
	{
		PlaySoundMem(bgmSoundHandle,DX_PLAYTYPE_LOOP,TRUE);
	}
}

void SoundManager::PlayStoneBreak()
{
	PlaySoundMem(stoneBrealSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayTakeCrystal()
{
	PlaySoundMem(takeCrystalSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayPlayerAttack()
{
	PlaySoundMem(playerAttackSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayPlayerMove()
{
	PlaySoundMem(playerMoveSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayPlayerLanding()
{
	PlaySoundMem(playerLandingSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayEnemyDie()
{
	PlaySoundMem(takeCrystalSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayFire()
{
	PlaySoundMem(fireSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayTerror()
{
	PlaySoundMem(terrorSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayLaugh()
{
	PlaySoundMem(laughSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::PlayPlayerExplosion()
{
	PlaySoundMem(playerExplosionSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::GameEndSound()
{
	PlaySoundMem(gameEndSoundHandle, DX_PLAYTYPE_BACK, TRUE);
	StopSoundMem(bgmSoundHandle);
}

SoundManager::SoundManager()
{
	bgmSoundHandle = LoadSoundMem("Sound/BGM.mp3");
	ChangeVolumeSoundMem(255 * 30 / 100, bgmSoundHandle);
	stoneBrealSoundHandle = LoadSoundMem("Sound/StoneBreak1.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, stoneBrealSoundHandle);
	takeCrystalSoundHandle = LoadSoundMem("Sound/GlassBreak.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, takeCrystalSoundHandle);
	playerAttackSoundHandle = LoadSoundMem("Sound/PlayerAttack.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, playerAttackSoundHandle);
	enemyDirSoundHandle = LoadSoundMem("Sound/EnemyDie2.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, enemyDirSoundHandle);
	fireSoundHandle = LoadSoundMem("Sound/Fire.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, fireSoundHandle);
	playerMoveSoundHandle = LoadSoundMem("Sound/PlayerMove.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, playerMoveSoundHandle);
	playerLandingSoundHandle = LoadSoundMem("Sound/puyon1.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, playerLandingSoundHandle);
	terrorSoundHandle = LoadSoundMem("Sound/fear1.mp3");
	ChangeVolumeSoundMem(255 * 70 / 100, terrorSoundHandle);
	laughSoundHandle = LoadSoundMem("Sound/laugh.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, laughSoundHandle);
	playerExplosionSoundHandle = LoadSoundMem("Sound/strange_wave.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, playerExplosionSoundHandle);
	gameEndSoundHandle = LoadSoundMem("Sound/Phrase05-1.mp3");
	ChangeVolumeSoundMem(255 * 60 / 100, gameEndSoundHandle);
}

SoundManager::~SoundManager()
{
	DeleteSoundMem(bgmSoundHandle);
	DeleteSoundMem(stoneBrealSoundHandle);
	DeleteSoundMem(takeCrystalSoundHandle);
	DeleteSoundMem(playerAttackSoundHandle);
	DeleteSoundMem(enemyDirSoundHandle);
	DeleteSoundMem(fireSoundHandle);
	DeleteSoundMem(playerMoveSoundHandle);
	DeleteSoundMem(playerLandingSoundHandle);
	DeleteSoundMem(terrorSoundHandle);
	DeleteSoundMem(laughSoundHandle);
	DeleteSoundMem(playerExplosionSoundHandle);
	DeleteSoundMem(gameEndSoundHandle);


}
