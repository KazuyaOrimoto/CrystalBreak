//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Camera;
class Stage;
class ActionManager;
class EffectCreater;
class FileManager;
class Sphere;
class SoundManager;
class InputManager;
class PlayerState;
class Score;

class Player
{
public:
	Player(ActionManager actionManager);
	~Player();
	void Update(Stage& stage, Camera & camera, ActionManager& actionManager, InputManager& inputManager);
	void Draw();
	void Attacked();
	void SwallowDark(VECTOR position);
	bool CanUseBomb();
	void NextStageCreate();
	bool IsSwallowDark();
	void BarrierItemGet();
	void BombItemGet();
	void PlayerDie();
	void PlayExplosion();
	void GameEnd(){gameEndFlag = true;}

    /**
        @brief  エフェクト発生位置のgetter関数
        @return 吸い込まれるエフェクトの発生ポジションを返す
    */
	VECTOR GetSwallowPosition() { return swallowDarkPosition; }
    /**
        @brief  プレイヤーのRotationのgetter関数
        @return 現在のモデルがどのくらい回転しているかを返す
    */
	VECTOR GetRotation() { return MV1GetRotationXYZ(modelHandle); }
    /**
        @brief  プレイヤーの当たり判定クラスのgetter関数
        @return 現在の当たり判定情報が入ったクラスのポインタを返す
    */
	Sphere& GetCollisionSphere() { return *collisionSphere; }
    /**
        @brief  プレイヤーの高さのgetter関数
        @return 現在のプレイヤーの高さを返す
    */
	float GetHight() { return exactlyPosition.y; }
    /**
        @brief  プレイヤーのポジションのgetter関数
        @return 現在のプレイヤーのポジションを返す
    */
	VECTOR GetPosition() { return position; }
    /**
        @brief  プレイヤーのキリのいいポジションのgetter関数
        @return 現在のプレイヤーのキリのいいポジションを返す
    */
	VECTOR GetExactlyPosition() { return exactlyPosition; }
    /**
        @brief  プレイヤーの要素位置のgetter関数
        @return 現在のプレイヤーの要素位置を返す
    */
	IndexPair GetIndexPair() { return indexPair; }
    /**
        @brief  プレイヤーがのgetter関数
        @return 現在のプレイヤーのキリのいいポジションを返す
    */
	bool GetIsAlive() { return isAlive; }
	bool GetPlayerExplosion() { return playerExplosion; }
	bool GetPlayingExplosion() { return playingExplosion; }
	int GetPlayerBombNum(){ return bombNum; }
	int GetHeight() { return height; }
	bool CheckGameEnd();
private:

	void ChangeIndexPair(ActionManager& actionManager);	//プレイヤーの要素位置の変更
	void ChangeExactlyPosition();
	void Barrier();
	void ChangePlayerState();
	void ChangeReflection();							//変更の反映

	const VECTOR START_POS = {	/* X */	(BLOCK_NUM_X * BLOCK_SIZE / 2) - (BLOCK_SIZE / 2) ,
								/* Y */	-220,
								/* Z */	0.0f	};
	const int INVINCIBLE_TIME = 60 * 2;					//無敵時間
	const float INVINCIBLE_OPACITY = 0.5f;				//無敵時の透明度
	const float NORMAL_OPACITY = 1.0f;


	int			modelHandle;							//プレイヤーのモデルハンドル
	VECTOR		position;								//プレイヤーのポジション
	VECTOR		exactlyPosition;						//マップ上でキリがいいポジション
	VECTOR		rotation;								//プレイヤーのローテーション
	VECTOR		scale;									//プレイヤーのスケール
	IndexPair	indexPair;								//プレイヤーの要素位置

	EffectCreater* effectCreater;
	SoundManager* soundManager;
	FileManager* fileManager;
	Sphere* collisionSphere;
	Score* score;

	bool swallowDarkFlag = false;
	VECTOR swallowDarkPosition;
	int swallowCount = 0;

	PlayerState* nowPlayerState;
	PlayerState* nextPlayerState;

	bool barrier = false;

	bool damaged = false;
	int damagedCount = 0;

	int bombNum = 5;
	bool isAlive;

	bool playerExplosion = false;
	bool playingExplosion = false;

	int height;
	bool gameEndFlag;
};

