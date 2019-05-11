//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "ActionManager.h"
#include "EffectCreater.h"
#include "Sphere.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "FileManager.h"
#include "PlayerState.h"
#include "Score.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
Player::Player(ActionManager actionManager)
{
	effectCreater = EffectCreater::GetInstance();
	soundManager = SoundManager::GetInstance();
	fileManager = FileManager::GetInstance();
	modelHandle = fileManager->GetPlayerModel();
	nextPlayerState = NULL;
	swallowDarkPosition = VECTOR_ZERO;
	indexPair = { 0,0 };
	position = START_POS;
	exactlyPosition = position;
	ChangeIndexPair(actionManager);
	actionManager.SetPlayerIndexPair(indexPair);
	collisionSphere = new Sphere();
	nowPlayerState = PlayerState::InitPlayerState();
	score = Score::GetInstance();
	collisionSphere->radius = MAGNIFICATION_RATE;
	collisionSphere->centerPos = position;
	isAlive = true;
	playerExplosion = false;
	height = 0;
	gameEndFlag = false;
	MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
	rotation = MV1GetRotationXYZ(modelHandle);
	scale = MV1GetScale(modelHandle);
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
Player::~Player()
{
	effectCreater->PlayerBarrierEffectEnd(position);
	delete(collisionSphere);
	MV1DeleteModel(modelHandle);
	delete(nowPlayerState);
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void Player::Update(Stage& stage, Camera& camera, ActionManager& actionManager, InputManager& inputManager)
{
	if (!isAlive)
	{
		return;
	}
	//それぞれのステートの処理をさせる
	nextPlayerState = nowPlayerState->Update(*this, stage, inputManager, actionManager);

	//変更された値の反映
	ChangeReflection();

	//必要なポジションの変更
	ChangeExactlyPosition();
	ChangeIndexPair(actionManager);

	//ステートの変更
	ChangePlayerState();

	//カメラのポジションの変更
	camera.SetTargetPosition(exactlyPosition);
	collisionSphere->centerPos = position;

	//バリア
	Barrier();

	//ダメージを受けて生きているとき
	if (damaged)
	{
		MV1SetOpacityRate(modelHandle, INVINCIBLE_OPACITY);
		if (damagedCount > INVINCIBLE_TIME)
		{
			damaged = false;
			MV1SetOpacityRate(modelHandle, NORMAL_OPACITY);
		}
		else
		{
			damagedCount++;
		}
	}
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

//-----------------------------------------------------------------------------//
//								攻撃されたとき
//-----------------------------------------------------------------------------//
void Player::Attacked()
{
	if (barrier)
	{
		effectCreater->PlayerBarrierEffectEnd(position);
		barrier = false;
		damaged = true;
		damagedCount = 0;
		return;
	}
	if (damaged)
	{
		return;
	}
	playerExplosion = true;
}

//-----------------------------------------------------------------------------//
//								吸い込まれるとき
//-----------------------------------------------------------------------------//
void Player::SwallowDark(VECTOR position)
{
	swallowDarkFlag = true;
	swallowDarkPosition = position;
}

//-----------------------------------------------------------------------------//
//						ゲーム終了フラグが立っているか
//-----------------------------------------------------------------------------//
bool Player::CheckGameEnd()
{
	return gameEndFlag;
}

//-----------------------------------------------------------------------------//
//								要素位置の変更
//-----------------------------------------------------------------------------//
void Player::ChangeIndexPair(ActionManager& actionManager)
{
	indexPair = { int(exactlyPosition.x / BLOCK_SIZE) ,int(exactlyPosition.y / -BLOCK_SIZE) };
	actionManager.SetPlayerIndexPair(indexPair);
}

//-----------------------------------------------------------------------------//
//						マス丁度のときのポジションの変更
//-----------------------------------------------------------------------------//
void Player::ChangeExactlyPosition()
{
	exactlyPosition.x = (int)(position.x / BLOCK_SIZE) * BLOCK_SIZE;
	exactlyPosition.y = (int)(position.y / BLOCK_SIZE) * BLOCK_SIZE;
	exactlyPosition.z = (int)(position.z / BLOCK_SIZE) * BLOCK_SIZE;
}

//-----------------------------------------------------------------------------//
//								バリアの処理
//-----------------------------------------------------------------------------//
void Player::Barrier()
{
	if (IsSwallowDark())
	{
		return;
	}
	if (barrier)
	{
		effectCreater->PlayerBarrierEffectSetPosition(position);
	}
}

//-----------------------------------------------------------------------------//
//						次のステートが変わっていたら変更する
//-----------------------------------------------------------------------------//
void Player::ChangePlayerState()
{
	if (nextPlayerState != nowPlayerState)
	{
		nextPlayerState->SetRotation(rotation);
		nextPlayerState->passPreviewDirection(nowPlayerState->GetDirecion());
		delete(nowPlayerState);
		nowPlayerState = nextPlayerState;
		nextPlayerState = NULL;
	}
}

void Player::ChangeReflection()
{
	//変更分の値の反映
	position = VAdd(position, nowPlayerState->GetMoveAmount());
	rotation = nowPlayerState->GetRotation();
	scale = VAdd(scale, nowPlayerState->GetScaleAmount());

	score->AddHeight(-(int)(nowPlayerState->GetMoveAmount().y));

	if (scale.x < VECTOR_ZERO.x)
	{
		scale.x = VECTOR_ZERO.x;
	}
	if (scale.y < VECTOR_ZERO.y)
	{
		scale.y = VECTOR_ZERO.y;
	}
	if (scale.z < VECTOR_ZERO.z)
	{
		scale.z = VECTOR_ZERO.z;
	}



	//変更された値をモデルに反映
	MV1SetPosition(modelHandle, VAdd(position, nowPlayerState->GetAnimationPosition()));
	MV1SetRotationXYZ(modelHandle, rotation);
	MV1SetScale(modelHandle, scale);
}

//-----------------------------------------------------------------------------//
//								爆弾を使えるか
//-----------------------------------------------------------------------------//
bool Player::CanUseBomb()
{
	if (bombNum > 0)
	{
		bombNum--;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//								次のステージを作る際の処理
//-----------------------------------------------------------------------------//
void Player::NextStageCreate()
{
	position.y += NEXT_STAGE_CREATE_ADD_POSITION;
}

//-----------------------------------------------------------------------------//
//								吸い込まれている状態か
//-----------------------------------------------------------------------------//
bool Player::IsSwallowDark()
{
	return swallowDarkFlag;
}

//-----------------------------------------------------------------------------//
//							バリアアイテムを取った時
//-----------------------------------------------------------------------------//
void Player::BarrierItemGet()
{
	if (barrier == false)
	{
		effectCreater->CreatePlayerBarrierEffect(position);
		barrier = true;
	}
	barrier = true;
}

//-----------------------------------------------------------------------------//
//							爆弾のアイテムを取った時
//-----------------------------------------------------------------------------//
void Player::BombItemGet()
{
	bombNum++;
}

//-----------------------------------------------------------------------------//
//							プレイヤーが死んだとき
//-----------------------------------------------------------------------------//
void Player::PlayerDie()
{
	isAlive = false;
	gameEndFlag = true;
}

//-----------------------------------------------------------------------------//
//						プレイヤーが爆発して死ぬとき
//-----------------------------------------------------------------------------//
void Player::PlayExplosion()
{
	playingExplosion = true;
}
