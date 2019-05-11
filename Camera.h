#pragma once

class Camera
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	Camera();
	~Camera();
	void Update();
	void SetTargetPosition(VECTOR targetPosition);			//目標地点の座標をセットする
	void NextStageCreate();
	void SetPosition();
private:
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	VECTOR position;										//カメラの座標
	VECTOR viewPointPosition;								//カメラの注視点の座標
	VECTOR targetPosition;									//目標地点の座標
	float positionDifferenceY;								//カメラのY座標と目標地点のY座標の差
};
