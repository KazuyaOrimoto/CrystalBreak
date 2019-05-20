//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

//クラスの前方宣言
class BlockBase;
class EffectCreater;

class CrumblyBlock : public BlockBase
{
public:
	CrumblyBlock(int sourceModelHandle, VECTOR startPos);
	~CrumblyBlock();
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player) override;
	void Draw()override;
private:
	bool onRode = false;
	int breakToCount;
	VECTOR drawPos;
};

