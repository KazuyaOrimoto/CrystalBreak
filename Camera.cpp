//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "Camera.h"
#include "EffectCreater.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
Camera::Camera()
{
	position = VGet(BLOCK_SIZE * BLOCK_NUM_X / 2 - 10, -180, -200);
	targetPosition = VECTOR_ZERO;
	SetCameraNearFar(50.0f, 300.0f);
	//SetCameraScreenCenter(CAMERA_SCREEN_CENTER_X, CAMERA_SCREEN_CENTER_Y);
	EffectCreater* effectCreater = EffectCreater::GetInstance();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
Camera::~Camera()
{
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void Camera::Update()
{
	//ターゲットのポジションとカメラのポジションの差を求める
	positionDifferenceY = targetPosition.y - position.y;
	//カメラの位置とターゲットの位置がブロックサイズより大きくなったら
	if (positionDifferenceY > BLOCK_SIZE)
	{
		position = VAdd(position, VGet(0.0f, positionDifferenceY * LERP_NUM,0.0f));
	}
	else if (positionDifferenceY < -BLOCK_SIZE)
	{
		position = VAdd(position, VGet(0.0f, positionDifferenceY * LERP_NUM, 0.0f));
	}
	//カメラのターゲットの位置をカメラのポジションからまっすぐ見た位置に設定
	viewPointPosition = VGet(position.x, position.y, 0.0f);
	// カメラの位置と向きをセットする
	SetCameraPositionAndTarget_UpVecY(position, viewPointPosition);
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}

//-----------------------------------------------------------------------------//
//								目標地点の座標をセット
//-----------------------------------------------------------------------------//
void Camera::SetTargetPosition(VECTOR targetPos)
{
	targetPosition = targetPos;
}

void Camera::NextStageCreate()
{
	position.y += NEXT_STAGE_CREATE_ADD_POSITION;
}

void Camera::SetPosition()
{
	SetCameraPositionAndTarget_UpVecY(position, viewPointPosition);
}


