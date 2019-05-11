#pragma once

//クラスの前方宣言
class BlockBase;
class EffectCreater;

class BarrierItemBlock : public BlockBase
{
public:
	BarrierItemBlock(int sourceModelHandle, VECTOR startPos);
	~BarrierItemBlock();
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player)override;
private:
	int playingHandle;
	int playingHandleBlock;
};

