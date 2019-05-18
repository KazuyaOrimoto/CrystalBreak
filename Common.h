#pragma once

//-----------------------------------------------------------------------------//
//全ファイル共通ライブラリ
//-----------------------------------------------------------------------------//
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

class EnemyBase;
class BlockBase;
struct IndexPair;
class Fire;

using namespace std;

typedef tagVECTOR VECTOR;
typedef std::vector<EnemyBase*> EnemyVector;
typedef std::vector<BlockBase*> BlockVector;
typedef std::map<IndexPair, BlockBase*> BlockMap;
typedef std::vector<Fire*> FireVector;

//-----------------------------------------------------------------------------//
//全ファイル共通の定数
//-----------------------------------------------------------------------------//
const static int SCREEN_SIZE_X = 1920;
const static int SCREEN_SIZE_Y = 1080;
const static int COLOR_BIT = 32;
const static float SEMICIRCLE = 180.0f;
const static VECTOR VECTOR_ZERO = VGet(0.0f, 0.0f, 0.0f);   //全要素がゼロのベクトル
const static VECTOR MOVE_RIGHT_ROTETION = VGet(0.0f, -80.0f * DX_PI_F / SEMICIRCLE, 0.0f);
const static VECTOR MOVE_LEFT_ROTETION = VGet(0.0f, 80.0f * DX_PI_F / SEMICIRCLE, 0.0f);
const static int SCREEN_W = 1920;                           //スクリーンサイズ（横）
const static int SCREEN_H = 1080;                           //スクリーンサイズ（縦）
const static int BLOCK_NUM_X = 9;                           //Ｘ方向のブロック数
const static int BLOCK_NUM_Y = 80;                          //Ｚ方向のブロック数
const static float BLOCK_SIZE = 20.0f;                      //ブロックのサイズ
const static float CAMERA_Y = 2000.0f;                      //カメラの高さ
const static float LERP_NUM = 0.05f;                        //ラープで使う定数（0～1）
const static float GRAVITY_ACCELERATION = 2.0;              //重力加速度
const static float FALL_MAX_SPEED = 10.0f;                  //落下するときの最高速度
const static float PLAYER_MOVE_SPEED = 2.0f;                //プレイヤーの移動スピード
const static float ENEMY_MOVE_SPEED = 0.5f;                 //エネミーの移動するスピード
const static float FIRE_MOVE_SPEED = 2.0f;                  //火の玉の動くスピード
const static float MAGNIFICATION_RATE = 10.0f;              //モデルの拡大率
const static float FIRE_MAGNIFICATION_RATE = 5.0;           //モデルの拡大率
const static float BLOCK_MAGNIFICATION_RATE = 10.0f;        //モデルの拡大率
const static float PLAYER_SCALE_AMOUNT = 1.0f;
const static int FIRE_BLOCK_INCREASE_NUM = 5;
const static int ENEMY_INCREASE_NUM = 20;
const static float ENEMY_FALL_SPEED = 2.0;
const static int CRUMBLY_TIME = 60 * 1;
const static int BOMB_BREAK_EIDTH_X = 3;
const static int BOMB_BREAK_EIDTH_Y = 3;
const static float NEXT_STAGE_CREATE_ADD_POSITION = BLOCK_NUM_Y * BLOCK_SIZE;
const static int CREATE_ITEM_NUM = 20;
const static int FIRING_COUNT_TIME = 60 * 2;                //炎を発射するまでのカウント
const static int FIRE_CREATE_TIME = 60 * 6;
const static float CAMERA_SCREEN_CENTER_X = SCREEN_W / 4.0f;
const static float CAMERA_SCREEN_CENTER_Y = SCREEN_H / 2.0f;
const static int ALPHA_MAX = 255;

struct IndexPair
{
	int x;
	int y;
	bool operator < (const IndexPair& value) const
	{
		int compareNum = x * 100 + y;
		int conpareValue = value.x * 100 + value.y;
		if (compareNum < conpareValue)
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}

	IndexPair IndexPairRight()
	{
		IndexPair right = { x + 1 ,y };
		return right;
	}
	IndexPair IndexPairLeft()
	{
		IndexPair left = { x - 1 ,y };
		return left;
	}
	IndexPair IndexPairUp()
	{
		IndexPair up = { x ,y - 1 };
		return up;
	}
	IndexPair IndexPairDown()
	{
		IndexPair down = { x  ,y + 1 };
		return down;
	}
};

enum BlockName
{
	NO_BLOCK,
	WALL,
	BLOCK,
	CRUMBLY_BLOCK,
	FIRE_CUBE,
	SHARP_BLOCK
};

enum EnemyName
{
	NO_ENEMY,
	FIRE_FLY = 6,
	BOAR = 7
};

enum Direction
{
	NO_DIRECTION,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum Action
{
	NO_ACTION,
	MOVE,
	ATTACK
};
