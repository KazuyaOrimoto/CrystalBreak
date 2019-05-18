//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

//クラスの前方宣言
class BlockBase;
class EffectCreater;

class BreakableBlock : public BlockBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	BreakableBlock(int sourceModelHandle, VECTOR startPos);
	~BreakableBlock();
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player)override;
};
