#pragma once

//クラスの前方宣言
class Scenebase;
class InputManager;

class ResultScene : public SceneBase
{
public:
	ResultScene(int score,int height);
	~ResultScene()override;
	SceneBase* Update() override;
	void Draw() override;
private:
	void DrawNumber(int graphHandle[], int x, int y, int number, int length);

	InputManager* inputManager;
	const int score;
	const int height;
	int sumScore;
	int resultGraph;
	int numberGraph40[10];
	int numberGraph48[10];

	int previewScore;
	int previewHeight;
	int previewSumScore;

	bool drawEnd;
};

